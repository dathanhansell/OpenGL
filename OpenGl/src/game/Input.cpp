#include "Input.h"
#include <gl\glut.h>
using namespace std;

void MousePassive(int X, int Y) 
{
	if (GetActiveWindow() == 00000000) return;
}
Input::Input() {
	Init();
}
Input::~Input() {
	
}
void Input::Init()
{
	cout << "Initializing Input Module..." << endl;
	
	cout << "Done!" << endl;
	
}
void Input::Update() {

	for (int i = 0; i < Key::KeyCount; i++) {
		lastKeys[i] = sf::Keyboard::isKeyPressed(sf::Keyboard::Key(i));
	}

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