#include "commands.hpp"

void run_LOGOUT(Context &context, largs::cli_parser &parsed_cli_args)
{
    llog::file::push("\tCommandID::LOGOUT\n");
    if (!require_logged_in(context)) return;
    context.account_manager.logout(context.account_data);
    std::cout << "Logout Successful\n";
    llog::file::push("\t\tLogout Successful\n");
}