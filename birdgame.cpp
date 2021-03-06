// birdgame.cpp: A program using the TL-Engine

#include <TL-Engine.h>	// TL-Engine include file and namespace
#include <iostream>
#include <math.h>
#include "Object.h"
#include "Engine.h"
#include "LuaMap.h"

extern "C"
{
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

using namespace tle;

void main()
{
	// Create a 3D engine (using TLX engine here) and open a window for it
	I3DEngine* myEngine = New3DEngine( kTLX );
	myEngine->StartWindowed();

	// Set the active engine for other areas of code to access
	SetEngine( myEngine );

	// Add default folder for meshes and other media
	myEngine->AddMediaFolder( "C:\\ProgramData\\TL-Engine\\Media" );

	//--------- Prepare Lua
	lua_State* l = lua_open();
	luaL_openlibs( l );

	lua_register( l, "AddObject", _lua_AddObject );

	if ( luaL_dofile( l, "load_map.lua" ) != 0 )
	{
		std::cerr << "Unable to run load_map.lua. This either means the file is missing or the Lua syntax is incorrect." << std::endl;
		lua_close( l );
		delete myEngine;
		return;
	}
	/**** Set up your scene here ****/
	int test = 0;
	//ICamera* camera = myEngine->CreateCamera( kFPS );
	IMesh* cube_mesh = myEngine->LoadMesh( "Cube.x" );
	IMesh* floorMesh = myEngine->LoadMesh("floor.x");
	IMesh* birdMesh = myEngine->LoadMesh("seagull.x");

	IModel* floorModel = floorMesh->CreateModel();
	IModel* birdModel = birdMesh->CreateModel(0,100,-50);

	ICamera* myCamera;
	myCamera = myEngine->CreateCamera( kManual,0,200,-150 );
	//myCamera->AttachToParent (birdModel);

	//Bird movement values
	float mouseMove;
	float birdAngle = 0.0f;
	float birdRads = 0.0f;
	float birdXmovement;

	//Object* cube_object = CreateObject( cube_mesh, 10, 10, 10 );

	// The main game loop, repeat until engine is stopped
	while (myEngine->IsRunning())
	{
		// Draw the scene
		myEngine->DrawScene();

		/**** Update your scene each frame here ****/
		myEngine->StartMouseCapture();
		birdAngle = myEngine->GetMouseMovementX();
		birdRads = (birdAngle/180)*3.14;
		birdXmovement = sin(birdRads);
		birdModel->Move(birdXmovement*20,-0.005,0.05);
		//birdModel->RotateLocalZ(-birdXmovement*5);
		if ( myEngine->KeyHit( Key_Escape ))
		{
			myEngine->Stop();
		}
	}

	// Delete the 3D engine now we are finished with it
	myEngine->Delete();
}
