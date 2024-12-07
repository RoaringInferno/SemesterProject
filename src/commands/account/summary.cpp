#include "commands.hpp"

void run_ACCOUNT_SUMMARY(Context &context, largs::cli_parser &parsed_cli_args)
{
    if (!require_logged_in(context)) return;

    if (!require_arg_count(parsed_cli_args, 0)) return;

    std::cout <<
        "Account Summary\n" <<
        "Account ID: " << context.account_data.get_account_id() << '\n' <<
        "Username: " << context.account_data.get_username() << '\n' <<
        "Password: " << context.account_data.get_password() << '\n' <<
        "Personal Email: " << context.account_data.get_personal_email() << '\n' <<
        "School Email: " << context.account_data.get_school_email() << '\n' <<
        "Phone: " << context.account_data.get_phone() << '\n' <<
        "First Name: " << context.account_data.get_first_name() << '\n' <<
        "Last Name: " << context.account_data.get_last_name() << '\n' <<
        "Type: " << Account::encode_type(context.account_data.get_type()) << '\n'
        << std::flush
    ;
}