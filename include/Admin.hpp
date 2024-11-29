#ifndef ADMIN_HPP
#define ADMIN_HPP

#include "user.hpp"

class admin : public user {
public:
    admin(int id, string username, string password);
    void deleteUser(); // Just an example placeholder
};

#endif
