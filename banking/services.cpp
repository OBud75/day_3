#include "services.hpp"

using namespace std;

std::unique_ptr<Bank> make_bank() {
    return std::make_unique<Bank>();
}