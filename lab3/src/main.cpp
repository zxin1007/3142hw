#include "readAndWrite.h"
#include "function.h"
#include "enrollment.h"
int main (){
    vector<Student> student;

    //read in the data
    readData(student);

    //mode 1 = instructor
    //modee 2 = course number
    //mode 3 = term
    int mode;

    pass_rate(student, 1);
    pass_rate(student, 2);
    pass_rate(student, 3);

    w_rate(student, 1);
    w_rate(student, 2);
    w_rate(student, 3);

    //class for new enrollment
    StudentEnroll student_enroll("123", "T10");
    student_enroll.setGrade("B");

    printf("Grade for student %s is %s\n", student_enroll.getId().c_str(), student_enroll.getGrade().c_str());

    printf("--- Finish execution, outputs are under the output folder ---");
}