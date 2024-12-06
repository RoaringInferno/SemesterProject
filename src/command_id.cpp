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
    return ID::ERR;
}

CommandID::CommandID(std::string_view raw_command) :
    id(GetId(raw_command))
{}
