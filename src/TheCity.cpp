#include <iostream>
#include <SDL2/SDL.h>
#include "../include/res_path.h"
#include "../include/cleanup.h"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "CharacterClasses/MainCharacter.h"
//#include "CharacterClasses/NPCCommon.h"
//#include "Maps/BaseMap.h"

/*
 * Lesson 0: Test to make sure SDL is setup properly
 */

const int SCREEN_WIDTH  = 640;
const int SCREEN_HEIGHT = 480;
const int TILE_SIZE=40;

/**
* Log an SDL error with some error message to the output stream of our choice
* @param os The output stream to write the message to
* @param msg The error message to write, format will be msg error: SDL_GetError()
*/
void logSDLError(std::ostream &os, const std::string &msg){
	os << msg << " error: " << SDL_GetError() << std::endl;
}

/**
* Loads a BMP image into a texture on the rendering device
* @param file The BMP image file to load
* @param ren The renderer to load the texture onto
* @return the loaded texture, or nullptr if something went wrong.
*/
// SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *ren){
// 	//Initialize to nullptr to avoid dangling pointer issues
// 	SDL_Texture *texture = nullptr;
// 	//Load the image
// 	SDL_Surface *loadedImage = SDL_LoadBMP(file.c_str());
// 	//If the loading went ok, convert to texture and return the texture
// 	if (loadedImage != nullptr){
// 		texture = SDL_CreateTextureFromSurface(ren, loadedImage);
// 		SDL_FreeSurface(loadedImage);
// 		//Make sure converting went ok too
// 		if (texture == nullptr){
// 			logSDLError(std::cout, "CreateTextureFromSurface");
// 		}
// 	}
// 	else {
// 		logSDLError(std::cout, "LoadBMP");
// 	}
// 	return texture;
// }

/**
* Loads an image into a texture on the rendering device
* @param file The image file to load
* @param ren The renderer to load the texture onto
* @return the loaded texture, or nullptr if something went wrong.
*/
SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *ren){
	SDL_Texture *texture = IMG_LoadTexture(ren, file.c_str());
	if (texture == nullptr){
		logSDLError(std::cout, "LoadTexture");
	}
	return texture;
}




// /**
// * Draw an SDL_Texture to an SDL_Renderer at position x, y, preserving
// * the texture's width and height
// * @param tex The source texture we want to draw
// * @param ren The renderer we want to draw to
// * @param x The x coordinate to draw to
// * @param y The y coordinate to draw to
// */
// void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y){
// 	//Setup the destination rectangle to be at the position we want
// 	SDL_Rect dst;
// 	dst.x = x;
// 	dst.y = y;
// 	//Query the texture to get its width and height to use
// 	SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
// 	SDL_RenderCopy(ren, tex, NULL, &dst);
// }

/**
* Draw an SDL_Texture to an SDL_Renderer at position x, y, with some desired
* width and height
* @param tex The source texture we want to draw
* @param ren The renderer we want to draw to
* @param x The x coordinate to draw to
* @param y The y coordinate to draw to
* @param w The width of the texture to draw
* @param h The height of the texture to draw
*/
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h){
	//Setup the destination rectangle to be at the position we want
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	dst.w = w;
	dst.h = h;
	SDL_RenderCopy(ren, tex, NULL, &dst);
}

SDL_Texture *loadFromRenderedText(SDL_Renderer *gRenderer, std::string textureText)
{
	//Get rid of preexisting texture
	//free();

    //Set text color as black
    SDL_Color textColor = { 0, 0, 0, 0xFF };

    //Initialize SDL_ttf
    if( TTF_Init() == -1 )
    {
        printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
        //return false;
        return NULL;
    }
    
    TTF_Font *gFont = TTF_OpenFont( "/home/steven/Projects/TheCity/src/OpenSans-Regular.ttf", 10 );
	
    if (gFont==NULL)
        std::cout<<"gFont is Null";
    if(textureText=="")
        std::cout<<"No Text";
    //if(textColor==nullptr)
    //    std::cout<<"no Color";

    //Render text surface
	SDL_Surface *textSurface = TTF_RenderText_Blended_Wrapped( gFont, textureText.c_str(), textColor,TILE_SIZE );
    //SDL_Surface *textSurface = TTF_RenderText_Solid( gFont, textureText.c_str(), textColor );
    
    SDL_Texture *mTexture;
	if( textSurface != NULL )
	{
		//Create texture from surface pixels
        mTexture = SDL_CreateTextureFromSurface( gRenderer, textSurface );
		if( mTexture == NULL )
		{
			printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
		}
		else
		{
			//Get image dimensions
			//mWidth = textSurface->w;
			//mHeight = textSurface->h;
            TTF_CloseFont(gFont);
		}

		//Get rid of old surface
		SDL_FreeSurface( textSurface );
	}
	else
	{
		printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
	}

	//Return success
	//return mTexture!=NULL;
    return mTexture;
    //return textSurface;
}

/**
* Draw an SDL_Texture to an SDL_Renderer at position x, y, preserving
* the texture's width and height
* @param tex The source texture we want to draw
* @param ren The renderer we want to draw to
* @param x The x coordinate to draw to
* @param y The y coordinate to draw to
*/
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y){
	int w, h;
	SDL_QueryTexture(tex, NULL, NULL, &w, &h);
	renderTexture(tex, ren, x, y, w, h);
}


void drawBorderRectangle(SDL_Renderer *renderer, int X, int Y, int W, int H){

    SDL_Rect clip;
    clip.x = X;
    clip.y = Y;
    clip.w = W;
    clip.h = H;

    

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderSetClipRect(renderer, &clip);
    SDL_RenderFillRect(renderer,&clip);

    //Border must come first
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_Rect border = {X,Y,W,H};
    SDL_RenderDrawRect(renderer,&border);

}

void drawDialogBox(SDL_Renderer *renderer,std::string inputText){
    SDL_Texture *theText=loadFromRenderedText(renderer, inputText.c_str());
    //SDL_Surface *textSurface=loadFromRenderedText(renderer, inputText.c_str());
    SDL_Rect destination;

    int X=3*TILE_SIZE;
    int Y=3*TILE_SIZE;
    int W=5*TILE_SIZE;
    int H=2*TILE_SIZE;

    int TextWidth=W;
    int TextHeight=H; //lines in box

    destination.x = X + W - TextWidth;
    destination.y = Y+10;
    destination.w = TextWidth;
    destination.h = TextHeight;

    drawBorderRectangle(renderer,X,Y,W,H);
    
    //SDL_Surface * glyph = SDL_CreateRGBSurface(0, 100, 100, 32, 0, 0, 0, 0);
    //SDL_FillRect(glyph, NULL, SDL_MapRGB(glyph->format, 255, 255, 255));

    //SDL_Surface *screen = SDL_GetWindowSurface(window);
    
    //SDL_BlitSurface(glyph,NULL,glyph,NULL);


    SDL_RenderCopy(renderer, theText, NULL, &destination);
    SDL_RenderSetClipRect(renderer, NULL); //clip is to keep text in box
    SDL_DestroyTexture(theText);
    //SDL_FreeSurface(textSurface);
    //SDL_FreeSurface(glyph);
}


int main(int, char**){
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
	logSDLError(std::cout, "SDL_Init");
	return 1;
    }

    SDL_Window *window = SDL_CreateWindow("Lesson 2", 100, 100, SCREEN_WIDTH,
        SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr){
        logSDLError(std::cout, "CreateWindow");
        SDL_Quit();
        return 1;
    }
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr){
        logSDLError(std::cout, "CreateRenderer");
        cleanup(window);
        SDL_Quit();
        return 1;
    }

    if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG){
        logSDLError(std::cout, "IMG_Init");
        SDL_Quit();
        return 1;
    }

    const std::string resPath = getResourcePath("img");
    SDL_Texture *background = loadTexture(resPath + "tree.png", renderer);
    SDL_Texture *stonepath = loadTexture(resPath + "stonepath.png",renderer);
    SDL_Texture *randomperson = loadTexture(resPath+ "RandomPerson.png",renderer);

    SDL_Texture *image = loadTexture(resPath + "Joe.png", renderer);
    MainCharacter *Joe = new MainCharacter();

    //Make sure they both loaded ok
    if (background == nullptr || image == nullptr){
        cleanup(background, image, renderer, window);
        IMG_Quit();
        SDL_Quit();
        return 1;
    }
    
    //Determine how many tiles we'll need to fill the screen
    int xTiles = SCREEN_WIDTH / TILE_SIZE;
    int yTiles = SCREEN_HEIGHT / TILE_SIZE;

    

    int iW, iH;
    SDL_QueryTexture(image, NULL, NULL, &iW, &iH);
    int x = SCREEN_WIDTH / 2 - iW / 2;
    int y = SCREEN_HEIGHT / 2 - iH / 2;

    //renderTexture(image, renderer, x, y);
    //SDL_RenderPresent(renderer);
    //SDL_Delay(2000);
    // //Our event structure
	SDL_Event e;
	//For tracking if we want to quit
	bool quit = false;

    BaseMap *baseMap = new BaseMap();

	while (!quit){
	//Read any events that occured, for now we'll just quit if any event occurs
        while (SDL_PollEvent(&e)){
                //If user closes the window
                if (e.type == SDL_QUIT){
                    quit = true;
                }
                
                Joe->handleEvent(e);

                //If user clicks the mouse
                if (e.type == SDL_MOUSEBUTTONDOWN){
                    quit = true;
                }
        }

        

		//Rendering
		SDL_RenderClear(renderer);
		//Draw the image

        
        Joe->currentMap=baseMap;
        //std::cout<<baseMap->tileTypes[0][0];
        //Draw the tiles by calculating their positions
        for (int i = 0; i < xTiles * yTiles; ++i){
            int x = i % xTiles;
            int y = i / xTiles;
            //std::cout << std::to_string(x) + ", " + std::to_string(y)<<std::endl;
            switch(baseMap->tileTypes[y][x]){
            case 0:
                renderTexture(background, renderer, x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE,
                TILE_SIZE);
                break;
            case 1:
                renderTexture(stonepath, renderer, x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE,
                TILE_SIZE);
                break;
            case 2:
            case 3:
                renderTexture(randomperson, renderer, x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE,
                TILE_SIZE);
                break;
            }
        }

		renderTexture(image, renderer, Joe->PosX, Joe->PosY,TILE_SIZE,TILE_SIZE);
        
        if(Joe->dialogOn){
            //renderTexture(dialog1,renderer,5*TILE_SIZE,5*TILE_SIZE,5*TILE_SIZE,2*TILE_SIZE);
            if(Joe->currentDialogString!="")            
                drawDialogBox(renderer,Joe->currentDialogString);
        }

		//Update the screen
		SDL_RenderPresent(renderer);
	}

    cleanup(background,stonepath,randomperson, image, renderer, window);
    delete(Joe);
    delete(baseMap);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
	return 0;
}