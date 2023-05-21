//ELECTION INTEGRITY CHECKER - PROJECT WRITTEN BY ALEXANDRU MICLEA
//FMI UNIBUC 2023

#include <iostream>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;

// abstract class

// every class must have
// empty c
// copy c
// param c
// = op
// destructor
// read
// write
// create read and write from file

// todo redo constructors and = 

class ExistingVoter : public exception {
public:
	const char* what() const throw() { return "Acest votant exista deja!\nMasuri antifrauda au fost luate.\n"; };
};
class ExistingCandidate : public exception {
public:
	const char* what() const throw() { return "Acest candidat exista deja!\nMasuri antifrauda au fost luate.\n"; };
};
class InvalidVoter : public exception {
public:
	const char* what() const throw() { return "CNP-ul folosit nu figureaza pe lista de votanti inregistrati!\n"; };
};
class InvalidCandidate : public exception {
public:
	const char* what() const throw() { return "Optiunea aleasa nu figureaza pe lista de candidati!\n"; };
};
class ExistingVote : public exception {
public:
	const char* what() const throw() { return "Votul acesta a fost facut deja!\nMasuri antifrauda au fost luate.\n"; };
};
class WrongID : public exception {
public:
	const char* what() const throw() { return "CNP-ul introdus nu este valid (varsta prea mica)/numar invalid!\n"; };
};
// todo use
class InsufCandidates : public exception {
public:
	const char* what() const throw() { return "Nu sunt suficienti candidati in cursa!\n"; };
};

// todo template class
// a class that for each type of election can make a candidate/voter valid

//template <typename Proces>
//class Election_Sway {
//	Proces p;
// 
//};

class Alegere {
protected:
	const double eps = 1e-6;
	set <long long> votant; // cnp-urile se pun individual aici
	set<long long> invalidV; // cine e invalidat va fi trimis aici
	list <string> candidat;
	list <string> invalidC;
	map <string, vector<long long>> vot; // candidat, cnp
	map <string, float> rezultate;
	bool electionRan;

	bool parseID(long long id) {
		long long mask = 1;
		for (int i = 1; i <= 13; i++) mask *= 10;

		int firstDig = (id % mask) / (mask / 10);
		mask /= 10;
		if (firstDig == 5 || firstDig == 6) {
			int year = 10 * ((id % mask) / (mask / 10)) + (id % (mask / 10)) / (mask / 100);
			mask /= 100;
			if (year > 5) return 0; // view cam brut, vom reveni
		}
		else if (firstDig == 3 || firstDig == 4 || firstDig == 7 || firstDig == 8 || firstDig == 9 || firstDig == 0) return false;


		return true;
	}

	bool valideazaCandidat(string opt) {
		try {
			for (auto& x : invalidC) {
				if (x == opt) throw InvalidCandidate();
			}
			for (auto& x : candidat) {
				if (x == opt) {
					throw ExistingCandidate();
				}
			}
		}
		catch (ExistingCandidate& e) {
			cout << e.what();
			this->candidat.erase(find(this->candidat.begin(), this->candidat.end(), opt));
			this->invalidC.push_back(opt);
			return false;
		}
		catch (InvalidCandidate& i) {
			cout << i.what();
			return false;
		}

		cout << "Candidatul a fost validat si adaugat in baza de date cu succes!\n";
		return true;
	}

	bool valideazaVotant(long long cnp) {
		try {
			if (!parseID(cnp)) throw WrongID();
			for (auto& x : invalidV) {
				if (x == cnp) throw InvalidVoter();
			}
			for (auto& x : votant) {
				if (x == cnp) {
					throw ExistingVoter();
				}
			}
		}
		catch (WrongID& wi) {
			cout << wi.what();
			return false;
		}
		catch (ExistingVoter& e) {
			cout << e.what();
			this->votant.erase(cnp);
			this->invalidV.insert(cnp);
			return false;
		}
		catch (InvalidVoter& i) {
			cout << i.what();
			return false;
		}

		cout << "Votantul a fost validat si adaugat in baza de date cu succes!\n";
		return true;
	}

	bool valideazaVot(long long cnp, string opt) {
		try {
			for (auto& x : invalidV) {
				if (x == cnp) throw InvalidVoter();
			}
			for (auto& x : invalidC) {
				if (x == opt) throw InvalidCandidate();
			}
			bool registered = false;
			for (auto& x : votant) {
				if (x == cnp) registered = true;
			}
			if (!registered) throw InvalidVoter();
			bool cand = false;
			for (auto& x : candidat) {
				if (x == opt) cand = true;
			}
			if (!cand) throw InvalidCandidate();
			if (find(vot[opt].begin(), vot[opt].end(), cnp) != vot[opt].end()) {
				throw ExistingVote();
			}

		}
		catch (InvalidVoter& iv) {
			cout << iv.what();
			return false;
		}
		catch (InvalidCandidate& ic) {
			cout << ic.what();
			return false;
		}
		catch (ExistingVote& ev) {
			cout << ev.what();
			this->votant.erase(cnp);
			this->invalidV.insert(cnp);

			while (find(vot[opt].begin(), vot[opt].end(), cnp) != vot[opt].end()) {
				vot[opt].erase(find(vot[opt].begin(), vot[opt].end(), cnp));
			}

			return false;
		}

		cout << "Votul a fost inregistrat cu succes!\n";
		return true;
	}

	void incCitire(istream& in) {

		if (!candidat.empty() && !votant.empty()) {
			cout << "Deja exista date despre alegatori/alesi. Doriti recitirea lor?(y/n)\n";
			char ans = 0;
			in >> ans;
			try {
				while (ans != 'y' && ans != 'n') {
					in >> ans;
					ans = tolower(ans);
				}
				throw ans;
			}
			catch (char c) {
				if (c == 'y') citireDate(in);
			}
		}
		else {
			citireDate(in);
		}

		cout << "Doriti inceperea alegerilor?(y/n)\n";
		char ans = 0;
		try {
			while (ans != 'y' && ans != 'n') {
				in >> ans;
				ans = tolower(ans);
			}
			throw ans;
		}
		catch (char c) {
			if (c == 'y') procAlegere(in);
		}
	}

	istream& citireDate(istream& in) {
		cout << "Pentru o buna desfasurare a procesului electoral, se vor citi CNP-urile votantilor, " << endl;
		cout << "urmat de lista de candidati. Dupa care se vor exprima dorintele de vot." << endl;
		string inp = "";
		while (true) {
			cout << "Introduceti CNP-ul votantului (enter x2 pentru a inceta introducerea): " << endl;
			getline(in, inp);
			stringstream id(inp);
			long long num = 0;
			if (id >> num || inp == "") {
				if (num == 0) break;
				if (inp == "") break;
				if (valideazaVotant(num)) {
					this->votant.insert(num);
				}
			}
			else {
				cout << "Va rog sa introduceti un numar!\n";
			}

		}
		string cand = "";
		getline(in, cand); // trebuie pt ca e pretentios 
		while (true) {
			cout << "Introduceti numele candidatului (enter pentru a inceta introducerea): " << endl;
			getline(in, cand);
			transform(cand.begin(), cand.end(), cand.begin(), [](char c) {return tolower(c); }); // view lambda expresii suntem smenari
			if (cand == "") break;
			if (valideazaCandidat(cand)) {
				this->candidat.push_back(cand);
			}
		}

		return in;
	}

	istream& preluareVoturi(istream& in) {

		long long cnp = 0;
		string cand = "";
		while (true) {
			cout << "Introduceti votantul: " << endl;
			in >> cnp;
			getline(in, cand);
			cout << "Introduceti candidatul: " << endl;
			getline(in, cand);
			transform(cand.begin(), cand.end(), cand.begin(), [](char c) {return tolower(c); });
			if (cnp == 0 && cand == "") break;
			if (valideazaVot(cnp, cand)) {
				vot[cand].push_back(cnp);
			}
		}

		return in;
	}
	virtual istream& procAlegere(istream&) = 0;

public:

	Alegere() { this->electionRan = false; }
	Alegere(const Alegere& obj) {
		this->votant = obj.votant;
		this->invalidV = obj.invalidV;
		this->candidat = obj.candidat;
		this->invalidC = obj.invalidC;
		this->vot = obj.vot;
		this->rezultate = obj.rezultate;
		this->electionRan = obj.electionRan;
	}
	Alegere(set<long long> votant_, set<long long> iv_, list<string> candidat_, list<string> ic_, map<string, vector<long long>> vot_, map <string, float> rezultate_, bool electionRan_) {
		this->votant = votant_;
		this->invalidV = iv_;
		this->candidat = candidat_;
		this->invalidC = ic_;
		this->vot = vot_;
		this->rezultate = rezultate_;
		this->electionRan = electionRan_;
	}
	Alegere& operator=(const Alegere& obj) {
		if (this != &obj) {
			this->votant = obj.votant;
			this->invalidV = obj.invalidV;
			this->candidat = obj.candidat;
			this->invalidC = obj.invalidC;
			this->vot = obj.vot;
			this->rezultate = obj.rezultate;
			this->electionRan = obj.electionRan;
		}
		return *this;
	}

	virtual ~Alegere() {}
};

class Prezidentiale : public Alegere {
protected:
	int numarTururi;
	vector<map<string, float>> rezultateTur;

	istream& procAlegere(istream& in) {
		cout << "Urmeaza a se citi voturile, urmat de validarea procesului electoral: \n";
		cout << "Pentru a inceta citirea, apasati 0 apoi enter de 2 ori\n";
		long long cnp = 0;
		string cand = "";
		while (true) {
			cout << "Incepe turul " << numarTururi << "!\n";
			preluareVoturi(in);
			if (derulareAlegere()) {
				electionRan = true;
				cout << "Alegerile au luat sfarsit!\n";
				break;
			}
			else {
				numarTururi++;
			}
		}

		return in;
	}
	bool derulareAlegere() {

		map <string, float> tur;
		multimap<float, string, greater<float>> aux;

		int voturiTotale = 0;

		for (auto& x : vot) {
			tur[x.first] += x.second.size();
			voturiTotale += x.second.size();
		}
		for (auto& x : tur) {
			x.second /= voturiTotale;
		}

		for (auto& x : tur) {
			aux.insert({ x.second, x.first });
		}

		cout << "Rezultatele turului " << numarTururi << " sunt urmatoarele:\n";
		for (auto& x : aux) {
			cout << x.second << ": " << x.first * 100 << "%\n";
		}
		this->rezultateTur.push_back(tur);
		if ((aux.begin()->first + eps) <= 0.5f) {
			// ne ducem in turul +1

			vot.clear();
			if (numarTururi == 1) {
				candidat.clear();
				int candidati = 1;
				for (auto i = aux.begin(); i != aux.end() && candidati <= 2; i++)
					candidat.push_back((*i).second), candidati++;
				//for (auto i = candidat.begin(); i != candidat.end(); i++) cout << (*i) << ' ';
			}
			return false;
		}

		return true;
	}
public:
	Prezidentiale() {
		this->numarTururi = 1;
	};
	Prezidentiale(const Prezidentiale& obj) :Alegere(obj) { this->numarTururi = obj.numarTururi, this->rezultateTur = obj.rezultateTur; };
	Prezidentiale(set<long long> votant_, set<long long> iv_, list<string> candidat_, list<string> ic_, map<string, vector<long long>> vot_, map <string, float> rezultate_, bool electionRan_, int numarTururi_, vector<map<string, float>> rezultateTur_) 
	:Alegere(votant_, iv_, candidat_, ic_, vot_, rezultate_, electionRan_)
	{
		this->numarTururi = numarTururi_, this->rezultateTur = rezultateTur_;
	};

	Prezidentiale& operator=(const Prezidentiale& obj) {
		if (this != &obj) {
			Alegere::operator=(obj);
			this->rezultateTur = obj.rezultateTur;
			this->numarTururi = obj.numarTururi;
		}
		return *this;
	}

	~Prezidentiale() {}

	friend ostream& operator<<(ostream& out, const Prezidentiale& obj) {

		if (!obj.electionRan) {
			out << "Aceasta alegere inca nu s-a desfasurat!\n";
		}
		else {
			out << "Aceasta alegere a fost una prezidentiala." << endl;
			out << "Aceasta alegere s-a desfasurat in " << obj.numarTururi << " tururi." << endl;
			out << "Rezultatele pentru fiecare tur sunt urmatoarele: \n\n";
			int tur = 1;
			for (auto& x : obj.rezultateTur) {
				out << "Turul " << tur++ << ": \n";
				for (auto& y : x) {
					out << y.first << ": " << y.second * 100 << "%\n";
				}
				out << '\n';
			}
			out << "Castigatorul alegerilor este " << (obj.rezultateTur.end() - 1)->rbegin()->first << ". Felicitari!\n";
		}

		return out;
	}

	friend istream& operator>>(istream& in, Prezidentiale& obj) {
		obj.incCitire(in);

		return in;
	}
};

class Parlamentare : public Alegere {
protected:
	istream& procAlegere(istream& in) {
		cout << "Urmeaza a se citi voturile, urmat de validarea procesului electoral: \n";
		cout << "Pentru a inceta citirea, apasati 0, apoi enter x2\n"; // todo fa mai frumos
		long long cnp = 0;
		string cand = "";
		while (true) {
			cout << "Introduceti votantul: " << endl;
			in>>cnp;
			getline(in, cand);
			cout << "Introduceti candidatul: " << endl;
			getline(in, cand);
			transform(cand.begin(), cand.end(), cand.begin(), [](char c) {return tolower(c); });
			if (cnp == 0 && cand == "") break;
			if (valideazaVot(cnp, cand)) {
				vot[cand].push_back(cnp);
			}
		}
		derulareAlegere();
		cout << "Alegerile au luat sfarsit!\n";

		return in;
	}

	bool derulareAlegere() {

		map <string, float> voturi;

		int voturiTotale = 0;

		for (auto& x : this->vot) {
			voturi[x.first] += x.second.size();
			voturiTotale += x.second.size();
		}
		for (auto& x : voturi) {
			x.second /= voturiTotale;
		}

		cout << "Rezultatele sunt urmatoarele:\n";
		for (auto& x : voturi) {
			cout << x.first << ": " << x.second * 100<< "%\n";
		}
		rezultate = voturi;

		electionRan = true;
		return true;
	}
public:
	Parlamentare() {};
	Parlamentare(const Parlamentare& obj) :Alegere(obj) {};
	Parlamentare(set<long long> votant_, set<long long> iv_, list<string> candidat_, list<string> ic_, map<string, vector<long long>> vot_, map <string, float> rezultate_, bool electionRan_) 
	:Alegere(votant_, iv_, candidat_, ic_, vot_, rezultate_, electionRan_) {};

	Parlamentare& operator=(const Parlamentare& obj) {
		if (this != &obj) {
			Alegere::operator=(obj);
		}
		return *this;
	}

	~Parlamentare() {}

	friend ostream& operator<<(ostream& out, const Parlamentare& obj) { 
		if (!obj.electionRan) {
			out << "Aceasta alegere inca nu s-a desfasurat!\n";
		}
		else {
			out << "Aceasta alegere a fost una parlamentara." << endl;
			out << "Rezultatele alegerilor sunt urmatoarele: \n\n";
			for (auto& y : obj.rezultate) {
				out << y.first << ": " << y.second * 100 << "%\n";
			}
			out << "Castigatorul alegerilor este " << (obj.rezultate.rbegin())->first << ". Felicitari!\n";
		}

		return out;
	}

	friend istream& operator>>(istream& in, Parlamentare& obj) { 
		
		obj.incCitire(in);

		return in;
	}

	
};

class EuroParlamentare : public Parlamentare {
protected:
	map<string, string> afiliereBloc; // key = partid, value = bloc ex(PNL, PPE)/

	bool derulareAlegere() {

		map <string, float> voturi;

		int voturiTotale = 0;

		for (auto& x : this->vot) {
			voturi[x.first] += x.second.size();
			voturiTotale += x.second.size();
		}
		cout << voturiTotale << ' ';
		for (auto& x : voturi) {
			x.second /= voturiTotale;
		}

		cout << "Rezultatele sunt urmatoarele:\n";
		for (auto& x : voturi) {
			cout << x.first << ": " << x.second * 100 << "%\n";
		}
		this->rezultate = voturi;

		electionRan = true;
		return true;
	}

	istream& procAlegere(istream& in) {

		cout << "Inainte de a incepe procedura de citire a voturilor, stabiliti legatura intre partid\n";
		cout << "si blocul in care este afiliat respectivul partid: \n";
		string bloc = "";
		getline(in, bloc);

		for (auto& x : candidat) {
			cout << x << ": ";
			getline(in, bloc);
			afiliereBloc[x] = bloc;
			cout << '\n';
		}

		cout << "Urmeaza a se citi voturile, urmat de validarea procesului electoral: \n";
		cout << "Pentru a inceta citirea, apasati 0 apoi enter de 2 ori\n"; // todo fa mai frumos
		long long cnp = 0;
		string cand = "";
		while (true) {
			cout << "Introduceti votantul: " << endl;
			in >> cnp;
			getline(in, cand);
			cout << "Introduceti candidatul: " << endl;
			getline(in, cand);
			transform(cand.begin(), cand.end(), cand.begin(), [](char c) {return tolower(c); });
			if (cnp == 0 && cand == "") break;
			if (valideazaVot(cnp, cand)) {
				vot[cand].push_back(cnp);
			}
		}
		derulareAlegere();
		cout << "Alegerile au luat sfarsit!\n";

		return in;
	}

public:
	EuroParlamentare() {};

	EuroParlamentare(const EuroParlamentare& obj) :Parlamentare(obj) {this->afiliereBloc = obj.afiliereBloc;};
	EuroParlamentare(set<long long> votant_, set<long long> iv_, list<string> candidat_, list<string> ic_, map<string, vector<long long>> vot_, map <string, float> rezultate_, bool electionRan_, map<string, string> afiliereBloc_)
		:Parlamentare(votant_, iv_, candidat_, ic_, vot_, rezultate_, electionRan_) {this->afiliereBloc = afiliereBloc_;};

	EuroParlamentare& operator=(const EuroParlamentare& obj) {
		if (this != &obj) {
			Parlamentare::operator=(obj);
			this->afiliereBloc = afiliereBloc;
		}
		return *this;
	}

	~EuroParlamentare() {}

	friend ostream& operator<<(ostream& out, const EuroParlamentare& obj) {
		if (!obj.electionRan) {
			out << "Aceasta alegere inca nu s-a desfasurat!\n";
		}
		else {
			out << "Aceasta alegere a fost una europarlamentara." << endl;
			out << "Rezultatele alegerilor sunt urmatoarele: \n\n";
			for (auto& y : obj.rezultate) {
				out << y.first << "(" << obj.afiliereBloc.find(y.first)->second << "): " << y.second * 100 << "%\n";
			}
			out << "Castigatorul alegerilor este " << (obj.rezultate.rbegin())->first << "(" << obj.afiliereBloc.find((obj.rezultate.rbegin())->first)->second << ")" << ". Felicitari!\n";
		}

		return out;
	}
	friend istream& operator>>(istream& in, EuroParlamentare& obj) { 
	
		obj.incCitire(in);

		return in;
	}
};

class Locale : public Alegere {
protected:
	string zona;
public:
	Locale() { this->zona = ""; };

	Locale(const Locale& obj) :Alegere(obj) { this->zona = obj.zona; };
	Locale(set<long long> votant_, set<long long> iv_, list<string> candidat_, list<string> ic_, map<string, vector<long long>> vot_, map <string, float> rezultate_, bool electionRan_, string zona_)
		:Alegere(votant_, iv_, candidat_, ic_, vot_, rezultate_, electionRan_) {
			this->zona = zona_;
		};

	Locale& operator=(const Locale& obj) {
		if (this != &obj) {
			Alegere::operator=(obj);
		}
		return *this;
	}

	~Locale() {}

	istream& procAlegere(istream& in) {
		cout << "Inainte de a citi voturile, specificati regiunea in care se va desfasura alegerea:\n";
		getline(in, this->zona);
		getline(in, this->zona);

		cout << "Urmeaza a se citi voturile, urmat de validarea procesului electoral: \n";
		cout << "Pentru a inceta citirea, apasati 0 apoi enter de 2 ori\n";

		preluareVoturi(in);
		
		derulareAlegere();
		cout << "Alegerile au luat sfarsit!\n";

		return in;
	}

	bool derulareAlegere() {

		map <string, float> voturi;

		int voturiTotale = 0;

		for (auto& x : this->vot) {
			voturi[x.first] += x.second.size();
			voturiTotale += x.second.size();
		}
		for (auto& x : voturi) {
			x.second /= voturiTotale;
		}

		cout << "Rezultatele sunt urmatoarele:\n";
		for (auto& x : voturi) {
			cout << x.first << ": " << x.second * 100 << "%\n";
		}
		rezultate = voturi;

		electionRan = true;
		return true;
	}

	friend ostream& operator<<(ostream& out, const Locale& obj) {
		if (!obj.electionRan) {
			out << "Aceasta alegere inca nu s-a desfasurat!\n";
		}
		else {
			out << "Aceasta alegere a fost una locala. S-a desfasurat pentru zona " << obj.zona << "." << endl;
			out << "Rezultatele alegerilor sunt urmatoarele: \n\n";
			for (auto& y : obj.rezultate) {
				out << y.first << ": " << y.second * 100 << "%\n";
			}
			out << "\nCastigatorul alegerilor este " << (obj.rezultate.rbegin())->first << ". Felicitari!\n";
		}

		return out;
	}
	friend istream& operator>>(istream& in, Locale& obj) { 
		obj.incCitire(in);

		return in;
	}
};

class Menu {
private:
	static Menu* instance;
	Menu() = default;
	Menu(const Menu& menu) = delete;
public:
	static Menu* getInstance() {
		if (instance == nullptr) {
			instance = new Menu();
		}
		return instance;
	}
	//void printExist() {cout << "Hello!";}
};
Menu* Menu::instance = nullptr;

int main() {
	Menu* meniu = Menu::getInstance();

	EuroParlamentare p;
	cin >> p;
	cout << p;
	return 0;
}