#ifndef LIBRARY_H
#define LIBRARY_H

#include "structures.h"

class Library
{
private:
    // Lab 01: Student records (singly linked list).
    StudentNode* studentsHead;

    // Lab 05: Main book collection (singly linked list).
    BookNode* booksHead;

    // Lab 02: Recently viewed books (stack).
    HistoryNode* historyTop;
    int historyCount;

    // Lab 03: Normal book requests (FIFO queue).
    RequestNode* requestFront;
    RequestNode* requestRear;
    int requestCount;

    // Lab 04: Urgent book requests (priority queue).
    RequestNode* priorityFront;
    int priorityCount;

    // Lab 06: Featured book rotation (circular linked list).
    CircularBookNode* featuredHead;
    CircularBookNode* featuredCurrent;

    // Lab 07: Book browsing (doubly linked list).
    DoublyBookNode* browseHead;
    DoublyBookNode* browseTail;
    DoublyBookNode* browseCurrent;

    int nextRequestID;

    BookNode* findBook(int bookID) const;
    StudentNode* findStudent(int studentID) const;
    void clearStudents();
    void clearBooks();
    void clearHistory();
    void clearRequests(RequestNode*& front, RequestNode*& rear);
    void clearPriorityRequests();
    void clearFeatured();
    void clearBrowse();

public:
    Library();
    ~Library();

    // Student records (Lab 01).
    void addStudent(int id, const string& name, const string& department);
    void displayStudents() const;

    // Book collection and linked-list operations (Lab 05).
    void addBook(int id, const string& title, const string& author);
    void removeBook(int id);
    void insertBookAt(int position, int id, const string& title, const string& author);
    void removeBookAt(int position);
    void swapBooks(int firstID, int secondID);
    void sortBooksByID();
    void reverseBooks();
    void displayBooks() const;
    void displayBookStatus(int id) const;

    // Stack operations (Lab 02).
    void viewBook(int id);
    void displayRecentlyViewed() const;
    void popRecentlyViewed();

    // FIFO queue operations (Lab 03).
    void enqueueRequest(int studentID, int bookID);
    void processNextRequest();
    void displayRequests() const;

    // Priority queue operations (Lab 04).
    void addPriorityRequest(int studentID, int bookID, int priority);
    void processPriorityRequest();
    void displayPriorityRequests() const;

    // Circular linked list operations (Lab 06).
    void addFeaturedBook(int bookID);
    void showFeaturedBook() const;
    void moveToNextFeatured();
    void displayFeaturedBooks() const;

    // Doubly linked list operations (Lab 07).
    void buildBrowseList();
    void showCurrentBrowseBook() const;
    void browseNext();
    void browsePrevious();
    void displayBrowseForward() const;
    void displayBrowseBackward() const;
};

#endif
