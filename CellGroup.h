#pragma once
#include "cell.h"

class CellGroup
{
public:
	CellGroup();
	~CellGroup();
	
	//method to input a cell. Then return the row number, box number and collumn number that cell is present in. 
	//With these numbers check if the candi
	//Method that finds an unasigned cell or cells and returns it.

	//method that returns all values inside the cells. 
	//These number are then used to determine the candidate list for that location.

	//method to return indexes of all unasighned cells as a vector. 

	const vector<int> unassignedCells() const;
	const int findCell(int cellID) const; //Given a cell ID method will returns the column, block or row the cell is sitting in
	void setID(int groupID);
	bool changeCellValue(int cellID, int newValue);
	const bool solved() const;
	 vector<int> getValues() const; //Method return all the numbers in cells within that cell group. 
	 const	vector<int> getCandidateList(int id) const; //get candidate list from a cell from an id. 
	 const vector<int> getCandidates(int groupID) const; //first finds all the cells with the given and returns their candidates. 
	 vector<int> combinedVector(vector<int> &list1, vector<int> &list2) const;
	  vector<int>getAllCandidates() const;
	void nakedSingle();


	void SetCell(int index, cell *cell);
	void setCandidateList(const int &id, const vector<int> &candidateList) const; //given an id of the cell and new candidate list for that cell. 
	
	int getCellValue(int elementIndex) const;
	
private:
	vector<int> m_candidateList;
	vector<int> zeroToNine = { 1,2,3,4,5,6,7,8,9 }; //A list of 1-9 values. 
	cell* m_cells[9] = {};
	 int id = 0;

};

