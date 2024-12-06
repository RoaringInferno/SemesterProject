#pragma once

#include "account.hpp"

#include "light-csv"

class AccountManager
{
private:
    lcsv::csv_file account_data;
private:
    void populate(const size_t index, Account &account) const;
    bool get_account_index(const Account::ID account_id, size_t &index) const;
    void sort();
public: // Helpers
    /// @brief Gets the account data from the account ID
    /// @param account_id The account ID to get
    /// @param account The account to populate
    /// @return True if the account was found, false otherwise
    bool get_account(const Account::ID account_id, Account &account) const;
public:
    /// @brief Gets the account data from the account ID
    /// @param username The username to get the account data from
    /// @return The account ID. 0 if the account was not found.
    Account::ID get_account_id(const std::string &username) const;

    /// @brief Checks if the username and password are valid. If so, the account is populated. Otherwise, the account is unchanged.
    /// @param account_id The account ID to check. This function assumes that this is valid.
    /// @param password The password to check
    /// @param account The account to populate if the username and password are valid
    /// @return True if the username and password are valid, false otherwise
    bool login(const Account::ID account_id, const std::string &password, Account &account) const;

    /// @brief Saves the account data. Then resets the account to a default state.
    /// @param account The account to logout
    void logout(Account &account);

    /// @brief Returns an unused account ID
    /// @return The new account ID
    Account::ID create_account();

    /// @brief Deletes the account with the given ID
    /// @param account_id The account ID to delete
    /// @return True if the account was deleted, false if the account was not found
    bool delete_account(const Account::ID account_id);
public:
    /// @brief Initializes the account data file
    AccountManager();
    /// @brief Saves the account data file
    ~AccountManager();
};