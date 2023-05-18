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
	const char* what() const throw() {return "Acest votant exista deja!"; };
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

class Alegere {
	int numarTururi;
	set <long long> votant; // cnp-urile se pun individual aici
	list <string> candidat;
	map <string, long long> vot; // candidat, cnp

public:
	virtual void derulareAlegere() = 0;
	
	int getNumarTururi() {return this->numarTururi;};
	void setNumarTururi(int nr) {this->numarTururi = nr;};
	bool parseID(long long id) {
		// prima cifra 
		// prima cifra 1 sau 2 -> varsta ok
		// prima cifra 3 sau 4 -> no vote 4 u boomer
		// prima cifra 5 sau 6 -> vedem daca ai 18 ani la data rularii
		// 7 si 8 pentru rezidente, au drept de vot macar?
		// 9 nu figureaza, paaaaaaa

		// todo implement https://ro.wikipedia.org/wiki/Cod_numeric_personal_(Rom%C3%A2nia)

		return true;
	}

	bool valideazaVot(long long cnp, string opt) {
		
		try {
			if(this->votant.find(cnp) != this->votant.end()) throw ExistingVoter();
			bool okChoice = false;
			for (auto& x : candidat) {
				if (x == opt) okChoice = true;
			}
			if(!okChoice) throw InvalidChoice();
			if(!this->parseID(cnp)) throw WrongID();
		}
		catch (ExistingVoter& e) {
			return false;
		}
		catch (InvalidChoice& i) {
			return false;
		}
		catch (WrongID& w) {
			return false;
		}
		return true;
	}

	Alegere() {
		this->numarTururi = 0;
	}
	Alegere(const Alegere& obj) {
		this->numarTururi = obj.numarTururi;
		this->votant = obj.votant;
		this->candidat = obj.candidat;
		this->vot = obj.vot;
	}
	Alegere(int numarTururi_, set<long long> votant_, list<string> candidat_, map<string, long long> vot_) {
		this->numarTururi = numarTururi_;
		this->votant = votant_;
		this->candidat = candidat_;
		this->vot = vot_;
	}

	Alegere& operator=(const Alegere& obj) {
		if (this != &obj) {
			this->numarTururi = obj.numarTururi;
			this->votant = obj.votant;
			this->candidat = obj.candidat;
			this->vot = obj.vot;
		}
	}

	virtual ~Alegere() {}

	virtual ostream& afisare(ostream& out) const {
		out << "Aceasta alegere s-a desfasurat in " << this->numarTururi << " tururi." << endl;
		out << "In cadrul alegerilor au existat un numar de " << this->votant.size() << " votanti ale caror voturi au fost validate." << endl;
		out << "Candidatii care au participat in alegeri si numarul lor de voturi este urmatorul: " << endl;
		for (auto& x : this->vot) {
			out << x.first << ": " << x.first.size() << endl;
		}

		return out;
	}

	virtual istream& citire(istream& in) {
		cout << "Introduceti CNP - ul votantului si optiunea aleasa : " << endl;
		long long voter; cin >> voter;
		string opt; getline(cin, opt);
		while (this->valideazaVot(voter, opt) != true) {
			cout << "Introduceti CNP-ul votantului si optiunea aleasa: " << endl;
			long long voter; cin >> voter;
			string opt; getline(cin, opt);
		}
	}

	friend ostream& operator<<(ostream& out, const Alegere& alegere) {return alegere.afisare(out); };
	friend istream& operator>>(istream& in, Alegere& alegere) {return alegere.citire(in);};
};

// todo implement election in one or 3+ run-off votes
class Prezidentiale : public Alegere{
public:
	Prezidentiale() {this->setNumarTururi(2);};
	Prezidentiale(const Prezidentiale& obj):Alegere(obj) {
		this->setNumarTururi(2);
	}
	Prezidentiale(int numarTururi_, set<long long> votant_, map<string, long long> vot_, list<string> candidat_):Alegere(numarTururi_, votant_, vot_, candidat_) {
		this->setNumarTururi(2);
	}

	Prezidentiale& operator=(const Prezidentiale& obj) {
		if (this != &obj) {
			Alegere::operator=(obj);
			this->setNumarTururi(2);
		}
	}

	~Prezidentiale() {}

	friend ostream& operator<<(ostream& out, const Prezidentiale& prezidentiale) {return prezidentiale.afisare(out); };

	friend istream& operator>>(istream& in, Prezidentiale& prezidentiale) {
		cout << "introduceti CNP-ul votantului si optiunea aleasa: " << endl;
		long long voter; cin >> voter;
		string opt; getline(cin, opt);
		try {
			valideazaVot(voter, opt);
		}
		catch (ExistingVoter& e) {

		}
		catch (InvalidChoice& i) {

		}
	}

	void derulareAlegere() {

	}
};

class Parlamentare: public Alegere {
	list <string> partid;
};

class EuroParlamentare : public Parlamentare {
	list <string> partid;
	map<string, string> AfiliereBloc; // key = bloc, value = partid ex(PPE, PNL)/
};

class Nationale :public Parlamentare {
	list <string> partid;

};

class Locale : public Alegere {

};

template <typename alegere>
class Desfasurare {
	alegere 
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
	void printExist() {cout << "Hello!";}
};
Menu* Menu::instance = nullptr;

int main() {
	Menu* meniu = Menu::getInstance();
	meniu->printExist();

	return 0;
}