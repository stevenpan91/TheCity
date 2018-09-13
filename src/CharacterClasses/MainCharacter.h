
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include "../Maps/BaseMap.h"
#include "NPCCommon.h"
class MainCharacter{
    public:
        int PosX;
        int PosY;
        double POS_DISPLACE; //how much MC moves
        MainCharacter();
        BaseMap *currentMap;
        void handleEvent(SDL_Event& e);
        bool checkCollision(std::string direction); //colliding with tile (for instance, NPC or tree)
        int getAdjacentCode(); //get tile code of what the MC is facing
        std::string faceDirection; //MC facing Left Right Up or Down
        bool dialogOn; //talking right now
        std::string currentDialogString;
    private:
        bool checkIndividualCollision(int theXPos, int theYPos);
        NPCCommon *adjacentCharacter;
        int dialogIndex; //index of how far along in dialog MC is with someone else
        

};