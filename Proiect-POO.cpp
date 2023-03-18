//CORPORATE EVENT MANAGER - PROJECT WRITTEN BY ALEXANDRU MICLEA
//FMI UNIBUC 2023

// TODO BIG
// 2 * 2 class addition
// menu & functionality

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

#pragma warning (disable : 4996)

// class declarations
class Company;
class Event;
class EventRoom;
class Calendar;
class Conference;


// TODO Company
// partial constructors, functionality


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

};

int Company::countID = 100;

Company::Company() :companyID(countID++) {
    this->hosting = false;
    this->companyName = "New Company";
    this->representativeNo = 0;
    this->representatives.push_back("Representative Name");
}

Company::~Company() {
    this->representatives.clear();
}

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
    cout << "What is your company's name: ";
    in >> company.companyName;

    cout << "Are you expected to host a conference: ";
    in >> company.hosting;

    cout << "How many representatives will be present from your company: ";
    in >> company.representativeNo;

    for (int i = 1; i <= company.representativeNo; i++) {
        cout << "Enter the name of representative " << i << ": ";
        string aux;
        in >> aux;
        company.representatives.push_back(aux);
    }

    cout << endl;
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
// TODO DEBUG
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










































// TODO EventRoom
// functionality


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
    facilities.clear();
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

    cout << "What is this room's name: ";
    in >> eventRoom.roomName;

    cout << "How many seats does it have: ";
    in >> eventRoom.seatNo;

    cout << "In what pavilion does it exist: ";
    in >> eventRoom.pavilion;

    cout << "How many facilities does this room have: ";
    in >> eventRoom.noOfFacilities;

    for (int i = 1; i <= eventRoom.noOfFacilities; i++) {
        cout << "Enter facility number " << i << ": ";
        string aux;
        in >> aux;
        eventRoom.facilities.push_back(aux);
    }

    return in;
}

EventRoom& EventRoom::operator=(const EventRoom& eventRoom){

    if (this != &eventRoom) {
        this->roomName = eventRoom.roomName;
        this->seatNo = eventRoom.seatNo;
        this->pavilion = eventRoom.pavilion;
        this->facilities = eventRoom.facilities;
    }

    return *this;
}

// string cast
// TODO DEBUG
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











































class Conference {
private:

    const int conferenceID;
    static int countConference;

    int expectedAtendees;
    float duration;
    string conferenceTitle;
    Company* hostingCompany;
    int hostNo;
    vector <string> hostNames;

public:


    // getters 
    const int getConferenceID() { return this->conferenceID; };
    int getExpectedAtendees() { return this->expectedAtendees; };
    float getDuration() { return this->duration; };
    string getConferenceTitle() { return this->conferenceTitle; };
    Company* getHostingCompany() { return this->hostingCompany; };
    int getHostNo() { return this->hostNo; };
    vector <string> getHostNames() { return this->hostNames; };

    // setters 
    void setExpectedAtendees(int expectedAtendees) { this->expectedAtendees = expectedAtendees; };
    void setDuration(float duration) { this->duration = duration; };
    void setConferenceTitle(string conferenceTitle) { this->conferenceTitle = conferenceTitle; };
    void setHostingCompany(Company* hostingCompany) { this->hostingCompany = hostingCompany; };
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

};

int Conference::countConference = 1000;

// empty constructor
Conference::Conference():conferenceID(countConference++) {
    this->expectedAtendees = 0;
    this->duration = 0.0f;
    this->conferenceTitle = "New Conference";
    this->hostingCompany = NULL;
    this->hostNo = 0;
}
// destructor
Conference::~Conference(){
    this->hostNames.clear();
}

// full constructor
Conference::Conference(int expectedAtendees, float duration, string conferenceTitle, Company* hostingCompany, int hostNo, vector <string> hostNames) :conferenceID(countConference++) {
    this->expectedAtendees = expectedAtendees;
    this->duration = duration;
    this->conferenceTitle = conferenceTitle;
    this->hostingCompany = hostingCompany;
    this->hostNo = hostNo;
    this->hostNames = hostNames;
}

// copy constructor
Conference::Conference(const Conference& conference) :conferenceID(countConference++) {
    this->expectedAtendees = conference.expectedAtendees;
    this->duration = conference.duration;
    this->conferenceTitle = conference.conferenceTitle;
    this->hostingCompany = conference.hostingCompany;
    this->hostNo = conference.hostNo;
    this->hostNames = conference.hostNames;
}

// << overload
ostream& operator <<(ostream& out, const Conference& conference) {

    out << "The conference's title is " << conference.conferenceTitle << "." << endl;
    out << "This conference is expected to have " << conference.expectedAtendees << " attendants." << endl;
    out << "This conference will last " << conference.duration << " hours." << endl;
    out << "It will be hosted by the " << conference.hostNo << " hosts of " << conference.hostingCompany->getCompanyName() << ". Their names are: " << endl;
    for (int i = 1; i <= conference.hostNo; i++) {
        out << i << ". " << conference.hostNames[i - 1] << endl;
    }

    return out;
}

// >> overload
istream& operator >>(istream& in, Conference& conference) {

    cout << "What is this conference's title: ";
    in >> conference.conferenceTitle;

    cout << "How many attendants do you expect: ";
    in >> conference.expectedAtendees;

    cout << "How long do you think this conference will last: ";
    in >> conference.duration;

    cout << "How many hosts will this conference have: ";
    in >> conference.hostNo;

    for (int i = 1; i <= conference.hostNo; i++) {
        cout << "Enter the name of host " << i << ": ";
        string aux;
        in >> aux;
        conference.hostNames.push_back(aux);
    }

    return in;
}

// = overload
Conference& Conference::operator=(const Conference& conference) {
    if (this != &conference) {
        this->expectedAtendees = conference.expectedAtendees;
        this->duration = conference.duration;
        this->conferenceTitle = conference.conferenceTitle;
        this->hostingCompany = conference.hostingCompany;
        this->hostNo = conference.hostNo;
        this->hostNames = conference.hostNames;
    }
    return *this;
}

// string cast
// TODO DEBUG str cast conf
Conference::operator string() {

    if (this->hostingCompany == NULL) {
        return "There is no company hosting yet!";
    }
    else if (this->conferenceTitle == "New Conference") {
        return "There is no conference name assigned yet!";
    }
    else if (this->hostNo == 0) {
    return "This conference does not have hosts assigned yet!";
    }
    else {
        return this->hostingCompany->getCompanyName();
    }
}

// == overload
bool Conference::operator==(const Conference& conference) {
    return (this->conferenceTitle == conference.conferenceTitle) && (this->hostingCompany->getCompanyName() == conference.hostingCompany->getCompanyName());
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
// TODO test
Conference Conference::operator+(string representative) {
    this->hostNo++;
    this->hostNames.push_back(representative);
    return *this;
}

// - overload 
// TODO test
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
// TODO debug
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
// TODO debug
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
// TODO debug
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











































// TODO Calendar
// +-,  functionality



class Calendar {
private:

    const int calendarID;
    static int countCalendar;

    string calendarName;
    string eventType;
    string month;
    int noOfDays;
    int* dates;

    Event* event;

public:

    // getters 
    const int getCalendarID() { return this->calendarID; };
    string getCalendarName() { return this->calendarName; };
    string getEventTypee() { return this->eventType; };
    string getMonth() { return this->month; };
    int getnoOfDays() { return this->noOfDays; };
    int* getDates() { return this->dates; };
    Event* getEvent() { return this->event; };

    // setters 
    void setCalendarName(string calendarNamecalendarName) { this->calendarName = calendarName; };
    void setEventTypee(string eventType) { this->eventType = eventType; };
    void setMonth(string month) { this->month = month; };
    void setnoOfDays(int noOfDays) { this->noOfDays = noOfDays; };
    void setDates(int dates[]);
    void setEvent(Event* event) {this->event = event;}

    Calendar(); // empty constructor
    ~Calendar(); // destructor
    Calendar(string calendarName, string eventType, string month, int noOfDays, int* dates, Event* event); // full constructor
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
    // adunare cu un int imi adauga atatea zile noi
    Calendar operator-(int); // - overload 
    // scadere cu un int imi scoate atatea zile din calendar
    friend Calendar operator-(int, Calendar); // - comutativ
    friend Calendar operator+(int, Calendar); // + comutativ
    bool operator==(const Calendar&); // == overload
    bool operator<(const Calendar&); // < overload

    operator string(); // string cast
};

void Calendar::setDates(int dates[]) {
    if (this->dates != NULL) {
        delete[] this->dates;
    }

    this->dates = new int[sizeof(dates)];
    for (int i = 0; i < sizeof(dates); i++) {
        this->dates[i] = dates[i];
    }
}

int Calendar::countCalendar = 10000;

// partial constructor 1
Calendar::Calendar(string calendarName, string month, int noOfDays, int* dates) :calendarID(countCalendar++) {
    this->calendarName = calendarName;
    this->eventType = "Unassigned";
    this->month = month;
    this->noOfDays = noOfDays;
    if (this->dates != NULL) {
        delete[] this->dates;
    }

    this->dates = new int[noOfDays];
    for (int i = 0; i < noOfDays; i++) {
        this->dates[i] = dates[i];
    }
    this->event = NULL;
}

// partial constructor 2
Calendar::Calendar(string calendarName) :calendarID(countCalendar++) {
    this->calendarName = calendarName;
    this->eventType = "Unassigned";
    this->month = "Unassigned";
    this->noOfDays = 0;
    this->dates = new int(0);
    this->event = NULL;
}


// empty constructor
Calendar::Calendar():calendarID(countCalendar++) {
    this->calendarName = "New Calendar";
    this->eventType = "Unassigned";
    this->month = "Unassigned";
    this->noOfDays = 0;
    this->dates = new int(0); 
    this->event = NULL;
}

// destructor
Calendar::~Calendar() {
    
    if (this->dates != NULL) {
        delete[] this->dates;
        this->dates = NULL;
    }
}

// full constructor
Calendar::Calendar(string calendarName, string eventType, string month, int noOfDays, int* dates, Event* event):calendarID(countCalendar++) {
    this->calendarName = calendarName;
    this->eventType = eventType;
    this->month = month;
    this->noOfDays = noOfDays;
    this->event = event;
    
    if (this->dates != NULL) {
        delete[] this->dates;
    }

    this->dates = new int[sizeof(dates)];
    for (int i = 0; i < sizeof(dates); i++) {
        this->dates[i] = dates[i];
    }
}

// copy constructor
Calendar::Calendar(const Calendar& calendar) :calendarID(countCalendar++){
    this->calendarName = calendar.calendarName;
    this->eventType = calendar.eventType;
    this->month = calendar.month;
    this->noOfDays = calendar.noOfDays;
    this->event = calendar.event;

    if (this->dates != NULL) {
        delete[] this->dates;
    }

    this->dates = new int[sizeof(calendar.dates)];
    for (int i = 0; i < sizeof(calendar.dates); i++) {
        this->dates[i] = calendar.dates[i];
    }
}

ostream& operator <<(ostream& out, const Calendar& calendar) {
    
    out << "This calendar is called " << calendar.calendarName << "." << endl;
    out << "The type of event it tracks is" << calendar.eventType << "." << endl;
    out << "The event takes place in the month of " << calendar.month << ", across " << calendar.noOfDays << "." << endl;
    out << "The days in which the event takes place are: " << endl;
    for (int i = 1; i <= calendar.noOfDays; i++) {
        out << calendar.dates[i - 1] << ", ";
    }

    return out;
}

istream& operator >>(istream& in, Calendar& calendar){

    cout << "Enter calendar name: ";
    in >> calendar.calendarName;

    cout << "Enter event type: ";
    in >> calendar.eventType;

    cout << "Enter the month in which the event takes place: ";
    in >> calendar.month;

    cout << "How many days will the event span: ";
    in >> calendar.noOfDays;

    if (calendar.dates != NULL) {
        delete[] calendar.dates;
        calendar.dates = NULL;
    }

    calendar.dates = new int[calendar.noOfDays];

    cout << "Enter the days the event will take place: " << endl;
    for (int i = 1; i <= calendar.noOfDays; i++) {
        cout << "Day " << i << ": ";
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
        this->event = calendar.event;

        if (this->dates != NULL) {
            delete[] this->dates;
        }

        this->dates = new int[sizeof(calendar.dates)];
        for (int i = 0; i < sizeof(calendar.dates); i++) {
            this->dates[i] = calendar.dates[i];
        }
    }
    
    return *this;
}


// [] overload
// TODO debug dupa ce faci Event
int Calendar::operator[](int zi) {
    if (zi < 0 || zi >= this->noOfDays) throw runtime_error("Invalid index!");
    if (this->noOfDays == NULL) throw runtime_error("Days were not assigned!");

    return this->dates[zi];
}

// ++ prefix overload
// TODO DEBUG
Calendar& Calendar::operator++() {
    
    if (this->dates != NULL) {
        int* aux = new int[this->noOfDays];
        for (int i = 0; i < noOfDays; i++) aux[i] = this->dates[i];

        delete[] this->dates;
        this->noOfDays++;
        this->dates = new int[this->noOfDays];
        for (int i = 0; i < noOfDays; i++) this->dates[i] = aux[i];
        this->dates[this->noOfDays] = 0;
    }
    else {
        this->dates = new int(0);
    }

    return *this;
}

// ++ postfix operator
// TODO DEBUG
Calendar Calendar::operator++(int) {
    Calendar aux(*this);

    if (this->dates != NULL) {
        int* aux = new int[this->noOfDays];
        for (int i = 0; i < noOfDays; i++) aux[i] = this->dates[i];

        delete[] this->dates;
        this->noOfDays++;
        this->dates = new int[this->noOfDays];
        for (int i = 0; i < noOfDays; i++) this->dates[i] = aux[i];
        this->dates[this->noOfDays] = 0;
    }
    else {
        this->noOfDays = 1;
        this->dates = new int(0);
    }

    return aux;
}


// + overload
Calendar Calendar::operator+(int val) {
    
    Calendar aux(*this);

    if (this->dates != NULL) {
        int* aux = new int[this->noOfDays];
        for (int i = 0; i < noOfDays; i++) aux[i] = this->dates[i];

        delete[] this->dates;
        this->noOfDays++;
        this->dates = new int[this->noOfDays];
        for (int i = 0; i < noOfDays; i++) this->dates[i] = aux[i];
        this->dates[this->noOfDays] = 0;
    }
    else {
        this->noOfDays = 1;
        this->dates = new int(0);
    }


    return aux;
}



// string cast
// TODO DEBUG
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
    return this->event == calendar.event;
}

// < overload
bool Calendar::operator<(const Calendar& calendar) {
    return this->noOfDays < calendar.noOfDays;
}

// + overload  
// adding with an int will add me this amount of days
//Calendar Calendar::operator+(int x){
//    
//}
//
// - overload 
// scadere cu un int imi scoate atatea zile din calendar
//Calendar Calendar::operator-(int x) {
//
//}
//
// - comutativ
//Calendar operator-(int x, Calendar calendar) {
//
//}
//
// + comutativ
//Calendar operator+(int x, Calendar calendar) {
//
//}




































// TODO TEST
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
    Company* hostCompany;
    Company* attendingCompanies;
    EventRoom* eventRooms;
    Calendar* calendar;
    Conference* conferences;

public:

    // getters 
    const int getEventID() { return this->eventID; };
    int getExpectedAtendees() { return this->expectedAtendees; };
    int getConferenceNo() { return this->conferenceNo; };
    float getSpan() { return this->span; };
    char* getEventName() { return this->eventName; };

    Company* getHostCompany() { return this->hostCompany; };
    Company* getAttendingCompanies() { return this->attendingCompanies; };
    EventRoom* getEventRooms() { return this->eventRooms; };
    Calendar* getCalendar() { return this->calendar; };
    Conference* getConferences() { return this->conferences; };

    // setters 
    void setExpectedAtendees(int expectedAtendees) { this->expectedAtendees = expectedAtendees; };
    void setConferenceNo(int conferenceNo) { this->conferenceNo = conferenceNo; };
    void setSpan(float span) { this->span = span; };
    void setEventName(char* eventName);

    void setHostCompany(Company* hostCompany) { this->hostCompany = hostCompany; };
    void setAttendingCompanies(Company* attendingCompanies) { this->attendingCompanies = attendingCompanies; };
    void setEventRooms(EventRoom* eventRooms) { this->eventRooms = eventRooms; };
    void setCalendar(Calendar* calendar) { this->calendar = calendar; };
    void setConferences(Conference* conferences) { this->conferences = conferences; };

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
    void createEvent(Company*, Company*, EventRoom*, Calendar*, Conference*); // class function
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

    // TODO alter values
    this->hostCompany = NULL;
    this->attendingCompanies = NULL;
    this->eventRooms = NULL;
    this->calendar = NULL;
    this->conferences = NULL;
}

// partial constructor 1
Event::Event(int conferenceNo, char* eventName) :eventID(countEvent++) {
    this->expectedAtendees = 0;
    this->conferenceNo = conferenceNo;
    this->span = 0;
    this->eventName = new char[strlen(eventName) + 1];
    strcpy(this->eventName, eventName);

    // TODO alter values
    this->hostCompany = new Company[1];
    this->attendingCompanies = NULL;
    this->eventRooms = new EventRoom[50];
    this->calendar = new Calendar[1];
    this->conferences = new Conference[conferenceNo];
}

// partial constructor 2
Event::Event(char* eventName) :eventID(countEvent++) {
    this->expectedAtendees = 0;
    this->conferenceNo = 0;
    this->span = 0;
    this->eventName = new char[strlen(eventName) + 1];
    strcpy(this->eventName, eventName);

    // TODO alter values
    this->hostCompany = new Company[1];
    this->attendingCompanies = new Company[20];
    this->eventRooms = new EventRoom[50];
    this->calendar = new Calendar[1];
    this->conferences = new Conference[80];
}

// destructor
Event::~Event() {
    this->eventName = NULL;
    this->hostCompany = NULL;
    this->attendingCompanies = NULL;
    this->eventRooms = NULL;
    this->calendar = NULL;
    this->conferences = NULL;
}

// full constructor
Event::Event(int expectedAtendees, int reservedRooms, int conferenceNo, float span, char* eventName):eventID(countEvent++) {
    this->expectedAtendees = expectedAtendees;
    this->conferenceNo = conferenceNo;
    this->reservedRooms = reservedRooms;
    this->span = span;
    this->eventName = new char[strlen(eventName) + 1];
    strcpy(this->eventName, eventName);

    this->hostCompany = new Company;
    this->attendingCompanies = new Company[expectedAtendees];
    this->eventRooms = new EventRoom[reservedRooms];
    this->calendar = new Calendar;
    this->conferences = new Conference[conferenceNo];
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

    this->hostCompany = new Company;
    this->attendingCompanies = new Company[event.expectedAtendees];
    this->eventRooms = new EventRoom[event.reservedRooms];
    this->calendar = new Calendar;
    this->conferences = new Conference[event.conferenceNo];

    this->hostCompany = event.hostCompany;
    this->attendingCompanies = event.attendingCompanies;
    this->eventRooms = event.eventRooms;
    this->calendar = event.calendar;
    this->conferences = event.conferences;
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
        this->eventRooms = event.eventRooms;
        this->calendar = event.calendar;
        this->conferences = event.conferences;
    }
    return *this;
}

// overload input
istream& operator>>(istream& in, Event& event) {
    cout << "How many attendants do you expect: ";
    in >> event.expectedAtendees;

    cout << "How many conferences do you want to host: ";
    in >> event.conferenceNo;

    cout << "How long do you expect to hold your event: ";
    in >> event.span;

    if (event.eventName != NULL) {
        delete[] event.eventName;
        event.eventName = NULL;
    }

    char aux[50];
    cout << "What is the event name: ";
    in >> aux;
    event.eventName = new char[strlen(aux) + 1];
    strcpy(event.eventName, aux);

    cout << endl;
    return in;
}

// overload output
ostream& operator<<(ostream& out, const Event& event) {
    out << "This event is expected to have " << event.expectedAtendees << " attendants." << endl;
    out << "This event will have a numer of " << event.conferenceNo << " conferences." << endl;
    out << "The event is expected to last a number of " << event.span << " days." << endl;
    out << "The event is called " << event.eventName << "." << endl;
    out << "The event is hosted by " << event.hostCompany->getCompanyName() << "." << endl;

    return out;
}



// string cast
Event::operator string() {

    if (this->eventName == "New Event") {
        return "There is no event name assigned yet!";
    }
    else if (this->hostCompany == NULL) {
        return "There is no host company assigned yet!";
    }
    else if (this->conferenceNo == 0) {
        return "There are no conferences assigned yet!";
    }
    else {
        string aux = "This event is called ";
        string aux2(this->eventName);
        aux += aux2 + " ";
        aux += "and is brought to you by ";
        aux += this->hostCompany->getCompanyName() + ".\n";
        aux += "It will consist of " + to_string(this->conferenceNo) + " conferences called: \n";
        for (int i = 0; i < conferenceNo; i++) {
            aux += to_string(i+1) + ". " + this->conferences[i].getConferenceTitle() + '\n';
        }
        return aux;
    }
}

// index overload
Conference& Event::operator[](int x) {

    if (this->conferences == NULL) {
        throw runtime_error("No conferences assigned to this event!");
    }
    if (x < 0 || x >= this->conferenceNo) {
        throw runtime_error("Invalid index!");
    }

    return this->conferences[x];
}

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

// class function
void Event::createEvent(Company* hostCompany, Company* companies, EventRoom* eventRooms, Calendar* calendar, Conference* conferences) {
    this->hostCompany = hostCompany;
    this->attendingCompanies = companies;
    this->eventRooms = eventRooms;
    this->calendar = calendar;
    this->conferences = conferences;

}

// < operator
bool Event::operator<(const Event& event) {
    return this->conferenceNo < event.conferenceNo;
}

// Event + Conference
Event Event::operator+(const Conference& conference) {
    Event ans(*this);

    for (int i = 0; i < this->conferenceNo; i++) {
        if (this->conferences[i] == conference) {
            throw runtime_error("This conference is already in this event!");
        }
    }
    Conference* aux = new Conference[this->conferenceNo];
    for (int i = 0; i < this->conferenceNo; i++) {
        aux[i] = this->conferences[i];
    }
    ans.conferences = new Conference[++ans.conferenceNo];
    for (int i = 0; i < ans.conferenceNo - 1; i++) {
        ans.conferences[i] = aux[i];
    }
    ans.conferences[ans.conferenceNo - 1] = conference;

    return ans;
}

// Event - Conference
Event Event::operator-(const Conference& conference) {
    Event ans(*this);
    Conference* aux = new Conference[this->conferenceNo - 1];
    int ptr = 0;
    int ok = 0;

    for (int i = 0; i < this->conferenceNo; i++) {
        if (this->conferences[i] == conference) {
            ok = 1;
            break;
        }
    }
    if (ok) {
        
        for (int i = 0; i < this->conferenceNo; i++) {
            if (this->conferences[i] == conference) {
                continue;
            }
            else {
                aux[ptr++] = this->conferences[i];
            }
        }
        ans.conferences = new Conference[--ans.conferenceNo];
        for (int i = 0; i < ans.conferenceNo - 1; i++) {
            ans.conferences[i] = aux[i];
        }

        return ans;
    }
    else {
        throw runtime_error("This conference does not exist in the event!");
    }
}

// Conference + Event
Event operator+(Conference conference, Event event) {
    Event ans(event);

    for (int i = 0; i < event.conferenceNo; i++) {
        if (event.conferences[i] == conference) {
            throw runtime_error("This conference is already in this event!");
        }
    }
    Conference* aux = new Conference[event.conferenceNo];
    for (int i = 0; i < event.conferenceNo; i++) {
        aux[i] = event.conferences[i];
    }
    ans.conferences = new Conference[++ans.conferenceNo];
    for (int i = 0; i < ans.conferenceNo - 1; i++) {
        ans.conferences[i] = aux[i];
    }
    ans.conferences[ans.conferenceNo - 1] = conference;

    return ans;
}

// Conference - Event
Event operator-(Conference conference, Event event) {
    Event ans(event);

    Conference* aux = new Conference[event.conferenceNo - 1];
    int ptr = 0;
    int ok = 0;

    for (int i = 0; i < event.conferenceNo; i++) {
        if (event.conferences[i] == conference) {
            ok = 1;
            break;
        }
    }
    if (ok) {
        for (int i = 0; i < event.conferenceNo; i++) {
            if (event.conferences[i] == conference) {
                continue;
            }
            else {
                aux[ptr++] = event.conferences[i];
            }
        }
        ans.conferences = new Conference[--ans.conferenceNo];
        for (int i = 0; i < ans.conferenceNo; i++) {
            ans.conferences[i] = aux[i];
        }

        return ans;
    }
    else {
        throw runtime_error("This conference does not exist in the event!");
    }
}

// + overload  
Event Event::operator+(const Event& event) {
    Event ans(*this);
    Conference* aux = new Conference[this->conferenceNo + event.conferenceNo];

    for (int i = 0; i < this->conferenceNo; i++) {
        aux[i] = this->conferences[i];
    }
    for (int i = this->conferenceNo; i < this->conferenceNo + event.conferenceNo; i++) {
        aux[i] = event.conferences[i - this->conferenceNo];
    }
    ans.conferenceNo += event.conferenceNo;
    ans.conferences = aux;

    return ans;
}

// - overload 
Event Event::operator-(const Event& event) {
    Event ans(*this);

    for (int i = 0; i < event.conferenceNo; i++) {
        ans = (ans - event.conferences[i]);
    }
    return ans;
}



































int main() {

    // (bool hosting, string companyName, int representativeNo, vector <string> representatives)
    Company c1(true,"Armada",3,{"Daniel","Petru","Alexandru"});
    Company c2(true,"QuikSolv",2,{"Dana","Damian"});
    Company c3(true,"TerBonna",5,{"Cristian","Eduard","Flavia", "Fabiana", "Emma"});
    //cout << c1 << c2 << c3;

    // la conference string cast nu are sens!
    
    // int expectedAtendees, float duration, string conferenceTitle, Company* hostingCompany, int hostNo, vector <string> hostNames)
    Conference co1(25,3.5,"Programare etica",&c3,2,{"Cristian", "Fabiana"});
    Conference co2(40, 2, "E-Government", &c2, 2, {"Dana", "Damian"});
    Conference co3(25,3.5,"Programare etica",&c3,2,{"Eduard", "Emma"});
    Conference co4(50, 4, "Programare functionala", &c1, 2, { "Daniel", "Alexandru" });

    EventRoom er1("Skip Room", 200, 'A', 3, {"Aer conditionat", "Dozatoare", "Fierbator de apa"});
    EventRoom er2("Electrify Room", 180, 'B', 3, {"Aer conditionat", "Dozatoare", "Fierbator de apa"});
    EventRoom er3("Darwin Solenza Room", 320, 'D', 4, {"Aer conditionat", "Dozatoare", "Fierbator de apa", "Extinctor"});

    char* aux = new char[strlen("Etica in programare si introducere in E-Government") + 1];
    strcpy(aux, "Etica in programare si introducere in E-Government");

    Event e1(500,3,3,13.5,aux);
    Company* cl = new Company[3];
    cl[0] = c1; 
    cl[1] = c2; 
    cl[2] = c3;
    EventRoom* erl = new EventRoom[3];
    erl[0] = er1;
    erl[1] = er2;
    erl[2] = er3;
    Conference* col = new Conference[3];
    col[0] = co1;
    col[1] = co2;
    col[2] = co3;
    e1.createEvent(&c3,cl,erl,NULL,col);

    Event e2;
    e2 = e1;
    cout << (string)(e1 + e2);
    cout << (string)e2;
    cout << (string)e1;

    co1.setHostingCompany(nullptr);
    cout << (string)co1;
    
    Event e3;
    //cout << (string)e3;
    

    cout << "Compileaza. GG." << endl;
    return 0;

    //e1.createEvent(&c3,{&c1,&c2,&c3},{&er1,&er2,&er3},NULL,{&co1,&co2,&co3});

    /*cout << er1;
    cout << er2;
    cout << 330 - er3;*/

    /*cout << co1;
    co1 = co1 + "Ioana";
    cout << co1;
    co1 = co1 - "Cristian";
    cout << co1;*/

    /*cout << co2;
    co2 = "Iulian" + co2;
    cout << co2;
    co2 = "Dana" - co2;
    cout << co2;*/
    //cout << (co1 + co3);


    


    /*Conference c1, c2;
    Event e1;
    e1 = e1 + c1;
    cout << e1;*/

    //cout << "Welcome to event planner v0.31rc4" << endl;
    //cout << "At any time you can quit by typing (quit)." << endl;
    //cout << "The instruction to be used is written between round braces, as in the following example: (your_command_here)." << endl << endl;

    //cout << "Please enter one of the following instructions to begin: " << endl;
    //cout << "1. Create event (create_event);" << endl;
    //cout << "2. Create company (create_company);" << endl;
    //cout << "3. Create event room (create_eventroom);" << endl;
    //cout << "4. Create conference (create_conference);" << endl;
    //cout << "5. Create calendar (create_calendar);" << endl;
    //cout << "6. Continue to data printing (continue)" << endl;
    //string input = "";

    //// TODO cum aloc dinamic crearea de clase?
    //Event* Events = new Event[10];
    //Company* Companies = new Company[10];
    //EventRoom* EventRooms = new EventRoom[10];
    //Conference* Conferences = new Conference[10];
    //Calendar* Calendars = new Calendar[10];

    //cin >> input;
    //std::transform(input.begin(), input.end(), input.begin(), ::tolower);
    //while (input != "quit") {
    //    
    //    if (input == "create") {
    //        while (input != "continue") {
    //            // TODO o fi bine sa am valori constante aici?
    //            if (input == "create_event") {
    //                const int ptr = Events->getEventID();
    //                cin >> Events[ptr - 10];
    //            }
    //            else if (input == "create_company") {
    //                const int ptr = Companies->getCompanyID();
    //                cin >> Companies[ptr - 100];
    //            }
    //            else if (input == "create_eventroom") {
    //                const int ptr = EventRooms->getRoomNo();
    //                cin >> EventRooms[ptr - 200];
    //            }
    //            else if (input == "create_conference") {
    //                const int ptr = Conferences->getConferenceID();
    //                cin >> Conferences[ptr - 1000];
    //            }
    //            else if (input == "create_calendar") {
    //                const int ptr = Calendars->getCalendarID();
    //                cin >> Calendars[ptr - 10000];
    //            }
    //        }
    //    }
    //    else if (input == "read") {
    //        while (input != "continue") {
    //            input = "";

    //            cout << "Next, you can " << endl << endl;

    //            cout << "Please enter one of the following instructions to begin: " << endl;
    //            cout << "1. Create event (create_event);" << endl;
    //            cout << "2. Create company (create_company);" << endl;
    //            cout << "3. Create event room (create_eventroom);" << endl;
    //            cout << "4. Create conference (create_conference);" << endl;
    //            cout << "5. Create calendar (create_calendar);" << endl;
    //            cout << "6. Continue to data printing (continue)" << endl;

    //            while (input != "continue") {
    //                cout << "hello!";

    //                cin >> input;
    //                std::transform(input.begin(), input.end(), input.begin(), ::tolower);
    //            }
    //        }
    //    }
    //    else if (input == "update") {
    //        while (input != "continue") {

    //        }
    //    }
    //    else if (input == "delete") {
    //        while (input != "continue") {

    //        }
    //    }
    //    else {
    //        cout << "Unknown command! Please try again!" << endl;
    //    }

    //    cin >> input;
    //    std::transform(input.begin(), input.end(), input.begin(), ::tolower);
    //}
    //
    //cout << "Thank you for using our app!" << endl;

    
}


// li-l dam pe tot
// li- le dam tot codul
// sa se spele cu el pe cap
// nici noi nu mai intelegem ce dracu am scris in codul ala