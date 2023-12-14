#include "../include/app.h"
#include <iostream>
#include <ctime>
#include <fstream>
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
                clock_t start = clock();
                controller.get_service()->act_enemies_mt();
                clock_t end = clock();
                double time = static_cast<double>(double(end - start) * 1000 / CLOCKS_PER_SEC);
                std::ofstream out("timing paralled.txt", std::ios::app);
                if (out.is_open())
                    out << time << std::endl;
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
    Necromant* hero = new Necromant(name, Creature::Fraction::necromant, {10,13}, hero_stats);
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
        Skill::init_skill();
        Curse::init_curse();
        Dessication_for_health::init_dessication();
        Dessication_for_mana::init_dessication();
        Undead::init_stats();
        Living::init_stats();
        Golem::init_golem_stats();
        Necromant *hero = App::make_hero();
        std::vector<matrix<Cell*>> floors = App::load_map();
        std::unordered_map<std::pair<size_t, size_t>, Creature *, pair_hash> alive = load_creatures();
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
    std::string zombie = "zombie";
    std::string knight = "knight";
    std::string skeleton = "skeleton";
    Golem* enemy_1 = new Golem(zombie, {1,2}, rand()%100 + 100, Golem::golem_type::fire);
    Golem* enemy_4 = new Golem(zombie, {3,4}, rand()%100 + 100, Golem::golem_type::essence);
    Living* enemy_2 = new Living(knight, {2,10}, rand()%100 + 100, Living::living_type::knight);
    Undead* enemy_3 = new Undead(skeleton, {2,15}, rand()%100 + 100, Undead::undead_type::skeleton);
    Undead* enemy_5 = new Undead(skeleton, {3,21}, rand()%100 + 100, Undead::undead_type::zombie);
    Undead* enemy_6 = new Undead(skeleton, {6,11}, rand()%100 + 100, Undead::undead_type::ogre);
    Golem* enemy_7 = new Golem(zombie, {9,1}, rand()%100 + 100, Golem::golem_type::essence);
    Undead* enemy_8 = new Undead(zombie, {9,19}, rand()%100 + 100, Undead::undead_type::ogre);
    Living* enemy_9 = new Living(zombie, {16,2}, rand()%100 + 100, Living::living_type::soldier);
    Living* enemy_10 = new Living(zombie, {16,8}, rand()%100 + 100, Living::living_type::soldier);
    Undead* enemy_11 = new Undead(skeleton, {15,19}, rand()%100 + 100, Undead::undead_type::skeleton);
    Undead* enemy_12 = new Undead(skeleton, {17,5}, rand()%100 + 100, Undead::undead_type::skeleton);
    Living* enemy_13 = new Living(skeleton, {17,15}, rand()%100 + 100, Living::living_type::knight);


    std::unordered_map<std::pair<size_t, size_t>, Creature *, pair_hash> alive;
    alive.insert(std::make_pair(enemy_1->get_coordinates(),enemy_1));
    alive.insert(std::make_pair(enemy_2->get_coordinates(),enemy_2));
    alive.insert(std::make_pair(enemy_3->get_coordinates(),enemy_3));
    alive.insert(std::make_pair(enemy_4->get_coordinates(),enemy_4));
    alive.insert(std::make_pair(enemy_5->get_coordinates(),enemy_5));
    alive.insert(std::make_pair(enemy_7->get_coordinates(),enemy_7));
    alive.insert(std::make_pair(enemy_8->get_coordinates(),enemy_8));
    alive.insert(std::make_pair(enemy_9->get_coordinates(),enemy_9));
    alive.insert(std::make_pair(enemy_10->get_coordinates(),enemy_10));
    alive.insert(std::make_pair(enemy_11->get_coordinates(),enemy_11));
    alive.insert(std::make_pair(enemy_12->get_coordinates(),enemy_12));
    alive.insert(std::make_pair(enemy_6->get_coordinates(),enemy_6));
    alive.insert(std::make_pair(enemy_13->get_coordinates(),enemy_13));

    return alive;
}


std::vector<matrix<Cell *>> App::load_map() {
    std::vector<std::vector<short>> pre_map = {
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
            {0,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
            {0,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
            {0,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,5,1,1,1,1,1,0},
            {0,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
            {0,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
            {0,0,0,2,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
            {0,0,0,2,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
            {0,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
            {0,1,1,1,1,1,1,2,5,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
            {0,1,1,1,1,1,1,2,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
            {0,0,0,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
            {0,0,0,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
            {0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0},
            {0,1,1,1,1,5,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,1,1,0},
            {0,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,0},
            {0,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,5,5,0},
            {0,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,5,5,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
    };
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