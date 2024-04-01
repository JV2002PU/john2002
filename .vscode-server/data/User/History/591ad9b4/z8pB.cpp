#include <iostream>
#include <vector>
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
    void printcount()  {
        cout << "count: " << count << endl;
    }

};

int person::count = 0; // Initialization of static member

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
    person p1= person("panos", "anastasopoulos");
    person p2= person("panos", "anastasopoulos");
    cin>> p;
    cout<< p;
    p.printcount();
    person p3= person("panos", "anastasopoulos");
    person p4= person("panos", "anastasopoulos");
    p.printcount();

return 0;
}