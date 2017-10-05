#include "backtrack_forwardcheck_heuristics.h"
using namespace std;

//********************************************************************************************************************
// Constructor for the BacktrackForwardcheckheuristics, calling BacktrackForwardcheck's constructor to set up grid
//********************************************************************************************************************
BacktrackForwardcheckHeuristics::BacktrackForwardcheckHeuristics(int grid[][GRID_SIZE]):BacktrackForwardcheck(grid) {}


//********************************************************************************************************************
// Function to get the most restricted variable and store the index into row and column correspondingly if there is
//		an available cell has not been assinged yet; otherwise, return false, which means all cells are filled.
//********************************************************************************************************************
bool BacktrackForwardcheckHeuristics::most_restricted_variable(int &row, int &column) {
	int mrv_value = GRID_SIZE+1; // initial most restricted value, large enough to be updated by any available cell
	int total_available_values = 0; // 0 means the grid is full, done

	for (int i = 0; i < GRID_SIZE; i++) {
		for (int j = 0; j < GRID_SIZE; j++) {
			if (!grid[i][j]) { // only process empty cells
				int available_values = 0; // to keep track of the number of avilable values for each cell
				for (int k = 1; k <= GRID_SIZE; k++) {
					if (check_availability(i, j, k)) {
						available_values++; // increment the counter
						total_available_values++; // increment the total counter
					} // if
				} // for
				if (available_values <= mrv_value) { // check if we need to update the mrv
					if (available_values == mrv_value) { // tie break with most constraining variable
						if (number_constraining_variable(i, j) < number_constraining_variable(row, column)) continue;
					} // if
					// update the row, column, and current minimum number of values that can be filled in
					row = i;
					column = j;
					mrv_value = available_values;
				} // if
			} // if
		} // for
	} // for

	if (total_available_values) { // there is at least one cell empty
		return true;
	} else { // no cell is available to fill in, done
		return false;
	} // if
}

//********************************************************************************************************************
// Function to calculate the number of constraining variable for the cell(row,column)
//		Try every potential affected cell, keep a number of available cells before assigning the cell(row, column),
//		and a number of available cells after assigning the cell(row, column). It returns the difference between two
//		counters.
//********************************************************************************************************************
int BacktrackForwardcheckHeuristics::number_constraining_variable(int row, int column) {
	int subgrid_start_row = row / SUBGRID_SIZE * SUBGRID_SIZE;
	int subgrid_start_column = column / SUBGRID_SIZE * SUBGRID_SIZE;

	// before
	int number_other_cells_available_before = 0;
	for (int i = 0; i < SUBGRID_SIZE; i++) {
		for (int j = 0; j < SUBGRID_SIZE; j++) {
			// does not check itself and cells that are already filled
			if ((grid[subgrid_start_row+i][subgrid_start_column+j]) || 
				((subgrid_start_row+i == row) && (subgrid_start_column+j == column))) continue;
			for (int k = 1; k <= GRID_SIZE; k++) {
				// check all empty cells and increment the counter for variables are available before assignment
				if (check_availability(subgrid_start_row+i, subgrid_start_column+j, k)) {
					++number_other_cells_available_before;
				} // if
			} // for
		} // for
	} // for

	// after
	int number_other_cells_available_after = 0;
	for (int i = 0; i < SUBGRID_SIZE; i++) {
		for (int j = 0; j < SUBGRID_SIZE; j++) {
			// does not check itself and cells that are already filled
			if ((grid[subgrid_start_row+i][subgrid_start_column+j]) || 
				((subgrid_start_row+i == row) && (subgrid_start_column+j == column)))continue;
			for (int k = 1; k <= GRID_SIZE; k++) {
				// try to assign k to the cell(row, column)
				bool tried_k = false;
				if (check_availability(row, column, k)) {
					grid[row][column] = k;
					tried_k = true;
				} // if
				// check all empty cells and increment the counter for variables are available after assignment
				if (check_availability(subgrid_start_row+i, subgrid_start_column+j, k)) {
					++number_other_cells_available_after;
				} // if
				if (tried_k) {
					grid[row][column] = 0; // reset the cell(row, column) back to 0
				} // if
			} // for
		} // for
	} // for

	// calculate the difference between before and after assignment
	return number_other_cells_available_before - number_other_cells_available_after;
}


//********************************************************************************************************************
// Function to calculate the the number of constraining value for the cell(row, column) with the value.
//		Try every possible affected cell, and keep a number of available values before value being assigned in the
//		cell(row, column), and a counter to keep track of available values after the value being assigned in the
//		cell(row, column). It returns the difference between the two counter;
//********************************************************************************************************************
int BacktrackForwardcheckHeuristics::number_constraining_value(int row, int column, int value) {
	int subgrid_start_row = row / SUBGRID_SIZE * SUBGRID_SIZE;
	int subgrid_start_column = column / SUBGRID_SIZE * SUBGRID_SIZE;

	// before
	int number_other_cells_values_available_before = 0;
	for (int i = 0; i < SUBGRID_SIZE; i++) {
		for (int j = 0; j < SUBGRID_SIZE; j++) {
			// does not check itself and cells that are already filled
			if ((grid[subgrid_start_row+i][subgrid_start_column+j]) || 
				((subgrid_start_row+i == row) && (subgrid_start_column+j == column))) continue;
			if (check_availability(subgrid_start_row+i, subgrid_start_column+j, value)) {
				// to keep track of the total number of values that are available to other cells before assignment
				++number_other_cells_values_available_before;
			} // if
		} // for
	} // for

	// after
	int number_other_cells_values_available_after = 0;
	grid[row][column] = value; // assign the cell(row, column) with the value
	for (int i = 0; i < SUBGRID_SIZE; i++) {
		for (int j = 0; j < SUBGRID_SIZE; j++) {
			// does not check itself and cells that are already filled
			if ((grid[subgrid_start_row+i][subgrid_start_column+j]) || 
				((subgrid_start_row+i == row) && (subgrid_start_column+j == column)))continue;
			if (check_availability(subgrid_start_row+i, subgrid_start_column+j, value)) {
				// to keep track of the total number of values that are available to other cells after assignment
				++number_other_cells_values_available_after;
			} // if
		} // for
	} // for
	grid[row][column] = 0; // reset the cell(row, column) back to 0, empty

	// calculate the difference between before and after assignment
	return number_other_cells_values_available_before - number_other_cells_values_available_after;
}


//********************************************************************************************************************
// Function to solve the Sudoku with the heuristics
//		Find the next most restricted available cell and then compute all safe values for the current
//		cell(row, column) and push them in a priority queue ordered by the number of constraining value in ascending
//		order. Try to solve it with the value in priority queue's order, where the least constraining value will be
//		tried first. Everything else is the same as solve function in Backtrack class.
//********************************************************************************************************************
bool BacktrackForwardcheckHeuristics::solve() {
	int row, column;

	if (most_restricted_variable(row, column)) { // get next available cell, which is also the most restricted variable
		// priority queue to maintain the order from smallest to largest
		//		for values that may be filled in the cell(row, column)
		priority_queue<pair<int,int>, vector<pair<int,int> >, compare_number_of_constraining_value> try_order;
		for (int i = 1; i <= GRID_SIZE; i++) {
			if (check_availability(row, column, i)) { // only push safe values
				try_order.push(make_pair(i, number_constraining_value(row, column, i)));
			} // if
		} // for

		int len = try_order.size();
		// loop through all safe values by the order from least constraining value to most constraining value
		for (int i = 0; i < len; i++) {
			int value = (try_order.top()).first;
			grid[row][column] = value; // try to assign a value
			total_number_of_assignment++;
			// if it is over 10000, then just return true and stop solving
			if (total_number_of_assignment > MAX_NUMBER_ASSIGNMENT_ALLOWED) return true;
			// checking unsolvable problem (one-step forward checking) and 
			//		recursive call on current grid with the trial above (backtracking)
			if (!cause_unsolvable() && solve()) {
				return true;
			} // if
			grid[row][column] = 0; // reset back to 0
			try_order.pop(); // pop the least constraining value from the priority queue
		} // for
		return false;
	} else { // no available, solved
		return true;
	} // for
}

