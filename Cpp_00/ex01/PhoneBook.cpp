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
    if (text.length() > kColumnWidth)
        return text.substr(0, kColumnWidth - 1) + ".";
    return text;
}

void PhoneBook::addContact(const Contact &contact)
{
    _contacts[_nextIndex] = contact;
    _nextIndex = (_nextIndex + 1) % kMaxContacts;
    if (_count < kMaxContacts)
        ++_count;
}

void PhoneBook::displayList(void) const
{
    std::cout << std::setw(kColumnWidth) << "index" << "|"
              << std::setw(kColumnWidth) << "first name" << "|"
              << std::setw(kColumnWidth) << "last name" << "|"
              << std::setw(kColumnWidth) << "nickname" << "|" << std::endl;

    for (int i = 0; i < _count; ++i)
    {
        const Contact &contact = _contacts[i];

        std::cout << std::setw(kColumnWidth) << i << "|"
                  << std::setw(kColumnWidth) << formatColumn(contact.getFirstName()) << "|"
                  << std::setw(kColumnWidth) << formatColumn(contact.getLastName()) << "|"
                  << std::setw(kColumnWidth) << formatColumn(contact.getNickname()) << "|" << std::endl;
    }
}

bool PhoneBook::isValidIndex(int index) const
{
    return index >= 0 && index < _count;
}

void PhoneBook::displayContact(int index) const
{
    if (!isValidIndex(index))
    {
        std::cerr << "Invalid contact index." << std::endl;
        return;
    }

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
