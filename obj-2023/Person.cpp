#include <iostream>
#include <string>         // pointer vector logo polumorphismou
#include "Person.h"



    person::person(){
    }
   person:: person(std::string name,std::string surname){
        Name=name;
        Surname=surname;
    }
   person:: ~person(){                                    
    }

    void person:: giveBirth(){
        std::string answer;
        std::cout<<"Enter birthdate:"<<std::endl;
        std::cin>>answer;
        this->SetBirth(answer);
    }
    void person::Givephone(){
        std::string answer;
        std::cout<<"Enter Phonenumber:"<<std::endl;
        std::cin>>answer;
        this->SetPhone(answer);
    }
    void person::SetBirth(std::string birthdate){                    // surantisi pou allazei h orizei birthdate
        BirthDate=birthdate;
        
    }
    void person::SetPhone(std::string phone){                    // surantisi pou allazei h orizei arithmo thlefonou
        PhoneNumber=phone;
    }   
    void person::setSname(std::string name,std::string surname){ // epitrepei na allaxoume to name kai surname enos person
        std::cout<< "please enter new name(cancel if name correct)"<< std::endl;
        std::cin>>name;
        if(name!="cancel")
            Name=name;
        std::cout<<"please enter new Surname(cancel if Surname correct)"<<std::endl;
        std::cin>>surname;
        if(surname!="cancel")
            Surname=surname;
    }
    void person::getSname(){ // ektuponei to name kai surname enos person
        std::cout<< this->Name<< "  "<< this->Surname ;
    }





