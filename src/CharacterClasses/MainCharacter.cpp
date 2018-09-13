#include "MainCharacter.h"

const int SCREEN_WIDTH  = 640;
const int SCREEN_HEIGHT = 480;
const int TILE_SIZE=40;

MainCharacter::MainCharacter(){
    PosX=0;
    PosY=0;
    POS_DISPLACE=2;
    faceDirection="None";
    dialogOn=false;
    dialogIndex=0; //start for dialog progression of MC with someone else
    currentDialogString="";
    adjacentCharacter=NULL;
}

void MainCharacter::handleEvent(SDL_Event& e)
{
    

    //If user presses any key
    if (e.type == SDL_KEYDOWN){

        //std::cout<<"The adjacent code is "+std::to_string(getAdjacentCode())<<std::endl;

        int n, count = 0;
        const uint8_t *keystate = SDL_GetKeyboardState(&count);



        if(keystate[SDL_SCANCODE_LEFT])
        {
            faceDirection="Left";
        }

        if(keystate[SDL_SCANCODE_RIGHT] )
        {
            faceDirection="Right";
        }

        if(keystate[SDL_SCANCODE_UP])
        {
            faceDirection="Up";
        }
        if(keystate[SDL_SCANCODE_DOWN] )
        {
            faceDirection="Down";
        }


        if (keystate[SDL_SCANCODE_SPACE] && adjacentCharacter==NULL){

            adjacentCharacter=new NPCCommon(getAdjacentCode());
            std::cout<< "The adjacent code is " + std::to_string(getAdjacentCode()) + " . Direction is "+faceDirection<<std::endl;
        }

        if(keystate[SDL_SCANCODE_SPACE] && adjacentCharacter!=NULL){
            //std::cout<<"dialog area entered"<<std::endl;
            if(dialogIndex >= (long long)adjacentCharacter->dialogProgression.size()){
                //std::cout<<"Dialog shutdown."<<std::endl;
                dialogOn=false;
                dialogIndex=0;
                currentDialogString="";
                delete adjacentCharacter;
                adjacentCharacter=NULL;
            }
            else{
                dialogOn=true;
                
                std::string thisString = adjacentCharacter->dialogProgression[dialogIndex];
                if(thisString.length()>20){
                    adjacentCharacter->dialogProgression.insert(adjacentCharacter->dialogProgression.begin()+dialogIndex+1,thisString.substr(20,thisString.length()-20));
                    adjacentCharacter->dialogProgression[dialogIndex]=adjacentCharacter->dialogProgression[dialogIndex].substr(0,20);
                }

                currentDialogString=adjacentCharacter->dialogProgression[dialogIndex];
                dialogIndex++;
            }

        }

        int margin=0;
        if(PosX<0 ){
            PosX+=POS_DISPLACE+margin;
        }

        else if(PosY<0 )
        {
            PosY+=POS_DISPLACE+margin;
        }
        else if(PosX+TILE_SIZE>SCREEN_WIDTH )
        {
            PosX-=POS_DISPLACE-margin;
        }
        else if(PosY+TILE_SIZE>SCREEN_HEIGHT )
        {
            PosY-=POS_DISPLACE-margin;
        }
        else{
            //if(!checkCollision()){
                //continuous-response keys
                if(keystate[SDL_SCANCODE_LEFT] && ! checkCollision("LEFT"))
                {
                    PosX -= POS_DISPLACE;
                }
                else
                    PosX+=POS_DISPLACE+margin;

                if(keystate[SDL_SCANCODE_RIGHT] && ! checkCollision("RIGHT"))
                {
                    PosX += POS_DISPLACE;
                }
                else
                    PosX -=POS_DISPLACE-margin;

                if(keystate[SDL_SCANCODE_UP] && ! checkCollision("UP"))
                {
                    PosY -= POS_DISPLACE;
                }
                else
                    PosY+=POS_DISPLACE+margin;

                if(keystate[SDL_SCANCODE_DOWN] && ! checkCollision("DOWN"))
                {
                    PosY += POS_DISPLACE;
                }
                else
                    PosY-=POS_DISPLACE-margin;

                std::cout<<"Current position is X:" + std::to_string(PosX) + " Y:" + std::to_string(PosY)<<std::endl;
            //}
        }

        //checkCollision();
        // if(checkCollision()){
        //     if(keystate[SDL_SCANCODE_LEFT]){
        //         PosX+=POS_DISPLACE;
        //     }

        //     else if(keystate[SDL_SCANCODE_UP])
        //     {
        //         PosY+=POS_DISPLACE;
        //     }
        //     else if(keystate[SDL_SCANCODE_RIGHT])
        //     {
        //         PosX-=POS_DISPLACE;
        //     }
        //     else if(keystate[SDL_SCANCODE_DOWN])
        //     {
        //         PosY-=POS_DISPLACE;
        //     }
        // }

        // switch( e.key.keysym.sym )
        // {
        //     case SDLK_UP: Joe->PosY -= POS_DISPLACE; break;
        //     case SDLK_DOWN: Joe->PosY += POS_DISPLACE; break;
        //     case SDLK_LEFT: Joe->PosX -= POS_DISPLACE; break;
        //     case SDLK_RIGHT: Joe->PosX += POS_DISPLACE; break;
            
            
        // }

        // if(e.key.keysym.sym==SDLK_RIGHT){
        //     Joe->PosX+=2;
        // }

        // if(e.key.keysym.sym==SDLK_LEFT){
        //     Joe->PosX-=2;
        // }
        // if(e.key.keysym.sym==SDLK_UP){
        //     Joe->PosY-=2;
        // }
        // if(e.key.keysym.sym==SDLK_DOWN){
        //     Joe->PosY+=2;
        // }
    }
}





bool MainCharacter::checkCollision(std::string direction){
    int margin=1;

    bool LeftCoord = checkIndividualCollision(PosX-margin,PosY);
    bool RightCoord = checkIndividualCollision(PosX+TILE_SIZE+margin,PosY);
    bool BotCoord = checkIndividualCollision(PosX,PosY+TILE_SIZE+margin);
    bool UpCoord = checkIndividualCollision(PosX,PosY-margin);
    

    if(direction=="LEFT" && LeftCoord)
        return true;

    if(direction=="RIGHT" && RightCoord)
        return true;
    
    if(direction=="UP" && UpCoord)
        return true;
    
    if(direction=="DOWN" && BotCoord)
        return true;

    return false;
    
}

int MainCharacter::getAdjacentCode(){
    int xTile = PosX/TILE_SIZE;
    int yTile = PosY/TILE_SIZE;
    
    int xTileCorrect=0;
    int yTileCorrect=0;

    int xCorrection=0, yCorrection=0;
    if(xTile>=0 && yTile>=0)
    {
        int n, count = 0;
        const uint8_t *keystate = SDL_GetKeyboardState(&count);

        if(faceDirection=="Left")
        {
            xCorrection=-1;
        }
        if(faceDirection=="Right")
        {
            xCorrection=1;
        }
        if(faceDirection=="Up")
        {
            yCorrection=-1;
        }
        if(faceDirection=="Down")
        {
            yCorrection=1;
        }

        xTileCorrect=xTile+xCorrection;
        yTileCorrect=yTile+yCorrection;
        std::cout<<//std::to_string(PosX)+", "+std::to_string(PosY)+":"+
        //         std::to_string(xTile) +", " +std::to_string(yTile)+":"+
        //         std::to_string(xCorrection) +", " +std::to_string(yCorrection)+
                   std::to_string(xTileCorrect) +", " +std::to_string(yTileCorrect)//+
                   <<std::endl;

        if((xTile>=0 && yTile>=0) ){//&& (xTileCorrect>=0 && yTileCorrect>=0)){
            int tileIndex = currentMap->tileTypes[yTileCorrect][xTileCorrect];
            std::cout<<"The adjacent tile index is " + std::to_string(tileIndex)<<std::endl;
            //int tileIndexCorrect=currentMap->tileTypes[yTileCorrect][xTileCorrect];
            //if(tileIndex==0 || tileIndexCorrect==0)
                //tileIndex=0;
            
            return tileIndex;
        }
    }
}

bool MainCharacter::checkIndividualCollision(int theXPos, int theYPos){
    int xTile = theXPos/TILE_SIZE;
    int yTile = theYPos/TILE_SIZE;
    
    int xTileCorrect=0;
    int yTileCorrect=0;

    int xCorrection=0, yCorrection=0;
    if(xTile>=0 && yTile>=0)
    {
        int n, count = 0;
        const uint8_t *keystate = SDL_GetKeyboardState(&count);

        if(keystate[SDL_SCANCODE_LEFT])
        {
            xCorrection=-1;
        }
        if(keystate[SDL_SCANCODE_RIGHT])
        {
            xCorrection=1;
        }
        if(keystate[SDL_SCANCODE_UP])
        {
            yCorrection=-1;
        }
        if(keystate[SDL_SCANCODE_DOWN])
        {
            yCorrection=1;
        }

        xTileCorrect=xTile+xCorrection;
        yTileCorrect=yTile+yCorrection;
        std::cout<<std::to_string(theXPos)+", "+std::to_string(theYPos)+":"
                 +std::to_string(xTile) +", " +std::to_string(yTile)+":"
        //         +std::to_string(xCorrection) +", " +std::to_string(yCorrection)
                <<std::endl;

        if((xTile>=0 && yTile>=0) ){//&& (xTileCorrect>=0 && yTileCorrect>=0)){
            int tileIndex = currentMap->tileTypes[yTile][xTile];
            //int tileIndexCorrect=currentMap->tileTypes[yTileCorrect][xTileCorrect];
            //if(tileIndex==0 || tileIndexCorrect==0)
                //tileIndex=0;

            switch (tileIndex){
                case 0:
                    //std::cout<<"A tree"<<std::endl<<std::endl;
                    return true;
                    break;
                case 1:
                    //std::cout<<"A path"<<std::endl<<std::endl;
                    return false;
                    break;
                default:
                    return true;
                    break;
            }
        }

        
    }
}
