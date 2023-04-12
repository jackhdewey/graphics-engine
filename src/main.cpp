#include "SDLGraphicsProgram.hpp"

int main(int argc, char** argv){
	// Create our SDLGraphicsProgram
	SDLGraphicsProgram mySDLGraphicsProgram(2560, 1440);
    // Initialize the scene
    mySDLGraphicsProgram.InitScene();
	// Main Loop
	mySDLGraphicsProgram.Loop();

	return 0;
}
