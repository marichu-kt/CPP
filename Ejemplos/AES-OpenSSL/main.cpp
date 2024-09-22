#include <openssl/aes.h>      // FUNCIONES CIFRADO AES
#include <openssl/err.h>      // GESTIONAR ERRORES
#include <openssl/rand.h>     // GENERAR VALORES ALEATORIOS
#include <iostream>           // ENTRADA/SALIDA DE DATOS
#include <cstring>            // FUNCIONES DE MEMORIA
#include <iomanip>            // FORMATEAR SALIDA EN HEXADECIMAL
#include <vector>             // ESTRUCTURAS DINÁMICAS (VECTORES)

// FUNCIÓN PARA MANEJAR LOS ERRORES
void handleErrors() {
    ERR_print_errors_fp(stderr); // IMPRIME ERRORES
    abort();  // FINALIZA PROGRAMA
}

// FUNCIÓN QUE CIFRA USANDO AES
void AES_encrypt(const unsigned char *key, const unsigned char *plaintext, unsigned char *ciphertext, int len) {
    AES_KEY encryptKey;
    // ESTABLECE LA CLAVE DE CIFRADO AES DE 128 BITS (16 BYTES)
    if (AES_set_encrypt_key(key, 128, &encryptKey) < 0) handleErrors();
    
    // CIFRA EN BLOQUES DE 16 BYTES
    for (int i = 0; i < len; i += AES_BLOCK_SIZE) {
        AES_encrypt(plaintext + i, ciphertext + i, &encryptKey); // CIFRA UN BLOQUE
    }
}

// FUNCIÓN QUE DESCIFRA USANDO AES
void AES_decrypt(const unsigned char *key, const unsigned char *ciphertext, unsigned char *plaintext, int len) {
    AES_KEY decryptKey;
    // ESTABLECE LA CLAVE DE DESCIFRADO AES DE 128 BITS (16 BYTES)
    if (AES_set_decrypt_key(key, 128, &decryptKey) < 0) handleErrors();
    
    // DESCIFRA EN BLOQUES DE 16 BYTES
    for (int i = 0; i < len; i += AES_BLOCK_SIZE) {
        AES_decrypt(ciphertext + i, plaintext + i, &decryptKey); // DESCIFRA UN BLOQUE
    }
}

// FUNCIÓN PARA IMPRIMIR DATOS EN FORMATO HEXADECIMAL
void printHex(const unsigned char *data, size_t len) {
    for (size_t i = 0; i < len; ++i) {
        // IMPRIME CADA BYTE COMO UN NÚMERO HEXADECIMAL DE 2 DÍGITOS
        std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)data[i];
    }
    std::cout << std::dec << std::endl;  // VUELVE A LA SALIDA EN FORMATO DECIMAL
}

int main() {
    unsigned char key[AES_BLOCK_SIZE]; // CLAVE DE 16 BYTES PARA AES
    std::string input;                 // VARIABLE PARA ALMACENAR EL MENSAJE DEL USUARIO

    // PEDIR AL USUARIO QUE INTRODUZCA UN MENSAJE A CIFRAR
    std::cout << "Introduce el mensaje a cifrar: ";
    std::getline(std::cin, input);  // LEE LA ENTRADA DEL USUARIO

    // AJUSTE PARA QUE EL TAMAÑO DEL MENSAJE SEA MÚLTIPLO DE 16 BYTES (AES_BLOCK_SIZE)
    int padded_len = ((input.length() / AES_BLOCK_SIZE) + 1) * AES_BLOCK_SIZE;
    std::vector<unsigned char> plaintext(padded_len);  // VECTOR PARA EL MENSAJE CON PADDING
    std::memcpy(plaintext.data(), input.c_str(), input.length());  // COPIA EL MENSAJE ORIGINAL
    
    // AÑADIR PADDING PARA QUE EL TAMAÑO SEA MÚLTIPLO DE 16 BYTES
    unsigned char padding_value = padded_len - input.length();
    std::memset(plaintext.data() + input.length(), padding_value, padding_value);  // RELLENA CON EL VALOR DE PADDING

    // VECTORES PARA ALMACENAR EL MENSAJE CIFRADO Y EL MENSAJE DESENCRIPTADO
    std::vector<unsigned char> ciphertext(padded_len);
    std::vector<unsigned char> decryptedtext(padded_len);

    // GENERAR UNA CLAVE ALEATORIA PARA AES
    if (!RAND_bytes(key, sizeof(key))) handleErrors();

    // CIFRAR EL MENSAJE
    AES_encrypt(key, plaintext.data(), ciphertext.data(), padded_len);
    // DESENCRIPTAR EL MENSAJE
    AES_decrypt(key, ciphertext.data(), decryptedtext.data(), padded_len);

    // ELIMINAR EL PADDING DESPUÉS DE LA DESENCRIPTACIÓN
    int unpadded_len = padded_len - decryptedtext[padded_len - 1];
    decryptedtext.resize(unpadded_len);  // AJUSTAR EL TAMAÑO DESPUÉS DE ELIMINAR EL PADDING

    // MOSTRAR LOS RESULTADOS
    std::cout << "Mensaje original: " << input << std::endl;  // MENSAJE ORIGINAL
    std::cout << "Mensaje cifrado (en hexadecimal): ";
    printHex(ciphertext.data(), ciphertext.size());  // IMPRIME EL TEXTO CIFRADO EN FORMATO HEXADECIMAL
    std::cout << "Mensaje desencriptado: " << std::string(decryptedtext.begin(), decryptedtext.end()) << std::endl;

    return 0;
}
