#include <iostream>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <string>
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
	const char* what() const throw() {return "Acest votant exista deja!\nMasuri antifrauda au fost luate."; };
};
class ExistingCandidate : public exception {
public:
	const char* what() const throw() { return "Acest candidat exista deja!\nMasuri antifrauda au fost luate."; };
};
class InvalidVoter : public exception {
public:
	const char* what() const throw() { return "CNP-ul folosit nu figureaza pe lista de votanti inregistrati!"; };
};
class InvalidChoice : public exception {
public:
	const char* what() const throw() { return "Optiunea aleasa nu figureaza pe lista de candidati!"; };
};
class WrongID : public exception {
public:
	const char* what() const throw() { return "CNP-ul introdus nu este valid (varsta prea mica)/numar invalid!"; };
};

// todo template class

//template <typename alegere>
//class Desfasurare {
//	alegere
//};

class Alegere {
protected:
	set <long long> votant; // cnp-urile se pun individual aici
	set<long long> invalidV; // cine e invalidat va fi trimis aici
	list <string> candidat;
	list <string> invalidC;
	map <string, vector<long long>> vot; // candidat, cnp
	bool electionRan;

public:
	virtual void derulareAlegere() = 0;
	bool parseID(long long id) {
		long long mask = 1;
		for (int i = 1; i <= 13; i++) mask *= 10;

		int firstDig = (id % mask) / (mask / 10);
		mask /= 10;
		if (firstDig == 5 || firstDig == 6) {
			int year = 10 * ((id % mask) / (mask / 10)) + (id % (mask/10)) / (mask / 100);
			mask /= 100;
			if (year > 5) return 0; // view cam brut, vom reveni
		}
		else if (firstDig == 3 || firstDig == 4 || firstDig == 7 || firstDig == 8 || firstDig == 9 || firstDig == 0) return false;


		return true;
	}

	bool valideazaCandidat(string opt) {
		try {
			for (auto& )
			for (auto& x : candidat) {
				if (x == opt) {
					throw ExistingCandidate();
				}
			}
		}
		catch (ExistingCandidate& e) {
			cout << e.what();
			this->candidat.erase(opt);
			this->invalidC.insert(opt);
			return false;
		}

		return true;
	}

	bool valideazaVotant(long long cnp) {
		try {
			if (this->votant.find(cnp) != this->votant.end()) throw ExistingVoter();
			if (!this->parseID(cnp)) throw WrongID();
		}
		catch (ExistingVoter& e){ return false;}
		catch (WrongID& w){ return false;}

		return true;
	}

	bool valideazaVot() {


	}

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
			cout << "Introduceti CNP-ul votantului (0 pentru a inceta introducerea): " << endl;
			in >> id;
			if (id == 0) break;
			if (valideazaVotant(id)) {
				votant.insert(id);
				cout << "Votantul a fost introdus in baza de date cu succes!" << endl;
			}
			else {
				cout << "Eroare la introducerea ID-ului!" << endl;
			}
		}
		string cand = "";
		while (true) {
			cout << "Introduceti numele candidatului (enter pentru a trece peste): " << endl;
			getline(in, cand);
			cout << 'a';
			if (cand == "") break;
			cout << 'b';
			if (valideazaCandidat(cand)) {
				candidat.push_back(cand);
				cout << "Candidatul a fost introdus in baza de date cu succes!" << endl;
			}
			else {
				cout << "Eroare la introducerea candidatului!" << endl;
			}
		}
		
		return in;
	}

};

// todo implement election in one or 3+ run-off votes
class Prezidentiale : public Alegere{
protected:
	int numarTururi;
	vector <int> turnout; // poz -> turul poz + 1

public:
	Prezidentiale() {
		this->numarTururi = 1;
	};
	Prezidentiale(const Prezidentiale& obj):Alegere(obj) {this->numarTururi = obj.numarTururi, this->turnout = obj.turnout;};
	Prezidentiale(set<long long> votant_, list<string> candidat_, map<string, vector<long long>> vot_, int numarTururi_, vector<int> turnout_,bool electionRan_):Alegere(votant_, candidat_, vot_, electionRan_)
	{this->numarTururi = numarTururi_, this->turnout = turnout_;};

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
		out << "Aceasta alegere a fost una prezidentiala." << endl;
		out << "Aceasta alegere s-a desfasurat in " << this->numarTururi << " tururi." << endl;
		out << "In cadrul celor " << this->numarTururi << " tururi au fost prezenti urmatorul numar de oameni: " << endl;
		int tur = 1;
		for (auto& x : turnout) {
			out << "Turul " << tur << ": " << x << " voturi validate." << endl;
		}

		return out;
	}

	virtual istream& citire(istream& in) {

		Alegere::citire(in);

		return in;
	}

	friend ostream& operator<<(ostream& out, const Prezidentiale& prezidentiale) {return prezidentiale.afisare(out);}
	friend istream& operator>>(istream& in, Prezidentiale& prezidentiale) {return prezidentiale.citire(in);}

	void derulareAlegere() {

		

		map<string,float> rezultateTur;

		while ((*(rezultateTur.begin())).second <= 50) {
			
		}
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
//
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