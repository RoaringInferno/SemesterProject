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