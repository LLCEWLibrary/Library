#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "Project1.h"



int main()
{

	DataBase database;

	for (int i = 0; i < 100; ++i) {
		Book book;

		book.author = "EMCJava";
		book.date = i * 100;
		book.homeland = "LLLCEW";
		book.ID = i;
		book.name = "EMCJava" + to_string(i);

		database.addBook(book);
	}

	for (int i = 0; i < 100; ++i) {
		printBook(database.getBook(i));
	}

	// Create the main window
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");
	// Create a graphical text to display
	sf::Font font;
	if (!font.loadFromFile("Xanadu.ttf"))
		return EXIT_FAILURE;
	sf::Text text("Hello SFML", font, 50);


	////

	std::string str, texta;

	////


	// Start the game loop
	while (window.isOpen())
	{
		// Process events
		sf::Event event;
		while (window.pollEvent(event))
		{
			// Close window: exit
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::TextEntered)
			{
				// Handle ASCII characters only
				if (event.text.unicode < 128)
				{
					if (event.text.unicode == 13) {
						database.search(texta);
						str = "";
						Book book = database.getBook(database.result.at(0).ID);

						texta = book.name;
					}
					else if (event.text.unicode == 8) {
						if (str.size() > 0)
							str.resize(str.size() - 1);
						texta = str;

					}
					else {
						str += static_cast<char>(event.text.unicode);
						texta = str;
					}

				}
			}
		}
		// Clear screen
		window.clear();
		// Draw the string
		text.setString(texta);
		window.draw(text);
		// Update the window
		window.display();
	}
	return EXIT_SUCCESS;
}
