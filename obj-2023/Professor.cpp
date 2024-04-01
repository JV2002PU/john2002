#include <iostream>
#include <string>         // pointer vector logo polumorphismou
#include <vector>
#include <sstream>
#include "Person.h"
#include "Course.h"
#include "Professor.h"

    int Professor::NextKey;
    Professor::Professor(Professor& prof){      //copy constructor
        Name = prof.Name;
        Surname = prof.Surname;
        BirthDate = prof.BirthDate;
        PhoneNumber = prof.PhoneNumber;
        Key= prof.Key;
        
        
    }
    Professor::Professor(std::string name,std::string surname): person(name,surname){
    }
    void Professor::SetKey(int key){   //write key
        this->Key=key;
    }
    int Professor::GetKey(){   //read key
        return Key;
    }
    void Professor::WriteProfFile(std::ofstream& file){     //write professor info in file
         file << Name <<" " << Surname <<" "<< Key <<" "<< BirthDate <<" "<< PhoneNumber<<std::endl;

    }
    Professor::~Professor(){ 
    }
    bool Professor::operator<(Professor* prof){         // comparison operator for map
        return this->GetKey()<prof->GetKey();
    }
    bool Professor::operator==(Professor* prof){       // equality operator for map
        return this->GetKey()==prof->GetKey();
    }
    void Professor::GiveNextKey(){
        this->Key=NextKey;
        Professor::NextKey++;
    }
    int Professor::GetNextKey(){
        return NextKey;
    }
    void Professor::SetNewKey(int key){
        NextKey=key;
    }
   
         
   




