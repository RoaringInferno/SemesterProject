#include "commands.hpp"

#include <iostream>

#define CASE_BLOCK(command_id) case CommandID::command_id: run_##command_id(context, parsed_cli_args); break;

void execute_command(Context &context, CommandID command, largs::cli_parser &parsed_cli_args)
{
    switch (command)
    {
    CASE_BLOCK(LOGIN)
    CASE_BLOCK(LOGOUT)
    CASE_BLOCK(ACCOUNT_CREATE)
    CASE_BLOCK(ACCOUNT_DELETE)
    CASE_BLOCK(ACCOUNT_SET_USERNAME)
    CASE_BLOCK(ACCOUNT_SET_PASSWORD)
    CASE_BLOCK(ACCOUNT_SET_FIRST_NAME)
    CASE_BLOCK(ACCOUNT_SET_LAST_NAME)
    CASE_BLOCK(ACCOUNT_SET_PERSONAL_EMAIL)
    CASE_BLOCK(ACCOUNT_SET_SCHOOL_EMAIL)
    CASE_BLOCK(ACCOUNT_SET_PHONE)
    CASE_BLOCK(ACCOUNT_SET_TYPE)
    CASE_BLOCK(ACCOUNT_SUMMARY)
    CASE_BLOCK(ACCOUNT_GET_COURSES)
    CASE_BLOCK(COURSE_SUMMARY)
    CASE_BLOCK(COURSE_ADD_STUDENT)
    CASE_BLOCK(COURSE_REMOVE_STUDENT)
    CASE_BLOCK(COURSE_ADD_TEACHER)
    CASE_BLOCK(COURSE_REMOVE_TEACHER)
    CASE_BLOCK(COURSE_SET_NAME)
    CASE_BLOCK(COURSE_SET_DESCRIPTION)
    default:
        llog::file::push("\t[!] No handler for given command enum\n");
        break;
    }
}

#undef CASE_BLOCK

bool require_logged_in(Context &context)
{
    if (!context.account_data.get_logged_in())
    {
        std::cout << "Not logged in\n";
        llog::file::push("\t\tNot logged in\n");
        return false;
    }
    return true;
}

bool require_arg_count(largs::cli_parser &parsed_cli_args, size_t count)
{
    if (parsed_cli_args.argument_list().size() != count)
    {
        std::cout << "Incorrect number of arguments\n";
        llog::file::push("\t\tIncorrect number of arguments\n");
        return false;
    }
    return true;
}

bool require_admin_password(Context &context)
{
    while(true)
    {
        std::cout << "Enter admin username (\"cancel\" to cancel): ";
        std::string username;
        std::cin >> username;
        std::cout << "Enter admin password: ";
        std::string password;
        std::cin >> password;
        if (username == "cancel") return false;

        Account::ID account_id = context.account_manager.get_account_id(username);
        if (account_id == 0) {
            std::cout << "Account not found (Invalid Username)\n";
            llog::file::push("\t\t[!] Account not found (Invalid Username)\n");
            continue;
        }
        bool login_success = context.account_manager.login(account_id, password, context.account_data);
        if (login_success) {
            std::cout << "Login Successful\n";
            llog::file::push("\t\tLogin Successful\n");
            return true;
        } else {
            std::cout << "Login Failed (Invalid Password)\n";
            llog::file::push("\t\t[!] Login Failed (Invalid Password)\n");
            continue;
        }
    }
}

Context::~Context()
{
    account_manager.logout(account_data);
}