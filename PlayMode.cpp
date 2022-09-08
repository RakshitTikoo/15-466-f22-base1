#include "PlayMode.hpp"

//for the GL_ERRORS() macro:
#include "gl_errors.hpp"

//for glm::value_ptr() :
#include <glm/gtc/type_ptr.hpp>

#include <random>
#include <stdio.h>



PlayMode::PlayMode() {
reset_values(true);
//Insert Code Below

// Following asset code developed using asset pipeline script convert_png_2_code.py. 
// The asset pipeline code scans the png sprites, creates the code, and writes it below 


// Following code for asset : Background.png

ppu.tile_table[0].bit0 = {
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
};

ppu.tile_table[0].bit1 = {
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
};

ppu.palette_table[0] = {
	glm::u8vec4(0xa1, 0x00, 0xb2, 0xff),
	glm::u8vec4(0x00, 0x00, 0x00, 0xff),
	glm::u8vec4(0x00, 0x00, 0x00, 0xff),
	glm::u8vec4(0x00, 0x00, 0x00, 0xff),
};


// Following code for asset : Ball.png

ppu.tile_table[1].bit0 = {
	0b00111100,
	0b01111110,
	0b11111111,
	0b11111111,
	0b11111111,
	0b11111111,
	0b01111110,
	0b00111100,
};

ppu.tile_table[1].bit1 = {
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
};

ppu.palette_table[1] = {
	glm::u8vec4(0xa1, 0x00, 0xb2, 0xff),
	glm::u8vec4(0x17, 0xcc, 0x0c, 0xff),
	glm::u8vec4(0x00, 0x00, 0x00, 0xff),
	glm::u8vec4(0x00, 0x00, 0x00, 0xff),
};


// Following code for asset : Bomb.png

ppu.tile_table[2].bit0 = {
	0b00111100,
	0b00011000,
	0b11111111,
	0b11100111,
	0b11100111,
	0b11111111,
	0b00011000,
	0b00111100,
};

ppu.tile_table[2].bit1 = {
	0b00000000,
	0b01100110,
	0b00000000,
	0b00011000,
	0b00011000,
	0b00000000,
	0b01100110,
	0b00000000,
};

ppu.palette_table[2] = {
	glm::u8vec4(0xa1, 0x00, 0xb2, 0xff),
	glm::u8vec4(0x34, 0x34, 0x34, 0xff),
	glm::u8vec4(0x6f, 0x00, 0x00, 0xff),
	glm::u8vec4(0x00, 0x00, 0x00, 0xff),
};


// Following code for asset : Clock.png

ppu.tile_table[3].bit0 = {
	0b00111100,
	0b01111110,
	0b11111111,
	0b11111111,
	0b11111111,
	0b11111111,
	0b01111110,
	0b00111100,
};

ppu.tile_table[3].bit1 = {
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
};

ppu.palette_table[3] = {
	glm::u8vec4(0xa1, 0x00, 0xb2, 0xff),
	glm::u8vec4(0x00, 0x64, 0xc3, 0xff),
	glm::u8vec4(0x00, 0x00, 0x00, 0xff),
	glm::u8vec4(0x00, 0x00, 0x00, 0xff),
};


// Following code for asset : ExtraLife.png

ppu.tile_table[4].bit0 = {
	0b00000000,
	0b00011000,
	0b00011000,
	0b00111100,
	0b01111110,
	0b11111111,
	0b11111111,
	0b01100110,
};

ppu.tile_table[4].bit1 = {
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
};

ppu.palette_table[4] = {
	glm::u8vec4(0xa1, 0x00, 0xb2, 0xff),
	glm::u8vec4(0xd2, 0x00, 0x00, 0xff),
	glm::u8vec4(0x00, 0x00, 0x00, 0xff),
	glm::u8vec4(0x00, 0x00, 0x00, 0xff),
};


// Following code for asset : Player.png

ppu.tile_table[5].bit0 = {
	0b11111111,
	0b11111111,
	0b00001111,
	0b00001111,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
};

ppu.tile_table[5].bit1 = {
	0b11111111,
	0b11111111,
	0b11110000,
	0b11110000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
};

ppu.palette_table[5] = {
	glm::u8vec4(0x00, 0x00, 0x00, 0xff),
	glm::u8vec4(0x04, 0x59, 0xff, 0xff),
	glm::u8vec4(0xff, 0x04, 0x04, 0xff),
	glm::u8vec4(0xa5, 0x5c, 0x0a, 0xff),
};

}

PlayMode::~PlayMode() {
}

float PlayMode::float_abs(float val) {
	if (val < 0.0f) { return -1.0f*val;}
	return val;
}

void PlayMode::reset_values(bool printmsg) 
{
	if(printmsg) {
		printf("\n\n############\nNEW GAME\n############\n");
		printf("\nLevel 1\nLives = 1\n");
	}

	// Reset time power 
	time_pow_left = 100.0f;

	// Movement values
	ItemDropSpeed = 500.0f;
	AngularSpeed = 0.03f;
	radius = center.y*0.75f;

	// Time Power Values
	time_power_consumption = 1.0f; 
	time_power_regeneration = 0.1f;

	// Speedup and Slowdown Values
	drop_speedup = 1.25f; 
	angular_speedup = 1.25f; 
	slowdown = 0.5f;

	// Reset Level and Lives 
	level = 1;
	lives = 1;

	//Initialize Positions for sprites
	player_at = center_bottom;
	player_at.y += (center.y*0.25f - 8.0f);
	bomb_at = center;

	extralife_pow_at = center;
	time_pow_at = center;

	ball_at[0] = center;
	ball_at[1] = center;
	ball_at[2] = center;
	ball_at[3] = center;
	ball_at[4] = center;
	ball_at[5] = center;
	ball_at[6] = center;
	ball_at[7] = center;
	ball_at[8] = center;
	ball_at[9] = center;

	time_bar_at[0].x = top_left.x; time_bar_at[0].y = top_left.y - 0*16.0f;
	time_bar_at[1].x = top_left.x; time_bar_at[1].y = top_left.y - 1*16.0f;
	time_bar_at[2].x = top_left.x; time_bar_at[2].y = top_left.y - 2*16.0f;
	time_bar_at[3].x = top_left.x; time_bar_at[3].y = top_left.y - 3*16.0f;
	time_bar_at[4].x = top_left.x; time_bar_at[4].y = top_left.y - 4*16.0f;
	time_bar_at[5].x = top_left.x; time_bar_at[5].y = top_left.y - 5*16.0f;
	time_bar_at[6].x = top_left.x; time_bar_at[6].y = top_left.y - 6*16.0f;
	time_bar_at[7].x = top_left.x; time_bar_at[7].y = top_left.y - 7*16.0f;
	time_bar_at[8].x = top_left.x; time_bar_at[8].y = top_left.y - 8*16.0f;
	time_bar_at[9].x = top_left.x; time_bar_at[9].y = top_left.y - 9*16.0f;


	//ExtraLife Bar 
	extralife_bar_at = top_right;


	//Set variable visibility sprite default attributes
	bomb_attr = 0x82;

	extralife_pow_attr = 0x84;
	time_pow_attr = 0x83;

	ball_attr[0] = 0x81;
	ball_attr[1] = 0x81;
	ball_attr[2] = 0x81;
	ball_attr[3] = 0x81;
	ball_attr[4] = 0x81;
	ball_attr[5] = 0x81;
	ball_attr[6] = 0x81;
	ball_attr[7] = 0x81;
	ball_attr[8] = 0x81;
	ball_attr[9] = 0x81;

	time_bar_attr[0] = 0x03;
	time_bar_attr[1] = 0x03;
	time_bar_attr[2] = 0x03;
	time_bar_attr[3] = 0x03;
	time_bar_attr[4] = 0x03;
	time_bar_attr[5] = 0x03;
	time_bar_attr[6] = 0x03;
	time_bar_attr[7] = 0x03;
	time_bar_attr[8] = 0x03;
	time_bar_attr[9] = 0x03;

	extralife_bar_attr = 0x84;

	// Flag value setting 
	dwnflg_ball[0] = 2;
	dwnflg_ball[1] = 2;
	dwnflg_ball[2] = 2;
	dwnflg_ball[3] = 2;
	dwnflg_ball[4] = 2;
	dwnflg_ball[5] = 2;
	dwnflg_ball[6] = 2;
	dwnflg_ball[7] = 2;
	dwnflg_ball[8] = 2;
	dwnflg_ball[9] = 2;

	rotateflg_ball[0] = 2;
	rotateflg_ball[1] = 2;
	rotateflg_ball[2] = 2;
	rotateflg_ball[3] = 2;
	rotateflg_ball[4] = 2;
	rotateflg_ball[5] = 2;
	rotateflg_ball[6] = 2;
	rotateflg_ball[7] = 2;
	rotateflg_ball[8] = 2;
	rotateflg_ball[9] = 2;

	dwnflg_bomb = 2;
	dwnflg_el = 2;
	dwnflg_time = 2;

	// Random Function Gen 
	// 0 - ball, 1 - bomb, 2 - el pow, 3 - tf pow
	wt_rand = {0, 0 ,0, 0, 0, 1, 1, 1, 2, 3};
	randflg = 0;

	// Ball left count
	ball_left = 10;
}

void PlayMode::level_up() {
	float temp_ItemDropSpeed = ItemDropSpeed;
	float temp_AngularSpeed = AngularSpeed;
	uint32_t temp_level = level;
	uint8_t temp_lives = lives;
	float temp_timeleft = time_pow_left;

	reset_values(false);

	ItemDropSpeed = temp_ItemDropSpeed*drop_speedup; // Increase by speedup factor
	AngularSpeed = temp_AngularSpeed*angular_speedup; // Increase by speedup factor
	level = temp_level + 1;
	lives = temp_lives;
	time_pow_left = temp_timeleft;
	if(lives == 2) {
		extralife_bar_attr = extralife_bar_attr & 0x7F; // Enable the power bar
	}
	printf("\n\n############\nLEVEL UP!\n############\n");
	printf("\nLevel %d\nLives = %d\n", level, lives);

}

void PlayMode::time_bar_update(float time_left) {// This updates visibility of time power bar
	uint32_t en = 10;

	if(time_left <= 100.0f && time_left >= 90.0f) {en = 10;}
	if(time_left < 90.0f && time_left >= 80.0f) {en = 9;}
	if(time_left < 80.0f && time_left >= 70.0f) {en = 8;}
	if(time_left < 70.0f && time_left >= 60.0f) {en = 7;}
	if(time_left < 60.0f && time_left >= 50.0f) {en = 6;}
	if(time_left < 50.0f && time_left >= 40.0f) {en = 5;}
	if(time_left < 40.0f && time_left >= 30.0f) {en = 4;}
	if(time_left < 30.0f && time_left >= 20.0f) {en = 3;}
	if(time_left < 20.0f && time_left >= 10.0f) {en = 2;}	
	if(time_left < 10.0f && time_left > 0.0f) {en = 1;}	
	if(time_left == 0.0f) {en = 0;}
	
	uint32_t i, j;
	for(i = 0; i < en; i ++) time_bar_attr[i] = time_bar_attr[i] & 0x7F; // Enable 
	for(j = i; j < 10; j ++) time_bar_attr[j] = time_bar_attr[j] | 0x80; // Disable 
}

bool PlayMode::handle_event(SDL_Event const &evt, glm::uvec2 const &window_size) {
	// Debounce Flag added to make one keypress one event. F is timestop which stays on till the button is pressed. 
	// So no flag check for button F. 
	if (evt.type == SDL_KEYDOWN) {
		if (evt.key.keysym.sym == SDLK_SPACE && space.debounce_flg == 0) {
			space.downs += 1;
			space.pressed = 1;
			space.debounce_flg = 1;
			return true;
		}
		else if (evt.key.keysym.sym == SDLK_s  && S.debounce_flg == 0) {
			S.downs += 1;
			S.pressed = 1;
			S.debounce_flg = 1;
			return true;
		}
		else if (evt.key.keysym.sym == SDLK_f) {
			F.downs += 1;
			F.pressed = 1;
			F.debounce_flg = 1;
			return true;
		}
	} else if (evt.type == SDL_KEYUP) {
		if (evt.key.keysym.sym == SDLK_SPACE) {
			space.pressed = 0;
			space.debounce_flg = 0;
			return true;
		} 
		else if (evt.key.keysym.sym == SDLK_s) {
			S.pressed = 0;
			S.debounce_flg = 0;
			return true;
		}
		else if (evt.key.keysym.sym == SDLK_f) {
			F.pressed = 0;
			F.debounce_flg = 0;
			return true;
		}
	}

	return false;
}

void PlayMode::update(float elapsed) {

	// Set speeds -
	Curr_ItemDropSpeed = ItemDropSpeed;
	Curr_AngularSpeed = AngularSpeed;

	// Code to decide which item appears in the center next
	if(randflg == 0) {
		randnum = std::rand() % 10;
		randflg = 1;
		if(wt_rand[randnum] == 0) { // Ball need to appear
			dwnflg_ball[ball_left - 1] = 0;
			rotateflg_ball[ball_left - 1] = 0;
			ball_attr[ball_left - 1] = ball_attr[ball_left - 1] & 0x7F; // Make visible in random function
		}
		else if(wt_rand[randnum] == 1) {
			dwnflg_bomb = 0;
			bomb_attr = bomb_attr & 0x7F;
		}
		else if(wt_rand[randnum] == 2) {
			if(lives == 1){
				dwnflg_el = 0;
				extralife_pow_attr = extralife_pow_attr & 0x7F;
			}
			else randflg = 0;
		}
		else if(wt_rand[randnum] == 3) {
			dwnflg_time = 0;
			time_pow_attr = time_pow_attr & 0x7F;
		}
	}
	
	
	
	// The following code enables slowdown
	if(F.pressed) {
		if(time_pow_left > 0.0f) {
			Curr_AngularSpeed = AngularSpeed*slowdown;
			Curr_ItemDropSpeed = ItemDropSpeed*slowdown;
			time_pow_left -= time_power_consumption;
		}
	}

	else {
		if(time_pow_left < 100.0f) time_pow_left += time_power_regeneration;
	}
	
	if(time_pow_left < 0.0f) time_pow_left = 0.0f;
	time_bar_update(time_pow_left);

	


	// The following code enables swatting bombs
	if(S.pressed && S.debounce_flg == 1) {
		S.debounce_flg = 2;
		if(wt_rand[randnum] == 1) {
			dwnflg_bomb = 2;
			bomb_attr = bomb_attr | 0x80;
			randflg = 0;
		}		
	}

	// The following code enables the drop of item logic
	if (space.pressed && space.debounce_flg == 1) {
		space.debounce_flg = 2;
		if(dwnflg_ball[ball_left - 1] == 0 && rotateflg_ball[ball_left - 1] == 0) {
			dwnflg_ball[ball_left - 1] = 1;
		}
		else if(dwnflg_bomb == 0) {
			dwnflg_bomb = 1;
		}
		else if(dwnflg_el == 0) {
			dwnflg_el = 1;
		}
		else if(dwnflg_time == 0) {
			dwnflg_time = 1;
		}
	}

	// The following code does the drop
	if(dwnflg_ball[ball_left - 1] == 1) { // Ball drop
		if(ball_at[ball_left - 1].y > center.y - radius) {
			ball_at[ball_left - 1].y -= Curr_ItemDropSpeed*elapsed;
		}
		if(ball_at[ball_left - 1].y <= center.y - radius) {
			
			ball_at[ball_left - 1].y = center.y - radius;
			dwnflg_ball[ball_left - 1] = 2;
			rotateflg_ball[ball_left - 1] = 1;
			angle_ball[ball_left - 1] = pi;

			// Check if some other ball is in vicinity
			for(uint32_t i = 0; i < 10; i++) {
				if(i != ball_left - 1) {
					if(ball_at[i].y < center.y && float_abs(ball_at[i].x - ball_at[ball_left - 1].x) <= 8.0f) { // This is a lose condition. 
						lives --;
						// Reset Ball
						ball_at[ball_left - 1].y = center.y;
						dwnflg_ball[ball_left - 1] = 2;
						rotateflg_ball[ball_left - 1] = 2;
						ball_attr[ball_left - 1] = ball_attr[ball_left - 1] | 0x80; 
						ball_left++;
						printf("Lives = %d\n", lives);
						if(lives == 1) {
							extralife_bar_attr = extralife_bar_attr | 0x80; // Disable the power bar
						}
					}
				}
			}
			ball_left--;
			randflg = 0;
		}
	}
	else if(dwnflg_bomb == 1) { // Bomb Drop
		if(bomb_at.y > center.y - radius) {
			bomb_at.y -= Curr_ItemDropSpeed*elapsed;
		}
		if(bomb_at.y <= center.y - radius) { // This is a lose condition, reset values. 
			bomb_at.y = center.y; // Snap Back to center
			dwnflg_bomb = 2; // Reset Values
			bomb_attr = bomb_attr | 0x80; // Make invisible again. 
			randflg = 0;
			lives --; // Lives are reduced
			printf("Lives = %d\n", lives);
			if(lives == 1) {
				extralife_bar_attr = extralife_bar_attr | 0x80; // Disable the power bar
			}
		}
	}

	else if(dwnflg_el == 1) { // el power up drop
		if(extralife_pow_at.y > extralife_pow_at.y - radius) {
			extralife_pow_at.y -= Curr_ItemDropSpeed*elapsed;
		}
		if(extralife_pow_at.y <= center.y - radius) { // This is a power up condition, use lives count to see if we regenerate. 
			extralife_pow_at.y = center.y; // Snap Back to center
			dwnflg_el = 2; // Reset Values
			extralife_pow_attr = extralife_pow_attr | 0x80; // Make invisible again. 
			extralife_bar_attr = extralife_bar_attr & 0x7F; // Enable the power bar
			lives += 1;
			printf("Lives = %d\n", lives);
			randflg = 0;
		}
	}

	else if(dwnflg_time == 1) { // time power up drop
		if(time_pow_at.y > time_pow_at.y - radius) {
			time_pow_at.y -= Curr_ItemDropSpeed*elapsed;
		}
		if(time_pow_at.y <= center.y - radius) { // This is a power up condition, update time bar. 
			time_pow_at.y = center.y; // Snap Back to center
			dwnflg_time = 2; // Reset Values
			time_pow_attr = time_pow_attr | 0x80; // Make invisible again. 
			time_pow_left = 100; //Reset time power
			randflg = 0;
		}
	}


	// The following code does level up
	if(ball_left == 0) {
		level_up();
	}

	// The following code handles game over
	if(lives <= 0) {
		reset_values(true);
	}

	// The following is rotate logic for all the balls
	for(uint32_t i = 0; i < 10; i++) {
		if(rotateflg_ball[i] == 1) {
			
		ball_at[i].x = player_at.x + radius*std::sin(angle_ball[i]);
		ball_at[i].y = center.y + radius*std::cos(angle_ball[i]);
		angle_ball[i] += Curr_AngularSpeed;
		}
	}
	


	//reset button press counters:
	space.downs = 0;
	S.downs = 0;
	F.downs = 0;
}



void PlayMode::draw(glm::uvec2 const &drawable_size) {
	//--- set ppu state based on game state ---

	//Set all background tiles to a solid value
	for (uint32_t x = 0; x < PPU466::BackgroundHeight * PPU466::BackgroundWidth; x++) {
			ppu.background[x] = 0;
	}

	//player sprite 0 
	ppu.sprites[0].x = int8_t(player_at.x);
	ppu.sprites[0].y = int8_t(player_at.y);
	ppu.sprites[0].index = 5;
	ppu.sprites[0].attributes = 5;

	//bomb sprite 1
	ppu.sprites[1].x = int8_t(bomb_at.x);
	ppu.sprites[1].y = int8_t(bomb_at.y);
	ppu.sprites[1].index = 2;
	ppu.sprites[1].attributes = bomb_attr;

	//extra life power up sprite 2
	ppu.sprites[2].x = int8_t(extralife_pow_at.x);
	ppu.sprites[2].y = int8_t(extralife_pow_at.y);
	ppu.sprites[2].index = 4;
	ppu.sprites[2].attributes = extralife_pow_attr;

	// time power up sprite 3
	ppu.sprites[3].x = int8_t(time_pow_at.x);
	ppu.sprites[3].y = int8_t(time_pow_at.y);
	ppu.sprites[3].index = 3;
	ppu.sprites[3].attributes = time_pow_attr;

	// ball at sprites 4-13
	for(uint32_t i = 4; i <= 13; i++) {
		ppu.sprites[i].x = int8_t(ball_at[i-4].x);
		ppu.sprites[i].y = int8_t(ball_at[i-4].y);
		ppu.sprites[i].index = 1;
		ppu.sprites[i].attributes = ball_attr[i-4];
	}
	//time bar sprites 14-23 
	for(uint32_t i = 14; i <= 23; i++) {
		ppu.sprites[i].x = int8_t(time_bar_at[i-14].x);
		ppu.sprites[i].y = int8_t(time_bar_at[i-14].y);
		ppu.sprites[i].index = 3;
		ppu.sprites[i].attributes = time_bar_attr[i-14];
	}

	//extra life bar sprite 24
	ppu.sprites[24].x = int8_t(extralife_bar_at.x);
	ppu.sprites[24].y = int8_t(extralife_bar_at.y);
	ppu.sprites[24].index = 4;
	ppu.sprites[24].attributes = extralife_bar_attr;

	//--- actually draw ---
	ppu.draw(drawable_size);
}
