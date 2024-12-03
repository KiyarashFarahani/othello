#ifndef ADMIN_HPP
#define ADMIN_HPP
#include "User.hpp"

class Admin : public User {
    public:
        Admin();
        Admin(int id, string username, string password);
        Admin* login(const string& username, const string& password) override;
        bool deleteUser(const string& username);
};

#endif