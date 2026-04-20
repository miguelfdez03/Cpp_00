#include "PhoneBook.hpp"

#include <cctype>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>

namespace
{
const std::size_t kPhoneDigits = 9;
const int         kPhoneBookCapacity = 8;
}

static bool isAsciiAlnum(const std::string &value)
{
    for (std::string::size_type i = 0; i < value.length(); ++i)
    {
        unsigned char c = static_cast<unsigned char>(value[i]);

        if (c > 127 || !(std::isalnum(c) || c == ' '))
            return false;
    }
    return true;
}

static bool isNineDigits(const std::string &value)
{
    if (value.length() != kPhoneDigits)
        return false;
    for (std::string::size_type i = 0; i < value.length(); ++i)
    {
        if (!std::isdigit(static_cast<unsigned char>(value[i])))
            return false;
    }
    return true;
}

static bool promptAsciiAlnumField(const std::string &label, std::string &value)
{
    while (true)
    {
        std::cout << label;
        if (!std::getline(std::cin, value))
            return false;
        if (value.empty())
        {
            std::cout << "Field cannot be empty. Please try again." << std::endl;
            continue;
        }
        if (!isAsciiAlnum(value))
        {
            std::cout << "Only ASCII letters, digits, spaces are allowed." << std::endl;
            continue;
        }
        return true;
    }
}

static bool promptPhoneField(std::string &value)
{
    while (true)
    {
        std::cout << "Phone number (9 digits): ";
        if (!std::getline(std::cin, value))
            return false;
        if (!isNineDigits(value))
        {
            std::cout << "Phone number must contain exactly 9 numeric digits." << std::endl;
            continue;
        }
        return true;
    }
}

static bool getIndexFromInput(const std::string &input, int &index)
{
    std::istringstream iss(input);
    char               extra;

    if (!(iss >> index))
        return false;
    if (iss >> extra)
        return false;
    return true;
}

static void toUpperAsciiInPlace(std::string &text)
{
    for (std::string::size_type i = 0; i < text.length(); ++i)
        text[i] = static_cast<char>(std::toupper(static_cast<unsigned char>(text[i])));
}

static void handleAdd(PhoneBook &phoneBook)
{
    std::string firstName;
    std::string lastName;
    std::string nickname;
    std::string phoneNumber;
    std::string darkestSecret;
    std::string confirmation;

    if (phoneBook.getCount() >= kPhoneBookCapacity)
    {
        std::cout << "The phonebook is full. If you create a new contact, the oldest one will be deleted. Continue? (y/n): ";
        if (!std::getline(std::cin, confirmation))
            return;
        toUpperAsciiInPlace(confirmation);
        if (!(confirmation == "Y" || confirmation == "YES"))
        {
            std::cout << "Add cancelled." << std::endl;
            return;
        }
    }

    if (!promptAsciiAlnumField("First name: ", firstName)
        || !promptAsciiAlnumField("Last name: ", lastName)
        || !promptAsciiAlnumField("Nickname: ", nickname)
        || !promptPhoneField(phoneNumber)
        || !promptAsciiAlnumField("Darkest secret: ", darkestSecret))
        return;

    Contact contact;
    contact.setContact(firstName, lastName, nickname, phoneNumber, darkestSecret);
    phoneBook.addContact(contact);
    std::cout << "Contact saved." << std::endl;
}

static void handleSearch(const PhoneBook &phoneBook)
{
    std::string input;
    int         index;

    if (phoneBook.getCount() == 0)
    {
        std::cout << "PhoneBook is empty." << std::endl;
        return;
    }

    phoneBook.displayList();
    std::cout << "Enter index: ";
    if (!std::getline(std::cin, input))
        return;
    if (!getIndexFromInput(input, index) || !phoneBook.isValidIndex(index))
    {
        std::cout << "Invalid index." << std::endl;
        return;
    }
    phoneBook.displayContact(index);
}

int main(void)
{
    PhoneBook    phoneBook;
    std::string  command;
    std::string  normalizedCommand;

    while (true)
    {
        std::cout << "Enter command (ADD, SEARCH, EXIT): ";
        if (!std::getline(std::cin, command))
            break;
        normalizedCommand = command;
        toUpperAsciiInPlace(normalizedCommand);

        if (normalizedCommand == "ADD")
            handleAdd(phoneBook);
        else if (normalizedCommand == "SEARCH")
            handleSearch(phoneBook);
        else if (normalizedCommand == "EXIT")
            break;
    }

    return EXIT_SUCCESS;
}
