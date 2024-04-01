
#include <iostream>
#include <string>
#include <vector>
#include <fstream>



using namespace std;



int main() {

    vector<Student> students = {
        {"John Doe", 20, 3},
        {"Alice Smith", 22, 4},
        {"Bob Johnson", 21, 3}


    };

    for (const auto& student : students) {
        student.saveToFile("students.txt");
    }
    fstream myfile;
    myfile.open("student.txt",ios::out);
    myfile<<"hello";
    myfile.close();



    return 0;
}