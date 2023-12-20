#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "../Stats/include/Stats.h"
#include "../Creature/include/Creature.h"
#include "../Enemy/Base_Enemy/include/Enemy.h"
#include "../Enemy/Undead/include/Undead.h"
#include "../Necromant/include/Necromant.h"
#include "../Skill/Curse/include/Curse.h"
#include "../Skill/Dessication/include/Dessication.h"
#include "../Skill/Morphism/include/Morphism.h"
#include "../Game_state/include/Game_state.h"
#include "../Enemy/Living/include/Living.h"
#include "../Matrix/include/dynamic_array.h"

TEST_CASE("Stats tests")
{
    SECTION("Constructors")
    {
        Stats a;
        REQUIRE(a.get_max_hp() == 0);
        REQUIRE(a.get_curr_hp() == 0);
        REQUIRE(a.get_curr_mp() == 0);
        REQUIRE(a.get_max_mp() == 0);
        REQUIRE(a.get_curr_xp() == 0);
        REQUIRE(a.get_max_curr_xp() == 0);
        REQUIRE(a.get_base_dmg() == 0);
        REQUIRE(a.get_curr_level() == 0);
        REQUIRE(a.get_max_level() == 0);
        REQUIRE(a.get_block_probability() == 0);
        REQUIRE(a.get_incremential_rate() == 0);

        Stats b(0.05);
        REQUIRE(b.get_max_hp() == 0);
        REQUIRE(b.get_curr_hp() == 0);
        REQUIRE(b.get_curr_mp() == 0);
        REQUIRE(b.get_max_mp() == 0);
        REQUIRE(b.get_curr_xp() == 0);
        REQUIRE(b.get_max_curr_xp() == 0);
        REQUIRE(b.get_base_dmg() == 0);
        REQUIRE(b.get_curr_level() == 0);
        REQUIRE(b.get_max_level() == 0);
        REQUIRE(b.get_block_probability() == 0.05);
        REQUIRE(b.get_incremential_rate() == 0);

        Stats c(20,5,5);
        REQUIRE(c.get_max_hp() == 20);
        REQUIRE(c.get_curr_hp() == 20);
        REQUIRE(c.get_curr_mp() == 5);
        REQUIRE(c.get_max_mp() == 5);
        REQUIRE(c.get_curr_xp() == 0);
        REQUIRE(c.get_max_curr_xp() == 0);
        REQUIRE(c.get_base_dmg() == 5);
        REQUIRE(c.get_curr_level() == 1);
        REQUIRE(c.get_max_level() == 1);
        REQUIRE(c.get_block_probability() == 0);
        REQUIRE(c.get_incremential_rate() == 0);

        Stats d(a);
        REQUIRE(d.get_max_hp() == 0);
        REQUIRE(d.get_curr_hp() == 0);
        REQUIRE(d.get_curr_mp() == 0);
        REQUIRE(d.get_max_mp() == 0);
        REQUIRE(d.get_curr_xp() == 0);
        REQUIRE(d.get_max_curr_xp() == 0);
        REQUIRE(d.get_base_dmg() == 0);
        REQUIRE(d.get_curr_level() == 0);
        REQUIRE(d.get_max_level() == 0);
        REQUIRE(d.get_block_probability() == 0);
        REQUIRE(d.get_incremential_rate() == 0);
    }
    SECTION("Setters"){
        Stats a;
        a.set_curr_mp(5);
        REQUIRE(a.get_curr_mp() == 0);
        a.set_max_mp(5);
        REQUIRE(a.get_max_mp() == 5);
        a.set_curr_mp(5);
        REQUIRE(a.get_curr_mp() == 5);
        a.set_max_hp(50);
        REQUIRE(a.get_max_hp() == 50);
        a.set_curr_hp(30);
        REQUIRE(a.get_curr_hp() == 30);
        a.set_curr_hp(51);
        REQUIRE(a.get_curr_hp() == 50);
        a.set_max_level(1);
        REQUIRE(a.get_max_level() == 1);
        a.set_curr_level(1);
        REQUIRE(a.get_curr_level() == 1);
        REQUIRE_THROWS(a.set_block_probability(1.0));
        a.set_block_probability(0.5);
        REQUIRE(a.get_block_probability() == 0.5);
        a.set_incremential_rate(1.4);
        REQUIRE(a.get_incremential_rate() == 1.4);
    }
    SECTION("Logic functions"){
        Stats a(50,10,15);
        a.set_block_probability(0.5);
        a.set_max_curr_xp(40);
        a.set_max_level(2);
        a.set_incremential_rate(1.2);
        int c = a.get_curr_hp();
        a.set_curr_level(2);
        REQUIRE(c < a.get_curr_hp());
        c = a.get_curr_hp();
        a.set_curr_level(1);
        REQUIRE(c > a.get_curr_hp());
        a.set_curr_hp(30);
        a.add_hp(5);
        REQUIRE(a.get_curr_hp() == 35);
        a.set_curr_mp(0);
        a.add_mp(15);
        REQUIRE(a.get_curr_mp() == 10);
        a.add_xp(30);
        REQUIRE(a.get_curr_xp() == 30);
        a.add_xp(10);
        REQUIRE(a.get_curr_xp() == 0);
        REQUIRE(a.get_curr_level() == 2);
    }
}

TEST_CASE("Creature"){
    std::string name = "aaa";
    Creature a(name, Creature::Fraction::undead, {0,0});
    REQUIRE(a.get_name() == name);
    REQUIRE(a.get_fraction() == Creature::Fraction::undead);
    REQUIRE(a.get_coordinates().first == 0);
    REQUIRE(a.get_coordinates().second == 0);
    Stats b;
    REQUIRE(a.get_stats().get_curr_hp() == 0);
    a.set_coordinates({1,1});
    REQUIRE(a.get_coordinates().first == 1);
    REQUIRE(a.get_coordinates().second == 1);
    a.get_stats().set_max_hp(20);
    a.get_stats().set_curr_hp(20);
    a.receive_dmg(10);
    REQUIRE(a.get_stats().get_curr_hp() == 10);
    REQUIRE(a.is_alive() == true);
    REQUIRE(a.triggered() == false);
    a.trigger(true);
    REQUIRE(a.triggered() == true);
    a.die();
    REQUIRE(a.is_alive() == false);
    a.set_dead_state(false);
    REQUIRE(a.is_alive() == true);
    a.set_fraction(Creature::Fraction::necromant);
    REQUIRE(a.get_fraction() == Creature::Fraction::necromant);
    a.get_stats().set_base_dmg(10);
    Creature c(name,Creature::Fraction::undead,{1,1},a.get_stats());
    a.deal_dmg(c);
    REQUIRE(c.get_stats().get_curr_hp() == 0);
    REQUIRE(c.is_alive() == false);
}

TEST_CASE("Base Enemy"){
    std::string name = "name";
    Enemy a(name,Creature::Fraction::undead, {0,0}, 34);
    REQUIRE(a.get_xp_after_death() == 34);
}

TEST_CASE("Undead"){
    Undead::init_stats();
    std::string name = "name";
    Undead a(name,{0,0},34,Undead::undead_type::zombie);
    REQUIRE(a.get_stats().get_max_hp() == 34);
    REQUIRE(a.get_stats().get_curr_hp() == 34);
    REQUIRE(a.get_stats().get_max_mp() == 3);
    REQUIRE(a.get_stats().get_curr_mp() == 3);
    REQUIRE(a.get_stats().get_incremential_rate() == 1.1);
    REQUIRE(a.get_stats().get_curr_level() == 1);
    REQUIRE(a.get_stats().get_block_probability() == 0.13);
    REQUIRE(a.get_type() == Undead::undead_type::zombie);
    REQUIRE(a.get_coordinates().first == 0);
    REQUIRE(a.get_coordinates().second == 0);
    REQUIRE(a.get_stats().get_base_dmg() == 15);
    Undead b(name,{0,0},34,Undead::undead_type::skeleton);
    REQUIRE(b.get_stats().get_max_hp() == 30);
    REQUIRE(b.get_stats().get_curr_hp() == 30);
    REQUIRE(b.get_stats().get_max_mp() == 5);
    REQUIRE(b.get_stats().get_curr_mp() == 5);
    REQUIRE(b.get_stats().get_incremential_rate() == 1.1);
    REQUIRE(b.get_stats().get_curr_level() == 1);
    REQUIRE(b.get_stats().get_block_probability() == 0.05);
    REQUIRE(b.get_type() == Undead::undead_type::skeleton);
    REQUIRE(b.get_coordinates().first == 0);
    REQUIRE(b.get_coordinates().second == 0);
    REQUIRE(b.get_stats().get_base_dmg() == 10);
    Undead c(name,{0,0},34,Undead::undead_type::ogre);
    REQUIRE(c.get_stats().get_max_hp() == 50);
    REQUIRE(c.get_stats().get_curr_hp() == 50);
    REQUIRE(c.get_stats().get_max_mp() == 4);
    REQUIRE(c.get_stats().get_curr_mp() == 4);
    REQUIRE(c.get_stats().get_incremential_rate() == 1.1);
    REQUIRE(c.get_stats().get_curr_level() == 1);
    REQUIRE(c.get_stats().get_block_probability() == 0.02);
    REQUIRE(c.get_type() == Undead::undead_type::ogre);
    REQUIRE(c.get_coordinates().first == 0);
    REQUIRE(c.get_coordinates().second == 0);
    REQUIRE(c.get_stats().get_base_dmg() == 14);
    c.set_type(Undead::undead_type::skeleton);
    REQUIRE(c.get_type() == Undead::undead_type::skeleton);
}

TEST_CASE("Skills"){
    Skill::init_skill();
    SECTION("Curse") {
        Curse::init_curse();
        Curse a;
        REQUIRE(a.get_damage() == 20);
        REQUIRE(a.get_development() == 1);
        REQUIRE(a.get_mana_cost() == 15);
        a.upgrade();
        REQUIRE(a.get_damage() == 22);
        REQUIRE(a.get_development() == 2);
        REQUIRE(a.get_mana_cost() == 13);
        Creature b(const_cast<std::string &>(a.get_name()), Creature::Fraction::necromant, {0, 0});
        b.get_stats().set_max_hp(50);
        b.get_stats().set_curr_hp(50);
        a.apply_on(b);
        REQUIRE(b.get_stats().get_curr_hp() == 28);
    }

    SECTION("Dessication"){
        std::string name = "name";
        Dessication_for_health::init_dessication();
        Dessication_for_mana::init_dessication();
        Necromant* a = new Necromant(name,Creature::Fraction::necromant, {0,0});
        a->get_stats().set_max_hp(100);
        a->get_stats().set_max_mp(100);
        Creature b(name, Creature::Fraction::necromant, {0, 0});
        b.get_stats().set_max_hp(50);
        b.get_stats().set_curr_hp(50);
        b.get_stats().set_max_mp(50);
        b.get_stats().set_curr_mp(50);
        Dessication_for_mana c(a);
        Dessication_for_health d(a);
        REQUIRE(c.get_coefficient() == 1.7);
        REQUIRE(d.get_coefficient() == 1.5);
        REQUIRE(c.get_development() == 1);
        REQUIRE(d.get_development() == 1);
        c.apply_on(b);
        d.apply_on(b);
        REQUIRE(a->get_stats().get_curr_hp() == 75);
        REQUIRE(a->get_stats().get_curr_mp() == 85);
    }

    SECTION("Morphism"){
        std::string name = "name";
        Undead::init_stats();
        Undead b(name, {0, 0}, 34, Undead::undead_type::zombie);
        Morphism a(Undead::undead_type::skeleton);
        Creature d(name, Creature::Fraction::necromant, {0, 0});
        REQUIRE_NOTHROW(a.apply_on(b));
        REQUIRE(b.get_stats().get_curr_hp() == 30);
        REQUIRE(b.get_stats().get_max_hp() == 30);
        REQUIRE(b.get_stats().get_curr_mp() == 5);
        REQUIRE(b.get_stats().get_max_mp() == 5);
        REQUIRE(b.get_stats().get_base_dmg() == 10);
        REQUIRE(b.get_type() == Undead::undead_type::skeleton);
        REQUIRE_THROWS(a.apply_on(d));
    }

}

TEST_CASE("Vector"){
    SECTION("Default constructor"){
        Vector<int> v;
        REQUIRE(v.get_size() == 0);
        REQUIRE(v.get_capacity() == 0);
        REQUIRE(v.empty() == true);
        v.push_back(5);
        REQUIRE(*v.begin() == 5);
        REQUIRE_NOTHROW(v.at(0));
    }
    SECTION("explicit constructors"){
        {
            Vector<int> v(4);
            REQUIRE(v.get_size() == 4);
            REQUIRE(v.get_capacity() == 4);
            REQUIRE(v.empty() == false);
        }
        {
            Vector<int> v(2,35);
            REQUIRE(v.get_size() == 2);
            REQUIRE(v.get_capacity() == 2);
            REQUIRE(v[0] == 35);
            REQUIRE(v[1] == 35);
        }
        {
            std::initializer_list<int> il = {1,2,3};
            Vector<int> v(il);
            REQUIRE(v.get_size() == 3);
            REQUIRE(v.get_capacity() == 3);
            REQUIRE(v[0] == 1);
            REQUIRE(v[1] == 2);
            REQUIRE(v[2] == 3);
        }
    }
    SECTION("copy constructor"){
        Vector<int> a = {1,2,3,4};
        Vector<int> b(a);
        REQUIRE(b.empty() == false);
        REQUIRE(b.get_size() == 4);
        REQUIRE(b.get_capacity() == 4);
        REQUIRE_NOTHROW(b.at(2));
        a.clear();
        REQUIRE(b[0] == 1);
    }SECTION("move constructor"){
        Vector<int> a = {1,2,3,4};
        Vector<int> b(std::move(a));
        REQUIRE(a.empty() == true);
        REQUIRE(a.get_size() == 0);
        REQUIRE(a.get_capacity() == 0);
        REQUIRE(b[0] == 1);
    }

    SECTION("operators"){
        SECTION("assignment"){
            {
                Vector<int> a = {1, 2, 3};
                Vector<int> b;
                REQUIRE(b.empty() == true);
                b = a;
                REQUIRE(b.empty() == false);
                REQUIRE(b.get_size() == 3);
                REQUIRE(b.get_capacity() == 3);
                REQUIRE(a.get_size() == b.get_size());
                for (int i = 0; i < a.get_size(); ++i)
                    REQUIRE(a[i] == b[i]);
            }

            {
                Vector<int> a = {1,2,3};
                Vector<int> b;
                b = std::move(a);
                REQUIRE(a.get_size() == 0);
                REQUIRE(a.get_capacity() == 0);
                REQUIRE(a.data() == nullptr);
                REQUIRE(b.get_size() == 3);
                REQUIRE(b.get_capacity() == 3);
            }

            {
                std::initializer_list<int> il = {1,2,3};
                Vector<int> a;
                a = il;
                REQUIRE(a.empty() == false);
                REQUIRE(a.get_size() == 3);
                REQUIRE(a.get_capacity() == 3);
            }

        }
        SECTION("== operator"){
            Vector<int> a({1,2,3});
            Vector<int> b;
            Vector<int> c;
            REQUIRE((c == b) == true);
            REQUIRE((a == c) == false);
        }
        SECTION("subscript operator and front() and back()"){
            Vector<int> a = {1,2,3};
            for(int i = 0; i < a.get_size();++i){
                REQUIRE(a[i] == i+1);
            }
            REQUIRE(a.front() == 1);
            REQUIRE(a.back() == 3);
            REQUIRE_NOTHROW(a.at(2));
            REQUIRE_THROWS(a.at(3));
        }

        SECTION("memory methods"){
            Vector<int> a = {1,2,3};
            REQUIRE(a.get_capacity() == 3);
            a.reserve(2);
            REQUIRE(a.get_capacity() == 3);
            a.reserve(5);
            REQUIRE(a.get_capacity() == 5);

            a.shrink_to_fit();
            REQUIRE(a.get_capacity() == 3);

            Vector<int> b = {1,2,3,4,5,6};
            b.resize(4);
            REQUIRE(b.get_size() == 4);
            REQUIRE(b.get_capacity() == 4);
            REQUIRE(b[0] == 1);
            REQUIRE(b[1] == 2);
            REQUIRE(b[2] == 3);
            REQUIRE(b[3] == 4);
            REQUIRE_THROWS(b.at(4));
            b.resize(6);
            REQUIRE(b.get_size() == 6);
            REQUIRE(b.get_capacity() == 6);
            REQUIRE(b[0] == 1);
            REQUIRE(b[1] == 2);
            REQUIRE(b[2] == 3);
            REQUIRE(b[3] == 4);
            REQUIRE_NOTHROW(b.at(5));
        }

        SECTION("insertions"){
            {
                Vector<int> a;
                a.push_back(5);
                REQUIRE(a.empty() == false);
                REQUIRE(a.get_size() == 1);
                REQUIRE(a.get_capacity() == 1);
                REQUIRE(a[0] == 5);
                a.push_back(135);
                REQUIRE(a.empty() == false);
                REQUIRE(a.get_size() == 2);
                REQUIRE(a.get_capacity() == 2);
                REQUIRE(a[1] == 135);
            }

            {
                Vector<int> a = {1,2,3};
                auto it = a.insert(a.begin() + 1, 6);
                REQUIRE(*it == 6);
                REQUIRE(a.get_size() == 4);
                REQUIRE(a[1] == 6);
            }

            {
                Vector<int> a;
                a.assign(4, 24);
                REQUIRE(a.get_size() == 4);
                REQUIRE(a.get_capacity() == 4);
                REQUIRE(a[0] == 24);
            }
        }

        SECTION("deletions"){
            {
                Vector<int> v = {1, 2, 3, 4};
                auto it = v.erase(v.begin() + 1);
                REQUIRE(v.get_size() == 3);
                REQUIRE(*it == 3);
                REQUIRE(v[0] == 1);
                REQUIRE(v[1] == 3);
                REQUIRE(v[2] == 4);
                it = v.erase(v.end() - 1);
                REQUIRE(v.get_size() == 2);
                REQUIRE(it == v.end());
                REQUIRE(v[0] == 1);
                REQUIRE(v[1] == 3);
            }

            {
                Vector<int> v = {1,2,3};
                v.pop_back();
                REQUIRE(v.get_size() == 2);
                REQUIRE_THROWS(v.at(2));
            }
        }
    }


    SECTION("iterators"){
        Vector<int> v = {1,2,3};
        auto it = v.begin();
        REQUIRE((it != v.begin() + 1) == true);
        REQUIRE((v.end() > it) == true);
        REQUIRE(*it == 1);
        REQUIRE(*(++it) == 2);
        REQUIRE(--it == v.begin());
        REQUIRE((it + 3) == v.end());
        REQUIRE((++it - v.end()) == -2);
        REQUIRE((v.end() - it) == 2);
        REQUIRE(it[0] == 2);
        REQUIRE(it[1] == 3);
    }
}


TEST_CASE("Necromant"){
    std::string name = "name";
    Necromant* a = new Necromant(name,Creature::Fraction::necromant,{0,0});
    REQUIRE(a->get_skill_points() == 0);
    REQUIRE(a->get_curr_minions() == 0);
    REQUIRE(a->get_max_minions() == 3);
    REQUIRE(a->get_essence() == 0);
    a->get_stats().set_max_hp(50);
    a->get_stats().set_curr_hp(50);
    a->set_skill_points(5);
    Curse* b = new Curse;
    REQUIRE_NOTHROW(a->learn_skill(*b));
    REQUIRE(a->get_skill_points() == 4);
    REQUIRE_NOTHROW(a->choose_skill(b->get_name()));
    REQUIRE(b == a->choose_skill(b->get_name()));
    a->set_skill_points(1);
    REQUIRE_NOTHROW(a->upgrade_skill(*b));
    REQUIRE(a->get_skill_points() == 0);
    REQUIRE_THROWS(a->upgrade_skill(*b));
    a->set_essence(359);
    REQUIRE(a->get_essence() == 359);
}

TEST_CASE("Game state"){
    std::string name = "name";
    Necromant* hero = new Necromant(name,Creature::Fraction::necromant,{0,0});
    std::unordered_map<std::pair<size_t,size_t>, Creature*, pair_hash> alive;
    std::vector<std::vector<short>> lvl =
            {{0,0,0,0,0,0},
             {0,0,1,1,1,1},
             {0,1,1,1,1,1}};
    std::vector<matrix<Cell*>> map;
    matrix<Cell*> level;
    for(int i = 0; i < lvl.size(); ++i)
    {
        std::vector<Cell*> row;
        for(int j = 0; j < lvl[0].size(); ++j)
        {
            switch (lvl[i][j]) {
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
            }
        }
        level.emplace_back_row(row);
    }
    map.emplace_back(level);
    Game_state* state = new Game_state(hero, alive, map);
    REQUIRE(state->get_level() == 1);
    REQUIRE(state->get_max_level() == 1);
    REQUIRE_THROWS(state->get_alive_creature_by_coordinates({0,0}));
    REQUIRE_THROWS(state->get_dead_creature_by_coordinates({0,0}));
    Undead b(name, {0, 0}, 34, Undead::undead_type::zombie);
    REQUIRE_NOTHROW(state->add_alive_creature(b));
    REQUIRE_THROWS(state->add_alive_creature(b));
    REQUIRE_NOTHROW(state->get_alive_creature_by_coordinates({0,0}));
    REQUIRE(state->get_alive_creature_by_coordinates({0,0}) == &b);
    REQUIRE_THROWS(state->get_dead_creature_by_coordinates({0,0}));
    state->remove_alive_creature({0,0});
    REQUIRE_THROWS(state->get_dead_creature_by_coordinates({0,0}));
    REQUIRE_THROWS(state->get_alive_creature_by_coordinates({0,0}));
    Living c(name,{1,2},34,Living::living_type::knight);
    REQUIRE_NOTHROW(state->add_alive_creature(c));
    state->add_dead_creature(c);
    REQUIRE_NOTHROW(state->get_dead_creature_by_coordinates(c.get_coordinates()));
}
