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
    void printcount() const {
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
 
class secretary{
    private:
    vector<person*> lists;

    public:
        secretary(&person){}

        ~Secretary() {
        // Clean up dynamically allocated memory in the vector
        for (Person* p : persons) {
            delete p;
        }
        persons.clear();
        
    }
    void operator+=(Person* p) {
        persons.push_back(p);
    }

    friend istream& operator>>(istream& input, Secretary& secretary) {
        
        return input;
    }
    friend ostream& operator<<(ostream&  output, Secretary& secretary){
        for (const Person* p : secretary.persons) {
            output << *p << std::endl; 
        }
        return output;
    }
} 






int main(){
    person p= person("panos", "anastasopoulos");
    cin>> p;
    cout<< p;
    p.printcount();

return 0;
}