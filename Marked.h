// Marked.h : header file
//
/////////////////////////////////////////////////////////////////////////////
/*
	Copyright 2004 Gabriel Dimitriu

	This file is part of Petri Network.
	This is the class used for simulate the Petri Networks: mJPN,mPN,mTPN.

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

#if !defined(AFX_MARKED_H__75C80ED3_DAC2_4824_A4D7_64947EAB1CD8__INCLUDED_)
#define AFX_MARKED_H__75C80ED3_DAC2_4824_A4D7_64947EAB1CD8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include<afxmt.h>
#include "PetriNetworkDoc.h"
#include "Value1.h"


// CMarked thread
class CPetriNetworkDoc;

class CMarked : public CWinThread
{
	DECLARE_DYNCREATE(CMarked)
protected:
	CMarked();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:
	CEvent *m_StartStop;
	CCriticalSection * m_Sincro;
	int Run();
	CMarked(int **Pre,int **Post,int nrL,int nrT,int *mark,int *delay,CCriticalSection *sec,int *oper,CEvent *event,CPetriNetworkDoc *pdoc,int type,CObArray *jump);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMarked)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CMarked();

	// Generated message map functions
	//{{AFX_MSG(CMarked)
	//}}AFX_MSG
private:
	int m_max;
	void mTPN();
	void mJPN();
	void mPN();
	HANDLE m_handlepriv;
	int **m_Pre;
	int **m_Post;
	int **m_Delta;
	int *m_mark;
	int *execc;
	int *m_Pret;
	int *m_oper;
	int *m_jump;
	int *m_delay;
	int *m_Ro;
	bool *m_exclude;
	int m_nrLoc;
	int m_nrTran;
	int m_Oper;
	int m_Type;
	bool flag;
	long val;
	CObArray *JumpRel;
	int concurent;
	CValue1 valtemp;
	CString valstr;
	CPetriNetworkDoc *m_pDoc;
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MARKED_H__75C80ED3_DAC2_4824_A4D7_64947EAB1CD8__INCLUDED_)
