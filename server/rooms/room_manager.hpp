/* Copyright: (c) Kayne Ruse 2013-2016
 * 
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 * 
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 * 
 * 1. The origin of this software must not be misrepresented; you must not
 * claim that you wrote the original software. If you use this software
 * in a product, an acknowledgment in the product documentation would be
 * appreciated but is not required.
 * 
 * 2. Altered source versions must be plainly marked as such, and must not be
 * misrepresented as being the original software.
 * 
 * 3. This notice may not be removed or altered from any source
 * distribution.
*/
#pragma once

#include "character_data.hpp"
#include "room_data.hpp"
#include "singleton.hpp"

#include "lua.hpp"
#include "sqlite3.h"

#include <functional>
#include <map>

class RoomManager: public Singleton<RoomManager> {
public:
	//common public methods
	int Create(std::string name, std::string tileset);

	void UnloadAll();
	void UnloadIf(std::function<bool(std::pair<const int, RoomData const&>)> fn);

	void PushCharacter(CharacterData* character);
	void PopCharacter(CharacterData const* character);

	//accessors and mutators
	RoomData* Find(int uid);
	RoomData* Find(std::string name);
	int GetLoadedCount();
	std::map<int, RoomData>* GetContainer();

	//API interfaces
	lua_State* SetLuaState(lua_State* L);
	lua_State* GetLuaState();
	sqlite3* SetDatabase(sqlite3* db);
	sqlite3* GetDatabase();

	//hooks
	int SetCreateReference(int i);
	int SetUnloadReference(int i);

	int GetCreateReference();
	int GetUnloadReference();

private:
	friend Singleton<RoomManager>;

	RoomManager() = default;
	~RoomManager() = default;

	//members
	std::map<int, RoomData> elementMap;
	int counter = 0;

	//API
	lua_State* lua = nullptr;
	sqlite3* database = nullptr;

	//hooks
	int createRef = LUA_NOREF;
	int unloadRef = LUA_NOREF;
};
