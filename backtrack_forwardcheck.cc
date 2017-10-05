#include "backtrack_forwardcheck.h"
using namespace std;


//********************************************************************************************************************
// Constructor for the BacktrackForwardcheck, calling Backtrack's constructor to set up grid
//********************************************************************************************************************
BacktrackForwardcheck::BacktrackForwardcheck(int grid[][GRID_SIZE]):Backtrack(grid) { }


//********************************************************************************************************************
// Function to perform a one-step forward checking.
//		It checks the whole grid to see if there is a cell cannot be assinged with any values, which
//		means the Sudoku is unsolvable because of the assignment of previous cell; thus, do not have to
//		continue recursively call following the "wrong assignment", and then jump to next possible value
//********************************************************************************************************************
bool BacktrackForwardcheck::cause_unsolvable() {
	for (int i = 0; i < GRID_SIZE; i++) {
		for (int j = 0; j < GRID_SIZE; j++) {
			if (grid[i][j] == 0) {
				int available = false;
				for (int k = 1; k <= GRID_SIZE; k++) {
					if (check_availability(i, j, k)) { // check if it is safe to assign the corresponding value
						available = true; // there is a value can be assigned, so the current cell is still active
						break;
					} // if
				} // for
				// no available value can be assigned with the current cell(i,j), cause unsolvable
				if (!available) return true;
			} // if
		} // for
	} // for
	return false; // every cell has at least one value available to be assigned
}


