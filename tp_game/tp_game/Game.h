#pragma once

//======================================================================================================================================//
// === Classes Headers === //
#include "Stage.h"
#include "Main_Menu.h"
#include "NewGame_Menu.h"
#include "Pause_Menu.h"
#include "Game_State.h"

//======================================================================================================================================//
// === Game Class === //
class Game
{
private:
	static Game* _instance;
	Graphical_Manager* _window;

	Main_Menu* _main_menu;
	NewGame_Menu* _newGame_menu;
	//Saves_Menu* _saves_menu;
	Pause_Menu* _pause_menu;

	int _nPlayers;
	Player* _pPlayer1;
	Player* _pPlayer2;

	Stage* _stage1;
	//Stage1* _stage2;
	Stage* _currentStage;

	//Save* _currentSave;

	//State control
	bool _runningStage; //True if a stage is running, paused or not
	
	//Time control
	float _deltaTime;
	sf::Clock _clock; //To get the deltaTime
	
	Game_State* _state;

private:
	//================================================================//
	// ========== Constructors ========== //
	Game();
public:
	// ========== Destructors ========== //
	~Game();
	
	//================================================================//
	// ========== Singleton ========== //
	static Game* getInstance();

	//================================================================//
	// ========== Initializers ========== //
	void initialize();
	void initialize_player1();
	void initialize_player2();
	void initialize_stage1();

	//================================================================//
	// ========== Menus ========== //
	void open_Main_Menu();
	void open_NewGame_Menu();
	void open_Saves_Menu();
	void open_Pause_Menu();

	//================================================================//
	static void main_loop();
	void execute();
	void draw();
	void update_deltaTime();

	void changeState(Game_State* state);

	void close();

	void pause_stage();
	void unpause_stage();
	bool isRunning_stage();
	void run_stage();
	void stop_runningStage();

	void resetPlayers();
	void set_nPlayers(int nP);
	void set_currentStage(int stg_id);
	Stage* get_currentStage();
	Main_Menu* get_main_menu();
	NewGame_Menu* get_newGame_menu();
	//Saves_Menu* get_saves_menu();
	Pause_Menu* get_pause_menu();
};