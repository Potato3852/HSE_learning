#include "crypto.hpp"

// Простое XOR-шифрование
std::string encrypt(const std::string& plaintext, const std::string& key) {
    std::string result = plaintext;
    for (size_t i = 0; i < plaintext.length(); ++i) {
        result[i] ^= key[i % key.length()];
    }
    return result;
}

// Дешифровка XOR-шифрования
std::string decrypt(const std::string& ciphertext, const std::string& key) {
    return encrypt(ciphertext, key);
} 