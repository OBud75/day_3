#include "services.hpp"

#include <iostream>
#include <algorithm>
#include <limits>
#include <memory>

using namespace std;


shared_ptr<World> make_world(int const size) {
    auto world = make_shared<World>(size);
    World::objects.insert(world);
    return world;
}

shared_ptr<World> get_world(DataMapper &data_mapper, int const id) {
    return World::get(data_mapper, id);
}

Tour make_best_tour(vector<Location> *locations) {
    sort(locations->begin(), locations->end());
    Tour best_tour(locations);
    double min_dist = numeric_limits<double>::max();
    auto p(0);
    do {
        p++;
        Tour current_tour(locations);
        if (current_tour.distance() < min_dist) {
            min_dist = current_tour.distance();
            best_tour = current_tour;
        }
    } while (next_permutation(locations->begin(),
                              locations->end()));
    cout << "Nombre de permutations: " << p << endl;
    return best_tour;
}
