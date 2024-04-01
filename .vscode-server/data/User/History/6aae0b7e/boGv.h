#include <iostream>
#include <string>         // pointer vector logo polumorphismou
#include <vector>
#include <map>
#include <utility> // nomizo gia to pair
#include <fstream> //read txt file
#include <sstream>  // read strings from file file
#include "pan3.cpp"
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