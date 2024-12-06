#include "account_manager.hpp"

#include "filesystem.hpp"

#include <iostream>
#include <algorithm>

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

const std::string ACCOUNT_CSV_FILE_HEADER = "account_id,username,password,personal_email,school_email,phone,first_name,last_name,type";

void AccountManager::populate(const size_t index, Account &account) const
{
    account.set_account_id(std::stoi(account_data[index][ACCOUNT_ID]));
    account.set_username(account_data[index][USERNAME]);
    account.set_password(account_data[index][PASSWORD]);
    account.set_personal_email(account_data[index][PERSONAL_EMAIL]);
    account.set_school_email(account_data[index][SCHOOL_EMAIL]);
    account.set_phone(account_data[index][PHONE]);
    account.set_first_name(account_data[index][FIRST_NAME]);
    account.set_last_name(account_data[index][LAST_NAME]);
    account.set_type(Account::decode_type(account_data[index][TYPE]));
}

bool AccountManager::get_account_index(const Account::ID account_id, size_t &index) const
{
    auto get_id = [&](const size_t row_index) -> Account::ID { return std::stoi(account_data[row_index][ACCOUNT_ID]); };
    // Linear Search Algorithm:
    for (size_t i = 0; i < account_data.size(); i++)
    {
        if (get_id(i) == account_id)
        {
            index = i;
            return true;
        }
    }
    return false;

    /*
    Complex Search Algorithm:
        Start from the index that corresponds to the account_id
        The left side is expected to be dense
        The right side is expected to be sparse
        So we can use a binary search algorithm to find the account_id on the right side
        And then linear search the left side
     */
    return false;
}

void AccountManager::sort()
{
    std::sort(account_data.begin(), account_data.end(), [](const lcsv::csv_row &a, const lcsv::csv_row &b) {
        return std::stoi(a[ACCOUNT_ID]) < std::stoi(b[ACCOUNT_ID]);
    });
}

bool AccountManager::get_account(const Account::ID account_id, Account &account) const
{
    size_t index;
    if (get_account_index(account_id, index))
    {
        populate(index, account);
        return true;
    }
    return false;
}

Account::ID AccountManager::get_account_id(const std::string &username) const
{
    std::cout << "Entered AccountManager::get_account_id()\n"; // Debugging
    for (const auto &row : account_data)
    {
        if (row[USERNAME] == username)
        {
            return std::stoi(row[ACCOUNT_ID]);
        }
    }
    return 0;
}

bool AccountManager::login(const Account::ID account_id, const std::string &password, Account &account) const
{
    std::cout << "Entered AccountManager::login()\n"; // Debugging
    size_t index;
    get_account_index(account_id, index);
    std::cout << "\tFound account index: " << index << "\n"; // Debugging
    const lcsv::csv_row &row = account_data[index];
    if (row[PASSWORD] == password)
    {
        populate(account_id, account);
        account.set_logged_in(true);
        return true;
    }
    return false;
}

void AccountManager::logout(Account &account)
{
    if (!account.get_logged_in()) return; // Already logged out
    lcsv::csv_row &row = account_data[account.get_account_id()];
    row.set(ACCOUNT_ID, std::to_string(account.get_account_id()));
    row.set(USERNAME, account.get_username());
    row.set(PASSWORD, account.get_password());
    row.set(PERSONAL_EMAIL, account.get_personal_email());
    row.set(SCHOOL_EMAIL, account.get_school_email());
    row.set(PHONE, account.get_phone());
    row.set(FIRST_NAME, account.get_first_name());
    row.set(LAST_NAME, account.get_last_name());
    row.set(TYPE, Account::encode_type(account.get_type()));
    account.set_logged_in(false);
}

Account::ID AccountManager::create_account()
{
    Account::ID new_id = 1;
    // Find the first unused account_id
    for (auto it = account_data.begin(); it != account_data.end(); it++)
    {
        if (std::stoi((*it)[ACCOUNT_ID]) != new_id)
        {
            break;
        }
        else
        {
            new_id++;
        }
    }
    // Add the row
    lcsv::csv_row new_row(ACCOUNT_CSV_ROW_FIELD_COUNT);
    new_row.set(ACCOUNT_ID, std::to_string(new_id));
    account_data.push_back(new_row);
    // Sort it into place
    sort();
    return new_id;
}

bool AccountManager::delete_account(const Account::ID account_id)
{
    size_t index;
    if (get_account_index(account_id, index))
    {
        account_data.erase(account_data.begin() + index);
        return true;
    }
    return false;
}

AccountManager::AccountManager() :
    account_data(ACCOUNT_CSV_FILE_PATH)
{
    account_data.header() = ACCOUNT_CSV_FILE_HEADER;

    // Sort the file by account_id
    sort();
}

AccountManager::~AccountManager()
{
    account_data.write();
}
