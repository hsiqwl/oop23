#ifndef LAB3_HERO_SERVICE_H
#define LAB3_HERO_SERVICE_H
#include "../../Game_state/include/Game_state.h"
#include "../../Cell/interactable_cell/include/Interactable_cell.h"
class Hero_service{
private:
    Game_state* state;
    bool check_if_can_apply_skill(const std::pair<size_t,size_t>& coordinates);
public:
    Hero_service(Game_state* state_);
    void cast_skill(const std::string& skill_name ,const std::pair<size_t,size_t>& coordinates);
    void interact_with_cell(const std::pair<size_t,size_t>& coordinates);
};

#endif //LAB3_HERO_SERVICE_H
