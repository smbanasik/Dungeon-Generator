#include "dungeon_generator.hpp"

#include <stdint.h>
#include <iostream>
#include <random>
#include <cmath>
# define M_PI 3.14159265358979323846

void DungeonGenerator::resize_dungeon(uint16_t x, uint16_t y) {

    if (floor_data != nullptr)
        free_floor_data();

    floor_data = new uint16_t[x * y]{ 0 };
    width = x;
    height = y;

}

void DungeonGenerator::config_spacing(uint16_t spacing) {
    this->settings.tiles_spacing = spacing;
}
void DungeonGenerator::config_share_walls(bool share) {
    this->settings.should_share_walls = share;
}
void DungeonGenerator::config_num_towers(uint16_t towers) {
    this->settings.towers = towers;;
}
void DungeonGenerator::config_num_rooms(uint16_t rooms) {
    this->settings.rooms = rooms;
}

void DungeonGenerator::generate_floor() {

    generate_starter();

    for (int i = 0; i < settings.rooms; i++) {
        uint32_t spot = pick_spot();
        generate_room(spot, 5, 5);
    }
    for (int i = 0; i < settings.towers; i++) {
        uint32_t spot = pick_spot();
        generate_tower(spot, 5);
    }
}

void DungeonGenerator::print_dungeon() {

    char out_char = '\0';
    for (int i = 0; i < height*width; i++) {
        switch (floor_data[i]) {
        case 0:
            out_char = 'X';
            break;
        case 1:
            out_char = ' ';
            break;
        case 2:
            out_char = '@';
            break;
        default:
            out_char = '+';
            break;
        }

        std::cout << out_char;

        if ((i+1) % (width) == 0)
            std::cout << "\n";

    }
}


void DungeonGenerator::initialize_settings() {

    this->settings.rooms = 5;
    this->settings.should_share_walls = false;
    this->settings.towers = 1;
    this->settings.tiles_spacing = 2;
    this->settings.seed = 105;
    this->settings.last_value = 0;

}
void DungeonGenerator::free_floor_data() {

    delete[] floor_data;
}

void DungeonGenerator::generate_starter() {

    uint32_t spot = pick_spot();

    floor_data[spot] = 2;

    generate_room(spot, 7, 7);
    //generate_hall(0, 349);
    //generate_room(spot, 3, 5);
    //generate_room(spot - 60, 5, 5);

}
void DungeonGenerator::generate_room(uint32_t center, uint32_t x, uint32_t y) {

    // Our center is a number in the data
    uint32_t spot = center - (std::floor(y*0.5f) * width) - std::floor(x*0.5f);

    for (uint32_t i = 0; i < x * y; i++) {
        if (spot < height*width && floor_data[spot] == 0)
            floor_data[spot] = 1;
        spot++;
        if ((i + 1) % x == 0) {
            spot -= x;
            spot = spot + width;
        }
    }
}
void DungeonGenerator::generate_tower(uint32_t center, uint32_t radius) {

    // Our center is a number in the data
    uint32_t spot = center - (std::floor(radius) * width) - std::floor(radius);
    uint32_t diameter = radius * 2;

    int32_t center_y = get_pos_y(center);
    int32_t center_x = get_pos_x(center);

    for (uint32_t i = 0; i < diameter * diameter; i++) {
        // To generate a circle, get the distance from the spot to the center.
        int32_t spot_y = get_pos_y(spot);
        int32_t spot_x = get_pos_x(spot);

        int32_t dx = spot_x - center_x;
        int32_t dy = spot_y - center_y;

        uint32_t distance = std::sqrt((dx * dx) + (dy * dy));

        if (spot < height * width && floor_data[spot] == 0 && distance < radius)
            floor_data[spot] = 1;
        spot++;

        if ((i + 1) % diameter == 0) {
            spot -= diameter;
            spot = spot + width;
        }
    }
}
void DungeonGenerator::generate_hall(uint32_t start, uint32_t end) {

    // TODO: this algorithm is dependent on the slope being <1
    // and the start_x < end_x
    // to handle the slope being >1, we can just swap the x and y (since a tall x is a wide y)
    // to handle the start x < end x, we just need to normalize the coordinates

    int32_t start_x = get_pos_x(start);
    int32_t start_y = get_pos_y(start);
    int32_t end_x = get_pos_x(end);
    int32_t end_y = get_pos_y(end);

    int32_t dx = start_x - end_x;
    int32_t dy = start_y - end_y;

    for (int i = start_x; i < end_x; i++) {
        int j = start_y + dy * (i - start_x) / dx;
        uint32_t spot = get_index_from_coords(i, j);
        if (floor_data[spot] == 0)
            floor_data[spot] = 1;
    }
}
uint32_t DungeonGenerator::pick_spot() {

    std::mt19937 generator(settings.seed + settings.last_value);
    std::uniform_int_distribution<uint16_t> number(0, width * height);
    settings.last_value = number(generator);
    return settings.last_value;
}

uint32_t DungeonGenerator::get_pos_x(uint32_t position) {
    return position % width;
}
uint32_t DungeonGenerator::get_pos_y(uint32_t position) {
    return position / width;
}
uint32_t DungeonGenerator::get_index_from_coords(uint32_t x, uint32_t y) {
    return (y * width) + x;
}