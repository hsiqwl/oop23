#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "../../Game_service/include/Game_service.h"

struct window_info{
    sf::RenderWindow* window;
    float window_width;
    float window_height;
    float rendering_width;
    float rendering_height;
    window_info(sf::RenderWindow* window, float, float, float , float);
};

class Controller{
private:
    Game_service* service;
    std::pair<size_t, size_t> get_coordinates_on_map(const sf::Vector2i& mouse_position, window_info& info);
    void handle_key_pressed(sf::Keyboard::Key key_code, window_info& info, bool& event_occured);
    void handle_mouse_pressed(sf::Mouse::Button button, window_info& info);
    void handle_window_resize(sf::Event& event, window_info& info);
    void handle_level_change();
public:
    Controller(Game_service* service);
    Game_service* get_service() {return service;};
    void handle_event(sf::Event& event, window_info& info, bool& event_occured);
    ~Controller();
};


#endif //GAME_CONTROLLER_H
