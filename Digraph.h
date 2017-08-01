// Digraph.h : header file
//
/*
	Copyright 2004 Gabriel Dimitriu

	This file is part of Petri Network.
	This is the class used for simulation the graphs and digraphs structures.

    Petri Network is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    Petri Network is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Petri Network; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  
*/

#if !defined(AFX_DIGRAPH_H__62EA8BC7_B4BB_42DD_9827_FCEEFD17C4EE__INCLUDED_)
#define AFX_DIGRAPH_H__62EA8BC7_B4BB_42DD_9827_FCEEFD17C4EE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include<afxmt.h>
#include "PetriNetworkDoc.h"
#include "Value1.h"
#include "Ask.h"
#include "dimensions.h"
#include <fstream>
#include "Queue.h"
#include "MinMax.h"
using namespace std ;

/////////////////////////////////////////////////////////////////////////////
// CDigraph thread

class CDigraph : public CWinThread
{
	DECLARE_DYNCREATE(CDigraph)
protected:
	CDigraph();           // protected constructor used by dynamic creation

// Attributes
public:
// Operations
public:
	CEvent *m_StartStop;
	CCriticalSection * m_Sincro;
	int Run();
	CDigraph(int nrL,CCriticalSection *sec,int *oper,CEvent *event,CPetriNetworkDoc *pdoc,int type,int *oper1,int **mat,int inf);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDigraph)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CDigraph();

	// Generated message map functions
	//{{AFX_MSG(CDigraph)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
private:
	bool run_bk();
	bool init_bk();
	bool run_prim();
	bool init_prim();
	bool run_kruskal();
	bool init_kruskal();
	void init_min_cost();
	void init_eulerian();
	void run_eulerian();
	void run_min_cost();
	void Eulerian_Cycle(int i);
	bool Merimont(void);
	bool Conexity(bool automata);

	int stepe;
	struct qelement
	{
		int i;
		int j;
		int val;
		struct qelement *next;
	};
	struct qelement* queue;
	bool teaching;
	int old;
	CDigraph::qelement *createQ(int nr,int **mat);
	CDigraph::qelement *getQ(CDigraph::qelement *coada,int *i,int *j,int *val);
	CValue1 valtemp;
	CAsk askYN;
	CString valstr;
	CPetriNetworkDoc *m_pDoc;
	HANDLE m_handlepriv;
	
	CString m_afisaj;
	CString m_result;
	int m_start;
	int m_end;
	int m_cost;
	int m_tval;
	int m_j;
	int m_i;
	int m_infinite;
	int m_nrLoc;
	int m_Oper;
	int *m_L;
	int *m_L1;
	int *m_oper;
	int *m_opgraph;
	int **m_mat;
	int ** m_emat;
	int ** m_tmat;
	int m_Type;
	bool m_file;
	bool m_conex;
	bool m_minmax; //true=max, false=min
	long m_arcs;
	bool m_cyclic; //true for ciclic
	
	bool flag;
	long val;
	int nr_ram;
	int grad;
	int element;
	int *tempm;
	ofstream ofile;
	CQueue *m_queues;
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIGRAPH_H__62EA8BC7_B4BB_42DD_9827_FCEEFD17C4EE__INCLUDED_)
