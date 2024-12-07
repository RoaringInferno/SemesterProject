#include "command_id.hpp"
#include "account.hpp"
#include "account_manager.hpp"
#include "commands.hpp"

#include "cli_parser"
#include "light-log"

#include <iostream>
#include <string>
#include <vector>
#include <filesystem>

const std::string DATA_DIR = "data/";
const std::string LOG_DIR = "logs/";

void args_raw_parse(std::vector<std::string> &args, const std::string &raw_args);
void get_command_id(CommandID& command);
void log_parsed_cli_args(largs::cli_parser& parsed_cli_args);

void login(Account &account_data, AccountManager &account_manager, const std::string &username, const std::string &password);

int main() {
    llog::file log_file;
    Context runtime_context;

    // Ensure data directory exists
    llog::file::push("Checkpoint: ## Directory Definitions ##\n");
    llog::file::push("\tData Directory: " + DATA_DIR + "\n");
    llog::file::push("\tLog Directory: " + LOG_DIR + "\n");
    std::filesystem::create_directory(DATA_DIR);

    size_t loop_count = 1;
    while (true)
    {
        llog::file::push("=============== Loop #"+std::to_string(loop_count)+" Start ===============\n");
        std::cout << runtime_context.account_data.get_username() << " > ";
        // ===== Command Parse =====
        llog::file::push("Checkpoint: ## Command Parse ##\n");
        CommandID command;
        get_command_id(command);
        if (command == CommandID::ERR) { continue; }
        if (command == CommandID::EXIT) {
            llog::file::push("Terminating program\n");
            break;
        }

        // ===== Argument Parse =====
        llog::file::push("Checkpoint: ## Argument Parse ##\n");
        std::string raw_args;
        std::getline(std::cin, raw_args);
        std::vector<std::string> args; // Needs to be owned outside of the cli_parser
        // Parse arguments into args vector
        llog::file::push("\tParsing Raw Arguments\n");
        args_raw_parse(args, raw_args);
        largs::cli_parser parsed_cli_args(args);
        llog::file::push("\tParsed Arguments:\n");
        log_parsed_cli_args(parsed_cli_args);

        // ===== Command Execution =====
        llog::file::push("Checkpoint: ## Command Execution ##\n");
        execute_command(runtime_context, command, parsed_cli_args);

        loop_count++;
    }
    std::cout << "===== Dumping Log Buffer: =====\n";
    llog::file::dump();
    return 0;
}

void args_raw_parse(std::vector<std::string> &args, const std::string &raw_args)
{
    std::string field;

    auto push_field = [&field, &args]() {
        if (!field.empty())
        {
            args.push_back(field);
            llog::file::push("\t\tPushing Field: \"" + field + "\"\n");
            field.clear();
        }
    };
    bool quoted = false;
    for (size_t i = 0; i < raw_args.size(); ++i)
    {
        if (raw_args[i] == '\\') // Escape character
        {
            if (i + 1 < raw_args.size()) // Not last character
            {
                i++; // Skip escaping backslash
                field.push_back(raw_args[i]);
                continue;
            } else // Last character
            {
                llog::file::push("\t\t[!] Ignoring unused escape backslash\n");
                push_field();
                break; // Exit loop
            }
        }
        if (raw_args[i] == ' ') // Space character
        {
            if (quoted) // Inside quotes
            {
                field.push_back(raw_args[i]);
            } else // Outside quotes
            {
                push_field();
            }
            continue;
        }
        if (raw_args[i] == '\"')
        {
            quoted = !quoted;
            continue;
        }
        field.push_back(raw_args[i]);
    }
    push_field();
}

void get_command_id(CommandID &command)
{
    std::string raw_command;
    std::cin >> raw_command;
    llog::file::push("\tRaw Command: \"" + raw_command + "\"\n");

    command = CommandID::GetId(raw_command);
    llog::file::push("\tEnum Value: \"" + std::to_string(command) + "\"\n");

    if (command == CommandID::ERR) {
        std::cout << "Unknown command: " << raw_command << std::endl;
        llog::file::push("\t[!] Ignoring unknown command\n");
        return;
    }
}

void log_parsed_cli_args(largs::cli_parser &parsed_cli_args)
{
    for (const auto& arg : parsed_cli_args.argument_list())
    {
        llog::file::push("\t\t\"" + std::string(arg.argument_value) + "\": ");
        switch (arg.argument_type)
        {
        case largs::cli_parser::argument_t::type::hard_argument:
            llog::file::push("Hard Argument\n");
            break;
        case largs::cli_parser::argument_t::type::soft_argument:
            llog::file::push("Soft Argument\n");
            break;
        case largs::cli_parser::argument_t::type::short_option_string:
            llog::file::push("Short Option String\n");
            break;
        case largs::cli_parser::argument_t::type::long_option:
            llog::file::push("Long Option\n");
            break;
        case largs::cli_parser::argument_t::type::passed_long_option_value:
            llog::file::push("Passed Long Option Value\n");
            break;
        default:
            llog::file::push("Error Type\n");
            break;
        }
    }
}