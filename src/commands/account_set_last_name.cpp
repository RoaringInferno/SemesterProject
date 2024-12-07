#include "commands.hpp"

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