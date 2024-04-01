
#include <iostream>
#include <string>         // pointer vector logo polumorphismou
#include "Person.h"
#include "Course.h"
#include "Student.h"


    int Student::NextAM;
    Student::Student(std::string name,std::string surname) : person(name,surname){    //student constructor
        eligible =0;
    }
    void Student::SetNextAM(int a){
        NextAM=a;
    }
    int Student::GetNextAM(){
        return NextAM;
    }
    Student::Student(Student& student){      //copy constructor
        Name = student.Name;
        Surname = student.Surname;
        BirthDate = student.BirthDate;
        PhoneNumber = student.PhoneNumber;
        AM = student.AM;
    }
    void Student::GiveNewAm(){
        this->AM=NextAM;
        Student::NextAM++;
    }
    bool Student::operator<(Student* student){
        return this->GetAm()<student->GetAm();
    }
    bool Student::operator==(Student* student){
        return this->GetAm()==student->GetAm();
    }
    void Student::InitMandCount(){
        this->mandatoryCount=0;
    }
    void Student::WriteStudentFile(std::ofstream& file){     //remove secretary XXXXXXXXXXXXX
        file << Name <<" " << Surname <<" "<< AM <<" "<< BirthDate <<" "<< PhoneNumber<<" "<< CurrentSemester<<" "<< eligible<<" "<<ectsSum<<std::endl; // writ student info in file
    }
    void Student::addSemester(){  //when new semester begins increase current semester by 1
        CurrentSemester=CurrentSemester++;
    }
    void Student::CopyAm(int am){
        this->AM=am;
    }
    void Student::SetAm(){ //write student am
        int answer;
        std::cout << "pls assign new student AM:  "<< std::endl;
        std::cin>> answer;
        this->AM=answer;
    }
    int Student::GetAm(){ //read am
        return AM;
    }
    Student::~Student(){                             // destructor
    }
    int Student::ReadMandCount(){
        return mandatoryCount;
    }
    void Student::AddMandCount(){
        this->mandatoryCount++;
    }
    void Student::Graduate(){
        if(this->eligible==0){
            this->eligible=1;
        }
        else{
            std::cout<< this << " already graduated"<<std::endl;
        } 
    }
    void Student::AddEctsSum(int count){
        this->ectsSum=this->ectsSum+count;
    }
    void Student::InitEctsSum(){
        this->ectsSum=0;
    }
    int Student::GetEctsSum(){
        return ectsSum;
    }
    int Student::ReadCurentSemester(){
        return CurrentSemester;
    }
    void Student::MakeGrad(){
        this->eligible=1;
    }
    int Student::ReadEligible(){
        return eligible;
    }
    void Student:: SetSemester(int semester){
        this->CurrentSemester=semester;
    }


