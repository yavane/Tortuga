/* Copyright: (c) Kayne Ruse 2013-2015
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

/* DOCS: The headers indicate what packet type is used for each message
 * different messages under the same header will carry different amounts of
 * valid data, but it will still be carried in that packet's format.
 * FORMAT_* is for internal use, deviding the different format bounds.
*/

enum class SerialPacketType {
	//default: there is something wrong
	NONE,

	//-------------------------
	//ServerPacket
	//  name, player count, version
	//-------------------------

	FORMAT_SERVER,

	//heartbeat
	PING,
	PONG,

	//Used for finding available servers
	BROADCAST_REQUEST,
	BROADCAST_RESPONSE,

	FORMAT_END_SERVER,

	//-------------------------
	//ClientPacket
	//  client index, account index, username
	//-------------------------

	FORMAT_CLIENT,

	//Connecting to a server as a client
	JOIN_REQUEST,
	JOIN_RESPONSE,

	//disconnect from the server
	DISCONNECT_REQUEST,
	DISCONNECT_RESPONSE,
	ADMIN_DISCONNECT_FORCED,

	//load the account
	LOGIN_REQUEST,
	LOGIN_RESPONSE,

	//unload the account
	LOGOUT_REQUEST,
	LOGOUT_RESPONSE,

	//shut down the server
	ADMIN_SHUTDOWN_REQUEST,

	FORMAT_END_CLIENT,

	//-------------------------
	//RegionPacket
	//  room index, x, y, raw data
	//-------------------------

	FORMAT_REGION,

	//map data
	REGION_REQUEST,
	REGION_CONTENT,

	FORMAT_END_REGION,

	//-------------------------
	//CharacterPacket
	//  character index,
	//  handle, avatar,
	//  account index (owner),
	//  room index, origin, motion
	//-------------------------

	FORMAT_CHARACTER,

	//full data update
	CHARACTER_UPDATE,

	//character management
	CHARACTER_CREATE,
	CHARACTER_DELETE,
	CHARACTER_LOAD,
	CHARACTER_UNLOAD,

	//find out info from the server
	QUERY_CHARACTER_EXISTS,
	QUERY_CHARACTER_STATS,
	QUERY_CHARACTER_LOCATION,

	//actions taken
	CHARACTER_MOVEMENT,
	CHARACTER_ATTACK,
	CHARACTER_DAMAGE,

	//admin control
//	ADMIN_SET_CHARACTER_ORIGIN,

	FORMAT_END_CHARACTER,

	//-------------------------
	//MonsterPacket
	//  monster index,
	//  handle, avatar
	//  bounds
	//  room index, origin, motion
	//-------------------------

	FORMAT_MONSTER,

	//full data update
	MONSTER_UPDATE,

	//character management
	MONSTER_CREATE,
	MONSTER_DELETE,

	//find out info from the server
	QUERY_MONSTER_EXISTS,
	QUERY_MONSTER_STATS,
	QUERY_MONSTER_LOCATION,

	//actions taken
	MONSTER_MOVEMENT,
	MONSTER_ATTACK,
	MONSTER_DAMAGE,

	FORMAT_END_MONSTER,

	//-------------------------
	//TextPacket
	//  name, text
	//-------------------------

	FORMAT_TEXT,

	//general speech
	TEXT_BROADCAST,
	TEXT_SPEECH,
	TEXT_WHISPER,

	//rejection/error messages
	JOIN_REJECTION,
	LOGIN_REJECTION,
	REGION_REJECTION,
	CHARACTER_REJECTION,
	MONSTER_REJECTION,
	SHUTDOWN_REJECTION,
	QUERY_REJECTION,

	FORMAT_END_TEXT,

	//-------------------------
	//not used
	//-------------------------

	LAST
};