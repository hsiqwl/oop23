#include "../include/View.h"
#include <iostream>
/*!
 * @brief loading necessary tiles and images for landscape drawing
 */
map_textures::map_textures() {
    floor.loadFromFile("../../tiles/stone_tile.png");
    wall.loadFromFile("../../tiles/wall.png");
    lava.loadFromFile("../../tiles/lava_tile.png");
    stairs.loadFromFile("../../tiles/stairs_up.png");
    door.loadFromFile("../../tiles/door.png");
    essence.loadFromFile("../../tiles/essence.png");
}
/*!
 * @brief loading necessary tiles and images for creatures drawing
 */
creature_textures::creature_textures() {
    hero.loadFromFile("../../tiles/necromant.png");
    zombie.loadFromFile("../../tiles/zombie.png");
    ogre.loadFromFile("../../tiles/ogre.png");
    knight.loadFromFile("../../tiles/knight.png");
    skeleton.loadFromFile("../../tiles/skeleton.png");
    soldier.loadFromFile("../../tiles/soldier.png");
    fire_golem.loadFromFile("../../tiles/fire_golem.png");
    stone_golem.loadFromFile("../../tiles/stone_golem.png");
    essence_golem.loadFromFile("../../tiles/essence_golem.png");
    ashes.loadFromFile("../../tiles/ashes.png");
}

map_drawer::map_drawer(float w, float h, size_t w_b, size_t h_b) {
    width = w;
    height = h;
    width_in_blocks = w_b;
    height_in_blocks = h_b;
}
/*!
 * @brief gets necessary sprite for a cell
 * @param type cell type
 * @return sf::Sprite object that contains a sprite
 */
sf::Sprite map_drawer::get_sprite_for_cell(Cell::Type type) {
    switch (type) {
        case Cell::Type::floor:{
            sf::Sprite sprite(m_textures.floor);
            return sprite;
        }
        case Cell::Type::lava:{
            sf::Sprite sprite(m_textures.lava);
            return sprite;
        }
        case Cell::Type::wall:{
            sf::Sprite sprite(m_textures.wall);
            return sprite;
        }
        case Cell::Type::essence:{
            sf::Sprite sprite(m_textures.essence);
            return sprite;
        }
        case Cell::Type::door:{
            sf::Sprite sprite(m_textures.door);
            return sprite;
        }
        case Cell::Type::stairs:{
            sf::Sprite sprite(m_textures.stairs);
            return sprite;
        }
    }
}
/*!
 * @brief gets a sprite for hero
 * @return sf::Sprite object
 */
sf::Sprite map_drawer::get_sprite_for_hero() {
    sf::Sprite sprite(c_textures.hero);
    return sprite;
}

/*!
 * @brief gets a sprite for a living type creature
 * @param target Living type reference to a creature
 * @return sf::Sprite object
 */
sf::Sprite map_drawer::get_sprite_for_living(Living &target) {
    switch(target.get_type()){
        case Living::living_type::knight:
            return sf::Sprite(c_textures.knight);
        case Living::living_type::soldier:
            return sf::Sprite(c_textures.soldier);
    }
}
/*!
 * @brief gets a sprite for an undead type creature
 * @param target Undead type reference to a creature
 * @return sf::Sprite object
 */
sf::Sprite map_drawer::get_sprite_for_undead(Undead &target) {
    switch (target.get_type()) {
        case Undead::undead_type::zombie:
            return sf::Sprite(c_textures.zombie);
        case Undead::undead_type::skeleton:
            return sf::Sprite(c_textures.skeleton);
        case Undead::undead_type::ogre:
            return sf::Sprite(c_textures.ogre);
    }
}
/*!
 * @brief gets a sprite for a golem type creature
 * @param target Golem type reference to a creature
 * @return sf::Sprite object
 */
sf::Sprite map_drawer::get_sprite_for_golem(Golem& target) {
    switch (target.get_type()) {
        case Golem::golem_type::fire:
            return sf::Sprite(c_textures.fire_golem);
        case Golem::golem_type::stone:
            return sf::Sprite(c_textures.stone_golem);
        case Golem::golem_type::essence:
            return sf::Sprite(c_textures.essence_golem);
    }
}

/*!
 * @brief gets a sprite for a creature
 * @param target Creature type reference to a creature
 * @return sf::Sprite object
 */
sf::Sprite map_drawer::get_sprite_for_creature(Creature &target) {
    switch (target.get_fraction()){
        case Creature::Fraction::living:{
            Living& enemy = dynamic_cast<Living&>(target);
            return get_sprite_for_living(enemy);
        }
        case Creature::Fraction::undead:{
            Undead& enemy = dynamic_cast<Undead&>(target);
            return get_sprite_for_undead(enemy);
        }
        case Creature::Fraction::golem:{
            Golem& enemy = dynamic_cast<Golem&>(target);
            return get_sprite_for_golem(enemy);
        }
        case Creature::Fraction::necromant:
            try{
                Undead& enemy = dynamic_cast<Undead&>(target);
                return get_sprite_for_undead(enemy);
            }
            catch (...) {
                return get_sprite_for_hero();
            }
    }
}
/*!
 * @brief draws a landscape
 * @param window sf::RenderWindow pointer to the window to be drawn into
 * @param map matrix of the current map
 */
void map_drawer::draw_map(sf::RenderWindow *window, const matrix<Cell*>& map) {
    float sprite_width = width / width_in_blocks;
    float sprite_height = height / height_in_blocks;
    for (int i = 0; i < height_in_blocks; ++i) {
        for (int j = 0; j < width_in_blocks; ++j) {
            sf::Sprite sprite = get_sprite_for_cell(map[i][j]->get_type());
            sprite.scale(sprite_width / sprite.getTexture()->getSize().x,
                         sprite_height / sprite.getTexture()->getSize().y);
            sprite.setPosition(j * sprite_width, i * sprite_height);
            window->draw(sprite);
        }
    }
}
/*!
 * @brief draws dead creatures on the map
 * @param window sf::RenderWindow pointer to the window to be drawn into
 * @param dead hash_map of dead creatures
 */
void map_drawer::draw_dead_creatures(sf::RenderWindow *window,
                                     const std::unordered_map<std::pair<size_t, size_t>, Creature *, pair_hash> &dead) {
    float scaled_width = width / width_in_blocks;
    float scaled_height = height / height_in_blocks;
    auto creature = dead.begin();
    while(creature!=dead.end()){
        c_textures.ashes.createMaskFromColor(sf::Color::White);
        sf::Texture texture;
        texture.loadFromImage(c_textures.ashes);
        sf::Sprite sprite = sf::Sprite(texture);
        sprite.setOrigin(scaled_width/2, scaled_height/2);
        sprite.setPosition(creature->second->get_coordinates().second * scaled_width + scaled_width/4, creature->second->get_coordinates().first * scaled_height + scaled_height/4);
        sprite.scale(scaled_width * 0.5 / sprite.getTexture()->getSize().x, scaled_height * 0.5 / sprite.getTexture()->getSize().y);
        window->draw(sprite);
        ++creature;
    }
}
/*!
 * @brief draws all the alive creatures on the map
 * @param window sf::RenderWindow pointer to the window to be drawn into
 * @param alive hash_map of alive creatures
 * @param hero Necromant type reference to a hero
 */
void map_drawer::draw_creatures(sf::RenderWindow *window,
                                const std::unordered_map<std::pair<size_t, size_t>, Creature *, pair_hash> &alive,
                                const Necromant &hero) {
    draw_hero(window, hero);
    float scaled_width = width / width_in_blocks;
    float scaled_height = height / height_in_blocks;
    auto creature = alive.begin();
    while(creature!=alive.end()){
        sf::Sprite sprite = get_sprite_for_creature(*creature->second);
        double health_bar_scale = static_cast<double>(creature->second->get_stats().get_curr_hp()) / static_cast<double>(creature->second->get_stats().get_max_hp());
        sf::RectangleShape health_bar(sf::Vector2f(scaled_width * 0.5 * health_bar_scale,10));
        sprite.setOrigin(scaled_width/2, scaled_height/2);
        sprite.setPosition(creature->second->get_coordinates().second * scaled_width + scaled_width/4, creature->second->get_coordinates().first * scaled_height + scaled_height/4);
        sprite.scale(scaled_width * 0.5 / sprite.getTexture()->getSize().x, scaled_height * 0.5 / sprite.getTexture()->getSize().y);
        health_bar.setPosition(creature->second->get_coordinates().second * scaled_width + scaled_width/4, creature->second->get_coordinates().first * scaled_height + scaled_height/4 - 15);
        if(creature->second->get_fraction() == Creature::Fraction::necromant){
            health_bar.setFillColor(sf::Color::Green);
        }else{
            health_bar.setFillColor(sf::Color::Red);
        }
        window->draw(sprite);
        window->draw(health_bar);
        ++creature;
    }
}
/*!
 * @brief draws the hero on the map
 * @param window sf::RenderWindow pointer to the window to be drawn into
 * @param hero Necromant type reference to a hero
 */
void map_drawer::draw_hero(sf::RenderWindow *window, const Necromant &hero){
    sf::Sprite hero_sprite = get_sprite_for_hero();
    double health_bar_scale = static_cast<double>(hero.get_stats().get_curr_hp()) / static_cast<double>(hero.get_stats().get_max_hp());
    float scaled_width = width / width_in_blocks;
    float scaled_height = height / height_in_blocks;
    sf::RectangleShape health_bar(sf::Vector2f(scaled_width * 0.5 * health_bar_scale,10));
    health_bar.setFillColor(sf::Color::Green);
    hero_sprite.scale(scaled_width * 0.6 / hero_sprite.getTexture()->getSize().x, scaled_height * 0.6 / hero_sprite.getTexture()->getSize().y);
    hero_sprite.setPosition(hero.get_coordinates().second * scaled_width + scaled_width / 4, hero.get_coordinates().first * scaled_height + scaled_height/4);
    health_bar.setPosition(hero.get_coordinates().second * scaled_width + scaled_width / 4, hero.get_coordinates().first * scaled_height + scaled_height/4 - 15);
    window->draw(hero_sprite);
    window->draw(health_bar);
    draw_hero_info(window, hero);
}
/*!
 * @brief draws hero information into the window
 * @param window sf::RenderWindow pointer to the window to be drawn into
 * @param hero Necromant type reference to a hero
 */
void map_drawer::draw_hero_info(sf::RenderWindow *window, const Necromant &hero) {
    std::string hp_info = std::format("HP:{}/{}", hero.get_stats().get_curr_hp(), hero.get_stats().get_max_hp());
    std::string mp_info = std::format("MP:{}/{}", hero.get_stats().get_curr_mp(), hero.get_stats().get_max_mp());
    std::string xp_info = std::format("XP:{}/{}, LVL:{}", hero.get_stats().get_curr_xp(), hero.get_stats().get_max_curr_xp(), hero.get_stats().get_curr_level());
    std::string essence_info = std::format("ESSENCE:{}", hero.get_essence());
    std::vector<std::string> info_strings = {hp_info, mp_info, xp_info, essence_info};
    for(int i = 0; i < info_strings.size(); ++i){
        sf::Text text;
        text.setString(info_strings[i]);
        text.setCharacterSize(24);
        text.setFont(font);
        text.setPosition(width, 24 * i);
        window->draw(text);
    }
}


