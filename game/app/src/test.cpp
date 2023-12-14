#include "../include/app.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode(1800, 1000), "game");
    try {
        App app;
        app.start(&window);
    }catch (std::exception& e) {
        std::cout<<"endinig game\n";
        std::cout<<e.what()<<"\n";
        std::cout << "fail!!!!\n";
    }
}