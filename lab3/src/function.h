#include <vector>
#include <type_traits>
#include <map>
#include <string> 
using namespace std;

int count (vector<Student> vector,string instructor_id ,bool pass,int mode);
map<string,int> max (vector<Student> vector,int mode);

void pass_rate(vector<Student> vector, int mode){

    map<string,int> myMap = max(vector,mode); //stores the number of pass student per (instructor/course number/term) base on the mode
    map<string,float> dataTobePrint;
    string file_name;
    if (mode == 1){
        file_name = "../output/passratePerInstructor.txt";
        for (map<string,int>::iterator it=myMap.begin(); it!=myMap.end(); ++it){
            float pass_rate = ((float)count(vector,it->first,true,mode)/it->second)*100;
            dataTobePrint.insert(pair<string,float>(it->first.c_str(), pass_rate));
        }
    } else if (mode == 2){
        file_name = "../output/passratePerCourseNumber.txt";
        for (map<string,int>::iterator it=myMap.begin(); it!=myMap.end(); ++it){
            float pass_rate = ((float)count(vector,it->first,true,mode)/it->second)*100;
            dataTobePrint.insert(pair<string,float>(it->first.c_str(), pass_rate));
        }
    } else if (mode == 3){
       file_name = "../output/passratePerTerm.txt";
        for (map<string,int>::iterator it=myMap.begin(); it!=myMap.end(); ++it){
            float pass_rate = ((float)count(vector,it->first,true,mode)/it->second)*100;
            dataTobePrint.insert(pair<string,float>(it->first.c_str(), pass_rate));
        }
    }

    writeToFile(file_name,true ,mode, dataTobePrint);
}

void w_rate(vector<Student> vector, int mode){

    map<string,int> myMap = max(vector,mode);
    map<string,float> dataTobePrint;
    string file_name;
    if (mode == 1){
        file_name = "../output/wratePerInstructor.txt";
        for (map<string,int>::iterator it=myMap.begin(); it!=myMap.end(); ++it){
            float w_rate = ((float)count(vector,it->first,false,mode)/it->second)*100;
            dataTobePrint.insert(pair<string,float>(it->first.c_str(), w_rate));
        }
    } else if (mode == 2){
        file_name = "../output/wratePerCourseNumber";
        for (map<string,int>::iterator it=myMap.begin(); it!=myMap.end(); ++it){
            float w_rate = ((float)count(vector,it->first,false,mode)/it->second)*100;
            dataTobePrint.insert(pair<string,float>(it->first.c_str(), w_rate));
        }
    } else if (mode == 3){
        file_name = "../output/wratePerTerm.txt";
        for (map<string,int>::iterator it=myMap.begin(); it!=myMap.end(); ++it){
            float w_rate = ((float)count(vector,it->first,false,mode)/it->second)*100;
            dataTobePrint.insert(pair<string,float>(it->first.c_str(), w_rate));
        }
    }

    writeToFile(file_name, false,mode, dataTobePrint);

}

//count the pass/fail rate for each instructor
int count (vector<Student> vector,string condition ,bool pass,int mode){
    int amount = 0;
    for (int i = 0; i < vector.size(); i++)
    {
        if (mode == 1){
            if (pass && vector[i].instructor.instructor_id==condition&&vector[i].pass=='p'){
                amount+=1;
            } else if (!pass && vector[i].instructor.instructor_id==condition && vector[i].pass=='w'){
                amount+=1;
            }
        } else if (mode == 2){
            if (pass && to_string(vector[i].instructor.course.course_id)==condition&&vector[i].pass=='p'){
                amount+=1;
            } else if (!pass && to_string(vector[i].instructor.course.course_id)==condition && vector[i].pass=='w'){
                amount+=1;
            }
        } else if (mode == 3){
            if (pass && vector[i].instructor.term.term_name==condition&&vector[i].pass=='p'){
                amount+=1;
            } else if (!pass && vector[i].instructor.term.term_name==condition && vector[i].pass=='w'){
                amount+=1;
            }
        }
    } 

    return amount;
    
}

map<string,int> max (vector<Student> vector, int mode){
    map<string,int> myMap;
    for (int i = 0; i < vector.size(); i++)
    {
        map<string,int>::iterator it = myMap.begin();
        if (mode == 1){
            for (map<string,int>::iterator it=myMap.begin(); it!=myMap.end(); ++it){
                if (vector[i].instructor.instructor_id.c_str() == it->first){
                    int num = myMap.at(vector[i].instructor.instructor_id);
                    myMap.at(vector[i].instructor.instructor_id) = num+1;
                }
            }
            myMap.insert(pair<string,int>(vector[i].instructor.instructor_id,1));
        } else if (mode == 2){
            for (map<string,int>::iterator it=myMap.begin(); it!=myMap.end(); ++it){
                if (to_string(vector[i].instructor.course.course_id) == it->first){
                    int num = myMap.at(to_string(vector[i].instructor.course.course_id));
                    myMap.at(to_string(vector[i].instructor.course.course_id)) = num+1;
                }
            }
            myMap.insert(pair<string,int>(to_string(vector[i].instructor.course.course_id),1));
        } else if (mode ==3){
            for (map<string,int>::iterator it=myMap.begin(); it!=myMap.end(); ++it){
                if (vector[i].instructor.term.term_name == it->first){
                    int num = myMap.at(vector[i].instructor.term.term_name);
                    myMap.at(vector[i].instructor.term.term_name) = num+1;
                }
            }
            myMap.insert(pair<string,int>(vector[i].instructor.term.term_name,1));
        }
    }

    return myMap;
}