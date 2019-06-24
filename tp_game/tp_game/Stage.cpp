//======================================================================================================================================//
// === Pre-Compiled Header === //
#include "stdafx.h"

//======================================================================================================================================//
// === This Class Header === //
#include "Stage.h"

//======================================================================================================================================//
// === Classes headers for definition === //
#include "Game.h"

//======================================================================================================================================//
// === Stage methods === //

Stage::Stage(const int id, const int nPlayers) : Abstract_Entity(id)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	initializeStage(nPlayers);
}
Stage::~Stage()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	for (Level* pL : _vLevels)
	{
		if (pL)
			delete pL;
	}
	_vLevels.clear();
}

void Stage::initializeStage(const int nPlayers)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	_currentLevel_id = 0;
	_nPlayers = nPlayers;
	_running = false;

	srand(static_cast<unsigned int>(time(NULL)));
	_nEnemies = (rand() % 11) + 5;
	_nObstacles = (rand() % 11) + 5;

	//levels_dir + stage2_dir + stg2_prefix + "id" + pos_sufix;
	int lv_id = 1;
	std::string tiles_fp = get_lv_fp(_id, lv_id) + gMng::tile_sufix;
	
	_vLevels.push_back(new Level(tiles_fp, { 0.0f, 0.0f }, _nEnemies, _nObstacles));
}

void Stage::execute(const float deltaTime)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	check_pauseKey();

	if (!this->isPaused())
		_vLevels[_currentLevel_id]->execute(deltaTime);
}

void Stage::draw()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	_vLevels[_currentLevel_id]->draw();
}

void Stage::start()
{
	unpause();
	_running = true;
	_vLevels[_currentLevel_id]->start();
}

void Stage::pause()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	this->desactivate();
}

void Stage::unpause()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	_vLevels[_currentLevel_id]->setViewToCenter();
	this->activate();
}

bool Stage::isPaused()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	return !this->isActive();
}

void Stage::check_pauseKey()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	if (pauseKey_isPressed())
	{
		this->pause();
	}
}

bool Stage::pauseKey_isPressed()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	return (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape));
}

const std::string Stage::get_stg_fp(const int stg_id) const
{
	return gMng::levels_dir + "Stage_" + std::to_string(stg_id) + "/st" + std::to_string(stg_id);
}

const std::string Stage::get_lv_fp(const int stg_id, const int lv_id) const
{
	return get_stg_fp(stg_id) + "_lv" + std::to_string(lv_id);
}