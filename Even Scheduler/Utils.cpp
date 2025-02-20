// Utils.cpp
#include "Utils.hpp"
#include <cstdlib>

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

bool isValidDate(const std::string& date) {
    if (date.length() != 10 || date[4] != '-' || date[7] != '-') return false;
    return true;
}

bool isValidTime(const std::string& time) {
    if (time.length() != 5 || time[2] != ':') return false;
    return true;
}

Date parseDate(const std::string& dateStr) {
    Date d;
    d.year = std::atoi(dateStr.substr(0, 4).c_str());
    d.month = std::atoi(dateStr.substr(5, 2).c_str());
    d.day = std::atoi(dateStr.substr(8, 2).c_str());
    return d;
}

bool compareDates(const std::string& date1, const std::string& date2) {
    Date d1 = parseDate(date1);
    Date d2 = parseDate(date2);
    if (d1.year != d2.year) return d1.year < d2.year;
    if (d1.month != d2.month) return d1.month < d2.month;
    return d1.day < d2.day;
}

bool compareNames(const std::string& name1, const std::string& name2) {
    return name1 <= name2;
}