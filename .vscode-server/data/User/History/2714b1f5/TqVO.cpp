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

}
class Secretary{                                                              
    vector <Student*>  StudentList;                                              // 
    vector <Professor*> ProfList;
    vector <Course*>  CourseList;
    static bool xeimerino;                                                             //xeimerino earino examino
    static map<pair<Student*,Course*>,  int> grade;                                   // bathmos foititi se mathima    isos xoris *
    static int mandatoryTotal;

    public:
    friend class Professor;
    friend class Course;
    friend class Student;

        Secretary(vector<Student*>& newstudentlist,vector<Professor*>& newproflist,vector<Course*>& newcourselist){                                 //constructor
            newDepartment();

            ifstream StudentFile("student.txt");                //opens file                               
            try{
                if (!StudentFile.is_open()) {                   //checks if file is open and throw exception if not
                    throw "Failed to open file";
                }else {
                    string line;
                    while (getline(StudentFile, line)) {    // Read each line from  file          
                        istringstream studentfile(line);                          
                        string name, surname, birthDate, phoneNumber;     
                        int CurrentSemester,eligible,ectsSum,am;

                        studentfile >> name >> surname >> birthDate >> phoneNumber >> CurrentSemester >> eligible >> ectsSum >> am  ;   //seperates values based on whitespaces wth >>

                        Student newStudent(name, surname);               //creates a student object
                        newStudent.SetBirth(birthDate);                   //set birth and phone
                        newStudent.SetPhone(phoneNumber);
                        newStudent.SetAm(am);
                        StudentList.push_back(new Student(newStudent));    //add a pointer to the student in the vector
                    }
                    StudentFile.close();                                 //close file
                }
                }catch(const char* txtmessage){                         //catch exception
                    cout<<txtmessage<<endl;                             //print exception message
                }


            ifstream ProfessorFile("professor.txt");     //open file
            try{
                if (!ProfessorFile.is_open()) {          //checks if file is open and throw exception if not
                    throw "Failed to open file";
                }else {
                    string line;
                    while (getline(ProfessorFile, line)) {  // Read each line from  file
                        istringstream professorfile(line);
                        string name, surname, birthDate, phoneNumber;
                        int key;
                        professorfile >> name >> surname >> birthDate >> phoneNumber>>key;        //seperates values based on whitespaces wth >>

                        Professor newProfessor(name, surname);           //creates a professor object
                        newProfessor.SetBirth(birthDate);               //set birth and phone
                        newProfessor.SetPhone(phoneNumber);
                        newProfessor.SetKey(key);
                        ProfList.push_back(new Professor(newProfessor));         //add a pointer to the professor in the vector
                    }
                    ProfessorFile.close();                 //close file
                }
            }catch(const char* txtmessage){                   //catch exception
                cout<<txtmessage<<endl;                     //print exception message
            }

            ifstream CourseFile("course.txt");         //open file
            try{
                if (!CourseFile.is_open()) {        //checks if file is open and throw exception if not
                    throw "Failed to open file";
                }else {
                    string line;
                    while (getline(CourseFile, line)) {     // Read each line from file
                        istringstream coursefile(line);
                        string name;
                        int ects, semester,code;
                        bool type;

                        coursefile >> name >> ects >> semester >> type>>code;         //seperates values based on whitespaces wth >>

                        Course newCourse(name);         //creates a course object
                        newCourse.SetEcts(ects);        //set ects , semester and type
                        newCourse.SetSemester(semester);
                        newCourse.SetType(type);
                        newCourse.SetCode(code);
                        CourseList.push_back(new Course(newCourse));    //add a pointer to the course in the vector 
                    }

                
                CourseFile.close();           //close file
                }
            }catch(const char* txtmessage){         //catch exception
                cout<<txtmessage<<endl;                  //print exception message
            }

            
        }
        
        void StoreData(){    //apothikeuei sto txt tA dedomena mas meta tis allages mas
            ofstream StudentFile( "student.txt",ios::trunc);          //open file in trunc mode
            try{
                if (!StudentFile.is_open()){                 //if  file hasnt opened throw an exception
                    throw "failed to open file";
                }else{
                    for(Student* newStudent:StudentList){           //  for each student in the list
                        newStudent->WriteStudentFile(StudentFile);  //  write his info
                    }
                    StudentFile.close();                           //close file
                }
            }catch(const char* txtmessage){                       //catch exception
                cout<<txtmessage<<endl;                           //catch exception
            }

            ofstream professorfile( "professor.txt",ios::trunc);   //open file in trunc mode
            try{
                if (!professorfile.is_open()){                  //if  file hasnt opened throw an exception
                    throw "failed to open file";
                }else{
                    for(Professor* newProfessor:ProfList){               //for each professor in the list
                        newProfessor->WriteProfFile(professorfile);      //write his info
                    }
                    professorfile.close();                 //close file
                }
            }catch(const char* txtmessage){         //catch exception
                cout<<txtmessage<<endl;                //print exception message
            }

            ofstream coursefile( "course.txt",ios::trunc);     //open file in trunc mode
            try{
                if (!coursefile.is_open()){                      //if  file hasnt opened throw an exception
                    throw "failed to open file";
                }else{
                    for(Course* newCourse:CourseList){              //for each course in the list
                        newCourse->WriteCourseFile(coursefile);     //write its info
                    }
                    coursefile.close();                    //close file
                }
            }catch(const char* txtmessage){             //catch exception
                cout<<txtmessage<<endl;                 //print exception message
            }



        }

        Secretary(Secretary& original){                                             //copy constructor
        }

        ~Secretary() {                                                                  // destructor-deallocation of memory                    
            for (Student* student : StudentList) {               //for students
                delete student;
            }
            StudentList.clear();
            for (Professor* professor : ProfList) {              //for professors
                delete professor;
            }
            ProfList.clear();
            for (Course* course : CourseList) {                  //for courses
                delete course;
            }
            CourseList.clear();                            
        }   

        void newDepartment(){                 //proti entoli p prepei na trexei otan ftiaxnoume ena neo tmima
            xeimerino=1;
        }
        void CountMand(){                    // upologizei ton arithmo ton upoxreotikon mathimaton tou tmimatos
                mandatoryTotal=0;
            for(Course* mathima:CourseList){
                if(mathima->Type==0){
                    mandatoryTotal++;
                }  
            }
        }

        void NextSemester(){             //enarxi neou  examinou exei douleia akoma
            if(xeimerino==1){            //allagi tou apo earino se xeimerino kai antistrofa
                xeimerino=0;
            }else
                xeimerino=1;

            for(Student* student:StudentList){    //auxanei to current semester ton foititon kata 1 kaikanei clear ti list ton mathimaton autou tou examinou
                student->addSemester();
                student->ClearList();
            }
            for(Course* course:CourseList){   //kanei intialise ta stats tou kathe mathimatos
                course->InitStats();
            }

                
        }

        void addStudent() {                               //sunartisi pou  prostheti neo melos ston katalogo thelei douleia
            string name,surname;
            cout<<"Enter student name"<<endl;
            cin>>name; //dinoume to onoma
            cout<<"Enter student surname"<<endl;
            cin>>surname;    //dinoume to surname
            Student newStudent(name,surname);  //constructor
            newStudent.GiveNewAm();     // pername to am sto object
            StudentList.push_back(new Student(newStudent)); //pername pointer sto vextor dynamika
        }
        void removeStudent(int am) {
            for (auto it = StudentList.begin(); it != StudentList.end(); ++it) {  //xekinaei na anazita sti lista apo tin arxi os to telos
                if ((*it)->GetAm() == am) {               //an brei kapoio student me idio am
                    delete *it;                             // to diagrafei
                    StudentList.erase(it);                  //kai afairei to pointer apo to vector
                    break;                                    //telos brogxou
                }
            }
        }

    void addProf(Professor prof){      //prosthetoume neoprof sti lista opos akrivos kai sto student
        string name,surname;
        int key;
        cout<<"Enter professor name"<<endl;
        cin>>name;
        cout<<"Enter professor surname"<<endl;
        cin>>surname; 
        cout<<"Enter professor key"<<endl;
        cin>>key;
        Professor newProfessor(name,surname);
        newProfessor.SetKey(key);
        ProfList.push_back(new Professor(newProfessor));
    }

    void removeProf(int key){  //afairei prof opos akrivos me to student
        for (auto it = ProfList.begin(); it != ProfList.end(); ++it) {
            if ((*it)->GetKey() == key) {
                delete *it;  
                 ProfList.erase(it);
                break; 
            }
        }
    }

    void addCourse(Course course){  // prosthetei ena course sto vector opos akrivos me to student
        string name;
        int code;
        cout<<"Enter Course name"<<endl;
        cin>>name; 
        cout<<"Enter Course code"<<endl;
        cin>>code;
        Course newCourse(name);
        newCourse.SetCode(code);
        CourseList.push_back(new Course(newCourse));
    }

    void removeCourse(int code){ //afairei ena course apo to  vector opos akrivos me to student
        for (auto it = CourseList.begin(); it != CourseList.end(); ++it) {
            if ((*it)->GetCode() == code) {
                delete *it;  
                 CourseList.erase(it);
                break;  
            }
        }
    }

    void printEligible(){             //prints if each student is eligible to graduate
        for(Student* student:StudentList){         //checkarei kathe student sto vector 
            student->getSname();                     //print his name and surname
            cout<< " with am " << student->GetAm()<< " is "; 
            student->MakeEligible();   //prints wether he can graduate
        }
    }    
    static bool GetXeimerino(){
        return xeimerino;
    }
    void WritePass(Course* course){
        for(Student* student:StudentList){
            if( grade[std::make_pair(student, course)]>=5){
                //write names in a file
            }
        }
    }




};
int main() { 
    vector<Student*> studentList;
    vector<Professor*> profList;
    vector<Course*> courseList;

    Secretary secretary(studentList, profList, courseList);

    return 0;
}

