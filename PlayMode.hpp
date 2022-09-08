#include "PPU466.hpp"
#include "Mode.hpp"

#include <glm/glm.hpp>

#include <vector>
#include <deque>

struct PlayMode : Mode {
	PlayMode();
	virtual ~PlayMode();

	//functions called by main loop:
	virtual bool handle_event(SDL_Event const &, glm::uvec2 const &window_size) override;
	virtual void update(float elapsed) override;
	virtual void draw(glm::uvec2 const &drawable_size) override;
	
	//Function to reset to default values
	void reset_values(bool printmsg);

	// To level up 
	void level_up();

	// To get absolute values
	float float_abs(float val);

	// To update time power bar
	void time_bar_update(float time_left);
	//----- game state -----

	//input tracking:
	struct Button {
		uint8_t downs = 0;
		uint8_t pressed = 0;
		uint8_t debounce_flg = 0;
	} space, S, F; // Use space - drop item, s - swat away bomb, f - freezetime

	
	float pi = 3.1415926f;	

	// Useful Screen Positions
	glm::vec2 center = glm::vec2(PPU466::ScreenWidth*0.5f, PPU466::ScreenHeight*0.5f);
	glm::vec2 center_bottom = glm::vec2(PPU466::ScreenWidth*0.5f, 0.0f);
	glm::vec2 top_left = glm::vec2(0.0f, PPU466::ScreenHeight*0.9f);
	glm::vec2 top_right = glm::vec2(PPU466::ScreenWidth*0.95f, PPU466::ScreenHeight*0.9f);
	
	//player position:
	glm::vec2 player_at;

	//Bomb Position
	glm::vec2 bomb_at;
	uint8_t bomb_attr;

	//ExtraLife Power Up Pos
	glm::vec2 extralife_pow_at;
	uint8_t extralife_pow_attr;

	//Time Power Up Pos
	glm::vec2 time_pow_at;
	uint8_t time_pow_attr;

	//Total Balls - 10
	std::array< glm::vec2, 10 > ball_at;
	std::array< uint8_t, 10 > ball_attr;
	uint32_t ball_left;

	//Time Stop Bar - 10
	std::array< glm::vec2, 10 > time_bar_at;
	std::array< uint8_t, 10 > time_bar_attr;

	//ExtraLife Bar 
	glm::vec2 extralife_bar_at;
	uint8_t extralife_bar_attr;

	uint32_t level;
	uint8_t lives; //Max 2

	float angular_speedup; // Angular speed increase after level increase
	float drop_speedup; // Drop speed increase after level increase
	float slowdown; // Time Free Factor

	float time_power_consumption; // How quickly time power is consumed
	float time_power_regeneration; //How quickly time power is regenerated

	float Curr_ItemDropSpeed;
	float Curr_AngularSpeed;

	float time_pow_left;

	float ItemDropSpeed;
	float AngularSpeed;
	float radius;

	//Define for each item
	std::array< uint8_t, 10 > dwnflg_ball;
	std::array< uint8_t, 10 > rotateflg_ball;
	std::array< float, 10 > angle_ball;

	uint8_t dwnflg_bomb;
	//uint8_t rotateflg_bomb;
	//float angle_bomb;

	uint8_t dwnflg_el;
	//uint8_t rotateflg_el;
	//float angle_el;
	uint8_t dwnflg_time;

	//Weighted Random Num Gen Array 
	std::array<uint8_t, 10> wt_rand;
	uint8_t randnum;
	uint8_t randflg;

	// Game over flag - This tells if game is over

	//----- drawing handled by PPU466 -----
	PPU466 ppu;
};
