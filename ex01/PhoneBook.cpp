#include "PhoneBook.hpp"

#include <iomanip>
#include <iostream>

PhoneBook::PhoneBook(void) : _count(0), _nextIndex(0)
{
}

PhoneBook::~PhoneBook(void)
{
}

std::string PhoneBook::formatColumn(const std::string &text)
{
    if (text.length() > 10)
        return text.substr(0, 9) + ".";
    return text;
}

void PhoneBook::addContact(const Contact &contact)
{
    _contacts[_nextIndex] = contact;
    _nextIndex = (_nextIndex + 1) % 8;
    if (_count < 8)
        ++_count;
}

void PhoneBook::displayList(void) const
{
    std::cout << std::setw(10) << "index" << "|"
              << std::setw(10) << "first name" << "|"
              << std::setw(10) << "last name" << "|"
              << std::setw(10) << "nickname" << std::endl;

    for (int i = 0; i < _count; ++i)
    {
        std::cout << std::setw(10) << i << "|"
                  << std::setw(10) << formatColumn(_contacts[i].getFirstName()) << "|"
                  << std::setw(10) << formatColumn(_contacts[i].getLastName()) << "|"
                  << std::setw(10) << formatColumn(_contacts[i].getNickname()) << std::endl;
    }
}

bool PhoneBook::isValidIndex(int index) const
{
    return index >= 0 && index < _count;
}

void PhoneBook::displayContact(int index) const
{
    std::cout << "First name: " << _contacts[index].getFirstName() << std::endl;
    std::cout << "Last name: " << _contacts[index].getLastName() << std::endl;
    std::cout << "Nickname: " << _contacts[index].getNickname() << std::endl;
    std::cout << "Phone number: " << _contacts[index].getPhoneNumber() << std::endl;
    std::cout << "Darkest secret: " << _contacts[index].getDarkestSecret() << std::endl;
}

int PhoneBook::getCount(void) const
{
    return _count;
}
