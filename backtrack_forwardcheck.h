#include <iostream>
#include "backtrack.h"


//********************************************************************************************************************
// This class is standard Backtracking search + Forward Checking
// Base class for class BacktrackForwardcheckHeuristics
// Derived class from class Backtrack
//********************************************************************************************************************
class BacktrackForwardcheck : public Backtrack {
protected:
	bool cause_unsolvable(); // check if there is a cell cannot be assigned with any values, which means unsolvable
public:
	BacktrackForwardcheck(int grid[][GRID_SIZE]); // constructor to set up the grid
};
