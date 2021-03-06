//======================================================================================================================================//
// === Pre-Compiled Header === //
#include "stdafx.h"

//======================================================================================================================================//
// === This Class Header === //
#include "Menu.h"

//======================================================================================================================================//
// === Static initializations === //
const float Menu::keysCD = 0.20f;

//======================================================================================================================================//
// === Menu methods === //

Menu::Menu(const sf::Vector2f initPosit) :
	Abstract_Entity(initPosit), _betweenKeys(keysCD)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	_onOp = 0;
	_nOps = 0;
	_betweenKeys.trigger();
}

Menu::Menu() : Abstract_Entity(), _betweenKeys()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 1 | ");

	_onOp = 0;
	_nOps = 0;
}

Menu::~Menu()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	/*for (int i = 0; i < _vOptions.size(); i++)
	{
		if (_vOptions[i])
			delete _vOptions[i];
	}
	*/
	for (Option* option : _vOptions)
	{
		if (option)
			delete option;
	}
	_vOptions.clear();
}

void Menu::initializeTitle(const std::string str, const int charSize, const sf::Vector2f pos, sf::Color fillColor, sf::Color olColor, const float olThickness, sf::Font* ft)
{
	_title_text = new sf::Text(str, *ft, charSize);
	_title_text->setOrigin(_title_text->getGlobalBounds().width / 2.0f, _title_text->getGlobalBounds().height / 2.0f);
	_title_text->setPosition(pos);
	_title_text->setOutlineThickness(olThickness);
	_title_text->setOutlineColor(olColor);
	_title_text->setFillColor(fillColor);
}

void Menu::initialize_n_addOp(Option*& pOp, const sf::Vector2f position, const std::string label, const int actSize, const int deactSize, sf::Color actColor, sf::Color deactColor, sf::Font* font)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	initializeOp(pOp, position, label, actSize, deactSize, actColor, deactColor);
	this->operator<<(pOp);
}

void Menu::initializeOp(Option*& pOp, const sf::Vector2f position, const std::string label, const int actSize, const int deactSize, sf::Color actColor, sf::Color deactColor, sf::Font* font)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	pOp = new Option(font, position, label, actSize, deactSize, actColor, deactColor);
}

void Menu::execute(const float deltaTime)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	if (this->isActive())
	{
		deactivate_allOps();

		activate_onOp();

		check_allKeys();
	}
}

void Menu::draw()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	//window->draw(*_animator->getpSprite());
	/*for (int i = 0; i < _vOptions.size(); i++)
	{
		_vOptions[i]->draw(window);
	}
	*/
	for (Option* option : _vOptions)
	{
		option->draw();
	}

	_pGraphMng->draw(*_title_text);
}

void Menu::activate_onOp()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	_vOptions[_onOp]->activate();
}

void Menu::check_allKeys()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	if (_betweenKeys.isZeroed())
	{
		if (selectionKey_isPressed())
		{
			_betweenKeys.reset_and_trigger();
			execute_onOp();
			this->close();
		}
		if (upKey_isPressed())
		{
			_betweenKeys.reset_and_trigger();
			upOp();
		}
		if (downKey_isPressed())
		{
			_betweenKeys.reset_and_trigger();
			downOp();
		}
	}
	else
	{
		_betweenKeys.decreaseTime();
	}
}

bool Menu::selectionKey_isPressed()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	return(sf::Keyboard::isKeyPressed(sf::Keyboard::Return));
}

bool Menu::upKey_isPressed()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	return (sf::Keyboard::isKeyPressed(sf::Keyboard::W));
}

bool Menu::downKey_isPressed()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	return (sf::Keyboard::isKeyPressed(sf::Keyboard::S));
}

void Menu::close()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	this->desactivate();
}

void Menu::open()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	this->activate();
	_onOp = 0;
}

bool Menu::isOpen()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	return this->isActive();
}

void Menu::deactivate_allOps()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	for (Option* option : _vOptions)
	{
		option->desactivate();
	}
}

void Menu::add_option(Option* pOp)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	if (pOp)
	{
		_vOptions.push_back(pOp);
		_nOps++;
	}
}

void Menu::operator<<(Option* pOp)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	if (pOp)
		add_option(pOp);
}

void Menu::upOp()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	if(_onOp != 0)
		_onOp--;
}

void Menu::downOp()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	if (_onOp != _nOps - 1)
		_onOp++;
}

//======================================================================================================================================//
// === Option methods === //

Menu::Option::Option(sf::Font* font, const sf::Vector2f position, const std::string label, const int actSize, const int deactSize, sf::Color actColor, sf::Color deactColor) :
	Abstract_Entity(position)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	_charSize_active = actSize;
	_charSize_deactive = deactSize;

	_textColor_active = actColor;
	_textColor_deactive = deactColor;

	initializeText(font, label); //position 
}

Menu::Option::Option() : Abstract_Entity(), _text()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 1 | ");

	_text = NULL;

	_charSize_active = 0;
	_charSize_deactive = 0;

	_textColor_active = sf::Color::White;
	_textColor_deactive = sf::Color::White;
}

Menu::Option::~Option()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

}

void Menu::Option::initializeText(sf::Font* font, const std::string label)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	_text = new sf::Text(label, *font);
	_text->setPosition(this->getPosition());
}

void Menu::Option::execute(const float deltaTime)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

}

void Menu::Option::draw()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	Abstract_Entity::_pGraphMng->draw(*_text);
}

void Menu::Option::activate()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	_active = true;
	_text->setFillColor(_textColor_active);
	_text->setCharacterSize(_charSize_active);
	_text->setOrigin(_text->getLocalBounds().width / 2.0f, _text->getLocalBounds().height / 2.0f);
}

void Menu::Option::desactivate()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	_active = false;
	_text->setFillColor(_textColor_deactive);
	_text->setCharacterSize(_charSize_deactive);
	_text->setOrigin(_text->getLocalBounds().width / 2.0f, _text->getLocalBounds().height / 2.0f);
}

void Menu::Option::setText(sf::Text* text)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	_text = text;
}

sf::Text* Menu::Option::getText()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	return _text;
}