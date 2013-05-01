#ifndef SURFACEMANAGER_HPP_
#define SURFACEMANAGER_HPP_

#include "SDL/SDL.h"

#include <map>
#include <string>

class SurfaceManager {
public:
	SurfaceManager();
	~SurfaceManager();

	SDL_Surface* Load(std::string key, std::string fname);
	SDL_Surface* Reload(std::string key, std::string fname);
	SDL_Surface* Get(std::string key);
	SDL_Surface* Set(std::string key, SDL_Surface* ptr);
	void Free(std::string key);
	void FreeAll();
private:
	SDL_Surface* LoadSurface(std::string key, std::string fname);
	typedef std::map<std::string, SDL_Surface*> mapType;
	mapType surfaceMap;
};

#endif