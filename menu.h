#include <SFML\Graphics.hpp>

using namespace sf;

void menu(RenderWindow & window) {
	Texture menu1, menu2, menu3, about, menuBackground;
	menu1.loadFromFile("images/newgame.png");
	menu2.loadFromFile("images/about1.png");
	menu3.loadFromFile("images/exit.png");
	about.loadFromFile("images/about.png");
	menuBackground.loadFromFile("images/menu2.png");
	Sprite menu1_1(menu1), menu2_2(menu2), menu3_3(menu3), about_4(about), menuBg(menuBackground);
	bool isMenu = 1;
	int menuNum = 0;
	menu1_1.setPosition(20, 30);
	menu2_2.setPosition(20, 90);
	menu3_3.setPosition(20, 550);
	menuBg.setPosition(0, 0);

	while (isMenu)
	{
		menu1_1.setColor(Color::White);
		menu2_2.setColor(Color::White);
		menu3_3.setColor(Color::White);
		menuNum = 0;
		window.clear(Color(242, 131, 236));

		if (IntRect(20, 30, 300, 50).contains(Mouse::getPosition(window))) { menu1_1.setColor(Color::Blue); menuNum = 1; }
		if (IntRect(20, 90, 300, 50).contains(Mouse::getPosition(window))) { menu2_2.setColor(Color::Blue); menuNum = 2; }
		if (IntRect(20, 550, 300, 50).contains(Mouse::getPosition(window))) { menu3_3.setColor(Color::Blue); menuNum = 3; }

		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (menuNum == 1) isMenu = false;
			if (menuNum == 2) { window.draw(about_4); window.display(); while (!Keyboard::isKeyPressed(Keyboard::Escape)); }
			if (menuNum == 3)  { window.close(); isMenu = false; }

		}

		window.draw(menuBg);
		window.draw(menu1_1);
		window.draw(menu2_2);
		window.draw(menu3_3);

		window.display();
	}
}
