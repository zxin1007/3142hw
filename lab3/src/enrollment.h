#include <string>
//class of student new enrollement
class StudentEnroll{
    private:
        string emplid;
        string grade;
        string course_num;

    public:
        StudentEnroll(string id,string course){
            emplid = id;
            course_num = course;
        }
        void setGrade(string newGrade){
            grade = newGrade;
        }
        
        string getGrade(){
            return grade;
        }

        string getId(){
            return emplid;
        }
};