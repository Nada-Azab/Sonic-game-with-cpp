#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<ctime>
#include<SFML/Audio.hpp>
#include<iostream>
#include<fstream>
#include <chrono>
#include <thread>


    using namespace std::this_thread; // sleep_for, sleep_until
    using namespace std::chrono; // nanoseconds, system_clock, seconds


#define X 36
#define Y 41
#define WIDTH 1280
#define HEIGHT 720
#define sizeENEMIES 3

using namespace sf;
using namespace std;

struct enemies
{
	Texture enemytexture;
	Sprite enemy;
	bool isvisible = true;
}; enemies enemy[sizeENEMIES];

string text_username;
string arr[10] = { "--" };


void SONIC_ANIMATION(RenderWindow& window, Sprite& sonic, View& camera);
void GameWorld(RenderWindow& window, Texture Castle, Texture Flag, Texture Thorns, Texture Smallblock, Texture Halfcastle, Texture Mirrorcliff, Texture Cliff, Texture Block, Texture Background, Texture Ground, Sprite& win, Sprite& sonic);
void UI(RenderWindow& window, Text& text, Text& text1, Text& text05, Sprite& mouse, RectangleShape& background,Text text06);
void Intersections(RenderWindow& window, View& camera, int& t_rings, ofstream& input, Sprite& gameover, Sprite& sonic,/* Sprite spritesthorns[2], Sprite& halfcastle,*/ Sprite coin[], Sprite coin1[], Sprite coin2[], Sound& sound, enemies enemy[], Text& text0, Sound& soundout, Text& text03, int& SCORE, int& health, Text& text04, Sprite& win);
void CameraView(RenderWindow& window, View& camera, Sprite& sonic, Text& text0, Text& text02, Text& text03, Text& text04, Sprite& heart0);
void RESUME(RenderWindow& window, Text& text, Text& text1, Sprite& mouse, RectangleShape& background);
void jump(RenderWindow& window, Sprite& sonic);
void drow_coin(RenderWindow& window, Sprite coin[], Sprite coin1[], Sprite coin2[], Sprite coin3[], Sprite coin4[], Sprite coin5[], Sprite coin6[], Sprite& sonic, Texture Cointure);
void enemiesload_draw(RenderWindow& window, enemies enemy[], int& enemyanmationcounter);
enemies enemies_move(RenderWindow& window, enemies enemy[], float Deltatime, Clock& clock, Sprite coin[]);
void calculatetime(int&, int&, Clock&);
void How_we_want_Time(int, int, Text& text2, RenderWindow&);
void END(RenderWindow& window, Text& LEVEL2, Text& EXIT);
void Game_Over(RenderWindow& window, Text& text, Text& text1, Sprite& mouse, RectangleShape& backgroundForUI);
void GameWorld2(RenderWindow& window, Texture Castle, Texture Flag, Texture Block2, Texture Halfcastle, Texture Mirrorcliff, Texture Cliff, Texture Block, Texture Background, Texture Ground, Sprite& win, Sprite& sonic);	
void drow_coin2(RenderWindow& window, Sprite coin[], Sprite coin1[], Sprite coin4[], Sprite& sonic, Texture Cointure);
void user_name(RenderWindow& window, Font& font, string&, Event& event);
void cridit(RenderWindow& window, Font& font, string& input_uname);
//void collision_enemies_and_coin(RenderWindow& window, Sprite& sonic, Sprite coin[], Sound& sound, enemies enemy[], Text& text, Sound& soundout, Text& text3, int& score);


int score = 0, time1 = 10, time2 = 0, time001 = 0, timer002, sonic_lives = 0, SCORE = 0;
int x = 0, y = 0;
int click = 0, health = 3;
struct pos {
	int x, y;
}sonicPos;

bool rs = false;
static const int SONIC_Y_BUTTOM = HEIGHT - 60;
bool game = true;
float frame = 0.f;
float frameSpeed = 0.4f;
const int changeCount = 5;
const int gravity = 5;
bool isJumping = false;
bool isBottom = true;


bool bcoin[4] = {};
bool bcoin1[4] = {};
bool bcoin2[3] = {};
bool benemy[3] = {};
int rings = 0, coinanmationcounter = 0, enemyanmationcounter = 0, enemyanmationcounter1 = 0;

int main(void) {


	RenderWindow window(VideoMode(WIDTH, HEIGHT), "Sonic");
	window.setFramerateLimit(30);
	// Camera view
	View camera;
	camera.setCenter(Vector2f(350.f, 200.f));
	camera.setSize(Vector2f(800.f, 400.f));

	// SONIC
	Texture sonicF;
	sonicF.loadFromFile("Tex/SonicAnimation.png");
	Sprite sonic(sonicF);
	// this to make photo subRectangles
	sonic.setTextureRect(IntRect(x * X, Y * 41, X, Y));



	// font and texts
	Font font;
	font.loadFromFile("Font/font.ttf");
	std::string exit = "EXIT", play = "PLAY", resume = "RESUME", highscore = "HIGH SCORE";
	Text text;
	text.setFont(font);
	text.setCharacterSize(24);
	text.setFillColor(Color::White);
	text.setStyle(Text::Bold);
	text.setString(play);

	Text text1;
	text1.setFont(font);
	text1.setCharacterSize(24);
	text1.setFillColor(Color::White);
	text1.setStyle(Text::Bold);
	text1.setString(exit);

	Text text05;
	text05.setFont(font);
	text05.setCharacterSize(24);
	text05.setFillColor(Color::White);
	text05.setStyle(Text::Bold);
	text05.setString("CRIDIT");


	Text text06;
	text06.setFont(font);
	text06.setCharacterSize(24);
	text06.setFillColor(Color::White);
	text06.setStyle(Text::Bold);
	text06.setString("CRIDIT");


	Text text2;
	text2.setFont(font);
	text2.setCharacterSize(24);
	text2.setFillColor(Color::White);
	text2.setStyle(Text::Bold);
	text2.setString(resume);

	text.setPosition(((float)window.getSize().x / 2) - 100, 100.f);
	text1.setPosition(((float)window.getSize().x / 2) - 100, 450.f);
	text2.setPosition(((float)camera.getCenter().x / 2), 150.f);
	text06.setPosition(((float)window.getSize().x / 2) - 120, 200.f);
	text05.setPosition(((float)window.getSize().x / 2) - 130, 250.f);

	sonicPos.x = (int)sonic.getGlobalBounds().width;
	sonicPos.y = SONIC_Y_BUTTOM;
	// the mouse 
	Texture Mouse;
	Mouse.loadFromFile("Tex/mouse.png");
	Sprite mouse(Mouse);
	mouse.setScale(0.08f, 0.08f);

	// this to set postitions of PLAY and EXIT
	int Ylimite = window.getSize().y;
	int select = 0;
	// background for UI
	RectangleShape backgroundForUI(Vector2f((float)window.getSize().x, (float)window.getSize().y));
	Texture back;
	back.loadFromFile("tex/ui.jpg");
	backgroundForUI.setTexture(&back);

	// background for End 

	Texture backEnd;
	RectangleShape backgroundForEnd(Vector2f(camera.getCenter().x, camera.getCenter().y));
	backEnd.loadFromFile("Tex/background.jfif");
	backgroundForEnd.setTexture(&backEnd);


	//Background for GAME
	Texture Background;
	Background.loadFromFile("tex/background.JPEG");

	//ground
	Texture Ground;
	Ground.loadFromFile("Tex/ground.PNG");
	
	

	//Block 
	Texture Block;
	Block.loadFromFile("TEX/block.PNG");
	

	//smallBlock 
	Texture smallblock;
	smallblock.loadFromFile("TEX/smallblock.png");
	
	//cliff
	Texture Cliff;
	Cliff.loadFromFile("tex/cliff.PNG");
	
	

	//mirrorcliff
	Texture Mirrorcliff;
	Mirrorcliff.loadFromFile("tex/mirrorcliff.PNG");
	
	//Background
	Texture Background2;
	Background2.loadFromFile("tex/background2.png");
	//flag
	Texture Flag2;
	Flag2.loadFromFile("tex/flag2.PNG");
	//Castle
	Texture Castle2;
	Castle2.loadFromFile("tex/castle2.PNG");
	//halfCastle
	Texture Halfcastle2;
	Halfcastle2.loadFromFile("tex/halfcastle2.PNG");


	//Thorns
	Texture Thorns;
	Thorns.loadFromFile("tex/thorns1.PNG");

	//Flag
	Texture Flag;
	Flag.loadFromFile("tex/flag1.PNG");
	
	
	//Castle
	Texture Castle;
	Castle.loadFromFile("tex/castle1.PNG");
	
	
	//halfCastle
	Texture Halfcastle;
	Halfcastle.loadFromFile("tex/halfcastle.PNG");
	
	
	//win
	Texture Win;
	Win.loadFromFile("win.PNG");
	Sprite win;
	win.setTexture(Win);
	win.setScale(1.3, 1);
	win.setPosition(4380, 0);

	//end
	Texture winEnd;
	winEnd.loadFromFile("Tex/winEnd.jpg");
	Sprite WinEnd;
	WinEnd.setTexture(winEnd);
	//WinEnd.setPosition(100, 50);
	//WinEnd.setScale(1, 1);




	sonic.setOrigin(sonic.getGlobalBounds().width, -300);


	int Score = 0;
	int timer = 0, t_rings = 0;
	float time = 0;

	Clock  Time_clock, enemydeltatime, enemiesclock;
	float DeltaTime = 0;
	int minutes = 0;

	Texture Cointure;
	Cointure.loadFromFile("Tex/coins1.PNG");
	Sprite coin[4];
	Sprite coin1[4];
	Sprite coin2[4];
	Sprite coin3[4];
	Sprite coin4[4];
	Sprite coin5[4];
	Sprite coin6[4];
	
	for (size_t i = 0; i < 4; i++) {
		coin[i].setPosition(1230 + (i * 30), 150);
		coin[i].setTexture(Cointure);
		coin[i].setScale(0.2, 0.2);
		if (sonic.getGlobalBounds().intersects(coin[i].getGlobalBounds()))
			coin[i].setScale(0, 0);
	}

	Font font0;
	font0.loadFromFile("Tex/PlayfairDisplay-Bold.ttf");
	Text text0;
	text0.setFont(font0);
	text0.setString("Rings : " + to_string(rings));
	text0.setFillColor(Color(75, 67, 75, 255));
	text0.setPosition(10, 10);
	text0.setScale(.75, .75);
	text0.setCharacterSize(32);



	Text text02;
	text02.setFont(font0);
	text02.setString("Time : " + to_string(time));
	text02.setFillColor(Color(70, 67, 70, 255));
	text02.setPosition(10, 50);
	text02.setScale(.75, .75);
	text02.setCharacterSize(32);

	Text text03;
	text03.setFont(font0);
	text03.setString("Score : " + to_string(Score));
	text03.setFillColor(Color(70, 70, 75, 245));
	text03.setPosition(10, 90);
	text03.setScale(.75, .75);
	text03.setCharacterSize(32);

	SoundBuffer soundb;
	soundb.loadFromFile("Tex/Ringsound (2).ogg");
	Sound sound;
	sound.setBuffer(soundb);

	SoundBuffer sound_out;
	sound_out.loadFromFile("Tex/ring_out.OGG");
	Sound soundout;
	soundout.setBuffer(sound_out);

	SoundBuffer sound_ground;
	sound_ground.loadFromFile("Tex/con_out1.ogg");
	Sound soundground;
	soundground.setBuffer(sound_ground);
	soundground.play();

	Texture Heart;
	Heart.loadFromFile("Tex/nheart.png");
	Sprite heart0;
	heart0.setPosition(0, 380);
	heart0.setTexture(Heart);
	heart0.setScale(0.05, 0.05);

	Font font01;
	font01.loadFromFile("Tex/PlayfairDisplay-Regular.ttf");
	Text text04;
	text04.setFont(font01);
	text04.setString("x " + to_string(health));
	text04.setFillColor(Color(75, 67, 75, 255));
	text04.setPosition(25, 370);
	text04.setScale(.7, .7);
	text04.setCharacterSize(32);

	enemy[2].enemy.setPosition(0, 100);
	enemy[0].enemy.setPosition(385, 250);
	enemy[1].enemy.setPosition(enemy[2].enemy.getPosition().x, enemy[2].enemy.getPosition().y + 20);

	Texture game_over;
	game_over.loadFromFile("Tex/gameover1.png");
	Sprite gameover;
	gameover.setScale(0, 0);
	gameover.setTexture(game_over);


	Text exitForEnd;
	exitForEnd.setFont(font);
	exitForEnd.setCharacterSize(24);
	exitForEnd.setFillColor(Color::White);
	exitForEnd.setStyle(Text::Bold);
	exitForEnd.setString("EXIT");


	Text LEVEL2;
	LEVEL2.setFont(font);
	LEVEL2.setCharacterSize(24);
	LEVEL2.setFillColor(Color::White);
	LEVEL2.setStyle(Text::Bold);
	LEVEL2.setString("LEVEL2");



	exitForEnd.setPosition((float)camera.getCenter().x / 2, (float)camera.getCenter().x / 2);
	LEVEL2.setPosition((float)camera.getCenter().x / 2, (float)camera.getCenter().x / 3);
	// this to set postitions of PLAY and EXIT
	//int Ylimite = window.getSize().y;
	//int select = 0;
	ofstream input;


	while (window.isOpen()) {
		Event event;

		int seconds = Time_clock.getElapsedTime().asSeconds();
		DeltaTime = enemydeltatime.restart().asSeconds();
		enemies emove = enemies_move(window, enemy, DeltaTime, enemiesclock, coin);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			cout << "X" << sf::Mouse::getPosition(window).x << endl;


			cout << "Y" << sf::Mouse::getPosition(window).y << endl << "***" << endl;
		}


		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
			if (event.KeyPressed && event.key.code == Keyboard::Escape)
				window.close();
		}
		//UPDATE 
		// this is the main game
		// DRAW
		window.clear(Color::White);
		//if (sonic.getGlobalBounds().intersects(halfcastle.getGlobalBounds())) {
		//	//click = 2;
		//	game = false;

		//}
		if (game == false) {
			window.draw(win);
			cout << "Rawan";
		}
		if (click == 0)
			UI(window, text1, text, text05, mouse, backgroundForUI,text06);
		if (click == 1 && !rs) {

			SONIC_ANIMATION(window, sonic, camera);
			GameWorld(window, Castle, Flag, Thorns, smallblock, Halfcastle, Mirrorcliff, Cliff, Block, Background, Ground, win, sonic);
			
			enemiesload_draw(window, enemy, enemyanmationcounter);
			/*if (enemyanmationcounter1 == 1) {
				enemy[1].enemy.setPosition(enemy[2].enemy.getPosition().x, enemy[2].enemy.getPosition().y + 20);
			}*/
			enemies_move(window, enemy, DeltaTime, enemiesclock, coin);

			Intersections(window, camera, t_rings, input, gameover, sonic,/* spritesthorns, halfcastle,*/ coin, coin1, coin2, sound, enemy, text0, soundout, text03, SCORE, health, text04, win);
			jump(window, sonic);
			CameraView(window, camera, sonic, text0, text02, text03, text04, heart0);
			window.setView(camera);
			if (game == true)
			{
				window.draw(sonic);
				window.draw(text0);
				window.draw(text02);
				window.draw(text03);
				window.draw(text04);
				
				window.draw(heart0);
				window.draw(gameover);
			}
			/*for (int i = 0; i < 5; i++) {
				if (sonic.getGlobalBounds().intersects(spritescactus[i].getGlobalBounds()))
					spritesheart[i].setScale(0, 0);
			}
			for (int i = 0; i < 3; i++)
				window.draw(spritesheart[i]);*/
			drow_coin(window, coin, coin1, coin2, coin3, coin4, coin5, coin6, sonic, Cointure);
			calculatetime(seconds, minutes, Time_clock);
			How_we_want_Time(seconds, minutes, text02, window);
			if (Keyboard::isKeyPressed(Keyboard::Tab)) {
				rs = true;

			}
			if (camera.getCenter().x > coin2[2].getPosition().x + 410)
			{


				/*for (int i = 0; i < 4; i++) {
					if (!bcoin[i])
						coin[i].setPosition(coin[i].getPosition().x + 1000.f, coin[i].getPosition().y);
					else
					{
						coin[i].setPosition(coin[i].getPosition().x + 2000.f, coin[i].getPosition().y);
						bcoin[i] = 0;
					}if (!bcoin1[i])
						coin1[i].setPosition(coin1[i].getPosition().x + 1000.f, coin1[i].getPosition().y);
					else
					{
						coin1[i].setPosition(coin1[i].getPosition().x + 2000.f, coin1[i].getPosition().y);
						bcoin1[i] = 0;
					}
				}
				for (int i = 0; i < 3; i++) {
					if (!bcoin2[i])
						coin2[i].setPosition(coin2[i].getPosition().x + 1000.f, coin2[i].getPosition().y);
					else
					{
						coin2[i].setPosition(coin2[i].getPosition().x + 2000.f, coin2[i].getPosition().y);
						bcoin2[i] = 0;
					}
				}*/
				for (int i = 0; i < 4; i++) {
					if (!benemy[i])
						enemy[i].enemy.setPosition(enemy[i].enemy.getPosition().x + 500.f, enemy[i].enemy.getPosition().y);
					else
					{
						enemy[i].enemy.setPosition(enemy[i].enemy.getPosition().x + 1500.f, enemy[i].enemy.getPosition().y);
						benemy[i] = 1;
					}
				}

			}
			

		}
		if(click==3)
			user_name(window, font, text_username, event);

		if (click == 4) {
			//END(window, exitForEnd, LEVEL2);
			//window.clear();
			//sonic.setOrigin(sonic.getGlobalBounds().width, -300);
			//sonic.setPosition(10, 20.f);
			Time_clock.restart();
			//camera.setCenter(Vector2f(350.f, 200.f));
			CameraView(window, camera, sonic, text0, text02, text03, text04, heart0);
			text0.setPosition(10, 10);
			text02.setPosition(10, 50);
			text03.setPosition(10, 90);
			SONIC_ANIMATION(window, sonic, camera);
			GameWorld2(window, Castle2, Flag2, smallblock, Halfcastle2, Mirrorcliff, Cliff, Block, Background2, Ground, win, sonic);
		 
			enemiesload_draw(window, enemy, enemyanmationcounter);
		
			enemies_move(window, enemy, DeltaTime, enemiesclock, coin);

			Intersections(window, camera, t_rings, input, gameover, sonic,/* spritesthorns, halfcastle,*/ coin, coin1, coin2, sound, enemy, text0, soundout, text03, SCORE, health, text04, win);
			jump(window, sonic);
			//CameraView(window, camera, sonic, text0, text02, text03, text04, heart0);
			window.setView(camera);
			window.draw(sonic);
			
			window.draw(text0);
			window.draw(text02);
			window.draw(text03);
			window.draw(text04);
			window.draw(heart0);
			window.draw(gameover);
			/*for (int i = 0; i < 5; i++) {
				if (sonic.getGlobalBounds().intersects(spritescactus[i].getGlobalBounds()))
					spritesheart[i].setScale(0, 0);
			}
			for (int i = 0; i < 3; i++)
				window.draw(spritesheart[i]);*/
			drow_coin2(window, coin, coin1, coin4, sonic, Cointure);
			calculatetime(seconds, minutes, Time_clock);
			How_we_want_Time(seconds, minutes, text02, window);
			if (Keyboard::isKeyPressed(Keyboard::Tab)) {
				rs = true;

			}
			if (camera.getCenter().x > coin2[2].getPosition().x + 410)
			{


				for (int i = 0; i < 4; i++) {
					if (!bcoin[i])
						coin[i].setPosition(coin[i].getPosition().x + 1000.f, coin[i].getPosition().y);
					else
					{
						coin[i].setPosition(coin[i].getPosition().x + 2000.f, coin[i].getPosition().y);
						bcoin[i] = 0;
					}if (!bcoin1[i])
						coin1[i].setPosition(coin1[i].getPosition().x + 1000.f, coin1[i].getPosition().y);
					else
					{
						coin1[i].setPosition(coin1[i].getPosition().x + 2000.f, coin1[i].getPosition().y);
						bcoin1[i] = 0;
					}
				}
				for (int i = 0; i < 3; i++) {
					if (!bcoin2[i])
						coin2[i].setPosition(coin2[i].getPosition().x + 1000.f, coin2[i].getPosition().y);
					else
					{
						coin2[i].setPosition(coin2[i].getPosition().x + 2000.f, coin2[i].getPosition().y);
						bcoin2[i] = 0;
					}
				}
				for (int i = 0; i < 4; i++) {
					if (!benemy[i])
						enemy[i].enemy.setPosition(enemy[i].enemy.getPosition().x + 500.f, enemy[i].enemy.getPosition().y);
					else
					{
						enemy[i].enemy.setPosition(enemy[i].enemy.getPosition().x + 1500.f, enemy[i].enemy.getPosition().y);
						benemy[i] = 1;
					}
				}

			}
		}
		/*if (click == 3) {

		Game_Over(window, text, text1, mouse, backgroundForUI);
			click = 0;
		}*/
		/*if (click == 1 && rs) {
			RESUME(window, text1, text2, mouse, backgroundForEnd);
		}*/
		if (click == 6)
			cridit( window, font, text_username);
		exitForEnd.setPosition((float)camera.getCenter().x, 150.f);
		LEVEL2.setPosition((float)camera.getCenter().x, 250.f);
		window.setMouseCursorVisible(false);


		window.display();
	}
}
void Intersections(RenderWindow& window, View& camera, int& t_rings, ofstream& input, Sprite& gameover, Sprite& sonic,/* Sprite spritesthorns[2], Sprite& halfcastle,*/ Sprite coin[], Sprite coin1[], Sprite coin2[], Sound& sound, enemies enemy[], Text& text0, Sound& soundout, Text& text03, int& SCORE, int& health, Text& text04, Sprite& win) {

	// this for thorns
	//for (int i = 0; i < 2; i++)
	//{
	//	if (sonic.getGlobalBounds().intersects(spritesthorns[i].getGlobalBounds())) {
	//		// WHAT WILL HAPPEND
	//	}
	//}
	//// this for halfcastle 

	//if (sonic.getGlobalBounds().intersects(halfcastle.getGlobalBounds())) {
	//	//click = 2;
	//	window.draw(win);
	//}
	for (int i = 0; i < 4; i++) {
		if (sonic.getGlobalBounds().intersects(coin[i].getGlobalBounds())) {
			coin[i].setPosition(coin[i].getPosition().x - 1000.f, coin[i].getPosition().y);
			bcoin[i] = 1;
			rings++;

			t_rings++;
			text0.setString("Rings : " + to_string(rings));
			sound.play();
		}

		if (sonic.getGlobalBounds().intersects(coin1[i].getGlobalBounds())) {
			coin1[i].setPosition(coin1[i].getPosition().x - 1000.f, coin1[i].getPosition().y);
			bcoin1[i] = 1;
			rings++;
			t_rings++;
			text0.setString("Rings : " + to_string(rings));
			sound.play();
		}


	}
	for (int i = 0; i < 3; i++) {
		if (sonic.getGlobalBounds().intersects(coin2[i].getGlobalBounds())) {
			coin2[i].setPosition(coin2[i].getPosition().x - 1000.f, coin2[i].getPosition().y);
			bcoin2[i] = 1;
			rings++;
			t_rings++;
			text0.setString("Rings : " + to_string(rings));
			sound.play();
		}
	}



	for (int i = 0; i < sizeENEMIES; i++) {
		if (sonic.getGlobalBounds().intersects(enemy[i].enemy.getGlobalBounds())) {
			rings = 0;
			text0.setString("Rings : " + to_string(rings));
			health--;
			text04.setString("x " + to_string(health));
			soundout.play();
			enemy[i].enemy.setPosition(enemy[i].enemy.getPosition().x - 500.f, enemy[i].enemy.getPosition().y);
			benemy[i] = 1;
		}
		/*if (sonic.getGlobalBounds().intersects(enemy[i].enemy.getGlobalBounds())&&rings==0){
		health--;
		text04.setString("x " + to_string(health));
		}

		*/
	}
	if (health == 0 && rings == 0) {
		gameover.setPosition(camera.getCenter().x - 150, camera.getCenter().y - 130);

		gameover.setScale(0.8, 0.8);

		input.open("High Score.txt");
		input << "High Score \n " << t_rings;

		input.close();
		sleep_for(nanoseconds(10));
		sleep_until(system_clock::now() + (1s));


	}

}
void SONIC_ANIMATION(RenderWindow& window, Sprite& sonic, View& camera) {
	cout << sonic.getPosition().x << endl;
	//movement at cliff
	if (sonic.getPosition().x >= 620 && sonic.getPosition().x < 850)
	{
		if (Keyboard::isKeyPressed(Keyboard::Key::D) && sonic.getPosition().x >= 620)
			sonic.move(0, -11);
		else if (Keyboard::isKeyPressed(Keyboard::Key::A) && sonic.getPosition().x >= 620)
			sonic.move(0, 11);
	}
	if (sonic.getPosition().x >= 850 && sonic.getPosition().x < 2020)
	{
		if (Keyboard::isKeyPressed(Keyboard::Key::D) && sonic.getPosition().x <= 2020)
			sonic.move(0, 0);
		else if (Keyboard::isKeyPressed(Keyboard::Key::A) && sonic.getPosition().x <= 2020)
			sonic.move(0, 0);
	}
	if (sonic.getPosition().x >= 2020 && sonic.getPosition().x < 2260)
	{
		if (Keyboard::isKeyPressed(Keyboard::Key::D) && sonic.getPosition().x <= 2260)
			sonic.move(0, 11);
		else if (Keyboard::isKeyPressed(Keyboard::Key::A) && sonic.getPosition().x <= 2260)
			sonic.move(0, -11);
	}


	if (Keyboard::isKeyPressed(Keyboard::D)) {
		y = 0;
		sonic.setTextureRect(IntRect(X * x, y * Y, X, Y));
		x++;
		x %= 9;
		sonic.move(20.f, 0.f);
	}

	else if (Keyboard::isKeyPressed(Keyboard::A)) {
		y = 0;
		sonic.setTextureRect(IntRect(X * x, Y * y, -X, Y));
		x %= 9;
		x++;
		if (x > 9) {
			x = 0;
		}
		sonic.move(-20.f, 0.f);
	}

	else if (Keyboard::isKeyPressed(Keyboard::Space)) {
		// here will be jump animation

	}

	else {
		y = 1;
		sonic.setTextureRect(IntRect(x * X - 5, y * Y, X, Y));
		x %= 1;
		x++;
		if (x > 1) {
			x = 0;
		}
	}

}
void jump(RenderWindow& window, Sprite& sonic) {
	if (Keyboard::isKeyPressed(Keyboard::Space))
	{
		//std::cout << "Space is pressed";
		if (isBottom && !isJumping)
		{
			//make jumping stage;
			isJumping = true;
			isBottom = false;
		}
	}

	//sonic jump(up and down)
	if (isJumping)
	{
		sonicPos.y -= gravity;
	}
	else
	{
		sonicPos.y += gravity;
	}
	//sonic jump limit, sonic bottom limit.
	if (sonicPos.y >= 0)
	{
		sonicPos.y = 0;
		isBottom = true;
	}

	if (sonicPos.y <= 0 - 100)
	{
		isJumping = false;
	}
	//sonic step.

	frame += frameSpeed;
	if (frame > changeCount)
	{
		frame -= changeCount;
	}

}
void CameraView(RenderWindow& window, View& camera, Sprite& sonic, Text& text0, Text& text02, Text& text03, Text& text04, Sprite& heart0) {
	if (Keyboard::isKeyPressed(Keyboard::D)) {
		if (camera.getCenter().x + 350 < 6215 /* && sonic.getPosition(window).x>-5*/) {
			camera.move(Vector2f(20.f, 0.f));

		}
		//camera.move(Vector2f(4.f, 0.f));
		text0.move(20.f, 0.f);
		text02.move(20.f, 0.f);
		text03.move(20.f, 0.f);
		text04.move(20.f, 0.f);
		heart0.move(20.f, 0.f);

	}
	else if (Keyboard::isKeyPressed(Keyboard::A)) {
		if (camera.getCenter().x - 350 > 0) {
			camera.move(Vector2f(-5.3f, 0.f));
		}
		//camera.move(Vector2f(-5.3f, 0.f));
		text0.move(-5.3f, 0.f);
		text02.move(-5.3f, 0.f);
		text03.move(-5.3f, 0.f);
		text04.move(-5.3f, 0.f);
		heart0.move(-5.3f, 0.f);
	}
	sonic.setOrigin(sonic.getGlobalBounds().width, -300 - sonicPos.y);
}
void UI(RenderWindow& window, Text& text, Text& text1, Text& text05, Sprite& mouse, RectangleShape& background,Text text06) {
	// draw
	window.draw(background);
	window.draw(mouse);
	window.draw(text);
	window.draw(text1);
	window.draw(text05);
	//window.draw(text06);
	// this two switch between play and exit
	if (time1 < 10)
		time1++;
	if (time2 < 10)
		time2++;

	if (Keyboard::isKeyPressed(Keyboard::Tab))
		rs = false;
	if (Keyboard::isKeyPressed(Keyboard::Up) && time1 >= 10 || Keyboard::isKeyPressed(Keyboard::Down) && time1 >= 10) {
		score++;
		time1 = 0;
	}
	if (score == 1) {
		text.setFillColor(Color::Blue);
		text1.setFillColor(Color::Black);
		text05.setFillColor(Color::Black);
		text06.setFillColor(Color::Black);
	}
	if (score == 2) {
		text.setFillColor(Color::Black);
		text1.setFillColor(Color::Blue);
		text05.setFillColor(Color::Black);
		text06.setFillColor(Color::Black);
	}
	if (score == 3) {
		text.setFillColor(Color::Black);
		text1.setFillColor(Color::Black);
		text05.setFillColor(Color::Blue);
		text06.setFillColor(Color::Black);
	}
	if (score >= 3)
		score = 0;
	if (Keyboard::isKeyPressed(Keyboard::Enter) && score == 1 && time2 >= 10) {
		window.close();
		time2 = 0;
	}
	if (Keyboard::isKeyPressed(Keyboard::Enter) && score == 2 && time2 >= 10) {
		//std::cout << "play is pressed\n";
		click = 3;
		time2 = 0;
	}
	if (Keyboard::isKeyPressed(Keyboard::Enter) && score == 3 && time2 >= 10) {
		click = 6;

		time2 = 0;
	}
	if (score == 4) {
		text.setFillColor(Color::Black);
		text1.setFillColor(Color::Black);
		text05.setFillColor(Color::Black);
		text06.setFillColor(Color::Blue);
	}
	if (Keyboard::isKeyPressed(Keyboard::Enter) && score == 2 && time2 >= 10) {
		//std::cout << "play is pressed\n";
		click = 6;
		time2 = 0;
	}
	// Mouse postition and collistions
	mouse.setPosition((float)Mouse::getPosition().x, (float)Mouse::getPosition().y);
	if (mouse.getGlobalBounds().intersects(text1.getGlobalBounds())) {
		text1.setFillColor(Color::Blue);
		text.setFillColor(Color::Black);
		text05.setFillColor(Color::Black);
		text06.setFillColor(Color::Black);
	}
	if (mouse.getGlobalBounds().intersects(text.getGlobalBounds())) {
		text.setFillColor(Color::Blue);
		text1.setFillColor(Color::Black);
		text06.setFillColor(Color::Black);
		text05.setFillColor(Color::Black);
	}
	if (mouse.getGlobalBounds().intersects(text05.getGlobalBounds())) {
		text05.setFillColor(Color::Blue);
		text.setFillColor(Color::Black);
		text1.setFillColor(Color::Black);
		text06.setFillColor(Color::Black);
	}
	if (mouse.getGlobalBounds().intersects(text06.getGlobalBounds())) {
		text.setFillColor(Color::Black);
		text1.setFillColor(Color::Black);
		text05.setFillColor(Color::Black);
		text06.setFillColor(Color::Blue);
	}
	if (mouse.getGlobalBounds().intersects(text1.getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left)) {
		click = 1;
	}
	if (mouse.getGlobalBounds().intersects(text.getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left)) {
		window.close();
	}
}
void GameWorld(RenderWindow& window, Texture Castle, Texture Flag, Texture Thorns, Texture Smallblock, Texture Halfcastle,Texture Mirrorcliff, Texture Cliff, Texture Block, Texture Background, Texture Ground, Sprite& win, Sprite& sonic) {
	Sprite background;
	background.setTexture(Background);
	background.setScale(0.5f, 0.6f);
	background.setPosition(-50.f, 0.f);
	Sprite spritesbackground[11];
	for (int i = 0; i < 11; i++) {
		spritesbackground[i] = background;
		spritesbackground[i].setPosition(-50.f + ((float)i * 565), 0);
	}

	Sprite ground;
	ground.setTexture(Ground);
	ground.setScale(0.5f, 0.3f);
	ground.setPosition(-50, 343);
	Sprite spritesground[20];
	for (int i = 0; i < 20; i++) {
		spritesground[i] = ground;
		spritesground[i].setPosition(-50 + ((float)i * 410), 343);
	}
	Sprite block;
	block.setTexture(Block);
	block.setScale(0.5, 0.5);
	block.setPosition(2600, 155);
	Sprite spritesblock[3];
	for (size_t i = 0; i < 3; i++) {
		spritesblock[i] = block;
		spritesblock[i].setPosition(2600 + (i * 400), 223);
	}

	Sprite cliff;
	cliff.setTexture(Cliff);
	cliff.setScale(0.8, 0.65);
	cliff.setPosition(525, 155);

	Sprite mirrorcliff;
	mirrorcliff.setTexture(Mirrorcliff);
	mirrorcliff.setScale(0.8, 0.65);
	mirrorcliff.setPosition(1825, 155);

	Sprite smallblock;
	smallblock.setTexture(Smallblock);
	smallblock.setScale(0.75, 0.25);
	smallblock.setPosition(1070, 150);
	Sprite spritessmallblock[2];
	for (size_t i = 0; i < 2; i++) {
		spritessmallblock[i] = smallblock;
		spritessmallblock[i].setPosition(1050 + (i * 350), 150);
	}

	Sprite thorns;
	thorns.setTexture(Thorns);
	thorns.setScale(0.5, 0.35);
	//thorns.setPosition(2820, 245);
	Sprite spritesthorns[2];
	for (size_t i = 0; i < 2; i++) {
		spritesthorns[i] = thorns;
		spritesthorns[i].setPosition(2760 + (i * 400), 245);
	}

	Sprite flag;
	flag.setTexture(Flag);
	flag.setScale(0.7, 0.7);
	flag.setPosition(3850, 115);

	Sprite castle;
	castle.setTexture(Castle);
	castle.setScale(0.7, 0.7);
	castle.setPosition(4140, 118);

	Sprite halfcastle;
	halfcastle.setTexture(Halfcastle);
	halfcastle.setScale(0.385, 0.39);
	halfcastle.setPosition(4375, 120);

	if (sonic.getGlobalBounds().intersects(castle.getGlobalBounds()))
	{
		castle.setScale(0, 0);
		click = 4;
	}
	
	
	if (game == true)
	{
		for (int i = 0; i < 11; i++) {
			window.draw(spritesbackground[i]);
		}
		window.draw(background);

		for (int i = 0; i < 20; i++) {
			window.draw(spritesground[i]);
		}
		window.draw(ground);

		for (int i = 0; i < 3; i++) {
			window.draw(spritesblock[i]);
		}

		for (int i = 0; i < 2; i++) {
			window.draw(spritessmallblock[i]);
		}

		for (int i = 0; i < 2; i++) {
			window.draw(spritesthorns[i]);
		}

		window.draw(cliff);

		window.draw(mirrorcliff);

		window.draw(flag);

		window.draw(castle);

		window.draw(halfcastle);
		//if (sonic.getGlobalBounds().intersects(halfcastle.getGlobalBounds())) {
		//	//click = 2;
		//	//cout << "Rawan ";
		//	window.draw(win);
		//}
	}
}
void RESUME(RenderWindow& window, Text& text, Text& text1, Sprite& mouse, RectangleShape& background) {
	//// code 
	//	// draw
	//window.draw(background);
	//window.draw(mouse);
	//window.draw(text);
	//window.draw(text1);
	//// this two switch between play and exit
	//if (time1 < 10)
	//	time1++;
	//if (time2 < 10)
	//	time2++;
	//if (Keyboard::isKeyPressed(Keyboard::Up) && time1 >= 10 || Keyboard::isKeyPressed(Keyboard::Down) && time1 >= 10) {
	//	score++;
	//	time1 = 0;
	//}
	//if (score % 2 == 0) {
	//	text.setFillColor(Color::Red);
	//	text1.setFillColor(Color::Black);
	//}
	//if (score % 2 == 1) {
	//	text.setFillColor(Color::Black);
	//	text1.setFillColor(Color::Red);
	//}
	//if (Keyboard::isKeyPressed(Keyboard::Enter) && score % 2 == 0 && time2 >= 10) {
	//	window.close();
	//	time2 = 0;
	//}
	//if (Keyboard::isKeyPressed(Keyboard::Enter) && score % 2 == 1 && time2 >= 10) {
	//	//std::cout << "play is pressed\n";
	//	click = 1;
	//	time2 = 0;
	//}

	//// Mouse postition and collistions
	//mouse.setPosition((float)Mouse::getPosition().x, (float)Mouse::getPosition().y);
	//if (mouse.getGlobalBounds().intersects(text1.getGlobalBounds())) {
	//	text1.setFillColor(Color::Red);
	//	text.setFillColor(Color::Black);
	//}
	//if (mouse.getGlobalBounds().intersects(text.getGlobalBounds())) {
	//	text.setFillColor(Color::Red);
	//	text1.setFillColor(Color::Black);
	//}
	//if (mouse.getGlobalBounds().intersects(text1.getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left)) {
	//	click = 1;
	//}
	//if (mouse.getGlobalBounds().intersects(text.getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left)) {
	//	window.close();
	//}
}
void drow_coin(RenderWindow& window, Sprite coin[], Sprite coin1[], Sprite coin2[], Sprite coin3[], Sprite coin4[], Sprite coin5[], Sprite coin6[], Sprite& sonic, Texture Cointure) {
	
	

	
	for (size_t i = 0; i < 4; i++) {
		coin1[i].setPosition(940 + (i * 30), 175); //300 + (i * 1000), 223
		coin1[i].setTexture(Cointure);
		coin1[i].setScale(0.2, 0.2);
		if (sonic.getGlobalBounds().intersects(coin2[i].getGlobalBounds()))
			coin1[i].setScale(0, 0);
	}

		for (size_t i = 0; i < 4; i++) {
		coin2[i].setPosition(1590 + (i * 30), 150);//850 + ((float)i * 1000), 170
		coin2[i].setTexture(Cointure);
		coin2[i].setScale(0.2, 0.2);
		if (sonic.getGlobalBounds().intersects(coin2[i].getGlobalBounds()))
			coin2[i].setScale(0, 0);

	}
	
	for (size_t i = 0; i < 4; i++) {
		coin3[i].setPosition(1890 + (i * 30), 170);//850 + ((float)i * 1000), 170
		coin3[i].setTexture(Cointure);
		coin3[i].setScale(0.2, 0.2);
		if (sonic.getGlobalBounds().intersects(coin3[i].getGlobalBounds()))
			coin3[i].setScale(0, 0);
	}
	
	for (size_t i = 0; i < 4; i++) {
		coin4[i].setPosition(2670 + (i * 30), 180);//850 + ((float)i * 1000), 170
		coin4[i].setTexture(Cointure);
		coin4[i].setScale(0.2, 0.2);

	}
	
	for (size_t i = 0; i < 4; i++) {
		coin5[i].setPosition(3080 + (i * 30), 180);//850 + ((float)i * 1000), 170
		coin5[i].setTexture(Cointure);
		coin5[i].setScale(0.2, 0.2);

	}
	
	for (size_t i = 0; i < 4; i++) {
		coin6[i].setPosition(3465 + (i * 30), 180);//850 + ((float)i * 1000), 170
		coin6[i].setTexture(Cointure);
		coin6[i].setScale(0.2, 0.2);

	}


	coinanmationcounter %= 4;
	coinanmationcounter++;
	/*if (time001 < 3)
		time001++;
	if (time001 >= 3) {
		time001 = 0;*/

	for (int i = 0; i < 4; i++) {

		coin[i].setTextureRect(IntRect(coinanmationcounter * 127.75, coinanmationcounter * 127.75, 127.75, 127.75));
		window.draw(coin[i]);

	}
	for (int i = 0; i < 4; i++) {
		coin1[i].setTextureRect(IntRect(coinanmationcounter * 127.75, coinanmationcounter * 127.75, 127.75, 127.75));
		window.draw(coin1[i]);
	}
	for (int i = 0; i < 4; i++) {
		coin2[i].setTextureRect(IntRect(coinanmationcounter * 127.75, coinanmationcounter * 127.75, 127.75, 127.75));
		window.draw(coin2[i]);
	}
	for (int i = 0; i < 4; i++) {
		coin3[i].setTextureRect(IntRect(coinanmationcounter * 127.75, coinanmationcounter * 127.75, 127.75, 127.75));
		window.draw(coin3[i]);
	}
	for (int i = 0; i < 4; i++) {
		coin4[i].setTextureRect(IntRect(coinanmationcounter * 127.75, coinanmationcounter * 127.75, 127.75, 127.75));
		window.draw(coin4[i]);
	}
	for (int i = 0; i < 4; i++) {
		coin5[i].setTextureRect(IntRect(coinanmationcounter * 127.75, coinanmationcounter * 127.75, 127.75, 127.75));
		window.draw(coin5[i]);
	}
	for (int i = 0; i < 4; i++) {
		coin6[i].setTextureRect(IntRect(coinanmationcounter * 127.75, coinanmationcounter * 127.75, 127.75, 127.75));
		window.draw(coin6[i]);
	}


}
void collision_enemies_and_coin(RenderWindow& window, Sprite& sonic, Sprite coin[], Sound& sound, enemies enemy[], Text& text, Sound& soundout, Text& text3, int& score) {

	//for (int i = 0; i < 4; i++) {
	//	if (sonic.getGlobalBounds().intersects(coin[i].getGlobalBounds())) {
	//		coin[i].setScale(20, 20);
	//		rings++;
	//		text.setString("Rings : " + to_string(rings));
	//		sound.play();
	//	}
	//}

	////int e_x = enemy[0].enemy.getPosition().x;
	//int e_y = enemy[0].enemy.getPosition().y;
	//if (sonic.getGlobalBounds().intersects(enemy[0].enemy.getGlobalBounds())) {
	//	if (sonic.getGlobalBounds().intersects(enemy[0].enemy.getGlobalBounds()) && sonic.getPosition().y == e_y)

	//	{
	//		SCORE = +100;
	//		text3.setString("Score : " + to_string(SCORE));
	//		enemy[0].enemy.setScale(0, 0);
	//	}
	//	rings = 0;
	//	text.setString("Rings : " + to_string(rings));
	//	soundout.play();

	//}
}
void enemiesload_draw(RenderWindow& window, enemies enemy[], int& enemyanmationcounter) {

	enemy[0].enemytexture.loadFromFile("Tex/enemy3.png");
	enemy[1].enemytexture.loadFromFile("Tex/nshots.png");
	enemy[2].enemytexture.loadFromFile("Tex/enemy03.png");

	for (int i = 0; i < sizeENEMIES; i++) {
		enemy[i].enemy.setTexture(enemy[i].enemytexture);


		enemy[i].enemy.setScale(1, 1);

	}

	enemyanmationcounter %= 6;
	enemyanmationcounter++;

	enemyanmationcounter1 %= 2;
	enemyanmationcounter1++;
	/*if (timer002 < 10)
		timer002++;
	if (timer002 >= 10) {
		timer002 = 0;*/

	enemy[1].enemy.setTextureRect(IntRect(0, enemyanmationcounter * 46, 17, 46));

	enemy[2].enemy.setTextureRect(IntRect(enemyanmationcounter1 * 49.5, 0, 49.5, 35));
	/*if (enemyanmationcounter1 == 1) {
		enemy[1].enemy.setPosition(enemy[2].enemy.getPosition().x, enemy[2].enemy.getPosition().y + 20);
	}*/
	window.draw(enemy[2].enemy);
	window.draw(enemy[1].enemy);
	enemy[0].enemy.setTextureRect(IntRect(enemyanmationcounter * 41, 0, 38, 44));

	if (enemy[0].isvisible)
		window.draw(enemy[0].enemy);


}
enemies enemies_move(RenderWindow& window, enemies enemy[], float Deltatime, Clock& enemiesclock, Sprite coin[]) {
	int seconds_for_enemies = enemiesclock.getElapsedTime().asSeconds();
	int velocity = 2.f;
	int displacement = 20.f;

	for (int i = 0; i < sizeENEMIES; i++) {
		if (velocity * seconds_for_enemies <= displacement) {
			enemy[i].enemy.move(20.f * Deltatime, 0);
			for (int i = 0; i < 4; i++) {

				coin[i].setTextureRect(IntRect(coinanmationcounter * 127.75, coinanmationcounter * 127.75, 127.75, 127.75));
				window.draw(coin[i]);
			}
			if (i == 1) {
				enemy[i].enemy.move(0, 20.f * Deltatime);
				continue;
			}
		}
		else {
			if (i == 1) {
				enemy[i].enemy.move(0, 20.f * Deltatime);
				continue;
			}
			enemy[i].enemy.move(-20.f * Deltatime, 0);
			if ((velocity * seconds_for_enemies) == 2 * displacement)
				enemiesclock.restart();
		}
	}

	for (int i = 0; i < sizeENEMIES; i++)
		return enemy[i];
}
void calculatetime(int& seconds, int& minutes, Clock& Time_clock) {
	if (seconds == 60) {
		Time_clock.restart();
		minutes++;
	}
}
void How_we_want_Time(int seconds, int minutes, Text& text02, RenderWindow& window) {
	if (seconds < 10) {
		if (minutes < 10)
			text02.setString("Time: 0" + to_string(minutes) + ":0" + to_string(seconds));
		else
			text02.setString("Time: " + to_string(minutes) + ":0" + to_string(seconds));

	}
	else {
		if (minutes < 10)
			text02.setString("Time: 0" + to_string(minutes) + ":" + to_string(seconds));
		else
			text02.setString("Time: " + to_string(minutes) + ":" + to_string(seconds));
	}
}
void Game_Over(RenderWindow& window, Text& text, Text& text1, Sprite& mouse, RectangleShape& backgroundForUI) {



	// this two switch between play and exit
	if (time1 < 10)
		time1++;
	if (time2 < 10)
		time2++;
	/*	system("pause");
		UI(window, text1, text, mouse, backgroundForUI);*/
	if (Keyboard::isKeyPressed(Keyboard::Tab))
		rs = false;
	if (Keyboard::isKeyPressed(Keyboard::Up) && time1 >= 10 || Keyboard::isKeyPressed(Keyboard::Down) && time1 >= 10) {
		score++;
		time1 = 0;
	}
	if (Keyboard::isKeyPressed(Keyboard::Enter) && score % 2 == 0 && time2 >= 10) {
		window.close();
		time2 = 0;
	}
	if (Keyboard::isKeyPressed(Keyboard::Enter) && score % 2 == 1 && time2 >= 10) {
		//std::cout << "play is pressed\n";
		click = 1;
		time2 = 0;
	}
}
void END(RenderWindow& window, Text& LEVEL2, Text& EXIT) {


	window.draw(LEVEL2);
	window.draw(EXIT);

	// this two switch between play and exit
	if (time1 < 10)
		time1++;
	if (time2 < 10)
		time2++;

	if (Keyboard::isKeyPressed(Keyboard::Tab))
		rs = false;
	if (Keyboard::isKeyPressed(Keyboard::Up) && time1 >= 10 || Keyboard::isKeyPressed(Keyboard::Down) && time1 >= 10) {
		score++;
		time1 = 0;
	}
	if (score % 2 == 0) {
		LEVEL2.setFillColor(Color::Red);
		EXIT.setFillColor(Color::Black);
	}
	if (score % 2 == 1) {
		LEVEL2.setFillColor(Color::Black);
		EXIT.setFillColor(Color::Red);
	}
	if (Keyboard::isKeyPressed(Keyboard::Enter) && score % 2 == 0 && time2 >= 10) {
		window.close();
		time2 = 0;
	}
	if (Keyboard::isKeyPressed(Keyboard::Enter) && score % 2 == 1 && time2 >= 10) {
		//std::cout << "play is pressed\n";
		click = 1;
		time2 = 0;
	}
}
void GameWorld2(RenderWindow & window, Texture Castle, Texture Flag, Texture Block2, Texture Halfcastle, Texture Mirrorcliff, Texture Cliff, Texture Block, Texture Background, Texture Ground, Sprite & win, Sprite &sonic) {
	Sprite background;
	background.setTexture(Background);
	background.setScale(0.5, 0.53);
	background.setPosition(-50, 0);
	Sprite spritesbackground[14];
	for (size_t i = 0; i < 14; i++) {
		spritesbackground[i] = background;
		spritesbackground[i].setPosition(-50 + (i * 450), 0);
	}

	//ground
	
	Sprite ground;
	ground.setTexture(Ground);
	ground.setScale(0.5, 0.5);
	ground.setPosition(-50, 300);
	Sprite spritesground[15];
	for (size_t i = 0; i < 15; i++) {
		spritesground[i] = ground;
		spritesground[i].setPosition(-50 + (i * 410), 300);
	}

	//cliff
	
	Sprite cliff;
	cliff.setTexture(Cliff);
	cliff.setScale(0.8, 0.65);
	cliff.setPosition(2025, 110);

	//mirrorcliff
	
	Sprite mirrorcliff;
	mirrorcliff.setTexture(Mirrorcliff);
	mirrorcliff.setScale(0.8, 0.65);
	mirrorcliff.setPosition(2565, 110);



	//small block down

	Sprite block;
	block.setTexture(Block2);
	block.setScale(0.5, 0.25);
	block.setPosition(500, 180);
	Sprite spritesblock[3];
	for (size_t i = 0; i < 3; i++) {
		spritesblock[i] = block;
		spritesblock[i].setPosition(500 + (i * 410), 180);
	}


	//small block up 
	
	Sprite block2;
	block2.setTexture(Block2);
	block2.setScale(0.5, 0.25);
	block2.setPosition(720, 130);
	Sprite spritesblock2[2];
	for (size_t i = 0; i < 2; i++) {
		spritesblock2[i] = block2;
		spritesblock2[i].setPosition(720 + (i * 410), 130);
	}
	//block 
	Sprite block3;
	block3.setTexture(Block);
	block3.setScale(0.5, 0.5);
	block3.setPosition(3500, 180);

	//flat blocks 

	Sprite block4;
	block4.setTexture(Block2);
	block4.setScale(1, 0.25);
	block4.setPosition(3600, 100);
	Sprite spritesblock4[2];
	for (size_t i = 0; i < 2; i++) {
		spritesblock4[i] = block4;
		spritesblock4[i].setPosition(3600 + (i * 350), 100);
	}


	//small block 
	Sprite block5;
	block5.setTexture(Block2);
	block5.setScale(0.5, 0.25);
	block5.setPosition(4400, 180);

	Sprite flag;
	flag.setTexture(Flag);
	flag.setScale(0.8, 0.8);
	flag.setPosition(4900, 45);

	Sprite castle;
	castle.setTexture(Castle);
	castle.setScale(0.7, 0.7);
	castle.setPosition(5185, 75);


	Sprite halfcastle;
	halfcastle.setTexture(Halfcastle);
	halfcastle.setScale(0.385, 0.39);
	halfcastle.setPosition(5430, 77);

		if (sonic.getGlobalBounds().intersects(castle.getGlobalBounds()))
		{
			castle.setScale(0, 0);
			click = 4;
		}

	
	for (int i = 0; i < 14; i++) {
		window.draw(spritesbackground[i]);
	}
	window.draw(background);


	for (int i = 0; i < 15; i++) {
		window.draw(spritesground[i]);
	}
	window.draw(ground);

	for (int i = 0; i < 3; i++) {
		window.draw(spritesblock[i]);
	}
	//window.draw(block);

	for (int i = 0; i < 2; i++) {
		window.draw(spritesblock2[i]);
	}
	window.draw(block2);

	window.draw(cliff);

	window.draw(mirrorcliff);

	window.draw(block3);

	for (int i = 0; i < 2; i++) {
		window.draw(spritesblock4[i]);
	}
	window.draw(block4);

	window.draw(block5);

	window.draw(flag);

	window.draw(castle);

	window.draw(halfcastle);
}
void drow_coin2(RenderWindow& window, Sprite coin[], Sprite coin1[], Sprite coin4[], Sprite& sonic, Texture Cointure) {




	for (size_t i = 0; i < 4; i++) {
		coin[i].setPosition(630 + (i * 40), 310);
		coin[i].setTexture(Cointure);
		coin[i].setScale(0.2, 0.2);

	}

	for (size_t i = 0; i < 4; i++) {
		coin1[i].setPosition(320 + (i * 70), 195); //300 + (i * 1000), 223
		coin1[i].setTexture(Cointure);
		coin1[i].setScale(0.2, 0.2);

	}

	for (size_t i = 0; i < 4; i++) {
		coin4[i].setPosition(2670 + (i * 30), 180);//850 + ((float)i * 1000), 170
		coin4[i].setTexture(Cointure);
		coin4[i].setScale(0.2, 0.2);

	}

	coinanmationcounter %= 4;
	coinanmationcounter++;
	/*if (time001 < 3)
		time001++;
	if (time001 >= 3) {
		time001 = 0;*/

	for (int i = 0; i < 4; i++) {

		coin[i].setTextureRect(IntRect(coinanmationcounter * 127.75, coinanmationcounter * 127.75, 127.75, 127.75));
		window.draw(coin[i]);

	}
	for (int i = 0; i < 4; i++) {
		coin1[i].setTextureRect(IntRect(coinanmationcounter * 127.75, coinanmationcounter * 127.75, 127.75, 127.75));
		window.draw(coin1[i]);
	}
	
	for (int i = 0; i < 4; i++) {
		coin4[i].setTextureRect(IntRect(coinanmationcounter * 127.75, coinanmationcounter * 127.75, 127.75, 127.75));
		window.draw(coin4[i]);
	}

}
void user_name(RenderWindow& window, Font& font, string& input_uname, Event& event) {
	RectangleShape backgfor_usernameR(Vector2f((float)window.getSize().x, (float)window.getSize().y));
	Texture backgfor_username;
	backgfor_username.loadFromFile("Tex/username.jpg");
	backgfor_usernameR.setTexture(&backgfor_username);


	////click = 1;
	//rs = false;

	Text user_name;
	user_name.setFont(font);
	user_name.setCharacterSize(24);
	user_name.setFillColor(Color::Black);
	user_name.setStyle(Text::Bold);
	user_name.setString("ENTER YOUR NAME");
	user_name.setPosition(((float)window.getSize().x / 2) - 200, 200.f);


	Text user_nameFINAL;
	user_nameFINAL.setFont(font);
	user_nameFINAL.setCharacterSize(24);
	user_nameFINAL.setFillColor(Color::Black);
	user_nameFINAL.setStyle(Text::Bold);



	window.draw(backgfor_usernameR);
	window.draw(user_name);

	if (event.type == Event::TextEntered) {
		if (!Keyboard::isKeyPressed(Keyboard::Escape))
		{
			input_uname += static_cast<String>(event.text.unicode);
			user_nameFINAL.setString(input_uname);


		}
	}
	if (Keyboard::isKeyPressed(Keyboard::BackSpace) && input_uname.size() > 0) {
		input_uname.resize(input_uname.size() - 1);
		user_nameFINAL.setString(input_uname);
	}
	if (Keyboard::isKeyPressed(Keyboard::Enter) && input_uname.size() > 1) {

		click = 1;
		//return;

	}




	user_nameFINAL.setPosition(((float)window.getSize().x / 2) - 220, 350.f);
	window.draw(user_nameFINAL);



}
void cridit(RenderWindow& window, Font& font, string& input_uname) {
	RectangleShape backgfor_usernameR(Vector2f((float)window.getSize().x, (float)window.getSize().y));
	Texture backgfor_username;
	backgfor_username.loadFromFile("Tex/username.jpg");
	backgfor_usernameR.setTexture(&backgfor_username);


	////click = 1;
	//rs = false;

	Text user_name;
	user_name.setFont(font);
	user_name.setCharacterSize(24);
	user_name.setFillColor(Color::Black);
	user_name.setStyle(Text::Bold);
	user_name.setString("ENTER YOUR NAME");
	user_name.setPosition(((float)window.getSize().x / 2) - 200, 200.f);


	Text user_nameFINAL;
	user_nameFINAL.setFont(font);
	user_nameFINAL.setCharacterSize(24);
	user_nameFINAL.setFillColor(Color::Black);
	user_nameFINAL.setStyle(Text::Bold);


	user_nameFINAL.setString(input_uname);
	user_nameFINAL.setPosition(((float)window.getSize().x / 2) - 220, 350.f);

	window.draw(backgfor_usernameR);
	window.draw(user_name);
	
}