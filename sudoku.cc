#include <fstream>                              // to choose the input source (stdin or command line infile)
#include <cstdlib>                              // for exit
#include <cstring>                              // for s_ctr and atoi
#include "backtrack_forwardcheck_heuristics.h"  // including backtrack + forwardcheck + heuristics header
using namespace std;                            // direct access to std


//********************************************************************************************************************
// Program for usage error handling
//********************************************************************************************************************
static void usage(char *argv[]) {
    cerr << "Usage: " << argv[0] << " [input-file]" << endl;
    exit(EXIT_FAILURE);                         // TERMINATE
} // usage


//********************************************************************************************************************
// Main driver for the program.
//********************************************************************************************************************
int main(int argc, char *argv[]) {
    istream *infile = &cin;                     // default value
    switch (argc) {                             // handling command line argument
        case 2:
            try {
                infile = new ifstream(argv[1]);
            } catch(...) {
                cerr << "Error! Could not open input file \"" << argv[1] << "\"" << endl;
                exit(EXIT_FAILURE);
            } // try
            // FALL THROUGH
        case 1:                                 // all defaults
            break;
        default:                                // wrong number of options
            usage(argv);
    } // switch

    int grid[GRID_SIZE][GRID_SIZE];             // grid to store cells

    string cell;

    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            *infile >> cell;                    // read in the grid cell by cell
            if (infile->fail()) {
                cerr << "Error! file does not exist or cannot be read" << endl;
                exit(EXIT_FAILURE);
            } // if
            grid[i][j] = atoi(cell.c_str());    // convert each cell to an integer
        } // for
    } // for


    Backtrack bk(grid);                         // For standard Backtracking search

    if (bk.solve()) {
        bk.print_grid();                        // print the final states
    } else {
        cout << "Cannot solve it" << endl;
    } // if

    BacktrackForwardcheck bkfc(grid);           // For Backtracking + Forward Checking

    if (bkfc.solve()) {
        bkfc.print_grid();                      // print the final states
    } else {
        cout << "Cannot solve it" << endl;
    } // if

    BacktrackForwardcheckHeuristics bkfch(grid);// For Backtracking + Forward Checking + Heuristics

    if (bkfch.solve()) {
        bkfch.print_grid();                     // print the final states
    } else {
        cout << "Cannot solve it" << endl;
    } // if


    if (infile != &cin) delete infile;          // close file, do not delete cin!
} // main

