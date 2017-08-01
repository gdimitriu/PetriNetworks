// PetriNetworkView.cpp : implementation of the CPetriNetworkView class
//
/*
	Copyright 2004 Gabriel Dimitriu

	This file is part of Petri Network.

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

#include "stdafx.h"
#include "PetriNetwork.h"

#include "PetriNetworkDoc.h"
#include "PetriNetworkView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
IMPLEMENT_SERIAL(CPetriNetworkView, CView,1)
/////////////////////////////////////////////////////////////////////////////
// CPetriNetworkView


BEGIN_MESSAGE_MAP(CPetriNetworkView, CView)
	//{{AFX_MSG_MAP(CPetriNetworkView)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_CONTEXTMENU()
	ON_WM_CHAR()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPetriNetworkView construction/destruction

CPetriNetworkView::CPetriNetworkView()
{
	/*
		This is the constructor for View class.
	*/
	m_pdc=NULL;
	uptest=false;
	m_loadt=false;
	zoom=1.0;
}

CPetriNetworkView::~CPetriNetworkView()
{
	/*
		This is the destructor for View class.
	*/
	if(m_pdc!=NULL) delete m_pdc;
}

BOOL CPetriNetworkView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CPetriNetworkView drawing

void CPetriNetworkView::OnDraw(CDC* pDC)
{
	/*
		This function draws the entire design.
	*/
	CPetriNetworkDoc* pDoc = GetDocument();
	ASSERT(pDoc!=NULL);
	//My code
	int Count;
	int Pos;
	Count=pDoc->GetCountLocation();
	if(Count) //we have Locations
	{
		CLocation *ploc;
		for(Pos=0;Pos<Count;Pos++)
		{
			ploc=pDoc->GetLocation(Pos);
			ploc->Draw(pDC);
		}
	}
	Count=pDoc->GetCountTransition();
	if(Count) //we have Transitions
	{
		CTransition *ploc;
		for(Pos=0;Pos<Count;Pos++)
		{
			ploc=pDoc->GetTransition(Pos);
			ploc->Draw(pDC);
		}
	}
	Count=pDoc->GetCountArcs();
	if(Count) //we have Arcs
	{
		CArcs *parc;
		for(Pos=0;Pos<Count;Pos++)
		{
			parc=pDoc->GetArc(Pos);
			parc->Draw(pDC);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
// CPetriNetworkView printing

BOOL CPetriNetworkView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CPetriNetworkView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CPetriNetworkView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CPetriNetworkView diagnostics

#ifdef _DEBUG
void CPetriNetworkView::AssertValid() const
{
	CView::AssertValid();
}

void CPetriNetworkView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPetriNetworkDoc* CPetriNetworkView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPetriNetworkDoc)));
	return (CPetriNetworkDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPetriNetworkView message handlers

void CPetriNetworkView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	/*
		This function implents the Left Button Down of the mouse.
		In function of the state of the document we do different operation.
	*/
	SetCapture();
//	CClientDC dc(this);
	if(m_pdc==NULL) m_pdc=new CClientDC(this);
	switch (GetDocument()->GetState())
	{
	case 0: //add a location
		{
			CLocation *plocation=GetDocument()->AddLocation(point,true,0);
			if(plocation!=NULL)
				//plocation->Draw(&dc);
				plocation->Draw(m_pdc);
			break;
		}
	case 1: //add a transition
		{
			CTransition *ptransition=GetDocument()->AddTransition(point,true,0);
			if(ptransition!=NULL)
				//ptransition->Draw(&dc);
				ptransition->Draw(m_pdc);
			break;
		}
	case 2: //add an arc with multiple points
		{
			//GetDocument()->AddArc(point,&dc);
			GetDocument()->AddArc(point,m_pdc);
			break;
		}
	case 3: //move a location
		{
			GetDocument()->GetLocation(point);
			break;
		}
	case 4: //move a transition
		{
			GetDocument()->GetTransition(point);
			break;
		}
	case 5: //erase a location
		{
			//GetDocument()->DeleteLocation(point,&dc);
			GetDocument()->DeleteLocation(point,m_pdc);
			break;
		}
	case 6: //erase a transition
		{
			//GetDocument()->DeleteTransition(point,&dc);
			GetDocument()->DeleteTransition(point,m_pdc);
			break;
		}
	case 10: //erase an arc
		{
			//GetDocument()->DeleteArc(point,&dc);
			GetDocument()->DeleteArc(point,m_pdc);
			break;
		}
	case 7: //create an arc with 2 points
		{
			if(GetDocument()->nr_points==0)
			{
				//GetDocument()->AddArc(point,&dc);
				GetDocument()->AddArc(point,m_pdc);
				GetDocument()->nr_points++;
			}
			else if(GetDocument()->nr_points==1)
			{
				CArcs *larc=GetDocument()->GetWArc();
				if(larc!=NULL)
					//larc->AddPoint(point,&dc);
					larc->AddPoint(point,m_pdc);
				//GetDocument()->ResetArc(point,&dc);
				GetDocument()->ResetArc(point,m_pdc);
			}
			else GetDocument()->nr_points=0;
			break;
		}
	case 8: //add a mark to a location
		{
			GetDocument()->AddMark(point);
//			if(m_pdc!=NULL) delete m_pdc;
//			m_pdc=new CClientDC(this);
			GetDocument()->PutDoc(m_pdc,this);
			break;
		}
	case 9: //create an arc with 4 points
		{
			if(GetDocument()->nr_points==0)
			{
				//GetDocument()->AddArc(point,&dc);
				GetDocument()->AddArc(point,m_pdc);
				GetDocument()->nr_points++;
			}
			else if(GetDocument()->nr_points<3)
			{
				CArcs *larc=GetDocument()->GetWArc();
				if(larc!=NULL)
				{
					//larc->AddPoint(point,&dc);
					larc->AddPoint(point,m_pdc);
					GetDocument()->nr_points++;
				}
			}
			else if(GetDocument()->nr_points==3)
			{
				CArcs *larc=GetDocument()->GetWArc();
				if(larc!=NULL)
				{
					//larc->AddPoint(point,&dc);
					larc->AddPoint(point,m_pdc);
					//GetDocument()->ResetArc(point,&dc);
					GetDocument()->ResetArc(point,m_pdc);
				}
				GetDocument()->nr_points=0;
			}
			else GetDocument()->nr_points=0;
			break;
		}
	case 11: //decrease with 1 the mark of a location
		{
			GetDocument()->UnMark(point);
			//if(m_pdc!=NULL) delete m_pdc;
			//m_pdc=new CClientDC(this);
			GetDocument()->PutDoc(m_pdc,this);
			break;
		}
	case 20: //pan the design
		{
			stPoint=point;
			break;
		}
	case 21: //zoom in
		{
			zoom+=(float)0.2;
			GetDocument()->Zoom(zoom);
			break;
		}
	case 22: //zoom out
		{
			zoom-=(float)0.2; 
			GetDocument()->Zoom(zoom);
			break;
		}
	}
//	OnDraw(&dc);
	OnDraw(m_pdc);
	CView::OnLButtonDown(nFlags, point);
}

void CPetriNetworkView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	/*
		This function implents the Left Button Down of the mouse.
		In function of the state of the document we do different operation.
	*/
//	CClientDC dc(this);
	if(GetCapture()==this)
	{
		//is so release it for other application
		ReleaseCapture();
		switch (GetDocument()->GetState())
		{
		case 2://add an arc with multiple points
			{
				//GetDocument()->ResetArc(point,&dc);
				//OnDraw(&dc);
				GetDocument()->ResetArc(point,m_pdc);
				OnDraw(m_pdc);
				break;
			}
		case 3://move a location
			{
				GetDocument()->ResetLocation();
				break;
			}
		case 4://move a transition
			{
				GetDocument()->ResetTransition();
				break;
			}
		case 20: //pan the entire design
			{
				GetDocument()->SetState(0);
				break;
			}
		case 21://zoom in
			{
				zoom=1.0;
				break;
			}
		case 22: //zoom out
			{
				zoom=1.0;
				break;
			}
		}
	}
	CView::OnLButtonUp(nFlags, point);
}

void CPetriNetworkView::OnMouseMove(UINT nFlags, CPoint point) 
{	
	/*
		This function implents the mouse movement.
		In function of the state of the document we do different operation.
	*/
	//first time capture the view
	if(uptest==false)
	{
		SetCapture();
		//if(m_pdc!=NULL){ delete m_pdc; m_pdc=NULL);}
		if(m_pdc==NULL) m_pdc=new CClientDC(this);
		GetDocument()->PutDoc(m_pdc,this);
		GetDocument()->Auto(m_pdc,this);
		uptest=true;
		ReleaseCapture();
	}
	//for auto
	if(m_loadt==false && GetDocument()->m_load==true)
		{
			SetCapture();
			if(m_pdc!=NULL) delete m_pdc;
			m_pdc=new CClientDC(this);
			GetDocument()->Auto(m_pdc,this);
			m_loadt=true;
			ReleaseCapture();
		}
	if(GetDocument()->GetState()==23) //set view
	{
		SetCapture();
		if(m_pdc!=NULL) delete m_pdc;
		m_pdc=new CClientDC(this);
		GetDocument()->SetDC(m_pdc);
		GetDocument()->SetView(this);
		ReleaseCapture();
	}
	tmpPoint=point-stPoint;
	stPoint=point;
	if((nFlags & MK_LBUTTON)==MK_LBUTTON)
	{
		if(GetCapture()==this)
		{
			//CClientDC dc(this); //get device context
			switch(GetDocument()->GetState())
			{
			case 2:
				{
					CArcs *larc=GetDocument()->GetWArc();
					if(larc!=NULL)
						//larc->AddPoint(point,&dc);
						larc->AddPoint(point,m_pdc);
					break;
				}
			case 3://for move location
				{
					CLocation *tloc=GetDocument()->GetMoveLocation();
					if(tloc!=NULL)
						//tloc->MoveLocation(point,&dc);
						tloc->MoveLocation(point,m_pdc);
					break;
				}
			case 4://for move transition
				{
					CTransition *ttran=GetDocument()->GetMoveTransition();
					if(ttran!=NULL)
						//ttran->MoveTransition(point,&dc);
						ttran->MoveTransition(point,m_pdc);
					break;
				}
			case 20: //for pan
				{
					//GetDocument()->Move(tmpPoint,&dc);
					GetDocument()->Move(tmpPoint,m_pdc);
					break;
				}
			}
			//OnDraw(&dc);
			OnDraw(m_pdc);
		}
	}
	CView::OnMouseMove(nFlags, point);
}

void CPetriNetworkView::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	test=0;
	CMenu menu;
	// Load the context menu
	menu.LoadMenu(IDR_CONTEXTMENU);
	// Get the first sub menu (the real menu)
	CMenu *pContextMenu = menu.GetSubMenu(0);

	// Display the context menu for the user
	pContextMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_RIGHTBUTTON,
		point.x, point.y, AfxGetMainWnd());
}

void CPetriNetworkView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	char temp;
	temp=char(nChar);
	if(temp=='w' && test==0) test++;
	else if(temp=='h' && test==1) test++;
	else if(temp=='o'&& test==2) test++;
	else test=0;
	if(test==3)
	{
		AfxMessageBox("Copyright 2004 Gabriel Dimitriu");	
		test=0;
	}
	CView::OnChar(nChar, nRepCnt, nFlags);
}

void CPetriNetworkView::Serialize(CArchive &ar)
{
	/*
		This functions serializes the View.
	*/
	CView::Serialize(ar);
	if(!ar.IsStoring())
	{
		uptest=false;
		m_pdc=NULL;
	}
}

