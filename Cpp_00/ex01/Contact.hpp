#ifndef CONTACT_HPP
#define CONTACT_HPP

#include <string>

class Contact
{
private:
    std::string _firstName;
    std::string _lastName;
    std::string _nickname;
    std::string _phoneNumber;
    std::string _darkestSecret;
    bool        _isSet;

public:
    Contact(void);
    ~Contact(void);

    void setContact(const std::string &firstName,
                    const std::string &lastName,
                    const std::string &nickname,
                    const std::string &phoneNumber,
                    const std::string &darkestSecret);

    bool isSet(void) const;
    const std::string &getFirstName(void) const;
    const std::string &getLastName(void) const;
    const std::string &getNickname(void) const;
    const std::string &getPhoneNumber(void) const;
    const std::string &getDarkestSecret(void) const;
};

#endif
