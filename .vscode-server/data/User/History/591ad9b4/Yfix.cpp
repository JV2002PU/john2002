#include <iostream>

using namespace std;


class person{

string Name;
string Surname;
string BirthDate; 
string PhoneNumber; 
string occupation;                                                                       

public:
    person(string name,string surname){
        Name=name;
        Surname=surname;
        BirthDate="unknown";
        PhoneNumber="unknown"; 
        occupation="unknown";


    }
    
friend istream& operator >>(istream& input, person& p );
friend ostream& operator <<(ostream& output, person& p);

};


istream& operator >>(istream& input, person& p ){
    cout << "Enter birthday: ";
    input >> p.BirthDate;
    cout << "Enter PhoneNumber: ";
    input >> p.PhoneNumber;
    cout << "Enter occupation: ";
    input >> p.occupation;

    return input;

}

ostream& operator <<(ostream& output, person& p){
    cout << "Name:";
    output << p.Name;
     cout << "Surname:";
    output << p.Surname;
     cout << "Birthdate:";
    output << p.BirthDate;
     cout << "Phonenumber:";
    output << p.PhoneNumber;
     cout << "Occupation:";
    output << p.occupation;

    return output;
}