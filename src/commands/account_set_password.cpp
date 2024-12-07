#include "commands.hpp"

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