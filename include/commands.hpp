#pragma once

#include "account.hpp"
#include "course.hpp"
#include "command_id.hpp"

#include "light-log"
#include "cli_parser"

#include <iostream>

struct Context
{
    Account account_data;
    AccountManager account_manager;

    CourseManager course_manager;

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
void run_ACCOUNT_SUMMARY(Context &context, largs::cli_parser &parsed_cli_args);
void run_ACCOUNT_GET_COURSES(Context &context, largs::cli_parser &parsed_cli_args);
void run_COURSE_SUMMARY(Context &context, largs::cli_parser &parsed_cli_args);
void run_COURSE_ADD_STUDENT(Context &context, largs::cli_parser &parsed_cli_args);
void run_COURSE_REMOVE_STUDENT(Context &context, largs::cli_parser &parsed_cli_args);
void run_COURSE_ADD_TEACHER(Context &context, largs::cli_parser &parsed_cli_args);
void run_COURSE_REMOVE_TEACHER(Context &context, largs::cli_parser &parsed_cli_args);
void run_COURSE_SET_NAME(Context &context, largs::cli_parser &parsed_cli_args);
void run_COURSE_SET_DESCRIPTION(Context &context, largs::cli_parser &parsed_cli_args);

bool require_logged_in(Context &context);
bool require_arg_count(largs::cli_parser &parsed_cli_args, size_t count);
bool require_admin_password(Context &context);