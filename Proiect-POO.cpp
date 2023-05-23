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
#include <typeinfo>
#include <Windows.h>
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
					Beep(440, 1500);
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
					Beep(440, 1500);
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
				Beep(440, 1500);
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

// todo work on this shit
template <class Intrebari, class Raspunsuri>
class Referendum : public Alegere {
protected:
	int numarIntrebari;
	Intrebari intrebari;
	Raspunsuri raspunsuri;
	vector<multimap <float, string, greater<float>>> rezultateMulti;

	istream& citireDate(istream& in) {
		cout << "Pentru o buna desfasurare a referendumului, se vor citi CNP-urile votantilor, " << endl;
		cout << "urmat de lista de intrebari si raspunsuri. Dupa care se vor exprima dorintele de vot." << endl;
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

		if (this->numarIntrebari == 1) {
			while (true) {
				getline(in, intrebari); // trebuie pt ca e pretentios
				cout << "Introduceti intrebarea: " << endl;
				getline(in, intrebari);
				transform(intrebari.begin(), intrebari.end(), intrebari.begin(), [](char c) {return tolower(c); }); // view lambda expresii suntem smenari
				if (intrebari == "") continue;
				break;
			}
			while (true) {
				string raspuns = "";
				getline(in, raspuns);
				cout << "Introduceti raspuns (enter pt skip):\n";
				getline(in, raspuns);
				transform(raspuns.begin(), raspuns.end(), raspuns.begin(), [](char c) {return tolower(c); }); // view lambda expresii suntem smenari
				if(raspuns == "") break;
				this->raspunsuri.push_back(raspuns);
			}
		}
		else {
			for (int i = 1; i <= this->numarIntrebari; i++) {
				string intrebare = "";
				while (true) {
					getline(in, intrebare);
					cout << "Introduceti intrebarea: " << endl;
					getline(in, intrebare);
					transform(intrebare.begin(), intrebare.end(), intrebare.begin(), [](char c) {return tolower(c); }); // view lambda expresii suntem smenari
					if (intrebare == "") break;
				}
				vector <string> r_aux;
				while (true) {
					string raspuns = "";
					getline(in, raspuns);
					cout << "Introduceti raspuns (enter pt skip):\n";
					getline(in, raspuns);
					transform(raspuns.begin(), raspuns.end(), raspuns.begin(), [](char c) {return tolower(c); }); // view lambda expresii suntem smenari
					if (raspuns == "") break;
					this->r_aux.push_back(raspuns);
				}
				this->intrebari.push_back(intrebare);
				this->raspunsuri.push_back(r_aux);
			}
		}
		this->procAlegere<intrebari, raspunsuri>(in);
		return in;
	}
	
	istream& procAlegere(istream& in) {
		if (this->numarIntrebari == 1) {
			cout << "Urmeaza a se citi voturile, urmat de validarea procesului electoral: \n";
			cout << "Pentru a inceta citirea, apasati 0, apoi enter x2\n";
			cout << "Intrebarea referendumului este: \n";
			//cout << this->intrebari;
			long long cnp = 0;
			string rasp = "";
			while (true) {
				cout << "Introduceti votantul: " << endl;
				in >> cnp;
				getline(in, rasp);
				cout << "Introduceti raspunsul: " << endl;
				getline(in, rasp);
				transform(rasp.begin(), rasp.end(), rasp.begin(), [](char c) {return tolower(c); });
				if (cnp == 0 && rasp == "") break;
				if (valideazaVot(cnp, rasp)) {
					vot[rasp].push_back(cnp);
				}
			}
			derulareAlegere();
			cout << "Alegerile au luat sfarsit!\n";
		}
		else {
			cout << "Urmeaza a se citi voturile, urmat de validarea procesului electoral: \n";
			cout << "Pentru a inceta citirea, apasati 0, apoi enter x2\n";
			for (int i = 0; i < this->numarIntrebari; i++) {
				cout << "Intrebarea numarul " << i + 1 << " a referendumului este : \n";
				cout << this->intrebari[i];
				long long cnp = 0;
				string rasp = "";
				while (true) {
					cout << "Introduceti votantul: " << endl;
					in >> cnp;
					getline(in, rasp);
					cout << "Introduceti raspunsul: " << endl;
					getline(in, rasp);
					transform(rasp.begin(), rasp.end(), rasp.begin(), [](char c) {return tolower(c); });
					if (cnp == 0 && rasp == "") break;
					if (valideazaVot(cnp, rasp)) {
						vot[rasp].push_back(cnp);
					}
				}
				derulareAlegere();
				cout << "Alegerile au luat sfarsit!\n";
			}
		}

		return in;
	}

	bool derulareAlegere() {

		map <string, float> intre;
		multimap<float, string, greater<float>> aux;

		int voturiTotale = 0;

		if (this->numarIntrebari == 1) {
			for (auto& x : vot) {
				intre[x.first] += x.second.size();
				voturiTotale += x.second.size();
			}
			for (auto& x : intre) {
				x.second /= voturiTotale;
			}

			for (auto& x : intre) {
				aux.insert({ x.second, x.first });
			}
			cout << "Rezultatele referendumului sunt urmatoarele:\n";
			for (auto& x : aux) {
				cout << x.second << ": " << x.first * 100 << "%\n";
			}

			rezultateMulti.push_back(aux);
		}

		return true;
	}


public:

	Referendum():Alegere(){this->numarIntrebari = 0;}
	Referendum(int numarIntrebari_):Alegere(){this->numarIntrebari = numarIntrebari_;};
	Referendum(const Referendum& obj) :Alegere(obj) {
		this->numarIntrebari = obj.numarIntrebari;
		this->intrebari = obj.intrebari;
		this->raspunsuri = obj.raspunsuri;
		this->rezultateMulti = obj.rezultateMulti;
	}
	Referendum(set<long long> votant_, set<long long> iv_, list<string> candidat_, list<string> ic_, map<string, vector<long long>> vot_, map <string, float> rezultate_, bool electionRan_, int numarIntrebari_, Intrebari intrebari_, Raspunsuri raspunsuri_, vector<map <string, float>> rezultateMulti_) {
		this->numarIntrebari = numarIntrebari_;
		this->intrebari = intrebari_;
		this->raspunsuri = raspunsuri_;
		this->rezultateMulti = rezultateMulti_;
	}

	Referendum& operator=(const Referendum& obj) {
		if (this != &obj) {
			Alegere::operator=(obj);
			this->numarIntrebari = obj.numarIntrebari;
			this->intrebari = obj.intrebari;
			this->raspunsuri = obj.raspunsuri;
			this->rezultateMulti = obj.rezultateMulti;
		}
		return *this;
	}

	~Referendum(){}

	/*friend ostream& operator<<(ostream& out, const Referendum<intrebari, raspunsuri>& obj) {
		afisare(out, obj);
		return out;
	}*/

	friend ostream& operator<<(ostream& out, const Referendum& obj) {
		if (!obj.electionRan) {
			out << "Acest referendum inca nu s-a desfasurat!\n";
		}
		else{
			for (int i = 0; i < obj.numarIntrebari; i++) {
				out << "Intrebarea cu numarul " << i + 1 << " pusa in acestui referendum este : \n";
				out << obj.intrebari[i] << endl;
				out << "Rezultatele sunt urmatoarele: \n\n";
				for (auto& y : obj.rezultateMulti[i]) {
					out << y.second << ": " << y.first * 100 << "%\n";
				}
				out << '\n';
				out << "Raspunsul castigator este " << (obj.rezultateMulti.end() - 1)->begin()->first << ".\n";
			}
		}

		return out;
	}

	friend istream& operator>>(istream& in, Referendum& obj) {
		obj.incCitire(in);
		return in;
	}
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
		cout << "Pentru a inceta citirea, apasati 0, apoi enter x2\n"; 
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
		cout << "Pentru a inceta citirea, apasati 0 apoi enter de 2 ori\n"; 
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
	vector <Alegere*> alegeri;

public:
	static Menu* getInstance() {
		if (instance == nullptr) {
			instance = new Menu();
		}
		return instance;
	}

	void run() {
		std::cout << "Bine ati venit la alegeri!" << endl;
		std::cout << "Selectati una din urmatoarele: " << endl;
		std::cout << "1. Create (create)" << endl;
		std::cout << "2. Read (read)" << endl;
		std::cout << "3. Print (print)" << endl;
		std::cout << "4. Quit (quit)" << endl;
		string input = "";
		std::cin >> input;
		std::transform(input.begin(), input.end(), input.begin(), ::tolower);
		
		    
		while (input != "quit") {
		        
		    if (input == "create" || input == "c") {
		
		        while (input != "continue") {
		
		            std::cout << "1. Alegere prezidentiala (create_prezidentiala)" << endl;
		            std::cout << "2. Alegere parlamentara (create_parlamentara)" << endl;
					std::cout << "3. Alegere locala (create_locala)" << endl;
					std::cout << "4. Alegere europarlamentara (create_europarlamentara)" << endl;
		            std::cout << "5. Referendum (create_referendum)" << endl;
		            std::cout << "6. Continua catre alte instructiuni (continue)" << endl;
		            std::cin >> input;
		            std::transform(input.begin(), input.end(), input.begin(), ::tolower);
		                
		
		            if (input == "create_prezidentiala" || input == "cpr") {
						alegeri.push_back(new Prezidentiale());
						std::cout << "Alegere prezidentiala creata!" << endl;
					}
					else if (input == "create_parlamentara" || input == "cpa") {
						alegeri.push_back(new Parlamentare());
						std::cout << "Alegere parlamentara creata!" << endl;
					}
					else if (input == "create_locala" || input == "clo") {
						alegeri.push_back(new Locale());
						std::cout << "Alegere locala creata!" << endl;
					}
					else if (input == "create_europarlamentara" || input == "cep") {
						alegeri.push_back(new EuroParlamentare());
						std::cout << "Alegere europarlamentara creata!" << endl;
					}
					else if (input == "create_referendum" || input == "cre") {
						int aux = 0;
						while (true) {
							cout << "Cate intrebari va avea referendumul? (>= 1) (0 pt a iesi)\n";
							cin >> aux;
							if (aux <= 0) {
								break;
							}
							else if (aux == 1) {
								alegeri.push_back(new Referendum<string, vector<string>>(1));
								cout << "Referendum cu intrebare unica creat!\n";
							}
							else if (aux <= 3) {
								alegeri.push_back(new Referendum<vector<string>,vector<vector<string>>>(aux));
								cout << "Referendum cu mai multe intrebari (" << aux << ") creat!\n";
							}
							else {
								cout << "Are you sure about this? Think you should reconsider.\n";
							}
						}
					}
		            else if (input != "continue") {
		                std::cout << "Comanda necunoscuta! Incercati din nou." << endl;
		            }
		        }
		    }
		    else if (input == "read" || input == "r") {
		        while (input != "continue") {
		            int pos = 0;
		
					std::cout << "1. Citeste alegere (read_alegere)" << endl;
					std::cout << "2. Continua catre alte instructiuni (continue)" << endl;
		            std::cin >> input;
		            std::transform(input.begin(), input.end(), input.begin(), ::tolower);
		
		            if (input == "read_alegere" || input == "ra") {
		                if (!alegeri.empty()) {
		                    std::cout << "Alege indexul: 1 -> " << alegeri.size() << ": ";
		                    std::cin >> pos;
		                    if (0 < pos && pos <= alegeri.size()) {
								if (typeid(*alegeri[pos - 1]) == typeid(Prezidentiale)){
									cout << "Se vor citi datele despre alegerea prezidentiala!\n";
									cin >> dynamic_cast<Prezidentiale&>(*alegeri[pos - 1]);
								}
								if (typeid(*alegeri[pos - 1]) == typeid(Parlamentare)){
									cout << "Se vor citi datele despre alegerea parlamentara!\n";
									cin >> dynamic_cast<Parlamentare&>(*alegeri[pos - 1]);
								}
								if (typeid(*alegeri[pos - 1]) == typeid(Locale)){
									cout << "Se vor citi datele despre alegerea locala!\n";
									cin >> dynamic_cast<Locale&>(*alegeri[pos - 1]);
								}
								if (typeid(*alegeri[pos - 1]) == typeid(EuroParlamentare)){
									cout << "Se vor citi datele despre alegerea europarlamentara!\n";
									cin >> dynamic_cast<EuroParlamentare&>(*alegeri[pos - 1]);
								}
								if (typeid(*alegeri[pos - 1]) == typeid(Referendum<string, vector<string>>)) {
									cout << "Se vor citi datele despre referendumul cu o intrebare!\n";
									cin >> dynamic_cast<Referendum<string, vector<string>>&>(*alegeri[pos - 1]);
								}
								if (typeid(*alegeri[pos - 1]) == typeid(Referendum<vector<string>, vector<vector<string>>>)) {
									cout << "Se vor citi datele despre referendumul cu mai multe intrebari!\n";
									cin >> dynamic_cast<Referendum<vector<string>, vector<vector<string>>>&>(*alegeri[pos - 1]);
								}
		                    }
		                    else {
		                        std::cout << "Index invalid! Incercati din nou!" << endl;
		                    }
		                }
		                else {
		                    std::cout << "Organizati o alegere in primul rand!" << endl;
		                }
		            }
		            else if (input != "continue") {
		                std::cout << "Comanda necunoscuta! Incercati din nou." << endl;
		            }
		        }
		    }
		    else if (input == "print" || input == "p") {
		        while (input != "continue") {
		        int pos = 0;
		
		            std::cout << "1. Print event (print_event)" << endl;
		            std::cout << "2. Continua catre alte instructiuni (continue)" << endl;
		            std::cin >> input;
		            std::transform(input.begin(), input.end(), input.begin(), ::tolower);
		
		            if (input == "print_event" || input == "pe") {
		                if (0 < alegeri.size()) {
		                    std::cout << "Alegeti indexul: 1 -> " << alegeri.size() << ": ";
		                    std::cin >> pos;
		                    if (0 < pos && pos <= alegeri.size()) {
								if (typeid(*alegeri[pos - 1]) == typeid(Prezidentiale))
									cout << dynamic_cast<Prezidentiale&>(*alegeri[pos - 1]);
								if (typeid(*alegeri[pos - 1]) == typeid(Parlamentare))
									cout << dynamic_cast<Parlamentare&>(*alegeri[pos - 1]);
								if (typeid(*alegeri[pos - 1]) == typeid(Locale))
									cout << dynamic_cast<Locale&>(*alegeri[pos - 1]);
								if (typeid(*alegeri[pos - 1]) == typeid(EuroParlamentare))
									cout << dynamic_cast<EuroParlamentare&>(*alegeri[pos - 1]);
								if (typeid(*alegeri[pos - 1]) == typeid(Referendum<string, vector<string>>))
									cout << dynamic_cast<Referendum<string, vector<string>>&>(*alegeri[pos - 1]);
								if (typeid(*alegeri[pos - 1]) == typeid(Referendum<vector<string>, vector<vector<string>>>))
									cout << dynamic_cast<Referendum<vector<string>, vector<vector<string>>>&>(*alegeri[pos - 1]);

		                    }
		                    else {
		                        std::cout << "Index invalid! Incercati din nou!" << endl;
		                    }
		                }
		                else {
		                    std::cout << "Organizati o alegere in primul rand!" << endl;
		                }
		
		            }
		            else if (input != "continue") {
		                std::cout << "Comanda necunoscuta! Incercati din nou." << endl;
		            }
		        }
		    }
		    else if (input != "quit") {
		        std::cout << "Comanda necunoscuta! Incercati din nou." << endl;
		    }
		
		    cout << "Selectati una din urmatoarele: " << endl;
		    cout << "1. Create (create)" << endl;
		    cout << "2. Read (read)" << endl;
		    cout << "3. Print (print)" << endl;
		    cout << "4. Quit (quit)" << endl;
		
		    cin >> input;
		    transform(input.begin(), input.end(), input.begin(), ::tolower);
		}
	}

	//void printExist() {cout << "Hello!";}
};
Menu* Menu::instance = nullptr;

int main() {
	Menu* meniu = Menu::getInstance();
	meniu->run();
	

	return 0;
}