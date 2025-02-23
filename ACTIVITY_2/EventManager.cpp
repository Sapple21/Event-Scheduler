// EventManager.cpp
#include "EventManager.hpp"
#include "Utils.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>

EventManager::EventManager() : head(nullptr), eventCount(0) {}

EventManager::~EventManager() {
    Node* current = head;
    while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
    }
}

Node* EventManager::getMiddle(Node* currentHead) {
    Node* slow = currentHead;
    Node* fast = currentHead->next;
    
    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

Node* EventManager::merge(Node* left, Node* right) {
    if (!left) return right;
    if (!right) return left;
    
    Node* result = nullptr;
    if (compareDates(left->event.getDate(), right->event.getDate())) {
        result = left;
        result->next = merge(left->next, right);
    } else {
        result = right;
        result->next = merge(left, right->next);
    }
    return result;
}

void EventManager::mergeSort(Node*& headRef) {
    if (!headRef || !headRef->next) return;
    
    Node* mid = getMiddle(headRef);
    Node* nextToMid = mid->next;
    mid->next = nullptr;
    
    mergeSort(headRef);
    mergeSort(nextToMid);
    headRef = merge(headRef, nextToMid);
}

Node* EventManager::getTail(Node* cur) {
    while (cur != nullptr && cur->next != nullptr)
        cur = cur->next;
    return cur;
}

Node* EventManager::partition(Node* pivotNode, Node*& newHead, Node*& newEnd) {
    Node* pivot = pivotNode;
    Node* prev = nullptr;
    Node* cur = pivotNode;
    Node* tail = pivot;
    
    while (cur != nullptr) {
        if (compareNames(cur->event.getName(), pivot->event.getName())) {
            if (newHead == nullptr)
                newHead = cur;
            prev = cur;
            cur = cur->next;
        } else {
            if (prev)
                prev->next = cur->next;
            Node* tmp = cur->next;
            cur->next = nullptr;
            tail->next = cur;
            tail = cur;
            cur = tmp;
        }
    }
    
    if (newHead == nullptr)
        newHead = pivot;
    newEnd = tail;
    return pivot;
}

Node* EventManager::quickSortRec(Node* currentHead, Node* end) {
    if (!currentHead || currentHead == end) return currentHead;
    
    Node* newHead = nullptr;
    Node* newEnd = nullptr;
    
    Node* pivot = partition(currentHead, newHead, newEnd);
    
    if (newHead != pivot) {
        Node* tmp = newHead;
        while (tmp->next != pivot)
            tmp = tmp->next;
        tmp->next = nullptr;
        
        newHead = quickSortRec(newHead, tmp);
        
        tmp = getTail(newHead);
        tmp->next = pivot;
    }
    
    pivot->next = quickSortRec(pivot->next, newEnd);
    return newHead;
}

void EventManager::quickSort(Node*& headRef) {
    headRef = quickSortRec(headRef, getTail(headRef));
}

Node* EventManager::findNode(const std::string& eventID) {
    Node* current = head;
    while (current != nullptr) {
        if (current->event.getEventID() == eventID)
            return current;
        current = current->next;
    }
    return nullptr;
}

void EventManager::logEvent(const std::string& action, const Event& e) {
    std::ofstream logFile("event_log.txt", std::ios::app);
    if (!logFile) {
        std::cout << "Error opening log file!" << std::endl;
        return;
    }
    time_t now = time(0);
    std::string timestamp = ctime(&now);
    if (!timestamp.empty()) timestamp = timestamp.substr(0, timestamp.length() - 1);
    logFile << "[" << timestamp << "] " << action << ": " << e.getEventID() << ", "
            << e.getName() << ", " << e.getDate() << ", " << e.getTime() << ", " << e.getOrganizer()
            << ", " << (e.getIsApproved() ? "Approved" : "Pending") << std::endl;
    logFile.close();
}

int EventManager::loadEventsFromFile() {
    std::ifstream logFile("event_log.txt");
    if (!logFile) {
        std::cout << "No log file found. Starting fresh." << std::endl;
        return 0;
    }

    std::string line;
    while (std::getline(logFile, line)) {
        if (line.find("Added:") != std::string::npos) {
            std::string data = line.substr(line.find("Added:") + 7);
            std::stringstream ss(data);
            std::string token;

            std::getline(ss, token, ','); token = token.substr(token.find_first_not_of(" \t"));
            std::string eventID = token;

            std::getline(ss, token, ','); token = token.substr(token.find_first_not_of(" \t"));
            std::string name = token;

            std::getline(ss, token, ','); token = token.substr(token.find_first_not_of(" \t"));
            std::string date = token;

            std::getline(ss, token, ','); token = token.substr(token.find_first_not_of(" \t"));
            std::string time = token;

            std::getline(ss, token, ','); token = token.substr(token.find_first_not_of(" \t"));
            std::string organizer = token;

            std::getline(ss, token, ','); 
            token = token.substr(token.find_first_not_of(" \t")); 
            token = token.substr(0, token.find_last_not_of(" \t\n") + 1); 
            bool isApproved = (token == "Approved"); 

            std::cout << "Loading event " << eventID << " | Status token: '" << token << "' | isApproved: " << isApproved << std::endl;

            if (!isValidDate(date) || !isValidTime(time)) {
                std::cout << "Warning: Invalid date/time format in log for event " << eventID << ". Skipping." << std::endl;
                continue;
            }

            Node* newNode = new Node(Event(eventID, name, date, time, organizer, isApproved));
            newNode->next = head;
            head = newNode;
            eventCount++;
        }
    }
    logFile.close();
    return eventCount;
}

void EventManager::displayEvents() const {
    clearScreen();
    std::cout << "\n+----------------------- Event List -----------------------+" << std::endl;
    if (eventCount == 0) {
        std::cout << "| No events scheduled yet.                                |" << std::endl;
        std::cout << "+---------------------------------------------------------+" << std::endl;
        return;
    }
    
    Node* current = head;
    int index = 1;
    while (current != nullptr) {
        std::cout << "| Event " << index++ << ":" << std::endl;
        std::cout << "| ID: " << current->event.getEventID() 
                  << "  Name: " << current->event.getName() << std::endl;
        std::cout << "| Date: " << current->event.getDate() 
                  << "  Time: " << current->event.getTime() << std::endl;
        std::cout << "| Organizer: " << current->event.getOrganizer() 
                  << "  Status: " << (current->event.getIsApproved() ? "Approved" : "Pending") << std::endl;
        std::cout << "+---------------------------------------------------------+" << std::endl;
        current = current->next;
    }
}

void EventManager::displayEvent(const Event& e) const {
    clearScreen();
    std::cout << "\n+----------------------- Event Details -----------------------+" << std::endl;
    std::cout << "| ID: " << e.getEventID() 
              << "  Name: " << e.getName() << std::endl;
    std::cout << "| Date: " << e.getDate() 
              << "  Time: " << e.getTime() << std::endl;
    std::cout << "| Organizer: " << e.getOrganizer() 
              << "  Status: " << (e.getIsApproved() ? "Approved" : "Pending") << std::endl;
    std::cout << "+-------------------------------------------------------------+" << std::endl;
}

void EventManager::displayMenu() const {
    clearScreen();
    std::cout << "\n+=======================================+" << std::endl;
    std::cout << "|       Event Scheduling System         |" << std::endl;
    std::cout << "+=======================================+" << std::endl;
    std::cout << "| 1. View All Events                   |" << std::endl;
    std::cout << "| 2. Sort Events by Date (Merge Sort)  |" << std::endl;
    std::cout << "| 3. Sort Events by Name (Quick Sort)  |" << std::endl;
    std::cout << "| 4. Search Event by ID                |" << std::endl;
    std::cout << "| 5. Approve an Event                  |" << std::endl;
    std::cout << "| 6. Edit Event by ID                  |" << std::endl;
    std::cout << "| 7. Delete Event by ID                |" << std::endl;
    std::cout << "| 8. Exit                              |" << std::endl;
    std::cout << "+=======================================+" << std::endl;
    std::cout << "Please enter your choice (1-9): ";
}

void EventManager::scheduleEvent(const std::string& eventID, const std::string& name, 
                               const std::string& date, const std::string& time, 
                               const std::string& organizer, bool approved) {

    Node* current = head;
    while (current != nullptr) {
        if (current->event.getEventID() == eventID) {
            std::cout << "ERROR: Event ID '" << eventID << "' already exists!" << std::endl;
            return;
        }
        current = current->next;
    }


    if (!isValidDate(date) || !isValidTime(time)) {
        std::cout << "ERROR: Invalid date or time format for event '" << eventID << "'!" << std::endl;
        return;
    }


    Event newEvent(eventID, name, date, time, organizer, approved);
    Node* newNode = new Node(newEvent);
    newNode->next = head;
    head = newNode;
    eventCount++;


    logEvent("Added", newEvent);
    std::cout << "\nSUCCESS: Event '" << newEvent.getName() << "' scheduled!" << std::endl;
}

void EventManager::sortByDate() {
    if (eventCount == 0) {
        std::cout << "ERROR: No events to sort!" << std::endl;
    } else {
        mergeSort(head);
        std::cout << "SUCCESS: Events sorted by date!" << std::endl;
        displayEvents();
    }
    std::cout << "Press Enter to continue...";
    std::string input;
    std::getline(std::cin, input);
}

void EventManager::sortByName() {
    if (eventCount == 0) {
        std::cout << "ERROR: No events to sort!" << std::endl;
    } else {
        quickSort(head);
        std::cout << "SUCCESS: Events sorted by name!" << std::endl;
        displayEvents();
    }
    std::cout << "Press Enter to continue...";
    std::string input;
    std::getline(std::cin, input);
}

void EventManager::searchEventByID() {
    if (eventCount == 0) {
        std::cout << "ERROR: No events to search!" << std::endl;
    } else {
        std::string eventID;
        clearScreen();
        std::cout << "\n+==== Search Event by ID ====+ " << std::endl;
        std::cout << "Enter Event ID to search: ";
        std::getline(std::cin, eventID);
        
        Node* node = findNode(eventID);
        if (node) {
            displayEvent(node->event);
        } else {
            std::cout << "ERROR: Event ID '" << eventID << "' not found!" << std::endl;
        }
    }
    std::cout << "Press Enter to continue...";
    std::string input;
    std::getline(std::cin, input);
}

void EventManager::approveEvent() {
    std::string eventID;
    clearScreen();
    std::cout << "\n+==== Approve an Event ====+ " << std::endl;
    std::cout << "Enter Event ID to approve: ";
    std::getline(std::cin, eventID);
    
    Node* node = findNode(eventID);
    if (node) {
        node->event.setApproved(true);
        logEvent("Approved", node->event);
        std::cout << "SUCCESS: Event '" << eventID << "' approved!" << std::endl;
    } else {
        std::cout << "ERROR: Event ID '" << eventID << "' not found!" << std::endl;
    }
    std::cout << "Press Enter to continue...";
    std::string input;
    std::getline(std::cin, input);
}

void EventManager::editEventByID() {
    if (eventCount == 0) {
        std::cout << "ERROR: No events to edit!" << std::endl;
    } else {
        std::string eventID;
        clearScreen();
        std::cout << "\n+==== Edit Event by ID ====+ " << std::endl;
        std::cout << "Enter Event ID to edit: ";
        std::getline(std::cin, eventID);
        
        Node* node = findNode(eventID);
        if (node) {
            Event& e = node->event;
            std::string input;

            std::cout << "\nCurrent Event Details:" << std::endl;
            displayEvent(e);

            std::cout << "Enter New Event Name (press Enter to keep '" << e.getName() << "'): ";
            std::getline(std::cin, input);
            if (!input.empty()) e.setName(input);

            std::cout << "Enter New Date (YYYY-MM-DD, press Enter to keep '" << e.getDate() << "'): ";
            std::getline(std::cin, input);
            if (!input.empty()) {
                if (!isValidDate(input)) {
                    std::cout << "ERROR: Invalid date format! Use YYYY-MM-DD." << std::endl;
                } else {
                    e.setDate(input);
                }
            }

            std::cout << "Enter New Time (HH:MM, press Enter to keep '" << e.getTime() << "'): ";
            std::getline(std::cin, input);
            if (!input.empty()) {
                if (!isValidTime(input)) {
                    std::cout << "ERROR: Invalid time format! Use HH:MM." << std::endl;
                } else {
                    e.setTime(input);
                }
            }

            std::cout << "Enter New Organizer Name (press Enter to keep '" << e.getOrganizer() << "'): ";
            std::getline(std::cin, input);
            if (!input.empty()) e.setOrganizer(input);

            logEvent("Edited", e);
            std::cout << "\nSUCCESS: Event '" << e.getEventID() << "' edited!" << std::endl;
        } else {
            std::cout << "ERROR: Event ID '" << eventID << "' not found!" << std::endl;
        }
    }
    std::cout << "Press Enter to continue...";
    std::string input;
    std::getline(std::cin, input);
}

void EventManager::deleteEventByID() {
    if (eventCount == 0) {
        std::cout << "ERROR: No events to delete!" << std::endl;
    } else {
        std::string eventID;
        clearScreen();
        std::cout << "\n+==== Delete Event by ID ====+ " << std::endl;
        std::cout << "Enter Event ID to delete: ";
        std::getline(std::cin, eventID);
        
        Node* current = head;
        Node* prev = nullptr;
        
        while (current != nullptr && current->event.getEventID() != eventID) {
            prev = current;
            current = current->next;
        }
        
        if (current != nullptr) {
            std::cout << "\nConfirm deletion of:" << std::endl;
            displayEvent(current->event);
            std::cout << "Are you sure? (Y/N): ";
            std::string confirm;
            std::getline(std::cin, confirm);
            
            if (confirm == "Y" || confirm == "y") {
                if (prev == nullptr) {
                    head = current->next;
                } else {
                    prev->next = current->next;
                }
                logEvent("Deleted", current->event);
                delete current;
                eventCount--;
                std::cout << "\nSUCCESS: Event '" << eventID << "' deleted!" << std::endl;
            } else {
                std::cout << "Deletion canceled." << std::endl;
            }
        } else {
            std::cout << "ERROR: Event ID '" << eventID << "' not found!" << std::endl;
        }
    }
    std::cout << "Press Enter to continue...";
    std::string input;
    std::getline(std::cin, input);
}