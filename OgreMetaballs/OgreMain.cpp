#include "Common.h"
#include "MetaballsApp.h"

extern "C" {
#define WIN32_LEAN_AND_MEAN 
#include "windows.h" 
	INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT) 
	{
		//Create the application
		MetaballsApp myApp;
		try {
			myApp.go();
		}
		catch (Ogre::Exception& e) {
			MessageBoxA(NULL, e.getFullDescription().c_str(), "An exception has occured!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
			return 1;
		}
		return 0;
	}
}
