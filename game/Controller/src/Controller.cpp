#include "../include/Controller.h"
#include <cmath>
/*!
 * @brief constructor for the window info
 * @param window pointer to the sf::RenderWindow type
 * @param w width of the window
 * @param h height of the window
 * @param r_w width that will be rendered
 * @param r_h height that will be rendered
 */
window_info::window_info(sf::RenderWindow* window,float w, float h, float r_w, float r_h): window(window) {
    window_width = w;
    window_height = h;
    rendering_width = r_w;
    rendering_height = r_h;
}

Controller::Controller(Game_service *service): service(service){}
/*!
 * @brief method that calculates coordinates of map block based on the mose position
 * @param mouse_position pair of coordinates of the mouse position
 * @param info reference to window_info type
 * @return pair of coordinates on the map block
 */
std::pair<size_t, size_t> Controller::get_coordinates_on_map(const sf::Vector2i& mouse_position,window_info& info) {
    size_t block_width = info.rendering_width / service->get_state()->get_curr_map().get_columns();
    size_t block_height = info.rendering_height / service->get_state()->get_curr_map().get_rows();
    size_t x_coord = mouse_position.x;
    size_t y_coord = mouse_position.y;
    while(x_coord % block_width != 0)
        --x_coord;
    while(y_coord % block_height != 0)
        --y_coord;
    return std::make_pair(y_coord / block_height, x_coord / block_width);
}
/*!
 * @brief reacts to pressing a keyboard key
 * @param key_code enum type representing the letter that was pressed
 * @param info reference to a window_info type
 */
void Controller::handle_key_pressed(sf::Keyboard::Key key_code, window_info& info, bool& event_occured) {
    switch(key_code){
        case sf::Keyboard::Key::W: {
            service->get_creature_service()->move(service->get_creature_service()->get_state().get_necromant(),
                                                  Creature_service::Direction::up);
            break;
        }
        case sf::Keyboard::Key::S: {
            service->get_creature_service()->move(service->get_creature_service()->get_state().get_necromant(),
                                                  Creature_service::Direction::down);
            break;
        }
        case sf::Keyboard::Key::A: {
            service->get_creature_service()->move(service->get_creature_service()->get_state().get_necromant(),
                                                  Creature_service::Direction::left);
            break;
        }
        case sf::Keyboard::Key::D: {
            service->get_creature_service()->move(service->get_creature_service()->get_state().get_necromant(),
                                                  Creature_service::Direction::right);
            break;
        }
        case sf::Keyboard::Key::Z: {
            std::pair<size_t, size_t> target_coord = get_coordinates_on_map(sf::Mouse::getPosition(*info.window), info);
            service->get_creature_service()->get_hero_service().cast_skill("Curse", target_coord);
            Creature *target;
            try {
                target = service->get_state()->get_alive_creature_by_coordinates(target_coord);
            }catch (...){
                break;
            }
            if(!target->is_alive()) {
                service->get_creature_service()->handle_creature_death(*target);
                service->get_state()->get_necromant().get_stats().add_xp(((Enemy*)target)->get_xp_after_death());
            }
            break;
        }
        case sf::Keyboard::Key::X:{
            std::pair<size_t, size_t> target_coord = get_coordinates_on_map(sf::Mouse::getPosition(*info.window), info);
            service->get_creature_service()->get_hero_service().cast_skill("Dessication for mana", target_coord);
            service->get_state()->remove_dead_creature(target_coord);
            break;
        }
        case sf::Keyboard::Key::C:{
            std::pair<size_t, size_t> target_coord = get_coordinates_on_map(sf::Mouse::getPosition(*info.window), info);
            service->get_creature_service()->get_hero_service().cast_skill("Dessication for health", target_coord);
            service->get_state()->remove_dead_creature(target_coord);
            break;
        }
        case sf::Keyboard::Key::V:{
            std::pair<size_t, size_t> target_coord = get_coordinates_on_map(sf::Mouse::getPosition(*info.window), info);
            service->get_creature_service()->get_hero_service().cast_skill("Morph into ogre", target_coord);
            break;
        }
        case sf::Keyboard::Key::B:{
                std::pair<size_t, size_t> target_coord = get_coordinates_on_map(sf::Mouse::getPosition(*info.window),
                                                                                info);
                service->get_creature_service()->get_hero_service().cast_skill("Necromastery", target_coord);
                try {
                    Creature *target = service->get_state()->get_dead_creature_by_coordinates(target_coord);
                    target->set_dead_state(false);
                    service->get_state()->add_alive_creature(*target);
                    service->get_state()->remove_dead_creature(target_coord);
                }catch (...)
                {break;}
        }
        case sf::Keyboard::Key::E:{
            std::pair<size_t ,size_t> coord = service->get_state()->get_necromant().get_coordinates();
            service->get_creature_service()->get_hero_service().interact_with_cell(coord);
            break;
        }
        default:{
            event_occured = false;
            return;
        }
    }
    event_occured = true;
}
/*!
 * @brief reacts to pressing a mouse button
 * @param button enum type representing which button was pressed
 * @param info reference to window_info type
 */
void Controller::handle_mouse_pressed(sf::Mouse::Button button, window_info& info) {
    switch(button){
        case sf::Mouse::Button::Left:{
            try{
                std::pair<size_t, size_t> target_coord = get_coordinates_on_map(sf::Mouse::getPosition(*info.window), info);
                Creature& target = *service->get_state()->get_alive_creature_by_coordinates(target_coord);
                Creature& attacking = service->get_state()->get_necromant();
                service->get_creature_service()->attack(attacking, target);
                break;
            }catch(...)
            {
                button = sf::Mouse::Button::Right;
            }
        }
        case sf::Mouse::Button::Right:{
            break;
        }
    }
}
/*!
 * @brief reacts to window resizing
 * @param event an sf::Event type reference containing info about current size of a window
 * @param info reference to window_info type
 */
void Controller::handle_window_resize(sf::Event &event, window_info& info) {
    float scale_w = info.window_width / info.rendering_width;
    float scale_h = info.window_height / info.rendering_height;
    info.window_width = event.size.width;
    info.window_height = event.size.height;
    info.rendering_width = event.size.width / scale_w;
    info.rendering_height = event.size.height / scale_h;
}

/*!
 * @brief reacts to the given type of event that happened due to user's actions
 * @param event sf::Event type object containing info about event type
 * @param info  reference to window_info type
 * @param event_occured bool type parameter that shows if an event is considered past
 */
void Controller::handle_event(sf::Event &event, window_info& info, bool& event_occured) {
    switch (event.type) {
        case sf::Event::KeyPressed:
            event_occured = true;
            handle_key_pressed(event.key.code, info, event_occured);
            break;
        case sf::Event::MouseButtonPressed:
            handle_mouse_pressed(event.mouseButton.button, info);
            event_occured = true;
            break;
        case sf::Event::Resized:
            handle_window_resize(event, info);
            event_occured = false;
            break;
        default:
            event_occured = false;
            return;
    }
}
/*!
 * @brief destructor that frees all the resources used by a program
 */
Controller::~Controller() {
    std::cout<<"deleting controller\n";
    delete service;
}