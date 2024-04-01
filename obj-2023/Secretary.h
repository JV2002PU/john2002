#pragma once
#ifndef SECRETARY_H
#define SECRETARY_H
#include <iostream>
#include <string>         // pointer vector logo polumorphismou
#include <vector>
#include <map>
#include <utility> // nomizo gia to pair
#include <fstream> //read txt file
#include <sstream>

class Course;
class Student;
class Professor;

class Secretary{                                                              
    std::vector <Student*>  StudentList;                                              // 
    std::vector <Professor*> ProfList;
    std::vector <Course*>  CourseList;
    static bool xeimerino;                                                             //xeimerino earino examino
    static std::map<std::pair<int,int>,  int> grade;        //<AM,CODE=grade> bathmos foititi se mathima
    static std::multimap<int,int> AllSigned;            //<AM->CODE>kanei associate to AM student me  ta code ton mathimaton p exei dilosei All time
    static std::multimap<int,int> SemesterSigned;        // <AM->CODE>kanei associate to AM student me ta code ton mathimaton p exei parakoloutisei auto to semester
    static std::multimap<int,int> AllTeaching;           //<Key->Code> kanei associate to Key professor me ta code ton mathimaton p exei didaxei All time
    static int mandatoryTotal;  
public:
    Secretary(std::vector<Student*>& newstudentlist,std::vector<Professor*>& newproflist,std::vector<Course*>& newcourselist);
    void StoreData();
    Secretary(Secretary& original);
    ~Secretary();
    void newDepartment();
    void CountMand();
    void NextSemester();
    void FindAM();
    void FindKey();
    void FindCode();
    void addStudent() ;
    void removeStudent(int am) ;
    void addProf();
    void removeProf(int key);
    void addCourse();
    void removeCourse(int code);
    void printEligible();
    static bool GetXeimerino();
    void WriteXeimerino(bool a);
    void WritePass(int code);
    void WriteGrade(int am,int code,int  vathmos);
    void PrintGrades(int am);
    void SignToCourse(int am,int code);
    void CheckMand(int am);
    void MakeEligible(int am);
    void CountStudentEcts(int am);
    void StopTeaching(int key, int code);
    void StartTeaching(int key, int code);
    void PrintStats(int key);
    bool CheckSigning(int am,int code);
    void ChangeStudentAM(int am);
    void ChangeProfKey(int key);
    void ChangeCourseCode(int code);
    void ChangestudentSemester(int am);
    void ChangeCourseSemester(int code);
    void ChangeCourseEcts(int code);
    void ChangeCourseType(int code);
    void ChangeStudentBirth(int am);
    void ChangeStudentPhone(int am);
    void ChangeProfBirth(int key);
    void ChangeProfPhone(int key);
};
#endif