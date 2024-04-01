
#include <iostream>
#include <string>
#include <vector>
#include <fstream>



using namespace std;



int main() {
    fstream myfile;
    myfile.open("student.txt",ios::out);
    myfile<<"hello";
    myfile.close();



    return 0;
}