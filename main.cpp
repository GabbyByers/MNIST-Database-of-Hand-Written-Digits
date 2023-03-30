#include <iostream>
#include <fstream>
#include <vector>
#include "SFML/Graphics.hpp"

using namespace std;
#define _CRTDBG_MAP_ALLOC

void draw_image(sf::RenderWindow& window, int image_index, unsigned char* images)
{
	sf::Vertex box[5] =
	{
		sf::Vertex(sf::Vector2f(0, 0), sf::Color(255, 255, 255)),
		sf::Vertex(sf::Vector2f(28, 0), sf::Color(255, 255, 255)),
		sf::Vertex(sf::Vector2f(28, 28), sf::Color(255, 255, 255)),
		sf::Vertex(sf::Vector2f(0, 28), sf::Color(255, 255, 255)),
		sf::Vertex(sf::Vector2f(0, 0), sf::Color(255, 255, 255))
	};
	sf::Vertex* pixels = new sf::Vertex[784];
	for (int row = 0; row < 28; row++)
	{
		for (int column = 0; column < 28; column++)
		{
			int index = image_index * 784 + row * 28 + column;
			unsigned char pixel = images[index];
			pixels[row * 28  + column] = sf::Vertex(sf::Vector2f(column, row), sf::Color(pixel, pixel, pixel));
		}
	}
	sf::Transform transform = sf::Transform();
	transform.translate(100.0f, 100.0f);
	window.draw(pixels, 748, sf::Points, transform);
	window.draw(box, 5, sf::LinesStrip, transform);
	delete[] pixels;
}

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	sf::RenderWindow window(sf::VideoMode(500, 500), "Hello SFML", sf::Style::Close);
	sf::Event event;

	ifstream file;
	file.open("IDX/test-images.idx3-ubyte", ios::binary);

	if (!file.is_open())
	{
		cout << "Oh no! I couldn't open this file! :c\n";
	}

	unsigned char* bytes = new unsigned char[7840000];
	char byte;
	
	// Throw away first 16 bytes
	for (int i = 0; i < 16; i++)
	{
		file.read(&byte, 1);
	}

	// Read the rest of the file
	for (int i = 0; i < 7840000; i++)
	{
		file.read(&byte, 1);
		bytes[i] = (unsigned char)byte;
	}

	int image_index = 0;
	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		cout << "Image index: " << image_index << "\n";

		window.clear(sf::Color(0, 0, 0));
		draw_image(window, image_index++, bytes);
		window.display();
	}

	return 0;
}