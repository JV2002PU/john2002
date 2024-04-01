#include "Secretery.h"
#include <iostream>
#include <string>         // pointer vector logo polumorphismou
#include <vector>
#include <map>
#include <utility> // nomizo gia to pair
#include <fstream> //read txt file
#include <sstream>  // read strings from file file


using namespace std;

class Secretary;
class Course;
class Student;
class Course;
class Professor;


class person{                        
    protected:
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

    void SetBirth(string birthdate){                    // surantisi pou allazei h orizei birthdate
        BirthDate=birthdate;
    }

    void SetPhone(string phone){                    // surantisi pou allazei h orizei arithmo thlefonou
        PhoneNumber=phone;
    }
    
    void setSname(string name,string surname){ // epitrepei na allaxoume to name kai surname enos person
        cout<< "please enter new name(cancel if name correct)"<< endl;
        cin>>name;
        if(name!="cancel")
            Name=name;
        cout<<"please enter new Surname(cancel if Surname correct)"<<endl;
        cin>>surname;
        if(surname!="cancel")
            Surname=surname;
    }

    void getSname(){ // ektuponei to name kai surname enos person
        cout<< this->Name<< "  "<< this->Surname<< endl;
    }
};

class Course{
    string Name;
    int Ects,Code;
    int Semester;
    bool Type;                //0=mandatory, 1=optional
    int Pass=0, Cut=0;
    public:
    friend class Professor;
    friend class Student;
    friend class Secretary;
        Course(string name){
            Name=name;
        }
        Course(Course& course){      //copy constructor
            Name = course.Name;
            Ects = course.Ects;
            Semester = course.Semester;
            Type = course.Type;
            Code = course.Code;
            Pass = course.Pass;
            Cut = course.Cut;
        }

        
        ~Course(){
        }

        void SetEcts(int ects){          //write a courses ects
            Ects=ects;
        }

        void SetSemester(int semester){            //set a courses semester
            if(semester<=8)                    //8 examina uparxoun sto sxoli
                Semester=semester;
            else
            cout<< "Invalid semester"<< endl;  //an dothei megaluteros arithmos
        }

        void SetType(bool type){                //set a courses type
            if(type!=0 || type!=1)              //0 gia mandatory kai 1 gia optional otidipote allo einai invalid
                cout<< "invalid type"<<endl;
            else
            this->Type=type;
        }
        void SetCode(int code){       //write courses code
            Code=code;
        }

        int GetCode(){    //read courses code
            return Code;
        }
        void WriteCourseFile(ostream& file){                //write courses info in file
            file<< Name <<" "<< Ects <<" "<< Semester <<" "<< Type << endl;
        }
        void GotCut(){        //count how many students got cut in this course this semester
            this->Cut++;
        }
        void GotPass(){     //count how many students passed  this course this semester
            this->Pass++;
        }
        void InitStats(){  // initialise stats each semester
            this->Pass=0;
            this->Cut=0;
        }
};
class Student:public person{
    int AM;             
    int CurrentSemester;
    bool eligible=0;
    int ectsSum=0;
    int mandatoryCount;
    vector<Course*> AllStuding;   //lista olon ton mathimaton
    vector<Course*> CurrentSemesterList; // lista mathimaton parontos examinou (prepei na diagrafei me to neo examino)
    static int lastAm;                   //records the last am given to a person
    public:
        Student(string name,string surname) : person(name,surname){    //student constructor

        }
        
        Student(Student& student){      //copy constructor
            Name = student.Name;
            Surname = student.Surname;
            BirthDate = student.BirthDate;
            PhoneNumber = student.PhoneNumber;
            AM = student.AM;
            
            for(Course* course:student.CurrentSemesterList){        //gia kathe course p parakolouthei auto to examino
                CurrentSemesterList.push_back(new Course(*course));// antegrapse to sti nea lista
            }
            for(Course* course:student.AllStuding){        //gia kathe course p exei parakolouthisei ola to examina
                AllStuding.push_back(new Course(*course));// antegrapse to sti nea lista
            }
        }
        void GiveNewAm(){
            this->AM=lastAm;
        }

        void WriteStudentFile(ofstream& file){
            file << Name <<" " << Surname <<" "<< BirthDate <<" "<< PhoneNumber<<" "<< CurrentSemester<<" "<< eligible<<" "<<ectsSum<<endl; // writ student info in file
        }
        void SignIn(Course* mathima){                  // student signs for  course and adds it in current studying

            if(mathima->Semester%2== Secretary::GetXeimerino() && CurrentSemester>=mathima->Semester){       //checks if student can sign in this course based on Semester and year of study
                AllStuding.push_back(mathima);  //add to all time list
                CurrentSemesterList.push_back(mathima);//add to current semester list
            }
            else{                                               //in case he cant sign for this course
                cout<<"not currently available"<<endl;
            }
        }
        void addSemester(){  //when new semester begins increase current semester by 1
            CurrentSemester=CurrentSemester++;
        }
        void CheckMand(){                        //upologizeis posa upoxreotika mathimata exei perasei o foititis
            mandatoryCount=0;
            for(Course* mathima:AllStuding){
                if(mathima->Type==0 && Secretary::grade[std::make_pair(this, mathima)]>=5 ){   //checks if a course ia mand and if the grade of the student is sufficient
                    mandatoryCount++;
                }
            }
        }

        void ectsCount(){               //upologismos ects
            ectsSum=0;
            for (Course* mathima : AllStuding) {
                if(Secretary::grade[std::make_pair(this, mathima)]>=5){      //gives courses ects to student if grade >5 this
                    ectsSum=ectsSum+mathima->Ects;
                }
            }
        }
        void MakeEligible(){                      // elegxos ptuxiou
            CheckMand();
            if (this->ectsSum>=240 && this->CurrentSemester>=8 && this->mandatoryCount==Secretary::mandatoryTotal){ //check if student suuficient ects ,mand courses and if he has studied enough years
                eligible=1;
                cout<<"eligible to graduate"<<endl;         // if he can graduate
            }
            else{
                cout<<"not eligible to graduate"<<endl;     //if he cant
            }
        }
        void SetAm(int am){ //write student am
            string answer;
            cout << "do you want to assign a new am(yes/no) "<< endl;
            cin>> answer;
            if (answer=="yes"){        //if its a new student with a new am use the static lastAm as input
                am++;
                AM=am;
            }
            else{                           // if we made a typo  when setting am in this case input am should be the correct one
                AM=am;
            } 
            
        }
        int GetAm(){ //read am
            return AM;
        }
        void printGrade(){
            string answer;
            cout<<"do you want to print all  grades or this semester(all/semester)"<<endl;
            cin>>answer; //choose what to print
            if(answer=="all"){ //if you want to print all of your grades
                for(Course* course: AllStuding){        //koitaei kathe mathima p exei parakolouthisei o foititis
                    if(Secretary::grade[std::make_pair(this, course)]>=5){ //an o bathmos tou mathimatos einai pano apo 5
                        cout<< "printings all grades :"<<endl;
                        cout<< course << " grade is:"<< Secretary::grade[std::make_pair(this, course)] << endl; //printing
                    }
                }
            }else if(answer=="semester"){   //if you want to print only this semesters grades
                for (Course* course:CurrentSemesterList){ //koitaei kathe mathima p exei parakolouthisei o foititis auto to examino
                    if(Secretary::grade[std::make_pair(this, course)]>=5){
                        cout<< "printings all grades for this semester:"<<endl;
                        cout<< course << " grade is:"<< Secretary::grade[std::make_pair(this, course)] << endl; //printing
                    }
                }
            }else{  //incase user doesnt give a valid answer
                cout<<"invalid answer"<<endl;
            }
        }
        void ClearList(){                   //lista mathimaton gia stats autou tou examinou
            this->CurrentSemesterList.clear();  //ekkatharisi listas gia kathe neo examino
        }
        ~Student(){                             // destructor
            for (Course* course : AllStuding) {               
            }AllStuding.clear();
            for (Course* course : CurrentSemesterList) {               
                delete course;
            }CurrentSemesterList.clear();
        }    
};

class Professor: public person{
    vector<Course*> CurrentTeaching;  
    int Key;

    public:
    Professor(Professor& prof){      //copy constructor
        Name = prof.Name;
        Surname = prof.Surname;
        BirthDate = prof.BirthDate;
        PhoneNumber = prof.PhoneNumber;
        Key= prof.Key;
        
        for(Course* course:prof.CurrentTeaching){        //gia kathe course p didaskei o prof
            CurrentTeaching.push_back(new Course(*course));// antegrapse to sti nea lista
        }
    }
    Professor(string name,string surname): person(name,surname){
    }
    void addCourse(Course* mathima){                                        //prosthiki mathimatos p didaskei o kathigitis
        CurrentTeaching.push_back(mathima);
    }
    
    void StopTeaching(int code) {          
        for (auto it = CurrentTeaching.begin(); it != CurrentTeaching.end(); ++it) {  //xekinaei na anazita sti lista apo tin arxi os to telos
            if ((*it)->GetCode() == code) {               //an brei kapoio Course me idio code
                delete *it;                             // to diagrafei
                CurrentTeaching.erase(it);              //kai afairei to pointer apo to vector
                break;                                 //telos brogxou
            }
        }
    }

    void SetKey(int key){   //write key
        Key=key;
    }

    int GetKey(){   //read key
        return Key;
    }
    void WriteProfFile(ofstream& file){                                                         //write professor info in file
         file << Name <<" " << Surname <<" "<< BirthDate <<" "<< PhoneNumber<<endl;

    }
    void addGrade(Student* bathmologoumenos,Course* mathima){                   // vathmologisi
        int courseFound=0;
        int bathmos;
        for (Course* course : CurrentTeaching) {                     //elegxos an didaskei to pathima p thelei na bathmologisi
            if (course->GetCode() == mathima->GetCode()) {      //me basi to code tou mathimatos
                courseFound = 1;
                break;                                      //break an to brei
            }
        }
        if(courseFound==1 && mathima->Semester%2== Secretary::GetXeimerino()){          //an to didaskei
            cout<<"add"<<bathmologoumenos <<"grade in"<< mathima<<endl;       
            cin>>bathmos;                                 //write student grade
            Secretary::grade[std::make_pair(bathmologoumenos, mathima)] = bathmos;   //kataxorisi bathmou
        }
        else{                                              // an ekane lathos
            cout<<"not a current course"<<endl;
        }
    }
    void printStats(){         //print professor current semester's courses  success rates
        float success;
        for (Course* course: CurrentTeaching){  // checkarei kathe mathima pou o kathigitis didaskei
            success=course->Pass/(course->Pass+course->Cut);   //upologismos posostou epituxias
            
            if(course->Semester%2==Secretary::GetXeimerino()){  //elegxei an to didaskei auto to examino
                cout<< "success rate in "<<course << " for this semester is " << success<< endl;  //message printed 
            }
        }
    }
    
    ~Professor(){  //prof destructor
        for(Course* course:CurrentTeaching){
            delete course;
        }CurrentTeaching.clear();
    }

};







int main() { 
    vector<Student*> studentList;
    vector<Professor*> profList;
    vector<Course*> courseList;

    Secretary secretary(studentList, profList, courseList);

    return 0;
}

