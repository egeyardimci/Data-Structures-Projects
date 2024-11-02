#pragma once
#include <iostream>
#include <vector>
#include <string>

#define DIRNW 0
#define DIRNE 1
#define DIRSW 2
#define DIRSE 3


struct Node
{
	Node* NW;
	Node* NE;
	Node* SW;
	Node* SE;
	std::string name;
	int x;
	int y;

	Node(std::string name, int x, int y, Node* NW, Node* NE, Node* SW, Node* SE);
	Node(std::string name, int x, int y);

};

class Quadtree {
public:
	Quadtree();
	
	int xBound = 0;
	int yBound = 0;

	void insert(std::string name,int x,int y);
	void print();
	void callSearchRegion(int x, int y, int r, std::vector<std::string>& visitedCities, std::vector<std::string>& foundCities);

private:
	Node* root;

	void searchRegion(int x, int y, int r, Node* node, std::vector<std::string>& visitedCities, std::vector<std::string>& foundCities);
	int compareNodes(Node* node, Node* nodeToInsert);
	void insertNode(Node* node, Node* nodeToInsert);
	int findRegionOfNode(int,int,int,Node*,std::vector<std::string>& foundCities);
	void printNodes(Node* node);
};
