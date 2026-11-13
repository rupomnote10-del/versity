#include <iostream>
#include <string>
using namespace std;

class study{
public:
    string name;
    int roll;
    study(string name, int roll)
    {
        this->name=name;
        this->roll=roll;
    }
};
class work{
public:

    string place;
    int timeof;
    work(string place, int timeof)
    {
        this->place=place;
        this->timeof=timeof;
    }
};
class booth : public study ,public work
{
public:
    int noo;
    booth(string name, int roll, string place, int timeof, int noo) : study(name, roll), work(place, timeof)
    {
        this->noo = noo ;
    }
    void display()
    {
        cout << "Name: " << name << endl << "Roll: " << roll << endl << "Place: " << place << endl << "Time: " << timeof << endl << "No: " << noo << endl;
    }
};
int main()
{
    booth b1("farhan rupom", 184, "dhaka", 12, 01);
    b1.display();
}
