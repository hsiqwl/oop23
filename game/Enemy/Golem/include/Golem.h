#ifndef LAB3_GOLEM_H
#define LAB3_GOLEM_H
#include "../../Base_Enemy/include/Enemy.h"

class Golem: public Enemy{
public:
    enum class golem_type{
        fire,
        stone,
        essence
    };
private:
    static inline Stats golem_stats{};
    golem_type type;
public:
    Golem(std::string &name_, std::pair<size_t, size_t> coordinates_, size_t xp_after_death_, golem_type type_);
    const golem_type& get_type() const {return type;};
    static void init_golem_stats();
};

#endif //LAB3_GOLEM_H
