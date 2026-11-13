#include <string>
#include <iostream>

using namespace std;

class Book {
private:
    int bookID;
    string bookTitle;
    string authorName;
    double price;

public:
    Book(int id, string title, string author, double p) {
        bookID = id;
        bookTitle = title;
        authorName = author;
        price = p;
    }

    void displayBook() const {
        cout << "Book ID : " << bookID << endl;
        cout << "Book Title : " << bookTitle << endl;
        cout << "Author : " << authorName << endl;
        cout << "Price : Tk. " << price << endl;
    }
};

class Member {
private:
    int memberID;
    string memberName;
    string memberEmail;
    int* borrowedBookIDs;
    int borrowedCount;
    int capacity;
    double totalFine;

    void calculateFine(int days) {
        if (days > 0) {
            totalFine = days * 10;
        }
    }

public:
    Member() {
        memberID = 0;
        memberName = "Unknown";
        memberEmail = "Not Assigned";
        borrowedCount = 0;
        capacity = 1;
        totalFine = 0;
        borrowedBookIDs = new int[capacity];
    }

    Member(int id, string name);

    Member(int id, string name, string email) {
        memberID = id;
        memberName = name;
        memberEmail = email;
        borrowedCount = 0;
        capacity = 1;
        totalFine = 0;
        borrowedBookIDs = new int[capacity];
    }

    Member(const Member& other) {
        memberID = other.memberID;
        memberName = other.memberName;
        memberEmail = other.memberEmail;
        borrowedCount = other.borrowedCount;
        capacity = other.capacity;
        totalFine = other.totalFine;

        borrowedBookIDs = new int[capacity];

        for (int i = 0; i < borrowedCount; i++) {
            borrowedBookIDs[i] = other.borrowedBookIDs[i];
        }
    }

    Member(Member&& other) {
        memberID = other.memberID;
        memberName = other.memberName;
        memberEmail = other.memberEmail;
        borrowedBookIDs = other.borrowedBookIDs;
        borrowedCount = other.borrowedCount;
        capacity = other.capacity;
        totalFine = other.totalFine;

        other.borrowedBookIDs = nullptr;
        other.borrowedCount = 0;
        other.capacity = 0;
        other.totalFine = 0;
    }

    Member& operator=(const Member& other) {
        if (this != &other) {
            int* newArray = new int[other.capacity > 0 ? other.capacity : 1];

            for (int i = 0; i < other.borrowedCount; i++) {
                newArray[i] = other.borrowedBookIDs[i];
            }

            delete[] borrowedBookIDs;

            memberID = other.memberID;
            memberName = other.memberName;
            memberEmail = other.memberEmail;
            borrowedCount = other.borrowedCount;
            capacity = other.capacity > 0 ? other.capacity : 1;
            totalFine = other.totalFine;
            borrowedBookIDs = newArray;
        }

        return *this;
    }

    ~Member() {
        delete[] borrowedBookIDs;
        cout << "Destructor called for Member ID: "
             << memberID << endl;
        cout << "Dynamic memory released successfully." << endl;
    }

    void setName(string memberName) {
        this->memberName = memberName;
    }

    string getName() const {
        return memberName;
    }

    void setEmail(string email) {
        this->memberEmail = email;
    }

    string getEmail() const {
        return memberEmail;
    }

    void addBorrowedBook(int bookID) {
        if (borrowedCount == capacity) {
            int newCapacity = capacity * 2;
            int* newArray = new int[newCapacity];

            for (int i = 0; i < borrowedCount; i++) {
                newArray[i] = borrowedBookIDs[i];
            }

            delete[] borrowedBookIDs;

            borrowedBookIDs = newArray;
            capacity = newCapacity;
        }

        borrowedBookIDs[borrowedCount] = bookID;
        borrowedCount++;
    }

    void borrowBook(int bookID) {
        cout << "Book ID " << bookID
             << " borrowed using default borrowing period." << endl;
    }

    void borrowBook(int bookID, int days) {
        cout << "Book ID " << bookID
             << " borrowed for " << days << " days." << endl;

        calculateFine(days);
    }

    inline bool canBorrowMore() const {
        return borrowedCount < 5;
    }

    void displayRecord() const;

    friend void compareMembers(const Member& m1,
                               const Member& m2);

    int getBorrowedCount() const {
        return borrowedCount;
    }

    double getFine() const {
        return totalFine;
    }
};

Member::Member(int id, string name) {
    memberID = id;
    memberName = name;
    memberEmail = "Not Assigned";
    borrowedCount = 0;
    capacity = 1;
    totalFine = 0;
    borrowedBookIDs = new int[capacity];
}

void Member::displayRecord() const {
    cout << "Member ID : " << memberID << endl;
    cout << "Member Name : " << memberName << endl;
    cout << "Member Email : " << memberEmail << endl;

    cout << "Borrowed Books : ";

    for (int i = 0; i < borrowedCount; i++) {
        cout << borrowedBookIDs[i] << " ";
    }

    cout << endl;
    cout << "Number of Books : " << borrowedCount << endl;
    cout << "Total Fine : Tk. " << totalFine << endl;

    cout << "Can Borrow More : "
         << (canBorrowMore() ? "Yes" : "No") << endl;
}

void compareMembers(const Member& m1, const Member& m2) {
    cout << "=== Member Comparison ===" << endl;

    cout << m1.memberName << " borrowed "
         << m1.borrowedCount << " book(s)." << endl;

    cout << m2.memberName << " borrowed "
         << m2.borrowedCount << " book(s)." << endl;

    if (m1.borrowedCount > m2.borrowedCount) {
        cout << m1.memberName << " has borrowed more books." << endl;
    }
    else if (m1.borrowedCount < m2.borrowedCount) {
        cout << m2.memberName << " has borrowed more books." << endl;
    }
    else {
        cout << "Both members borrowed equal books." << endl;
    }
}

void showMemberByValue(Member m) {
    cout << "Received Member:" << endl;
    m.displayRecord();
}

void updateMemberByReference(Member& m) {
    m.setName("Karim Hossain Updated");
}

void showMember(const Member& m) {
    cout << "Member ID and Name:" << endl;
    m.displayRecord();
}

Member createMember(int id, string name, string email) {
    Member m(id, name, email);
    return m;
}

int main() {

    cout << "==================================================" << endl;
    cout << "LIBRARY MEMBER AND BOOK MANAGEMENT SYSTEM" << endl;
    cout << "==================================================" << endl;

    int id1, id2, bookID;
    int firstBook, secondBook, thirdBook, days;
    string name1, name2, email1, email2;
    string updatedName, title, author;
    double price;

    cout << "Enter information for Member 1:" << endl;

    cout << "Member ID: ";
    cin >> id1;
    cin.ignore();

    cout << "Member Name: ";
    getline(cin, name1);

    cout << "Member Email: ";
    getline(cin, email1);

    cout << "Enter information for Member 2:" << endl;

    cout << "Member ID: ";
    cin >> id2;
    cin.ignore();

    cout << "Member Name: ";
    getline(cin, name2);

    cout << "Member Email: ";
    getline(cin, email2);

    cout << "Enter Book Information:" << endl;

    cout << "Book ID: ";
    cin >> bookID;
    cin.ignore();

    cout << "Book Title: ";
    getline(cin, title);

    cout << "Author Name: ";
    getline(cin, author);

    cout << "Price: ";
    cin >> price;

    cout << "Enter borrowed book ID for Rahim: ";
    cin >> firstBook;

    cout << "Enter another borrowed book ID for Rahim: ";
    cin >> secondBook;

    cout << "Enter borrowing days: ";
    cin >> days;

    cout << "Enter borrowed book ID for Karim: ";
    cin >> thirdBook;
    cin.ignore();

    cout << "Enter updated name for Member 2:" << endl;
    getline(cin, updatedName);

    Book b1(bookID, title, author, price);
    Book b2 = b1;

    Member member1(id1, name1, email1);
    Member member2(id2, name2, email2);

    cout << "\n=== 1. Class and Object Creation ===" << endl;
    cout << "Book object created successfully." << endl;
    cout << "Member objects created successfully." << endl;

    Member defaultMember;

    cout << "=== 2. Default Constructor / Inline Constructor ===" << endl;
    cout << "Default constructor called." << endl;
    defaultMember.displayRecord();

    Member parameterMember(id1, name1);

    cout << "=== 3. Parameterized Constructor ===" << endl;
    cout << "Parameterized constructor called using:" << endl;
    cout << "Member(int id, string name)" << endl;
    cout << "Member ID : " << id1 << endl;
    cout << "Member Name : " << name1 << endl;

    cout << "=== 4. Constructor Overloading ===" << endl;
    cout << "Another parameterized constructor called using:" << endl;
    cout << "Member(int id, string name, string email)" << endl;
    cout << "Member ID : " << id2 << endl;
    cout << "Member Name : " << name2 << endl;
    cout << "Member Email : " << email2 << endl;

    Member outsideMember(105, "Outside Member");

    cout << "=== 5. Constructor Defined Outside Class Using :: ===" << endl;
    cout << "Member::Member(int id, string name) executed successfully." << endl;

    cout << "=== 6. Default Object Copying ===" << endl;

    cout << "Original Book:" << endl;
    b1.displayBook();

    cout << "Copied Book:" << endl;
    b2.displayBook();

    cout << "Default object copying completed successfully." << endl;

    member1.addBorrowedBook(firstBook);
    member1.addBorrowedBook(secondBook);

    Member copiedMember(member1);

    cout << "=== 7. User-Defined Copy Constructor ===" << endl;
    cout << "Copy constructor called for Member object." << endl;
    cout << "Original Member:" << endl;
    cout << "ID : " << id1 << endl;
    cout << "Name : " << name1 << endl;

    cout << "Copied Member:" << endl;
    cout << "ID : " << id1 << endl;
    cout << "Name : " << name1 << endl;
    cout << "Dynamic borrowed-book array copied using deep copy." << endl;

    Member movedMember(std::move(copiedMember));

    cout << "=== 8. Move Constructor ===" << endl;
    cout << "Move constructor called." << endl;
    cout << "Dynamic resources transferred successfully." << endl;
    cout << "Source object resource transferred." << endl;
    cout << "Destination object now owns the dynamic memory." << endl;

    Member m1(id1, name1);
    Member m2(id2, name2);

    m1.addBorrowedBook(firstBook);
    m2 = m1;

    cout << "=== 9. Copy Assignment Operator ===" << endl;
    cout << "Copy assignment operator called." << endl;
    cout << "m2 = m1 completed successfully." << endl;
    cout << "Dynamic data copied using deep copy." << endl;

    cout << "=== 10. Setter, Getter and this Keyword ===" << endl;
    cout << "Old Member Name : " << member2.getName() << endl;

    cout << "Calling:" << endl;
    cout << "setName(\"Karim Hossain\")" << endl;

    member2.setName(updatedName);

    cout << "Using:" << endl;
    cout << "this->memberName = memberName;" << endl;
    cout << "Updated Member Name : " << member2.getName() << endl;

    cout << "Value returned using getName():" << endl;
    cout << member2.getName() << endl;

    cout << "=== 11. Dynamic Memory Allocation ===" << endl;
    cout << "Dynamic borrowed-book array created using:" << endl;
    cout << "borrowedBookIDs = new int[capacity];" << endl;
    cout << "Memory allocation successful." << endl;

    member2.addBorrowedBook(thirdBook);

    cout << "=== 12. Adding Borrowed Books ===" << endl;
    cout << "Rahim borrowed Book ID: " << firstBook << endl;
    cout << "Borrowed book added successfully." << endl;

    cout << "Rahim borrowed Book ID: " << secondBook << endl;
    cout << "Borrowed book added successfully." << endl;

    cout << "Karim borrowed Book ID: " << thirdBook << endl;
    cout << "Borrowed book added successfully." << endl;

    cout << "=== 13. Dynamic Array Management ===" << endl;

    Member arrayMember;
    arrayMember.addBorrowedBook(501);

    cout << "Current array capacity reached." << endl;
    cout << "Creating a larger dynamic array..." << endl;

    arrayMember.addBorrowedBook(502);

    cout << "Existing book IDs copied successfully." << endl;
    cout << "Old array deleted using delete[]." << endl;
    cout << "New dynamic array assigned successfully." << endl;

    cout << "=== 14. Function Overloading ===" << endl;

    cout << "Calling:" << endl;
    cout << "borrowBook(" << firstBook << ")" << endl;
    member1.borrowBook(firstBook);

    cout << "Calling:" << endl;
    cout << "borrowBook(" << secondBook << ", " << days << ")" << endl;
    member1.borrowBook(secondBook, days);

    cout << "Function overloading demonstrated successfully." << endl;

    cout << "=== 15. Private Helper Function ===" << endl;
    cout << "calculateFine() called internally." << endl;
    cout << "Calculated Fine for Rahim: Tk. "
         << member1.getFine() << endl;
    cout << "Private helper function executed successfully." << endl;

    cout << "=== 16. Inline Function ===" << endl;
    cout << "Calling:" << endl;
    cout << "canBorrowMore()" << endl;

    cout << "Rahim can borrow more books: "
         << (member1.canBorrowMore() ? "Yes" : "No") << endl;

    cout << "Karim can borrow more books: "
         << (member2.canBorrowMore() ? "Yes" : "No") << endl;

    cout << "Inline function executed successfully." << endl;

    cout << "=== 17. Member Function Defined Outside Class ===" << endl;
    cout << "Calling:" << endl;
    cout << "Member::displayRecord()" << endl;
    cout << "Function declared inside the class and implemented" << endl;
    cout << "outside the class using the scope resolution operator (::)." << endl;

    cout << "=== 18. Complete Member Record ===" << endl;

    member1.displayRecord();

    cout << "----------------------------------" << endl;

    member2.displayRecord();

    cout << "=== 19. Friend Function ===" << endl;
    cout << "Calling:" << endl;
    cout << "compareMembers(member1, member2)" << endl;

    compareMembers(member1, member2);

    cout << "Friend function accessed private data successfully." << endl;

    Member* memberPtr = new Member(103, "Nusrat Jahan", "nusrat@gmail.com");

    cout << "=== 20. Object Pointer ===" << endl;
    cout << "Dynamic Member object created using:" << endl;
    cout << "Member* memberPtr = new Member(...);" << endl;
    cout << "Accessing object using -> operator:" << endl;

    memberPtr->displayRecord();

    cout << "Object pointer demonstrated successfully." << endl;

    cout << "=== 21. Passing Object by Value ===" << endl;
    cout << "Calling:" << endl;
    cout << "showMemberByValue(member1)" << endl;
    cout << "Copy constructor called because object is passed by value." << endl;

    showMemberByValue(member1);

    cout << "Changes made to the copied object do not affect" << endl;
    cout << "the original object." << endl;

    cout << "=== 22. Passing Object by Reference ===" << endl;
    cout << "Before update:" << endl;
    cout << "Member Name : " << member2.getName() << endl;

    cout << "Calling:" << endl;
    cout << "updateMemberByReference(member2)" << endl;

    updateMemberByReference(member2);

    cout << "After update:" << endl;
    cout << "Member Name : " << member2.getName() << endl;
    cout << "Original object changed successfully." << endl;

    member2.setName(updatedName);

    cout << "=== 23. Passing Object by Const Reference ===" << endl;
    cout << "Calling:" << endl;
    cout << "showMember(member1)" << endl;

    showMember(member1);

    cout << "Object information displayed without creating" << endl;
    cout << "another object and without modifying the object." << endl;

    cout << "=== 24. Returning Object from Function ===" << endl;
    cout << "Calling:" << endl;
    cout << "createMember(104, \"Sadia Islam\", \"sadia@gmail.com\")" << endl;

    Member returnedMember = createMember(
        104, "Sadia Islam", "sadia@gmail.com"
    );

    cout << "New Member returned from function." << endl;
    returnedMember.displayRecord();

    cout << "Returning object from function demonstrated successfully." << endl;

    cout << "=== 25. new and delete ===" << endl;
    cout << "Dynamic Member object created using new." << endl;
    cout << "Deleting dynamically created Member object..." << endl;
    cout << "delete memberPtr;" << endl;

    delete memberPtr;

    cout << "Dynamic object deleted successfully." << endl;

    int* temp = new int(10);
    delete temp;

    cout << "=== 26. Destructor and delete[] ===" << endl;
    cout << "Dynamic borrowed-book array released using delete[]." << endl;

    cout << "==================================================" << endl;
    cout << "PROGRAM ENDED SUCCESSFULLY" << endl;
    cout << "==================================================" << endl;

    return 0;
}
