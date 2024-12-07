#include "command_id.hpp"

CommandID::ID CommandID::GetId(std::string_view raw_command)
{
    /*
    NOTE: Replace with a hashing funciton once all commands are known
    */

    if (raw_command == "exit") return ID::EXIT;
    if (raw_command == "login") return ID::LOGIN;
    if (raw_command == "logout") return ID::LOGOUT;
    if (raw_command == "account-create") return ID::ACCOUNT_CREATE;
    if (raw_command == "account-delete") return ID::ACCOUNT_DELETE;
    if (raw_command == "account-set-username") return ID::ACCOUNT_SET_USERNAME;
    if (raw_command == "account-set-password") return ID::ACCOUNT_SET_PASSWORD;
    if (raw_command == "account-set-first-name") return ID::ACCOUNT_SET_FIRST_NAME;
    if (raw_command == "account-set-last-name") return ID::ACCOUNT_SET_LAST_NAME;
    if (raw_command == "account-set-personal-email") return ID::ACCOUNT_SET_PERSONAL_EMAIL;
    if (raw_command == "account-set-school-email") return ID::ACCOUNT_SET_SCHOOL_EMAIL;
    if (raw_command == "account-set-phone") return ID::ACCOUNT_SET_PHONE;
    if (raw_command == "account-set-type") return ID::ACCOUNT_SET_TYPE;
    if (raw_command == "account-summary") return ID::ACCOUNT_SUMMARY;
    if (raw_command == "account-get-courses") return ID::ACCOUNT_GET_COURSES;
    if (raw_command == "course-summary") return ID::COURSE_SUMMARY;
    if (raw_command == "course-add-student") return ID::COURSE_ADD_STUDENT;
    if (raw_command == "course-remove-student") return ID::COURSE_REMOVE_STUDENT;
    if (raw_command == "course-add-teacher") return ID::COURSE_ADD_TEACHER;
    if (raw_command == "course-remove-teacher") return ID::COURSE_REMOVE_TEACHER;
    if (raw_command == "course-set-name") return ID::COURSE_SET_NAME;
    if (raw_command == "course-set-description") return ID::COURSE_SET_DESCRIPTION;
    return ID::ERR;
}

CommandID::CommandID(std::string_view raw_command) :
    id(GetId(raw_command))
{}
