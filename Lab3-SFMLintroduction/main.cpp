#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>  // Para rand()
#include <ctime>    // Para time()

int main() {
    std::srand(static_cast<unsigned int>(std::time(nullptr))); // Seed do random

    const int window_width = 800;
    const int window_height = 600;

    sf::RenderWindow window(sf::VideoMode(window_width, window_height), "My window");

    // Shapes
    sf::CircleShape circle(100.0);
    circle.setPosition(100.0, 300.0);
    circle.setFillColor(sf::Color(100, 250, 50));

    sf::RectangleShape rectangle(sf::Vector2f(120.0, 60.0));
    rectangle.setPosition(500.0, 400.0);
    rectangle.setFillColor(sf::Color(100, 50, 250));

    sf::ConvexShape triangle;
    triangle.setPointCount(3);
    triangle.setPoint(0, sf::Vector2f(0.0, 0.0));
    triangle.setPoint(1, sf::Vector2f(0.0, 100.0));
    triangle.setPoint(2, sf::Vector2f(140.0, 40.0));
    triangle.setOutlineColor(sf::Color::Red);
    triangle.setOutlineThickness(5);
    triangle.setPosition(600.0, 100.0);

    // Velocities
    float rectangle_velocity_x = 50.f;
    float rectangle_velocity_y = 150.f;
    float rectangle_angular_velocity = 10.f;

    sf::Clock clock;

    while (window.isOpen()) {
        sf::Time elapsed = clock.restart();
        float dt = elapsed.asSeconds();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Move and rotate
        rectangle.move(rectangle_velocity_x * dt, rectangle_velocity_y * dt);
        rectangle.rotate(rectangle_angular_velocity * dt);

        // Get bounds
        sf::FloatRect bounds = rectangle.getGlobalBounds();

        // Check for bounce and change color
        bool bounced = false;

        if (bounds.left <= 0 || bounds.left + bounds.width >= window_width) {
            rectangle_velocity_x = -rectangle_velocity_x;
            bounced = true;
        }

        if (bounds.top <= 0 || bounds.top + bounds.height >= window_height) {
            rectangle_velocity_y = -rectangle_velocity_y;
            bounced = true;
        }

        if (bounced) {
            sf::Color random_color(rand() % 256, rand() % 256, rand() % 256);
            rectangle.setFillColor(random_color);
        }

        // Draw
        window.clear(sf::Color::Black);
        window.draw(circle);
        window.draw(rectangle);
        window.draw(triangle);
        window.display();
    }

    return 0;
}

