#include "SudokuPuzzle.h"
#include <Windows.h>
#include <string> 

SudokuPuzzle::SudokuPuzzle(void)
{
}

SudokuPuzzle::~SudokuPuzzle(void)
{
}


vector<int> combinedVector(vector<int> &list1, vector<int> &list2)
{
	list1.insert(list1.end(), list2.begin(), list2.end());
	return list1;
}

void SudokuPuzzle::InitialiseGrid(char filenameIn[])
{
	string sourceFile = filenameIn;
	ifstream fin;
	fin.open(sourceFile);
	int blockEnd;
	bool blockAssigned = false;
	int blockIndexes[9] = { 0 };
	int cellID = 0;
	for (int i = 0; i < 9; i++) 
	{
		m_gridCollumns[i].setID(i);
		m_gridBlocks[i].setID(i);
		m_gridRows[i].setID(i);
	}
	for (int row = 0; row < 9; ++row)
	{
		for (int column = 0; column < 9; ++column)
		{
			int value;
			fin >> value;
			cell* newCell = new cell(value, cellID);	//set cellgroup ID
			m_gridCollumns[column].SetCell(row, newCell);
			m_gridRows[row].SetCell(column, newCell);
			int blockNum = (row / 3) * 3 + (column / 3);//Create cell groups for 9 3x3 blocks. 
			if (!blockAssigned)
			{
				blockEnd = blockIndexes[blockNum] + 3;
				blockAssigned = true; 
			}
			
			m_gridBlocks[blockNum].SetCell(blockIndexes[blockNum], newCell);
			++cellID;
			++blockIndexes[blockNum];
			if (blockIndexes[blockNum] == blockEnd)
			{
				blockAssigned = false;
			}
		}
	}
	fin.close();
}

vector<int> completeList;
bool SudokuPuzzle::setCandidateList()
{
	completeList = getCompleteList();
	vector<int> candidateList;
	vector<int> allValues; 
	//create candidate lists for each cell. 
	for (int i = 0; i < completeList.size(); i++)
	{
		int blockID;
		int rowID;
		int collumnID;
		for (int j = 0; j < 9; j++)//take the cell index and find the box, collumn and row its siting in. 
		{
		int foundBlockID =    m_gridBlocks[j].findCell(completeList[i]);
		if (foundBlockID != 10)//If 10 is not returned then the result is correct. 
			blockID = foundBlockID;

		int	foundRowID =     m_gridRows[j].findCell(completeList[i]);
		if (foundRowID != 10)//If 10 is not returned then the result is correct. 
			rowID = foundRowID;
		
		int	foundCollumnID = m_gridCollumns[j].findCell(completeList[i]);
		if (foundCollumnID != 10)//If 10 is not returned then the result is correct. 
			collumnID = foundCollumnID;
		}
		allValues = combinedVector(allValues, m_gridBlocks[blockID].getValues());	//get all the values from indexes
		allValues = combinedVector(allValues, m_gridRows[rowID].getValues());
		allValues = combinedVector(allValues, m_gridCollumns[collumnID].getValues());
		for (auto number : zeroToNine)//make them unique 
		{
			auto it = std::find(allValues.begin(), allValues.end(), number);
			if (it == allValues.end())
			{candidateList.push_back(number);}
		}
		m_gridRows[rowID].setCandidateList(completeList[i], candidateList);//set the candidate list to the cell.
		if (i == 11)
		{
		//	cout << "Isd";
		}
		candidateList.clear();//clean lists, prepare for next unassigned cell. 
		allValues.clear();
	}
	return true; 
}

const vector<int>SudokuPuzzle::getCompleteList() const
{
	vector<int> completeList;
	//get collection of unasigned cells. 
	for (int i = 0; i < 9; ++i)
	{
		vector<int> list;
		list = m_gridRows[i].unassignedCells();
		completeList = combinedVector(completeList, list);
	}
	return completeList;
}

void SudokuPuzzle::nakedSingles()
{
	bool found; 
	for (int i = 0; i < 9; i++)
	{
		 m_gridBlocks[i].nakedSingle();//go through all groups and the one with 1 candidate is a naked single. 
	}
}

//Method that return all the candidates from cells current block, row and collumn 
//find first unasigned cell. Take the first candidate. take the candidates from cells current row, block and collumn. If candidate is unique then assign it. 

void SudokuPuzzle::tripleContext() 
{
	//candidate is determined by the safety of the value in its block, row and collumn. 
	//find hidden single by going through the candidate list and couting how man
	//At the end check if the puzzle has been solved. 

	bool setCandidate = setCandidateList();

	int solved = 0;
	bool complete = false;
	while (!complete)
	{
		completeList = getCompleteList();
		for (int i = 0; i < completeList.size(); i++)	//take first unasigned id in complete list. 
		{
			vector<int> cellCandidates; //loop through this 
			for (int b = 0; b < 9; b++) //when all the candidates for that one cell is found loop through each one and count occurnces. only 1 occurence means its a hiddens single. 
			{
				vector<int> found = m_gridRows[b].getCandidateList(completeList[i]);;
				if (found.size() != 0)
				{
					cellCandidates = combinedVector(cellCandidates, found);
					break;
				}
			}
			for (int j = 0; j < cellCandidates.size(); j++)
			{
				int analysedCandidate = cellCandidates[j];//the 1 candidate being checked. 
				vector<int> allCandidates;
				int blockID = 10;
				int rowID = 10;
				int collumnID = 10;
				for (int m = 0; m < 9; m++)
				{
					int foundBlockID = m_gridBlocks[m].findCell(completeList[i]);
					if (foundBlockID != 10)
						blockID = foundBlockID;
					int	foundRowID = m_gridRows[m].findCell(completeList[i]);
					if (foundRowID != 10)
						rowID = foundRowID;
					int	foundCollumnID = m_gridCollumns[m].findCell(completeList[i]);
					if (foundCollumnID != 10)
						collumnID = foundCollumnID;
					if (blockID != 10 && rowID != 10 && collumnID != 10)//break out of the loop early if all the correct values were found. 
						break;
				}
				allCandidates = combinedVector(allCandidates, m_gridRows[rowID].getAllCandidates());
				int rowOccurenceCount = 0;
				for (int f = 0; f < allCandidates.size(); f++)
				{
					if (analysedCandidate == allCandidates[f])
					{
						++rowOccurenceCount;
					}
				}
				allCandidates.clear();
				allCandidates = combinedVector(allCandidates, m_gridBlocks[blockID].getAllCandidates());
				int blockOccurenceCount = 0;
				for (int f = 0; f < allCandidates.size(); f++)
				{
					if (analysedCandidate == allCandidates[f])
					{
						++blockOccurenceCount;
					}
				}
				int collumnOccurenceCount = 0;
				allCandidates.clear();
				allCandidates = combinedVector(allCandidates, m_gridCollumns[collumnID].getAllCandidates());
				for (int f = 0; f < allCandidates.size(); f++)
				{
					if (analysedCandidate == allCandidates[f])
					{
						++collumnOccurenceCount;
					}
				}
				//	cout <<" testing " << analysedCandidate << " on cell index " << completeList[i] << endl;
				if (collumnOccurenceCount == 1 || blockOccurenceCount == 1 || rowOccurenceCount == 1)
				{
					for (int q = 0; q < 9; q++)	//its a hidden single. set the analysedCandidate into the cell. 
					{
						bool changed = m_gridRows[q].changeCellValue(completeList[i], analysedCandidate);
						if (changed)
						{
							solved++;
							std::string strCount = std::to_string(solved);
							//		cout << completeList[i] << " Hidden Single " << analysedCandidate << " Count: " << strCount <<  endl;
							bool setCandidate = setCandidateList();//recalculate candidate list
							break;
						}
					}
					break;
				}
				else
				{
					continue;
					//move onto the next number as its not a hidden a single. 
				}
			}
		}
		nakedSingles();
		bool setCandidate = setCandidateList();
		complete = checkComplete();
	}
}

const bool SudokuPuzzle::checkComplete() const
{
	bool solved = false; 
	for (int i = 0; i < 9; i++)
	{
		if (!m_gridRows[i].solved())
		{
			return solved = false; 
		}
	}
	return true; 
}

void SudokuPuzzle::Solve(char filenameIn[])
{
	InitialiseGrid(filenameIn);// read the values of the Sudoku puzzle into your data structure
	LARGE_INTEGER start, end, frequency;
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&start);
	tripleContext();
	// Solve the puzzle
	QueryPerformanceCounter(&end);
	float time = (end.QuadPart - start.QuadPart) / (static_cast<float> (frequency.QuadPart));
	Output();  // Output the solved puzzle
}

void SudokuPuzzle::Output() const// This is an example of how you may output the solved puzzle
{
	ofstream fout("sudoku_solution.txt"); // DO NOT CHANGE THE NAME OF THIS FILE
	if (fout.is_open())
	{
		for (int y = 0; y < 9; ++y)
		{
			for (int x = 0; x < 9; ++x)
			{
				fout << m_gridRows[y].getCellValue(x) << " ";
			}
			fout << endl;
		}
		fout.close();
	}
}

