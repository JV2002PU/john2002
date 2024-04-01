#include <iostream>
#include <string>         // pointer vector logo polumorphismou
#include <vector>
#include <map>
#include <utility> 
#include <fstream> //read txt file
#include <sstream>
#include "Person.h"
#include "Student.h"
#include "Professor.h"
#include "Course.h"
#include "Secretary.h"


    bool Secretary::xeimerino;                              //xeimerino earino examino
    std::map<std::pair<int,int>,  int> Secretary::grade;    //<AM,CODE=grade> bathmos foititi se mathima
    std::multimap<int,int> Secretary::AllSigned;            //<AM->CODE>kanei associate to AM student me  ta code ton mathimaton p exei dilosei All time
    std::multimap<int,int> Secretary::SemesterSigned;    //<AM->CODE>kanei associate to AM student me ta code ton mathimaton p exei parakoloutisei auto to semester
    std::multimap<int,int> Secretary::AllTeaching;          //<Key->Code> kanei associate to Key professor me ta code ton mathimaton p exei didaxei All time
    int Secretary::mandatoryTotal;  

    Secretary::Secretary(std::vector<Student*>& newstudentlist,std::vector<Professor*>& newproflist,std::vector<Course*>& newcourselist){  //constructor
        std::ifstream StudentFile("student_list.txt");                //opens file                               
        try{
            if (!StudentFile.is_open()) {                   //checks if file is open and throw exception if not
                throw "Failed to open file";
            }else {
                std::string line;
                while (getline(StudentFile, line)) {    // Read each line from  file 

                    std::istringstream studentfile(line);                          
                    std::string name, surname, birthDate, phoneNumber;     
                    int CurrentSemester,eligible,ectsSum,am;

                    studentfile >> name >> surname >> am  >> birthDate >> phoneNumber >> CurrentSemester >> eligible >> ectsSum  ;   //seperates values based on whitespaces wth >>

                    Student newStudent(name, surname);               //creates a student object
                    newStudent.SetBirth(birthDate);                   //set birth and phone
                    newStudent.SetPhone(phoneNumber);
                    newStudent.CopyAm(am);                         //pernaei to am apo ton fakelo
                    StudentList.push_back(new Student(newStudent));    //add a pointer to the student in the vector 
                }
                StudentFile.close();                                 //close file
                this->FindAM();                                       //initialise to NextAm 
            }
            }catch(const char* txtmessage){                         //catch exception
                std::cout<<txtmessage<<std::endl;                             //print exception message
            }


        std::ifstream ProfessorFile("professor_list.txt");     //open file
        try{
            if (!ProfessorFile.is_open()) {          //checks if file is open and throw exception if not
                throw "Failed to open file";
            }else {
                std::string line;
                while (getline(ProfessorFile, line)) {  // Read each line from  file
                    std::istringstream professorfile(line);
                    std::string name, surname, birthDate, phoneNumber;
                    int key;
                    professorfile >> name >> surname >> key >> birthDate >> phoneNumber;        //seperates values based on whitespaces wth >>

                    Professor newProfessor(name, surname);           //creates a professor object
                    newProfessor.SetBirth(birthDate);               //set birth and phone
                    newProfessor.SetPhone(phoneNumber);
                    newProfessor.SetKey(key);
                    ProfList.push_back(new Professor(newProfessor));         //add a pointer to the professor in the vector
                }
                ProfessorFile.close();                 //close file
                this->FindKey();                       //briskei to teleutaio am pou mpike apo ton fakelo
            }
        }catch(const char* txtmessage){                   //catch exception
            std::cout<<txtmessage<<std::endl;                     //print exception message
        }

        std::ifstream CourseFile("course_list.txt");         //open file
        try{
            if (!CourseFile.is_open()) {        //checks if file is open and throw exception if not
                throw "Failed to open file";
            }else {
                std::string line;
                while (getline(CourseFile, line)) {     // Read each line from file
                    std::istringstream coursefile(line);
                    std::string name;
                    int ects, semester,code;
                    bool type;

                    coursefile  >> name >> code >> ects >> semester >> type;         //seperates values based on whitespaces wth >>

                    Course newCourse(name);         //creates a course object
                    newCourse.SetCode(code);
                    newCourse.SetEcts(ects);        //set ects , semester and type
                    newCourse.SetSemester(semester);
                    newCourse.SetType(type);
                    CourseList.push_back(new Course(newCourse));    //add a pointer to the course in the vector 
                }

             
            CourseFile.close();           //close file
            this->FindCode();
            }
        }catch(const char* txtmessage){         //catch exception
            std::cout<<txtmessage<<std::endl;                  //print exception message
        }    
    }
    
    void Secretary::StoreData(){    //apothikeuei sto txt tA dedomena mas meta tis allages mas
        std::ofstream StudentFile( "student_list.txt",std::ios::trunc);          //open file in trunc mode
        try{
            if (!StudentFile.is_open()){                 //if  file hasnt opened throw an exception
                throw "failed to open file";
            }else{
                for(Student* newStudent:StudentList){           //  for each student in the list
                    newStudent->WriteStudentFile(StudentFile);  //  write his info
                }
                StudentFile.close();                           //  close file
            }
        }catch(const char* txtmessage){                       //  catch  exception
            std::cout<<txtmessage<<std::endl;                           //  catch exception
        }

        std::ofstream professorfile( "professor_list.txt",std::ios::trunc);   //open file in trunc mode
        try{
            if (!professorfile.is_open()){                  //if  file hasnt opened throw an exception
                throw "failed to open file";
            }else{
                for(Professor* newProfessor:ProfList){               //for each professor in the list
                    newProfessor->WriteProfFile(professorfile);      //write his info
                }
                professorfile.close();                 //  close file
            }
        }catch(const char* txtmessage){         // catch exception
            std::cout<<txtmessage<<std::endl;                //print exception message
        }

        std::ofstream coursefile( "course_list.txt",std::ios::trunc);     //open file in trunc mode
        try{
            if (!coursefile.is_open()){                      // if  file hasnt opened throw an exception
                throw "failed to open file";
            }else{
                for(Course* newCourse:CourseList){              //for each course in the list
                    newCourse->WriteCourseFile(coursefile);     //write its info
                }
                coursefile.close();                    //  close file
            }
        }catch(const char* txtmessage){             //catch exception
            std::cout<<txtmessage<<std::endl;                 //print exception message
        }



    }

    Secretary::Secretary(Secretary& original){                                             //copy constructor
    }
    
    Secretary::~Secretary() {                                                                  // destructor-deallocation of memory                    
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

    void Secretary::newDepartment(){                 //proti entoli p prepei na trexei otan ftiaxnoume ena neo tmima
        xeimerino=1;
    }
    void Secretary::CountMand(){                    // upologizei ton arithmo ton upoxreotikon mathimaton tou tmimatos
            mandatoryTotal=0;   // initialise 
        for(Course* mathima:CourseList){
            if(mathima->GetType()==0){ //gia kathe upoxreotiko mathima
                mandatoryTotal++; // auxise to kata 1
            }   
        }
    }

    void Secretary::NextSemester(){            //allagi tou apo earino se xeimerino kai antistrofa 
        if(xeimerino==1){            
            xeimerino=0;
        }else
            xeimerino=1;

        SemesterSigned.clear();                                                //clear ti list ton mathimaton autou tou examinou
        for(Student* student:StudentList){    //auxanei to current semester ton foititon kata 1 kaikanei 
            student->addSemester();
        }
        for(Course* course:CourseList){   //kanei intialise ta stats tou kathe mathimatos
            course->InitStats();
        }
        SemesterSigned.clear(); //clear to map tou examinou

            
    }
    void Secretary::FindAM(){ //briskei to teleutaio AM pou mpike apo ton fakelo
        int store=0;
        for(Student* student:StudentList){// gia kathe mathiti sto tmima
            if(student->GetAm()>store){  //an to am einai megalutero apo ti timi tou store
                store=student->GetAm(); //tote to store pairnei tin timi tou
            }    
        }
        Student::SetNextAM(store+1);   //kai to nextam tin epomeni timi
    }
    void Secretary::FindKey(){//briskei to teleutaio key pou mpike apo ton fakelo
        int store=0;
        for(Professor* prof:ProfList){// gia kathe professor sto tmima
            if(prof->GetNextKey()>store){//an to key einai megalutero apo ti timi tou store
                store=prof->GetNextKey();//tote to store pairnei tin timi tou
            }    
        }
        Professor::SetNewKey(store+1); //kai to nextkey tin epomeni timi
    }
    void Secretary::FindCode(){//briskei to teleutaio code pou mpike apo ton fakelo
        int store=0;
        for(Course* course:CourseList){// gia kathe course sto tmima
            if(course->GetCode()>store){//an to code einai megalutero apo ti timi tou store
                store=course->GetCode();//tote to store pairnei tin timi tou
            }    
        }
        Course::SetNextCode(store+1);  //kai to nextcode tin epomeni timi
    }

    void Secretary::addStudent() {                               //sunartisi pou  prostheti neo melos ston katalogo thelei douleia
        std::string name,surname;
        std::cout<<"Enter new student name"<<std::endl;
        std::cin>>name; //dinoume to onoma
        std::cout<<"Enter new student surname"<<std::endl;
        std::cin>>surname;    //dinoume to surname
        Student newStudent(name,surname);  //constructor
        newStudent.SetAm();     // pername to am sto object
        newStudent.Givephone();     //omoios
        newStudent.giveBirth();      
        StudentList.push_back(new Student(newStudent)); //pername pointer sto vextor dynamika

    }
    void Secretary::removeStudent(int am) {
        int found=0;
        for (std::vector<Student*>::iterator it = StudentList.begin(); it != StudentList.end(); ++it) {  //xekinaei na anazita sti lista apo tin arxi os to telos
            if ((*it)->GetAm() == am) {               //an brei kapoio student me idio am
                delete *it;                             // to diagrafei
                StudentList.erase(it);                  //kai afairei to pointer apo to vector
                std::cout<<"Student successfuly deleted"<<std::endl;
                found=1;
                break;                                    //telos brogxou
            }
        }
        if(found==0){
            std::cout<<"cant find student with matching Am "<<std::endl;
        }
    }   

    void Secretary::addProf(){      //prosthetoume neoprof sti lista opos akrivos kai sto student
        std::string name,surname;
        int key;
        std::cout<<"Enter new professor name"<<std::endl;       //dinoume ta info tou professor
        std::cin>>name;
        std::cout<<"Enter new professor surname"<<std::endl;
        std::cin>>surname; 
        std::cout<<"Enter new professor key"<<std::endl;
        std::cin>>key;
        Professor newProfessor(name,surname);
        newProfessor.SetKey(key);
        newProfessor.Givephone();     
        newProfessor.giveBirth();
        ProfList.push_back(new Professor(newProfessor)); //bazoume sto vector pointer  me dynamic alloc
    }

    void Secretary::removeProf(int key){  //afairei prof opos akrivos me to student
        int found=0;
        for (std::vector<Professor*>::iterator it = ProfList.begin(); it != ProfList.end(); ++it) {  //xekinaei na anazita sti lista apo tin arxi os to telos
            if ((*it)->GetKey() == key) {               //an brei kapoio student me idio am
                delete *it;                             // to diagrafei
                ProfList.erase(it);                  //kai afairei to pointer apo to vector
                std::cout<<"Professor successfuly deleted"<<std::endl;
                found=1;
                break;                                    //telos brogxou
            }
        }
        if(found==0){
            std::cout<<"cant find Professor with matching Key "<<std::endl;
        }
    }

    void Secretary::addCourse(){  // prosthetei ena course sto vector opos akrivos me to student 
        std::string name;
        int code;
        int semester,ects;
        bool type;
        std::cout<<"Enter new Course name"<<std::endl;
        std::cin>>name; 
        std::cout<<"Enter new Course code"<<std::endl;
        std::cin>>code;
        Course newCourse(name);
        newCourse.SetCode(code);
        newCourse.GiveSemester();
        newCourse.GiveEcts();
        newCourse.GiveType();
        CourseList.push_back(new Course(newCourse));

    }

    void Secretary::removeCourse(int code){ //afairei ena course apo to  vector opos akrivos me to student
        int found=0;
        for (std::vector<Course*>::iterator it = CourseList.begin(); it != CourseList.end(); ++it) {
            if ((*it)->GetCode() == code) {
                delete *it;  
                CourseList.erase(it);
                std::cout<<"Professor successfuly deleted"<<std::endl;
                found =1;
                break;  
            }
        }if(found==0){
            std::cout<<"cant find Course with matching Code "<<std::endl;
        }
    }

    void Secretary::printEligible(){             //prints if each student is eligible to graduate
        for(Student* student:StudentList){         //checkarei kathe student sto vector 
            if(student->ReadEligible()==1){          //an einai eligible for graduation
                student->getSname();                     //print his name and surname
                std::cout<< " with AM " << student->GetAm()<< " is "; 
            }     
        }
    }    
    bool Secretary::GetXeimerino(){ 
        return xeimerino;
    }
    void Secretary::WriteXeimerino(bool a){
        xeimerino=a;
    }
    void Secretary::WritePass(int code){ //write se file osous  student perasan ena mathima
        bool found=0;
        for(Course* course:CourseList){ //psaxnei kathe mathima sti lista
            if(course->GetCode()==code){//an brei kapoio me idio code
                found=1;                   //ginetai to found 1
                for(Student* student:StudentList){//kai gia kathe mathiti sti lista
                    if( grade[std::make_pair(student->GetAm(), course->GetCode())]>=5){ //an o grade>5:    
                        std::ofstream passerfile( "Passer.txt",std::ios::trunc);     //open file in trunc mode
                        try{
                            if (!passerfile.is_open()){                      //if  file hasnt opened throw an exception
                                throw "failed to open file";
                            }else{             
                                student->WriteStudentFile(passerfile);     //write the students info
                                passerfile.close();                    //close file
                            }
                        }catch(const char* txtmessage){          //catch exception
                            std::cout<<txtmessage<<std::endl;                 //print exception message
                        }
                    }
                }   
            }     
        }if(found==0){
            std::cout<<"No course with this code found"<<std::endl;
        }
    }
    void Secretary::WriteGrade(int am,int code,int  vathmos){         //kataxorisi bathmou 
        bool found1=0,found2=0;
        for(Student* student:StudentList){
            if(student->GetAm()==am and CheckSigning(am,code)==1 ){    // elegxos signed kai an uparxei mathitis me to am auto
                found1=1;
                for(Course* course:CourseList){     //psaxnei sti lista gia na matcharei course me code
                    if(course->GetCode()==code){
                        found2=1;
                        grade[std::make_pair(student->GetAm(), course->GetCode())] = vathmos; //kataxorisi vathmou
                        std::cout<<"Grade given Successfully"<<std::endl;
                        if(vathmos>=5){
                            course->GotPass();
                        }else{
                            course->GotCut();
                        }
                    }
                }if(found2==0){
                    std::cout<<"No Course with a matching  code found"<<std::endl; //an dn brethei course me to idio code 
                }
            }
        }if(found1==0){
            std::cout<<"No Student with a matching  AM found"<<std::endl; //an dn brethei student me to idio code
        }
    }
    void Secretary::PrintGrades(int am){ //ektuposi analutikis bathmologias
        std::string answer;
        int found=0;
        for(Student* student:StudentList){
            int found=0;
            if(student->GetAm()==am){
                found=1;
                std::cout<<"do you want to print all grades or this current semester grades only(all/current)"<<std::endl;//epilogi poion bathmologion thelei na ektuposei
                std::cin>>answer;
                if(answer=="all"){
                    std::cout<<"Printing all grades for student with am: "<<student->GetAm()<<std::endl;
                    std::multimap<int,int>::iterator it = AllSigned.find(student->GetAm());  //find the first occurance of my key in the [student->course]
                    while (it != AllSigned.end() && it->first == student->GetAm()) {        // search till the end of the map
                        if( grade[std::make_pair(student->GetAm(),it->second)]>=5){//it->second = course.code, [student,course->grade]
                           bool found2=0;
                           for(Course* course: CourseList){    //find course with same code (gia na tuposo to onoma tou course)
                              if(course->GetCode()==it->second){  //check code is the same
                                    found2=1;                      //if course is found
                                    std::cout<< course->ReturnName() << " grade is: "<< grade[std::make_pair(student->GetAm(),it->second)] <<std::endl;  //print grade
                                    break; //stop loop if grade is found
                                }
                            }
                            if(found2==0){ //an dn brethei
                                std::cout<<"Course with code:"<< it->second<<"not found"<<std::endl;
                            } 
                        }
                        ++it;   
                    }
                }else if(answer=="current"){
                    std::cout<<"Printing current semester grades for student with am: "<<student->GetAm()<<std::endl;
                    std::multimap<int,int>::iterator it = SemesterSigned.find(student->GetAm());  //find the first occurance of my key in the [student->course]
                    while (it != SemesterSigned.end() && it->first == student->GetAm()) {        // search till the end of the map for a student with the same AM
                        if( grade[std::make_pair(student->GetAm(),it->second)]>=5){//it->second = course.code, [student,course->grade]
                            bool found2=0;                        //elegxei an uparxei kapooio course sto courselist me to code mas
                            for(Course* course: CourseList){    //find course with same code (gia na tuposo to onoma tou course)
                                if(course->GetCode()==it->second){  //check code is the same
                                    found2=1;                      //if course is found
                                    std::cout<< course->ReturnName() << " grade is: "<< grade[std::make_pair(student->GetAm(),it->second)] <<std::endl;  //print grade
                                    break; //stop loop if grade is found
                                }
                            }
                            if(found2==0){ //an dn brethei
                                std::cout<<"Course with code:"<< it->second<<"not found"<<std::endl;
                            } 
                        }
                        ++it;      //epomeno code
                    }
                }else{
                    std::cout<<"invalid answer"<<std::endl;  //se periptosi pou dn dothei apantisi (all/semester)
                }
            }
        }if(found==0){
            std::cout<<"no Student with this AM exist"<<std::endl;
        }    
    }  
    void Secretary::SignToCourse(int am,int code){          // eggrafi mathiti se mathima
        bool found1=0,found2=0;
        for(Student* student:StudentList){ //psaxnoume sti lista ton mathiton gia kapoion me to idio am 
            if(student->GetAm()==am){
                found1=1;       //an brethei
                for(Course* course:CourseList){//psaxnoume kathe course sti lista gia ena me idio code
                    if(course->GetCode()==code){
                        found2=1; //an brethei
                        AllSigned.insert({student->GetAm(),course->GetCode()}); //sta map allsigned kai semester signed prosthetoume os associated value to code tou course kai os key to am tou mathiti
                        SemesterSigned.insert({student->GetAm(),course->GetCode()});
                        break;
                    }
                }if(found2==0){
                    std::cout<<"Cant find course with a matching code"<<std::endl;
                }
                break;
            }
        }if(found1==0){
            std::cout<<"Cant find student with a matching AM"<<std::endl;
        }
    }
    void Secretary::CheckMand(int am){    //upologizei posa upoxreotika mathimata exei perasei enas student
        bool found=0;
        for(Student* student: StudentList){
            if(student->GetAm()==am){
                found=1;
                student->InitMandCount();        //initialise to mandcount
                for(Course* course:CourseList){     //elegxei kathe mathima
                    if(course->GetType()==0 &&  grade[std::make_pair(student->GetAm(), course->GetCode())]>=5){ //an to mathima einai upoxreotiko kai exei o student grade>=5 auxanetai to mandatorycount
                        student->AddMandCount(); //kaleitai i sunartisi p auxanei to mandcount
                    }
                }
                break;
            }
        }if(found==0){
            std::cout<<"No student with matching AM found"<<std::endl;
        }        
    }
    void Secretary::MakeEligible(int am){      //elegxos an mporei na parei ptuxio
        for(Student* student:StudentList){
            if(student->GetAm()==am){
                this->CheckMand(student->GetAm());      //upologismos tou mandatorycount tou student
                if(student->ReadMandCount()==this->mandatoryTotal && student->ReadCurentSemester()>8 && student->GetEctsSum()>50 ){  // checkarei an  tous orous apofoitisis
                    student->MakeGrad(); //kanei eligible=1 gia to student
                }
                break;
            }
        }
    }
    void Secretary::CountStudentEcts(int am){ //upologismos ects enos student
        bool found=0;
            for(Student* student:StudentList){
                if(student->GetAm()==am){
                    found =1;
                    student->InitEctsSum();    //arxikopoiisi ects ectsSum=0;
                    std::multimap<int,int>::iterator it = AllSigned.find(student->GetAm());  //find the first occurance of my key in the [student->course]
                    while (it != AllSigned.end() && it->first == student->GetAm()) {   // search till the end of the map for a student with the same AM
                        if(grade[std::make_pair(student->GetAm(),it->second)]>=5){      //an o bathmos se mathima p o foititis exei parakolouthisei einai>=5
                            for(Course* course:CourseList){     //psakse kathe mathima sti lista
                                if(course->GetCode()==it->second){    //bres to mathima pou antistoixei ston kodiko t
                                    student->AddEctsSum(course->GetEcts()); //prosthese ta ects tou sto student ectssum
                                }
                            }
                        }
                    }
                    break;
                }
            }if(found==0){
                std::cout<<"No student with matching AM found"<<std::endl;
            }        
    }   
    
    void Secretary::StopTeaching(int key, int code){//afairei ena professor apo ti diadaskalia enos mathimatos
        bool found1=0,found2=0;
        for (Professor* professor:ProfList){
            if(professor->GetKey()==key ){
                found1=1;
                for(Course* course:CourseList){
                    if(course->GetCode()==code){
                        found2=1;
                        std::pair<std::multimap<int, int>::iterator, std::multimap<int, int>::iterator> range =AllTeaching.equal_range(key);//i metabliti range pairnei range.first tin arxi tou map kai os range.second to telos tou map
                        for (std::multimap<int, int>::iterator it = range.first; it != range.second; ++it) {//oso to it->first(key) dn exei ftasei to telos tou map(range.second)
                            if (it->second == code) {
                                AllTeaching.erase(it);//diagrafi code
                                break; 
                            }
                        }
                    }
                }if(found2==0){
                    std::cout<<"Cant find course with a matching code"<<std::endl;
                }
                break;
            }
        }if(found1==0){
            std::cout<<"Cant find professor with a matching Key"<<std::endl;
        }
    }
    void Secretary::StartTeaching(int key, int code){ //prosthiki enos kathigiti os didaktor enos mathimatos
        bool found1=0,found2=0;
        for (Professor* professor:ProfList){
            if(professor->GetKey()==key ){
                found1=1;
                for(Course* course:CourseList){
                    if(course->GetCode()==code){
                        found2=1;
                        AllTeaching.insert({professor->GetKey(),course->GetCode()});//prosthiki tou syadiasmou key-code sto map
                        break;
                    }
                }if(found2==0){
                    std::cout<<"Cant find professor with a matching Key"<<std::endl;
                }

                break;
            }
        }if(found1==0){
                std::cout<<"Cant find professor with a matching Key"<<std::endl;
        }
    }
    void Secretary::PrintStats(int key){//ektuposi ton statistikon enos kathigiti sta mathimata tou auto to examino
        bool found1=0,found2=0;
        for (Professor* professor:ProfList){
            if(professor->GetKey()==key ){
                found1=1;
                std::multimap<int, int>::iterator it = AllTeaching.find(key);
                for (; it != AllTeaching.end() && it->first == key; ++it) {//oso dn exoume ftasei sto telos tou map kai exoume to sosto key
                    for(Course* course: CourseList){    
                        if(course->GetCode()==it->second){//briskoume to course p antistoixei sto it->second
                            float success=course->GetPass()/(course->GetPass()+course->GetCut());//upologizoume kai kanoume print to pososto epituxias t
                            success=success*100;
                            professor->getSname();
                            std::cout <<" has a success rate of ";
                            printf("%.1f  in ", success);
                            std::cout << course->ReturnName() << std::endl;
                            break;
                        }
                    }
                } 
                break;
            }
        }if(found1==0){
            std::cout<<"Cant find professor with a matching Key"<<std::endl;
        }
    }
    bool Secretary::CheckSigning(int am,int code){ //return true if specific student has signed in specific course else false

        bool found1=0,found2=0;
        for (Student* student:StudentList){
            if(student->GetAm()==am ){
                found1=1;
                for(Course* course:CourseList){
                    if(course->GetCode()==code){
                        found2=1;
                       std::pair<std::multimap<int, int>::iterator, std::multimap<int, int>::iterator> range =AllSigned.equal_range(am);//i metabliti range pairnei range.first tin arxi tou map kai os range.second to telos tou map
                            for (std::multimap<int, int>::iterator it = range.first; it != range.second; ++it) {//oso to it->first(key) dn exei ftasei to telos tou map(range.second)
                                if (it->second == code) {// an brethei course me to idio code
                                    return true; 
                                }
                    }
                }if(found2==0){
                    std::cout<<"Cant find course with a matching code"<<std::endl;
                    return false;
                }


            }
            }if(found1==0){
                std::cout<<"Cant find student with a matching am"<<std::endl;
                return false;
            }
        }
        return false;
    } 

    void Secretary::ChangeStudentAM(int am){//allagi am student
        bool found=0;
        for(Student*student:StudentList){  //gia kathe student sti lista
            if(student->GetAm()==am){       //an enas student exei to idio am
                found=1;        //=1 giati brethike
                student->SetAm();//allagi am
                break;
            }
        }if(found==0){
            std::cout<<"No student with matching AM found"<<std::endl;//an dn brethei
        }
    }
    void Secretary::ChangeProfKey(int key){
        bool found=0;
        int answer;
        for(Professor* professor:ProfList){  //gia kathe professor sti lista
            if(professor->GetKey()==key){       //an enas professor exei to idio key
                found=1;        //=1 giati brethike
                std::cout<<"pls enter new key for professor"<<std::endl;
                std::cin>>answer; 
                professor->SetKey(answer);//allagi key
                break;
            }
        }if(found==0){
            std::cout<<"No professor with matching key found"<<std::endl;//an dn brethei
        }
    }
    void Secretary::ChangeCourseCode(int code){
        bool found=0;
        int answer;
        for(Course* course:CourseList){  //gia kathe course sti lista
            if(course->GetCode()==code){       //an ena course exei to idio code
                found=1;        //=1 giati brethike
                std::cout<<"pls enter new code for course"<<std::endl;
                std::cin>>answer; 
                course->SetCode(answer);//allagi code
                break;
            }
        }if(found==0){
            std::cout<<"No course with matching code found"<<std::endl;//an dn brethei
        }
    }
    void Secretary::ChangestudentSemester(int am){
        bool found=0;
        int answer;
        for(Student*student:StudentList){  //gia kathe student sti lista
            if(student->GetAm()==am){       //an enas student exei to idio am
                found=1;        //=1 giati brethike
                std::cout<<"pls enter new currnt semester for student"<<std::endl;
                std::cin>>answer;
                student->SetSemester(answer);//allagi current semester
                break;
            }
        }if(found==0){
            std::cout<<"No student with matching AM found"<<std::endl;//an dn brethei
        }
    }
    void Secretary::ChangeCourseSemester(int code){
        bool found=0;
        for(Course* course:CourseList){  //gia kathe course sti lista
            if(course->GetCode()==code){       //an ena course exei to idio am
                found=1;        //=1 giati brethike
                course->GiveSemester();//allagi semester
                break;
            }
        }if(found==0){
            std::cout<<"No course with matching code found"<<std::endl;//an dn brethei
        }
    }
    void Secretary::ChangeCourseEcts(int code){
        bool found=0;
        for(Course* course:CourseList){  //gia kathe course sti lista
            if(course->GetCode()==code){       //an ena course exei to idio code
                found=1;        //=1 giati brethike
                course->GiveEcts();//allagi ects
                break;
            }
        }if(found==0){
            std::cout<<"No course with matching code found"<<std::endl;//an dn brethei
        }
    }
    void Secretary::ChangeCourseType(int code){
        bool found=0;
        for(Course* course:CourseList){  //gia kathe course sti lista
            if(course->GetCode()==code){       //an enas course exei to idio code
                found=1;        //=1 giati brethike
                course->GiveType();//allagi type
                break;
            }
        }if(found==0){
            std::cout<<"No course with matching code found"<<std::endl;//an dn brethei
        }
    }
    void Secretary::ChangeStudentBirth(int am){
        bool found=0;
        for(Student*student:StudentList){  //gia kathe student sti lista
            if(student->GetAm()==am){       //an enas student exei to idio am
                found=1;        //=1 giati brethike
                student->giveBirth();//allagi birthdate
                break;
            }
        }if(found==0){
            std::cout<<"No student with matching AM found"<<std::endl;//an dn brethei
        }
    }
    void Secretary::ChangeStudentPhone(int am){
        bool found=0;
        for(Student*student:StudentList){  //gia kathe student sti lista
            if(student->GetAm()==am){       //an enas student exei to idio am
                found=1;        //=1 giati brethike
                student->Givephone();//allagi phone
                break;
            }
        }if(found==0){
            std::cout<<"No student with matching AM found"<<std::endl;//an dn brethei
        }
    }
    void Secretary::ChangeProfBirth(int key){
        bool found=0;
        for(Professor*professor:ProfList){  //gia kathe professor sti lista
            if(professor->GetKey()==key){       //an enas professor exei to idio key
                found=1;        //=1 giati brethike
                professor->giveBirth();//allagi birthdate
                break;
            }
        }if(found==0){
            std::cout<<"No professor with matching key found"<<std::endl;//an dn brethei
        }
    }
    void Secretary::ChangeProfPhone(int key){
        bool found=0;
        for(Professor*professor:ProfList){  //gia kathe professor sti lista
            if(professor->GetKey()==key){       //an enas professor exei to idio key
                found=1;        //=1 giati brethike
                professor->Givephone();//allagi phonenumber
                break;
            }
        }if(found==0){
            std::cout<<"No professor with matching key found"<<std::endl;//an dn brethei
        }
    }
