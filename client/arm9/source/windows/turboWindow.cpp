#include <string>  // std::string
#include "turboWindow.h"
#include "gui/checkButton.h"
#include "gui/label.h"
#include "core.h"

namespace D2K {namespace GUI {namespace Turbo {
//private
extern void CheckButtonLFunction();
extern void CheckButtonRFunction();
extern void CheckButtonLeftFunction();
extern void CheckButtonRightFunction();
extern void CheckButtonUpFunction();
extern void CheckButtonDownFunction();
extern void CheckButtonAFunction();
extern void CheckButtonBFunction();
extern void CheckButtonXFunction();
extern void CheckButtonYFunction();
extern void CheckButtonStartFunction();
extern void CheckButtonSelectFunction();
extern void CheckButtonEnableFunction();
extern void CheckButtonBlueFunction();
extern void CheckButtonYellowFunction();
extern void CheckButtonRedFunction();
extern void CheckButtonGreenFunction();

WindowClass* g_window;
Label* label_title;
CheckButton* check_button_l;
CheckButton* check_button_r;
CheckButton* check_button_left;
CheckButton* check_button_right;
CheckButton* check_button_up;
CheckButton* check_button_down;
CheckButton* check_button_a;
CheckButton* check_button_b;
CheckButton* check_button_x;
CheckButton* check_button_y;
CheckButton* check_button_start;
CheckButton* check_button_select;
CheckButton* check_button_enable;
CheckButton* check_button_blue;
CheckButton* check_button_yellow;
CheckButton* check_button_red;
CheckButton* check_button_green;

//public
WindowClass::WindowClass() : Window()
{
	m_screen = 0;

	AppendObject(label_title	= new Label(m_screen, Rect(24,0+3,128,10), "Turbo Settings"));
				
	AppendObject(check_button_l = new CheckButton(m_screen, Rect(39,39,10,10), "L", &CheckButtonLFunction));
	AppendObject(check_button_r = new CheckButton(m_screen, Rect(205,40,10,10), "R", &CheckButtonRFunction));

	AppendObject(check_button_left = new CheckButton(m_screen, Rect(9,95,10,10), "Left", &CheckButtonLeftFunction));
	AppendObject(check_button_right = new CheckButton(m_screen, Rect(69,95,10,10), "Right", &CheckButtonRightFunction));
	AppendObject(check_button_up = new CheckButton(m_screen, Rect(39,80,10,10), "Up", &CheckButtonUpFunction));
	AppendObject(check_button_down = new CheckButton(m_screen, Rect(39,110,10,10), "Down", &CheckButtonDownFunction));

	AppendObject(check_button_a = new CheckButton(m_screen, Rect(235,95,10,10), "A", &CheckButtonAFunction));
	AppendObject(check_button_b = new CheckButton(m_screen, Rect(205,110,10,10), "B", &CheckButtonBFunction));
	AppendObject(check_button_x = new CheckButton(m_screen, Rect(205,80,10,10), "X", &CheckButtonXFunction));
	AppendObject(check_button_y = new CheckButton(m_screen, Rect(175,95,10,10), "Y", &CheckButtonYFunction));

	AppendObject(check_button_start = new CheckButton(m_screen, Rect(145,115,10,10), "Start", &CheckButtonStartFunction));
	AppendObject(check_button_select = new CheckButton(m_screen, Rect(85,115,10,10), "Select", &CheckButtonSelectFunction));
	AppendObject(check_button_enable = new CheckButton(m_screen, Rect(100,35,10,10), "Enable", &CheckButtonEnableFunction));

				
	AppendObject(check_button_blue = new CheckButton(m_screen, Rect(40,130,10,10), "Blue", &CheckButtonBlueFunction));
	AppendObject(check_button_yellow = new CheckButton(m_screen, Rect(90,130,10,10), "Yellow", &CheckButtonYellowFunction));
	AppendObject(check_button_red = new CheckButton(m_screen, Rect(140,130,10,10), "Red", &CheckButtonRedFunction));
	AppendObject(check_button_green = new CheckButton(m_screen, Rect(190,130,10,10), "Green", &CheckButtonGreenFunction));
}
WindowClass::~WindowClass() { }
uint16_t currentTurboKeys = 0;
void UpdateTurboKeys()
{
	currentTurboKeys = 0;
	if(check_button_l->GetChecked())
		currentTurboKeys |= KEY_L;
	if(check_button_r->GetChecked())
		currentTurboKeys |= KEY_R;
	if(check_button_left->GetChecked())
		currentTurboKeys |= KEY_LEFT;
	if(check_button_right->GetChecked())
		currentTurboKeys |= KEY_RIGHT;
	if(check_button_up->GetChecked())
		currentTurboKeys |= KEY_UP;
	if(check_button_down->GetChecked())
		currentTurboKeys |= KEY_DOWN;
	if(check_button_a->GetChecked())
		currentTurboKeys |= KEY_A;
	if(check_button_b->GetChecked())
		currentTurboKeys |= KEY_B;
	if(check_button_x->GetChecked())
		currentTurboKeys |= KEY_X;
	if(check_button_y->GetChecked())
		currentTurboKeys |= KEY_Y;
	if(check_button_start->GetChecked())
		currentTurboKeys |= KEY_START;
	if(check_button_select->GetChecked())
		currentTurboKeys |= KEY_SELECT;
}
uint16_t CheckTurboKey(uint16_t a)
{
	if(currentTurboKeys&a)
		if(keysHeld()&a)
			return a;
	return 0;
}
uint16_t GetKeys()
{
	uint16_t keys = 0;
	if(check_button_enable->GetChecked() == false)
		return 0;
	UpdateTurboKeys();
	keys |= CheckTurboKey(KEY_A);
	keys |= CheckTurboKey(KEY_B);
	keys |= CheckTurboKey(KEY_X);
	keys |= CheckTurboKey(KEY_Y);
	keys |= CheckTurboKey(KEY_L);
	keys |= CheckTurboKey(KEY_R);
	keys |= CheckTurboKey(KEY_UP);
	keys |= CheckTurboKey(KEY_DOWN);
	keys |= CheckTurboKey(KEY_LEFT);
	keys |= CheckTurboKey(KEY_RIGHT);
	keys |= CheckTurboKey(KEY_START);
	keys |= CheckTurboKey(KEY_SELECT);
	return keys;
}
			
//gh
uint8_t currentGHTurboKeys = 0;
void GHUpdateTurboKeys()
{
	currentGHTurboKeys = 0;
	if(check_button_blue->GetChecked())
		currentGHTurboKeys |= GUITARGRIP_BLUE;
	if(check_button_yellow->GetChecked())
		currentGHTurboKeys |= GUITARGRIP_YELLOW;
	if(check_button_red->GetChecked())
		currentGHTurboKeys |= GUITARGRIP_RED;
	if(check_button_green->GetChecked())
		currentGHTurboKeys |= GUITARGRIP_GREEN;
}
uint8_t GHCheckTurboKey(uint16_t a)
{
	if(currentGHTurboKeys&a)
		if(guitarGripKeysHeld()&a)
			return a;
	return 0;
}
uint8_t GHGetKeys()
{
	uint8_t keys = 0;
	if(check_button_enable->GetChecked() == false)
		return 0;
	GHUpdateTurboKeys();
	keys |= GHCheckTurboKey(GUITARGRIP_BLUE);
	keys |= GHCheckTurboKey(GUITARGRIP_YELLOW);
	keys |= GHCheckTurboKey(GUITARGRIP_RED);
	keys |= GHCheckTurboKey(GUITARGRIP_GREEN);
	return keys;
}

void CheckButtonLFunction()
{
	check_button_l->SetChecked(!check_button_l->GetChecked());
}
void CheckButtonRFunction()
{
	check_button_r->SetChecked(!check_button_r->GetChecked());
}
void CheckButtonLeftFunction()
{
	check_button_left->SetChecked(!check_button_left->GetChecked());
}
void CheckButtonRightFunction()
{
	check_button_right->SetChecked(!check_button_right->GetChecked());
}
void CheckButtonUpFunction()
{
	check_button_up->SetChecked(!check_button_up->GetChecked());
}
void CheckButtonDownFunction()
{
	check_button_down->SetChecked(!check_button_down->GetChecked());
}
void CheckButtonAFunction()
{
	check_button_a->SetChecked(!check_button_a->GetChecked());
}
void CheckButtonBFunction()
{
	check_button_b->SetChecked(!check_button_b->GetChecked());
}
void CheckButtonXFunction()
{
	check_button_x->SetChecked(!check_button_x->GetChecked());
}
void CheckButtonYFunction()
{
	check_button_y->SetChecked(!check_button_y->GetChecked());
}
void CheckButtonStartFunction()
{
	check_button_start->SetChecked(!check_button_start->GetChecked());
}
void CheckButtonSelectFunction()
{
	check_button_select->SetChecked(!check_button_select->GetChecked());
}
void CheckButtonEnableFunction()
{
	check_button_enable->SetChecked(!check_button_enable->GetChecked());
}
void CheckButtonBlueFunction()
{
	check_button_blue->SetChecked(!check_button_blue->GetChecked());
}
void CheckButtonYellowFunction()
{
	check_button_yellow->SetChecked(!check_button_yellow->GetChecked());
}
void CheckButtonGreenFunction()
{
	check_button_green->SetChecked(!check_button_green->GetChecked());
}
void CheckButtonRedFunction()
{
	check_button_red->SetChecked(!check_button_red->GetChecked());
}
}}}//namespace D2K::GUI::Turbo
