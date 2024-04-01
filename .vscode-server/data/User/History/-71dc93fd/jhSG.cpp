#include <iostream>
#include <string>
#include <vector>
#include <map>

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
    vector <Student*>  department;                                              //        department=lista
    vector <Professor*> professors;
    vector <Course*>  KatalogosMathimaton;
    static bool xeimerino;                                                             //xeimerino earino examino
    static map<Student*,Course*> grade;                                   // bathmos foititi se mathima    isos xoris *
    static int mandatoryTotal; 
public:
friend class Professor;
friend class Course;
friend class Student;

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

    void newDepartment(){                 //proti entoli p prepei na trexei
        xeimerino=1;
    }
    void CountMand(){                    // upologizei ton arithmo ton upoxreotikon mathimaton
            mandatoryTotal=0;
        for(Course* mathima:KatalogosMathimaton){
            if(mathima->type==0){
                mandatoryTotal++;
            }
            
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



class Student:public person{
    int  CurrentSemester;
    bool eligible=0;
    int ectsSum=0;
    int mandatoryCount;
    vector<Course*> CurrentStuding;
public:
    void SignIn(Course* mathima){                                                   //eggrafi se mathima

        if(mathima->semester%2== Secretary::xeimerino && CurrentSemester>=mathima->semester){
            CurrentStuding.push_back(mathima);
        }
        else{
            cout<<"not currently available"<<endl;
        }
    }

    void CheckMand(Student* foititis){                        //upologizeis posa upoxreotika mathimata exei perasei o foititis
        mandatoryCount=0;
        for(Course* mathima:CurrentStuding){
            if(mathima->type==0 && Secretary::grade[make_pair(foititis, mathima)]>=5 ){
                mandatoryCount++;
            }
        }
    }

    void ectsCount(Student*bathmologoumenos){               //upologismos ects
        ectsSum=0;
        for (Course* mathima : CurrentStuding) {
            if(Secretary::grade[make_pair(bathmologoumenos, mathima)]>=5){
                ectsSum=ectsSum+mathima->ects;
            }
        }
    }
    void MakeEligible(Student* foititis){                      // elegxos ptuxiou
        if (foititis->ectsSum>=240 && foititis->CurrentSemester>=8 && foititis->mandatoryCount==Secretary::mandatoryTotal){
            eligible=1;
            cout<<"eligible to graduate"<<endl;
        }
        else{
            cout<<"not eligible to graduate"<<endl;
        }

    }
};

class Professor: public person{
    vector<Course*> CurrentTeaching;                   
    int bathmos=0;
public:
    void addCourse(Course* mathima){                                        //prosthiki mathimatos p didaskei o kathigitis
        if(mathima)
        CurrentTeaching.push_back(mathima);
    }
    
    void addGrade(Student* bathmologoumenos,Course* mathima){                   // vathmologisi
        int courseFound=0;
        for (Course* course : CurrentTeaching) {                     //elegxos an didaskei to pathima p thelei na bathmologisi
            if (course == mathima) {
                courseFound = 1;
                break;
            }
        }
        if(courseFound==1 && mathima->semester%2== Secretary::xeimerino){                                         //an to didaskei
            cout<<"add"<<bathmologoumenos <<"grade in"<<mathima<<endl;
            cin>>bathmos;
            Secretary::grade[make_pair(bathmologoumenos, mathima)] = bathmos;
        }
        else{                                              // an ekane lathos
            cout<<"not a current course"<<endl;
        }
    }
};

class Course{
    vector<Student*> CurrentStudents;   // osoi exoun eggrafei
    int ects;
    int semester;
    bool type;                //0=mand 1=opt
public:
friend class Professor;
friend class Student;
friend class Secretary;

};