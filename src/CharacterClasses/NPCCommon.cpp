#include "NPCCommon.h"

const int SCREEN_WIDTH  = 640;
const int SCREEN_HEIGHT = 480;
const int TILE_SIZE=40;

NPCCommon::NPCCommon(){
    PosX=0;
    PosY=0;
    POS_DISPLACE=2;
    dialogProgression=std::vector<std::string>{"Hello.","Do you know where you are?"};
}

NPCCommon::NPCCommon(int NPCIndex){
    PosX=0;
    PosY=0;
    POS_DISPLACE=2;
    switch(NPCIndex){
        case 2:
            dialogProgression=std::vector<std::string>{"Hello.","Do you know where you are?"};
            break;
        case 3:
            dialogProgression=std::vector<std::string>{"Bill sent you didn't he?",
                                                       "You want to know where you are don't you?",
                                                       "Or perhaps more importantly, why you are here.",
                                                       "The truth is we can tell you where you are but we don't know why you are here.",
                                                       "That is something you will have to discover for yourself."};
            break;
    }
}