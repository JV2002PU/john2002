#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Secretary;

class person{

string Name;
string Surname;
string BirthDate; 
string PhoneNumber;  
static int  count;                                                                      

public:
    person(){

    }

    person(string name,string surname){
        Name=name;
        Surname=surname;
        BirthDate="unknown";
        PhoneNumber="unknown"; 
        count++;
    }
friend istream& readSecretary(istream& input, Secretary& s);
friend Secretary& operator+(Secretary& secretary ,person& newMember)  ; 
friend std::istream& readperson(std::istream& input, person& p );
friend ostream& operator <<(ostream& output, person& p);

    ~person(){                                    // oxi testarismeno
    }

    void getcount(){                             //oxi testarismeno
    cout << count << endl;
}

};

int person::count = 0;

std::istream& readperson(std::istream& input, person& p ){
    cout << "Enter birthday: ";
    input >> p.BirthDate;
    cout << "Enter PhoneNumber: ";
    input >> p.PhoneNumber;

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

    cout<<endl;

    return output;

}








class Secretary{                                                                                  // υπερφορτωση τελεστη αναθεσης= ευρεση συγκεκριμενου person(?)
    vector <person*> department;                                                                 //gpt         department=lista


public:
friend std::istream& readSecretary(std::istream& input, Secretary& s);
friend Secretary& operator+(Secretary& secretary,person* newMember);
    Secretary(vector<person*>& newdepartment){                                                  //constructor
        department=newdepartment;
    }


    Secretary(Secretary& original){                                                             //copy constructor
            department=original.department;
    }

    ~Secretary() {
        for (person* person : department) {
        delete person;
        }                                                                      // destructor-deallocation of memory
    }   


    

    void addMember(person* newMember) {
        department.push_back(newMember);
    }
};

istream& readSecretary(istream& input, Secretary& s){                             //OVERLOAD CIN
        person tempP;
        cout << "Enter Name: ";
        input >> tempP.Name;
        cout << "Enter Surname: ";
        input >> tempP.Surname;

         bool exists = false;
        for(person* p :s.department){
           
            if (tempP.Name == p->Name && tempP.Surname == p->Surname) {
            exists = true;
            break;
        }

        }
        if (exists) {
        cout << "Person with the same Name and Surname already exists.\n";
         }

        else{
            cout<<"person doesnt exist";
        }
   
    return input;
   
    }


    Secretary& operator+(Secretary& secretary,person* newMember) {                                          //OVERLOAD +            {allaxa apo perso& se person* isos buggarei}
    secretary.addMember(newMember);                                                                       //mas espase ta arxidia as ftiaxo cin cout copy prota
    return secretary;
    }
                
     


 














int main(){
    person p= person("panos", "anastasopoulos");
    readperson(cin, p);
    cout<< p;

return 0;
}