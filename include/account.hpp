#pragma once

#include <string>

class Account
{
public:
    typedef unsigned int ID;

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
    bool is_valid{false};
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
    bool get_is_valid() const { return this->is_valid; };
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
    void set_is_valid(const bool &new_value) { this->is_valid = new_value; };
public:
    /// @brief Validates a username and password. If the username and password are valid, return true and populate the Account object with the user's data. Otherwise, return false.
    /// @param username The username to validate.
    /// @param password The password to validate.
    /// @return True if the username and password are valid, false otherwise.
    bool validate(std::string_view username, std::string_view password);

    /// @brief Updates the account data in the database.
    /// @return True if the account was successfully updated, false if a new account entry was created.
    bool write();

    /// @brief Deletes the account from the database.
    void delete_account();
    void wipe_cache();

    /// @brief Wipes the account data and gives it a new account ID that is not present in the datbase.
    void create_account();
public:
    Account();
    ~Account();
};