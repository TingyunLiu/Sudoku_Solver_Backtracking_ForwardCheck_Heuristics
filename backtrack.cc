#include "backtrack.h"
using namespace std;


//******************************************************************************************
// Constructor to set up the grid
//******************************************************************************************
Backtrack::Backtrack(int grid[][GRID_SIZE]) {
	total_number_of_assignment = 0;
	for (int i = 0; i < GRID_SIZE; i++) {
		for (int j = 0; j < GRID_SIZE; j++) {
			this->grid[i][j] = grid[i][j];
		} // for
	} // for
}


//******************************************************************************************
// Function to find the next available cell to be assigned, set the row and column with the
//		next available position if there is one available; otherwise, return false
//******************************************************************************************
bool Backtrack::find_next_available(int &row, int &column) {
	for (int i = 0; i < GRID_SIZE; i++) {
		for (int j = 0; j < GRID_SIZE; j++) {
			if (!grid[i][j]) { // found an available cell
				row = i;
				column = j;
				return true;
			} // if
		} // for
	} // for
	return false; // not found, which means all cells are filled, done
}


//******************************************************************************************
// Function to check if it is safe to assign the value in that corresponding row
//******************************************************************************************
bool Backtrack::check_same_row(int row, int value) {
	for (int i = 0; i < GRID_SIZE; i++) {
		if (grid[row][i] == value) { // value already exists in the row
			return false;
		} // if
	} // for
	return true;
}


//******************************************************************************************
// Function to check if it is safe to assign the value in that corresponding column
//******************************************************************************************
bool Backtrack::check_same_column(int column, int value) {
	for (int i = 0; i < GRID_SIZE; i++) {
		if (grid[i][column] == value) { // value already exists in the column
			return false;
		} // if
	} // for
	return true;
}


//******************************************************************************************
// Function to check if it is safe to assign the value in that corresponding 3x3 subgrid
//******************************************************************************************
bool Backtrack::check_same_subgrid(int row, int column, int value) {
	int subgrid_start_row = row / SUBGRID_SIZE * SUBGRID_SIZE; // beginning row
	int subgrid_start_column = column / SUBGRID_SIZE * SUBGRID_SIZE; // beginning column
	for (int i = 0; i < SUBGRID_SIZE; i++) {
		for (int j = 0; j < SUBGRID_SIZE; j++) {
			// value already exists in the subgrid
			if (grid[subgrid_start_row+i][subgrid_start_column+j] == value) {
				return false;
			} // if
		} // for
	} // for
	return true;
}


//******************************************************************************************
// Function calls all three other check function to check if it is safe to assign the value
//		to the (row, column)
//******************************************************************************************
bool Backtrack::check_availability(int row, int column, int value) {
	return (check_same_row(row, value) && 
			check_same_column(column, value) && 
			check_same_subgrid(row, column, value)); // check among row, column, subgrid
}


//******************************************************************************************
// Function to actually solve the Sudoku, it would try to solve it recursively. If everytime
//		we assign a valid value to a cell, and it does not cause any other cells unsolvable,
//		we continue recursively solve the Sudoku based on current grid status. Otherwise, we
//		reset the cell with value 0, and start backtracking.
//******************************************************************************************
bool Backtrack::solve() {
	int row, column;
	if (find_next_available(row, column)) { // get next available cell
		for (int i = 1; i <= GRID_SIZE; i++) { // loop through all possible values
			if (check_availability(row, column, i)) { // check if it is safe to assign value
				grid[row][column] = i; // try to assign a value
				total_number_of_assignment++; // increment the counter
				// if it is over 10000, then just return true and stop solving
				if (total_number_of_assignment > MAX_NUMBER_ASSIGNMENT_ALLOWED) return true;
				// recursive call on current grid (now grid is with the trial above)
				if (!cause_unsolvable() && solve()) {
					return true;
				} // if
				grid[row][column] = 0; // reset back to 0
			} // for
		} // for
		return false;
	} else { // no available cells, which means solved
		return true;
	} // if
}

//******************************************************************************************
// Function always returns false in this case because we do not perform forward check in
//		this method, this function will be doing the actual work in forward check class.
//******************************************************************************************
bool Backtrack::cause_unsolvable() {
	return false;
}


//******************************************************************************************
// Function to print the final Sudoku states and total number of variable assignment
//******************************************************************************************
void Backtrack::print_grid() {
/*
	for (int i = 0; i < GRID_SIZE; i++) {
		for (int j = 0; j < GRID_SIZE; j++) {
			cout << grid[i][j] << " ";
		} // for
		cout << endl;
	} // for
	cout << "Total number of assignment: " << total_number_of_assignment << endl;
*/
cout << total_number_of_assignment << endl;
}

