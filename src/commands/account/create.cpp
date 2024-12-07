#include "commands.hpp"

void run_ACCOUNT_CREATE(Context &context, largs::cli_parser &parsed_cli_args)
{
    llog::file::push("\tCommandID::ACCOUNT_CREATE\n");
    Account::ID new_account_id = context.account_manager.create_account();
    std::cout << "New Account ID: " << new_account_id << "\n";
    llog::file::push("\t\tAccount Created\n");
    llog::file::push("\t\tNew Account ID: " + std::to_string(new_account_id) + "\n");
    context.account_data = Account();
    context.account_data.set_account_id(new_account_id);
    context.account_data.set_username("user_" + std::to_string(new_account_id));
    context.account_data.set_logged_in(true);
}