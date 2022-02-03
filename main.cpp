#include "Map.h"

void menu(RenderWindow& window); // главное меню
bool game(RenderWindow& window); // игра
bool printResult(const char* value, RenderWindow& window); // печать итога

int main()
{

	RenderWindow window(VideoMode(840,600), "Tanks_2D");
	bool repeate = true;
	while (repeate) {
		repeate = false;
		menu(window);
		repeate = game(window);
	}
	

	return 0;
}

// главное меню
void menu(RenderWindow& window) {
	Texture menuTexture1, menuTexture2, menuTexture3, aboutTexture, menuBackground;
	menuTexture1.loadFromFile("images/1.png");
	menuTexture2.loadFromFile("images/2.png");
	menuTexture3.loadFromFile("images/3.png");
	aboutTexture.loadFromFile("images/about.png");
	Sprite menu1(menuTexture1), menu2(menuTexture2), menu3(menuTexture3), about(aboutTexture);
	bool isMenu = 1;
	int menuNum = 0;
	menu1.setPosition(355, 166);
	menu2.setPosition(361, 279);
	menu3.setPosition(356, 380);

	while (isMenu)
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed) {
				window.close();
			}
		}

		menu1.setColor(Color(129, 181, 221));
		menu2.setColor(Color(129, 181, 221));
		menu3.setColor(Color(129, 181, 221));
		menuNum = 0;
		window.clear(Color(129, 181, 221));

		if (IntRect(355, 166, 141, 40).contains(Mouse::getPosition(window))) { menu1.setColor(Color::Blue); menuNum = 1; }
		if (IntRect(361, 279, 112, 30).contains(Mouse::getPosition(window))) { menu2.setColor(Color::Blue); menuNum = 2; }
		if (IntRect(356, 380, 126, 40).contains(Mouse::getPosition(window))) { menu3.setColor(Color::Blue); menuNum = 3; }

		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (menuNum == 1) isMenu = false;
			if (menuNum == 2) { window.draw(about); window.display(); while (!Keyboard::isKeyPressed(Keyboard::Escape)); }
			if (menuNum == 3) { window.close(); isMenu = false; }

		}

		window.draw(menu1);
		window.draw(menu2);
		window.draw(menu3);

		window.display();
	}
}

// игра
bool game(RenderWindow& window) {
	Hero hero("hero.png", 40, 40, 61, 500);
	Enemy enemy("enemy.png", 40, 40, 740, 61);
	Map map("map.png");
	while (window.isOpen())
	{
		window.clear(Color::White);

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed) {
				window.close();
			}
		}

		if (map.getPresentValueTimer() > 0) {
			if (enemy.getAmountOfHealth() <= 0) {
				if (printResult("You winner!", window)) {
					return true;
				}
			}
			else if (hero.getAmountOfHealth() <= 0) {
				if (printResult("You lose!", window)) {
					return true;
				}
			}
			else {
				map.draw(window);
				hero.update(map, enemy, window);
				enemy.update(map, hero, window);
			}
		}
		else if (map.getPresentValueTimer() <= 0) {
			if (printResult("There is no winner!", window)) {
				return true;
			}
		}
		window.display();
	}
}

bool printResult(const char* value, RenderWindow& window) {
	window.clear(Color(129, 181, 221));
	Font font;
	font.loadFromFile("other/Arial.ttf");
	Text text("", font, 80);
	text.setOutlineColor(Color::Black);
	text.setFillColor(Color::Black);
	text.setStyle(Text::Bold);
	text.setPosition(100, 175);
	std::ostringstream textResult;
	textResult << value;
	text.setString(textResult.str());
	window.draw(text);
	Texture texture;
	texture.loadFromFile("images/ok.png");
	Sprite sprite(texture);
	sprite.setPosition(640, 555);
	sprite.setColor(Color(129, 181, 221));
	int menuNum = 0;
	if (IntRect(640, 555, 55, 32).contains(Mouse::getPosition(window))) { sprite.setColor(Color::Blue); menuNum = 1; }
	window.draw(sprite);
	if (Mouse::isButtonPressed(Mouse::Left) && menuNum == 1) {
		return true;
	}
	else {
		return false;
	}
}