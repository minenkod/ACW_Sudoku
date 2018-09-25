#include "CellGroup.h"
#include <algorithm>
#include <iostream>
using namespace std; 

CellGroup::CellGroup(): m_cells() ,id(0)
{


}

CellGroup::~CellGroup()
{
}


void CellGroup::setID(int groupID)
{
	id = groupID;

}
void CellGroup::SetCell(int index, cell *cell)
{
	m_cells[index] = cell;
}

const int CellGroup::findCell(int cellID) const
{

	for (int i = 0; i < 9; i++)
	{
		if (m_cells[i]->getID() == cellID)
		{
			return id; 
		}
	}

	return 10; //the cell was not found

}
const vector<int> CellGroup::getCandidateList(int inId) const//given a group id, all unasigned cells candidates are added to a vector.    
{
	vector<int>CandidateList;
     for (int i = 0; i < 9; i++)
	{
		 //find an 

		int cellID =  m_cells[i]->getID();
	
		if (cellID == inId)
		{
			CandidateList = m_cells[i]->getCandidateList();
			return CandidateList;
		}
	}
	return CandidateList;
}


 vector<int> CellGroup::getAllCandidates()  const
{
	//get all unuasined cells from the given id. 
	vector<int> massCandidates;
	vector<int> ids;
	for (int i = 0; i < 9; i++)
	{
		if (m_cells[i]->getAssigned() == false)
		{
			int gotid = m_cells[i]->getID();
			ids.push_back(id);
		}
	}
	for (int i = 0; i < ids.size(); i++)
	{
		for (int k = 0; k < 9; k++)
		{
			if (m_cells[k]->getID() == ids[i])
			{
				
				vector<int> itsCandidates = m_cells[k]->getCandidateList();
				massCandidates = combinedVector(massCandidates, itsCandidates);
			}
 		}
	}
	return massCandidates;
}

 vector<int>    CellGroup::combinedVector(vector<int> &list1, vector<int> &list2) const
{
	list1.insert(list1.end(), list2.begin(), list2.end());
	return list1;
}

bool CellGroup::changeCellValue(int cellID, int newValue)
{
	//find cell by its id and set the new value to it. 
	for (int i = 0; i < 9; i++)
	{
		if (m_cells[i]->getID() == cellID)
		{
			m_cells[i]->setValue(newValue);
			return true;
		}

	}
	return false; 
}

const vector<int> CellGroup::getCandidates(int groupID) const
{
	vector<int> allCandidates;
	vector<int> ids;
	if (groupID == id)
	{
		//first find all the ids of unasigned cells.

		for (int i = 0; i < 9; i++)
		{
			if (m_cells[i]->getAssigned() == false)
			{
				ids.push_back(	m_cells[i]->getID());
			}
		}

		for (int i = 0; i < 9; i++)
		{
			vector<int> currentCandidates;
			currentCandidates = getCandidateList(ids[i]);
			allCandidates = combinedVector(allCandidates, currentCandidates);
		}
		//ids.push_back()


	}

	return allCandidates;
}



void CellGroup::setCandidateList(const int   &id, const vector<int> &candidateList ) const
{
//find that cell with a given ID and set its new candidate list. 
	for (int i = 0; i < 9; i++)
	{
		if (m_cells[i]->getID() == id)//Found the cell
		{
			m_cells[i]->setCandidate(candidateList);
	     }
	
	}

}

const vector<int> CellGroup::unassignedCells() const
{
	vector<int> list; 
	for (int i = 0; i < 9; i++)
	{
		if (m_cells[i]->getAssigned() == false)
		{
			list.push_back(m_cells[i]->getID());
	    }
	}
	return list;
}

void CellGroup::nakedSingle()
{
	for (int i = 0; i < 9; i++)//find a single candidate cell
	{
		if (m_cells[i]->getAssigned() ==false)
		{
			vector<int> candidateList = m_cells[i]->getCandidateList();
			if (candidateList.size() == 1)
			{
				m_cells[i]->setValue(candidateList[0]);
			//	cout << "Naked Single at " << m_cells[i]->getID() << " set to " << candidateList[0] << endl;
			}
		}
		}
}
const bool CellGroup::solved()const //Method that checks if the array is solved by returning a boolean value. 
{
	int count = 0;
	//get all cell values stored and 
	for (int i = 0; i < 9; i++)
	{
		bool valueFound = m_cells[i]->getAssigned();
		if (valueFound== true)
		{
			count++;
		}
	}
	if(count == 9)
	return true; 

	return false; 

}

 vector<int> CellGroup::getValues() const   //Returns all values stored
{
	vector<int> values;
	//int count = 0;
	for (int i = 0; i < 9; ++i)
	{
		int valueFound = m_cells[i]->getValue();
		if (valueFound != 0)
		{
			values.push_back(valueFound);
		}
  }
	return values; 
}

 int CellGroup::getCellValue(int elementIndex) const
{
	int value; 
	value =  m_cells[elementIndex]->getValue(); //Derefrences the memory from the pointer done by -> symbol. 
	return  value;
}

