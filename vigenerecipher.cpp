// Vigenere Cipher, by Al Sweigart 
// The Vigenere cipher is a polyalphabetic substitution cipher that was
// powerful enough to remain unbroken for centuries.
// This code is available at https ://nostarch.com/big-book-small-python-programming
// #80 VIGENERE CIPHER

#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

char upper(char symbol);
char lower(char symbol);
string translateMessage(string message, string key, string mode);
string encryptMessage(string message, string key);
string decryptMessage(string message, string key);

// Every possible symbol that can be encrypted / decrypted:
string LETTERS = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

int main() {
    cout << "Vigenere Cipher, by Al Sweigart\n";
    cout << "The Viegenere cipher is a polyalphabetic substitution cipher that was\n";
    cout << "powerful enough to remain unbroken for centuries.\n";

    // Let the user specify if they are encrypting or decrypting:
    string response;
    string myMode;
    while (1) { // Keep asking until the user enters e or d.
        cout << "Do you want to (e)ncrypt or (d)ecrypt?\n";
        std::cout << "> ";
        getline(cin, response);
        transform(response.begin(), response.end(), response.begin(), ::tolower);
        if (response[0] == 'e') {
            myMode = "encrypt";
            break;
        } else if (response[0] == 'd') {
            myMode = "decrypt";
            break;
        }
        cout << "Please enter the letter e or d.\n";
    }
    // Let the user specify the key to use:
    string myKey;
    while (1) { // Keep asking until the user enters a valid key.
        cout << "Please specify the key to use.\n";
        cout << "It can be a word or any combination of letters:\n";
        std::cout << "> ";
        getline(cin, response);
        transform(response.begin(), response.end(), response.begin(), ::toupper);
        bool flagisalpha = true;
        for (char c : response) {
            if (!((c >= 'A' && c <= 'Z') || c == ' ')) {
                flagisalpha = false;
            }
        }
        if (flagisalpha) {
            myKey = response;
            break;
        }
    }
    
    // Let the user specify the message to encrypt/decrypt:
    cout << "Enter the message to " << myMode << ".\n";
    string myMessage;
    std::cout << "> ";
    getline(cin, myMessage);

    // Perform the encryption/decryption:
    string translated;
    if (myMode == "encrypt") {
        translated = encryptMessage(myMessage, myKey);
    } else if (myMode == "decrypt") {
        translated = decryptMessage(myMessage, myKey);
    }

    cout << myMode << "ed message:\n";
    cout << translated << '\n';

    return 0;
}

char upper(char symbol) {
    if (symbol >= 'A' && symbol <= 'Z') {
        return symbol;
    }

    if (symbol >= 'a' && symbol <= 'z') {
        return (symbol - 'a') + 'A';
    }

    return symbol;
}

char lower(char symbol) {
    if (symbol >= 'a' && symbol <= 'z') {
        return symbol;
    }

    if (symbol >= 'A' && symbol <= 'Z') {
        return (symbol - 'A') + 'a';
    }

    return symbol;
}

string translateMessage(string message, string key, string mode) {
    // Encrypt or decrypt the message using the key.
    string translated = ""; // Stores the encrypted/decrypted message string.
    int keyIndex = 0;
    transform(key.begin(), key.end(), key.begin(), ::toupper);

    for (char symbol : message) { // Loop through each character in message.
        int num = LETTERS.find(upper(symbol));
        if (num != string::npos) { // -1 means symbol.upper() was not in LETTERS.
            if (mode == "encrypt") {
                // Add if encrypting:
                num += LETTERS.find(key[keyIndex]);
            } else if (mode == "decrypt") {
                // Subtract if decrypti
                num -= LETTERS.find(key[keyIndex]);
                
            }
            while (num < 0) {
                num = num + 26;
            }

            num %= LETTERS.size();
            // Add the encrypted/decrypted symbol to translated.
            if (symbol >= 'A' && symbol <= 'Z') {
                translated.push_back(LETTERS[num]);
            } else if (symbol >= 'a' && symbol <= 'z') {
                translated.push_back(lower(LETTERS[num]));
            }

            ++keyIndex; // Move to the next letter in the key.
            if (keyIndex == key.size()) {
                keyIndex = 0;
            }
        } else {
            // Just add the symbol without encrypting/decrypting:
            translated.push_back(symbol);
        }
    }
    
    return translated;
}

string encryptMessage(string message, string key) {
    // Encrypt the message using the key.
    return translateMessage(message, key, "encrypt");
}

string decryptMessage(string message, string key) {
    // Decrypt the message using the key.
    return translateMessage(message, key, "decrypt");
}