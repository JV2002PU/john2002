#pragma once

#ifndef PROFESSOR_H
#define PROFESSOR_H
#include <iostream>
#include <string>         // pointer vector logo polumorphismou
#include <vector>
#include <fstream> //read txt file
#include <sstream>





class Professor: public person{
    int Key;
    static int NextKey;

public:
     Professor(Professor& prof);
    Professor(std::string name,std::string surname);
    void SetKey(int key);
    int GetKey();
    void WriteProfFile(std::ofstream& file);
    ~Professor();
    bool operator<(Professor* prof);
    bool operator==(Professor* prof);
    void GiveNextKey();
    static int GetNextKey();
    static void SetNewKey(int key);
    



   

};
#endif
