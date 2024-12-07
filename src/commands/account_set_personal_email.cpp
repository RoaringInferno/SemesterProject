#include "commands.hpp"

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