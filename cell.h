#pragma once
using namespace std;
#include <vector>
class cell
{
public:
	cell(int val, int givenId);
	~cell();
	void setValue(int val); //set
	void setCandidate(vector<int> const &candidateList);
    const vector<int> & getCandidateList() const;
	const int getValue() const; //get
	const bool getAssigned() const;
	const int getID() const; //get
	
private:

	vector<int> m_candidateList ; // or int m_candidateList[9];
	int m_value; 
	bool m_given; //if value false then it un-assigned. 
	int ID;  //Unique number to reference the cell. 
};

