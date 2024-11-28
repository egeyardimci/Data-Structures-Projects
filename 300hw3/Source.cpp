#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

#define EMPTY "0"

class HashTable
{
public:
    HashTable(int size);
    int hash(std::string val);
    void insert(std::string val);
    bool search(std::string val);

private:
    int size = 0;
    std::vector<std::string> hashArray;
    void reHash();

};

HashTable::HashTable(int size)
{
    this->size = size;
    for (int i = 0; i < this->size; i++) {
        hashArray.push_back(EMPTY);
    }
}

int HashTable::hash(std::string val) {
    int hashValue = 0;

    for (char c : val) {
        hashValue = (hashValue * 31 + int(c)) % this->size;
    }

    hashValue = (hashValue * 31) % this->size;

    return hashValue;
}

void HashTable::insert(std::string val) {
    int hashValue = this->hash(val);

    while (true) {
        if (this->hashArray[hashValue] == EMPTY) {
            this->hashArray[hashValue] = val;
            break;
        }
        else {
            hashValue = ++hashValue % this->size;
        }
    }
}

bool HashTable::search(std::string val) {
    int hashValue = this->hash(val);

    while (true) {
        if (this->hashArray[hashValue] != val) {
            hashValue++;
            if (this->hashArray[hashValue] == EMPTY) {
                return false;
            }
            else if (this->hashArray[hashValue] == val) {
                return true;
            }
        }
        else {
            return true;
        }
    }
}

std::string getFlattenedImageFromFile(std::string fileName) {

    std::ifstream file(fileName);
    if (!file.is_open()) {
        std::cerr << "Could not open the file!" << std::endl;
    }

    std::string line;
    std::string sum;

    while (std::getline(file, line)) {
        sum += line;
    }

    file.close();

    std::string formattedSum;
    for (char c : sum) {
        if (c != '\r') {
            formattedSum += c;
        }
    }

    return formattedSum;
}

std::string getImageFromFile(std::string fileName) {

    std::ifstream file(fileName);
    if (!file.is_open()) {
        std::cerr << "Could not open the file!" << std::endl;
    }

    std::string line;
    std::string sum;

    while (std::getline(file, line)) {
        sum += line + "\n";
    }

    file.close();

    std::string formattedSum;
    for (char c : sum) {
        if (c != '\r') {
            formattedSum += c;
        }
    }

    return formattedSum;
}

std::string encodeRLE(std::string flattened) {
    std::string rle;
    int count = 1;
    char current = flattened[0];
    flattened = flattened.substr(1);

    for (char c : flattened) {
        if (c == current) {
            count++;
        }
        else {
            rle += std::to_string(count);
            if (current == '0') {
                rle += 'B';
            }
            else {
                rle += 'W';
            }
            current = c;
            count = 1;
        }
    }
    rle += std::to_string(count);
    if (current == '0') {
        rle += 'B';
    }
    else {
        rle += 'W';
    }
    return rle;
}

void programLoop(HashTable& hashTable) {
    std::string input;
    bool queryMode = 0;
    while (true) {
        if (queryMode) {
            std::cout << "Enter image number to query (or 'exit' to quit):" << std::endl;
            std::cin >> input;
            if (input == "exit") {
                return;
            }
            else {
                std::string fileName = "query" + input + ".txt";
                std::string result = getFlattenedImageFromFile(fileName);
                result = encodeRLE(result);
                bool exists = hashTable.search(result);
                if (exists) {
                    std::cout << "RLE String for " + fileName + " found in hash table." << std::endl;
                    std::cout << getImageFromFile(fileName);
                }
                else {
                    std::cout << "No match for the image with encoding: ";
                    std::cout << encodeRLE(getFlattenedImageFromFile(fileName)) << std::endl;
                }
            }
        }
        else {
            std::cout << "Enter image number to insert into the hash table (or 'query' to continue):" << std::endl;
            std::cin >> input;
            if (input == "exit") {
                return;
            }
            else if (input == "query"){
                 queryMode = 1;
            }
            else {
                std::string result = getFlattenedImageFromFile("image" + input + ".txt");
                result = encodeRLE(result);
                hashTable.insert(result);
                std::cout << "Image " + input + " inserted into the hash table." << std::endl;
            }
        }
    }
}

int main() {
    //std::string flattenedImage = getFlattenedImageFromFile("test.txt");
    //std::cout << encodeRLE(flattenedImage) << std::endl;

    HashTable ht = HashTable(100);
    /*
    ht.insert("asdf");
    ht.insert("asdf");
    ht.insert("asdfe");
    ht.insert("asdfeg");


    std::cout << ht.search("asdf");

    std::cout << ht.search("asdfe");
    std::cout << "asd";
*/

    programLoop(ht);
    std::cout << "Exiting the program!";
}