#pragma once

#include "light-csv"

#include <string>

class Account
{
public:
    typedef unsigned int ID; // ID values are greater than 0

    /*
    For closed set of strings:
    - ADMIN
    - INSTRUCTOR
    - STUDENT

    Hash Tables:
    Fastest: [0] with opcount 0 and tightness 18 has hash table: 65 73 83
    Tightest: ([4] | 24) with opcount 1 and tightness 4 has hash table: 94 90 93
    */
    enum ACCOUNT_TYPE : unsigned char
    {
        ADMIN,
        INSTRUCTOR,
        STUDENT
    };

    static ACCOUNT_TYPE decode_type(const std::string &type);
    static std::string encode_type(const ACCOUNT_TYPE &type);
private:
    /// @brief The account ID. Cannot be 0.
    ID account_id{0};
    std::string username{"%"};
    std::string password{"*"};
    std::string personal_email{"john_doe@gmail.com"};
    std::string school_email{"john_doe@auburn.edu"};
    std::string phone{"(123) 456-7890"};
    std::string first_name{"John"};
    std::string last_name{"Doe"};
    ACCOUNT_TYPE type{STUDENT};
    bool logged_in{false};
public: // Getters
    ID get_account_id() const { return this->account_id; };
    std::string get_username() const { return this->username; };
    std::string get_password() const { return this->password; };
    std::string get_personal_email() const { return this->personal_email; };
    std::string get_school_email() const { return this->school_email; };
    std::string get_phone() const { return this->phone; };
    std::string get_first_name() const { return this->first_name; };
    std::string get_last_name() const { return this->last_name; };
    ACCOUNT_TYPE get_type() const { return this->type; };
    bool get_logged_in() const { return this->logged_in; };
public: // Setters
    void set_account_id(const ID new_value) { this->account_id = new_value; };
    void set_username(const std::string &new_value) { this->username = new_value; };
    void set_password(const std::string &new_value) { this->password = new_value; };
    void set_personal_email(const std::string &new_value) { this->personal_email = new_value; };
    void set_school_email(const std::string &new_value) { this->school_email = new_value; };
    void set_phone(const std::string &new_value) { this->phone = new_value; };
    void set_first_name(const std::string &new_value) { this->first_name = new_value; };
    void set_last_name(const std::string &new_value) { this->last_name = new_value; };
    void set_type(const ACCOUNT_TYPE &new_value) { this->type = new_value; };
    void set_logged_in(const bool &new_value) { this->logged_in = new_value; };
public:
    Account();
    ~Account();
};

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