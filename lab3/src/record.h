#include <string>
using namespace std;

struct Term
{
    string term_id;
    string term_name;
};

struct Course
{
    int course_id;
    string section_id;
    struct Term term;
};

struct Instructor
{
    string instructor_id;
    struct Course course;
    Term term;
};

struct Student
{
    string id;
    string grade;
    char pass;
    struct Instructor instructor;
};