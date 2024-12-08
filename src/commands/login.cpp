#include "commands.hpp"

void run_LOGIN(Context &context, largs::cli_parser &parsed_cli_args)
{
    llog::file::push("\tCommandID::LOGIN\n");
    if (parsed_cli_args.argument_list().size() != 2) {
        std::cout << "Usage: login <username> <password>\n";
        llog::file::push("\t\t[!] Invalid number of arguments\n");
        return;
    }
    const std::string &username = parsed_cli_args.argument_list()[0].argument_value.data();
    const std::string &password = parsed_cli_args.argument_list()[1].argument_value.data();

    llog::file::push("\t\tUsername: " + username +"\n");
    llog::file::push("\t\tPassword: " + password +"\n");
    Account::ID accnt_id = context.account_manager.get_account_id(username);
    if (accnt_id == 0) {
        std::cout << "Account not found (Invalid Username)\n";
        llog::file::push("\t\t[!] Account not found (Invalid Username)\n");
        return;
    }
    bool login_success = context.account_manager.login(accnt_id, password, context.account_data);
    if (login_success) {
        llog::file::push("\t\tLogin Successful\n");
    } else {
        std::cout << "Login Failed (Invalid Password)\n";
        llog::file::push("\t\t[!] Login Failed (Invalid Password)\n");
    }
}