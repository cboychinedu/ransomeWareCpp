// Including the header files 
#include <iostream>
#include <fstream>
#include <openssl/evp.h>
#include <openssl/rand.h>

// Creating a function for encrypting the files 
void encrypt(const std::string& inputFile, const std::string& outputFile, const std::string& key) {
	// Setting the cipher text 
	EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new(); 
	unsigned char iv[EVP_MAX_IV_LENGHT]; 
	unsigned char buffer[1024]; 
	unsigned char ciphertext[1024 + EVP_MAX_BLOCK_LENGHT]; 
	int len; 
	int ciphertext_len; 

	// Generate a ranodm IV 
	if (!RAND_bytes(iv, sizeof(iv))) {
		std::cerr << "Error generating IV. " << std::endl; 
		return; 

	}

	// Open input and output files 
	std::ifstream inFile(inputFile, std::ios::binary); 
	std::ofstream outFile(outputFile, std::ios::binary); 

	// Write the IV to the ouput file 
	outputFile.write(reinterpret_cast<char*>(iv), sizeof(iv)); 

	// Initailize encryption 
	EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), nullptr, reinterpret_cast<const unsigned char*>(key.c_str()), iv); 

	// Read from input file and encrypt 
	while (inFile.read(reinterpret_cast<char*>(buffer), sizeof(buffer))) {
		EVP_EncryptUpdate(ctx, ciphertext, &len, buffer, inFile.gcount());
        outFile.write(reinterpret_cast<char*>(ciphertext), len);
    }

    // Finalize encryption 
    EVP_EncryptionFinal_ex(ctx, ciphertext + len, &len); 
    outFile.write(reinterpret_cast<char*>(ciphertext), len); 

    // clean up 
    EVP_CIPHER_CTX_free(ctx); 
    inFile.close(); 
    outFile.close(); 
    
}