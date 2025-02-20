#include "Event.hpp"

Event::Event() : eventID(""), name(""), date(""), time(""), organizer(""), isApproved(false) {}

Event::Event(std::string id, std::string n, std::string d, std::string t, std::string org, bool approved)
    : eventID(id), name(n), date(d), time(t), organizer(org), isApproved(approved) {}