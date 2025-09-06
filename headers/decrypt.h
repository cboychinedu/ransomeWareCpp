#include <iostream>
#include <fstream>
#include <openssl/evp.h>

void decrypt(const std::string& inputFile, const std::string& outputFile, const std::string& key) {
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    unsigned char iv[EVP_MAX_IV_LENGTH];
    unsigned char buffer[1024];
    unsigned char plaintext[1024 + EVP_MAX_BLOCK_LENGTH];
    int len;
    int plaintext_len;

    // Open input and output files
    std::ifstream inFile(inputFile, std::ios::binary);
    std::ofstream outFile(outputFile, std::ios::binary);

    // Read the IV from the input file
    inFile.read(reinterpret_cast<char*>(iv), sizeof(iv));

    // Initialize decryption
    EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), nullptr, reinterpret_cast<const unsigned char*>(key.c_str()), iv);

    // Read from input file and decrypt
    while (inFile.read(reinterpret_cast<char*>(buffer), sizeof(buffer))) {
        EVP_DecryptUpdate(ctx, plaintext, &len, buffer, inFile.gcount());
        outFile.write(reinterpret_cast<char*>(plaintext), len);
    }

    // Finalize decryption
    EVP_DecryptFinal_ex(ctx, plaintext + len, &len);
    outFile.write(reinterpret_cast<char*>(plaintext), len);

    // Clean up
    EVP_CIPHER_CTX_free(ctx);
    inFile.close();
    outFile.close();
}