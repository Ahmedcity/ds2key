#pragma once

#include <windows.h>

namespace D2K {namespace GUI {

class Object
{
public:
	Object(int x, int y, int width, int height);
	virtual ~Object();
				
	//@returns true on success, else false
	virtual bool Attach(Object *parentObject);
				
	//@returns -1 if ID is not set
	int GetID();
				
	//@returns NULL_VALUE if Parent HWND not set
	HWND GetParentHWND();
				
	//@returns NULL_VALUE if parent not set
	Object *GetParent();
	void SetVisible(bool visible = true);
protected:
	HWND hwnd;				//This is the handle for our window
	Object *parent;			//pointer to attached parent object
	int X;
	int Y;
	int Width;
	int Height;
	int ID;					//event ID
};

}}//namespace D2K::GUI
