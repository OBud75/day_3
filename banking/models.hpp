#pragma once

#include <memory>
#include <vector>

class Bank;

class Card {
public:
    virtual int max_withdrawal() const = 0;
    virtual int max_credit() const = 0;
};

class GoldCard : public Card {
public:
    int max_withdrawal() const override { return 1500; }
    int max_credit() const override { return 5000; }
};

class PlatiniumCard : public Card {
public:
    int max_withdrawal() const override { return 2000; }
    int max_credit() const override { return 10000; }
};

class BlackCard : public Card {
public:
    int max_withdrawal() const override { return 3000; }
    int max_credit() const override { return 20000; }
};

class User {
public:
    explicit User(Bank* bank, std::string name);
    void set_card(std::unique_ptr<Card> card);
    std::unique_ptr<Card>& User::get_card() {
    return card;
}
    void deposit(int amount);
    bool withdraw(int amount);
    int get_balance() const;
    void add_to_bank(Bank* bank);
    void set_name(std::string name);
    std::string get_name() const;

private:
    Bank* bank;
    std::unique_ptr<Card> card;
    int balance;
    std::string name;
};

class Client {
public:
    Client(std::string name);
    void add_user(User* user);
    std::vector<User*> get_users() const;
    void add_to_bank(Bank* bank);
    std::string get_name() const;

private:
    std::vector<User*> users;
    std::string name;
};

class Bank {
public:
    Bank();
    void add_client(Client* client);
    std::vector<Client*> get_clients() const;
    void set_name(std::string name);
    std::string get_name() const;

private:
    std::vector<Client*> clients;
    std::string name;
};

class ATM {
public:
    bool verify_pin(std::string pin);
    void display_balance(int balance);
    void dispense_cash(int amount);
};
