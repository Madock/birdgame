#ifndef _LUAMAP_H_
#define _LUAMAP_H_

extern "C"
{
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

#include "Object.h"
#include <string>

inline int _lua_AddObject( lua_State* l )
{
	const int number_of_args = 10;
	const int number_of_args2 = 11;
	int argc = lua_gettop( l );

	if ( argc == number_of_args )
	{
		string mesh_name = lua_tostring( l, 1 );
		float x = (float)lua_tonumber( l, 2 );
		float y = (float)lua_tonumber( l, 3 );
		float z = (float)lua_tonumber( l, 4 );
		float x_scale = (float)lua_tonumber( l, 5 );
		float y_scale = (float)lua_tonumber( l, 6 );
		float z_scale = (float)lua_tonumber( l, 7 );
		float x_rot = (float)lua_tonumber( l, 8 );
		float y_rot = (float)lua_tonumber( l, 9 );
		float z_rot = (float)lua_tonumber( l, 10 );

		tle::IMesh* mesh = FindObjectMesh( mesh_name );
		Object* temp_object = CreateObject( mesh, x, y, z );
		temp_object->SetRotation( x_rot, y_rot, z_rot );
		temp_object->SetScale( x_scale, y_scale, z_scale );

		return 0;
		
	}
	else if ( argc == number_of_args2 )
	{
		string mesh_name = lua_tostring( l, 1 );
		float x = (float)lua_tonumber( l, 2 );
		float y = (float)lua_tonumber( l, 3 );
		float z = (float)lua_tonumber( l, 4 );
		float x_scale = (float)lua_tonumber( l, 5 );
		float y_scale = (float)lua_tonumber( l, 6 );
		float z_scale = (float)lua_tonumber( l, 7 );
		float x_rot = (float)lua_tonumber( l, 8 );
		float y_rot = (float)lua_tonumber( l, 9 );
		float z_rot = (float)lua_tonumber( l, 10 );
		string skin_name = lua_tostring( l, 11 );

		tle::IMesh* mesh = FindObjectMesh( mesh_name );
		Object* temp_object = CreateObject( mesh, x, y, z );
		temp_object->SetRotation( x_rot, y_rot, z_rot );
		temp_object->SetScale( x_scale, y_scale, z_scale );
		temp_object->SetSkin( skin_name );

		return 0;
	}
	else
	{
		std::cerr << "Incorrect number of arguments were passed to _lua_AddObject" << std::endl;
		return 0;
	}	
}

#endif