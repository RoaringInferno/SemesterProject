#include "commands.hpp"

#include "io.hpp"

void run_COURSE_SUMMARY(Context &context, largs::cli_parser &parsed_cli_args)
{
    if (!require_arg_count(parsed_cli_args, 1)) return;

    auto course_id = std::stoi(std::string(parsed_cli_args.argument_list()[0].argument_value));

    Course course;
    bool found = context.course_manager.get_course_by_id(course_id, course);
    if (!found)
    {
        std::cout << "Course not found" << std::endl;
        llog::file::push("\t\t[!] Course not found");
        return;
    }

    std::cout << 
        "Course Summary\n" <<
        "Course ID: " << course.get_course_id() << "\n" <<
        "Course Name: " << course.get_course_name() << "\n" <<
        "Course Description: " << course.get_course_description() << "\n"
        << std::flush;
    ;


    std::vector<std::string> member_table_header = {"ID", "Name", "Type"};
    std::vector<std::vector<std::string>> member_table;

    for (auto student_id : course.get_students())
    {
        Account student;
        bool found = context.account_manager.get_account(student_id, student);
        if (!found)
        {
            std::cout << "Student #"<<student_id<<"not found" << std::endl;
            llog::file::push("\t\t[!] Student #"+std::to_string(student_id)+" not found");
            continue;
        }

        member_table.push_back({
            std::to_string(student.get_account_id()),
            student.get_first_name() + " " + student.get_last_name(),
            "Student"
        });
    }
    for (auto instructor_id : course.get_instructors())
    {
        Account instructor;
        bool found = context.account_manager.get_account(instructor_id, instructor);
        if (!found)
        {
            std::cout << "Student #"<<instructor_id<<"not found" << std::endl;
            llog::file::push("\t\t[!] Student #"+std::to_string(instructor_id)+" not found");
            continue;
        }

        member_table.push_back({
            std::to_string(instructor.get_account_id()),
            instructor.get_first_name() + " " + instructor.get_last_name(),
            "Instructor"
        });
    }
}