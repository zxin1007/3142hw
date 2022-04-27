#include "readAndWrite.h"
#include "function.h"
#include "enrollment.h"
int main (){
    vector<Student> student;
    vector<Instructor> instructor;
    vector<Course> course;
    vector<Term> term;

    readData(student,instructor,course);

    //mode 1 = instructor
    //modee 2 = course number
    //mode 3 = term
    int mode;

    pass_rate(student, 3);

    //class for new enrollment
    StudentEnroll student_enroll("123", "T10");

    printf("--- Finish execution ---");
}