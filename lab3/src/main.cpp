#include "readAndWrite.h"

int main (){
    vector<Student> student;
    vector<Instructor> instructor;
    vector<Course> course;
    vector<Term> term;

    readData(student,instructor,course,term);

    cout << term.size() << endl;

    for (int i = 0; i < term.size();i++){
        cout << term[i].term_id << endl;
    }
}