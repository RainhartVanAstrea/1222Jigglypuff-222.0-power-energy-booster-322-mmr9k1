#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "map.h"
#include "cam.h"
#include "menu.h"
#include <sstream>
//#include"choise.h"

using namespace sf;

bool isChoise = 1;
	int choiseNum = 0;

class Elder {
public:
	float x, y, w, h, dx, dy, speed = 0;
	String Filename;
	Image image;
	Texture texture;
	Sprite sprite;

	Elder(Image &image, float X, float Y, float W, float H, String name){
		w = W; h = H;
		//image.loadFromFile("images/" + Filename);
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		x = X; y = Y;
	}
};




class Player: public Elder {
public:
	int health,playScore,gold,direction,moveTimer;
	bool life;
	bool walk;
	bool upspeed;
	bool lighton;
	Player(Image &image, float X, float Y, float W, float H, String name):Elder(image,X,Y,W,H,name){
		direction=0;playScore=0;health=1;gold=0;moveTimer = 0;
		life=using namespace sf;true;
		walk=true;
		upspeed=true;
		lighton=true;
		sprite.setTextureRect(IntRect(0, 0, w, h));
	}



	void upd(float time)
	{
		switch (direction)
		{
		case 0: dx = speed; dy = 0;   break;
		case 1: dx = -speed; dy = 0;   break;
		case 2: dx = 0; dy = speed;   break;
		case 3: dx = 0; dy = -speed;   break;
		}

		x += dx*time;
		y += dy*time;

		speed = 0;
		sprite.setPosition(x,y);
        if(walk)interactionMap();
        if (health <= 0){
            life = false;
            speed = 0;
            x=12800;y=12550;}
        if (health >= 2){
            life = false;
            speed = 0;
            x=12800;y=12550; }
	}

	void interactionMap()
	{
			for (int i = y / 32; i < (y + h) / 32; i++)
			for (int j = x / 32; j<(x + w) / 32; j++)
			{
				if (TileMap[i][j] == '0')
				{
					if (dy>0)
					{
						y = i * 32 - h;
					}
					if (dy<0)
					{
						y = i * 32 + 32;
					}
					if (dx>0)
					{
						x = j * 32 - w;
					}
					if (dx < 0)
					{
						x = j * 32 + 32;
					}
				}

				if (TileMap[i][j] == 'g') {
					gold+=1;
					TileMap[i][j]=' ';
				}
				if (TileMap[i][j] == 'm') {

					if(upspeed==true && lighton==true) walk=false;TileMap[i][j]=' ';
				}
				if (TileMap[i][j] == 'l') {

					if(upspeed==true && walk==true) lighton=false;TileMap[i][j]=' ';
				}
				if (TileMap[i][j] == 'u') {

					if(walk==true && lighton==true) upspeed=false;TileMap[i][j]=' ';
				}
				if (TileMap[i][j] == 't') {
					TileMap[i][j]='n';

				}
				if (TileMap[i][j] == 'e') {
					health+=1;

                    }
				if (TileMap[i][j] == 'p') {
					TileMap[i][j]='n';

				}
				if (TileMap[i][j] == 'n') {
					health-=1;
				}

			}
	}


	float getplayercoordinateX(){
		return x;
	}
	float getplayercoordinateY(){
		return y;
	}
};


class Enemy :public Elder{
public:
	Enemy(Image &image, float X, float Y, float W, float H, String name):Elder(image,X,Y,W,H,name){
			sprite.setTextureRect(IntRect(0, 0, w, h));
			dx = 0.1;
	}

	void CollisionWithMap(float Dx, float Dy)
	{
		for (int i = y / 32; i < (y + h) / 32; i++)
		for (int j = x / 32; j<(x + w) / 32; j++)
		{
			if (TileMap[i][j] == '0')
			{
				//if (Dy>0){ y = i * 32 - h; }
				//if (Dy<0){ y = i * 32 + 32; }
				if (Dx>0){ x = j * 32 - w; dx = -0.1;  }
				if (Dx<0){ x = j * 32 + 32; dx = 0.1;  }
			}
		}
	}

	void update(float time)
	{
			CollisionWithMap(dx, 0);
			x += dx*time;
			sprite.setPosition(x + w / 2, y + h / 2); //задаем позицию спрайта в место его центра
		}
};

void choise(RenderWindow & window) {
	Texture gamer1, gamer2, menuBackground;
	gamer1.loadFromFile("images/gamer_model.png");
	gamer2.loadFromFile("images/2.png");
	menuBackground.loadFromFile("images/menu2.png");
	Sprite gamer1_1(gamer1), gamer2_2(gamer2), menuBg(menuBackground);
	gamer1_1.setScale(2,2);
	gamer2_2.setScale(2,2);
	gamer1_1.setPosition(200, 300);
	gamer2_2.setPosition(400, 300);
	menuBg.setPosition(0, 0);

	while (isChoise)
	{
		choiseNum = 0;
		window.clear(Color(242, 131, 236));

		if (IntRect(200, 300, 32, 32).contains(Mouse::getPosition(window))) { gamer1_1.setColor(Color::Blue); choiseNum = 1; }
		if (IntRect(400, 300, 32, 32).contains(Mouse::getPosition(window))) { gamer2_2.setColor(Color::Blue); choiseNum = 2; }
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (choiseNum == 1) isChoise = false;
			if (choiseNum == 2) isChoise = false;

		}

		window.draw(menuBg);
		window.draw(gamer1_1);
		window.draw(gamer2_2);

		window.display();
	}
}



bool start(){
    RenderWindow window(VideoMode(600, 600), "Jigglypuff");

    SoundBuffer shootBuffer;
    shootBuffer.loadFromFile("audio/music.ogg");
    Sound shoot(shootBuffer);
    shoot.play();
    choise(window);
	menu(window);
    window.setFramerateLimit(60);

    Font font;
    font.loadFromFile("CyrilicOld.ttf");

    Text text("",font,50);
    text.setColor(Color::Red);
	text.setStyle(Text::Bold);

	Text death("",font,50);
    death.setColor(Color::Red);
	death.setStyle(Text::Bold);

	Text win("",font,50);
    win.setColor(Color::Red);
	win.setStyle(Text::Bold);


    Image maptexture;
	maptexture.loadFromFile("images/map.png");
	Texture map;
	map.loadFromImage(maptexture);
	Sprite spritemap;
	spritemap.setTexture(map);


	 Image deathshadow;
	deathshadow.loadFromFile("images/death.png");
	Texture deathsh;
	deathsh.loadFromImage(deathshadow);
	Sprite s_death;
	s_death.setTexture(deathsh);

    Image heroImage;
    Image enemyImage;
	if(choiseNum==1)heroImage.loadFromFile("images/gamer_model.png");
	if(choiseNum==2)heroImage.loadFromFile("images/2.png");
    enemyImage.loadFromFile("images/enemy.png");

    Player gamer (heroImage, 1258, 1255, 16.0, 16.0, "gamer");
    Enemy enemy (enemyImage, 600, 32, 16.0, 16.0, "enemy");

	Image light;
	light.loadFromFile("images/light2.png");
	Texture lightgame;
	lightgame.loadFromImage(light);
	Sprite s_light;
	s_light.setTexture(lightgame);


	Clock clock;

    while (window.isOpen())
    {

		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 700;
        Event e;
        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed)
                window.close();
        }
        if(gamer.walk==false)gamer.moveTimer += time;if (gamer.moveTimer>10000){gamer.moveTimer=0; gamer.walk=true; }
        if(gamer.lighton==false)gamer.moveTimer += time;if (gamer.moveTimer>10000){  gamer.moveTimer=0;gamer.lighton=true;}
        if(gamer.upspeed==false)gamer.moveTimer += time;if (gamer.moveTimer>10000){  gamer.moveTimer=0;gamer.upspeed=true;}
        if (Keyboard::isKeyPressed(Keyboard::Tab)) { return true; }
        if (Keyboard::isKeyPressed(Keyboard::Escape)) { return false; }
if (gamer.life){
     	if ((Keyboard::isKeyPressed(Keyboard::Left) )) {
            gamer.direction = 1; if(gamer.upspeed==true)gamer.speed = 0.1;if (gamer.upspeed==false) gamer.speed=0.3;
            gamer.sprite.setTextureRect(IntRect(0, 0, 16, 16));
            getcoordinateforview(gamer.getplayercoordinateX(), gamer.getplayercoordinateY());
             if(gamer.lighton==true) s_light.setPosition(gamer.getplayercoordinateX()-1250, gamer.getplayercoordinateY()-1250); if(gamer.lighton==false) s_light.setPosition(gamer.getplayercoordinateX()-12500, gamer.getplayercoordinateY()-12500);
            }
        if ((Keyboard::isKeyPressed(Keyboard::Right) )) {
            gamer.direction = 0; if(gamer.upspeed==true)gamer.speed = 0.1;if (gamer.upspeed==false)  gamer.speed=0.3;
            gamer.sprite.setTextureRect(IntRect(0, 0, 16, 16));
            getcoordinateforview(gamer.getplayercoordinateX(), gamer.getplayercoordinateY());
             if(gamer.lighton==true) s_light.setPosition(gamer.getplayercoordinateX()-1250, gamer.getplayercoordinateY()-1250); if(gamer.lighton==false) s_light.setPosition(gamer.getplayercoordinateX()-12500, gamer.getplayercoordinateY()-12500);
        }
        if ((Keyboard::isKeyPressed(Keyboard::Up) )) {
            gamer.direction = 3; if(gamer.upspeed==true)gamer.speed = 0.1;if (gamer.upspeed==false)  gamer.speed=0.3;
            gamer.sprite.setTextureRect(IntRect(0, 0, 16, 16));
            getcoordinateforview(gamer.getplayercoordinateX(), gamer.getplayercoordinateY());
            if(gamer.lighton==true) s_light.setPosition(gamer.getplayercoordinateX()-1250, gamer.getplayercoordinateY()-1250); if(gamer.lighton==false) s_light.setPosition(gamer.getplayercoordinateX()-12500, gamer.getplayercoordinateY()-12500);
            }
        if ((Keyboard::isKeyPressed(Keyboard::Down) )) {
            gamer.direction= 2; if(gamer.upspeed==true)gamer.speed = 0.1;if (gamer.upspeed==false)  gamer.speed=0.3;
            gamer.sprite.setTextureRect(IntRect(0, 0, 16, 16));
            getcoordinateforview(gamer.getplayercoordinateX(), gamer.getplayercoordinateY());
             if(gamer.lighton==true) s_light.setPosition(gamer.getplayercoordinateX()-1250, gamer.getplayercoordinateY()-1250); if(gamer.lighton==false) s_light.setPosition(gamer.getplayercoordinateX()-12500, gamer.getplayercoordinateY()-12500);
            }
}

		gamer.upd(time);
		window.setView(view);
        enemy.update(time);

    window.clear(Color(84,60,37,255));
    for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
		{
			if (TileMap[i][j] == ' ')  spritemap.setTextureRect(IntRect(0, 0, 32, 32));
			if (TileMap[i][j] == 'g')  spritemap.setTextureRect(IntRect(32, 0, 32, 32));
			if ((TileMap[i][j] == '0')) spritemap.setTextureRect(IntRect(64, 0, 32, 32));
            if ((TileMap[i][j] == 'e')) spritemap.setTextureRect(IntRect(96, 0, 32, 32));
            if ((TileMap[i][j] == 't')) spritemap.setTextureRect(IntRect(0, 0, 32, 32));
            if ((TileMap[i][j] == 'p')) spritemap.setTextureRect(IntRect(32, 0, 32, 32));
            if ((TileMap[i][j] == 'n')) spritemap.setTextureRect(IntRect(128, 0, 32, 32));
            if ((TileMap[i][j] == 'm')) spritemap.setTextureRect(IntRect(0, 0, 32, 32));
            if ((TileMap[i][j] == 'r')) spritemap.setTextureRect(IntRect(0, 0, 32, 32));
            if ((TileMap[i][j] == 'l')) spritemap.setTextureRect(IntRect(0, 0, 32, 32));
            if ((TileMap[i][j] == 'u')) spritemap.setTextureRect(IntRect(0, 0, 32, 32));
			spritemap.setPosition(j * 32, i * 32);

			window.draw(spritemap);
		}




        window.draw(gamer.sprite);
        window.draw(enemy.sprite);
        window.draw(s_light);
        std::ostringstream goldString;
		goldString << gamer.gold;
		text.setString("Собрано монет:" + goldString.str());
		text.setPosition(view.getCenter().x - 500, view.getCenter().y - 480);
		window.draw(text);
		if(!gamer.life){
            if(gamer.health>=2){win.setString("Вы победили!");
            win.setPosition(view.getCenter().x -150 , view.getCenter().y -50 );
            window.draw(win);

		}
		}
		if(!gamer.life){
            if(gamer.health<=0){death.setString("Вы погибли!");
            s_death.setPosition(view.getCenter().x-600, view.getCenter().y-600);
            death.setPosition(view.getCenter().x -150, view.getCenter().y -50 );
            window.draw(s_death);
            window.draw(death);

		}}



        window.display();

    }


return 0;
}





void Run(){
	if (start()) {
            Run();
}
}

int main()
{
    Run();
	return 0;
}
