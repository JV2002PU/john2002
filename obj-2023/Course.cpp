

#include "Course.h"
#include <iostream>
#include <string>         // pointer vector logo polumorphismou
#include <fstream> //read txt file
#include <sstream>


int Course::NextCode;

    Course::Course(std::string name){
        Name=name;
    }
    Course::Course(Course& course){      //copy constructor
        Name = course.Name;
        Ects = course.Ects;
        Semester = course.Semester;
        Type = course.Type;
        Code = course.Code;
        Pass = course.Pass;
        Cut = course.Cut;
    }

    
    Course::~Course(){
    }
    std::string Course::ReturnName(){
        return this->Name;
    }
    void Course::SetEcts(int ects){          //write a courses ects
        Ects=ects;
    }
    void Course::SetSemester(int semester){            //set a courses semester
        if(semester<=8)                    //8 examina uparxoun sto sxoli
            Semester=semester;
        else
        std::cout<< "Invalid semester"<<std::endl;  //an dothei megaluteros arithmos
    }
    void Course::SetType(bool type){                //set a courses type
        if(type!=1 && type!=0)              //0 gia mandatory kai 1 gia optional otidipote allo einai invalid
            std::cout<< "invalid type"<<std::endl;
        else
        this->Type=type;
    }   
    void Course::SetCode(int code){       //write courses code
        Code=code;
    }
    int Course::GetEcts(){
        return Ects;
    }
    int Course::GetType(){
        return this->Type;
    }
    int Course::GetCode(){    //read courses code
        return Code;
    }
    void Course::WriteCourseFile(std::ostream& file){                //write courses info in file
        file<< Name <<" "<< Code << " "<< Ects <<" "<< Semester <<" "<< Type << std::endl;
    }
    void Course::GotCut(){        //count how many students got cut in this course this semester
        this->Cut++;
    }
    void Course::GotPass(){     //count how many students passed  this course this semester
        this->Pass++;
    }
    void Course::InitStats(){  // initialise stats each semester
        this->Pass=0;
        this->Cut=0;
    }
    bool Course::operator<(Course* course){         // comparison operator for map
        return this->GetCode()<course->GetCode();
    }
    bool Course::operator==(Course* course){       // equality operator for map
        return this->GetCode()==course->GetCode();
    }
    void Course::GiveNextCode(){
        this->Code=NextCode;
        NextCode++;
    }
    int Course::GetNextCode(){
        return NextCode;
    }
    void Course::SetNextCode(int code){
        NextCode=code;
    }
    int Course::GetCut(){
        return Cut;
    }
    int Course::GetPass(){
        return Pass;
    }
    void Course::GiveSemester(){
        int semester;
        std::cout<< "type courses's semester(1-8)"<<std::endl;
        std::cin>>semester;
        this->SetSemester(semester);
    }
    void Course::GiveType(){
        int type;
        std::cout<< "type courses's type(0/1)"<<std::endl;
        std::cin>>type;
        this->SetType(type);
    }
    void Course::GiveEcts(){
        int ects;
        std::cout<< "type courses's ects(1/100)"<<std::endl;
        std::cin>>ects;
        this->SetEcts(ects);
    }


