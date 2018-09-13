#include <iostream>
#include <SDL2/SDL.h>
#include <vector>
class BaseMap{
    public:
        BaseMap();
        void handleEvent(SDL_Event& e);
        //12 down x 16 across
        std::vector<std::vector<int>> tileTypes;

};