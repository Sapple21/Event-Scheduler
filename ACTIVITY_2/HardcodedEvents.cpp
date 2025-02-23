#include "EventManager.hpp"
#include "Event.hpp"
#include <iostream>

void createHardcodedEvents(EventManager& manager) {
    manager.scheduleEvent("E001", "ACM GENERAL ASSEMBLY", "2025-03-25", "13:00", "ACM", false);
    manager.scheduleEvent("E003", "AITS GENERAL ASSEMBLY", "2025-02-28", "13:30", "AITS", false);
    manager.scheduleEvent("E008", "MIDTERM EXAM", "2025-03-14", "13:40", "HADJI TEJUCO", false);
    manager.scheduleEvent("E009", "TOMOHEROES 2024", "2025-05-01", "10:00", "SCC", false);
    manager.scheduleEvent("E010", "AI FUNDAMENTALS SEMINAR", "2025-04-05", "15:00", "ACM", false);
    manager.scheduleEvent("E011", "CYBERSECURITY BASICS WORKSHOP", "2025-03-18", "09:00", "AITS", false);
    manager.scheduleEvent("E012", "CIVIL ENGINEERING SUMMIT", "2025-05-10", "08:30", "ACES", false);
    manager.scheduleEvent("E013", "TECHNOPRENEURSHIP STARTUP TALKS", "2025-04-02", "13:00", "ASTI", false);
    manager.scheduleEvent("E014", "GAME DEVELOPMENT BOOTCAMP", "2025-03-22", "14:00", "TEAMS", false);
    manager.scheduleEvent("E015", "MACHINE LEARNING HACKATHON", "2025-04-15", "16:00", "ACM", false);
    manager.scheduleEvent("E016", "NETWORK SECURITY CONFERENCE", "2025-05-20", "10:00", "AITS", false);
    manager.scheduleEvent("E017", "STRUCTURAL ENGINEERING WORKSHOP", "2025-04-22", "14:30", "ACES", false);
    manager.scheduleEvent("E018", "INNOVATIVE BUSINESS STRATEGIES", "2025-03-10", "13:00", "ASTI", false);
    manager.scheduleEvent("E019", "DIGITAL DESIGN MASTERCLASS", "2025-05-05", "09:30", "TEAMS", false);
    manager.scheduleEvent("E020", "MECHANICAL SYSTEMS SEMINAR", "2025-04-10", "15:00", "MECHS", false);
    manager.scheduleEvent("E021", "COMPETITIVE GAMING STRATEGIES", "2025-05-02", "12:00", "TEC", false);
    manager.scheduleEvent("E022", "STUDENT LEADERSHIP FORUM", "2025-03-30", "14:00", "SCC", false);
    manager.scheduleEvent("E023", "FRESHMEN ORIENTATION", "2025-04-18", "10:00", "FSOC", false);
    manager.scheduleEvent("E024", "POWER SYSTEMS ENGINEERING", "2025-03-27", "13:30", "ECESS", false);
    manager.scheduleEvent("E025", "SOFTWARE DEVELOPMENT SUMMIT", "2025-04-08", "09:00", "ACM", false);
    manager.scheduleEvent("E026", "CLOUD COMPUTING WORKSHOP", "2025-05-15", "14:00", "AITS", false);
    manager.scheduleEvent("E027", "CONSTRUCTION TECHNOLOGIES", "2025-03-05", "10:00", "ACES", false);
    manager.scheduleEvent("E028", "STARTUP PITCHING COMPETITION", "2025-05-25", "13:00", "ASTI", false);
    manager.scheduleEvent("E029", "ANIMATION DESIGN WORKSHOP", "2025-04-12", "11:00", "TEAMS", false);
    manager.scheduleEvent("E030", "ADVANCED ROBOTICS SEMINAR", "2025-03-15", "14:30", "MECHS", false);
    manager.scheduleEvent("E031", "ESPORTS MANAGEMENT TRAINING", "2025-04-25", "09:30", "TEC", false);
    manager.scheduleEvent("E032", "STUDENT GOVERNANCE WORKSHOP", "2025-03-20", "16:00", "SCC", false);
    manager.scheduleEvent("E033", "AI IN BUSINESS FORUM", "2025-05-18", "12:30", "ASTI", false);
    manager.scheduleEvent("E034", "ELECTRICAL CIRCUIT DESIGN", "2025-03-22", "13:00", "ECESS", false);
}