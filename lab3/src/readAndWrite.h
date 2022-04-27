#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <dirent.h>
#include <algorithm>
#include <vector>
#include "record.h"
using namespace std;
bool has_suffix(const string& s, const string& suffix);

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
                        
                        if (term_temp.term_id=="T04"||term_temp.term_id=="T08"||term_temp.term_id=="T12"||term_temp.term_id=="T16"||term_temp.term_id=="T20"||term_temp.term_id=="T23"){
                            term_temp.term_name = "Fall";
                        } else {
                            term_temp.term_name = "Spring";
                        }

                        getline(str,course_temp.section_id,',');

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

bool has_suffix(const string& s, const string& suffix)
{
    return (s.size() >= suffix.size()) && equal(suffix.rbegin(), suffix.rend(), s.rbegin());    
}