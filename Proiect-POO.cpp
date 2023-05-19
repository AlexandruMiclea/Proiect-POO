//ELECTION INTEGRITY CHECKER - PROJECT WRITTEN BY ALEXANDRU MICLEA
//FMI UNIBUC 2023

#include <iostream>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <string>
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

class ExistingVoter : public exception {
public:
	const char* what() const throw() {return "Acest votant exista deja!\nMasuri antifrauda au fost luate.\n"; };
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
		catch (WrongID& wi){
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
		catch (InvalidVoter& iv){
			cout << iv.what();
			return false;
		}
		catch (InvalidCandidate& ic) {
			cout << ic.what();
			return false;
		}
		catch (ExistingVote& ev){
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

public:
	virtual bool derulareAlegere() = 0;

	Alegere() {this->electionRan = false;}
	Alegere(const Alegere& obj) {
		this->votant = obj.votant;
		this->invalidV = obj.invalidV;
		this->candidat = obj.candidat;
		this->invalidC = obj.invalidC;
		this->vot = obj.vot;
		this->electionRan = obj.electionRan;
	}
	Alegere(set<long long> votant_, set<long long> iv_, list<string> candidat_, list<string> ic_, map<string, vector<long long>> vot_, bool electionRan_) {
		this->votant = votant_;
		this->invalidV = iv_;
		this->candidat = candidat_;
		this->invalidC = ic_;
		this->vot = vot_;
		this->electionRan = electionRan_;
	}
	Alegere& operator=(const Alegere& obj) {
		if (this != &obj) {
			this->votant = obj.votant;
			this->invalidV = obj.invalidV;
			this->candidat = obj.candidat;
			this->invalidC = obj.invalidC;
			this->vot = obj.vot;
			this->electionRan = obj.electionRan;
		}
		return *this;
	}

	virtual ~Alegere() {}

	virtual ostream& afisare(ostream& out) const {
		out << "In cadrul alegerilor au existat un numar de " << this->votant.size() << " votanti ale caror voturi au fost validate." << endl;
		out << "Candidatii care au participat in alegeri si numarul lor de voturi este urmatorul: " << endl;
		for (auto& x : this->vot) {
			out << x.first << ": " << x.first.size() << endl;
		}

		return out;
	}

	virtual istream& citire(istream& in) {
		cout << "Pentru o buna desfasurare a procesului electoral, se vor citi CNP-urile votantilor, " << endl;
		cout << "urmat de lista de candidati. Dupa care se vor exprima dorintele de vot." << endl;
		long long id = 0;
		while (true) {
			cout << "Introduceti CNP-ul votantului (enter pentru a inceta introducerea): " << endl;
			in >> id;
			if (id == 0) break;
			if (valideazaVotant(id)) {
				this->votant.insert(id);
			}
		}
		string cand = "";
		getline(in, cand); // trebuie pt ca e pretentios 
		while (true) {
			cout << "Introduceti numele candidatului (enter pentru a inceta introducerea): " << endl;
			getline(in, cand);
			transform(cand.begin(),cand.end(),cand.begin(),[](char c){return tolower(c);}); // view lambda expresii suntem smenari
			if (cand == "") break;
			if (valideazaCandidat(cand)) {
				this->candidat.push_back(cand);
			}
		}
		
		return in;
	}

};

class Prezidentiale : public Alegere{
private:
	vector <map<string,float>> rezultate;
protected:
	int numarTururi;
	vector<map<string, float>> rezultateTur;
	vector <int> turnout; // poz -> turul poz + 1
	bool cmp(pair<string, float>& a, pair<string,float>& b) { return a.second < b.second; };

public:
	Prezidentiale() {
		this->numarTururi = 1;
	};
	Prezidentiale(const Prezidentiale& obj):Alegere(obj) {this->numarTururi = obj.numarTururi, this->rezultateTur = obj.rezultateTur, this->turnout = obj.turnout;};
	Prezidentiale(set<long long> votant_, set<long long> iv_, list<string> candidat_, list<string> ic_, map<string, vector<long long>> vot_, bool electionRan_, int numarTururi_, vector<map<string, float>> rezultateTur_, vector<int> turnout_):Alegere(votant_, iv_, candidat_, ic_, vot_, electionRan_)
	{this->numarTururi = numarTururi_, this->rezultateTur = rezultateTur_, this->turnout = turnout_;};

	Prezidentiale& operator=(const Prezidentiale& obj) {
		if (this != &obj) {
			Alegere::operator=(obj);
			this->numarTururi = obj.numarTururi;
			this->turnout = obj.turnout;
		}
		return *this;
	}

	~Prezidentiale() {}

	virtual ostream& afisare(ostream& out) const {
		
		if (!electionRan) {
			out << "Aceasta alegere inca nu s-a desfasurat!\n";
		}
		else {
			out << "Aceasta alegere a fost una prezidentiala." << endl;
			out << "Aceasta alegere s-a desfasurat in " << this->numarTururi << " tururi." << endl;
		}

		return out;
	}

	virtual istream& citire(istream& in) {

		Alegere::citire(in);
		cout << "Doriti inceperea procesului electoral (citirea voturilor pana la sfarsitul alegerilor)?(y/n)\n";

		cout << "Urmeaza a se citi voturile, urmat de validarea procesului electoral: \n";
		cout << "Pentru a inceta citirea, apasati enter de 2 ori\n";
		long long cnp = 0;
		string cand = "";
		while (true) {
			cout << "Incepe turul " << numarTururi << "!\n";
			while (true) {
				cout << "Introduceti votantul: " << endl;
				in >> cnp;
				getline(in, cand);
				cout << "Introduceti candidatul: " << endl;
				getline(in, cand);
				if (cnp == 0 && cand == "") break;
				if (valideazaVot(cnp, cand)) {
					vot[cand].push_back(cnp);
				}
				
			}
			if (derulareAlegere()) {
				electionRan = true;
				cout << "Alegerile au luat sfarsit!\n";
				break;
			}
			else{
				numarTururi++;
			}
		}

		return in;
	}

	friend ostream& operator<<(ostream& out, const Prezidentiale& prezidentiale) {return prezidentiale.afisare(out);}
	friend istream& operator>>(istream& in, Prezidentiale& prezidentiale) {return prezidentiale.citire(in);}

	bool derulareAlegere() {
		
		map <string, float> tur;
		multimap<float, string, greater<float>> aux;

		int voturiTotale = 0;

		for (auto& x : vot) {
			tur[x.first] += x.second.size();
			voturiTotale += x.second.size();
		}
		cout << voturiTotale << ' ';
		for (auto& x : tur) {
			x.second /= voturiTotale;
		}
		
		for (auto& x : tur) {
			aux.insert({x.second, x.first});
		}

		cout << "Rezultatele turului " << numarTururi << " sunt urmatoarele:\n";
		for (auto& x : aux) {
			cout << x.second << ": " << x.first << "%\n";
		}

		if ((aux.begin()->first + eps) <= 0.5f) {
			// ne ducem in turul +1
			rezultate.push_back(tur);
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
};

//class Parlamentare: public Alegere {
//public:
//	Parlamentare() {
//		this->numarTururi = 1;
//	};
//	Parlamentare(const Parlamentare& obj) :Alegere(obj) { this->numarTururi = obj.numarTururi; };
//	Parlamentare(int numarTururi_, set<long long> votant_, list<string> candidat_, map<string, long long> vot_) :Alegere(votant_, candidat_, vot_) { this->numarTururi = numarTururi_; };
//
//	Parlamentare& operator=(const Parlamentare& obj) {
//		if (this != &obj) {
//			Alegere::operator=(obj);
//			this->numarTururi = obj.numarTururi;
//		}
//		return *this;
//	}
//
//	~Parlamentare() {}
//
//	virtual ostream& afisare(ostream& out) const {
//		out << "Aceasta alegere a fost una prezidentiala." << endl;
//		out << "Aceasta alegere s-a desfasurat in " << this->numarTururi << " tururi." << endl;
//		out << "In cadrul celor " << this->numarTururi << " tururi au fost rezenti urmatorul numar de oameni: " << endl;
//		for (auto& x : turnout) {
//
//		}
//		out << "In cadrul alegerilor au existat un numar de " << this->votant.size() << " votanti ale caror voturi au fost validate." << endl;
//		out << "Candidatii care au participat in alegeri si numarul lor de voturi este urmatorul: " << endl;
//		for (auto& x : this->vot) {
//			out << x.first << ": " << x.first.size() << endl;
//		}
//
//		return out;
//	}
//
//	virtual istream& citire(istream& in) {
//		cout << "Introduceti CNP - ul votantului si optiunea aleasa : " << endl;
//		long long voter; cin >> voter;
//		string opt; getline(cin, opt);
//		while (this->valideazaVot(voter, opt) != true) {
//			cout << "Introduceti CNP-ul votantului si optiunea aleasa: " << endl;
//			long long voter; cin >> voter;
//			string opt; getline(cin, opt);
//		}
//	}
//
//	friend ostream& operator<<(ostream& out, const Parlamentare& Parlamentare) { return Parlamentare.afisare(out); }
//	friend istream& operator>>(istream& in, Parlamentare& Parlamentare) { return Parlamentare.citire(in); }
//
//	void derulareAlegere() {
//		map<string, float> rezultateTur;
//
//		while ((*(rezultateTur.begin())).second <= 50) {
//
//		}
//	}
//};

//class EuroParlamentare : public Parlamentare {
//	map<string, string> AfiliereBloc; // key = bloc, value = partid ex(PPE, PNL)/
//	int numarTururi;
//public:
//	EuroParlamentare() {
//		this->numarTururi = 1;
//	};
//	EuroParlamentare(const EuroParlamentare& obj) :Alegere(obj) { this->numarTururi = obj.numarTururi; };
//	EuroParlamentare(int numarTururi_, set<long long> votant_, list<string> candidat_, map<string, long long> vot_) :Alegere(votant_, candidat_, vot_) { this->numarTururi = numarTururi_; };
//
//	EuroParlamentare& operator=(const EuroParlamentare& obj) {
//		if (this != &obj) {
//			Alegere::operator=(obj);
//			this->numarTururi = obj.numarTururi;
//		}
//		return *this;
//	}
//
//	~EuroParlamentare() {}
//
//	virtual ostream& afisare(ostream& out) const {
//		out << "Aceasta alegere a fost una prezidentiala." << endl;
//		out << "Aceasta alegere s-a desfasurat in " << this->numarTururi << " tururi." << endl;
//		out << "In cadrul celor " << this->numarTururi << " tururi au fost rezenti urmatorul numar de oameni: " << endl;
//		for (auto& x : turnout) {
//
//		}
//		out << "In cadrul alegerilor au existat un numar de " << this->votant.size() << " votanti ale caror voturi au fost validate." << endl;
//		out << "Candidatii care au participat in alegeri si numarul lor de voturi este urmatorul: " << endl;
//		for (auto& x : this->vot) {
//			out << x.first << ": " << x.first.size() << endl;
//		}
//
//		return out;
//	}
//
//	virtual istream& citire(istream& in) {
//		cout << "Introduceti CNP - ul votantului si optiunea aleasa : " << endl;
//		long long voter; cin >> voter;
//		string opt; getline(cin, opt);
//		while (this->valideazaVot(voter, opt) != true) {
//			cout << "Introduceti CNP-ul votantului si optiunea aleasa: " << endl;
//			long long voter; cin >> voter;
//			string opt; getline(cin, opt);
//		}
//	}
//
//	friend ostream& operator<<(ostream& out, const EuroParlamentare& EuroParlamentare) { return EuroParlamentare.afisare(out); }
//	friend istream& operator>>(istream& in, EuroParlamentare& EuroParlamentare) { return EuroParlamentare.citire(in); }
//
//	void derulareAlegere() {
//		map<string, float> rezultateTur;
//
//		while ((*(rezultateTur.begin())).second <= 50) {
//
//		}
//	}
//};
//
//
//class Locale : public Alegere {
//
//public:
//	Locale() {
//		this->numarTururi = 1;
//	};
//	Locale(const Locale& obj) :Alegere(obj) { this->numarTururi = obj.numarTururi; };
//	Locale(int numarTururi_, set<long long> votant_, list<string> candidat_, map<string, long long> vot_) :Alegere(votant_, candidat_, vot_) { this->numarTururi = numarTururi_; };
//
//	Locale& operator=(const Locale& obj) {
//		if (this != &obj) {
//			Alegere::operator=(obj);
//			this->numarTururi = obj.numarTururi;
//		}
//		return *this;
//	}
//
//	~Locale() {}
//
//	virtual ostream& afisare(ostream& out) const {
//		out << "Aceasta alegere a fost una prezidentiala." << endl;
//		out << "Aceasta alegere s-a desfasurat in " << this->numarTururi << " tururi." << endl;
//		out << "In cadrul celor " << this->numarTururi << " tururi au fost rezenti urmatorul numar de oameni: " << endl;
//		for (auto& x : turnout) {
//
//		}
//		out << "In cadrul alegerilor au existat un numar de " << this->votant.size() << " votanti ale caror voturi au fost validate." << endl;
//		out << "Candidatii care au participat in alegeri si numarul lor de voturi este urmatorul: " << endl;
//		for (auto& x : this->vot) {
//			out << x.first << ": " << x.first.size() << endl;
//		}
//
//		return out;
//	}
//
//	virtual istream& citire(istream& in) {
//		cout << "Introduceti CNP - ul votantului si optiunea aleasa : " << endl;
//		long long voter; cin >> voter;
//		string opt; getline(cin, opt);
//		while (this->valideazaVot(voter, opt) != true) {
//			cout << "Introduceti CNP-ul votantului si optiunea aleasa: " << endl;
//			long long voter; cin >> voter;
//			string opt; getline(cin, opt);
//		}
//	}
//
//	friend ostream& operator<<(ostream& out, const Locale& Locale) { return Locale.afisare(out); }
//	friend istream& operator>>(istream& in, Locale& Locale) { return Locale.citire(in); }
//
//	void derulareAlegere() {
//		map<string, float> rezultateTur;
//
//		while ((*(rezultateTur.begin())).second <= 50) {
//
//		}
//	}
//};



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
	//meniu->printExist();

	Prezidentiale p;
	cin >> p;

	return 0;
}