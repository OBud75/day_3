#pragma once

#include "models.hpp"

// Déclarez la classe template
template<typename Card>
class Withdrawal {
public:
    Withdrawal(Card* card, int amount);
    void process(ATM& atm);
private:
    Card* card;
    int amount;
};

// Implémentez le constructeur
template<typename Card>
Withdrawal<Card>::Withdrawal(Card* card, int amount) : card(card), amount(amount) {}

// Implémentez la méthode process
template<typename Card>
void Withdrawal<Card>::process(ATM& atm) {
    if (atm.verify_pin("1234")) { // Vérifiez le code PIN
        if (card->max_withdrawal() >= amount) {
            atm.dispense_cash(amount);
        } else {
            std::cout << "Montant de retrait non autorisé." << std::endl;
        }
    } else {
        std::cout << "Code PIN incorrect. Transaction annulée." << std::endl;
    }
}
