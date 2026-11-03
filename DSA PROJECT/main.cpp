#include <iostream>
#include <limits>
#include <string>
#include "Library.h"

using namespace std;

// Read an integer and recover from invalid keyboard input.
int readInt(const string& prompt)
{
    int value;

    while (true)
    {
        cout << prompt;
        if (cin >> value)
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }

        // Clear the error state and discard the invalid input line.
        cout << "Invalid input. Please enter a number.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

// Read a complete line so titles and names may contain spaces.
string readText(const string& prompt)
{
    string value;
    cout << prompt;
    getline(cin, value);
    return value;
}

void showMenu()
{
    cout << "\n============================================\n";
    cout << "        LIBRARY MANAGEMENT SYSTEM\n";
    cout << "============================================\n";
    cout << " 1. Add Student Record\n";
    cout << " 2. Display Student Records\n";
    cout << " 3. Add Book\n";
    cout << " 4. Remove Book by ID\n";
    cout << " 5. Insert Book at Position\n";
    cout << " 6. Remove Book at Position\n";
    cout << " 7. Swap Two Books\n";
    cout << " 8. Sort Books by ID\n";
    cout << " 9. Reverse Book List\n";
    cout << "10. Display All Books\n";
    cout << "11. Check Book Availability\n";
    cout << "12. View a Book (Push to Stack)\n";
    cout << "13. Display Viewing History\n";
    cout << "14. Remove Latest History Entry (Pop)\n";
    cout << "15. Add Normal Book Request (FIFO)\n";
    cout << "16. Process Oldest Normal Request\n";
    cout << "17. Display Normal Requests\n";
    cout << "18. Add Priority Book Request\n";
    cout << "19. Process Highest-Priority Request\n";
    cout << "20. Display Priority Requests\n";
    cout << "21. Add Book to Featured Rotation\n";
    cout << "22. Show Current Featured Book\n";
    cout << "23. Move to Next Featured Book\n";
    cout << "24. Display Featured Books\n";
    cout << "25. Refresh Doubly Linked Browse List\n";
    cout << "26. Show Current Browsing Book\n";
    cout << "27. Browse Next Book\n";
    cout << "28. Browse Previous Book\n";
    cout << "29. Display Browse List Forward\n";
    cout << "30. Display Browse List Backward\n";
    cout << " 0. Exit\n";
    cout << "============================================\n";
}

int main()
{
    Library library;

    // Add starter data so the program can be tested immediately.
    library.addStudent(101, "Ali Ahmed", "Computer Science");
    library.addStudent(102, "Sara Khan", "Software Engineering");
    library.addStudent(103, "Ayesha Noor", "Information Technology");

    library.addBook(201, "Data Structures", "Mark Allen Weiss");
    library.addBook(202, "Database System Concepts", "Silberschatz");
    library.addBook(203, "Object Oriented Programming", "Robert Lafore");
    library.addBook(204, "Computer Networks", "Andrew Tanenbaum");

    int choice;

    // Repeat the menu until the user selects Exit.
    do
    {
        showMenu();
        choice = readInt("Enter your choice: ");

        // Each case calls the matching Library class operation.
        switch (choice)
        {
            case 1:
            {
                int id = readInt("Enter student ID: ");
                string name = readText("Enter student name: ");
                string department = readText("Enter department: ");
                library.addStudent(id, name, department);
                break;
            }

            case 2:
                library.displayStudents();
                break;

            case 3:
            {
                int id = readInt("Enter book ID: ");
                string title = readText("Enter book title: ");
                string author = readText("Enter author name: ");
                library.addBook(id, title, author);
                break;
            }

            case 4:
                library.removeBook(readInt("Enter book ID to remove: "));
                break;

            case 5:
            {
                int position = readInt("Enter zero-based position: ");
                int id = readInt("Enter new book ID: ");
                string title = readText("Enter book title: ");
                string author = readText("Enter author name: ");
                library.insertBookAt(position, id, title, author);
                break;
            }

            case 6:
                library.removeBookAt(readInt("Enter zero-based position: "));
                break;

            case 7:
            {
                int firstID = readInt("Enter first book ID: ");
                int secondID = readInt("Enter second book ID: ");
                library.swapBooks(firstID, secondID);
                break;
            }

            case 8:
                library.sortBooksByID();
                break;

            case 9:
                library.reverseBooks();
                break;

            case 10:
                library.displayBooks();
                break;

            case 11:
                library.displayBookStatus(readInt("Enter book ID: "));
                break;

            case 12:
                library.viewBook(readInt("Enter book ID to view: "));
                break;

            case 13:
                library.displayRecentlyViewed();
                break;

            case 14:
                library.popRecentlyViewed();
                break;

            case 15:
            {
                int studentID = readInt("Enter student ID: ");
                int bookID = readInt("Enter requested book ID: ");
                library.enqueueRequest(studentID, bookID);
                break;
            }

            case 16:
                library.processNextRequest();
                break;

            case 17:
                library.displayRequests();
                break;

            case 18:
            {
                int studentID = readInt("Enter student ID: ");
                int bookID = readInt("Enter requested book ID: ");
                int priority = readInt("Priority (1=High, 2=Medium, 3=Low): ");
                library.addPriorityRequest(studentID, bookID, priority);
                break;
            }

            case 19:
                library.processPriorityRequest();
                break;

            case 20:
                library.displayPriorityRequests();
                break;

            case 21:
                library.addFeaturedBook(readInt("Enter book ID to feature: "));
                break;

            case 22:
                library.showFeaturedBook();
                break;

            case 23:
                library.moveToNextFeatured();
                break;

            case 24:
                library.displayFeaturedBooks();
                break;

            case 25:
                library.buildBrowseList();
                break;

            case 26:
                library.showCurrentBrowseBook();
                break;

            case 27:
                library.browseNext();
                break;

            case 28:
                library.browsePrevious();
                break;

            case 29:
                library.displayBrowseForward();
                break;

            case 30:
                library.displayBrowseBackward();
                break;

            case 0:
                cout << "Thank you for using Library Management System.\n";
                break;

            default:
                cout << "Invalid choice. Please select from the menu.\n";
        }

    } while (choice != 0);

    return 0;
}
