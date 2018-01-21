#include "Input.h"
#include "LowLevelSystem.h"
#include "SFML/System/Vector2.hpp"   // for Vector2i
#include "SFML/Window/Keyboard.hpp"  // for Keyboard, Keyboard::Key
#include "SFML/Window/Mouse.hpp"     // for Mouse, Mouse::Button
#include "Vector2.h"                 // for Vector2
using namespace std;
	void MousePassive(int X, int Y)
	{
		
	}
	float Input::scroll = 0;
	Input::Input() {
		Init();
	}
	Input::~Input() {

	}
	void Input::Init()
	{
		Log("Initializing Input Module...\n");
		OpenBar();
		Log("Done!\n");
		CloseBar();
			

	}
	void Input::Update() {
		
	
		for (int i = 0; i < Key::KeyCount; i++) {
			lastKeys[i] = sf::Keyboard::isKeyPressed(sf::Keyboard::Key(i));
		}
		for (int i = 0; i < Button::ButtonCount; i++) {
			lastButton[i] = sf::Mouse::isButtonPressed(sf::Mouse::Button(i));
		}
		lastMousePos = { (float)sf::Mouse::getPosition().x, -(float)sf::Mouse::getPosition().y };
	}
	float Input::GetMouseScroll() {

		return scroll;
	}
	bool Input::GetMouseButton(Button button) {
		return sf::Mouse::isButtonPressed((sf::Mouse::Button)button);
	}
	bool Input::GetMouseButtonDown(Button button) {
		return sf::Mouse::isButtonPressed((sf::Mouse::Button)button) && !lastButton[button];;
	}
	bool Input::GetMouseButtonUp(Button button) {
		return sf::Mouse::isButtonPressed((sf::Mouse::Button)button) && lastButton[button];;
	}
	Vector2 Input::GetMouse() {
		Vector2 o = { (float)sf::Mouse::getPosition().x, -(float)sf::Mouse::getPosition().y  };
		o = (o - lastMousePos);
		o *= .01f;
		return o;
	}
	bool Input::GetKey(Key keycode)
	{
		return sf::Keyboard::isKeyPressed((sf::Keyboard::Key)keycode);
	}
	bool Input::GetKeyDown(Key keycode)
	{
		return sf::Keyboard::isKeyPressed((sf::Keyboard::Key)keycode) && !lastKeys[keycode];
	}
	bool Input::GetKeyUp(Key keycode)
	{
		return !sf::Keyboard::isKeyPressed((sf::Keyboard::Key)keycode) && lastKeys[keycode];
	}