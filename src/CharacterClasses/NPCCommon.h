#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <vector>
//#include "../Maps/BaseMap.h"
class NPCCommon{
    public:
        int PosX;
        int PosY;
        double POS_DISPLACE;
        NPCCommon();
        NPCCommon(int NPCIndex); //create NPC based on index
        //BaseMap *currentMap;
        void handleEvent(SDL_Event& e);
        bool checkCollision(std::string direction);
        std::vector<std::string> dialogProgression;
    private:
        bool checkIndividualCollision(int theXPos, int theYPos);

};