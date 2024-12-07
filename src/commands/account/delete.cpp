#include "commands.hpp"

void run_ACCOUNT_DELETE(Context &context, largs::cli_parser &parsed_cli_args)
{
    llog::file::push("\tCommandID::ACCOUNT_DELETE\n");
    if (!require_logged_in(context)) return;
    context.account_manager.delete_account(context.account_data.get_account_id());
    context.account_data = Account();
    std::cout << "Account Deleted\n";
    llog::file::push("\t\tAccount Deleted\n");
}