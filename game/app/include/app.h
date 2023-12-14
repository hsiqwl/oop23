#ifndef GAME_APP_H
#define GAME_APP_H
#include "../../View/include/View.h"
#include "../../Controller/include/Controller.h"
#include "../../Skill/Dessication/include/Dessication.h"
#include "../../Skill/Curse/include/Curse.h"
#include "../../Skill/Morphism/include/Morphism.h"
#include "../../Skill/Necromastery/include/Necromastery.h"
#include "../../Cell/Stairs/include/Stairs.h"
#include "../../Matrix/include/matrix.h"
#include <format>
#include <libconfig.h++>
class App{
public:
    App();
    void start(sf::RenderWindow* window);
private:
    void close_app(sf::RenderWindow* window);
    static Controller preload();
    static Necromant* make_hero();
    static std::unordered_map<std::pair<size_t ,size_t>, Creature*, pair_hash> load_creatures();
    static std::vector<matrix<Cell*>> load_map();
    static void mark_busy_cells(std::unordered_map<std::pair<size_t, size_t>, Creature *, pair_hash>& alive, matrix<Cell*> map);
    map_drawer drawer;
    Controller controller;
};

#endif //GAME_APP_H
