#include "banking/services.hpp"
#include "banking/models.hpp"
#include "banking/withdrawal.hpp"

#include <iostream>
#include <memory>

int main() {
    // Création de la banque
    std::unique_ptr<Bank> bank = make_bank();
    bank->set_name("Ma Banque");

    // Création d'un client
    std::unique_ptr<Client> client = make_client("Client A");

    // Création d'un utilisateur
    std::unique_ptr<User> user = make_user(bank.get(), "Utilisateur 1");
    user->set_card(std::make_unique<PlatiniumCard>());

    // Attribution d'un client à la banque
    bank->add_client(client.get());

    // Ajout de l'utilisateur au client
    client->add_user(user.get());
    client->add_to_bank(bank.get());

    // Interaction avec l'ATM
    ATM atm;
    std::string pin;
    std::cout << "Entrez votre code PIN : ";
    std::cin >> pin;
    if (atm.verify_pin(pin)) {
        std::cout << "Code PIN correct." << std::endl;
        Withdrawal<PlatiniumCard> withdrawal(user->get_card(), 1000);
        withdrawal.process(atm);
    } else {
        std::cout << "Code PIN incorrect. Transaction annulée." << std::endl;
    }

    return 0;
}
