/**
 * The main function for our graphics program.
 */

#include "SDLGraphicsProgram.hpp"

int main(int argc, char** argv){
	// Create an instance of an object for a SDLGraphicsProgram
	SDLGraphicsProgram mySDLGraphicsProgram(1280, 720);
	// Run our program forever
	mySDLGraphicsProgram.Loop();
	// When our program ends, it will exit scope, the
	// destructor will then be called and clean up the program.
	return 0;
}
