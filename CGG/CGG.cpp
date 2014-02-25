// CGG.cpp : main project file.

#include <stdafx.h>
#include <windows.h>
#include <objidl.h>
#include "Form1.h"

using namespace CGG;

[STAThreadAttribute]

int main(array<System::String ^> ^args)
{
	// Enabling Windows XP visual effects before any controls are created
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 
	// Create the main window and run it
	Application::Run(gcnew Form1());
	// Add your code here
	return 0;
}
