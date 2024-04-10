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
    // Vous vérifiez le code pin ici puis de nouveau dans la fonction process

    return 0;
}

// Les fichiers headers servent normalement uniquement aux déclarations
// Puis les implémentations dans les fichiers source (.cpp)

// Les noms sont bien choisis et vous implémentez votre logique, ce qui est apprécié.
// Attention vous vérifiez le code pin 2 fois (la seconde fois sera forcément validée puisqu'on est déjà dans le if (atm.verify()))
// Prennez le temps d'aller jusqu'au bout de vos idées puis amusez vous en faisant évoluer votre système en ajoutant ce que vous souahitez!

// 13/20
