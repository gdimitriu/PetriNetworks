// PetriNetworkView.h : interface of the CPetriNetworkView class
//
/////////////////////////////////////////////////////////////////////////////
/*
	Copyright 2004 Gabriel Dimitriu

	This file is part of Petri Network.
	This class implements the View class for MDI.

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

#if !defined(AFX_PETRINETWORKVIEW_H__8E8F531C_1D6D_44CC_B999_54972DA9925B__INCLUDED_)
#define AFX_PETRINETWORKVIEW_H__8E8F531C_1D6D_44CC_B999_54972DA9925B__INCLUDED_
#include "PetriNetworkDoc.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CPetriNetworkDoc;

class CPetriNetworkView : public CView
{
	DECLARE_SERIAL(CPetriNetworkView)
protected: // create from serialization only
	CPetriNetworkView();

// Attributes
public:
	CPetriNetworkDoc* GetDocument();

// Operations
public:
	CClientDC *m_pdc;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPetriNetworkView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	float zoom;
	virtual void Serialize(CArchive &ar);
	virtual ~CPetriNetworkView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	CPoint tmpPoint;
	CPoint stPoint;
	//{{AFX_MSG(CPetriNetworkView)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	bool m_loadt;
	bool uptest;
	int test;
};

#ifndef _DEBUG  // debug version in PetriNetworkView.cpp
inline CPetriNetworkDoc* CPetriNetworkView::GetDocument()
   { return (CPetriNetworkDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PETRINETWORKVIEW_H__8E8F531C_1D6D_44CC_B999_54972DA9925B__INCLUDED_)
