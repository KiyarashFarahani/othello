#ifndef ADMIN_HPP
#define ADMIN_HPP

#include "User.hpp"

class Admin : public User {
public:
    Admin(int id, string username, string password);
    void deleteUser(); // Just an example placeholder
};

#endif
