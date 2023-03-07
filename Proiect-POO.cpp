//CORPORATE EVENT MANAGER - PROJECT WRITTEN BY ALEXANDRU MICLEA
//FMI UNIBUC 2023

#include <iostream>
#include <string>
using namespace std;

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
    static int getCountEvent() {return Event::countEvent;};
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


//class Company {
//private:
//
//    const int companyID;
//    static int countID;
//
//    bool hosting;
//    string companyName;
//    int representativeNo;
//    string* representatives;
//public:
//
//};
//
//class EventRoom {
//private:
//
//    static int noOfConferences;
//
//    string roomName;
//    int seatNo;
//    char pavilion;
//    string* facilities;
//
//
//public:
//
//};
//
//class Conference {
//private:
//
//    const int conferenceID;
//    static int countConference;
//
//    int expectedAtendees;
//    float duration;
//    string conferenceTitle;
//    string hostingCompany;
//    int hostNo;
//    string* hostNames;
//
//public:
//
//    
//
//};
//
//class Calendar {
//private:
//
//    //aici folosesti float
//    // si int*
//public:
//
//};


int main() {

    
}