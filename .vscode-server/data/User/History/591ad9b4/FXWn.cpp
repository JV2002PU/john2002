#include <iostream>

using namespace std;


class person{

string Name;
string Surname;
string BirthDate; 
string PhoneNumber; 
string occupation;  
static int count;                                                                     

public:
    person(string name,string surname){
        Name=name;
        Surname=surname;
        BirthDate="unknown";
        PhoneNumber="unknown"; 
        occupation="unknown";
        count++;


    }
    
friend istream& operator >>(istream& input, person& p );
friend ostream& operator <<(ostream& output, person& p);
friend int getcout();


};


int person.count = 0; // Initialization of static member

int getcount() { // Definition of getcount function
    return person::count;
}

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
     cout << endl<<  "Surname:";
    output << p.Surname;
     cout << endl<<"Birthdate:";
    output << p.BirthDate;
     cout << endl<<"Phonenumber:";
    output << p.PhoneNumber;
     cout << endl<<"Occupation:";
    output << p.occupation;
    cout<<endl;

    return output;

}
 

int main(){
    person p= person("panos", "anastasopoulos");
    cin>> p;
    cout<< p;
    cout << "Count: " << getcount() << endl;

return 0;
}