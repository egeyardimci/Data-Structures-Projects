#include "Quadtree.h"

Node::Node(std::string name, int x, int y, Node* NW, Node* NE, Node* SW, Node* SE) : name(name), x(x), y(y), NW(NW), NE(NE), SW(SW), SE(SE) {}

Node::Node(std::string name, int x, int y) : name(name), x(x), y(y){
	this->NE = nullptr;
	this->NW = nullptr;
	this->SW = nullptr;
	this->SE = nullptr;
}

Quadtree::Quadtree() {
	this->root = nullptr;
}

void Quadtree::insert(std::string name,int x,int y) {
	Node* nodeToInsert = new Node(name, x, y);

	if(this->root == nullptr){
		this->root = nodeToInsert;
	}
	else {
		this->insertNode(this->root, nodeToInsert);
	}
}

int Quadtree::compareNodes(Node* node, Node* nodeToInsert) {
	if (nodeToInsert->x < node->x) {
		if (nodeToInsert->y < node->y) {
			return DIRSW;
		}
		else {
			return DIRNW;
		}
	}
	else if (nodeToInsert->y < node->y) {
		return DIRSE;
	}
	else {
		return DIRNE;
	}
}

void Quadtree::insertNode(Node* node,Node* nodeToInsert) {
	int direction = compareNodes(node, nodeToInsert);

	switch (direction)
	{
	case DIRNE:
		if (node->NE == nullptr) {
			node->NE = nodeToInsert;
			break;
		}
		insertNode(node->NE, nodeToInsert);
		break;

	case DIRNW:
		if (node->NW == nullptr) {
			node->NW = nodeToInsert;
			break;
		}
		insertNode(node->NW, nodeToInsert);
		break;

	case DIRSE:
		if (node->SE == nullptr) {
			node->SE = nodeToInsert;
			break;
		}
		insertNode(node->SE, nodeToInsert);
		break;

	case DIRSW:
		if (node->SW == nullptr) {
			node->SW = nodeToInsert;
			break;
		}
		insertNode(node->SW, nodeToInsert);
		break;
	}
}

void Quadtree::print() {
	this->printNodes(this->root);
}

void Quadtree::printNodes(Node* node) {
	if (node){
		std::cout << node->name << std::endl;
		printNodes(node->SE);
		printNodes(node->SW);
		printNodes(node->NE);
		printNodes(node->NW);
	}
}

int Quadtree::findRegionOfNode(int x, int y, int r, Node* root, std::vector<std::string>& foundCities) {
	if (root->y > (y + r)) {
		if (root->x < (x - r)) {
			return 1;
		}
		else if (root->x > (x + r)) {
			return 3;
		}
		else {
			return 2;
		}
	}
	else if (root->y < (y - r)) {
		if (root->x < (x - r)) {
			return 6;
		}
		else if (root->x > (x + r)) {
			return 8;
		}
		else {
			return 7;
		}
	}
	else if (root->x > (x + r)) {
		return 5;
	}
	else if (root->x < (x - r)) {
		return 4;
	}
	else if (std::sqrt(std::pow(root->x - x, 2) + std::pow(root->y - y, 2)) <= r) {
		foundCities.push_back(root->name);
		return 13;
	}
	else if (root->x < x) {
		if (root->y > y) {
			return 9;
		}
		else {
			return 11;
		}
	}
	else {
		if (root->y > y) {
			return 10;
		}
		else {
			return 12;
		}
	}
}

void Quadtree::searchRegion(int x, int y, int r, Node* node, std::vector<std::string>& visitedCities, std::vector<std::string>& foundCities) {
	
	if (!node) {
		return;
	}

	int region = findRegionOfNode(x,y,r,node,foundCities);
	visitedCities.push_back(node->name);

	switch (region) {
	case 1:
		searchRegion(x, y, r, node->SE,visitedCities,foundCities);
		break;
	case 2:
		searchRegion(x, y, r, node->SE, visitedCities, foundCities);
		searchRegion(x, y, r, node->SW, visitedCities, foundCities);
		break;
	case 3:
		searchRegion(x, y, r, node->SW, visitedCities, foundCities);
		break;
	case 4:
		searchRegion(x, y, r, node->SE, visitedCities, foundCities);
		searchRegion(x, y, r, node->NE, visitedCities, foundCities);
		break;
	case 5:
		searchRegion(x, y, r, node->SW, visitedCities, foundCities);
		searchRegion(x, y, r, node->NW, visitedCities, foundCities);
		break;
	case 6:
		searchRegion(x, y, r, node->NE, visitedCities, foundCities);
		break;
	case 7:
		searchRegion(x, y, r, node->NE, visitedCities, foundCities);
		searchRegion(x, y, r, node->NW, visitedCities, foundCities);
		break;
	case 8:
		searchRegion(x, y, r, node->NW, visitedCities, foundCities);
		break;
	case 9:
		searchRegion(x, y, r, node->SE, visitedCities, foundCities);
		searchRegion(x, y, r, node->SW, visitedCities, foundCities);
		searchRegion(x, y, r, node->NE, visitedCities, foundCities);
		break;
	case 10:
		searchRegion(x, y, r, node->SE, visitedCities, foundCities);
		searchRegion(x, y, r, node->NW, visitedCities, foundCities);
		searchRegion(x, y, r, node->SW, visitedCities, foundCities);
		break;
	case 11:
		searchRegion(x, y, r, node->SE, visitedCities, foundCities);
		searchRegion(x, y, r, node->NW, visitedCities, foundCities);
		searchRegion(x, y, r, node->NE, visitedCities, foundCities);
		break;
	case 12:
		searchRegion(x, y, r, node->SW, visitedCities, foundCities);
		searchRegion(x, y, r, node->NW, visitedCities, foundCities);
		searchRegion(x, y, r, node->NE, visitedCities, foundCities);
		break;
	case 13:
		searchRegion(x, y, r, node->SE, visitedCities, foundCities);
		searchRegion(x, y, r, node->NW, visitedCities, foundCities);
		searchRegion(x, y, r, node->NE, visitedCities, foundCities);
		searchRegion(x, y, r, node->SW, visitedCities, foundCities);
		break;
	}
}

void Quadtree::callSearchRegion(int x, int y, int r, std::vector<std::string>& visitedCities, std::vector<std::string>& foundCities){
	this->searchRegion(x, y, r, this->root, visitedCities, foundCities);
}