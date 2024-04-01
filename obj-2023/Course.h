#pragma once
#ifndef COURSE_H
#define COURSE_H
#include <iostream>
#include <string>         // pointer vector logo polumorphismou
#include <fstream> //read txt file
#include <sstream>

class Course{
    std::string Name;
    int Ects=10,Code;
    int Semester;
    bool Type;                //0=mandatory, 1=optional
    int Pass=0, Cut=0;
    static int NextCode;
public:
    Course(std::string name);;
    Course(Course& course);
    ~Course();
    std::string ReturnName();
    void SetEcts(int ects);
    void SetSemester(int semester);
    void SetType(bool type);
    void SetCode(int code);
    int GetEcts();
    int GetType();
    int GetCode();
    void WriteCourseFile(std::ostream& file);
    void GotCut();
    void GotPass();
    void InitStats();
    bool operator<(Course* course);
    bool operator==(Course* course);
    void GiveNextCode();
    static int GetNextCode();
    static void SetNextCode(int code);
    int GetCut();
    int GetPass();
    void GiveSemester();
    void GiveType();
    void GiveEcts();
};
#endif