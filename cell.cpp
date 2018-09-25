#include "cell.h"

cell::cell(int value, int givenId) :m_candidateList({ 0 }), m_value(value), m_given(true), ID(givenId) //Constructor
{
//set the cells unique ID.
	if (m_value == 0)
		m_given = false;
	else
		m_given = true;
}
 const vector<int> & cell::getCandidateList() const
{
	 const vector<int> &list = m_candidateList;
	  return  list;
}


void cell::setValue(int value)
{
	m_value = value;
	m_given = true;
}

const bool cell::getAssigned()const
{
	return m_given; 
}

const int cell::getID() const
{
	return ID;
}
void cell::setCandidate(vector<int> const &candidateList)
{
	m_candidateList = candidateList;
}

const int cell::getValue() const
{
	return m_value;
}

cell::~cell()
{
}

