#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>

int main()
{
    const int SIZE = 8000;
    int arr[SIZE];
    int N = sizeof(arr) / sizeof(arr[0]);

    // random seed
    std::srand(std::time(nullptr));

    // fills array
    for (int i = 0; i < SIZE; i++)
    {
        arr[i] = std::rand() % 1000;
    }

    sf::RenderWindow window(sf::VideoMode(800, 600), "Sorting Algorithms");

    // create rectangles
    sf::RectangleShape rectangle(sf::Vector2f(800.0f / SIZE, 0.0f));
    rectangle.setFillColor(sf::Color::Green);

    int i = 1;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        window.clear(sf::Color::Black);

        // Insertion Sort
        if (i < N)
        {
            int key = arr[i];
            int j = i - 1;
            while (j >= 0 && arr[j] > key)
            {
                arr[j + 1] = arr[j];
                j = j - 1;
            }
            arr[j + 1] = key;
            i++;
        }

        // draw the rectangles
        for (int i = 0; i < SIZE; i++)
        {
            rectangle.setSize(sf::Vector2f(800.0f / SIZE, (float)arr[i] * 0.6f));
            rectangle.setPosition((float)i * 800.0f / SIZE, 600.0f - (float)arr[i] * 0.6f);
            window.draw(rectangle);
        }

        window.display();
    }

    return 0;
}
