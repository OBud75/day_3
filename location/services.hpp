#pragma once

#include "models.hpp"

#include <memory>


std::shared_ptr<World> make_world(int const size);
std::shared_ptr<World> get_world(
    DataMapper &data_mapper, int const id);
Tour make_best_tour(std::vector<Location> *locations);
