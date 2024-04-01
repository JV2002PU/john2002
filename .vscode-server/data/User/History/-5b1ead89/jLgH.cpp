fix1.cpp: In member function ‘void Student::SignIn(Course*)’:
fix1.cpp:176:49: error: incomplete type ‘Secretary’ used in nested name specifier
  176 |             if(mathima->Semester%2== Secretary::GetXeimerino() && CurrentSemester>=mathima->Semester){       //checks if student can sign in this course based on Semester and year of study
      |                                                 ^~~~~~~~~~~~
fix1.cpp: In member function ‘void Student::CheckMand()’:
fix1.cpp:190:51: error: incomplete type ‘Secretary’ used in nested name specifier
  190 |                 if(mathima->Type==0 && Secretary::grade[std::make_pair(this, mathima)]>=5 ){   //checks if a course ia mand and if the grade of the student is sufficient
      |                                                   ^~~~~
fix1.cpp: In member function ‘void Student::ectsCount()’:
fix1.cpp:199:31: error: incomplete type ‘Secretary’ used in nested name specifier
  199 |                 if(Secretary::grade[std::make_pair(this, mathima)]>=5){      //gives courses ects to student if grade >5 this
      |                               ^~~~~
fix1.cpp: In member function ‘void Student::MakeEligible()’:
fix1.cpp:206:100: error: incomplete type ‘Secretary’ used in nested name specifier
  206 |             if (this->ectsSum>=240 && this->CurrentSemester>=8 && this->mandatoryCount==Secretary::mandatoryTotal){ //check if student suuficient ects ,mand courses and if he has studied enough years
      |                                                                                                    ^~~~~~~~~~~~~~
fix1.cpp: In member function ‘void Student::printGrade()’:
fix1.cpp:236:35: error: incomplete type ‘Secretary’ used in nested name specifier
  236 |                     if(Secretary::grade[std::make_pair(this, course)]>=5){ //an o bathmos tou mathimatos einai pano apo 5
      |                                   ^~~~~
fix1.cpp:238:68: error: incomplete type ‘Secretary’ used in nested name specifier
  238 |                         cout<< course << " grade is:"<< Secretary::grade[std::make_pair(this, course)] << endl; //printing
      |                                                                    ^~~~~
fix1.cpp:243:35: error: incomplete type ‘Secretary’ used in nested name specifier
  243 |                     if(Secretary::grade[std::make_pair(this, course)]>=5){
      |                                   ^~~~~
fix1.cpp:245:68: error: incomplete type ‘Secretary’ used in nested name specifier
  245 |                         cout<< course << " grade is:"<< Secretary::grade[std::make_pair(this, course)] << endl; //printing
      |                                                                    ^~~~~
fix1.cpp: In member function ‘void Professor::addGrade(Student*, Course*)’:
fix1.cpp:316:63: error: incomplete type ‘Secretary’ used in nested name specifier
  316 |         if(courseFound==1 && mathima->Semester%2== Secretary::GetXeimerino()){          //an to didaskei
      |                                                               ^~~~~~~~~~~~
fix1.cpp:319:24: error: incomplete type ‘Secretary’ used in nested name specifier
  319 |             Secretary::grade[std::make_pair(bathmologoumenos, mathima)] = bathmos;   //kataxorisi bathmou
      |                        ^~~~~
fix1.cpp: In member function ‘void Professor::printStats()’:
fix1.cpp:330:47: error: incomplete type ‘Secretary’ used in nested name specifier
  330 |             if(course->Semester%2==Secretary::GetXeimerino()){  //elegxei an to didaskei auto to examino
      |                                               ^~~~~~~~~~~~