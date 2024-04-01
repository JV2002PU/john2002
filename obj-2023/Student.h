#pragma once
#ifndef STUDENT_H
#define STUDENT_H
#include <iostream>
#include <string>         // pointer vector logo polumorphismou





class Student:public person{
    int AM;             
    int CurrentSemester=1;
    bool eligible=0;
    int ectsSum=0;
    int mandatoryCount=0;
    static int NextAM;                    //records the last am given to a person
public:
    Student(std::string name,std::string surname);
    static void SetNextAM(int a);
    static int GetNextAM();
    Student(Student& student);
    void GiveNewAm();
    bool operator<(Student* student);
    bool operator==(Student* student);
    void InitMandCount();
    void WriteStudentFile(std::ofstream& file);
    void addSemester();
    void CopyAm(int am);
    void SetAm();
    int GetAm();
    ~Student();
    void AddMandCount();
    void Graduate();
    void AddEctsSum(int count);
    void InitEctsSum();
    int GetEctsSum();
    int ReadCurentSemester();
    void MakeGrad();
    int ReadEligible();
    int ReadMandCount();
    void SetSemester(int semester);

};
#endif