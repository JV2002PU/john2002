#pragma once
#ifndef PERSON_H
#define PERSON_H
#include <iostream>
#include <string>         // pointer vector logo polumorphismou
 



class person{                        
protected:
    std::string Name;
    std::string Surname;
    std::string BirthDate; 
    std::string PhoneNumber;                                                    

public:
    person();
    person(std::string name,std::string surname);
    ~person();
    void SetBirth(std::string birthdate);
    void SetPhone(std::string phone);
    void setSname(std::string name,std::string surname);
    void getSname();
    void giveBirth();
    void Givephone();





};
#endif