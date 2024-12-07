#include "course.hpp"

#include "light-csv"

void CourseManager::add_course(const Course &course)
{
    this->courses.push_back(course);
}

std::vector<Course *> CourseManager::get_account_courses(const Account::ID account_id)
{
    std::vector<Course *> result;
    for (auto &course : this->courses)
    {
        if (std::find(course.get_students().begin(), course.get_students().end(), account_id) != course.get_students().end() ||
            std::find(course.get_instructors().begin(), course.get_instructors().end(), account_id) != course.get_instructors().end())
        {
            result.push_back(&course);
        }
    }
    return result;
}

bool CourseManager::get_course_by_id(const Course::ID course_id, Course &course)
{
    for (auto &c : this->courses)
    {
        if (c.get_course_id() == course_id)
        {
            course = c;
            return true;
        }
    }
    return false;
}

CourseManager::CourseManager()
{
    lcsv::csv_file course_data(this->COURSE_FILE);
    lcsv::csv_file member_data(this->COURSE_MEMBER_FILE);
    std::vector<std::vector<std::string>> member_data_rows(member_data.size());
    for (auto &row : member_data_rows)
    {
        member_data_rows.push_back(
            {
                row[MEMBER_COURSE_ID],
                row[MEMBER_ACCOUNT_ID],
                row[MEMBER_TYPE]
            }
        );
    }

    for (size_t i = 0; i < course_data.size(); i++)
    {
        lcsv::csv_row::iterator course_row = course_data[i].begin();
        const std::string & raw_course_id = course_row[0];
        const std::string & raw_course_name = course_row[1];
        const std::string & raw_course_description = course_row[2];
        std::vector<std::vector<std::string>> member_rows;
        for (auto &row : member_data_rows)
        {
            if (row[0] != raw_course_id)
            {
                continue;
            }
            member_rows.push_back(
                {
                    row[MEMBER_ACCOUNT_ID],
                    row[MEMBER_TYPE]
                }
            );
        }
        Course course(
            raw_course_id,
            raw_course_name,
            raw_course_description,
            member_rows
        );
        this->courses.push_back(course);
    }
}

CourseManager::~CourseManager() { this->write(); }

Course::MEMBER_TYPE Course::decode_type(const std::string &type)
{
    switch (type[0])
    {
        case 'S':
            return Course::MEMBER_TYPE::STUDENT;
        case 'I':
            return Course::MEMBER_TYPE::INSTRUCTOR;
        default:
            return Course::MEMBER_TYPE::STUDENT;
    }
}

std::string Course::encode_type(const MEMBER_TYPE &type)
{
    switch (type)
    {
        case Course::MEMBER_TYPE::STUDENT:
            return "STUDENT";
        case Course::MEMBER_TYPE::INSTRUCTOR:
            return "INSTRUCTOR";
        default:
            return "STUDENT";
    }
}

Course::Course(const std::string &course_id, const std::string &course_name, const std::string &course_description, const std::vector<std::vector<std::string>> &member_relationships) :
    course_id(std::stoi(course_id)),
    course_name(course_name),
    course_description(course_description)
{
    for (const auto &relationship : member_relationships)
    {
        const std::string &raw_member_id = relationship[0];
        const std::string &raw_member_type = relationship[1];


        if (relationship.size() != 2)
        {
            continue;
        }
        const ID member_id = std::stoi(raw_member_id);
        const MEMBER_TYPE member_type = Course::decode_type(raw_member_type);
        switch (member_type)
        {
            case Course::MEMBER_TYPE::STUDENT:
                this->students.push_back(member_id);
                break;
            case Course::MEMBER_TYPE::INSTRUCTOR:
                this->instructors.push_back(member_id);
                break;
            default:
                break;
        }
    }
}

std::vector<std::string> Course::to_string() const
{
    std::vector<std::string> result = {
        std::to_string(this->course_id),
        this->course_name,
        this->course_description
    };
    return result;
}

std::vector<std::vector<std::string>> Course::member_to_strings() const
{
    std::vector<std::vector<std::string>> result;
    for (const auto &student_id : this->students)
    {
        result.push_back({std::to_string(this->course_id), std::to_string(student_id), "STUDENT"});
    }
    for (const auto &instructor_id : this->instructors)
    {
        result.push_back({std::to_string(this->course_id), std::to_string(instructor_id), "INSTRUCTOR"});
    }
    return result;
}

bool Course::remove_student(const Account::ID account_id)
{
    for (auto it = this->students.begin(); it != this->students.end(); it++)
    {
        if (*it == account_id)
        {
            this->students.erase(it);
            return true;
        }
    }
    return false;
}

bool Course::remove_instructor(const Account::ID account_id)
{
    for (auto it = this->instructors.begin(); it != this->instructors.end(); it++)
    {
        if (*it == account_id)
        {
            this->instructors.erase(it);
            return true;
        }
    }
    return false;
}

void CourseManager::write() const
{
    lcsv::csv_file course_data(this->COURSE_FILE);
    lcsv::csv_file member_data(this->COURSE_MEMBER_FILE);
    course_data.header() = this->COURSE_HEADER;
    member_data.header() = this->COURSE_MEMBER_HEADER;
    course_data.clear();
    member_data.clear();
    course_data.reserve(this->courses.size());
    for (const auto &course : this->courses)
    {
        course_data.push_back(course.to_string());
        std::vector<std::vector<std::string>> member_strings = course.member_to_strings();
        member_data.reserve(member_strings.size());
        for (const auto &member : member_strings)
        {
            member_data.push_back(member);
        }
    }
    course_data.write();
    member_data.write();
}
