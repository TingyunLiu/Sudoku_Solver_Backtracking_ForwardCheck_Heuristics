#include "backtrack_forwardcheck.h"
#include <queue>

//******************************************************************************************************************
// This class is Backtracking + Forward Checking + Heuristics
// Derived class from class BacktrackForwardcheck
//******************************************************************************************************************
class BacktrackForwardcheckHeuristics : public BacktrackForwardcheck {
	int number_constraining_variable(int row, int column); // to calculate number of constraining variable
	int number_constraining_value(int row, int column, int value); // to calculate number of constraining value
	bool most_restricted_variable(int &row, int &column); // to get the next most restricted cell to assign
	// compare function for the proirity queue to compare the stored number of constraining value in ascending order
	struct compare_number_of_constraining_value {
		bool operator()(const std::pair<int,int> &v1, const std::pair<int,int> &v2) {
			return (v1.second > v2.second);
		}
	};
public:
	BacktrackForwardcheckHeuristics(int grid[][GRID_SIZE]); // constructor to set up the grid
	bool solve(); // to solve the Sudoku with heuristics
};


