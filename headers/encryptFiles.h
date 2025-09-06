// Including the header files 
#include <iostream>
#include <fstream>
#include <openssl/evp.h>
#include <openssl/rand.h>

// Creating a function for encrypting the files 
void encrypt(const std::string& inputFile, const std::string& outputFile, const std::string& key) {
    // Setting the cipher text 
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new(); 
    unsigned char iv[EVP_MAX_IV_LENGTH]; 
    unsigned char buffer[1024]; 
    unsigned char ciphertext[1024 + EVP_MAX_BLOCK_LENGTH]; // Adjusted size for ciphertext
    int len; 
    int ciphertext_len; 

    // Generate a random IV 
    if (!RAND_bytes(iv, sizeof(iv))) {
        std::cerr << "Error generating IV." << std::endl; 
        return; 
    }

    // Open input and output files 
    std::ifstream inFile(inputFile, std::ios::binary); 
    std::ofstream outFile(outputFile, std::ios::binary); 

    // Check if files are opened successfully
    if (!inFile.is_open() || !outFile.is_open()) {
        std::cerr << "Error opening files." << std::endl; 
        return; 
    }

    // Write the IV to the output file 
    outFile.write(reinterpret_cast<char*>(iv), sizeof(iv)); 

    // Initialize encryption 
    if (EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), nullptr, reinterpret_cast<const unsigned char*>(key.c_str()), iv) != 1) {
        std::cerr << "Error initializing encryption." << std::endl; 
        return; 
    }

    // Read from input file and encrypt 
    while (inFile.read(reinterpret_cast<char*>(buffer), sizeof(buffer))) {
        if (EVP_EncryptUpdate(ctx, ciphertext, &len, buffer, inFile.gcount()) != 1) {
            std::cerr << "Error during encryption." << std::endl; 
            return; 
        }
        outFile.write(reinterpret_cast<char*>(ciphertext), len);
    }

    // Finalize encryption 
    if (EVP_EncryptFinal_ex(ctx, ciphertext + len, &len) != 1) {
        std::cerr << "Error finalizing encryption." << std::endl; 
        return; 
    }
    outFile.write(reinterpret_cast<char*>(ciphertext), len); 

    // Clean up 
    EVP_CIPHER_CTX_free(ctx); 
    inFile.close(); 
    outFile.close(); 
}
