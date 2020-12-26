#include<SFML/Graphics.hpp>
#include<bits/stdc++.h>

#define gravity 9.8
#define ground_pos_x 0
#define ground_pos_y 400
#define ground_scale_x 0.5
#define ground_scale_y 0.65
#define runner_scale_x 0.27
#define runner_scale_y 0.27
#define runner_pos_x 270
#define runner_pos_y 332
#define window_x 800
#define window_y 600
#define frame_per_sec 9
#define little_runner_pos_x runner_pos_x+50
#define little_runner_pos_y runner_pos_y+34
#define little_runner_size 178
#define obstacle_size 904/3

using namespace sf;
using namespace std;

// v = u + at

double Velocity(double velocity,double g,int time){
	return velocity + g*time*1e-8;
}



int main(){

	vector<string>v;
	for(int i=1;i<=10;i++)v.push_back("e"+to_string(i)+".png");

	int frame_count = 0;
	int next_frame = 0,obstacle_frame = 0,little_runner_frame = 0;
	int time = 1;
	double velocity = 0;
	bool jump = false;
	bool gameOver = true;
	int score = 0;

	// F O N T
	
	Font font;
	if(font.loadFromFile("arial.ttf"));
	Text text;
	text.setFont(font);
	text.setFillColor(Color::Black);
	text.setStyle(Text::Bold);

	RenderWindow window;
	window.create(VideoMode(window_x,window_y),"G A M E");
	//window.setFramerateLimit(frame_per_sec);

	// T E X T U R E

	Texture backGround , ground , runner , little_runner , obstacle[v.size()];
	if(backGround.loadFromFile("back.png"));
	if(ground.loadFromFile("ground.png"));
	//if(little_runner.loadFromFile("run.png"));
	if(runner.loadFromFile("runner.png"));
	

	// S P R I T E

	Sprite s_backGround , s_ground , s_runner , s_little_runner , s_obstacle[v.size()];
	s_backGround.setTexture(backGround);
	s_ground.setTexture(ground);
	//s_little_runner.setTexture(little_runner);
	s_runner.setTexture(runner);



	// S E T  P O S I T I O N 

	s_ground.setPosition(ground_pos_x,ground_pos_y);
	//s_little_runner.setPosition(little_runner_pos_x,little_runner_pos_y);
	s_runner.setPosition(runner_pos_x,runner_pos_y);
	
	
    // S E T  S C A L E 

	s_ground.setScale(ground_scale_x,ground_scale_y);
	//s_little_runner.setScale(runner_scale_x-.05,runner_scale_y-.05);
	s_runner.setScale(runner_scale_x,runner_scale_y);

	// O B S T A C L E 

	for(int i=0;i<v.size();i++){       //______________________________________________________
		if(obstacle[i].loadFromFile(v[i]));
		s_obstacle[i].setTexture(obstacle[i]);
		s_obstacle[i].setPosition(window_x - 400*i,window_y-400);
		s_obstacle[i].setScale(runner_scale_x,runner_scale_y);
	}
	
	// G A M E  L O O P

	while(window.isOpen()){

		text.setString("\n   S C O R E  :  "+to_string(score/500));//________............................
		
		Event event;
		while(window.pollEvent(event)){
			if(event.type == Event::Closed)window.close();
			else if(Keyboard::isKeyPressed(Keyboard::Space)){
				velocity = 0.1;
				jump = true;
				printf("jump\n");
			}
			else if(Keyboard::isKeyPressed(Keyboard::E))window.close();
			else if(Keyboard::isKeyPressed(Keyboard::P)){
				gameOver = false;
				for(int i=0;i<v.size();i++)s_obstacle[i].setPosition(window_x+400*i,runner_pos_y);//________________________
			}
		}

		if(!gameOver){

			// F R A M E   C H A N G E

			//s_little_runner.setTextureRect(IntRect(little_runner_size*(little_runner_frame%9),0,177,150));
			s_runner.setTextureRect(IntRect(250*(next_frame%6),0,250,250));
			if(frame_count >= 150){
				if(!jump){
					next_frame++;
					little_runner_frame+=2;
				}
				obstacle_frame++;
				frame_count = 0;
			}
			frame_count++;
		


			// J U M P

			if(jump){
				double x = s_runner.getPosition().x;
				double y = s_runner.getPosition().y;
				//double _x = s_little_runner.getPosition().x;
				//double _y = s_little_runner.getPosition().y;
				velocity = Velocity(velocity,-gravity,time++);
				s_runner.setPosition(x,y-velocity);
				//s_little_runner.setPosition(_x,_y-velocity);
				if(y > runner_pos_y){
					printf("hi\n");
					s_runner.setPosition(runner_pos_x,runner_pos_y);
					//s_little_runner.setPosition(little_runner_pos_x,little_runner_pos_y);
					velocity = 0;
					jump = false;
					time = 1;
				}
				printf("%lf\n",velocity);
			}
		
			// O B S T A C L E   M O V E M E N T

			for(int i=0;i<v.size();i++){ 
				s_obstacle[i].setPosition(s_obstacle[i].getPosition().x-.1,s_obstacle[i].getPosition().y);
				if(s_obstacle[i].getPosition().x < -100)s_obstacle[i].setPosition(window_x+i*400,s_obstacle[i].getPosition().y);
					//___________________________________________________________________________________
			}

			// D R A W

			window.draw(s_backGround);
			window.draw(s_ground);
			//window.draw(s_little_runner);
			window.draw(s_runner);
			window.draw(text);
			for(int i=0;i<v.size();i++)window.draw(s_obstacle[i]);
		

			// G A M E  O V E R
			for(int i=0;i<v.size();i++){
				if(s_obstacle[i].getPosition().x >= s_runner.getPosition().x
					&& s_obstacle[i].getPosition().x <= s_runner.getPosition().x+50){
					if(jump)score++;
					else{
						gameOver = true;
						window.clear();
					}
				}
			}

					
		}
		else{
			Texture exit;
			Sprite s_exit;
			if(exit.loadFromFile("exit.png"));
			s_exit.setTexture(exit);
			text.setString("\n\n                             S C O R E  :  "+to_string(score/500));
			window.draw(s_exit);
			window.draw(text);

		}
		window.display();
		window.clear();
	}

	return 0;
}