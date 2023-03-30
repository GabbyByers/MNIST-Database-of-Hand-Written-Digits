#include <iostream>
#include <fstream>
#include <vector>
#include "SFML/Graphics.hpp"
using namespace std;

#include <chrono>
#include <thread>
using namespace std::this_thread;
using namespace std::chrono;

#define _CRTDBG_MAP_ALLOC

void draw_image(sf::RenderWindow& window, int image_index, unsigned char* images)
{
	int scale = 8;
	float x_pos = 100.0f;
	float y_pos = 100.0f;
	sf::Vertex box[5] =
	{
		sf::Vertex(sf::Vector2f(0, 0), sf::Color(255, 255, 255)),
		sf::Vertex(sf::Vector2f(28 * scale, 0), sf::Color(255, 255, 255)),
		sf::Vertex(sf::Vector2f(28 * scale, 28 * scale), sf::Color(255, 255, 255)),
		sf::Vertex(sf::Vector2f(0, 28 * scale), sf::Color(255, 255, 255)),
		sf::Vertex(sf::Vector2f(0, 0), sf::Color(255, 255, 255))
	};
	sf::Vertex* pixels = new sf::Vertex[784];
	for (int row = 0; row < 28; row++)
	{
		for (int column = 0; column < 28; column++)
		{
			int index = image_index * 784 + row * 28 + column;
			unsigned char pixel = images[index];
			pixels[row * 28 + column] = sf::Vertex(sf::Vector2f(column * scale, row * scale), sf::Color(pixel, pixel, pixel));
		}
	}
	for (int i = 0; i < scale; i++)
	{
		for (int j = 0; j < scale; j++)
		{
			sf::Transform transform = sf::Transform();
			transform.translate(x_pos + i, y_pos + j);
			window.draw(pixels, 748, sf::Points, transform);
		}
	}
	sf::Transform transform = sf::Transform();
	transform.translate(x_pos, y_pos);
	window.draw(box, 5, sf::LinesStrip, transform);
	delete[] pixels;
}

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	sf::RenderWindow window(sf::VideoMode(500, 500), "MNIST Database of Hand Written Digits", sf::Style::Close);
	sf::Event event;
	char byte;

	// Load in the Digit Images
	ifstream images_file;
	images_file.open("IDX/train-images.idx3-ubyte", ios::binary);
	unsigned char* images = new unsigned char[60000 * 28 * 28];
	if (!images_file.is_open())
	{
		cout << "Oh no! I couldn't open this file! :c\n";
	}
	for (int i = 0; i < 16; i++) // Skip the first 16 bytes
	{
		images_file.read(&byte, 1);
	}
	for (int i = 0; i < 60000 * 28 * 28; i++) // Read the rest of the bytes
	{
		images_file.read(&byte, 1);
		images[i] = (unsigned char)byte;
	}
	images_file.close();

	// Load in the Digit Labels
	ifstream labels_file;
	labels_file.open("IDX/train-labels.idx1-ubyte", ios::binary);
	unsigned char* labels = new unsigned char[60000];
	if (!labels_file.is_open())
	{
		cout << "Oh no! I couldn't open this file! :c\n";
	}
	for (int i = 0; i < 8; i++) // Skip the first 8 bytes
	{
		labels_file.read(&byte, 1);
	}
	for (int i = 0; i < 60000; i++) // Read the rest of the bytes
	{
		labels_file.read(&byte, 1);
		labels[i] = (unsigned char)byte;
	}
	labels_file.close();

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

		window.clear(sf::Color(0, 0, 0));
		draw_image(window, image_index, images);
		cout << "Label: " << (unsigned)labels[image_index] << "\n";
		sleep_for(milliseconds(50));
		image_index++;
		window.display();
	}

	delete[] images;
	delete[] labels;

	return 0;
}

