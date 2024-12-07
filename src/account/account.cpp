#include "account.hpp"

#include "filesystem.hpp"

#include "light-log"

Account::ACCOUNT_TYPE Account::decode_type(const std::string &type)
{
    switch (type[0])
    {
    case 'A':
        return ADMIN;
    case 'I':
        return INSTRUCTOR;
    case 'S':
        return STUDENT;
    default:
        return STUDENT;
    }
}

std::string Account::encode_type(const ACCOUNT_TYPE &type)
{
    switch (type)
    {
    case ADMIN:
        return "ADMIN";
    case INSTRUCTOR:
        return "INSTRUCTOR";
    case STUDENT:
        return "STUDENT";
    default:
        return "STUDENT";
    }
}

Account::Account()
{
}

Account::~Account()
{
}
