#include <string>
using namespace std;

struct Term
{
    string term_id;
    string term_name;

    bool operator!=(const Term& other) const
    {
        return term_id != other.term_id;
    }
};

struct Course
{
    int course_id;
    string section_id;
    struct Term term;
};

struct Student
{
    string id;
    string grade;
    Course course;
};

struct Instructor
{
    string instructor_id;
    struct Course course;
    Term term;
};