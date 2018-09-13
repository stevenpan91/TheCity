CXX = g++
# Update these paths to match your installation
# You may also need to update the linker option rpath, which sets where to look for
# the SDL2 libraries at runtime to match your install
#SDL_LIB = -L/usr/local/lib -lSDL2 -lSDL2_image -Wl,-rpath=/usr/local/lib
SDL_LIB = -L/usr/local/lib -lSDL2 -lSDL2_image -lSDL2_ttf
SDL_INCLUDE = -I/usr/local/include
# You may need to change -std=c++11 to -std=c++0x if your compiler is a bit older
CXXFLAGS = -Wall -c -std=c++11 $(SDL_INCLUDE)
LDFLAGS = $(SDL_LIB)
EXE = TheCity

all: $(EXE)


$(EXE): TheCity.o MainCharacter.o NPCCommon.o Maps.o

	$(CXX) $^ $(LDFLAGS) -o $@

TheCity.o: src/TheCity.cpp

	$(CXX) -c $(CXXFLAGS) $< -o $@ -g

MainCharacter.o: src/CharacterClasses/MainCharacter.cpp src/CharacterClasses/MainCharacter.h

	$(CXX) -c $(CXXFLAGS) $< -o $@ -g

NPCCommon.o: src/CharacterClasses/NPCCommon.cpp src/CharacterClasses/NPCCommon.h

	$(CXX) -c $(CXXFLAGS) $< -o $@ -g

Maps.o: src/Maps/*.cpp src/Maps/*.h

	$(CXX) -c $(CXXFLAGS) $< -o $@ -g 

clean:

	rm *.o && rm $(EXE)