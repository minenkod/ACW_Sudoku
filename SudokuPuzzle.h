#pragma once
#include "CellGroup.h"
#include <iostream>
#include <fstream>

using namespace std;

class SudokuPuzzle
{
public:
	SudokuPuzzle(void);
	~SudokuPuzzle(void);

	void Solve(char filenameIn[]);
private:
	void Output() const;
	vector<int> zeroToNine = { 1,2,3,4,5,6,7,8,9 }; //A list of 1-9 values. 
	const vector<int> getCompleteList() const;//get list of all the ids of un - asigned cells. 
	void nakedSingles();
	const bool checkComplete() const;
	//methods responsible for solving
	bool setCandidateList();
	void tripleContext();
	//
	
void InitialiseGrid(char filenameIn[]);
	// Other Methods
	CellGroup m_gridRows[9];
	CellGroup m_gridCollumns[9];
	CellGroup m_gridBlocks[9];
	// other CellGroups for columns and blocks and other member variables etc.

};

