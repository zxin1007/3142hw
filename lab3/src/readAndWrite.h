#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <dirent.h>
#include <algorithm>
#include <vector>
#include <map>
#include "record.h"
using namespace std;
bool has_suffix(const string& s, const string& suffix);

//reading in the data
void readData(vector<Student>& student){

    //read the files name under data
    string path = "../data";
    string courseno;
    DIR *dir = opendir(path.c_str());
    if(dir)
    {
        dirent *entry;
        while((entry = readdir(dir))!=NULL) 
        {
            if (has_suffix(entry->d_name, ".csv")){
                ifstream in_stream;
                string file = entry->d_name;
                in_stream.open("../data/"+file);
                
                if (!in_stream.fail()) {
                    string line;
                    //skip the header
                    getline(in_stream,line);
                    while (getline(in_stream,line)) {
                        
                        struct Student stu;
                        struct Instructor ins;
                        struct Course course_temp;
                        struct Term term_temp;

                        stringstream str(line); 
                        //read in the emplid
                        getline(str,stu.id,',');

                        getline(str,courseno,',');
                        course_temp.course_id = atoi(courseno.c_str());

                        getline(str,ins.instructor_id,',');

                        getline(str,term_temp.term_id,',');
                        
                        //determine the name of term based on the term id
                        if (term_temp.term_id=="T04"||term_temp.term_id=="T08"||term_temp.term_id=="T12"||term_temp.term_id=="T16"||term_temp.term_id=="T20"||term_temp.term_id=="T23"){
                            term_temp.term_name = "Fall";
                        } else {
                            term_temp.term_name = "Spring";
                        }

                        getline(str,course_temp.section_id,',');

                        //determine the whether the grade is passing/withdraw/fail
                        getline(str,stu.grade,',');
                        if (stu.grade=="A+"||stu.grade=="A"||stu.grade=="A-"||stu.grade=="B+"||stu.grade=="B"||stu.grade=="B-"||stu.grade=="C+"||stu.grade=="C"){
                            stu.pass = 'p';
                        } else if (stu.grade=="W"||stu.grade=="WU"||stu.grade=="WD"){
                            stu.pass = 'w';
                        } else{
                            stu.pass = 'f';
                        }
                        ins.course = course_temp;
                        ins.term = term_temp;
                        course_temp.term = term_temp;
                        stu.instructor = ins;
                        student.push_back(stu);
                    }
                }


            }
        }
    } else {
        cout << "path not found" << endl;
    }

    closedir(dir);
}

//check the file extension matches
bool has_suffix(const string& s, const string& suffix)
{
    return (s.size() >= suffix.size()) && equal(suffix.rbegin(), suffix.rend(), s.rbegin());    
}

//writing data into different files.
void writeToFile(string file_name, bool pass ,int mode, map<string,float> data){

    string type;
    string rate_type;

    if (mode==1){
        type = "instructor";
    } else if(mode==2){
        type = "course number";
    } else if (mode==3){
        type = "term";
    }

    if (pass){
        rate_type = "pass rate";
    } else{
        rate_type = "w rate";
    }

    ofstream myfile;
    myfile.open (file_name.c_str());

    for (map<string,float>::iterator it=data.begin(); it!=data.end(); ++it){
        myfile << "the " << rate_type << " for " << type.c_str() << " " << it->first.c_str() << " is " << it->second << "%" << endl;
    }
    myfile.close();
}