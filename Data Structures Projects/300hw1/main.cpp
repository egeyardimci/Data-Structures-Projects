#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "stack.h"
#include "stack.cpp"

using namespace std;

//Structure to save the moves into the stack
struct State {
	int row = 0;
	int col = 0;

	State(){}

	State(int row, int col) {
		this->row = row;
		this->col = col;
	}

};

//Constructs the safe matrix with all 0's
void consturctSafeMatrix(vector<vector<int>>& matrix, int N) {
	vector<int> zeroVector;

	for (int i = 0; i < N; i++) {
		zeroVector.push_back(0);
	}

	for (int i = 0; i < N; i++) {
		matrix.push_back(zeroVector);
	}
}

//Updates safe matrix in case of queen deletion of insertion by increment
void updateSafeMatrix(vector<vector<int>>& matrix, int row, int col,int increment) {
	for (int i = 0; i < matrix.size(); i++) {
		matrix[row][i] += increment;
		matrix[i][col] += increment;

		if (row + i < matrix.size() && col + i < matrix.size()) {
			matrix[row + i][col + i] += increment;
		}

		if (row - i >= 0 && col - i >= 0) { 
			matrix[row - i][col - i] += increment; 
		}

		if (row + i < matrix.size() && col - i >= 0) {
			matrix[row + i][col - i] += increment;
		}

		if (row - i >= 0 && col + i < matrix.size()) {
			matrix[row - i][col + i] += increment;
		}
	}
}

//For debugging purposes
void printMatrix(vector<vector<int>>& matrix) {
	for (int i = 0; i < matrix.size(); i++) {
		cout << endl;
		for (int j = 0; j < matrix.size(); j++) {
			cout << " " << matrix[i][j] << " ";
		}
	}
	cout << endl;

}

void takeInput(int& n) {
	cout << "Enter the value of N for the N-Queens problem: ";
	cin >> n;

	if (n <= 0) {
		cout << "Invalid input. Please enter a positive integer" << endl;
	}
}

void writeSolutionsToFile(vector<vector<int>> &solutions, int N) {
	string fileName = to_string(N) +  "queens_solutions.txt";

	ofstream outFile(fileName);

	if (outFile.is_open()) {
		outFile << "Total solutions for N="<< N << ": " << solutions.size() << endl << endl;
		for (int i = 0; i < solutions.size(); ++i) {
			outFile << "Solution " << i + 1 << ": [";
			for (int j = 0; j < solutions[i].size(); ++j) {
				outFile << solutions[i][j];
				if (j != solutions[i].size() - 1)
					outFile << ", ";
			}
			outFile << "]" << endl;
		}
		outFile.close();
	}

	cout << "Solutions have been saved to '" << fileName << "'" << endl;
}

void solveNQueens(vector<vector<int>> &safeMatrix, vector<vector<int>>& solutions , int N) {
	//Create a stack for saving the states
	Stack<State> stack;
	stack.push(State(0, 0));

	//Boolean to keep the track of if a quuen is placed in an itteration
	bool isQueenPlaced = 0;

	while (!stack.isEmpty()) {
		State current = stack.top();
		stack.pop();

		//If no queen was palced backtrack
		if (!isQueenPlaced) {
			if (current.col >= 1) {
				// since we save next collumn as the backtrack info delete col-1
				updateSafeMatrix(safeMatrix, current.row, current.col - 1, -1); 
			}
		}

		//Found solution
		if (current.row == N) {
			vector<int> solution;

			for (int i = 0; i < N; i++) {
				for (int j = 0; j < N; j++) {
					if (safeMatrix[i][j] == 6) {
						solution.push_back(j);
					}
				}
			}

			solutions.push_back(solution);
			isQueenPlaced = 0;
			continue;
		}

		isQueenPlaced = 0;

		for (int col = current.col; col < N; ++col) {
			if (safeMatrix[current.row][col] == 0) {
				isQueenPlaced = 1;
				updateSafeMatrix(safeMatrix,current.row, col, 1);
				// For backtracking
				stack.push(State(current.row, col + 1));
				// Move to next row
				stack.push(State(current.row + 1, 0));
				break;
			}
		}
	}
}

int main() {
	int N;
	vector<vector<int>> safeMatrix;
	vector<vector<int>> solutions;

	takeInput(N);
	consturctSafeMatrix(safeMatrix,N);
	solveNQueens(safeMatrix,solutions,N);
	writeSolutionsToFile(solutions,N);
}