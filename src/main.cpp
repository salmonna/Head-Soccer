
#pragma once
#include "Controller.h"
#include <exception>
#include <iostream>

// The main function of the program.
//----------------------------------------------------------------
int main() {

	try
	{
		// Creates an instance of the Controller class.
		Controller Controller;
	}
	catch (const std::exception & e)
	{
		std::cout << e.what() << std::endl;
	}
    
    // Indicates successful completion of the program.
    return EXIT_SUCCESS;
}
