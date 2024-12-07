#include "commands.hpp"

void run_ACCOUNT_SUMMARY(Context &context, largs::cli_parser &parsed_cli_args)
{
    if (!require_logged_in(context)) return;

    if (!require_arg_count(parsed_cli_args, 1)) return;

    Account::ID account_id = std::stoi(std::string(parsed_cli_args.argument_list()[0].argument_value));

    Account account;
    bool account_found = context.account_manager.get_account(account_id, account);

    std::cout <<
        "Account Summary\n" <<
        "Account ID: " << account.get_account_id() << '\n' <<
        "Username: " << account.get_username() << '\n' <<
        "Password: " << account.get_password() << '\n' <<
        "Personal Email: " << account.get_personal_email() << '\n' <<
        "School Email: " << account.get_school_email() << '\n' <<
        "Phone: " << account.get_phone() << '\n' <<
        "First Name: " << account.get_first_name() << '\n' <<
        "Last Name: " << account.get_last_name() << '\n' <<
        "Type: " << Account::encode_type(account.get_type()) << '\n'
        << std::flush
    ;
}