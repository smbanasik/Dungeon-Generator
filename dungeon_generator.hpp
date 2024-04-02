#ifndef SB_DUNGEON_GENERATOR_HPP
#define SB_DUNGEON_GENERATOR_HPP

#include <stdint.h>

class DungeonGenerator {
public:

    DungeonGenerator(uint16_t x, uint16_t y, uint32_t seed) : floor_data(nullptr), width(x), height(y) {

        resize_dungeon(x, y);
        initialize_settings();
        settings.seed = seed;
    }

    ~DungeonGenerator() {

        free_floor_data();
    }

    void resize_dungeon(uint16_t x, uint16_t y);

    void config_spacing(uint16_t spacing);
    void config_share_walls(bool share);
    void config_num_towers(uint16_t towers);
    void config_num_rooms(uint16_t rooms);

    // TODO: configure room size, add some variation
    //void config_room_size(uint16_t x, uint16_t y);

    void generate_floor();

    
    void print_dungeon();

private:

    uint16_t* floor_data;
    uint16_t width, height;

    struct {
        uint16_t tiles_spacing, towers, rooms, should_share_walls;
        uint32_t seed, last_value;
    } settings;

    void initialize_settings();
    void free_floor_data();

    void generate_starter();
    void generate_room(uint32_t center, uint32_t x, uint32_t y);
    void generate_tower(uint32_t center, uint32_t radius);
    void generate_hall(uint32_t start, uint32_t end);

    uint32_t pick_spot();
    uint32_t get_pos_x(uint32_t position);
    uint32_t get_pos_y(uint32_t position);
    uint32_t get_index_from_coords(uint32_t x, uint32_t y);

};

#endif