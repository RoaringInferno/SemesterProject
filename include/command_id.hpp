#pragma once

#include <string_view>

class CommandID
{
public:
    enum ID : int
    {
        ERR = -1,
        EXIT = 0,
        LOGIN,
        LOGOUT,
        ACCOUNT_CREATE,
        ACCOUNT_DELETE,
        ACCOUNT_SET_USERNAME,
        ACCOUNT_SET_PASSWORD,
        ACCOUNT_SET_FIRST_NAME,
        ACCOUNT_SET_LAST_NAME,
        ACCOUNT_SET_PERSONAL_EMAIL,
        ACCOUNT_SET_SCHOOL_EMAIL,
        ACCOUNT_SET_PHONE,
        ACCOUNT_SET_TYPE
    };
private:
    ID id{ERR};
public:
    static ID GetId(std::string_view raw_command);
public:
    CommandID() = default;
    CommandID(std::string_view raw_command);

    operator ID() const { return id; }

    CommandID& operator=(ID new_id) { id = new_id; return *this; }
};