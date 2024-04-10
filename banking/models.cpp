#include "models.hpp"
#include <iostream>
#include <memory>
User::User(Bank* bank, std::string name) : bank(bank), balance(0), name(name) {}

void User::set_card(std::unique_ptr<Card> card) {
    this->card = std::move(card);
}

std::unique_ptr<Card>& User::get_card() {
    return card;
}

void User::deposit(int amount) {
    balance += amount;
}

bool User::withdraw(int amount) {
    if (amount <= balance && amount <= card->max_withdrawal()) {
        balance -= amount;
        return true;
    }
    return false;
}

int User::get_balance() const {
    return balance;
}

void User::add_to_bank(Bank* bank) {
    this->bank = bank;
}

void User::set_name(std::string name) {
    this->name = name;
}

std::string User::get_name() const {
    return name;
}

Client::Client(std::string name) : name(name) {}

void Client::add_user(User* user) {
    users.push_back(user);
}

std::vector<User*> Client::get_users() const {
    return users;
}

void Client::add_to_bank(Bank* bank) {
    for (auto user : users) {
        user->add_to_bank(bank);
    }
}

std::string Client::get_name() const {
    return name;
}

Bank::Bank() {}

void Bank::add_client(Client* client) {
    clients.push_back(client);
}

std::vector<Client*> Bank::get_clients() const {
    return clients;
}

void Bank::set_name(std::string name) {
    this->name = name;
}

std::string Bank::get_name() const {
    return name;
}

bool ATM::verify_pin(std::string pin) {
    // Implémentation de la vérification du code PIN
    // Par exemple, vérifiez si le code PIN correspond à celui de la carte
    // Pour l'exemple, supposons que le code PIN est correct si "1234" est saisi
    return pin == "1234";
    // C'est une bonne idée de future implémentation, on peut facilement immagine
    // une propriété Card::pinCode
}

void ATM::display_balance(int balance) {
    std::cout << "Solde : " << balance << std::endl;
}

void ATM::dispense_cash(int amount) {
    std::cout << "Retrait de " << amount << " effectué." << std::endl;
}
