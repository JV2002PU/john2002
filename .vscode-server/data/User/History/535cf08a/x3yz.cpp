#include <iostream>
#include <string>
using namespace std;


class Person
{
    static int count;
    string Name;
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

}
void operator<<(ostreram& COUT, Person& Aperson){
    COUT << "Name: " << Aperson.Name << endl;
    COUT << "age: " << Aperson.age << endl;
    COUT << "id: " << Aperson.id << endl;
    COUT << "count: " << Aperson.count << endl;
};

int main(){
    Person Aperson("petros", 23, 2000016);
    cout << Aperson;


}