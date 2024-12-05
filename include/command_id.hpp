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
        LOGOUT
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