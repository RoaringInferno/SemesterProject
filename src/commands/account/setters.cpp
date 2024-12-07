#include "commands.hpp"

void run_ACCOUNT_SET_FIRST_NAME(Context &context, largs::cli_parser &parsed_cli_args)
{
    if (!require_logged_in(context)) return;
    if (!require_arg_count(parsed_cli_args, 1))
    {
        std::cout << "Usage: account_set_first_name <first_name>\n";
        return;
    }

    context.account_data.set_first_name(std::string(parsed_cli_args.begin()->argument_value));
    std::cout << "First name updated\n";
    llog::file::push("\t\tFirst name set to: " + context.account_data.get_first_name());
}

void run_ACCOUNT_SET_LAST_NAME(Context &context, largs::cli_parser &parsed_cli_args)
{
    if (!require_logged_in(context)) return;
    if (!require_arg_count(parsed_cli_args, 1))
    {
        std::cout << "Usage: account_set_last_name <last_name>\n";
        return;
    }

    context.account_data.set_last_name(std::string(parsed_cli_args.begin()->argument_value));
    std::cout << "Last name updated\n";
    llog::file::push("\t\tLast name set to: " + context.account_data.get_last_name());
}

void run_ACCOUNT_SET_PASSWORD(Context &context, largs::cli_parser &parsed_cli_args)
{
    llog::file::push("\tCommandID::ACCOUNT_SET_PASSWORD\n");
    if (!require_logged_in(context)) return;
    if (!require_arg_count(parsed_cli_args, 1)) {
        std::cout << "Usage: account-set-password <password>\n";
        return;
    }
    context.account_data.set_password(parsed_cli_args.begin()->argument_value.data());
    std::cout << "Password set\n";
    llog::file::push("\t\tPassword set\n");
}

void run_ACCOUNT_SET_PERSONAL_EMAIL(Context &context, largs::cli_parser &parsed_cli_args)
{
    if (!require_logged_in(context)) return;
    if (!require_arg_count(parsed_cli_args, 1))
    {
        std::cout << "Usage: account_set_personal_email <email>" << std::endl;
        return;
    }

    std::string email(parsed_cli_args.begin()->argument_value);

    context.account_data.set_personal_email(email);

    std::cout << "Personal email set to: " << email << std::endl;
    llog::file::push("\t\tPersonal email set to: " + email + "\n");
}

void run_ACCOUNT_SET_PHONE(Context &context, largs::cli_parser &parsed_cli_args)
{
    if (!require_logged_in(context)) return;

    if (!require_arg_count(parsed_cli_args, 1))
    {
        std::cout << "Usage: account_set_phone <phone>" << std::endl;
        return;
    }

    std::string phone(parsed_cli_args.begin()->argument_value);
    context.account_data.set_phone(phone);

    std::cout << "Phone number set to: " << phone << std::endl;
    llog::file::push("Phone number set to: " + phone + "\n");
}

void run_ACCOUNT_SET_SCHOOL_EMAIL(Context &context, largs::cli_parser &parsed_cli_args)
{
    if (!require_logged_in(context)) return;

    if (!require_arg_count(parsed_cli_args, 1))
    {
        std::cout << "Usage: account_set_school_email <email>" << std::endl;
        return;
    }

    std::string email(parsed_cli_args.begin()->argument_value);
    context.account_data.set_school_email(email);

    std::cout << "School email set to: " << email << std::endl;
    llog::file::push("School email set to: " + email + "\n");
}

void run_ACCOUNT_SET_TYPE(Context &context, largs::cli_parser &parsed_cli_args)
{
    if (!require_logged_in(context)) return;

    if (!require_arg_count(parsed_cli_args, 1))
    {
        std::cout << "Usage: account set type <ADMIN|STUDENT|INSTRUCTOR>" << std::endl;
        return;
    }
    if (!require_admin_password(context)) 
    {
        std::cout << "Requires admin authorization" << std::endl;
        return;
    }

    std::string type(parsed_cli_args.begin()->argument_value);
    Account::ACCOUNT_TYPE new_type = Account::decode_type(type);

    context.account_data.set_type(new_type);

    std::cout << "Account type set to " << type << std::endl;
    llog::file::push("\t\tAccount type set to " + type + "\n");
}

void run_ACCOUNT_SET_USERNAME(Context &context, largs::cli_parser &parsed_cli_args)
{
    llog::file::push("\tCommandID::ACCOUNT_SET_USERNAME\n");
    if (!require_logged_in(context)) return;
    if (!require_arg_count(parsed_cli_args, 1)) {
        std::cout << "Usage: account-set-username <username>\n";
        return;
    }
    if (!require_logged_in(context)) return;
    context.account_data.set_username(parsed_cli_args.begin()->argument_value.data());
    std::cout << "Username set to: " << context.account_data.get_username() << "\n";
    llog::file::push("\t\tUsername set to: " + context.account_data.get_username() + "\n");
}