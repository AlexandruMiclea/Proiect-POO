//CORPORATE EVENT MANAGER - PROJECT WRITTEN BY ALEXANDRU MICLEA
//FMI UNIBUC 2023

#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

#pragma warning (disable : 4996)

// class declarations

// part 1 classes
class Company;
class Event; 
class EventRoom;
class Calendar;
class Conference;
// Make sure you link the marketing plan here!


// part 2 classes

// functionalities related to marketing the event?
class Advertisement;
class OnlineAd;
class NewspaperAd;
class PhysicalAd;
class Marketing;


// PART 2 CLASSES

class Advertisement {
protected:
    string targetAudience;
    int budget;

public:
    // empty c
    Advertisement() {
        this->budget = 0;
        this->targetAudience = "";
    }
    // param c
    Advertisement(string targetAudience, int budget) {
        this->budget = budget;
        this->targetAudience = targetAudience;
    }
    // cc
    Advertisement(const Advertisement& obj) {
        this->budget = obj.budget;
        this->targetAudience = obj.targetAudience;
    }
    // = op
    Advertisement& operator=(const Advertisement& obj) {
        if (this != &obj) {
            this->budget = obj.budget;
            this->targetAudience = obj.targetAudience;

        }
        return *this;
    }
    // d, virtual in case I randomly delete a derived class using a pointer to base
    virtual ~Advertisement() {}
    // write
    virtual ostream& afisare(ostream& out) const{
        out << "The budget is " << this->budget << " dollars" << endl;
        out << "The target audience is " << this->targetAudience << endl;
        return out;
    }
    friend ostream& operator<<(ostream& out,const Advertisement& ad) {return ad.afisare(out); }
    // read
    virtual istream& citire(istream& in) {
        std::cout << "What is the budget?";
        in >> this->budget; 
        std::cout << "What is the target audience?";
        in >> this->targetAudience;
        return in;
    }
    friend istream& operator>>(istream& in, Advertisement& ad) { return ad.citire(in); }
    // present
    virtual void present() = 0;
};

class OnlineAd : public virtual Advertisement {
protected:
    float length;
    string platform;
public:
    // empty c
    OnlineAd() {
        this->length = 0.0f;
        this->platform = "";
    }
    // param c
    OnlineAd(string targetAudience, int budget, float length, string platform):Advertisement(targetAudience, budget) {
        this->length = length;
        this->platform = platform;
    }
    // cc
    OnlineAd(const OnlineAd& obj):Advertisement(obj) {
        this->length = obj.length;
        this->platform = obj.platform;
    }
    // = op
    OnlineAd& operator=(const OnlineAd& obj) {
        if (this != &obj) {
            Advertisement::operator=(obj);
            this->platform = obj.platform;
            this->length = obj.length;
        }
        return *this;
    }
    // d
    virtual ~OnlineAd() {}
    // read
    istream& citire(istream& in) {
        Advertisement::citire(in);
        std::cout << "What will be the length of this add?";
        in >> this->length;
        std::cout << "On what platform will you play this add?";
        in >> this->platform;

        return in;
    }
    // write
    ostream& afisare(ostream& out) const{
        Advertisement::afisare(out);
        out << "The length of the ad is " << this->length << " dollars" << endl;
        out << "The platform we will play this ad on is " << this->platform << endl;

        return out;
    }
    // present
    void present() {
        std::cout << "This event will be advertised with an online ad." << endl;
        this->afisare(std::cout); 
    }

    // rw operators
    friend ostream& operator<<(ostream& out, const OnlineAd& ad) { return ad.afisare(out); }
    friend istream& operator>>(istream& in, OnlineAd& ad) { return ad.citire(in); }
};

class NewspaperAd : public virtual Advertisement {
protected:
    int noOfColumns;
public:
    // empty c
    NewspaperAd() {
        this->noOfColumns = 0;
    }
    // param c
    NewspaperAd(string targetAudience, int budget, int noOfColumns) :Advertisement(targetAudience, budget) {
        this->noOfColumns = noOfColumns;
    }
    // cc
    NewspaperAd(const NewspaperAd& obj) :Advertisement(obj) {
        this->noOfColumns = obj.noOfColumns;
    }
    // = op
    NewspaperAd& operator=(const NewspaperAd& obj) {
        if (this != &obj) {
            Advertisement::operator=(obj);
            this->noOfColumns = obj.noOfColumns;
        }
        return *this;
    }
    // d
    virtual ~NewspaperAd() {}
    // read
    istream& citire(istream& in) {
        Advertisement::citire(in);
        std::cout << "How many columns do you want to purchase in the newspaper: ";
        in >> this->noOfColumns;

        return in;
    }
    // write
    ostream& afisare(ostream& out) const {
        Advertisement::afisare(out);
        out << "The number of columns purchased will be " << this->noOfColumns << endl;

        return out;
    }
    // present
    void present() {
        std::cout << "This event will be published in a newspaper." << endl;
        this->afisare(std::cout);
    }

    // rw operators
    friend ostream& operator<<(ostream& out, const NewspaperAd& ad) { return ad.afisare(out); }
    friend istream& operator>>(istream& in, NewspaperAd& ad) { return ad.citire(in); }
};

class PhysicalAd : public virtual Advertisement {
protected:
    float size;
    string printCompany;
public:
    // empty c
    PhysicalAd() {
        this->size = 0.0f;
        this->printCompany = "";
    }
    // param c
    PhysicalAd(string targetAudience, int budget, float size, string printCompany) :Advertisement(targetAudience, budget) {
        this->size = size;
        this->printCompany = printCompany;
    }
    // cc
    PhysicalAd(const PhysicalAd& obj) :Advertisement(obj) {
        this->size = obj.size;
        this->printCompany = obj.printCompany;
    }
    // = op
    PhysicalAd& operator=(const PhysicalAd& obj) {
        if (this != &obj) {
            Advertisement::operator=(obj);
            this->printCompany = obj.printCompany;
            this->size = obj.size;
        }
        return *this;
    }
    // d
    virtual ~PhysicalAd() {}
    // read
    istream& citire(istream& in) {
        Advertisement::citire(in);
        std::cout << "What size do you want your posters/fliers to be?";
        in >> this->size;
        std::cout << "Where do you intend to print your fliers?";
        in >> this->printCompany;

        return in;
    }
    // write
    ostream& afisare(ostream& out) const{
        Advertisement::afisare(out);
        out << "The size of your posters/flyers will be " << this->size << endl;
        out << "The printing company is " << this->printCompany << endl;

        return out;
    }
    // present
    void present() {
        std::cout << "This event will be advertised in physical format." << endl;
        this->afisare(std::cout);
    }

    // rw operators
    friend ostream& operator<<(ostream& out, const PhysicalAd& ad) { return ad.afisare(out); }
    friend istream& operator>>(istream& in, PhysicalAd& ad) { return ad.citire(in); }
};

class Marketing : public OnlineAd, public NewspaperAd, public PhysicalAd {
protected:
    float duration; // as in days
public:
    // empty c
    Marketing() {
        this->duration = 0.0f;
    }
    // param c
    Marketing(string targetAudience, int budget, float length, string platform, int noOfColumns, float size, string PrintCompany, float duration) :Advertisement(targetAudience, budget), OnlineAd(targetAudience, budget, length, platform), NewspaperAd(targetAudience, budget, noOfColumns), PhysicalAd(targetAudience, budget, size, PrintCompany) {
        this->duration = duration;
    }
    // cc
    Marketing(const Marketing& obj) :Advertisement(obj), OnlineAd(obj), NewspaperAd(obj), PhysicalAd(obj) {
        this->duration = obj.duration;
    }
    // = op
    Marketing& operator=(const Marketing& obj) {
        if (this != &obj) {
            OnlineAd::operator=(obj);
            NewspaperAd::operator=(obj);
            PhysicalAd::operator=(obj);
            this->duration = obj.duration;
        }
        return *this;
    }
    // d
    virtual ~Marketing() {}
    // read
    istream& citire(istream& in) {
        OnlineAd::citire(in);
        std::cout << "How many columns do you want to purchase in the newspaper: ";
        in >> this->noOfColumns;
        std::cout << "What size do you want your posters/fliers to be: ";
        in >> this->size;
        std::cout << "Where do you intend to print your fliers: ";
        in >> this->printCompany;
        std::cout << "How many days do you want it to span: ";
        in >> this->duration;

        return in;
    }
    // write
    ostream& afisare(ostream& out) const{
        OnlineAd::afisare(out);
        out << "The number of columns purchased will be " << this->noOfColumns << endl;
        out << "The size of your posters/flyers will be " << this->size << endl;
        out << "The printing company is " << this->printCompany << endl;
        out << "It will be played in the span of " << this->duration << " days" << endl;

        return out;
    }
    // present
    void present() {
        std::cout << "This event will have a fully fledged marketing campaign." << endl;
        this->afisare(std::cout);
    }
    // rw operators
    friend ostream& operator<<(ostream& out, const Marketing& ad) { return ad.afisare(out); }
    friend istream& operator>>(istream& in, Marketing& ad) { return ad.citire(in); }
};


// PART 1 CLASSES

class Company {
private:

    const int companyID;
    static int countID;

    bool hosting;
    string companyName;
    int representativeNo;
    vector <string> representatives;

public:


    // getters 
    const int getCompanyID() { return this->countID; };
    bool getHosting() { return this->hosting; };
    string getCompanyName() { return this->companyName; };
    int getRepresentantiveNo() { return this->representativeNo; };
    vector <string> getRepresentatives() { return this->representatives; };

    // setters 
    void setHosting(bool hosting) { this->hosting = hosting; };
    void setCompanyName(string companyName) { this->companyName = companyName; };
    void setRepresentantiveNo(int representativeNo) { this->representativeNo = representativeNo; };
    void setRepresentatives(vector <string> representatives) { this->representatives = representatives; };

    Company(); // empty constructor
    ~Company(); // destructor
    Company(bool hosting, string companyName, int representativeNo, vector <string> representatives); // full constructor
    Company(bool hosting, string companyName, int representativeNo); // partial constructor 1
    Company(string companyName, int representativeNo); // partial constructor 2
    Company(const Company& company); // copy constructor
    friend ostream& operator <<(ostream& out, const Company& Company); // output operator overload
    friend istream& operator >>(istream& in, Company& Company); // input operator overload
    Company& operator=(const Company& Company); // = overload
    string operator[](int); // index overload
    bool operator==(const Company&); // == overload
    bool operator<(const Company&); // < overload
    Company operator++(int); // postfix overload
    Company& operator++(); // prefix overload
    Company operator+(Company); // + overload  
    Company* operator*(int); // *overload
    friend Company* operator*(int, Company); // * overload
    operator string(); // string cast
    void printCompany();

};

int Company::countID = 100;

Company::Company() :companyID(countID++) {
    this->hosting = false;
    this->companyName = "New Company";
    this->representativeNo = 0;
}

// partial constructor 1
Company::Company(bool hosting, string companyName, int representativeNo) :companyID(countID++) {
    this->hosting = hosting;
    this->companyName = companyName;
    this->representativeNo = representativeNo;
}

// partial constructor 2
Company::Company(string companyName, int representativeNo) :companyID(countID++) {
    this->hosting = false;
    this->companyName = companyName;
    this->representativeNo = representativeNo;
}

Company::~Company(){}

Company::Company(bool hosting, string companyName, int representativeNo, vector <string> representatives) :companyID(countID++) {
    this->hosting = hosting;
    this->companyName = companyName;
    this->representativeNo = representativeNo;
    this->representatives = representatives;
}
Company::Company(const Company& company) :companyID(countID++) {
    this->hosting = company.hosting;
    this->companyName = company.companyName;
    this->representativeNo = company.representativeNo;
    this->representatives = company.representatives;
}

istream& operator >>(istream& in, Company& company) {
    std::cout << "What is your company's name: ";
    in >> company.companyName;

    std::cout << "Are you expected to host a conference (y/n): ";
    char aux;
    in >> aux;
    if (aux == 'y' || aux == 'Y') company.hosting = true;
    else company.hosting = false;

    std::cout << "How many representatives will be present from your company: ";
    in >> company.representativeNo;

    for (int i = 1; i <= company.representativeNo; i++) {
        std::cout << "Enter the name of representative " << i << ": ";
        string aux;
        in >> aux;
        company.representatives.push_back(aux);
    }

    std::cout << endl;
    return in;
}

ostream& operator <<(ostream& out, const Company& company) {

    out << "This company's name is " << company.companyName << endl;

    out << "This company is ";
    if (company.hosting == false) out << "NOT ";
    out << "expected to host a conference at this event." << endl;

    out << "This company will be represented by " << company.representativeNo << " individuals." << endl;
    out << "Their names are as follows: " << endl;
    for (int i = 1; i <= company.representativeNo; i++) {
        out << i << ". " << company.representatives[i - 1] << endl;
    }

    return out;
}


Company& Company::operator=(const Company& company) {

    if (this != &company) {
        this->hosting = company.hosting;
        this->companyName = company.companyName;
        this->representativeNo = company.representativeNo;
        this->representatives = company.representatives;
    }
    return *this;
}


// string cast
Company::operator string() {

    if (this->companyName == "New Company") {
        return "There is no company name assigned yet!";
    }
    else {
        string aux = "The company is called ";
        aux += this->companyName + " ";
        aux += "and it is ";
        aux += (hosting ? "" : "NOT ");
        aux += "expected to host a conference.";
        return aux;
    }
}


string Company::operator[](int x) {
    if (this->representatives.empty()) {
        throw runtime_error("No hosts have been named yet!");
    }
    if (x < 0 || x >= this->representativeNo) {
        throw runtime_error("Invalid index!");
    }

    return this->representatives[x];
}

bool Company::operator==(const Company& company) {
    return this->companyName == company.companyName;
}

Company Company::operator++(int) {
    Company aux(*this);
    this->representativeNo++;
    return aux;
}


Company& Company::operator++() {
    this->representativeNo++;
    return *this;
}

bool Company::operator<(const Company& company) {
    return this->representativeNo < company.representativeNo;
}

// + overload 
Company Company::operator+(Company company) {
    Company ans(*this);
    ans.representativeNo += company.representativeNo;
    for (auto& str : company.representatives) {
        ans.representatives.push_back(str);
    }
    return ans;
}

Company* Company::operator*(int x) {
    Company* ans = new Company[x];
    for (int i = 0; i < x; i++) {
        ans[i] = *this;
    }
    return ans;
}

Company* operator*(int x, Company company) {
    Company* ans = new Company[x];
    for (int i = 0; i < x; i++) {
        ans[i] = company;
    }
    return ans;
}

void Company::printCompany() {
    std::cout << *this;
}


class EventRoom {
private:

    const int roomNo;
    static int roomCnt;

    string roomName;
    int seatNo;
    char pavilion;
    int noOfFacilities;
    vector <string> facilities;


public:


    // getters 
    const int getRoomNo() { return this->roomNo; };
    string getRoomName() { return this->roomName; };
    int getSeatNo() { return this->seatNo; };
    char getPavilion() { return this->pavilion; };
    int getNoOfFacilities() { return this->noOfFacilities; };
    vector <string> getFacilities() { return this->facilities;};

    // setters 
    void setRoomName(string roomName) { this->roomName = roomName; };
    void setSeatNo(int seatNo) { this->seatNo = seatNo; };
    void setPavilion(char pavilion) { this->pavilion = pavilion; };
    void setNoOfFacilities(int noOfFacilities) { this->noOfFacilities = noOfFacilities; };
    void setFacilities(vector <string> facilities) { this->facilities = facilities;};

    EventRoom(); // empty constructor
    ~EventRoom(); // destructor
    EventRoom(string roomName, int seatNo, char pavilion, int noOfFacilities, vector <string> facilities); // full constructor
    EventRoom(string roomName, int seatNo, char pavilion); // partial constructor 1
    EventRoom(string roomName); // partial constructor 2
    EventRoom(const EventRoom& event); // copy constructor
    friend ostream& operator <<(ostream& out, const EventRoom& eventRoom); // output operator overload
    friend istream& operator >>(istream& in, EventRoom& eventRoom); // input operator overload
    EventRoom& operator=(const EventRoom& eventRoom); // = overload
    string operator[](int); // index overload 
    bool operator==(const EventRoom&); // == overload
    bool operator<(const EventRoom&); // < overload
    EventRoom operator++(int); // postfix operator
    EventRoom& operator++(); // prefix operator
    operator string(); // string cast
    EventRoom operator+(int); // + overload  
    EventRoom operator-(int); // - overload 
    friend EventRoom operator-(int, EventRoom); // comutative -
    friend EventRoom operator+(int, EventRoom); // comutative +
    void printEventRoom();

};

int EventRoom::roomCnt = 200;

EventRoom::EventRoom():roomNo(roomCnt++){
    this->roomName = "New Room";
    this->seatNo = 0;
    this->pavilion = 'X';
    this->noOfFacilities = 0;
}

// partial constructor 1
EventRoom::EventRoom(string roomName, int seatNo, char pavilion) :roomNo(roomCnt++) {
    this->roomName = roomName;
    this->seatNo = seatNo;
    this->pavilion = pavilion;
    this->noOfFacilities = 0;
}

// partial constructor 2
EventRoom::EventRoom(string roomName) :roomNo(roomCnt++) {
    this->roomName = roomName;
    this->seatNo = 0;
    this->pavilion = 'X';
    this->noOfFacilities = 0;
}

// destructor
EventRoom::~EventRoom(){
    //facilities.clear();
}

// full constructor
EventRoom::EventRoom(string roomName, int seatNo, char pavilion, int noOfFacilities, vector <string> facilities) :roomNo(roomCnt++) {
    this->roomName = roomName;
    this->seatNo = seatNo;
    this->pavilion = pavilion;
    this->noOfFacilities = noOfFacilities;
    this->facilities = facilities;
}

// copy constructor
EventRoom::EventRoom(const EventRoom& eventRoom) :roomNo(roomCnt++) {
    this->roomName = eventRoom.roomName;
    this->seatNo = eventRoom.seatNo;
    this->pavilion = eventRoom.pavilion;
    this->noOfFacilities = eventRoom.noOfFacilities;
    this->facilities = eventRoom.facilities;
}

// output overload
ostream& operator <<(ostream& out, const EventRoom& eventRoom) {

    out << "This room's name is " << eventRoom.roomName << "." << endl;
    out << "It has a number of " << eventRoom.seatNo << " seats." << endl;
    out << "It belongs to pavilion " << eventRoom.pavilion << "." << endl;
    out << "It has " << eventRoom.noOfFacilities << " facilities, which are the following: " << endl;
    for (int i = 1; i <= eventRoom.noOfFacilities; i++) {
        out << i << ". " << eventRoom.facilities[i-1] << endl;
    }
    
    return out;
}

// input overload
istream& operator >>(istream& in, EventRoom& eventRoom) {

    std::cout << "What is this room's name: ";
    in >> eventRoom.roomName;

    std::cout << "How many seats does it have: ";
    in >> eventRoom.seatNo;

    std::cout << "In what pavilion does it exist: ";
    in >> eventRoom.pavilion;

    std::cout << "How many facilities does this room have: ";
    in >> eventRoom.noOfFacilities;

    for (int i = 1; i <= eventRoom.noOfFacilities; i++) {
        std::cout << "Enter facility number " << i << ": ";
        string aux;
        in >> aux;
        eventRoom.facilities.push_back(aux);
    }

    return in;
}

EventRoom& EventRoom::operator=(const EventRoom& eventRoom){

    if (this != &eventRoom) {
        this->noOfFacilities = eventRoom.noOfFacilities;
        this->roomName = eventRoom.roomName;
        this->seatNo = eventRoom.seatNo;
        this->pavilion = eventRoom.pavilion;
        this->facilities = eventRoom.facilities;
    }

    return *this;
}

// string cast
EventRoom::operator string() {

    if (this->pavilion == 'X') {
        return "There is no pavilion assigned yet!";
    }
    else if (this->roomName == "New Room") {
        return "There are no room name assigned yet!";
    }
    else {
        return "This room is called " + this->roomName + " and is situated in pavilion " + this->pavilion + ".";
    }
}

string EventRoom::operator[](int x) {
    if (this->facilities.empty()) {
        throw runtime_error("No hosts have been named yet!");
    }
    if (x < 0 || x >= this->noOfFacilities) {
        throw runtime_error("Invalid index!");
    }

    return this->facilities[x];
}


bool EventRoom::operator==(const EventRoom& eventRoom) {
    return this->roomName == eventRoom.roomName;
}

EventRoom EventRoom::operator++(int) {
    EventRoom aux(*this);
    this->seatNo++;
    return aux;
}


EventRoom& EventRoom::operator++() {
    this->seatNo++;
    return *this;
}

bool EventRoom::operator<(const EventRoom& eventRoom) {
    return this->seatNo < eventRoom.seatNo;
}

// + overload
EventRoom EventRoom::operator+(int newSeats){
    EventRoom aux(*this);
    aux.seatNo += newSeats;
    return aux;
}

// - overload 
EventRoom EventRoom::operator-(int newSeats) {
    EventRoom aux(*this);
    aux.seatNo -= newSeats;
    return aux;
}

// comutative -
EventRoom operator-(int newSeats, EventRoom eventRoom) {
    EventRoom aux(eventRoom);
    aux.seatNo -= newSeats;
    return aux;
}

// comutative +
EventRoom operator+(int newSeats, EventRoom eventRoom) {
    EventRoom aux(eventRoom);
    aux.seatNo += newSeats;
    return aux;
}

void EventRoom::printEventRoom() {
    std::cout << *this;
}

class Conference {
protected:

    const int conferenceID;
    static int countConference;

    int expectedAtendees;
    float duration;
    string conferenceTitle;
    int hostNo;
    vector <string> hostNames;
    EventRoom eventRoom;

public:


    // getters 
    const int getConferenceID() { return this->conferenceID; };
    int getExpectedAtendees() { return this->expectedAtendees; };
    float getDuration() { return this->duration; };
    string getConferenceTitle() { return this->conferenceTitle; };
    int getHostNo() { return this->hostNo; };
    vector <string> getHostNames() { return this->hostNames; };

    // setters 
    void setExpectedAtendees(int expectedAtendees) { this->expectedAtendees = expectedAtendees; };
    void setDuration(float duration) { this->duration = duration; };
    void setConferenceTitle(string conferenceTitle) { this->conferenceTitle = conferenceTitle; };
    void setHostNo(int hostNo) { this->hostNo = hostNo; };
    void setHostNames(vector <string> hostNames) { this->hostNames = hostNames; };

    Conference(); // empty constructor
    ~Conference(); // destructor
    Conference(int expectedAtendees, float duration, string conferenceTitle, Company* hostingCompany, int hostNo, vector <string> hostNames); // full constructor
    Conference(const Conference& conference); // copy constructor
    Conference(int expectedAtendees, float duration, string conferenceTitle, int hostNo, vector <string> hostNames); // partial constructor 1
    Conference(string conferenceTitle); // partial constructor 2
    friend ostream& operator <<(ostream& out, const Conference& conference); // output operator overload
    friend istream& operator >>(istream& in, Conference& conference); // input operator overload
    Conference& operator=(const Conference& conference); // = overload
    bool operator==(const Conference&); // == overload
    bool operator<(const Conference&); // < overload
    operator string(); // string cast overload
    string operator[](int); // index overload 
    Conference& operator++(); // prefix overload
    Conference operator++(int); // postfix overload
    Conference operator+(string); // + overload  
    Conference operator-(string); // - overload 
    friend Conference operator+(string, Conference); // + commutative
    friend Conference operator-(string, Conference); // - commutative
    Conference operator+(const Conference&); // addition
    void printConference();

};

int Conference::countConference = 1000;

// empty constructor
Conference::Conference():conferenceID(countConference++) {
    this->expectedAtendees = 0;
    this->duration = 0.0f;
    this->conferenceTitle = "New Conference";
    this->hostNo = 0;
}
// destructor
Conference::~Conference(){
    //this->hostNames.clear();
    if (&(this->eventRoom) != NULL) {
        delete &(this->eventRoom);
    }
}

// full constructor
Conference::Conference(int expectedAtendees, float duration, string conferenceTitle, Company* hostingCompany, int hostNo, vector <string> hostNames) :conferenceID(countConference++) {
    this->expectedAtendees = expectedAtendees;
    this->duration = duration;
    this->conferenceTitle = conferenceTitle;
    this->hostNo = hostNo;
    this->hostNames = hostNames;
}

// copy constructor
Conference::Conference(const Conference& conference) :conferenceID(countConference++) {
    this->expectedAtendees = conference.expectedAtendees;
    this->duration = conference.duration;
    this->conferenceTitle = conference.conferenceTitle;
    this->hostNo = conference.hostNo;
    this->hostNames = conference.hostNames;

    this->eventRoom = conference.eventRoom;
}

// << overload
ostream& operator <<(ostream& out, const Conference& conference) {

    out << "The conference's title is " << conference.conferenceTitle << "." << endl;
    out << "This conference is expected to have " << conference.expectedAtendees << " attendants." << endl;
    out << "This conference will last " << conference.duration << " hours." << endl;
    out << "Data about the event room: " << endl;
    out << conference.eventRoom;

    return out;
}

// >> overload
istream& operator >>(istream& in, Conference& conference) {

    std::cout << "What is this conference's title: ";
    in >> conference.conferenceTitle;

    std::cout << "How many attendants do you expect: ";
    in >> conference.expectedAtendees;

    std::cout << "How long do you think this conference will last: ";
    in >> conference.duration;

    std::cout << "How many hosts will this conference have: ";
    in >> conference.hostNo;

    for (int i = 1; i <= conference.hostNo; i++) {
        std::cout << "Enter the name of host " << i << ": ";
        string aux;
        in >> aux;
        conference.hostNames.push_back(aux);
    }

    std::cout << "Please enter data about the event room: " << endl;
    in >> conference.eventRoom;

    return in;
}

// = overload
Conference& Conference::operator=(const Conference& conference) {
    if (this != &conference) {
        this->expectedAtendees = conference.expectedAtendees;
        this->duration = conference.duration;
        this->conferenceTitle = conference.conferenceTitle;
        this->hostNo = conference.hostNo;
        this->hostNames = conference.hostNames;
    }
    return *this;
}

// string cast
Conference::operator string() {

    if (this->conferenceTitle == "New Conference") {
        return "There is no conference name assigned yet!";
    }
    else if (this->hostNo == 0) {
    return "This conference does not have hosts assigned yet!";
    }
}

// == overload
bool Conference::operator==(const Conference& conference) {
    return (this->conferenceTitle == conference.conferenceTitle);
}

// [] overload
string Conference::operator[](int x) {
    if (this->hostNames.empty()) {
        throw runtime_error("No hosts have been named yet!");
    }
    if (x < 0 || x >= this->hostNo) {
        throw runtime_error("Invalid index!");
    }

    return this->hostNames[x];
}


// prefix overload
Conference& Conference::operator++() {
    this->duration++;
    return *this;
}

// postfix overload
Conference Conference::operator++(int) {
    Conference aux(*this);
    this->duration++;
    return aux;
}

// < overload
bool Conference::operator<(const Conference& conference) {
    return this->expectedAtendees < conference.expectedAtendees;
}


// + overload  
Conference Conference::operator+(string representative) {
    this->hostNo++;
    this->hostNames.push_back(representative);
    return *this;
}

// - overload 
Conference Conference::operator-(string representative) {
    vector <string> auxx;
    for (auto& rep : this->hostNames) {
        if (rep != representative) {
            auxx.push_back(rep);
        }
        else {
            this->hostNo--;
        }
    }
    this->hostNames = auxx;
    return *this;
}

// string + conference
Conference operator+(string str, Conference conference){
    for (auto& name : conference.hostNames) {
        if (str == name) {
            return conference;
        }
    }
    conference.hostNo++;
    conference.hostNames.push_back(str);
    return conference;
}

// string - conference
Conference operator-(string str, Conference conference){
    for (int i = 0; i < conference.hostNo; i++) {
        if (str == conference.hostNames[i]) {
            conference.hostNames.erase(conference.hostNames.begin() + i);
            i--;
            conference.hostNo--;
        }
    }
    return conference;
}

// addition between two of the same
Conference Conference::operator+(const Conference& conference) {
    Conference ans(*this);
    // illegal action, just return the first operator
    if (ans == conference) {
        // add the two representative teams
        for (auto& rep : conference.hostNames) {
            ans.hostNames.push_back(rep);
        }
        ans.expectedAtendees += conference.expectedAtendees;
        ans.hostNo += conference.hostNo;

        return ans;
    }
    else {
        throw runtime_error("Two different conferences should not be added together!");
    }
}

void Conference::printConference() {
    std::cout << *this;
}

class Calendar {
private:

    const int calendarID;
    static int countCalendar;

    string calendarName;
    string eventType;
    string month;
    int noOfDays;
    int* dates;

public:

    // getters 
    const int getCalendarID() { return this->calendarID; };
    string getCalendarName() { return this->calendarName; };
    string getEventTypee() { return this->eventType; };
    string getMonth() { return this->month; };
    int getnoOfDays() { return this->noOfDays; };
    int* getDates() { return this->dates; };

    // setters 
    void setCalendarName(string calendarName) { this->calendarName = calendarName; };
    void setEventTypee(string eventType) { this->eventType = eventType; };
    void setMonth(string month) { this->month = month; };
    void setnoOfDays(int noOfDays) { this->noOfDays = noOfDays; };
    void setDates(int dates[]);

    Calendar(); // empty constructor
    ~Calendar(); // destructor
    Calendar(string calendarName, string eventType, string month, int noOfDays, int* dates); // full constructor
    Calendar(string calendarName, string month, int noOfDays, int* dates); // partial constructor 1
    Calendar(string calendarName); // partial constructor 2
    Calendar(const Calendar& calendar); // copy constructor
    friend ostream& operator <<(ostream& out, const Calendar& calendar); // output operator overload
    friend istream& operator >>(istream& in, Calendar& calendar); // input operator overload
    Calendar& operator=(const Calendar& calendar); // = overload
    int operator[](int); // [] overload
    Calendar& operator++(); // ++ prefix operator
    Calendar operator++(int); // ++ postfix operator
    Calendar operator+(int); // + overload  
    Calendar operator-(int); // - overload 
    friend Calendar operator-(int, Calendar); // - comutativ
    friend Calendar operator+(int, Calendar); // + comutativ
    bool operator==(const Calendar&); // == overload
    bool operator<(const Calendar&); // < overload
    void printCalendar();
    operator string(); // string cast
};

void Calendar::setDates(int dates[]) {
    if (this->dates != NULL) {
        delete[] this->dates;
    }

    this->dates = new int[this->noOfDays];
    for (int i = 0; i < this->noOfDays; i++) {
        this->dates[i] = dates[i];
    }
}

int Calendar::countCalendar = 10000;

// full constructor
Calendar::Calendar(string calendarName, string eventType, string month, int noOfDays, int* dates) :calendarID(countCalendar++) {
    this->calendarName = calendarName;
    this->eventType = eventType;
    this->month = month;
    this->noOfDays = noOfDays;

    this->dates = new int[noOfDays];
    for (int i = 0; i < noOfDays; i++) {
        this->dates[i] = dates[i];
    }
}

// partial constructor 1
Calendar::Calendar(string calendarName, string month, int noOfDays, int* dates) :calendarID(countCalendar++) {
    this->calendarName = calendarName;
    this->eventType = "Unassigned";
    this->month = month;
    this->noOfDays = noOfDays;

    this->dates = new int[noOfDays];
    for (int i = 0; i < noOfDays; i++) {
        this->dates[i] = dates[i];
    }
}

// partial constructor 2
Calendar::Calendar(string calendarName) :calendarID(countCalendar++) {
    this->calendarName = calendarName;
    this->eventType = "Unassigned";
    this->month = "Unassigned";
    this->noOfDays = 0;
    this->dates = NULL;
}


// empty constructor
Calendar::Calendar():calendarID(countCalendar++) {
    this->calendarName = "New Calendar";
    this->eventType = "Unassigned";
    this->month = "Unassigned";
    this->noOfDays = 0;
    this->dates = NULL; 
}

// destructor
Calendar::~Calendar() {
    
    if (this->dates != NULL) {
        delete[] this->dates;
        this->dates = NULL;
    }
}

// copy constructor
Calendar::Calendar(const Calendar& calendar) :calendarID(countCalendar++){
    this->calendarName = calendar.calendarName;
    this->eventType = calendar.eventType;
    this->month = calendar.month;
    this->noOfDays = calendar.noOfDays;

    this->dates = new int[calendar.noOfDays];
    for (int i = 0; i < calendar.noOfDays; i++) {
        this->dates[i] = calendar.dates[i];
    }
}

ostream& operator <<(ostream& out, const Calendar& calendar) {
    
    out << "This calendar is called " << calendar.calendarName << "." << endl;
    out << "The type of event it tracks is " << calendar.eventType << "." << endl;
    out << "The event takes place in the month of " << calendar.month << ", across " << calendar.noOfDays << " days." << endl;
    out << "The days in which the event takes place are: ";
    for (int i = 1; i <= calendar.noOfDays - 1; i++) {
        out << calendar.dates[i - 1] << ", ";
    }
    out << calendar.dates[calendar.noOfDays - 1] <<".\n";

    return out;
}

istream& operator >>(istream& in, Calendar& calendar){

    std::cout << "Enter calendar name: ";
    in >> calendar.calendarName;

    std::cout << "Enter event type: ";
    in >> calendar.eventType;

    std::cout << "Enter the month in which the event takes place: ";
    in >> calendar.month;

    std::cout << "How many days will the event span: ";
    in >> calendar.noOfDays;

    if (calendar.dates != NULL) {
        delete[] calendar.dates;
        calendar.dates = NULL;
    }

    calendar.dates = new int[calendar.noOfDays];

    std::cout << "Enter the days the event will take place: " << endl;
    for (int i = 1; i <= calendar.noOfDays; i++) {
        std::cout << "Day " << i << ": ";
        in >> calendar.dates[i-1];
    }

    return in;
}


// = overload
Calendar& Calendar::operator=(const Calendar& calendar){
    
    if (this != &calendar) {
        this->calendarName = calendar.calendarName;
        this->eventType = calendar.eventType;
        this->month = calendar.month;
        this->noOfDays = calendar.noOfDays;

        if (this->dates != NULL) {
            delete[] this->dates;
        }

        this->dates = new int[calendar.noOfDays];
        for (int i = 0; i < calendar.noOfDays; i++) {
            this->dates[i] = calendar.dates[i];
        }
    }
    
    return *this;
}


// [] overload
int Calendar::operator[](int zi) {
    if (zi < 0 || zi >= this->noOfDays) throw runtime_error("Invalid index!");
    if (this->noOfDays == NULL) throw runtime_error("Days were not assigned!");

    return this->dates[zi];
}

// ++ prefix overload
Calendar& Calendar::operator++() {
    
    if (this->dates != NULL) {
        int* aux = new int[this->noOfDays];
        for (int i = 0; i < noOfDays; i++) aux[i] = this->dates[i];

        delete[] this->dates;
        this->noOfDays++;
        this->dates = new int[this->noOfDays];
        for (int i = 0; i < noOfDays - 1; i++) this->dates[i] = aux[i];
        this->dates[this->noOfDays - 1] = 0;
    }
    else {
        this->noOfDays = 1;
        this->dates = new int(0);
    }

    return *this;
}

// ++ postfix operator
Calendar Calendar::operator++(int) {
    Calendar aux(*this);

    if (this->dates != NULL) {
        int* aux = new int[this->noOfDays];
        for (int i = 0; i < this->noOfDays; i++){
            aux[i] = this->dates[i];
        }

        delete[] this->dates;
        this->noOfDays++;
        this->dates = new int[this->noOfDays];
        for (int i = 0; i < this->noOfDays - 1; i++){
            this->dates[i] = aux[i];
        }
        this->dates[this->noOfDays - 1] = 0;
    }
    else {
        this->noOfDays = 1;
        this->dates = new int(0);
    }

    return aux;
}

// string cast
Calendar::operator string() {
    
    if (this->month == "Unassigned") {
        return "There is no month assigned yet!";
    }
    else if (this->noOfDays == 0) {
        return "There are no days assigned yet!";
    }
    else {
        string aux = "This event will take place in ";
        aux += this->month + " ";
        aux += "during the following days: ";
        for (int i = 0; i < this->noOfDays - 1; i++) {
            aux += to_string(this->dates[i]);
            aux += ", ";
        }
        aux += to_string(this->dates[this->noOfDays - 1]) + ".";
        return aux;
    }
}

// == overload
bool Calendar::operator==(const Calendar& calendar) {
    return this->calendarName == calendar.calendarName;
}

// < overload
bool Calendar::operator<(const Calendar& calendar) {
    return this->noOfDays < calendar.noOfDays;
}

// + overload  
Calendar Calendar::operator+(int x){
    Calendar ans(*this);

    int* aux = new int[ans.noOfDays];
    for (int i = 0; i < this->noOfDays; i++) {
        aux[i] = ans.dates[i];
    }

    delete[] ans.dates;
    ans.dates = new int[++ans.noOfDays];
    for (int i = 0; i < this->noOfDays; i++) {
        ans.dates[i] = aux[i];
    }
    ans.dates[ans.noOfDays - 1] = x;

    return ans;
}

// - overload 
Calendar Calendar::operator-(int x) {
    int ok = 0;

    for (int i = 0; i < this->noOfDays; i++) {
        if (this->dates[i] == x) ok = 1;
    }
    if (ok) {
        Calendar ans(*this);

        delete[] ans.dates;
        ans.dates = new int[--ans.noOfDays];
        int ptr = 0;

        for (int i = 0; i < this->noOfDays; i++) {
            if (this->dates[i] == x) continue;
            ans.dates[ptr++] = this->dates[i];
        }

        return ans;
    }
    else {
        throw runtime_error("This date does not exist!");
    }
}

// - comutativ
Calendar operator-(int x, Calendar calendar) {
    int ok = 0;

    for (int i = 0; i < calendar.noOfDays; i++) {
        if (calendar.dates[i] == x) ok = 1;
    }
    if (ok) {
        Calendar ans(calendar);

        delete[] ans.dates;
        ans.dates = new int[--ans.noOfDays];
        int ptr = 0;

        for (int i = 0; i < calendar.noOfDays; i++) {
            if (calendar.dates[i] == x) continue;
            ans.dates[ptr++] = calendar.dates[i];
        }

        return ans;
    }
    else {
        throw runtime_error("This date does not exist!");
    }
}

// + comutativ
Calendar operator+(int x, Calendar calendar) {
    Calendar ans(calendar);

    int* aux = new int[ans.noOfDays];
    for (int i = 0; i < calendar.noOfDays; i++) {
        aux[i] = ans.dates[i];
    }

    delete[] ans.dates;
    ans.dates = new int[++ans.noOfDays];
    for (int i = 0; i < calendar.noOfDays; i++) {
        ans.dates[i] = aux[i];
    }
    ans.dates[ans.noOfDays - 1] = x;

    return ans;
}

void Calendar::printCalendar() {
    std::cout << *this;
}

class Event {
private:

    const int eventID;
    static int countEvent;

    // own variables
    int expectedAtendees;
    int reservedRooms;
    int conferenceNo;
    float span;
    char* eventName;

    // class variables
    Company hostCompany;
    vector<Company*> attendingCompanies;
    Calendar calendar;
    vector<Conference*> conferences;

public:

    // getters 
    const int getEventID() { return this->eventID; };
    int getExpectedAtendees() { return this->expectedAtendees; };
    int getConferenceNo() { return this->conferenceNo; };
    int getReservedRooms() { return this->reservedRooms; };
    float getSpan() { return this->span; };
    char* getEventName() { return this->eventName; };

    // setters 
    void setExpectedAtendees(int expectedAtendees) { this->expectedAtendees = expectedAtendees; };
    void setConferenceNo(int conferenceNo) { this->conferenceNo = conferenceNo; };
    void setReservedRooms(int reservedRooms) { this->reservedRooms = reservedRooms; };
    void setSpan(float span) { this->span = span; };
    void setEventName(char* eventName);

    Event(); // empty constructor
    ~Event(); // destructor
    Event(int expectedAtendees, int reservedRooms, int conferenceNo, float span, char* eventName); // full constructor
    Event(int conferenceNo, char* eventName); // partial constructor 1
    Event(char* eventName); // partial constructor 2
    Event(const Event& event); // copy constructor
    friend ostream& operator <<(ostream& out, const Event& event); // output operator overload
    friend istream& operator >>(istream& in, Event& event); // input operator overload
    Event& operator=(const Event& event); // = overload
    Conference& operator[](int); // index overload
    operator string(); // string cast
    Event& operator++(); // prefix overload
    Event operator++(int); // postfix overload
    bool operator==(const Event&); // == overload
    //void createEvent(Company*, Company*, EventRoom*, Calendar*, Conference*); // class function
    bool operator<(const Event&); // < overload

    // Adding and subtracting between Event and Conference
    Event operator+(const Conference&); // + overload  
    Event operator-(const Conference&); // - overload 

    // Addition and subtraction between Conference and Event
    friend Event operator+(Conference, Event); // + overload  
    friend Event operator-(Conference, Event); // - overload 

    Event operator+(const Event&); // + overload  
    Event operator-(const Event&); // - overload 
};

int Event::countEvent = 10;

// setEventName definition
void Event::setEventName(char* eventName) {
    if (this->eventName != NULL) {
        delete[] this->eventName;
        this->eventName = NULL;
    }

    this->eventName = new char[strlen(eventName) + 1];
    strcpy(this->eventName, eventName);
}

// constructor definition
Event::Event() :eventID(countEvent++) {
    this->expectedAtendees = 0;
    this->conferenceNo = 0;
    this->reservedRooms = 0;
    this->span = 0;
    this->eventName = new char[strlen("New Event") + 1];
    strcpy(this->eventName, "New Event");
}

// partial constructor 1
Event::Event(int conferenceNo, char* eventName) :eventID(countEvent++) {
    this->expectedAtendees = 0;
    this->reservedRooms = 0;
    this->conferenceNo = conferenceNo;
    this->span = 0;
    this->eventName = new char[strlen(eventName) + 1];
    strcpy(this->eventName, eventName);

}

// partial constructor 2
Event::Event(char* eventName) :eventID(countEvent++) {
    this->expectedAtendees = 0;
    this->conferenceNo = 0;
    this->reservedRooms = 0;
    this->span = 0;
    this->eventName = new char[strlen(eventName) + 1];
    strcpy(this->eventName, eventName);

}

// destructor
Event::~Event() {
    if (this->eventName != NULL) {
        delete[] this->eventName;
    }

    for (auto& x : attendingCompanies) delete x;
    //for (auto& x : conferences) delete x;
    attendingCompanies.clear();
    conferences.clear();
}

// full constructor
Event::Event(int expectedAtendees, int reservedRooms, int conferenceNo, float span, char* eventName):eventID(countEvent++) {
    this->expectedAtendees = expectedAtendees;
    this->conferenceNo = conferenceNo;
    this->reservedRooms = reservedRooms;
    this->span = span;
    this->eventName = new char[strlen(eventName) + 1];
    strcpy(this->eventName, eventName);

}

// copy constructor
Event::Event(const Event& event) :eventID(countEvent++) {
    this->expectedAtendees = event.expectedAtendees;
    this->conferenceNo = event.conferenceNo;
    this->reservedRooms = event.reservedRooms;
    this->reservedRooms = reservedRooms;
    this->span = event.span;
    this->eventName = new char[strlen(event.eventName) + 1];
    strcpy(this->eventName, event.eventName);


    Company hostCompany;
    vector<Company*> attendingCompanies;
    Calendar calendar;
    vector<Conference*> conferences;

    this->hostCompany = event.hostCompany;
    this->calendar = event.calendar;

    for (int i = 0; i < this->conferenceNo; i++) this->conferences.push_back(new Conference);
    for (int i = 0; i < this->conferenceNo; i++) *this->conferences[i] = (*(event.conferences[i]));
    for (int i = 0; i < this->expectedAtendees; i++) this->attendingCompanies.push_back(new Company);
    for (int i = 0; i < this->expectedAtendees; i++) *this->attendingCompanies[i] = (*(event.attendingCompanies[i]));
}

// = overload
Event& Event::operator=(const Event& event) {
    if (this != &event) {
        if (this->eventName != NULL) {
            delete[] this->eventName;
            this->eventName = NULL;
        }

        this->expectedAtendees = event.expectedAtendees;
        this->conferenceNo = event.conferenceNo;
        this->reservedRooms = event.reservedRooms;
        this->hostCompany = event.hostCompany;
        this->span = event.span;
        this->eventName = new char[strlen(event.eventName) + 1];
        strcpy(this->eventName, event.eventName);

        this->hostCompany = event.hostCompany;
        this->attendingCompanies = event.attendingCompanies;
        this->calendar = event.calendar;
        this->conferences = event.conferences;
    }
    return *this;
}

// overload input
istream& operator>>(istream& in, Event& event) {

    

    // class variables
    Company hostCompany;
    vector<Company*> attendingCompanies;
    Calendar calendar;
    vector<Conference*> conferences;


    std::cout << "How many attendants do you expect: ";
    in >> event.expectedAtendees;

    std::cout << "How many conferences do you want to host: ";
    in >> event.conferenceNo;

    std::cout << "How long do you expect to hold your event: ";
    in >> event.span;

    if (event.eventName != NULL) {
        delete[] event.eventName;
        event.eventName = NULL;
    }

    char aux[50];
    std::cout << "What is the event name: ";
    in >> aux;
    event.eventName = new char[strlen(aux) + 1];
    strcpy(event.eventName, aux);

    std::cout << endl;

    std::cout << "Enter data about host company: " << endl;
    in >> event.hostCompany;

    std::cout << "Enter data about calendar: " << endl;
    in >> event.calendar;

    for (int i = 1; i <= event.conferenceNo; i++) {
        event.conferences.push_back(new Conference);
        std::cout << "Enter data about conference no. " << i << ": ";
        cin >> *event.conferences[i - 1];
    }

    for (int i = 1; i <= event.expectedAtendees; i++) {
    event.attendingCompanies.push_back(new Company);
        std::cout << "Enter data about attending company no. " << i << ": ";
        cin >> *event.attendingCompanies[i - 1];
    }

    return in;
}

// overload output
ostream& operator<<(ostream& out, const Event& event) {
    out << "This event is expected to have " << event.expectedAtendees << " attendants." << endl;
    out << "This event will have a numer of " << event.conferenceNo << " conferences." << endl;
    out << "The event is expected to last a number of " << event.span << " days." << endl;
    out << "The event is called " << event.eventName << "." << endl;
    out << "Data about the hosting company: " << endl;
    out << event.hostCompany;
    out << "Data about the program: " << endl;
    out << event.calendar;
    out << "Data about the attending companies: " << endl;
    for (auto& x : event.attendingCompanies) out << x << endl;
    for (auto& x : event.conferences) out << x << endl;

    return out;
}

// string cast
Event::operator string() {

    if (this->eventName == "New Event") {
        return "There is no event name assigned yet!";
    }
    else if (this->conferenceNo == 0) {
        return "There are no conferences assigned yet!";
    }
    else {
        string aux = "This event is called ";
        string aux2(this->eventName);
        aux += aux2 + " ";
        aux += "and is brought to you by ";
        //aux += this->hostCompany->getCompanyName() + ".\n";
        aux += "It will consist of " + to_string(this->conferenceNo) + " conferences called: \n";
        
        return aux;
    }
}

//// index overload
//Conference& Event::operator[](int x) {
//
//    /*if (this->conferences == NULL) {
//        throw runtime_error("No conferences assigned to this event!");
//    }
//    if (x < 0 || x >= this->conferenceNo) {
//        throw runtime_error("Invalid index!");
//    }
//
//    return this->conferences[x];*/
//}

// prefix overload
Event& Event::operator++() {
    this->span++;
    return *this;
}

// postfix overload
Event Event::operator++(int) {
    Event aux(*this);
    this->span++;
    return aux;
}

// == overload
bool Event::operator==(const Event& event) {

    if (strcmp(this->eventName, event.eventName)) {
        return false;
    } return true;
    //return this->eventName == event.eventName;
}


// < operator
bool Event::operator<(const Event& event) {
    return this->conferenceNo < event.conferenceNo;
}

//// Event + Conference
//Event Event::operator+(const Conference& conference) {
//    Event ans(*this);
//
//    for (int i = 0; i < this->conferenceNo; i++) {
//        if (*this->conferences[i] == conference) {
//            throw runtime_error("This conference is already in this event!");
//        }
//    }
//    Conference* aux = new Conference[this->conferenceNo];
//    for (int i = 0; i < this->conferenceNo; i++) {
//        aux[i] = this->conferences[i];
//    }
//    ans.conferences = new Conference[++ans.conferenceNo];
//    for (int i = 0; i < ans.conferenceNo - 1; i++) {
//        ans.conferences[i] = aux[i];
//    }
//    ans.conferences[ans.conferenceNo - 1] = conference;
//
//    return ans;
//}
//
//// Event - Conference
//Event Event::operator-(const Conference& conference) {
//    Event ans(*this);
//    Conference* aux = new Conference[this->conferenceNo - 1];
//    int ptr = 0;
//    int ok = 0;
//
//    for (int i = 0; i < this->conferenceNo; i++) {
//        if (this->conferences[i] == conference) {
//            ok = 1;
//            break;
//        }
//    }
//    if (ok) {
//        
//        for (int i = 0; i < this->conferenceNo; i++) {
//            if (this->conferences[i] == conference) {
//                continue;
//            }
//            else {
//                aux[ptr++] = this->conferences[i];
//            }
//        }
//        ans.conferences = new Conference[--ans.conferenceNo];
//        for (int i = 0; i < ans.conferenceNo - 1; i++) {
//            ans.conferences[i] = aux[i];
//        }
//
//        return ans;
//    }
//    else {
//        throw runtime_error("This conference does not exist in the event!");
//    }
//}
//
//// Conference + Event
//Event operator+(Conference conference, Event event) {
//    Event ans(event);
//
//    for (int i = 0; i < event.conferenceNo; i++) {
//        if (event.conferences[i] == conference) {
//            throw runtime_error("This conference is already in this event!");
//        }
//    }
//    Conference* aux = new Conference[event.conferenceNo];
//    for (int i = 0; i < event.conferenceNo; i++) {
//        aux[i] = event.conferences[i];
//    }
//    ans.conferences = new Conference[++ans.conferenceNo];
//    for (int i = 0; i < ans.conferenceNo - 1; i++) {
//        ans.conferences[i] = aux[i];
//    }
//    ans.conferences[ans.conferenceNo - 1] = conference;
//
//    return ans;
//}
//
//// Conference - Event
//Event operator-(Conference conference, Event event) {
//    Event ans(event);
//
//    Conference* aux = new Conference[event.conferenceNo - 1];
//    int ptr = 0;
//    int ok = 0;
//
//    for (int i = 0; i < event.conferenceNo; i++) {
//        if (event.conferences[i] == conference) {
//            ok = 1;
//            break;
//        }
//    }
//    if (ok) {
//        for (int i = 0; i < event.conferenceNo; i++) {
//            if (event.conferences[i] == conference) {
//                continue;
//            }
//            else {
//                aux[ptr++] = event.conferences[i];
//            }
//        }
//        ans.conferences = new Conference[--ans.conferenceNo];
//        for (int i = 0; i < ans.conferenceNo; i++) {
//            ans.conferences[i] = aux[i];
//        }
//
//        return ans;
//    }
//    else {
//        throw runtime_error("This conference does not exist in the event!");
//    }
//}

//// + overload  
//Event Event::operator+(const Event& event) {
//    Event ans(*this);
//    Conference* aux = new Conference[this->conferenceNo + event.conferenceNo];
//
//    for (int i = 0; i < this->conferenceNo; i++) {
//        aux[i] = this->conferences[i];
//    }
//    for (int i = this->conferenceNo; i < this->conferenceNo + event.conferenceNo; i++) {
//        aux[i] = event.conferences[i - this->conferenceNo];
//    }
//    ans.conferenceNo += event.conferenceNo;
//    ans.conferences = aux;
//
//    return ans;
//}
//
//// - overload 
//Event Event::operator-(const Event& event) {
//    Event ans(*this);
//
//    for (int i = 0; i < event.conferenceNo; i++) {
//        ans = (ans - event.conferences[i]);
//    }
//    return ans;
//}


// MAIN MENU
int main() {

    std::cout << "Welcome to event planner!" << endl;
    std::cout << "The instruction to be used is written between round braces, as in the following example: (your_command_here)." << endl << endl;
    std::cout << "Please enter one of the following instructions: " << endl;
    std::cout << "1. Create (create)" << endl;
    std::cout << "2. Read (read)" << endl;
    std::cout << "3. Update (update)" << endl;
    std::cout << "4. Print (print)" << endl;
    std::cout << "5. Quit (quit)" << endl;
    string input = "";
    std::cin >> input;
    std::transform(input.begin(), input.end(), input.begin(), ::tolower);

    vector <Event*> Events;

    
    while (input != "quit") {
        
        if (input == "create" || input == "c") {

            while (input != "continue") {

                std::cout << "1. Create event (create_event)" << endl;
                std::cout << "2. Continue to other instructions (continue)" << endl;
                std::cin >> input;
                std::transform(input.begin(), input.end(), input.begin(), ::tolower);
                

                if (input == "create_event" || input == "ce") {
                    Events.push_back(new Event);
                    std::cout << "Event " << Events.size() << " created!" << endl;
                }
                else if (input != "continue") {
                    std::cout << "Unknown command. Please try again!" << endl;
                }
            }

        }
        else if (input == "read" || input == "r") {
            while (input != "continue") {
                int pos = 0;

                std::cout << "1. Read event (read_event)" << endl;
                std::cout << "2. Continue to other instructions (continue)" << endl;
                std::cin >> input;
                std::transform(input.begin(), input.end(), input.begin(), ::tolower);

                if (input == "read_event" || input == "re") {
                    if (!Events.empty()) {
                        std::cout << "Choose the index: 1 -> " << Events.size() << ": ";
                        std::cin >> pos;
                        if (0 < pos && pos <= Events.size()) {
                            std::cin >> *(Events[pos - 1]);
                        }
                        else {
                            std::cout << "Invalid index! Try again!" << endl;
                        }
                    }
                    else {
                        std::cout << "You should create an event first!" << endl;
                    }
                }
                else if (input != "continue") {
                    std::cout << "Unknown command. Please try again!" << endl;
                }
            }
        }
        //else if (input == "update") {
        //    while (input != "continue") {

        //        std::cout << "1. Link structures to an event (link_to_event)" << endl;
        //        std::cout << "2. Link host company to conference (link_to_conference);" << endl;
        //        std::cout << "3. Continue to other instructions (continue)" << endl;
        //        std::cin >> input;
        //        std::transform(input.begin(), input.end(), input.begin(), ::tolower);

        //        if (input == "link_to_event") {
        //            int ptr = 0;
        //            cout << "Choose the event! (1 -> " << ptrEvent << "): ";
        //            cin >> ptr;
        //            if (0 < ptr && ptr <= ptrEvent) {
        //                int ptr2 = 0;
        //                cout << "Your event needs a host. Choose one of the following: ";
        //                for (int i = 1; i <= ptrCompany; i++) {
        //                    if (Companies[i - 1]->getHosting() == true) cout << i << " ";
        //                }
        //                cin >> ptr2;
        //                if (Companies[ptr2 - 1]->getHosting() == true) {
        //                    Events[ptr - 1]->setHostCompany(Companies[ptr2-1]);
        //                }
        //                else {
        //                    cout << "Please try again!" << endl;
        //                }

        //                ptr2 = 0;
        //                cout << "Your event needs " << Events[ptr - 1]->getExpectedAtendees() << " attending companies. Choose from the following : ";
        //                for (int i = 1; i <= ptrCompany; i++) {
        //                    cout << i << " ";
        //                }
        //                Company* lista = new Company[Events[ptr - 1]->getExpectedAtendees()];
        //                for (int i = 0; i < Events[ptr - 1]->getExpectedAtendees(); i++) {
        //                    cin >> ptr2;
        //                    if (0 < ptr2 && ptr2 <= Events[ptr - 1]->getExpectedAtendees()) {
        //                        lista[i] = *Companies[ptr2 - 1];
        //                    }
        //                    else {
        //                        cout << "Please try again!" << endl;
        //                        i--;
        //                    }
        //                }


        //                Events[ptr - 1]->setAttendingCompanies(lista);


        //                //eventrooms
        //                ptr2 = 0;
        //                cout << "Your event needs " << Events[ptr - 1]->getReservedRooms() << " attending companies. Choose from the following : ";
        //                for (int i = 1; i <= ptrER; i++) {
        //                    cout << i << " ";
        //                }
        //                EventRoom* lista2 = new EventRoom[Events[ptr - 1]->getReservedRooms()];
        //                for (int i = 0; i < Events[ptr - 1]->getReservedRooms(); i++) {
        //                    cin >> ptr2;
        //                    if (0 < ptr2 && ptr2 <= Events[ptr - 1]->getReservedRooms()) {
        //                        lista2[i] = *EventRooms[ptr2 - 1];
        //                    }
        //                    else {
        //                        cout << "Please try again!" << endl;
        //                        i--;
        //                    }
        //                }


        //                Events[ptr - 1]->setEventRooms(lista2);


        //                //conferences
        //                ptr2 = 0;
        //                cout << "Your event needs " << Events[ptr - 1]->getConferenceNo() << " conferences. Choose from the following : ";
        //                for (int i = 1; i <= ptrConf; i++) {
        //                    cout << i << " ";
        //                }
        //                Conference* lista3 = new Conference[Events[ptr - 1]->getConferenceNo()];
        //                for (int i = 0; i < Events[ptr - 1]->getConferenceNo(); i++) {
        //                    cin >> ptr2;
        //                    if (0 < ptr2 && ptr2 <= Events[ptr - 1]->getConferenceNo()) {
        //                        lista3[i] = *Conferences[ptr2 - 1];
        //                    }
        //                    else {
        //                        cout << "Please try again!" << endl;
        //                        i--;
        //                    }
        //                }

        //                Events[ptr - 1]->setConferences(lista3);

        //                // calendar
        //                ptr2 = 0;
        //                cout << "Your event needs a calendar! Choose from the following : ";
        //                for (int i = 1; i <= ptrCal; i++) {
        //                    cout << i << " ";
        //                }
        //                Calendar* lista4 = new Calendar[1];
        //                cin >> ptr2;
        //                if (0 < ptr2 && ptr2 <= ptrCal) {
        //                    lista4[0] = *Calendars[ptr2 - 1];
        //                }
        //                else {
        //                    cout << "Please try again!" << endl;
        //                }


        //                Events[ptr - 1]->setCalendar(lista4);
        //            }
        //            else {
        //                cout << "Please try again!" << endl;
        //            }
        //        }
        //        else if (input == "link_to_conference") {
        //            int ptr = 0;
        //            cout << "Choose the conference! (1 -> " << ptrConf << "): ";
        //            cin >> ptr;
        //            if (0 < ptr && ptr <= ptrConf) {
        //                int ptr2 = 0;
        //                cout << "Your conference needs a company. Choose one of the following: ";
        //                for (int i = 1; i <= ptrCompany; i++) {
        //                    cout << i << " ";
        //                }
        //                cin >> ptr2;
        //                if (0 < ptr2 && ptr2 <= ptrCompany)
        //                    Conferences[ptr - 1]->setHostingCompany(Companies[ptr2 - 1]);
        //                else
        //                    cout << "Please try again!" << endl;
        //            }
        //            else {
        //                cout << "Please try again!" << endl;
        //            }
        //        }
        //        else if (input != "continue") {
        //            std::cout << "Unknown command. Please try again!" << endl;
        //        }

        //    }
        //}
        //else if (input == "print") {
        //    while (input != "continue") {
        //    int pos = 0;

        //        std::cout << "1. Print event (print_event)" << endl;
        //        std::cout << "2. Print company (print_company)" << endl;
        //        std::cout << "3. Print event room (print_eventroom)" << endl;
        //        std::cout << "4. Print conference (print_conference)" << endl;
        //        std::cout << "5. Print calendar (print_calendar)" << endl;
        //        std::cout << "6. Continue to other instructions (continue)" << endl;
        //        std::cin >> input;
        //        std::transform(input.begin(), input.end(), input.begin(), ::tolower);

        //        if (input == "print_event") {
        //            if (0 < ptrEvent) {
        //                std::cout << "Choose the index: 1 -> " << ptrEvent << ": ";
        //                std::cin >> pos;
        //                if (0 < pos && pos <= ptrEvent) {
        //                    std::cout << *(Events[pos - 1]);
        //                }
        //                else {
        //                    std::cout << "Invalid index! Try again!" << endl;
        //                }
        //            }
        //            else {
        //                std::cout << "You should create an event first!" << endl;
        //            }

        //        }
        //        else if (input == "print_company") {
        //            if (0 < ptrCompany) {
        //                std::cout << "Choose the index: 1 -> " << ptrCompany << ": ";
        //                std::cin >> pos;
        //                if (0 < pos && pos <= ptrCompany) {
        //                    std::cout << *(Companies[pos - 1]);
        //                }
        //                else {
        //                    std::cout << "Invalid index! Try again!" << endl;
        //                }
        //            }
        //            else {
        //                std::cout << "You should create a company first!" << endl;
        //            }
        //        }
        //        else if (input == "print_eventroom") {
        //            if (0 < ptrER) {
        //                std::cout << "Choose the index: 1 -> " << ptrER << ": ";
        //                std::cin >> pos;
        //                if (0 < pos && pos <= ptrER) {
        //                    std::cout << *(EventRooms[pos - 1]);
        //                }
        //                else {
        //                    std::cout << "Invalid index! Try again!" << endl;
        //                }
        //            }
        //            else {
        //                std::cout << "You should create an event room first!" << endl;
        //            }
        //        }
        //        else if (input == "print_conference") {
        //            if (0 < ptrConf) {
        //                std::cout << "Choose the index: 1 -> " << ptrConf << ": ";
        //                std::cin >> pos;
        //                if (0 < pos && pos <= ptrConf) {
        //                    std::cout << *(Conferences[pos - 1]);
        //                }
        //                else {
        //                    std::cout << "Invalid index! Try again!" << endl;
        //                }
        //            }
        //            else {
        //                std::cout << "You should create a conference first!" << endl;
        //            }
        //        }
        //        else if (input == "print_calendar") {
        //            if (0 < ptrCal) {
        //                std::cout << "Choose the index: 1 -> " << ptrCal << ": ";
        //                std::cin >> pos;
        //                if (0 < pos && pos <= ptrCal) {
        //                    std::cout << *(Calendars[pos - 1]);
        //                }
        //                else {
        //                    std::cout << "Invalid index! Try again!" << endl;
        //                }
        //            }
        //            else {
        //                std::cout << "You should create a calendar first!" << endl;
        //            }
        //        }
        //        else if (input != "continue") {
        //            std::cout << "Unknown command. Please try again!" << endl;
        //        }
        //    }
        //}
        else if (input != "quit") {
            std::cout << "Unknown command. Please try again!" << endl;
        }

        std::cout << "Please enter one of the following instructions: " << endl;
        std::cout << "1. Create (create)" << endl;
        std::cout << "2. Read (read)" << endl;
        std::cout << "3. Update (update)" << endl;
        std::cout << "4. Print (print)" << endl;
        std::cout << "5. Quit (quit)" << endl;

        std::cin >> input;
        std::transform(input.begin(), input.end(), input.begin(), ::tolower);
    }
    
    std::cout << "Thank you for using our app!" << endl;

    for (auto& x : Events) delete x;
    Events.clear();

    return 0;
}