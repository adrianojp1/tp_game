#pragma once

//======================================================================================================================================//
// === Classes Headers === //
#include "Animator.h"
#include "Timer.h"

//======================================================================================================================================//
// === Classes Declaration === //
class MyWindow;

//======================================================================================================================================//
// === Player Class === //
class Player
{
private:
	// ========= Visual Members ========= //
	//Animators
	Animator *_idle_animator; //Idle
	Animator *_walk_animator; //Walking
	Animator *_def1_animator; //Normal defense
	Animator *_def2_animator; //Counter defense

	Animator* _current_Animator; //Pointer for current animator

	//sf::Sprite _sprite; //Sprite for textures setting
	bool _facingRight;  //Bool for the side direction

	// ========= Motion Members ========= //
	//Colliders
	sf::RectangleShape* _idle_Collider; //Idle
	sf::RectangleShape* _walk_Collider; //Walking
	sf::RectangleShape* _def_Collider; //Defense

	sf::RectangleShape* _current_Collider; //Pointer for current collider

	float _walkSpeed; //Horizontal walking speed
	float _jumpHeight;
	sf::Vector2f _position;
	sf::Vector2f _velocity;

	// ========= Booleans for state control ========= //
	bool _defending;
	bool _defCounterUp;
	bool _canJump;

	Timer _defCounterTimer; //Timer for the defense counter

public:
	//================================================================//
	// ========== Constructors ========== //
	Player(sf::Vector2f initPosition, float speed, float jumpHeight);
	Player();
	// ========== Destructors ========== //
	~Player();

	//================================================================//
	// ========== Initializers ========== //
	void initializeAnimators();
	void initializeColliders();

	//================================================================//
	// ========== Loop methods ========== //
	void execute(float deltaTime);
	void draw(MyWindow *window);

	//================================================================//
	// ========== Collision ========== //
	void move(float dx, float dy) { _position += sf::Vector2f(dx, dy); }
	void move(sf::Vector2f offset) { _position += offset; }
	void onCollision(sf::Vector2f collisionDirection);
	//================================================================//
	// ========== State checkers ========== //
	bool isDefending() const;
	bool isCounterUp() const;
	bool isDefending_with_Counter() const;

	//================================================================//
	// ========== Sets & Gets ========== //
	// _walkSpeed
	void setWalkSpeed(float walkSpeed);
	float getWalkSpeed() const;
	// _jumpHeight
	void setJumpHeight(float jumpHeight);
	float getJumpHeight() const;
	// _position
	void setPosition(sf::Vector2f position);
	sf::Vector2f getPosition() const;
	// _collider
	sf::RectangleShape* getCollider() { return _current_Collider; }

private:
	// ========== Control keys methods ========== //
	bool leftIsKeyPressed();
	bool rightIsKeyPressed();
	bool jumpKeyPressed();
	bool defendKeyPressed();

	// ========== execute submethods ========== //
	void updatePosition(float deltaTime);
	void updateAnimation(float deltaTime);
	bool isNotWalking(float HorizontalMovement);
};
