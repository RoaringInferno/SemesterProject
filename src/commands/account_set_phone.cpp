#include "commands.hpp"

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