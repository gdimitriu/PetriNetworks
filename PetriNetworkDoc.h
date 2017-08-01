// PetriNetworkDoc.h : interface of the CPetriNetworkDoc class
//
/////////////////////////////////////////////////////////////////////////////
/*
	Copyright 2004 Gabriel Dimitriu

	This file is part of Petri Network.
	This is the main class (document class) for Petri Network Simulator.

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

#if !defined(AFX_PETRINETWORKDOC_H__6013CDC0_F171_4DE0_ACB0_8CC47E3871CD__INCLUDED_)
#define AFX_PETRINETWORKDOC_H__6013CDC0_F171_4DE0_ACB0_8CC47E3871CD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Location.h"
#include "Transition.h"
#include "Marked.h"
#include "Digraph.h"
#include "Arcs.h"
#include "JumpTable.h"
#include "PetriNetworkView.h"
#include<list>
#include<string>
#include<afxmt.h>
#include "dimensions.h"

class CPetriNetworkView;
class CMarked;
class CDigraph;
class CLocation;
class CTransition;
class CArcs;
using namespace std ;

class CPetriNetworkDoc : public CDocument
{
	DECLARE_SERIAL(CPetriNetworkDoc)
protected: // create from serialization only
	CPetriNetworkDoc();


// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPetriNetworkDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual void DeleteContents();
	//}}AFX_VIRTUAL

// Implementation
public:
	void SetView(CPetriNetworkView *pv);
	void SetDC(CDC *pdc);
	void AddArc(int i, int j, int val);
	void RemoveArc(int start,int stop);
	void Zoom(float zoom);
	void Move(CPoint point,CDC *pdc);
	void SetState(int state);
	void Auto(CDC *pdc,CPetriNetworkView *pv);
	bool TestState(int pos,int flag);
	void ReMark(bool flag);
	void PutDoc(CDC *pdc,CPetriNetworkView *pv);
	void AddMark(CPoint point);
	void UnMark(CPoint point);
	CArcs * GetArc(int nIndex);
	CArcs * GetWArc();
	int GetCountArcs();
	void ResetArc(CPoint point,CDC *pdc);
	void AddArc(CPoint point,CDC *pdc);
	void DeleteLocation(CPoint point,CDC *pdc);
	void DeleteTransition(CPoint point,CDC *pdc);
	void DeleteArc(CPoint point,CDC *pdc);
	void ResetLocation();
	void ResetTransition();
	void GetLocation(CPoint point);
	void GetTransition(CPoint point);
	CTransition* GetMoveTransition();
	CLocation * GetMoveLocation();
	int GetState();
	int GetCountLocation();
	int GetCountTransition();
	CLocation * GetLocation(int nIndex);
	CTransition * GetTransition(int nIndex);
	CLocation *AddLocation(CPoint point,bool flag,int pos);
	CTransition *AddTransition(CPoint point,bool flag,int pos);
	virtual ~CPetriNetworkDoc();
	list<int> m_darce;
	list<int>::iterator m_itint;
	int m_Oper;
	int * m_Mark;
	int ** m_Post;
	int ** m_Pre;
	int **m_mat;
	int * m_Delay;
	int m_nTransition;
	int m_nLocation;
	int nr_points;
	int m_inf;
	float dim;
	float dimsgn;
	bool m_load;
private:
	void SortTransition(void);
	void SortLocation(void);
	void AlocateMatrix();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CDC* pDC;
	CEvent *m_StartStop;
	CPetriNetworkView *m_View;
	CArcs *m_warc;			//arc who is moving
	CLocation *m_mLocation; //location who is moving
	CTransition *m_mTransition; //transition who is moving
	CObArray m_LocationArray;
	CObArray m_TransitionArray;
	CObArray m_ArcsArray;
	CObArray m_JumpArray;
	int m_state;
	/*
		0 is location
		1 is transition
		2 is arc
		3 is move location
		4 is move transition
		5 is delete location
		6 is delete transition
		7 is arc from 2 points
		8 is mark point
		9 is arc from 4 points
		10 is delete arc
		11 is unmark point
		20 is pan (move entire project)
		21 is zoom in
		22 is zoon out
	*/
	CMarked *simmark;
	CDigraph *simdig;
	CCriticalSection *m_CS;
// Generated message map functions
protected:
	int m_Type;
	//0 is marked Petri Network
	//1 is marked Temporizate Petri Network
	//2 is marked Jump Petri Network
	//-1 is Graph
	//-2 is DiGraph
	int *m_opgraph;
	bool *m_fopgraph;
	//[0] is conexity
	//[1] is maximum cost
	//[2] is eulerian cycle
	//[3] is tree min cost
	//[4] is Kruskal
	//[5] is Prim
	//[6] is Bellman Kalaba
	//{{AFX_MSG(CPetriNetworkDoc)
	afx_msg void OnArc();
	afx_msg void OnUpdateArc(CCmdUI* pCmdUI);
	afx_msg void OnLocation();
	afx_msg void OnUpdateLocation(CCmdUI* pCmdUI);
	afx_msg void OnTransition();
	afx_msg void OnMoveLocation();
	afx_msg void OnUpdateMoveLocation(CCmdUI* pCmdUI);
	afx_msg void OnDeleteLocation();
	afx_msg void OnUpdateDeleteLocation(CCmdUI* pCmdUI);
	afx_msg void OnArc2p();
	afx_msg void OnUpdateArc2p(CCmdUI* pCmdUI);
	afx_msg void OnMark();
	afx_msg void OnUpdateMark(CCmdUI* pCmdUI);
	afx_msg void OnArc4p();
	afx_msg void OnUpdateArc4p(CCmdUI* pCmdUI);
	afx_msg void Simulate();
	afx_msg void Generate();
	afx_msg void ContinueSim();
	afx_msg void ExitSim();
	afx_msg void StopSim();
	afx_msg void OnDeleteArc();
	afx_msg void OnUpdateDeleteArc(CCmdUI* pCmdUI);
	afx_msg void OnLoad();
	afx_msg void OnUnmark();
	afx_msg void OnUpdateUnmark(CCmdUI* pCmdUI);
	afx_msg void OnmJPN();
	afx_msg void OnUpdatemJPN(CCmdUI* pCmdUI);
	afx_msg void OnmPN();
	afx_msg void OnUpdatemPN(CCmdUI* pCmdUI);
	afx_msg void OnUpdateTransition(CCmdUI* pCmdUI);
	afx_msg void OnUpdateStop(CCmdUI* pCmdUI);
	afx_msg void OnJump();
	afx_msg void OnDeleteTran();
	afx_msg void OnUpdateDeleteTran(CCmdUI* pCmdUI);
	afx_msg void OnMoveTran();
	afx_msg void OnUpdateMoveTran(CCmdUI* pCmdUI);
	afx_msg void OnGraph();
	afx_msg void OnUpdateGraph(CCmdUI* pCmdUI);
	afx_msg void OnDigraph();
	afx_msg void OnUpdateDigraph(CCmdUI* pCmdUI);
	afx_msg void OnmTPN();
	afx_msg void OnUpdatemTPN(CCmdUI* pCmdUI);
	afx_msg void OnPn();
	afx_msg void OnUpdatePn(CCmdUI* pCmdUI);
	afx_msg void OnCnx();
	afx_msg void OnUpdateCnx(CCmdUI* pCmdUI);
	afx_msg void OnCiclicity();
	afx_msg void OnUpdateCiclicity(CCmdUI* pCmdUI);
	afx_msg void OnMinCost();
	afx_msg void OnUpdateMinCost(CCmdUI* pCmdUI);
	afx_msg void OnPan();
	afx_msg void OnUpdatePan(CCmdUI* pCmdUI);
	afx_msg void OnZoomIn();
	afx_msg void OnUpdateZoomIn(CCmdUI* pCmdUI);
	afx_msg void OnZoomOut();
	afx_msg void OnUpdateZoomOut(CCmdUI* pCmdUI);
	afx_msg void OnEuler();
	afx_msg void OnUpdateEuler(CCmdUI* pCmdUI);
	afx_msg void OnBk();
	afx_msg void OnUpdateBk(CCmdUI* pCmdUI);
	afx_msg void OnKruskal();
	afx_msg void OnUpdateKruskal(CCmdUI* pCmdUI);
	afx_msg void OnPrim();
	afx_msg void OnUpdatePrim(CCmdUI* pCmdUI);
	afx_msg void Onselect();
	afx_msg void OnUpdateselect(CCmdUI* pCmdUI);
	afx_msg void Onredone();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PETRINETWORKDOC_H__6013CDC0_F171_4DE0_ACB0_8CC47E3871CD__INCLUDED_)
