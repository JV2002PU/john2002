#include <iostream>
using namespace std;


class Person
{
    static int count;
    str Name;
    int age;
    int id;

    public:
        
        Person(string name, int age , int id){
            name=name;
            age=age;
            id=id;
            count++;
        }
        void GetInfo() {
		cout << "Name: " << Name << endl;
		cout << "age: " << age << endl;
		cout << "id: " << id << endl;
        cout << "count: " << count << endl;
		
		}
        ~Person() {
        --count;
        } 
void operator<<(ostreram& COUT, Person& Aperson){
    COUT << "Name: " << Aperson.Name << endl;
    COUT << "age: " << Aperson.age << endl;
    COUT << "id: " << Aperson.id << endl;
    COUT << "count: " << Aperson.count << endl;
}
        




};

int main(){
    Person Aperson()


}