#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "Quadtree.h"

struct SearchOperation
{
    int x;
    int y;
    int r;
};

void configureQuadtreeFromFile(Quadtree& qtree , std::string fileName) {

    std::ifstream file(fileName);
    if (!file.is_open()) {
        std::cerr << "Could not open the file!" << std::endl;
    }

    std::string line;
    bool isFirstLine = 1;

    while (std::getline(file, line)) { 
        std::istringstream stream(line);
        std::string word;

        if(isFirstLine){
            std::vector<std::string> words;
            while (stream >> word) {
                words.push_back(word);
            }
            qtree.xBound = std::stoi(words[0]);
            qtree.yBound = std::stoi(words[1]);
            isFirstLine = 0;
        }
        else {
            std::vector<std::string> words;
            while (stream >> word) {
                words.push_back(word);
            }
            qtree.insert(words[0], std::stoi(words[1]), std::stoi(words[2]));
        }

    }

    file.close(); 
}

void getSearchOperationFromFile(std::vector<SearchOperation>& searchOperations, std::string fileName) {

    std::ifstream file(fileName);
    if (!file.is_open()) {
        std::cerr << "Could not open the file!" << std::endl;
    }

    std::string line;
    bool isFirstLine = 1;

    while (std::getline(file, line)) {
        std::istringstream stream(line);
        std::string word;

        SearchOperation searchOperation = SearchOperation();
        std::vector<std::string> words;
        while (stream >> word) {
            word.erase(std::remove(word.begin(), word.end(), ','), word.end());
            words.push_back(word);
        }

        searchOperation.x = std::stoi(words[0]);
        searchOperation.y = std::stoi(words[1]);
        searchOperation.r = std::stoi(words[2]);

        searchOperations.push_back(searchOperation);
    }

    file.close();
}

void printSearchResult(std::vector<std::string>& visitedCities, std::vector<std::string>& foundCitites) {
    if (foundCitites.size() == 0) {
        std::cout << "<None>";
    }
    else {
        for (int i = 0; i < foundCitites.size(); i++) {
            if (i != foundCitites.size() - 1) {
                std::cout << foundCitites[i] << ", ";
            }
            else {
                std::cout << foundCitites[i];
            }
        }
    }

    std::cout << std::endl;

    for (int i = 0; i < visitedCities.size(); i++) {
        if (i != visitedCities.size() - 1) {
            std::cout << visitedCities[i] << ", ";
        }
        else {
            std::cout << visitedCities[i];
        }
    }

    std::cout << std::endl;
    std::cout << std::endl;
}

int main() {
	Quadtree qtree = Quadtree();
    
    configureQuadtreeFromFile(qtree, "cities.txt");
	qtree.print();

    std::cout << std::endl;

    std::vector<SearchOperation> searchOperations;
    getSearchOperationFromFile(searchOperations, "queries.txt");

    for (SearchOperation searchOpereation : searchOperations) {
        std::vector<std::string> visitedCities;
        std::vector<std::string> foundCitites;

        qtree.callSearchRegion(searchOpereation.x, searchOpereation.y, searchOpereation.r, visitedCities, foundCitites);
        printSearchResult(visitedCities, foundCitites);
    }
}