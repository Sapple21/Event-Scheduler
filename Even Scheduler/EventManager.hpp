#ifndef EVENT_MANAGER_HPP
#define EVENT_MANAGER_HPP

#include "Event.hpp"
#include <string>

// Move Node outside the class but keep it in the header
struct Node {
    Event event;
    Node* next;
    Node(const Event& e) : event(e), next(nullptr) {}
};

class EventManager {
private:
    Node* head;
    int eventCount;

    void mergeSort(Node*& headRef);
    Node* merge(Node* left, Node* right);
    Node* getMiddle(Node* head);
    void quickSort(Node*& headRef);
    Node* partition(Node* head, Node*& newHead, Node*& newEnd);
    Node* quickSortRec(Node* head, Node* end);
    Node* getTail(Node* cur);
    Node* findNode(const std::string& eventID);
    void logEvent(const std::string& action, const Event& e);

public:
    EventManager();
    ~EventManager();
    
    int loadEventsFromFile();
    void displayEvents() const;
    void displayEvent(const Event& e) const;
    void displayMenu() const;
    void scheduleEvent();
    void sortByDate();
    void sortByName();
    void searchEventByID();
    void approveEvent();
    void editEventByID();
    void deleteEventByID();
    int getEventCount() const { return eventCount; }
};

#endif