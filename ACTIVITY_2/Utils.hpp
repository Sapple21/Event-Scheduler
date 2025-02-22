// Utils.hpp
#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>

void clearScreen();
bool isValidDate(const std::string& date);
bool isValidTime(const std::string& time);
bool compareDates(const std::string& date1, const std::string& date2);
bool compareNames(const std::string& name1, const std::string& name2);

struct Date {
    int year, month, day;
};

Date parseDate(const std::string& dateStr);

#endif