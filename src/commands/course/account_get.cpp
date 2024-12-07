#include "commands.hpp"

#include "io.hpp"

void run_ACCOUNT_GET_COURSES(Context &context, largs::cli_parser &parsed_cli_args)
{
    if (!require_logged_in(context)) return;
    if (!require_arg_count(parsed_cli_args, 0)) return;

    auto account_id = context.account_data.get_account_id();
    Account accont;
    bool found = context.account_manager.get_account(account_id, accont);
    if (!found) {
        std::cout << "Account not found\n";
        llog::file::push("\t\t[!] Account not found\n");
        return;
    }

    std::vector<Course*> courses = context.course_manager.get_account_courses(account_id);

    std::vector<std::string> table_header = {"Course ID", "Course Name", "Course Description"};
    std::vector<std::vector<std::string>> table_data;
    for (auto course : courses) {
        table_data.push_back({
            std::to_string(course->get_course_id()),
            course->get_course_name(),
            course->get_course_description()
        });
    }
    print_table(table_header, table_data);
}