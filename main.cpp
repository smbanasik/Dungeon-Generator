#include "dungeon_generator.hpp"

int main(int argc, char* argv[]) {

    DungeonGenerator gen(80, 40, 1);

    gen.generate_floor();
    gen.print_dungeon();

}