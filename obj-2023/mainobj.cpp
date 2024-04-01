#include <iostream>
#include "Person.h"
#include "Professor.h"
#include "Secretary.h"
#include "Student.h"
#include "Course.h"



int main() { 
    std::vector<Student*> studentList;
    std::vector<Professor*> profList;
    std::vector<Course*> courseList;

    Secretary s1(studentList, profList, courseList);
    s1.newDepartment();         //to trexoume efoson einai neo to tmima apla orizei to examino os xeimerino
    s1.addStudent();            //prostetoume enan student sti lista
    s1.removeStudent(1);        //afairoume ton student me am=1 apo ti lista
    s1.addProf();               //prostetoume enan professor sti lista
    s1.removeProf(1);           //afairoume ton professor me key=1 apo ti lista
    s1.addCourse();             //prostetoume ena course sti lista
    s1.removeCourse(1);         //afairoume to course me code=1 apo ti lista
    s1.StartTeaching(2,2);      //o professor me key=2 arxizei na didaskei to course me code=2
    s1.SignToCourse(2,2);       //o student me Am=2 eggrafetai sto mathima me code=2
    s1.WriteGrade(2,2,6);        //o student me AM=2 pairnei vathmo 6 sto mathima me code=2
    s1.WritePass(2);            //sto fakelo pass.txt grafontai ta onomata ton mathiton pou perasan to mathima me code=2 auto to examino
    s1.PrintStats(2);         //ektuponoume to pososto epituxias sta mathiata tou professor me key=2
    s1.PrintGrades(2);        //ektuposi analutikis bathmologias olon ton eton h examinou tou mathiti me code=2
    s1.MakeEligible(2);        //elegxei an o mathitis mporei na parei ptuxio kai an mporei ton kanei eligible=1
    s1.printEligible();       //ektuposi ton student pou mporoun na paroun ptuxio
    s1.StoreData();            //apothikeusi ton allagon mas se txt arxeio


    //ME TIS PARAKATO ENTOLES MPOROUME NA ALLAXOUME STOIXEIA TON OBJECT MAS AN TA BGALOUME APO TA COMMENT

   // s1.ChangeStudentAM(4);                            //allagi tou am toy student me am=4
   // s1.ChangeProfKey(4);                              //allagi tou key toy professor me key=4
   // s1.ChangeCourseCode(4);                           //allagi tou code toy course me code=4
    //s1.ChangestudentSemester(4);                      //allagi tou current semester toy student me am=4
    //s1.ChangeCourseSemester(4);                       //allagi tou semester toy course me code=4
    //s1.ChangeCourseEcts(4);                           //allagi tou ects toy course me code=4
    //s1.ChangeCourseType(4);                           //allagi tou type toy course me code=4
    //s1.ChangeStudentBirth(4);                         //allagi tou birthdate toy student me am=4
    //s1.ChangeStudentPhone(4);                         //allagi tou phonenumber toy student me am=4
    //s1.ChangeProfBirth(4);                            //allagi tou birthdate toy professor me key=4
    //s1.ChangeProfPhone(4);                            //allagi tou phonenumber toy profssor me key=4




    return 0;
}


