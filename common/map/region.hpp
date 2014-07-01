/* Copyright: (c) Kayne Ruse 2014
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
#ifndef REGION_HPP_
#define REGION_HPP_

#include <bitset>
#include <cmath>

//the region's storage format
constexpr int REGION_WIDTH = 20;
constexpr int REGION_HEIGHT = 20;
constexpr int REGION_DEPTH = 3;

//the size of the solid map
constexpr int REGION_SOLID_FOOTPRINT = ceil(REGION_WIDTH * REGION_HEIGHT / 8.0);

class Region {
public:
	typedef unsigned char type_t;

	Region() = delete;
	Region(int x, int y);
	Region(Region const&);
	~Region() = default;

	type_t SetTile(int x, int y, int z, type_t v);
	type_t GetTile(int x, int y, int z);

	bool SetSolid(int x, int y, bool b);
	bool GetSolid(int x, int y);

	//accessors
	int GetX() const { return x; }
	int GetY() const { return y; }

	std::bitset<REGION_WIDTH*REGION_HEIGHT>* GetSolidBitset() { return &solid; }
private:
	const int x;
	const int y;

	type_t tiles[REGION_WIDTH][REGION_HEIGHT][REGION_DEPTH];
	std::bitset<REGION_WIDTH*REGION_HEIGHT> solid;
};

//the memory footprint of the tile and solid data; not including any metadata
constexpr int REGION_FOOTPRINT = REGION_WIDTH * REGION_HEIGHT * REGION_DEPTH * sizeof(Region::type_t) + REGION_SOLID_FOOTPRINT;

#endif
