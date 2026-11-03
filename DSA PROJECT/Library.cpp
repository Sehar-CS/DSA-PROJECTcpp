#include <iostream>
#include <iomanip>
#include "Library.h"

using namespace std;

// Constructor: initialize every linked-list pointer and counter.
Library::Library()
{
    studentsHead = nullptr;
    booksHead = nullptr;
    historyTop = nullptr;
    historyCount = 0;
    requestFront = requestRear = nullptr;
    requestCount = 0;
    priorityFront = nullptr;
    priorityCount = 0;
    featuredHead = featuredCurrent = nullptr;
    browseHead = browseTail = browseCurrent = nullptr;
    nextRequestID = 1;
}

// Destructor: release all dynamically allocated nodes.
Library::~Library()
{
    clearStudents();
    clearBooks();
    clearHistory();
    clearRequests(requestFront, requestRear);
    clearPriorityRequests();
    clearFeatured();
    clearBrowse();
}

void Library::clearStudents()
{
    while (studentsHead != nullptr)
    {
        StudentNode* temp = studentsHead;
        studentsHead = studentsHead->next;
        delete temp;
    }
}

void Library::clearBooks()
{
    while (booksHead != nullptr)
    {
        BookNode* temp = booksHead;
        booksHead = booksHead->next;
        delete temp;
    }
}

void Library::clearHistory()
{
    while (historyTop != nullptr)
    {
        HistoryNode* temp = historyTop;
        historyTop = historyTop->next;
        delete temp;
    }
    historyCount = 0;
}

void Library::clearRequests(RequestNode*& front, RequestNode*& rear)
{
    while (front != nullptr)
    {
        RequestNode* temp = front;
        front = front->next;
        delete temp;
    }
    rear = nullptr;
}

void Library::clearPriorityRequests()
{
    while (priorityFront != nullptr)
    {
        RequestNode* temp = priorityFront;
        priorityFront = priorityFront->next;
        delete temp;
    }
    priorityCount = 0;
}

void Library::clearFeatured()
{
    if (featuredHead == nullptr)
        return;

    // Break the circle first so normal node-by-node deletion is safe.
    CircularBookNode* last = featuredHead;
    while (last->next != featuredHead)
        last = last->next;
    last->next = nullptr;

    while (featuredHead != nullptr)
    {
        CircularBookNode* temp = featuredHead;
        featuredHead = featuredHead->next;
        delete temp;
    }
    featuredCurrent = nullptr;
}

void Library::clearBrowse()
{
    while (browseHead != nullptr)
    {
        DoublyBookNode* temp = browseHead;
        browseHead = browseHead->next;
        delete temp;
    }
    browseTail = browseCurrent = nullptr;
}

BookNode* Library::findBook(int bookID) const
{
    BookNode* current = booksHead;
    while (current != nullptr)
    {
        if (current->bookID == bookID)
            return current;
        current = current->next;
    }
    return nullptr;
}

StudentNode* Library::findStudent(int studentID) const
{
    StudentNode* current = studentsHead;
    while (current != nullptr)
    {
        if (current->studentID == studentID)
            return current;
        current = current->next;
    }
    return nullptr;
}

// Lab 01: Add a student record at the end of the singly linked list.
void Library::addStudent(int id, const string& name, const string& department)
{
    if (findStudent(id) != nullptr)
    {
        cout << "A student with this ID already exists.\n";
        return;
    }

    StudentNode* node = new StudentNode{id, name, department, nullptr};

    if (studentsHead == nullptr)
        studentsHead = node;
    else
    {
        StudentNode* current = studentsHead;
        while (current->next != nullptr)
            current = current->next;
        current->next = node;
    }
    cout << "Student added successfully.\n";
}

void Library::displayStudents() const
{
    if (studentsHead == nullptr)
    {
        cout << "No student records found.\n";
        return;
    }

    cout << "\n--- Student Records ---\n";
    StudentNode* current = studentsHead;
    while (current != nullptr)
    {
        cout << "ID: " << current->studentID
             << " | Name: " << current->studentName
             << " | Department: " << current->department << '\n';
        current = current->next;
    }
}

// Lab 05: Insert a new book at the end of the singly linked list.
void Library::addBook(int id, const string& title, const string& author)
{
    if (findBook(id) != nullptr)
    {
        cout << "A book with this ID already exists.\n";
        return;
    }

    BookNode* node = new BookNode{id, title, author, true, nullptr};

    if (booksHead == nullptr)
        booksHead = node;
    else
    {
        BookNode* current = booksHead;
        while (current->next != nullptr)
            current = current->next;
        current->next = node;
    }
    cout << "Book added successfully.\n";
}

// Lab 05: Remove a book by its ID.
void Library::removeBook(int id)
{
    BookNode* current = booksHead;
    BookNode* previous = nullptr;

    while (current != nullptr && current->bookID != id)
    {
        previous = current;
        current = current->next;
    }

    if (current == nullptr)
    {
        cout << "Book not found.\n";
        return;
    }

    if (previous == nullptr)
        booksHead = current->next;
    else
        previous->next = current->next;

    delete current;
    cout << "Book removed successfully.\n";
}

// Lab 05: Insert a book at a zero-based position.
void Library::insertBookAt(int position, int id, const string& title, const string& author)
{
    if (position < 0 || findBook(id) != nullptr)
    {
        cout << "Invalid position or duplicate book ID.\n";
        return;
    }

    BookNode* node = new BookNode{id, title, author, true, nullptr};

    if (position == 0)
    {
        node->next = booksHead;
        booksHead = node;
        cout << "Book inserted at position " << position << ".\n";
        return;
    }

    BookNode* current = booksHead;
    for (int i = 0; current != nullptr && i < position - 1; i++)
        current = current->next;

    if (current == nullptr)
    {
        delete node;
        cout << "Position is outside the list.\n";
        return;
    }

    node->next = current->next;
    current->next = node;
    cout << "Book inserted at position " << position << ".\n";
}

// Lab 05: Remove a book at a zero-based position.
void Library::removeBookAt(int position)
{
    if (position < 0 || booksHead == nullptr)
    {
        cout << "Invalid position or empty book list.\n";
        return;
    }

    BookNode* current = booksHead;

    if (position == 0)
        booksHead = booksHead->next;
    else
    {
        BookNode* previous = nullptr;
        for (int i = 0; current != nullptr && i < position; i++)
        {
            previous = current;
            current = current->next;
        }

        if (current == nullptr)
        {
            cout << "Position is outside the list.\n";
            return;
        }
        previous->next = current->next;
    }

    delete current;
    cout << "Book at position " << position << " removed.\n";
}

// Lab 05: Swap the data of two books without changing node links.
void Library::swapBooks(int firstID, int secondID)
{
    BookNode* first = findBook(firstID);
    BookNode* second = findBook(secondID);

    if (first == nullptr || second == nullptr)
    {
        cout << "Both book IDs must exist.\n";
        return;
    }

    int tempID = first->bookID;
    first->bookID = second->bookID;
    second->bookID = tempID;

    string tempTitle = first->title;
    first->title = second->title;
    second->title = tempTitle;

    string tempAuthor = first->author;
    first->author = second->author;
    second->author = tempAuthor;

    bool tempAvailability = first->available;
    first->available = second->available;
    second->available = tempAvailability;

    cout << "Book records swapped.\n";
}

// Lab 05: Sort the book list by ID using bubble sort on node data.
void Library::sortBooksByID()
{
    if (booksHead == nullptr || booksHead->next == nullptr)
    {
        cout << "Not enough books to sort.\n";
        return;
    }

    bool swapped;
    do
    {
        swapped = false;
        BookNode* current = booksHead;

        // Compare adjacent nodes and swap their data when out of order.
        while (current->next != nullptr)
        {
            if (current->bookID > current->next->bookID)
            {
                int id = current->bookID;
                current->bookID = current->next->bookID;
                current->next->bookID = id;

                string title = current->title;
                current->title = current->next->title;
                current->next->title = title;

                string author = current->author;
                current->author = current->next->author;
                current->next->author = author;

                bool available = current->available;
                current->available = current->next->available;
                current->next->available = available;

                swapped = true;
            }
            current = current->next;
        }
    } while (swapped);

    cout << "Books sorted by ID.\n";
}

// Lab 05: Reverse the singly linked book list.
void Library::reverseBooks()
{
    BookNode* previous = nullptr;
    BookNode* current = booksHead;

    // Reverse each next pointer while moving through the list.
    while (current != nullptr)
    {
        BookNode* nextNode = current->next;
        current->next = previous;
        previous = current;
        current = nextNode;
    }

    booksHead = previous;
    cout << "Book list reversed.\n";
}

void Library::displayBooks() const
{
    if (booksHead == nullptr)
    {
        cout << "No books in the library.\n";
        return;
    }

    cout << "\n--- Library Book Collection ---\n";
    BookNode* current = booksHead;
    while (current != nullptr)
    {
        cout << "ID: " << current->bookID
             << " | Title: " << current->title
             << " | Author: " << current->author
             << " | Status: " << (current->available ? "Available" : "Issued")
             << '\n';
        current = current->next;
    }
}

void Library::displayBookStatus(int id) const
{
    BookNode* book = findBook(id);
    if (book == nullptr)
        cout << "Book not found.\n";
    else
        cout << book->title << " is "
             << (book->available ? "available." : "currently issued.") << '\n';
}

// Lab 02: Push a viewed book onto the history stack.
void Library::viewBook(int id)
{
    BookNode* book = findBook(id);
    if (book == nullptr)
    {
        cout << "Book not found.\n";
        return;
    }

    HistoryNode* node = new HistoryNode{id, book->title, historyTop};
    historyTop = node;
    historyCount++;
    cout << "Viewing: " << book->title << '\n';
}

void Library::displayRecentlyViewed() const
{
    if (historyTop == nullptr)
    {
        cout << "Viewing history is empty.\n";
        return;
    }

    cout << "\n--- Recently Viewed Books (Newest First) ---\n";
    HistoryNode* current = historyTop;
    while (current != nullptr)
    {
        cout << current->bookID << " - " << current->title << '\n';
        current = current->next;
    }
    cout << "Total history entries: " << historyCount << '\n';
}

void Library::popRecentlyViewed()
{
    if (historyTop == nullptr)
    {
        cout << "Viewing history is empty.\n";
        return;
    }

    HistoryNode* temp = historyTop;
    historyTop = historyTop->next;
    cout << "Removed latest history entry: " << temp->title << '\n';
    delete temp;
    historyCount--;
}

// Lab 03: Add a normal request at the rear (FIFO).
void Library::enqueueRequest(int studentID, int bookID)
{
    StudentNode* student = findStudent(studentID);
    BookNode* book = findBook(bookID);

    if (student == nullptr || book == nullptr)
    {
        cout << "Student or book ID was not found.\n";
        return;
    }
    if (!book->available)
    {
        cout << "This book is currently issued.\n";
        return;
    }

    RequestNode* node = new RequestNode{
        nextRequestID++, studentID, student->studentName,
        bookID, book->title, 0, nullptr
    };

    if (requestRear == nullptr)
        requestFront = requestRear = node;
    else
    {
        requestRear->next = node;
        requestRear = node;
    }

    requestCount++;
    cout << "Book request added to the FIFO queue.\n";
}

// Lab 03: Process the oldest request first.
void Library::processNextRequest()
{
    if (requestFront == nullptr)
    {
        cout << "No normal requests are pending.\n";
        return;
    }

    RequestNode* temp = requestFront;
    requestFront = requestFront->next;
    if (requestFront == nullptr)
        requestRear = nullptr;

    BookNode* book = findBook(temp->bookID);
    if (book != nullptr && book->available)
    {
        book->available = false;
        cout << "Issued \"" << temp->bookTitle << "\" to "
             << temp->studentName << ".\n";
    }
    else
        cout << "Request could not be completed because the book is unavailable.\n";

    delete temp;
    requestCount--;
}

void Library::displayRequests() const
{
    if (requestFront == nullptr)
    {
        cout << "FIFO request queue is empty.\n";
        return;
    }

    cout << "\n--- Normal Requests (First In, First Out) ---\n";
    RequestNode* current = requestFront;
    while (current != nullptr)
    {
        cout << "Request #" << current->requestID
             << " | Student: " << current->studentName
             << " | Book: " << current->bookTitle << '\n';
        current = current->next;
    }
    cout << "Pending requests: " << requestCount << '\n';
}

// Lab 04: Insert an urgent request in ascending priority order.
void Library::addPriorityRequest(int studentID, int bookID, int priority)
{
    StudentNode* student = findStudent(studentID);
    BookNode* book = findBook(bookID);

    if (student == nullptr || book == nullptr)
    {
        cout << "Student or book ID was not found.\n";
        return;
    }
    if (!book->available)
    {
        cout << "This book is currently issued.\n";
        return;
    }
    if (priority < 1 || priority > 3)
    {
        cout << "Priority must be 1 (High), 2 (Medium), or 3 (Low).\n";
        return;
    }

    RequestNode* node = new RequestNode{
        nextRequestID++, studentID, student->studentName,
        bookID, book->title, priority, nullptr
    };

    // Insert before the current front when this request has higher priority.
    if (priorityFront == nullptr || priority < priorityFront->priority)
    {
        node->next = priorityFront;
        priorityFront = node;
    }
    else
    {
        RequestNode* current = priorityFront;
        // Keep equal-priority requests in their arrival order.
        while (current->next != nullptr &&
               current->next->priority <= priority)
            current = current->next;

        node->next = current->next;
        current->next = node;
    }

    priorityCount++;
    cout << "Priority request added successfully.\n";
}

// Lab 04: Process the request with the smallest priority number first.
void Library::processPriorityRequest()
{
    if (priorityFront == nullptr)
    {
        cout << "No priority requests are pending.\n";
        return;
    }

    RequestNode* temp = priorityFront;
    priorityFront = priorityFront->next;

    BookNode* book = findBook(temp->bookID);
    if (book != nullptr && book->available)
    {
        book->available = false;
        cout << "Priority " << temp->priority << " request issued \""
             << temp->bookTitle << "\" to " << temp->studentName << ".\n";
    }
    else
        cout << "Priority request could not be completed; book is unavailable.\n";

    delete temp;
    priorityCount--;
}

void Library::displayPriorityRequests() const
{
    if (priorityFront == nullptr)
    {
        cout << "Priority queue is empty.\n";
        return;
    }

    cout << "\n--- Priority Requests (1 = Highest) ---\n";
    RequestNode* current = priorityFront;
    while (current != nullptr)
    {
        cout << "Request #" << current->requestID
             << " | Student: " << current->studentName
             << " | Book: " << current->bookTitle
             << " | Priority: " << current->priority << '\n';
        current = current->next;
    }
}

// Lab 06: Add a book to the circular featured-books list.
void Library::addFeaturedBook(int bookID)
{
    BookNode* book = findBook(bookID);
    if (book == nullptr)
    {
        cout << "Book not found.\n";
        return;
    }

    CircularBookNode* node = new CircularBookNode{bookID, book->title, nullptr};

    if (featuredHead == nullptr)
    {
        featuredHead = node;
        node->next = featuredHead;
        featuredCurrent = featuredHead;
    }
    else
    {
        CircularBookNode* last = featuredHead;
        while (last->next != featuredHead)
            last = last->next;

        last->next = node;
        node->next = featuredHead;
    }

    cout << "Book added to featured rotation.\n";
}

void Library::showFeaturedBook() const
{
    if (featuredCurrent == nullptr)
    {
        cout << "No featured books have been added.\n";
        return;
    }

    cout << "Current featured book: " << featuredCurrent->title
         << " (ID: " << featuredCurrent->bookID << ")\n";
}

void Library::moveToNextFeatured()
{
    if (featuredCurrent == nullptr)
    {
        cout << "No featured books have been added.\n";
        return;
    }

    // The circular link automatically returns to the first node.
    featuredCurrent = featuredCurrent->next;
    showFeaturedBook();
}

void Library::displayFeaturedBooks() const
{
    if (featuredHead == nullptr)
    {
        cout << "Featured list is empty.\n";
        return;
    }

    cout << "\n--- Featured Books (Circular List) ---\n";
    CircularBookNode* current = featuredHead;
    do
    {
        cout << current->bookID << " - " << current->title << '\n';
        current = current->next;
    } while (current != featuredHead);
}

// Lab 07: Rebuild a doubly linked browsing list from the current book list.
void Library::buildBrowseList()
{
    clearBrowse();

    BookNode* book = booksHead;
    while (book != nullptr)
    {
        DoublyBookNode* node = new DoublyBookNode{
            book->bookID, book->title, book->author, browseTail, nullptr
        };

        if (browseHead == nullptr)
            browseHead = node;
        else
            browseTail->next = node;

        browseTail = node;
        book = book->next;
    }

    browseCurrent = browseHead;
    cout << "Browsing list refreshed from the library collection.\n";
}

void Library::showCurrentBrowseBook() const
{
    if (browseCurrent == nullptr)
    {
        cout << "Browsing list is empty. Refresh it first.\n";
        return;
    }

    cout << "Current Book: " << browseCurrent->title
         << " | Author: " << browseCurrent->author
         << " | ID: " << browseCurrent->bookID << '\n';
}

void Library::browseNext()
{
    if (browseCurrent == nullptr || browseCurrent->next == nullptr)
    {
        cout << "There is no next book.\n";
        return;
    }
    browseCurrent = browseCurrent->next;
    showCurrentBrowseBook();
}

void Library::browsePrevious()
{
    if (browseCurrent == nullptr || browseCurrent->previous == nullptr)
    {
        cout << "There is no previous book.\n";
        return;
    }
    browseCurrent = browseCurrent->previous;
    showCurrentBrowseBook();
}

void Library::displayBrowseForward() const
{
    if (browseHead == nullptr)
    {
        cout << "Browsing list is empty. Refresh it first.\n";
        return;
    }

    cout << "\n--- Browse Forward ---\n";
    DoublyBookNode* current = browseHead;
    while (current != nullptr)
    {
        cout << current->bookID << " - " << current->title
             << " by " << current->author << '\n';
        current = current->next;
    }
}

void Library::displayBrowseBackward() const
{
    if (browseTail == nullptr)
    {
        cout << "Browsing list is empty. Refresh it first.\n";
        return;
    }

    cout << "\n--- Browse Backward ---\n";
    DoublyBookNode* current = browseTail;
    while (current != nullptr)
    {
        cout << current->bookID << " - " << current->title
             << " by " << current->author << '\n';
        current = current->previous;
    }
}
