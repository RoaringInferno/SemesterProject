#pragma once

#include "account.hpp"

#include "filesystem.hpp"

#include <vector>
#include <string>

class Course
{
public:
    typedef unsigned int ID;

    enum MEMBER_TYPE : unsigned char
    {
        STUDENT,
        INSTRUCTOR
    };

    static MEMBER_TYPE decode_type(const std::string &type);
    static std::string encode_type(const MEMBER_TYPE &type);
private:
    ID course_id{0};
    std::string course_name{"course_name"};
    std::string course_description{"course_description"};
    std::vector<Account::ID> students;
    std::vector<Account::ID> instructors;
public: // Getters
    ID get_course_id() const { return this->course_id; };
    std::string get_course_name() const { return this->course_name; };
    std::string get_course_description() const { return this->course_description; };
    std::vector<Account::ID> get_students() const { return this->students; };
    std::vector<Account::ID> get_instructors() const { return this->instructors; };
public: // Setters
    void set_course_id(const ID& new_value) { this->course_id = new_value; };
    void set_course_name(const std::string& new_value) { this->course_name = new_value; };
    void set_course_description(const std::string& new_value) { this->course_description = new_value; };
    void set_students(const std::vector<Account::ID>& new_value) { this->students = new_value; };
    void set_instructors(const std::vector<Account::ID>& new_value) { this->instructors = new_value; };
public:
    Course() = default;
    ~Course() = default;

    Course(
        const std::string &course_id,
        const std::string &course_name,
        const std::string &course_description,
        const std::vector<std::vector<std::string>> &member_relationships
    );

    std::vector<std::string> to_string() const;
    std::vector<std::vector<std::string>> member_to_strings() const;
public:
    void add_student(const Account::ID account_id) { this->students.push_back(account_id); };
    void add_instructor(const Account::ID account_id) { this->instructors.push_back(account_id); };

    bool remove_student(const Account::ID account_id);
    bool remove_instructor(const Account::ID account_id);
};

class CourseManager
{
public:
    const std::string COURSE_FILE{DATA_DIR + "courses.csv"};
    const std::vector<std::string> COURSE_HEADER{
        "course_id",
        "course_name",
        "course_description"
    };
    enum COURSE_HEADER_INDEX : unsigned char
    {
        COURSE_ID,
        COURSE_NAME,
        COURSE_DESCRIPTION
    };

    const std::string COURSE_MEMBER_FILE{DATA_DIR + "course_members.csv"};
    const std::vector<std::string> COURSE_MEMBER_HEADER{
        "course_id",
        "account_id",
        "member_type"
    };
    enum COURSE_MEMBER_HEADER_INDEX : unsigned char
    {
        MEMBER_COURSE_ID,
        MEMBER_ACCOUNT_ID,
        MEMBER_TYPE
    };
private:
    std::vector<Course> courses;
public:
    std::vector<Course> get_courses() const { return this->courses; };
public:
    void write() const;

    void add_course(const Course& course);

    std::vector<Course*> get_account_courses(const Account::ID account_id);

    bool get_course_by_id(const Course::ID course_id, Course& course);
public:
    CourseManager();
    ~CourseManager();
};