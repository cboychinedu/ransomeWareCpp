#include <iostream>
#include <string>

// Creating a function for checking the operating system 
std::string checkOperatingSystem() {
	// Setting the result 
	std::string result; 

	// Checking if the operating system is windows
	#ifdef _WIN32
		result = "windows"; 

	// Checking if the operating system is linux 
	#elif defined(__linux__)
		result = "linux"; 

	// Checking if the operating system is unknown 
	#else
		result = "unknown"; 
	#endif

	// returning the result; 
	return result; 

}