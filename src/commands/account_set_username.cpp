#include "commands.hpp"

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