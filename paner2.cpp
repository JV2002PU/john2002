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
static int  count;                  //metraei posa object person exoun dimiourgithei                                                    

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

friend istream& readSecretary(istream& input, Secretary& s);                    //filikes sunartiseis
friend Secretary& operator+(Secretary& secretary ,person& newMember)  ; 
friend std::istream& readperson(std::istream& input, person& p );
friend ostream& operator <<(ostream& output, person& p);
friend ostream& viewlist(ostream& output,Secretary& s);
    ~person(){                                    
    }

    void getcount(){                                   //sunartisi pou kaleitai gia na kanei print to count
    cout << "person count is " << count<< endl;
}

};

int person::count = 0;                               //arxikopoiisei count

std::istream& readperson(std::istream& input, person& p ){                 //dinei tis upoloipes plirofories tou person
    cout << "Enter birthday: ";
    input >> p.BirthDate;
    cout << "Enter PhoneNumber: ";
    input >> p.PhoneNumber;

    return input;

}

ostream& operator <<(ostream& output, person& p){                    //ektuponei tis plirofories tou person
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


class Secretary{                                                              // υπερφορτωση τελεστη αναθεσης= ευρεση συγκεκριμενου person(?)
    vector <person*> department;                                              //        department=lista

public:
friend std::istream& readSecretary(std::istream& input, Secretary& s);
friend Secretary& operator+(Secretary& secretary,person* newMember);
friend ostream& viewlist(ostream& output,Secretary& s) ;

    Secretary(vector<person*>& newdepartment){                                 //constructor
        department=newdepartment;
    }


    Secretary(Secretary& original){                                             //copy constructor
        for ( person* p : original.department) {
            department.push_back(new person(*p));
        }
    }

    ~Secretary() {                                                                  // destructor-deallocation of memory
        for (person* p : department) {
        delete p;
        }                                                                      
    }   

    void addMember(person* newMember) {                               //sunartisi pou  prostheti neo melos ston katalogo
        department.push_back(newMember);
    }

    Secretary& operator=(Secretary& rhs){                                      //OVERLOAD = an theloume na antigrapsoume ena uparxon secretary se ena uparxo secretary
     if(this!= &rhs){
        department = rhs.department;
     }
    return *this;
    }
};

istream& readSecretary(istream& input, Secretary& s){                             //OVERLOAD CIN oste na anazitei ena sugkekrimeno atomo
        person tempP;                                                             //dimiourgia antikeimenou person gia na to exoume os metro sugkrisis
        cout<<"looking for person"<<endl;
        cout << "Enter Name: ";
        input >> tempP.Name;
        cout << endl<<"Enter Surname: ";
        input >> tempP.Surname;

         bool exists = false;                                                //false an dn upaxei - true an uparxei
        for(person* p :s.department){
            if (tempP.Name == p->Name && tempP.Surname == p->Surname) {
            exists = true;
            break;
            }
        }
        if (exists==true) {
        cout <<endl<< "Person with the same Name and Surname exists."<<endl;
        }
        else{
            cout<<endl<<"person doesnt exist"<<endl;
        }
    return input;
}

ostream& viewlist(ostream& output,Secretary& s){             //OVERLOAD SECRETARY COUT oste na deixnei ola ta onomata tou katalogou
    output<< "students and teachers in department:";
    for(person* p :s.department){
        output<<p->Name<<"    "<<p->Surname<<endl;
    }
    return output;
}


Secretary& operator+(Secretary& secretary,person* newMember) {              //OVERLOAD +  oste na kalei tin addmember
    secretary.addMember(newMember);                                                                       
    
    
    return secretary;
}
                



int main() {
    vector<person*> list1,list2,list3;           //dimiourgountai ta vectors dn eimai sigouros gt itan problima teleutaias stigmis
    
    Secretary di1(list1);                       //constructor secretary
    Secretary di2(list2);
    Secretary di3(list3);

    person p("John", "Doe");                     //constructor person
    person p1("nikos","papas");
    person p2("dimitris","gkikas");
    readperson(cin,p1);                         //kaleitai i readperson 
    cout<<p1;                                   //ektuponontai ta elements tou p1
    
    di2 = di1 + &p;                              //prostithetai person ston katalogo tis sxolis
    viewlist(cout, di2);                        //blepoume ton katalogo tis sxolis

    di3 = di2 + &p1 +&p2;                      //omoios alla me pio polla stoixeia
    viewlist(cout, di3);

    readSecretary(cin,di3);                    //anazitisi atomou ston katalogo ebala duo gia na einai ena true ena false
    readSecretary(cin,di3);
    
    p.getcount();                               //ektuponei to count
    return 0;
}