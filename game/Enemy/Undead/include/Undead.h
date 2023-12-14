#ifndef LAB3_UNDEAD_H
#define LAB3_UNDEAD_H
#include "../../Base_Enemy/include/Enemy.h"
#include <libconfig.h++>
class Undead: public Enemy{
public:
    enum class undead_type{
        skeleton,
        zombie,
        ogre
    };
private:
    static inline Stats skeleton_stats{};
    static inline Stats zombie_stats{};
    static inline Stats ogre_stats{};
    undead_type type;
    Stats get_stats_by_type(undead_type type_);
    static void init_skeleton_stats();
    static void init_zombie_stats();
    static void init_ogre_stats();
    static std::string get_name_by_type(undead_type type_);
public:
    void change_attributes(undead_type new_type);
    static void init_stats();
    Undead(std::string &name_, std::pair<size_t, size_t> coordinates_, size_t xp_after_death_,
           undead_type type_);
    undead_type get_type() const { return type;};
    void set_type(undead_type type_){type = type_;};
};


#endif //LAB3_UNDEAD_H
