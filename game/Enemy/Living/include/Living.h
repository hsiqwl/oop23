#ifndef LAB3_LIVING_H
#define LAB3_LIVING_H
#include "../../Base_Enemy/include/Enemy.h"
#include <libconfig.h++>
class Living: public Enemy{
public:
    enum class living_type{
        knight,
        soldier
    };
    Living(std::string& name_, std::pair<size_t, size_t> coordinates_, size_t xp_after_death, living_type type_);
    living_type get_type() const {return type;};
    static void init_stats();
private:
    living_type type;
    static inline Stats knight_stats{};
    static inline Stats soldier_stats{};
    static void init_knight_stats();
    static void init_soldier_stats();
};
#endif //LAB3_LIVING_H
