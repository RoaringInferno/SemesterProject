#pragma once

#include "account.hpp"
#include "account_manager.hpp"
#include "command_id.hpp"

#include "light-log"
#include "cli_parser"

#include <iostream>

struct Context
{
    Account account_data;
    AccountManager account_manager;

    ~Context();
};

void execute_command(Context &context, CommandID command, largs::cli_parser &parsed_cli_args);

void run_LOGIN(Context &context, largs::cli_parser &parsed_cli_args);
void run_LOGOUT(Context &context, largs::cli_parser &parsed_cli_args);
void run_ACCOUNT_CREATE(Context &context, largs::cli_parser &parsed_cli_args);
void run_ACCOUNT_DELETE(Context &context, largs::cli_parser &parsed_cli_args);
void run_ACCOUNT_SET_USERNAME(Context &context, largs::cli_parser &parsed_cli_args);
void run_ACCOUNT_SET_PASSWORD(Context &context, largs::cli_parser &parsed_cli_args);
void run_ACCOUNT_SET_FIRST_NAME(Context &context, largs::cli_parser &parsed_cli_args);
void run_ACCOUNT_SET_LAST_NAME(Context &context, largs::cli_parser &parsed_cli_args);
void run_ACCOUNT_SET_PERSONAL_EMAIL(Context &context, largs::cli_parser &parsed_cli_args);
void run_ACCOUNT_SET_SCHOOL_EMAIL(Context &context, largs::cli_parser &parsed_cli_args);
void run_ACCOUNT_SET_PHONE(Context &context, largs::cli_parser &parsed_cli_args);
void run_ACCOUNT_SET_TYPE(Context &context, largs::cli_parser &parsed_cli_args);

bool require_logged_in(Context &context);
bool require_arg_count(largs::cli_parser &parsed_cli_args, size_t count);
bool require_admin_password(Context &context);