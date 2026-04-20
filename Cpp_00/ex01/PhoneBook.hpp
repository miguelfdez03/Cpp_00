#ifndef PHONEBOOK_HPP
#define PHONEBOOK_HPP

#include "Contact.hpp"

class PhoneBook
{
private:
    enum
    {
        kMaxContacts = 8,
        kColumnWidth = 10
    };

    Contact _contacts[kMaxContacts];
    int     _count;
    int     _nextIndex;

    static std::string formatColumn(const std::string &text);

public:
    PhoneBook(void);
    ~PhoneBook(void);

    void addContact(const Contact &contact);
    void displayList(void) const;
    bool isValidIndex(int index) const;
    void displayContact(int index) const;
    int  getCount(void) const;
};

#endif
