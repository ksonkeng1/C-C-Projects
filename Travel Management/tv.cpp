#include<iostream>
#include<fstream>
#include<iomanip>
#include<windows.h>
using namespace std;


class Customers {
    public:
    string name, gender, address;
    int age, mobileNo, cusID;


    void getDetails() {

        ofstream out("old-customers.txt", ios::app);
        cout << "Enter customer ID: ";
        cin >> cusID;
        cout << "Enter customer Name: ";
        cin >> name;
        cout << "Enter customer Age: ";
        cin >> age;
        cout << "Enter customer Mobile Number: ";
        cin >> mobileNo;
        cout << "Enter customer Address: ";
        cin >> address;
        cout << "Enter customer Gender: ";
        cin >> gender;

    }

    void showDetails() {

    }

};

class Cabs {

};


class Booking {

};


class Charges {

};








int main() {

};