#include "account.hpp"

#include "filesystem.hpp"

#include "light-log"
#include "light-csv"

/*
File Structure:
- account_id
- username
- password
- personal_email
- school_email
- phone
- first_name
- last_name
- type (ADMIN, INSTRUCTOR, STUDENT)
*/

enum COLUMN_INDEX
{
    ACCOUNT_ID = 0,
    USERNAME,
    PASSWORD,
    PERSONAL_EMAIL,
    SCHOOL_EMAIL,
    PHONE,
    FIRST_NAME,
    LAST_NAME,
    TYPE
};

size_t ACCOUNT_CSV_ROW_FIELD_COUNT = 9;

const std::string ACCOUNT_CSV_FILE_PATH = DATA_DIR + "accounts.csv";

Account::ACCOUNT_TYPE Account::decode_type(const std::string &type)
{
    switch (type[0])
    {
    case 'A':
        return ADMIN;
    case 'I':
        return INSTRUCTOR;
    case 'S':
        return STUDENT;
    default:
        return STUDENT;
    }
}

std::string Account::encode_type(const ACCOUNT_TYPE &type)
{
    switch (type)
    {
    case ADMIN:
        return "ADMIN";
    case INSTRUCTOR:
        return "INSTRUCTOR";
    case STUDENT:
        return "STUDENT";
    default:
        return "STUDENT";
    }
}

size_t find_account_row_num(const std::string& value, size_t column)
{
    lcsv::csv_file account_file(ACCOUNT_CSV_FILE_PATH);

    for (size_t i = 0; i < account_file.size(); i++)
    {
        if (account_file[i][column] == value)
        {
            return i;
        }
    }

    return -1;
}

bool Account::validate(std::string_view username, std::string_view password)
{
    lcsv::csv_file account_file(ACCOUNT_CSV_FILE_PATH);
    if (account_file.empty())
    {
        llog::file::push("\t\t[!] No Account Data\n");
        this->is_valid = false;
        return false;
    }

    for (const auto& row : account_file)
    {
        if (row[USERNAME].get_value() == username)
        {
            if (row[PASSWORD].get_value() == password)
            {
                this->account_id = std::stoi(row[ACCOUNT_ID].get_value());
                this->username = row[USERNAME].get_value();
                this->password = row[PASSWORD].get_value();
                this->personal_email = row[PERSONAL_EMAIL].get_value();
                this->school_email = row[SCHOOL_EMAIL].get_value();
                this->phone = row[PHONE].get_value();
                this->first_name = row[FIRST_NAME].get_value();
                this->last_name = row[LAST_NAME].get_value();
                this->type = this->decode_type(row[TYPE].get_value());
                llog::file::push("\t\tValid Login to Account ID "+row[ACCOUNT_ID].get_value()+"\n");
                this->is_valid = true;
                return true;
            }
            llog::file::push("\t\tInvalid Password for Account ID "+row[ACCOUNT_ID].get_value()+"\n");
            this->is_valid = false;
            return false;
        }
    }
    llog::file::push("\t\tInvalid Username (Not Found): \""+std::string(username)+"\"\n");
    this->is_valid = false;
    return false;
}

bool Account::write()
{
    bool retval = true;
    this->is_valid = true; // Set the account as valid because it is being written to the database
    // Populate the write_row with the account data
    std::vector<std::string> write_row = 
    {
        std::to_string(this->account_id), // ACCOUNT_ID
        this->username, // USERNAME
        this->password, // PASSWORD
        this->personal_email, // PERSONAL_EMAIL
        this->school_email, // SCHOOL_EMAIL
        this->phone, // PHONE
        this->first_name, // FIRST_NAME
        this->last_name, // LAST_NAME
        this->encode_type(this->type) // TYPE
    };

    llog::file::push("\t\tWriting Account ID " + write_row[ACCOUNT_ID] + "\n");

    size_t row_num = find_account_row_num(write_row[ACCOUNT_ID], ACCOUNT_ID); // Find the row number of the account

    lcsv::csv_file account_file(ACCOUNT_CSV_FILE_PATH); // Open the account file
    if (row_num == -1)
    {
        account_file.emplace_back(write_row); // If the account was not found, create a new account entry
        retval = false;
    }
    else
    {
        account_file[row_num] = write_row; // If the account was found, update the account entry
    }
    account_file.write(); // Write the data to the file

    return retval;
}

void Account::delete_account()
{
    llog::file::push("\t\tDeleting Account ID " + std::to_string(this->account_id) + "\n");
    size_t row_num = find_account_row_num(std::to_string(this->account_id), ACCOUNT_ID); // Find the row number of the account

    lcsv::csv_file account_file(ACCOUNT_CSV_FILE_PATH); // Open the account file
    if (row_num != -1)
    {
        account_file.erase(account_file.begin() + row_num); // If the account was found, delete the account entry
    }
    account_file.write(); // Write the data to the file

    this->wipe_cache(); // Wipe the account data
}

void Account::wipe_cache()
{
    *this = Account(); // Wipe the account data
}

void Account::create_account()
{
    this->wipe_cache(); // Wipe the account data

    lcsv::csv_file account_file(ACCOUNT_CSV_FILE_PATH); // Open the account file

    std::vector<ID> account_ids(account_file.size()); // Create a vector to store all account IDs
    for (size_t i = 0; i < account_file.size(); i++)
    {
        account_ids[i] = std::stoi(account_file[i][ACCOUNT_ID].get_value());
    }

    /*
    if the accounts are sorted in ascending order, the first account ID to not be 1 greater than the previous account ID is the new account ID
    */
    //this->account_id = 0; // The account ID is 0 by default
    std::sort(account_ids.begin(), account_ids.end()); // Sort the account IDs in ascending order
    for (
        size_t i = 0;
        ;
        i++
    )
    {
        this->account_id++;
        if (i == account_ids.size() || this->account_id != account_ids[i])
        {
            break;
        }
    }

    this->is_valid = true; // Set the account as valid because it is being created
    this->write(); // Write the account data to the database

    llog::file::push("\t\tCreated Account with ID " + std::to_string(this->account_id) + "\n");
}

Account::Account()
{
}

Account::~Account()
{
    if (this->is_valid) { this->write(); }
}
