#ifndef GAME_VIEW_H
#define GAME_VIEW_H
#include <SFML/Graphics.hpp>
#include "../../Matrix/include/matrix.h"
#include "../../Cell/base_cell/include/Cell.h"
#include "../../Game_state/include/Game_state.h"
#include "../../Enemy/Undead/include/Undead.h"
#include "../../Enemy/Living/include/Living.h"
#include "../../Enemy/Golem/include/Golem.h"
#include "../../Cell/Essence/include/Essence.h"
#include <unordered_map>
#include <format>
struct map_textures{
    sf::Texture floor;
    sf::Texture wall;
    sf::Texture lava;
    sf::Texture stairs;
    sf::Texture door;
    sf::Texture essence;
    map_textures();
};

struct creature_textures{
    sf::Texture hero;
    sf::Texture skeleton;
    sf::Texture ogre;
    sf::Texture zombie;
    sf::Texture knight;
    sf::Texture soldier;
    sf::Texture stone_golem;
    sf::Texture fire_golem;
    sf::Texture essence_golem;
    sf::Image ashes;
    creature_textures();
};

struct map_drawer final {
    map_textures m_textures;
    creature_textures c_textures;
    sf::Font font;
    float width;
    float height;
    size_t width_in_blocks;
    size_t height_in_blocks;
    map_drawer() = default;
    map_drawer(float w, float h, size_t w_b, size_t h_b);
    void draw_dead_creatures(sf::RenderWindow* window, const std::unordered_map<std::pair<size_t,size_t>, Creature*, pair_hash>& dead);
    void draw_hero(sf::RenderWindow* window, const Necromant& hero);
    void draw_map(sf::RenderWindow* window, const matrix<Cell*>& map);
    void draw_creatures(sf::RenderWindow* window, const std::unordered_map<std::pair<size_t,size_t>, Creature*, pair_hash>& alive, const Necromant& hero);
    void draw_hero_info(sf::RenderWindow* window, const Necromant& hero);
private:
    sf::Sprite get_sprite_for_golem(Golem& golem);
    sf::Sprite get_sprite_for_cell(Cell::Type type);
    sf::Sprite get_sprite_for_creature(Creature& target);
    sf::Sprite get_sprite_for_undead(Undead& target);
    sf::Sprite get_sprite_for_living(Living& target);
    sf::Sprite get_sprite_for_hero();
};





#endif //GAME_VIEW_H
