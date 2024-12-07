#include "command_id.hpp"

CommandID::ID CommandID::GetId(std::string_view raw_command)
{
    // if (raw_command == "exit") return ID::EXIT;
    // if (raw_command == "login") return ID::LOGIN;
    // if (raw_command == "logout") return ID::LOGOUT;
    // if (raw_command == "account-create") return ID::ACCOUNT_CREATE;
    // if (raw_command == "account-delete") return ID::ACCOUNT_DELETE;
    // if (raw_command == "account-set-username") return ID::ACCOUNT_SET_USERNAME;
    // if (raw_command == "account-set-password") return ID::ACCOUNT_SET_PASSWORD;
    // if (raw_command == "account-set-first-name") return ID::ACCOUNT_SET_FIRST_NAME;
    // if (raw_command == "account-set-last-name") return ID::ACCOUNT_SET_LAST_NAME;
    // if (raw_command == "account-set-personal-email") return ID::ACCOUNT_SET_PERSONAL_EMAIL;
    // if (raw_command == "account-set-school-email") return ID::ACCOUNT_SET_SCHOOL_EMAIL;
    // if (raw_command == "account-set-phone") return ID::ACCOUNT_SET_PHONE;
    // if (raw_command == "account-set-type") return ID::ACCOUNT_SET_TYPE;
    // if (raw_command == "account-summary") return ID::ACCOUNT_SUMMARY;
    // if (raw_command == "account-get-courses") return ID::ACCOUNT_GET_COURSES;
    // if (raw_command == "course-summary") return ID::COURSE_SUMMARY;
    // if (raw_command == "course-add-student") return ID::COURSE_ADD_STUDENT;
    // if (raw_command == "course-remove-student") return ID::COURSE_REMOVE_STUDENT;
    // if (raw_command == "course-add-teacher") return ID::COURSE_ADD_TEACHER;
    // if (raw_command == "course-remove-teacher") return ID::COURSE_REMOVE_TEACHER;
    // if (raw_command == "course-set-name") return ID::COURSE_SET_NAME;
    // if (raw_command == "course-set-description") return ID::COURSE_SET_DESCRIPTION;

    /*
    For closed set of strings:
    - exit
    - login
    - logout
    - account
    - course
    ([0] & [3]) with opcount 1 and tightness 11 has hash table: 100 104 108 97 98
    ([0] & [3])-97 : 3 7 11 0 1
    */
    size_t offset = 0;
    switch((raw_command[0] & raw_command[3])-97)
    {
    case 3: // exit
        return ID::EXIT;
    case 7: // login
        return ID::LOGIN;
    case 11: // logout
        return ID::LOGOUT;
    case 0: // account
        /*
        For closed set of strings:
        - create
        - delete
        - set
        - summary
        - get
        ([0] & [1]) with opcount 1 and tightness 16 has hash table: 98 100 97 113 101
        ([0] & [1])-97 : 1 3 0 2 4
        */
        offset += 7 + 1;
        switch((raw_command[0+offset] & raw_command[1+offset])-97)
        {
        case 1: // create
            return ID::ACCOUNT_CREATE;
        case 3: // delete
            return ID::ACCOUNT_DELETE;
        case 0: // set
            /*
            For closed set of strings:
            - username
            - password
            - first
            - last
            - personal
            - school
            - phone
            - type
            ([0] | [1]) with opcount 1 and tightness 16 has hash table: 119 113 111 109 117 115 120 125
            ([0] | [1])-109 : 10 4 2 0 8 6 11 16
            */
            offset += 3 + 1;
            switch((raw_command[0+offset] | raw_command[1+offset])-109)
            {
            case 10: // username
                return ID::ACCOUNT_SET_USERNAME;
            case 4: // password
                return ID::ACCOUNT_SET_PASSWORD;
            case 2: // first
                return ID::ACCOUNT_SET_FIRST_NAME;
            case 0: // last
                return ID::ACCOUNT_SET_LAST_NAME;
            case 8: // personal
                return ID::ACCOUNT_SET_PERSONAL_EMAIL;
            case 6: // school
                return ID::ACCOUNT_SET_SCHOOL_EMAIL;
            case 11: // phone
                return ID::ACCOUNT_SET_PHONE;
            case 16: // type
                return ID::ACCOUNT_SET_TYPE;
            }
        case 2: // summary
            return ID::ACCOUNT_SUMMARY;
        case 4: // get
            return ID::ACCOUNT_GET_COURSES;
        }
    case 1: // course
        /*
        For closed set of strings:
        - summary
        - add
        - remove
        - set
        ([0] ^ [1]) with opcount 1 and tightness 18 has hash table: 6 5 23 22
        ([0] ^ [1])-5 : 1 0 18 17
        */
        offset += 6 + 1;
        switch((raw_command[0+offset] ^ raw_command[1+offset])-5)
        {
        case 1: // summary
            return ID::COURSE_SUMMARY;
        case 0: // add
            offset += 3 + 1;
            switch (raw_command[0+offset])
            {
                case 's': return ID::COURSE_ADD_STUDENT;
                case 't': return ID::COURSE_ADD_TEACHER;
            }
        case 18: // remove
            offset += 6 + 1;
            switch (raw_command[0+offset])
            {
                case 's': return ID::COURSE_REMOVE_STUDENT;
                case 't': return ID::COURSE_REMOVE_TEACHER;
            }
        case 17: // set
            offset += 3 + 1;
            switch (raw_command[0+offset])
            {
                case 'n': return ID::COURSE_SET_NAME;
                case 'd': return ID::COURSE_SET_DESCRIPTION;
            }
        }
    }
    return ID::ERR;
}

CommandID::CommandID(std::string_view raw_command) :
    id(GetId(raw_command))
{}
