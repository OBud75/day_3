#pragma once

#include "models.hpp"
#include <iostream>
#include <memory>


std::unique_ptr<User> make_user(Bank* bank, std::string name);
std::unique_ptr<Client> make_client(std::string name);
std::unique_ptr<Bank> make_bank();
