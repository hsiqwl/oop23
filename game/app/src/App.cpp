#include "../include/app.h"
#include <iostream>
#include <chrono>
#include <fstream>
#include <thread>
/*!
 * @brief the main method that runs the game and draws the current game state
 * @param window sf::RenderWindow pointer to the window to draw into
 */
void App::start(sf::RenderWindow *window) {
    window_info info(window, 1800, 1000, 1800 * 3 / 4, 1000);
    while (window->isOpen()) {
        sf::Event event;
        bool event_occured = false;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window->close();
                return;
            }
            controller.handle_event(event, info, event_occured);
            if (controller.get_service()->get_state()->get_level() >
                controller.get_service()->get_state()->get_max_level()) {
                return;
            }
            if (event_occured) {
                auto start = std::chrono::steady_clock::now();
                controller.get_service()->act_enemies();
                auto finish = std::chrono::steady_clock::now();
                auto time = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start);
                std::fstream out("timing unparalled.txt", std::ios::app);
                if(out.is_open()){
                  out << time <<std::endl;
                }
                out.close();
                if (!controller.get_service()->get_state()->get_necromant().is_alive()) {
                    close_app(window);
                }
            }
        }
        window->clear();
        drawer.draw_map(window, controller.get_service()->get_state()->get_curr_map());
        drawer.draw_creatures(window, controller.get_service()->get_state()->get_alive_creatures(),
                              controller.get_service()->get_state()->get_necromant());
        drawer.draw_dead_creatures(window, controller.get_service()->get_state()->get_dead_creatures());
        window->display();
    }

}
/*!
 * @brief constructor of an App type object, preloads all necessary info and creates the game state
 */
App::App(): controller(App::preload()){
    drawer.width_in_blocks = controller.get_service()->get_state()->get_curr_map().get_columns();
    drawer.height_in_blocks = controller.get_service()->get_state()->get_curr_map().get_rows();
    drawer.width = 1800 * 3 / 4;
    drawer.height = 1000;
    drawer.font.loadFromFile("../../tiles/Fonphoria.otf");
}

Necromant* App::make_hero() {
    Stats hero_stats(200, 50, 10);
    hero_stats.set_block_probability(0.15);
    hero_stats.set_max_level(4);
    hero_stats.set_curr_level(1);
    hero_stats.set_max_curr_xp(400);
    hero_stats.set_incremential_rate(1.5);
    std::string name = "necromant";
    Necromant* hero = new Necromant(name, Creature::Fraction::necromant, {30,30}, hero_stats);
    Curse* curse = new Curse();
    Dessication_for_mana* dess_mana = new Dessication_for_mana(hero);
    Dessication_for_health* dess_health = new Dessication_for_health(hero);
    Morphism* morphism = new Morphism(Undead::undead_type::ogre);
    Necromastery* necromastery = new Necromastery(Undead::undead_type::ogre);
    hero->learn_skill(*curse);
    hero->learn_skill(*dess_health);
    hero->learn_skill(*dess_mana);
    hero->learn_skill(*morphism);
    hero->learn_skill(*necromastery);
    return hero;
}

Controller App::preload() {
    try {
        std::vector<matrix<Cell*>> floors;
        std::jthread thread_3([&](){floors = App::load_map();});
        std::jthread thread_1([](){
            Skill::init_skill();
            Curse::init_curse();
            Dessication_for_health::init_dessication();
            Dessication_for_mana::init_dessication();
        });
        std::jthread thread_2([](){
            Undead::init_stats();
            Living::init_stats();
            Golem::init_golem_stats();
        });
        thread_1.join();
        Necromant *hero = App::make_hero();
        thread_2.join();
        std::unordered_map<std::pair<size_t, size_t>, Creature *, pair_hash> alive = load_creatures();
        thread_3.join();
        mark_busy_cells(alive, floors[0]);
        Game_state* game_state = new Game_state(hero, alive, floors);
        Game_service* game_service = new Game_service(game_state);
        return Controller(game_service);
    }catch (...)
    {
        throw;
    }
}

void App::mark_busy_cells(std::unordered_map<std::pair<size_t, size_t>, Creature *, pair_hash>& alive, matrix<Cell*> map)
{
    auto it = alive.begin();
    while(it!=alive.end()) {
        map[it->second->get_coordinates().first][it->second->get_coordinates().second]->set_if_movable_to(false);
        ++it;
    }
}

std::unordered_map<std::pair<size_t, size_t>, Creature *, pair_hash> App::load_creatures() {
    std::string skeleton = "skeleton";
    std::unordered_map<std::pair<size_t, size_t>, Creature *, pair_hash> alive;
    for(int j = 0; j < 60; ++j){
        Undead* enemy1 = new Undead(skeleton, {0,j}, rand()%10+1, Undead::undead_type::skeleton);
        Undead* enemy2 = new Undead(skeleton, {59,j}, rand()%10+1, Undead::undead_type::skeleton);
        alive.insert(std::make_pair(enemy1->get_coordinates(), enemy1));
        alive.insert(std::make_pair(enemy2->get_coordinates(), enemy2));
    }
    for(int i = 1; i < 59; ++i){
        Undead* enemy1 = new Undead(skeleton, {i,0}, rand()%10+1, Undead::undead_type::skeleton);
        Undead* enemy2 = new Undead(skeleton, {i,59}, rand()%10+1, Undead::undead_type::skeleton);
        alive.insert(std::make_pair(enemy1->get_coordinates(), enemy1));
        alive.insert(std::make_pair(enemy2->get_coordinates(), enemy2));
    }
    return alive;
}


std::vector<matrix<Cell *>> App::load_map() {
    std::vector<std::vector<short>> pre_map(60,std::vector<short>(60,1));
    std::vector<matrix<Cell*>> map;
    matrix<Cell*> level;
    for(int i = 0; i < pre_map.size(); ++i)
    {
        std::vector<Cell*> row;
        for(int j = 0; j < pre_map[0].size(); ++j)
        {
            switch (pre_map[i][j]) {
                case 0:{
                    Cell* cell = new Cell(Cell::Type::wall);
                    row.emplace_back(cell);
                    continue;
                }
                case 1:{
                    Cell* cell = new Cell(Cell::Type::floor);
                    row.emplace_back(cell);
                    continue;
                }
                case 2:{
                    Lava* cell = new Lava;
                    row.emplace_back(cell);
                    continue;
                }
                case 3:{
                    Stairs* cell = new Stairs(true);
                    row.emplace_back(cell);
                    continue;
                }
                case 4:{
                    Stairs* cell = new Stairs(false);
                    row.emplace_back(cell);
                    continue;
                }
                case 5:{
                    Essence* cell = new Essence;
                    row.emplace_back(cell);
                    continue;
                }
            }
        }
        level.emplace_back_row(row);
    }
    map.emplace_back(level);
    return map;
}

void App::close_app(sf::RenderWindow *window) {
    std::cout<<"ending game\n";
    sf::Text text;
    text.setString("GAME OVER");
    text.setFont(drawer.font);
    text.setCharacterSize(40);
    text.setPosition(900, 400);
    window->clear();
    window->draw(text);
    window->display();
    sleep(1);
    window->close();
}