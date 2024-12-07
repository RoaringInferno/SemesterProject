#include "commands.hpp"

void run_COURSE_ADD_STUDENT(Context &context, largs::cli_parser &parsed_cli_args)
{
    if (!require_logged_in(context)) return;
    if (!require_admin_password(context)) return;
    if (!require_arg_count(parsed_cli_args, 2)) return;

    Course::ID course_id = std::stoi(std::string(parsed_cli_args.argument_list()[0].argument_value));
    Account::ID account_id = std::stoi(std::string(parsed_cli_args.argument_list()[1].argument_value));

    Course course;
    bool found = context.course_manager.get_course_by_id(course_id, course);
    if (!found)
    {
        std::cout << "Course not found." << std::endl;
        llog::file::push("\t\t[!] Course not found.");
        return;
    }

    course.add_student(account_id);
}

void run_COURSE_REMOVE_STUDENT(Context &context, largs::cli_parser &parsed_cli_args)
{
    if (!require_logged_in(context)) return;
    if (!require_admin_password(context)) return;
    if (!require_arg_count(parsed_cli_args, 2)) return;

    Course::ID course_id = std::stoi(std::string(parsed_cli_args.argument_list()[0].argument_value));
    Account::ID account_id = std::stoi(std::string(parsed_cli_args.argument_list()[1].argument_value));

    Course course;
    bool found = context.course_manager.get_course_by_id(course_id, course);
    if (!found)
    {
        std::cout << "Course not found." << std::endl;
        llog::file::push("\t\t[!] Course not found.");
        return;
    }

    if (!course.remove_student(account_id))
    {
        std::cout << "Student not found." << std::endl;
        llog::file::push("\t\t[!] Student not found.");
        return;
    }
}

void run_COURSE_ADD_TEACHER(Context &context, largs::cli_parser &parsed_cli_args)
{
    if (!require_logged_in(context)) return;
    if (!require_admin_password(context)) return;
    if (!require_arg_count(parsed_cli_args, 2)) return;

    Course::ID course_id = std::stoi(std::string(parsed_cli_args.argument_list()[0].argument_value));
    Account::ID account_id = std::stoi(std::string(parsed_cli_args.argument_list()[1].argument_value));

    Course course;
    bool found = context.course_manager.get_course_by_id(course_id, course);
    if (!found)
    {
        std::cout << "Course not found." << std::endl;
        llog::file::push("\t\t[!] Course not found.");
        return;
    }

    course.add_instructor(account_id);
}

void run_COURSE_REMOVE_TEACHER(Context &context, largs::cli_parser &parsed_cli_args)
{
    if (!require_logged_in(context)) return;
    if (!require_admin_password(context)) return;
    if (!require_arg_count(parsed_cli_args, 2)) return;

    Course::ID course_id = std::stoi(std::string(parsed_cli_args.argument_list()[0].argument_value));
    Account::ID account_id = std::stoi(std::string(parsed_cli_args.argument_list()[1].argument_value));

    Course course;
    bool found = context.course_manager.get_course_by_id(course_id, course);
    if (!found)
    {
        std::cout << "Course not found." << std::endl;
        llog::file::push("\t\t[!] Course not found.");
        return;
    }

    if (!course.remove_instructor(account_id))
    {
        std::cout << "Teacher not found." << std::endl;
        llog::file::push("\t\t[!] Teacher not found.");
        return;
    }
}

void run_COURSE_SET_NAME(Context &context, largs::cli_parser &parsed_cli_args)
{
    if (!require_logged_in(context)) return;
    if (!require_admin_password(context)) return;
    if (!require_arg_count(parsed_cli_args, 2)) return;

    Course::ID course_id = std::stoi(std::string(parsed_cli_args.argument_list()[0].argument_value));

    Course course;
    bool found = context.course_manager.get_course_by_id(course_id, course);
    if (!found)
    {
        std::cout << "Course not found." << std::endl;
        llog::file::push("\t\t[!] Course not found.");
        return;
    }

    course.set_course_name(std::string(parsed_cli_args.argument_list()[1].argument_value));
}

void run_COURSE_SET_DESCRIPTION(Context &context, largs::cli_parser &parsed_cli_args)
{
    if (!require_logged_in(context)) return;
    if (!require_admin_password(context)) return;
    if (!require_arg_count(parsed_cli_args, 2)) return;

    Course::ID course_id = std::stoi(std::string(parsed_cli_args.argument_list()[0].argument_value));
    Account::ID account_id = std::stoi(std::string(parsed_cli_args.argument_list()[1].argument_value));

    Course course;
    bool found = context.course_manager.get_course_by_id(course_id, course);
    if (!found)
    {
        std::cout << "Course not found." << std::endl;
        llog::file::push("\t\t[!] Course not found.");
        return;
    }

    course.set_course_description(std::string(parsed_cli_args.argument_list()[1].argument_value));
}
