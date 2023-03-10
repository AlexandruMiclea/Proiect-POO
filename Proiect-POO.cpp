//CORPORATE EVENT MANAGER - PROJECT WRITTEN BY ALEXANDRU MICLEA
//FMI UNIBUC 2023

#include <iostream>
#include <string>
#include <vector>
using namespace std;

#pragma warning (disable : 4996)

// Event class

class Event {
private:

    const int eventID;
    static int countEvent;

    int expectedAtendees;
    int conferenceNo;
    float span;
    char* eventName;
    string hostName;

public:

    // getters 
    const int getEventID() {return this->eventID;};
    int getExpectedAtendees() {return this->expectedAtendees;};
    int getConferenceNo() {return this->conferenceNo;};
    float getSpan() {return this->span;};
    string getHostName() {return this->hostName;};
    char* getEventName() {return this->eventName;};

    // setters 
    void setExpectedAtendees(int expectedAtendees) {this->expectedAtendees = expectedAtendees;};
    void setConferenceNo(int conferenceNo) {this->conferenceNo = conferenceNo;};
    void setSpan(float span) {this->span = span;};
    void setEventName(char* eventName);
    void setHostName(string hostName) { this->hostName = hostName;};

    Event(); // empty constructor
    ~Event(); // destructor
    Event(int expectedAtendees, int conferenceNo, float span, char* eventName, string hostName); // full constructor
    Event(const Event& event); // copy constructor
    friend ostream& operator <<(ostream& out, const Event& event); // output operator overload
    friend istream& operator >>(istream& in, Event& event); // input operator overload
    Event& operator=(const Event& event); // = overload
};

int Event::countEvent = 10;

// setEventName definition
void Event::setEventName(char* eventName) {
    if (this->eventName != NULL) {
        delete[] this->eventName;
        this->eventName = NULL;
    }

    this->eventName = new char[strlen(eventName)+1];
    strcpy(this->eventName, eventName);
}

// constructor definition
Event::Event():eventID(countEvent++){
    this->expectedAtendees = 0;
    this->conferenceNo = 0;
    this->span = 0;
    this->eventName = new char[strlen("New Event") + 1];
    strcpy(this->eventName, "New Event");
    this->hostName = "Unassigned Host";
}

// destructor
Event::~Event() {
    if (this->eventName != NULL) {
        delete[] this->eventName;
        this->eventName = NULL;
    }
}

// full constructor
Event::Event(int expectedAtendees, int conferenceNo, float span, char* eventName, string hostName):eventID(countEvent++) {
    this->expectedAtendees = expectedAtendees;
    this->conferenceNo = conferenceNo;
    this->span = span;
    this->eventName = new char[strlen(eventName) + 1];
    strcpy(this->eventName, eventName);
    this->hostName = hostName;
}

// copy constructor
Event::Event(const Event& event):eventID(countEvent++) {
    this->expectedAtendees = event.expectedAtendees;
    this->conferenceNo = event.conferenceNo;
    this->span = event.span;
    this->eventName = new char[strlen(event.eventName) + 1];
    strcpy(this->eventName, event.eventName);
    this->hostName = event.hostName;
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
        this->span = event.span;
        this->eventName = new char[strlen(event.eventName) + 1];
        strcpy(this->eventName, event.eventName);
        this->hostName = event.hostName;

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

    cout << "What is the host's name: ";
    in >> event.hostName;

    cout << endl;
    return in;
}

// overload output
ostream& operator<<(ostream& out, const Event& event) {
    out << "This event is expected to have " << event.expectedAtendees << " attendants." << endl;
    out << "This event will have a numer of " << event.countEvent << " events." << endl;
    out << "The event is expected to last a number of " << event.span << " days." << endl;
    out << "The event is called " << event.eventName << "." << endl;
    out << "The event is hosted by " << event.hostName << "." << endl;

    out << endl;
    return out;
}

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
    bool getHosting() {return this->hosting;};
    string getCompanyName() {return this->companyName;};
    int getRepresentantiveNo() { return this->representativeNo; };
    vector <string> getRepresentatives() { return this->representatives;};

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

};

int Company::countID = 100;

Company::Company():companyID(countID++) {
    this->hosting = false;
    this->companyName = "New Company";
    this->representativeNo = 0;
    this->representatives.push_back("Representative Name");
}

Company::~Company(){
    // destructor, need to find a use for it
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
        out << i << ". " << company.representatives[i-1] << endl;
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
    // TODO see if getRoomNo can be accessed
    void setRoomName(string roomName) { this->roomName = roomName; };
    void setSeatNo(int seatNo) { this->seatNo = seatNo; };
    void setPavilion(char pavilion) { this->pavilion = pavilion; };
    void setNoOfFacilities(int noOfFacilities) { this->noOfFacilities = noOfFacilities; };
    void setFacilities(vector <string> facilities) { this->facilities = facilities;};

    EventRoom(); // empty constructor
    ~EventRoom(); // destructor
    EventRoom(string roomName, int seatNo, char pavilion, int noOfFacilities, vector <string> facilities); // full constructor
    EventRoom(const EventRoom& event); // copy constructor
    friend ostream& operator <<(ostream& out, const EventRoom& eventRoom); // output operator overload
    friend istream& operator >>(istream& in, EventRoom& eventRoom); // input operator overload
    EventRoom& operator=(const EventRoom& eventRoom); // = overload

};

int EventRoom::roomCnt = 200;

EventRoom::EventRoom():roomNo(roomCnt++){
    this->roomName = "New Room";
    this->seatNo = 0;
    this->pavilion = 'X';
    this->noOfFacilities = 0;
    this->facilities.push_back("");
        
}
//~EventRoom(); // destructor

EventRoom::EventRoom(string roomName, int seatNo, char pavilion, int noOfFacilities, vector <string> facilities) :roomNo(roomCnt++) {
    this->roomName = roomName;
    this->seatNo = seatNo;
    this->pavilion = pavilion;
    this->noOfFacilities = noOfFacilities;
    this->facilities = facilities;
}
EventRoom::EventRoom(const EventRoom& eventRoom) :roomNo(roomCnt++) {
    this->roomName = eventRoom.roomName;
    this->seatNo = eventRoom.seatNo;
    this->pavilion = eventRoom.pavilion;
    this->noOfFacilities = eventRoom.noOfFacilities;
    this->facilities = eventRoom.facilities;
}
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

istream& operator >>(istream& in, EventRoom& eventRoom) {

    

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


class Conference {
private:

    const int conferenceID;
    static int countConference;

    int expectedAtendees;
    float duration;
    string conferenceTitle;
    string hostingCompany;
    int hostNo;
    vector <string> hostNames;

public:


    // getters 
    const int getConferenceID() { return this->conferenceID; };
    int getExpectedAtendees() { return this->expectedAtendees; };
    float getDuration() { return this->duration; };
    string getConferenceTitle() { return this->conferenceTitle; };
    string getHostingCompany() { return this->hostingCompany; };
    int getHostNo() { return this->hostNo; };
    vector <string> getHostNames() { return this->hostNames; };

    // setters 
    void setExpectedAtendees() { this->expectedAtendees = expectedAtendees; };
    void setDuration() { this->duration = duration; };
    void setConferenceTitle() { this->conferenceTitle = conferenceTitle; };
    void setHostingCompany() { this->hostingCompany = hostingCompany; };
    void setHostNo() { this->hostNo = hostNo; };
    void setHostNames() { this->hostNames = hostNames; };

    Conference(); // empty constructor
    ~Conference(); // destructor
    Conference(int expectedAtendees, float duration, string conferenceTitle, string hostingCompany, int hostNo, vector <string> hostNames); // full constructor
    Conference(const Conference& conference); // copy constructor
    friend ostream& operator <<(ostream& out, const Conference& conference); // output operator overload
    friend istream& operator >>(istream& in, Conference& conference); // input operator overload
    Conference& operator=(const Conference& conference); // = overload

};

//Conference(); // empty constructor
//~Conference(); // destructor
//Conference(int expectedAtendees, float duration, string conferenceTitle, string hostingCompany, int hostNo, vector <string> hostNames); // full constructor
//Conference(const Conference& conference); // copy constructor
//friend ostream& operator <<(ostream& out, const Conference& conference); // output operator overload
//friend istream& operator >>(istream& in, Conference& conference); // input operator overload
//Conference& operator=(const Conference& conference); // = overload

// ABOVE THIS LINE IS OK

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
    void setCalendarName() { this->calendarName; };
    void setEventTypee() { this->eventType; };
    void setMonth() { this->month; };
    void setnoOfDays() { this->noOfDays; };
    void setDates(); // TODO implement this

    Calendar(); // empty constructor
    ~Calendar(); // destructor
    Calendar(string calendarName, string eventType, string month, int noOfDays, int* dates); // full constructor
    Calendar(const Calendar& calendar); // copy constructor
    friend ostream& operator <<(ostream& out, const Calendar& calendar); // output operator overload
    friend istream& operator >>(istream& in, Calendar& calendar); // input operator overload
    Calendar& operator=(const Calendar& calendar); // = overload
};

//Calendar(); // empty constructor
//~Calendar(); // destructor
//Calendar(string calendarName, string eventType, string month, int noOfDays, int* dates); // full constructor
//Calendar(const Calendar& calendar); // copy constructor
//friend ostream& operator <<(ostream& out, const Calendar& calendar); // output operator overload
//friend istream& operator >>(istream& in, Calendar& calendar); // input operator overload
//Calendar& operator=(const Calendar& calendar); // = overload

int main() {

    /*Event a1;
    cout << a1.getConferenceNo();
    cout << a1.getEventID();
    cout << a1.getEventName();

    char nume[] = "Dansul lambada in 5 pasi simpli.";

    Event a2(5,3,2.5,nume,"Ana danseaza lambada");
    cout << a2.getEventName() << endl;
    cout << a2.getHostName() << endl;

    Event a3(a2), a4 = a2;

    cout << a3.getEventName() << endl << endl;
    cout << a4.getHostName() << endl;

    cin >> a3;
    cout << a3;*/

    Company c1;
    cout << c1.getCompanyName();

    vector <string> aux;
    aux.push_back("Copac");
    aux.push_back("Masina Zdrobita");
    aux.push_back("Securist ramas prin zona (se asigura ca moare ceo-ul).");

    Company c2(true, "HexiPharma",3,aux);
    cout << c2;

    return 0;
}