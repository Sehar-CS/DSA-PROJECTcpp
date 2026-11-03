#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <string>
using namespace std;

// Lab 01: Singly linked student record node.
struct StudentNode
{
    int studentID;
    string studentName;
    string department;
    StudentNode* next;
};

// Lab 05: Singly linked book collection node.
struct BookNode
{
    int bookID;
    string title;
    string author;
    bool available;
    BookNode* next;
};

// Lab 02: Stack node for recently viewed books (LIFO).
struct HistoryNode
{
    int bookID;
    string title;
    HistoryNode* next;
};

// Lab 03 and Lab 04: Book request node for FIFO and priority queues.
struct RequestNode
{
    int requestID;
    int studentID;
    string studentName;
    int bookID;
    string bookTitle;
    int priority; // Smaller number means higher priority.
    RequestNode* next;
};

// Lab 06: Circular linked list node for rotating featured books.
struct CircularBookNode
{
    int bookID;
    string title;
    CircularBookNode* next;
};

// Lab 07: Doubly linked list node for forward/backward book browsing.
struct DoublyBookNode
{
    int bookID;
    string title;
    string author;
    DoublyBookNode* previous;
    DoublyBookNode* next;
};

#endif
