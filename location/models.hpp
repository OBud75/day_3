#pragma once

#include <vector>
#include <set>

#include "../database/data_mappers.hpp"

class LabyrinthBlockMapper;
class DataMapper;
class Location;


class World {
    private:
        int _id;
        int const _height, _width;
        std::vector<std::vector<std::unique_ptr<Location>>> _locations;

    public:
        explicit World(int const size);
        explicit World(int const id, int const size);

        int id();
        void set_id(int const id);
        int height(), width();

        static std::set<std::shared_ptr<World>> objects;
        std::vector<std::vector<std::unique_ptr<Location>>> &locations();
        void bind_locations();

        void save(DataMapper &data_mapper);
        static std::shared_ptr<World> get(DataMapper &data_mapper, int const id);
};


class Location {
    private:
        int _latitude, _longitude;
        World *_world;
        Location *_up, *_right, *_down, *_left;

    public:
        explicit Location();
        explicit Location(
            World *const world, int const x, int const y);
        explicit Location(int const x, int const y);
        explicit Location(int id, int x, int y);
        bool operator<(const Location& other) const;
        bool operator==(const Location &other) const;

        int id;
        World &world();
        int latitude();
        int longitude();
        double get_dist(Location *const other);

        void set_up(Location *up);
        void set_right(Location *up);
        void set_down(Location *up);
        void set_left(Location *left);
        Location *up(), *right(), *down(), *left();
        std::array<Location*, 4> neighbours();
};


struct Labyrinth {
    explicit Labyrinth(LabyrinthBlockMapper mapper);
    void set_locations(
        std::vector<std::vector<std::unique_ptr<Location>>> &&locations);

    private:
        std::vector<std::vector<std::unique_ptr<Location>>> _locations;
};



class Tour {
    private:
        std::vector<Location> *_locations;
        double _distance;
        void update_distance();

    public:
        Tour(std::vector<Location> *locations);
        std::vector<Location> &locations();
        double distance();
};
