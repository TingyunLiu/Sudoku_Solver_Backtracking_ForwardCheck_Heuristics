CXX = g++
CXXFLAGS = -MMD -g
EXEC = sudoku
OBJECTS = sudoku.o backtrack.o backtrack_forwardcheck.o backtrack_forwardcheck_heuristics.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
