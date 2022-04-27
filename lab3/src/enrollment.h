#include <string>
class StudentEnroll{
    private:
        string emplid;
        string grade;
        string course_num;

    public:
        StudentEnroll(string emplid,string course){
            emplid = emplid;
            course_num = course;
        }
        void setGrade(string grade){
            grade = grade;
        }
        
        string getGrade(){
            return grade;
        }
};