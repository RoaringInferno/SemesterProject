#include "commands.hpp"

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