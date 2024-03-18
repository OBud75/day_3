#include "models.hpp"
#include "../database/data_mappers.hpp"

#include <cmath>
#include <iostream>

using namespace std;


World::World(int const size): _height(size), _width(size) {
    _id = 0;
    _locations.resize(size);
    for(auto i(0); i < size; ++i) {
        _locations[i].resize(size);
        for(auto j(0); j < size; ++j) {
            _locations.at(i).at(j) = make_unique<Location>(this, j, i);
        }
    }
}

World::World(int const id, int const size): World(size) {
    _id = id;
}

set<shared_ptr<World>> World::objects;

int World::id() {return _id;}
void World::set_id(int const id) {_id = id;}

int World::height() {return _height;}
int World::width() {return _width;}

vector<vector<unique_ptr<Location>>> &World::locations() {
    return _locations;
}

void World::bind_locations() {
    for (auto i(0); i < _height; ++i) {
        for (auto j(0); j < _width; ++j) {
            auto location = _locations.at(j).at(i).get();
            if (i) {
                location->set_left(_locations.at(i-1).at(j).get());
                location->left()->set_right(location);
            }
            if (j) {
                location->set_up(_locations.at(i).at(j-1).get());
                location->up()->set_down(location);
            }
        }
    }
}

shared_ptr<World> World::get(DataMapper &data_mapper, int const id) {
    for (auto &world: World::objects) {
        if (world->id() == id) {
            return world;
        }
    }
    return data_mapper.make_world(id);
}

void World::save(DataMapper &data_mapper) {
    data_mapper.save_world(*this);
}

Location::Location() {}

Location::Location(World *const world, int const x, int const y):
    _world(world), _latitude(x), _longitude(y) {}

Location::Location(int const x, int const y):
    _latitude(x), _longitude(y) {}

Location::Location(int id, int x, int y):
    id(id), _longitude(x), _latitude(y) {}

bool Location::operator<(const Location &other) const {
    if (_latitude != other._latitude) {
        return _latitude < other._latitude;
    }
    return _longitude < other._longitude;
}

bool Location::operator==(const Location &other) const {
    return (
        (_latitude == other._latitude)
        and (_longitude == other._longitude)
    );
}

int Location::latitude() {return _latitude;}
int Location::longitude() {return _longitude;}
World &Location::world() {return *_world;}

array<Location*, 4> Location::neighbours() {
    return {_up, _right, _down, _left};
}

void Location::set_up(Location *up) {_up = up;};
void Location::set_right(Location *right) {_right = right;};
void Location::set_down(Location *down) {_down = down;};
void Location::set_left(Location *left) {_left = left;};

Location *Location::up() {
    return _world->locations().at(_longitude - 1).at(_latitude).get();
}
Location *Location::right() {
    return _world->locations().at(_longitude).at(_latitude + 1).get();
}
Location *Location::down() {
    return _world->locations().at(_longitude + 1).at(_latitude).get();
}
Location *Location::left() {
    return _world->locations().at(_longitude).at(_latitude - 1).get();
}

double Location::get_dist(Location *const other) {
    int diff_lat = abs(latitude() - other->latitude());
    int diff_long = abs(longitude() - other->longitude());
    auto dist = hypot(diff_lat, diff_long);
    cout << "La distance est de : " << dist <<endl;
    return dist;
}


Labyrinth::Labyrinth(LabyrinthBlockMapper mapper) {
    mapper.set_blocks(*this);
}

void Labyrinth::set_locations(vector<vector<unique_ptr<Location>>> &&locations) {
    _locations = move(locations);
}


Tour::Tour(vector<Location> *locations):
    _locations(locations) {update_distance();}

void Tour::update_distance() {
    double distance = 0;
    cout << "\nDistance entre chaque ville : " << "\n";
    for (size_t i(0); i < _locations->size() - 1; ++i) {
        distance += _locations->at(i).get_dist(&_locations->at(i+1));
    }
    if (not _locations->empty()) {
        distance += _locations->back().get_dist(&_locations->front());
    }
    _distance = distance;
    cout << "Distance du tour : " << _distance << "\n";
}

double Tour::distance() {return _distance;}

vector<Location> &Tour::locations() {
    return *_locations;
}
