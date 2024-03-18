#include "services.hpp"

std::unique_ptr<User> make_user(Bank* bank, std::string name) {
    return std::make_unique<User>(bank, name);
}

std::unique_ptr<Client> make_client(std::string name) {
    return std::make_unique<Client>(name);
}
