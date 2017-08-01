// Queue.cpp: implementation of the CQueue class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PetriNetwork.h"
#include "Queue.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CQueue::CQueue()
{
	m_head=NULL;
}

CQueue::~CQueue()
{
	while(m_head!=NULL)
	{
		nod=m_head;
		m_head=m_head->next;
		free(nod);
	}
}
void CQueue::create(int nr,int **mat,bool type)
{
	/*
		This function creates a queue of qelement structure.
		It is called in case of min cost tree.
	*/
	int i,j,k;
	m_head=NULL;
	for(i=0;i<nr;i++)
	{
		if(type==true) //digraf
			k=0;
		else k=i;
		for(j=k;j<nr;j++)
		{
			if(mat[i][j]!=0)
			{
      			if(m_head==NULL)
				{
         			m_head=(struct qelement *)calloc(1,sizeof(struct qelement));
					m_head->next=NULL;
					m_head->i=i;
					m_head->j=j;
					m_head->val=mat[i][j];
				}
				else
				{
         			nod=(struct qelement *)calloc(1,sizeof(struct qelement));
					nod->i=i;
					nod->j=j;
					nod->val=mat[i][j];
					curent=m_head;
					temp=NULL;
					nod->next=NULL;
					while(curent!=NULL)
					{
						if(nod->val<=curent->val)
						{
               				if(temp==NULL)
							{
	               				nod->next=m_head;
   								m_head=nod;
								break;
							}
							else
							{
                  				temp->next=nod;
								nod->next=curent;
								break;
							}
						}
						else
						{
							temp=curent;
							curent=curent->next;
						}
					}
					if(curent==NULL) temp->next=nod;
				}
			}
		}
	}
}

void CQueue::get(int *i,int *j,int *val)
{
	/*
		This function gets an element from a queue of qelement structure.
		It is called in case of min cost tree.
	*/
	*i=m_head->i;
	*j=m_head->j;
	*val=m_head->val;
	temp=m_head;
	m_head=m_head->next;
	free(temp);
}

void CQueue::add(int i, int j, int val)
{
	if(val!=0)
	{
    	if(m_head==NULL)
		{
    		m_head=(struct qelement *)calloc(1,sizeof(struct qelement));
			m_head->next=NULL;
			m_head->i=i;
			m_head->j=j;
			m_head->val=val;
		}
		else
		{
        	nod=(struct qelement *)calloc(1,sizeof(struct qelement));
			nod->i=i;
			nod->j=j;
			nod->val=val;
			curent=m_head;
			temp=NULL;
			nod->next=NULL;
			while(curent!=NULL)
			{
				if(nod->val<=curent->val)
				{
            		if(temp==NULL)
					{
	           			nod->next=m_head;
   						m_head=nod;
						break;
					}
					else
					{
                  		temp->next=nod;
						nod->next=curent;
						break;
					}
				}
				else
				{
					temp=curent;
					curent=curent->next;
				}
			}
			if(curent==NULL) temp->next=nod;
		}
	}
}

bool CQueue::empty()
{
	if(m_head==NULL) return true;
	else return false;
}
