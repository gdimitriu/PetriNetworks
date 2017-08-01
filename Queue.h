// Queue.h: interface for the CQueue class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_QUEUE_H__1645DD41_3100_11DB_B910_BACAAEF13902__INCLUDED_)
#define AFX_QUEUE_H__1645DD41_3100_11DB_B910_BACAAEF13902__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CQueue : public CObject  
{
public:
	bool empty();
	void add(int i,int j,int val);
	CQueue();
	void create(int nr,int **mat,bool type);
	void get(int *i,int *j,int *val);
	virtual ~CQueue();
protected:
	struct qelement
	{
		int i;
		int j;
		int val;
		struct qelement *next;
	};
	qelement *nod,*curent,*temp;
	qelement *m_head;
};

#endif // !defined(AFX_QUEUE_H__1645DD41_3100_11DB_B910_BACAAEF13902__INCLUDED_)
