// Event.hpp
#ifndef EVENT_HPP
#define EVENT_HPP

#include <string>

class Event {
private:
    std::string eventID;
    std::string name;
    std::string date;
    std::string time;
    std::string organizer;
    bool isApproved;

public:
    Event();
    Event(std::string id, std::string n, std::string d, std::string t, std::string org, bool approved = false);
    

    std::string getEventID() const { return eventID; }
    std::string getName() const { return name; }
    std::string getDate() const { return date; }
    std::string getTime() const { return time; }
    std::string getOrganizer() const { return organizer; }
    bool getIsApproved() const { return isApproved; }

    void setName(const std::string& n) { name = n; }
    void setDate(const std::string& d) { date = d; }
    void setTime(const std::string& t) { time = t; }
    void setOrganizer(const std::string& org) { organizer = org; }
    void setApproved(bool approved) { isApproved = approved; }
};

#endif