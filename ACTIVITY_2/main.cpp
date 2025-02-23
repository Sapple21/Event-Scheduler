// main.cpp
#include "EventManager.hpp"
#include "HardcodedEvents.hpp"
#include "Utils.hpp"
#include <iostream>
#include <string>

int main() {
    EventManager manager;
    manager.loadEventsFromFile();
    createHardcodedEvents(manager);
    std::string choice;
    while (true) {
        manager.displayMenu();
        std::getline(std::cin, choice);

        if (choice.length() > 1 || choice.empty()) {
            std::cout << "ERROR: Invalid choice! Please enter a number between 1 and 9.\n";
            std::cout << "Press Enter to continue...";
            std::string input;
            std::getline(std::cin, input);
            continue;
        }

        switch (choice[0]) {
            
            case '1':
                manager.displayEvents();
                std::cout << "Press Enter to continue...";
                {
                    std::string input;
                    std::getline(std::cin, input);
                }
                break;

            case '2':
                manager.sortByDate();
                break;

            case '3':
                manager.sortByName();
                break;

            case '4':
                manager.searchEventByID();
                break;

            case '5':
                manager.approveEvent();
                break;

            case '6':
                manager.editEventByID();
                break;

            case '7':
                manager.deleteEventByID();
                break;

            case '8':
                clearScreen();
                std::cout << "\n+=======================================+\n"
                          << "| Exiting Event Scheduling System...    |\n"
                          << "| Goodbye!                              |\n"
                          << "+=======================================+\n";
                return 0;

            default:
                std::cout << "ERROR: Invalid choice! Please enter a number between 1 and 9.\n";
                std::cout << "Press Enter to continue...";
                {
                    std::string input;
                    std::getline(std::cin, input);
                }
                break;
        }
    }
    
    return 0;
}