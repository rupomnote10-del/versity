#include <iostream>
#include <string>
using namespace std;

class Book{
private:
    int bookID;
    string bookTitle;
    string authorName;
    double price;
public:
    string type;

    Book(int id, string title, string name, double pri)
    {
        bookID = id;
        bookTitle = title;
        authorName = name;
        price = pri;
        type = "Original";
    }
    void displaybook()
    {
        cout << type << " Book: " << endl << "Book ID : " << bookID << endl;
        cout << "Book Title : " << bookTitle << endl;
        cout << "Author : " << authorName << endl;
        cout << "Price : Tk. " << price << endl << endl;
    }
};

class Member{
private:
    int memberID;
    string memberName;
    string memberEmail;
    int* borrowedBookIDs;
    int borrowedCount;
    int capacity;
    double totalFine;

    void calculateFine()
    {
        totalFine = (totalFine/(borrowedCount-1))*borrowedCount;
    }
public:
    Member()
    {
        memberID = 0 ;
        memberName = "Unknown" ;
        memberEmail =  "Not Assigned" ;
        borrowedCount = 0 ;
        totalFine = 0 ;
        capacity = 2 ;
        borrowedBookIDs = new int[capacity];
        cout << "Default constructor called." << endl << endl ;
    }

    Member(int id, string name);

    Member(int id, string name, string email)
    {
        memberID = id ;
        memberName = name ;
        memberEmail = email ;
        borrowedCount = 0 ;
        capacity = 2 ;
        totalFine = 0 ;
        borrowedBookIDs = new int[capacity];
        cout << "Parameterized constructor called." << endl<< endl ;
    }
    Member(Member& other)
    {
        memberID = other.memberID ;
        memberName = other.memberName ;
        memberEmail =  other.memberEmail ;
        borrowedCount = other.borrowedCount ;
        totalFine = other.totalFine ;

        capacity = other.capacity ;
        borrowedBookIDs = new int[capacity];
        for (int i=0; i<borrowedCount; i++)
        {
            borrowedBookIDs[i]= other.borrowedBookIDs[i];
        }
    }
    Member(Member&& other)
    {
        memberID = other.memberID ;
        memberName = other.memberName ;
        memberEmail =  other.memberEmail ;
        borrowedCount = other.borrowedCount ;
        totalFine = other.totalFine ;
        borrowedBookIDs= other.borrowedBookIDs;
        capacity = other.capacity ;

        other.borrowedBookIDs = new int[capacity];
        other.capacity = 0;
        other.borrowedCount = 0;
        other.memberID = 0;
    }

    string getName() const
    {
        return memberName;
    }

    string getEmail() const
    {
        return memberEmail;
    }

    void setName(string memberName)
    {
        this->memberName = memberName;
    }

    void setEmail(string memberEmail)
    {
        this->memberEmail = memberEmail;
    }

    Member& operator=(const Member& other)
    {
        if(this != &other)
        {
            int* newArray = new int[other.capacity];
            for(int i = 0; i < other.borrowedCount; i++)
            {
                newArray[i] = other.borrowedBookIDs[i];
            }

            delete[] borrowedBookIDs;
            memberID = other.memberID;
            memberName = other.memberName;
            memberEmail = other.memberEmail;
            borrowedCount = other.borrowedCount;
            capacity = other.capacity;
            totalFine = other.totalFine;
            borrowedBookIDs = newArray;
        }
        cout << "Copy assignment operator called." << endl<< endl ;
        return *this;
    }

    void addBorrowedBook(int bookID)
    {
        if(borrowedCount == capacity)
        {
            capacity = capacity*2;
            int* borrowedcopy = new int [capacity];

            for(int i=0; borrowedCount>i; i++)
            {
                borrowedcopy[i]= borrowedBookIDs[i];
            }
            delete[] borrowedBookIDs;

            borrowedBookIDs = borrowedcopy;
            cout << "Array capacity has increased..." << endl;
        }
        borrowedBookIDs[borrowedCount] = bookID;
        borrowedCount++;
        cout << "Book id: " << bookID << " has added..." << endl<<endl;
    }

    void borrowBook(int bookID)
    {
        addBorrowedBook(bookID);
        cout << "Default borrowing period used..." << endl<<endl;
        calculateFine();
    }

    void borrowBook(int bookID, int numberOfDays)
    {
        addBorrowedBook(bookID);
        cout << "Default borrowing period used..." << endl<<endl;
        if (numberOfDays > 7)
        {
            totalFine += (numberOfDays - 7) * 10;
        }
        calculateFine();
    }

    inline bool canBorrowMore() const
    {
        return borrowedCount < 5;
    }

    void displayRecord() const;

    friend void compareMembers(const Member& m1,const Member& m2);

    ~Member()
    {
        delete[] borrowedBookIDs;
        cout << "Destructor called for Member ID: " << memberID << endl<<endl;
    }
};

    Member::Member(int id, string name)
    {
        memberName = name;
        memberID = id;
        memberEmail = "Not Assigned";
        borrowedCount = 0;
        capacity = 2;
        totalFine = 0;
        borrowedBookIDs = new int [capacity];
        cout << "Parameterized constructor called..." << endl<<endl;
    }
    void updateMemberByReference(Member& m)
    {
        m.setName("Farhan Rupom Updated");
    }

    void showMember(const Member& m)
    {
        cout << "Member ID and Name are displayed." << endl;
        cout << "Name: " << m.getName() << endl<<endl ;
    }
    Member createMember(int id, string name, string email)
    {
        Member temp(id, name, email);
        return temp;
    }

    void Member::displayRecord() const
    {
        cout << "Member ID : " << memberID;
        cout << "\nMember Name : " << memberName;
        cout << "\nMember Email : " << memberEmail;
        cout << "\nBorrowed Books : " ;

        for (int i=0; i< borrowedCount; i++)
            cout << borrowedBookIDs[i] << " ";

        cout << "\nNumber of Books : " << borrowedCount;
        cout << "\nTotal Fine : Tk. " << totalFine;
        cout << "\nCan Borrow More : " ;

        if(borrowedCount<capacity)
            cout << "Yes\n\n";
        else
            cout << "No\n\n";
    }
    void compareMembers(const Member& m1, const Member& m2)
    {
        cout << m1.memberName << " borrowed " << m1.borrowedCount << " book's" << endl ;
        cout << m2.memberName << " borrowed " << m2.borrowedCount << " book's" << endl ;
        if (m1.borrowedCount == m2.borrowedCount)
        {
            cout << "Both of them has borrowed same number of books." << endl;
        }
        else if (m1.borrowedCount > m2.borrowedCount)
        {
            cout << m1.memberName <<" has borrowed more books." << endl ;
        }
        else
        {
            cout << m2.memberName <<" has borrowed more books." << endl ;
        }
        cout << "Friend function is called..." <<endl<< endl ;
    }
    void showMemberByValue(Member m)
    {
        cout << "Member received by value:" << endl << "Name: " << m.getName() <<endl<<endl;
    }

    int main()
    {
        Book b1(501, "Object Oriented Programming", "SASA SASA", 175);
        Book b2 = b1;
        b1.displaybook();
        cout << "Copied Book:" << endl;
        b2.displaybook();

        Member m0;
        m0.displayRecord();

        Member m1(101, "Farhan Rupom");
        Member m2(102, "Sasa SWAN", "swanbird@gmail.com");
        m1.setEmail("rupom@gmail.com");
        m1.displayRecord();
        m2.displayRecord();

        m2.setName("Swan SASA");
        m2.setEmail("itssasa@gmail.com");
        cout << "Updated Name: " << m2.getName() << endl << "Updated Email: " << m2.getEmail() << endl;

        m1.borrowBook(501);
        m1.borrowBook(502, 10);
        m1.borrowBook(503, 8);
        m1.borrowBook(504);
        m1.borrowBook(505);
        m1.displayRecord();

        Member m3(m1);
        m3.displayRecord();

        Member m4(std::move(m3));
        m4.displayRecord();

        Member m5;
        m5 = m2;
        m5.displayRecord();

        cout << "Can Sasa borrow more books? ";
        cout << (m1.canBorrowMore() ? "Yes" : "No") << endl;
        m2.displayRecord();

        compareMembers(m1, m2);

        Member* memberPtr = new Member(103, "IDk who", "who@gmail.com");
        memberPtr->borrowBook(601);
        memberPtr->displayRecord();
        delete memberPtr;

        showMemberByValue(m2);
        cout << "Before : " << m2.getName() << endl;
        updateMemberByReference(m2);
        cout << "After : " << m2.getName() << endl;
        showMember(m1);

        Member m6 = createMember(104, "whooo twotwo", "whootwo@gmail.com");
        m6.displayRecord();

        cout << "\nProgram ended successfully." << endl;
        return 0;
    }
