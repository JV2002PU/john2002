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
friend ostream& viewlist(ostream& output,Secretary& s);
    ~person(){                                    // oxi testarismeno
    }

    void getcount(){                             //oxi testarismeno
    cout << "count: " << count<< endl;
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
friend ostream& viewlist(ostream& output,Secretary& s) ;

    Secretary(vector<person*>& newdepartment){                                                  //constructor
        department=newdepartment;
    }


    Secretary(Secretary& original){                                                             //copy constructor
        for (const person* p : original.department) {
            department.push_back(new person(*p));
        }
    }

    ~Secretary() {
        for (person* p : department) {
        delete p;
        }                                                                      // destructor-deallocation of memory
    }   

    void addMember(person* newMember) {
        department.push_back(newMember);
    }

    Secretary& operator=(Secretary& rhs){                             //OVERLOAD =
     if(this!= &rhs){
        department = rhs.department;
     }
    return *this;
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
        cout << "Person with the same Name and Surname already exists.";
        }
        else{
            cout<<"person doesnt exist";
        }
    return input;
}

ostream& viewlist(ostream& output,Secretary& s){             //OVERLOAD SECRETARY COUT
    output<< "students and teachers in department:";
    for(person* p :s.department){
        output<<p->Name<<"    "<<p->Surname<<endl;
    }
    return output;
}


Secretary& operator+(Secretary& secretary,person* newMember) {                                          //OVERLOAD + {allaxa apo perso& se person* isos buggarei}
    secretary.addMember(newMember);                                                                       
    return secretary;
}
                



int main(){
    Secretary s1(pliroforiki);
    person p1 ("panos","anas");
    s1=s1+p1;
    viewlist(cout,s1);


return 0;
}