// PetriNetworkDoc.cpp : implementation of the CPetriNetworkDoc class
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
#include "Value1.h"
#include "InJump.h"
#include <malloc.h>
#include <fstream>
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
IMPLEMENT_SERIAL(CPetriNetworkDoc,CDocument,1)
/////////////////////////////////////////////////////////////////////////////
// CPetriNetworkDoc

BEGIN_MESSAGE_MAP(CPetriNetworkDoc, CDocument)
	//{{AFX_MSG_MAP(CPetriNetworkDoc)
	ON_COMMAND(ID_ARC, OnArc)
	ON_UPDATE_COMMAND_UI(ID_ARC, OnUpdateArc)
	ON_COMMAND(ID_LOCATION, OnLocation)
	ON_UPDATE_COMMAND_UI(ID_LOCATION, OnUpdateLocation)
	ON_COMMAND(ID_TRANSITION, OnTransition)
	ON_COMMAND(ID_MOVE_LOCATION, OnMoveLocation)
	ON_UPDATE_COMMAND_UI(ID_MOVE_LOCATION, OnUpdateMoveLocation)
	ON_COMMAND(ID_DELETE_LOCATION, OnDeleteLocation)
	ON_UPDATE_COMMAND_UI(ID_DELETE_LOCATION, OnUpdateDeleteLocation)
	ON_COMMAND(ID_ARC_2P, OnArc2p)
	ON_UPDATE_COMMAND_UI(ID_ARC_2P, OnUpdateArc2p)
	ON_COMMAND(ID_MARK, OnMark)
	ON_UPDATE_COMMAND_UI(ID_MARK, OnUpdateMark)
	ON_COMMAND(ID_ARC_4P, OnArc4p)
	ON_UPDATE_COMMAND_UI(ID_ARC_4P, OnUpdateArc4p)
	ON_COMMAND(ID_START, Simulate)
	ON_COMMAND(ID_GENERATE, Generate)
	ON_COMMAND(ID_CONTINUE, ContinueSim)
	ON_COMMAND(ID_SEXIT, ExitSim)
	ON_COMMAND(ID_STOP, StopSim)
	ON_COMMAND(ID_DELETE_ARC, OnDeleteArc)
	ON_UPDATE_COMMAND_UI(ID_DELETE_ARC, OnUpdateDeleteArc)
	ON_COMMAND(ID_LOAD, OnLoad)
	ON_COMMAND(ID_UNMARK, OnUnmark)
	ON_UPDATE_COMMAND_UI(ID_UNMARK, OnUpdateUnmark)
	ON_COMMAND(ID_mJPN, OnmJPN)
	ON_UPDATE_COMMAND_UI(ID_mJPN, OnUpdatemJPN)
	ON_COMMAND(ID_mPN, OnmPN)
	ON_UPDATE_COMMAND_UI(ID_mPN, OnUpdatemPN)
	ON_UPDATE_COMMAND_UI(ID_TRANSITION, OnUpdateTransition)
	ON_UPDATE_COMMAND_UI(ID_STOP, OnUpdateStop)
	ON_COMMAND(ID_JUMP, OnJump)
	ON_COMMAND(ID_DELETE_TRAN, OnDeleteTran)
	ON_UPDATE_COMMAND_UI(ID_DELETE_TRAN, OnUpdateDeleteTran)
	ON_COMMAND(ID_MOVE_TRAN, OnMoveTran)
	ON_UPDATE_COMMAND_UI(ID_MOVE_TRAN, OnUpdateMoveTran)
	ON_COMMAND(ID_GRAPH, OnGraph)
	ON_UPDATE_COMMAND_UI(ID_GRAPH, OnUpdateGraph)
	ON_COMMAND(ID_DIGRAPH, OnDigraph)
	ON_UPDATE_COMMAND_UI(ID_DIGRAPH, OnUpdateDigraph)
	ON_COMMAND(ID_mTPN, OnmTPN)
	ON_UPDATE_COMMAND_UI(ID_mTPN, OnUpdatemTPN)
	ON_COMMAND(ID_PN, OnPn)
	ON_UPDATE_COMMAND_UI(ID_PN, OnUpdatePn)
	ON_COMMAND(ID_CNX, OnCnx)
	ON_UPDATE_COMMAND_UI(ID_CNX, OnUpdateCnx)
	ON_COMMAND(ID_CICLICITY, OnCiclicity)
	ON_UPDATE_COMMAND_UI(ID_CICLICITY, OnUpdateCiclicity)
	ON_COMMAND(ID_MIN_COST, OnMinCost)
	ON_UPDATE_COMMAND_UI(ID_MIN_COST, OnUpdateMinCost)
	ON_COMMAND(ID_PAN, OnPan)
	ON_UPDATE_COMMAND_UI(ID_PAN, OnUpdatePan)
	ON_COMMAND(ID_ZOOM_IN, OnZoomIn)
	ON_UPDATE_COMMAND_UI(ID_ZOOM_IN, OnUpdateZoomIn)
	ON_COMMAND(ID_ZOOM_OUT, OnZoomOut)
	ON_UPDATE_COMMAND_UI(ID_ZOOM_OUT, OnUpdateZoomOut)
	ON_COMMAND(ID_EULER, OnEuler)
	ON_UPDATE_COMMAND_UI(ID_EULER, OnUpdateEuler)
	ON_COMMAND(ID_BK, OnBk)
	ON_UPDATE_COMMAND_UI(ID_BK, OnUpdateBk)
	ON_COMMAND(ID_KRUSKAL, OnKruskal)
	ON_UPDATE_COMMAND_UI(ID_KRUSKAL, OnUpdateKruskal)
	ON_COMMAND(ID_PRIM, OnPrim)
	ON_UPDATE_COMMAND_UI(ID_PRIM, OnUpdatePrim)
	ON_COMMAND(ID_select, Onselect)
	ON_UPDATE_COMMAND_UI(ID_select, OnUpdateselect)
	ON_COMMAND(ID_redone, Onredone)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPetriNetworkDoc construction/destruction

CPetriNetworkDoc::CPetriNetworkDoc()
{
	/*
		This is the constructor for the Petri Network document.
	*/
	m_Pre=NULL;
	m_Post=NULL;
	m_Mark=NULL;
	m_Delay=NULL;
	m_mat=NULL;
	nr_points=0;
	m_load=false;
	m_Type=0;
	m_CS=NULL;
	m_StartStop=NULL;
	m_opgraph=new int[OPDIM];
	m_fopgraph=new bool[OPDIM];
	for(int i=0;i<OPDIM;i++)
	{
		m_opgraph[i]=0;
		m_fopgraph[i]=false;
	}
	m_inf=0;
	dim=20.0;
	dimsgn=3.0;
}

CPetriNetworkDoc::~CPetriNetworkDoc()
{
	/*
		This function is the destuctor for the Petri Network Document.
	*/
	if(m_Post!=NULL)
	{
		free(*m_Post);
		free(m_Post);
		m_Post=NULL;
	}
	if(m_Pre!=NULL)
	{
		free(*m_Pre);
		free(m_Pre);
		m_Pre=NULL;
	}
	if(m_Mark!=NULL)
	{
		free(m_Mark);
		m_Mark=NULL;
	}
	if(m_Delay!=NULL)
	{
		free(m_Delay);
		m_Delay=NULL;
	}
	if(m_CS!=NULL)
	{
		m_CS->Unlock();
		delete m_CS;
	}
	if(m_StartStop!=NULL)
	{
		m_StartStop->Unlock();
		delete m_StartStop;
	}
	delete [] m_opgraph;
	delete [] m_fopgraph;
}

BOOL CPetriNetworkDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	// (SDI documents will reuse this document)
	m_state=-1;
	nr_points=0;
	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CPetriNetworkDoc serialization

void CPetriNetworkDoc::Serialize(CArchive& ar)
{
	/*
		This function serialize the document.
	*/
	int i,j;
	CDocument::Serialize(ar);
	if (ar.IsStoring())
	{
		ar<<m_Type;
	}
	else
	{
		ar>>m_Type;
	}
	m_LocationArray.Serialize(ar);
	m_ArcsArray.Serialize(ar);
	for(i=0;i<m_ArcsArray.GetSize();i++)
		((CArcs *)m_ArcsArray[i])->m_Type=m_Type;
	if(m_Type>=0)
	{
		m_TransitionArray.Serialize(ar);
		m_JumpArray.Serialize(ar);
	}
	if (!ar.IsStoring())
	{
		if(m_Type>=0)
		{
			CLocation *ploc;
			CTransition *ptran;
			CArcs *parc;
			for(i=0;i<m_ArcsArray.GetSize();i++)
			{
				parc=(CArcs*)m_ArcsArray[i];
				if(parc->reuse[0]==-1)
				{
					for(j=0;j<m_LocationArray.GetSize();j++)
						if(((CLocation *)m_LocationArray[j])->position==parc->reuse[2])
						{
							ploc=(CLocation *)m_LocationArray[j];
							break;
						}
					for(j=0;j<m_TransitionArray.GetSize();j++)
						if(((CTransition *)m_TransitionArray[j])->position==parc->reuse[1])
						{
							ptran=(CTransition *)m_TransitionArray[j];
							break;
						}
					parc->AddLocTrn(ploc,ptran);
					ploc->AddOutputArc(parc);
					ptran->AddInputArc(parc);
				}
				else
				{
					for(j=0;j<m_LocationArray.GetSize();j++)
						if(((CLocation *)m_LocationArray[j])->position==parc->reuse[0])
						{
							ploc=(CLocation *)m_LocationArray[j];
							break;
						}
					for(j=0;j<m_TransitionArray.GetSize();j++)
						if(((CTransition *)m_TransitionArray[j])->position==parc->reuse[3])
						{
							ptran=(CTransition *)m_TransitionArray[j];
							break;
						}
					parc->AddTrnLoc(ptran,ploc);
					ptran->AddOutputArc(parc);
					ploc->AddInputArc(parc);
				}
			}
		}
		else
		{
			CLocation *ploc1,*ploc2;
			CArcs *parc;
			for(i=0;i<m_ArcsArray.GetSize();i++)
			{
				parc=(CArcs*)m_ArcsArray[i];
				for(j=0;j<m_LocationArray.GetSize();j++)
					if(((CLocation *)m_LocationArray[j])->position==parc->reuse[2])
					{
						ploc1=(CLocation *)m_LocationArray[j];
						break;
					}
				for(j=0;j<m_LocationArray.GetSize();j++)
					if(((CLocation *)m_LocationArray[j])->position==parc->reuse[0])
					{
						ploc2=(CLocation *)m_LocationArray[j];
						break;
					}
				parc->AddLocLoc(ploc1,ploc2);
				ploc1->AddOutputArc(parc);
				ploc2->AddInputArc(parc);
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
// CPetriNetworkDoc diagnostics

#ifdef _DEBUG
void CPetriNetworkDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPetriNetworkDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPetriNetworkDoc commands

CLocation * CPetriNetworkDoc::AddLocation(CPoint point,bool flag,int pos)
{
	/*
		This function adds an Location with center at point.
		If flag is true we have manual mode.
		If flag is false we have automatic mode.
	*/
	CLocation *plocation=new CLocation(point,this,flag,pos,m_Type,dim);
	if(plocation->m_center.x>=0 && plocation->m_center.y>=0)
	{
		try
		{
			m_LocationArray.Add(plocation);
			SetModifiedFlag();
		}
		catch (CMemoryException *perr)
		{
			// Display a message for the user, giving him or her the
			// bad news
			AfxMessageBox("Out of memory", MB_ICONSTOP | MB_OK);
			if (plocation)
			{
				// Delete it
				delete plocation;
				plocation = NULL;
			}
			// Delete the exception object
			perr->Delete();
		}
	}
	else
	{
		delete plocation;
		plocation = NULL;
	}
	return plocation;
}

CTransition * CPetriNetworkDoc::AddTransition(CPoint point,bool flag,int pos)
{
	/*
		This function add a transition with the center in point.
		If flag is true we have manual mode.
		If flag is false we have automatic mode.
	*/
	CTransition *ptransition;
	if(m_Type==1 && flag==false) ptransition=new CTransition(point,this,pos,m_Type,m_Delay[pos],dim);
	else ptransition=new CTransition(point,this,flag,pos,m_Type,dim);
	if(ptransition->m_center.x>=0 && ptransition->m_center.y>=0)
	{
		try
		{
			m_TransitionArray.Add(ptransition);
			SetModifiedFlag();
		}
		catch (CMemoryException *perr)
		{
			// Display a message for the user, giving him or her the
			// bad news
			AfxMessageBox("Out of memory", MB_ICONSTOP | MB_OK);
			if (ptransition)
			{
				// Delete it
				delete ptransition;
				ptransition = NULL;
			}
			// Delete the exception object
			perr->Delete();
		}
	}
	else
	{
		delete ptransition;
		ptransition=NULL;
	}
	return ptransition;
}


int CPetriNetworkDoc::GetCountLocation()
{
	/*
		This function gives the number of the locations.
	*/
	return m_LocationArray.GetSize();
}

CLocation * CPetriNetworkDoc::GetLocation(int nIndex)
{
	/*
		This function gives the reference to the location with nIndex in the array.
	*/
	return (CLocation *)m_LocationArray[nIndex];
}


int CPetriNetworkDoc::GetCountTransition()
{
	/*
		This function gives the number of the transitions.
	*/
	return m_TransitionArray.GetSize();
}

CTransition * CPetriNetworkDoc::GetTransition(int nIndex)
{
	/*
		This function gives the reference to the transition with nIndex in the array.
	*/
	return (CTransition *)m_TransitionArray[nIndex];
}

CLocation * CPetriNetworkDoc::GetMoveLocation()
{
	/*
		This function returns the reference to the moving location.
		This function is called after GetLocation.
	*/
	return m_mLocation;
}

CTransition * CPetriNetworkDoc::GetMoveTransition()
{
	/*
		This function returns the reference to the moving transition.
		This function is called after GetTransition.
	*/
	return m_mTransition;
}


void CPetriNetworkDoc::GetLocation(CPoint point)
{
	/*
		This function set the m_mLocation with the reference to the location which 
		has the point.
		This function is used for set location which we want to move..
	*/
	//find id we had select a location
	int nrloc=m_LocationArray.GetSize();
	CLocation *ploc;
	for(int i=0;i<nrloc;i++)
	{
		ploc=(CLocation*)m_LocationArray[i];
		if(abs(ploc->m_center.x-point.x)<=15 && abs(ploc->m_center.y-point.y)<=15)
		{
			m_mLocation=ploc;
			break;
		}
	}
}

void CPetriNetworkDoc::GetTransition(CPoint point)
{
	/*
		This function set the m_mTransition with the reference to the transition which 
		has the point.
		This function is used for set transition which we want to move..
	*/
	//find if we had select a transition
	int nrtran=m_TransitionArray.GetSize();
	CTransition *ptran;
	for(int i=0;i<nrtran;i++)
	{
		ptran=(CTransition*)m_TransitionArray[i];
		if(abs(ptran->m_center.x-point.x)<=15 && abs(ptran->m_center.y-point.y)<=15)
		{
			m_mTransition=ptran;
			break;
		}
	}

}

void CPetriNetworkDoc::ResetTransition()
{
	/*
		This function reset the moving transition.
	*/
	m_mTransition=NULL;
}

void CPetriNetworkDoc::ResetLocation()
{
	/*
		This function reset the moving location.
	*/
	m_mLocation=NULL;
}

void CPetriNetworkDoc::DeleteTransition(CPoint point,CDC *pdc)
{
	/*
		This function deletes a transition given by point.
		If the point is inside a transition it erases the transition.
	*/
	int nrtran=m_TransitionArray.GetSize();
	CTransition *ptran;
	int i;
	for(i=0;i<nrtran;i++)
	{
		ptran=(CTransition*)m_TransitionArray[i];
		if(abs(ptran->m_center.x-point.x)<=15 && abs(ptran->m_center.y-point.y)<=15)
		{
			m_darce.clear();
			ptran->DeleteTransition(pdc,&m_darce);
			m_TransitionArray.RemoveAt(i,1);
			m_TransitionArray.FreeExtra();
			delete ptran;
			for(m_itint=m_darce.begin();m_itint!=m_darce.end();++m_itint)
			{
				for(int i=0;i<m_ArcsArray.GetSize();i++)
					if(((CArcs*)m_ArcsArray[i])->pos==*m_itint)
					{
						CArcs *parc;
						parc=(CArcs *)m_ArcsArray[i];
						m_ArcsArray.RemoveAt(i,1);
						m_ArcsArray.FreeExtra();
						delete parc;
						break;
					}
			}
			break;
		}
	}
	for(i=0;i<m_ArcsArray.GetSize();i++)
		((CArcs*)m_ArcsArray[i])->pos=i;
}

void CPetriNetworkDoc::DeleteLocation(CPoint point,CDC *pdc)
{
	/*
		This function delete the location given by the point.
		If the point in inside a location it erases the location.
	*/
	//find id we had select a location
	int nrloc=m_LocationArray.GetSize();
	CLocation *ploc;
	int i;
	for(i=0;i<nrloc;i++)
	{
		ploc=(CLocation*)m_LocationArray[i];
		if(abs(ploc->m_center.x-point.x)<=15 && abs(ploc->m_center.y-point.y)<=15)
		{
			m_darce.clear();
			ploc->DeleteLocation(pdc,&m_darce);
			delete m_LocationArray[i];
			m_LocationArray.RemoveAt(i,1);
			m_LocationArray.FreeExtra();
			for(m_itint=m_darce.begin();m_itint!=m_darce.end();++m_itint)
			{
				for(int i=0;i<m_ArcsArray.GetSize();i++)
					if(((CArcs*)m_ArcsArray[i])->pos==*m_itint)
					{
						m_ArcsArray.RemoveAt(i,1);
						m_ArcsArray.FreeExtra();
						delete ploc;
						break;
					}
			}
			break;
		}
	}
	for(i=0;i<m_ArcsArray.GetSize();i++)
		((CArcs*)m_ArcsArray[i])->pos=i;

}

void CPetriNetworkDoc::OnLocation() 
{
	/*
		Set the state of the document to the put location.
	*/
	m_state=0;	
}

void CPetriNetworkDoc::OnUpdateLocation(CCmdUI* pCmdUI) 
{
	/*
		Update the state of the document to the put location.
	*/
	pCmdUI->SetCheck(m_state==0 ? 1 : 0);
}


void CPetriNetworkDoc::OnMoveLocation() 
{
	/*
		Set the state of the document to the move location.
	*/
	m_state=3;
}

void CPetriNetworkDoc::OnUpdateMoveLocation(CCmdUI* pCmdUI) 
{
	/*
		Update the state of the document to the move location.
	*/
	pCmdUI->SetCheck(m_state==3 ? 1 : 0);
}

void CPetriNetworkDoc::OnUpdateMoveTran(CCmdUI* pCmdUI) 
{
	/*
		Update the state of the document to the move transition.
	*/
	pCmdUI->SetCheck(m_state==4 ? 1 : 0);
}

void CPetriNetworkDoc::OnMoveTran() 
{
	/*
		Set the state of the document to the move transition.
	*/
	m_state=4;
}

void CPetriNetworkDoc::OnTransition() 
{
	/*
		Set the state of the document to the put transition.
	*/
	m_state=1;
}

void CPetriNetworkDoc::OnUpdateTransition(CCmdUI* pCmdUI) 
{
	/*
		Update the state of the document to the put transition.
	*/
	pCmdUI->SetCheck(m_state==1 ? 1 : 0);
}

void CPetriNetworkDoc::OnArc() 
{
	/*
		Set the state of the document to the arc with multiple points.
	*/
	m_state=2;	
}

void CPetriNetworkDoc::OnUpdateArc(CCmdUI* pCmdUI) 
{
	/*
		Update the state of the document to the arc with multiple points.
	*/
	pCmdUI->SetCheck(m_state==2 ? 1 : 0);
}

void CPetriNetworkDoc::OnDeleteLocation() 
{
	/*
		Set the state of the document to the delete location.
	*/
	m_state=5;
}

void CPetriNetworkDoc::OnUpdateDeleteLocation(CCmdUI* pCmdUI) 
{
	/*
		Update the state of the document to the delete location.
	*/
	pCmdUI->SetCheck(m_state==5 ? 1 : 0);
}

void CPetriNetworkDoc::OnDeleteTran() 
{
	/*
		Set the state of the document to the delete transition.
	*/
	m_state=6;
}

void CPetriNetworkDoc::OnUpdateDeleteTran(CCmdUI* pCmdUI) 
{
	/*
		Update the state of the document to the delete transition.
	*/
	pCmdUI->SetCheck(m_state==6 ? 1 : 0);
}

void CPetriNetworkDoc::OnArc2p() 
{
	/*
		Set the state of the document to the put arc with 2 points.
	*/
	m_state=7;
}

void CPetriNetworkDoc::OnUpdateArc2p(CCmdUI* pCmdUI) 
{
	/*
		Update the state of the document to the put arc with 2 points.
	*/
	pCmdUI->SetCheck(m_state==7 ? 1 : 0);
}

void CPetriNetworkDoc::OnDeleteArc() 
{
	/*
		Set the state of the document to the delete arc.
	*/
	m_state=10;	
}

void CPetriNetworkDoc::OnMark() 
{
	/*
		Set the state of the document to the mark location.
	*/
	m_state=8;
}

void CPetriNetworkDoc::OnUpdateMark(CCmdUI* pCmdUI) 
{
	/*
		Update the state of the document to the mark location.
	*/
	pCmdUI->SetCheck(m_state==8 ? 1 : 0);
}

void CPetriNetworkDoc::OnArc4p() 
{
	/*
		Set the state of the document to the put arc with 4 points.
	*/
	m_state=9;
}

void CPetriNetworkDoc::OnUpdateArc4p(CCmdUI* pCmdUI) 
{
	/*
		Update the state of the document to the put arc with 4 points.
	*/
	pCmdUI->SetCheck(m_state==9 ? 1 : 0);
}

void CPetriNetworkDoc::OnUpdateDeleteArc(CCmdUI* pCmdUI) 
{
	/*
		Update the state of the document to delete arc.
	*/
	pCmdUI->SetCheck(m_state==10 ? 1 : 0);
}

void CPetriNetworkDoc::OnUnmark() 
{
	/*
		Set the state of the document to unmark a location.
	*/
	m_state=11;	
}

void CPetriNetworkDoc::OnUpdateUnmark(CCmdUI* pCmdUI) 
{
	/*
		Update the state of the document to unmark a location.
	*/
	pCmdUI->SetCheck(m_state==11 ? 1 : 0);
}

void CPetriNetworkDoc::OnPan() 
{
	/*
		Set the state of the document to pan (move of entire design).
	*/
	m_state=20;	
}

void CPetriNetworkDoc::OnUpdatePan(CCmdUI* pCmdUI) 
{
	/*
		Update the state of the document to pan (move of entire design)/
	*/
	pCmdUI->SetCheck(m_state==20 ? 1 : 0);
}

void CPetriNetworkDoc::OnZoomIn() 
{
	/*
		Set the state of the document to zoom in.
	*/
	m_state=21;
}

void CPetriNetworkDoc::OnUpdateZoomIn(CCmdUI* pCmdUI) 
{
	/*
		Update the state of the document to zoom in.
	*/
	pCmdUI->SetCheck(m_state==21 ? 1 : 0);
}

void CPetriNetworkDoc::OnZoomOut() 
{
	/*
		Set the state of the document to zoom out.
	*/
	m_state=22;		
}

void CPetriNetworkDoc::OnUpdateZoomOut(CCmdUI* pCmdUI) 
{
	/*
		Update the state of the document to zoom out.
	*/
	pCmdUI->SetCheck(m_state==22 ? 1 : 0);
}

void CPetriNetworkDoc::Onselect() 
{
	m_state=23;
}

void CPetriNetworkDoc::OnUpdateselect(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_state==23 ? 1 : 0);
}

void CPetriNetworkDoc::Onredone() 
{
/*
	This function redraw the arc deleted by one of the teaching methods
*/
	int i,j;
	if(m_Type==-1 || m_Type==-2)
	{
		for(i=0;i<m_nLocation;i++)
			for(j=0;j<m_nLocation;j++)
				if(m_mat[i][j]!=0)
					AddArc(i,j,m_mat[i][j]);
	}
}

int CPetriNetworkDoc::GetState()
{
	/*
		This function return the state of the document.
		It is used for mouse movement.
	*/
	return m_state;
}

void CPetriNetworkDoc::SetState(int state)
{
	/*
		This function set the state of the document.
		It is used for mouse movement.
	*/
	m_state=state;
}

void CPetriNetworkDoc::AddArc(CPoint point, CDC *pdc)
{
	/*
		This function add an arc to the instance who have the point.
		This function also sets the working arc.
	*/
	bool flag;
	pDC=pdc;
	CArcs *parc=new CArcs(point,pdc,m_Type,dimsgn,dim);	
	//see if we have a transition
	flag=false;
	int nrtran=m_TransitionArray.GetSize();
	CTransition *ptran;
	for(int i=0;i<nrtran;i++)
	{
		ptran=(CTransition*)m_TransitionArray[i];
		if(abs(ptran->m_center.x-point.x)<=dim && abs(ptran->m_center.y-point.y)<=dim)
		{
			parc->AddStart(ptran);
			parc->ConnectS();
			ptran->AddOutputArc(parc);
			flag=true;
			break;
		}
	}
	if(flag==false)
	{
		//see if we have a location
		int nrloc=m_LocationArray.GetSize();
		CLocation *ploc;
		for(int i=0;i<nrloc;i++)
		{
			ploc=(CLocation*)m_LocationArray[i];
			if(abs(ploc->m_center.x-point.x)<=dim && abs(ploc->m_center.y-point.y)<=dim)
			{
				parc->AddStart(ploc);
				parc->ConnectS();
				ploc->AddOutputArc(parc);
				flag=true;
				break;
			}
		}
	}
	if(flag==false)
	{
		delete parc;
		m_warc=NULL;
	}
	else
	{
		parc->pos=-1;
		m_warc=parc;
	}
	nr_points=0;
}

void CPetriNetworkDoc::ResetArc(CPoint point,CDC *pdc)
{
	/*
		Reset the state of an arc.
		It puts in the same time the end point of an arc.
	*/
	bool flag;
	flag=false;
	int nrtran=m_TransitionArray.GetSize();
	CTransition *ptran;
	if(m_warc!=NULL)
	{
		//see if we have a transition
		for(int i=0;i<nrtran;i++)
		{
			ptran=(CTransition*)m_TransitionArray[i];
			if(abs(ptran->m_center.x-point.x)<=15 && abs(ptran->m_center.y-point.y)<=15)
			{
				m_warc->AddEnd(ptran,true,0);
				m_warc->ConnectE();
				ptran->AddInputArc(m_warc);
				flag=true;
				break;
			}
		}
		if(flag==false)
		{
			//see if we have a location
			int nrloc=m_LocationArray.GetSize();
			CLocation *ploc;
			for(int i=0;i<nrloc;i++)
			{
				ploc=(CLocation*)m_LocationArray[i];
				if(abs(ploc->m_center.x-point.x)<=15 && abs(ploc->m_center.y-point.y)<=15)
				{
					m_warc->AddEnd(ploc,true,0);
					m_warc->ConnectE();
					ploc->AddInputArc(m_warc);
					flag=true;
					break;
				}
			}
		}
		try
		{
			if(flag==true) //we have a location or transition
			{
				m_warc->pos=m_ArcsArray.Add(m_warc);
				SetModifiedFlag();
			}
			else //we haven't a valid arc
			{
				m_warc->DeleteArc(pdc,2);
				delete m_warc;
			}
		}
		catch (CMemoryException *perr)
		{
			// Display a message for the user, giving him or her the
			// bad news
			AfxMessageBox("Out of memory", MB_ICONSTOP | MB_OK);
			if (m_warc)
			{
				// Delete it
				m_warc->DeleteArc(pdc,2);
				delete m_warc;
			}
			// Delete the exception object
			perr->Delete();
		}
	}
	nr_points=0;
	m_warc=NULL;
}

void CPetriNetworkDoc::DeleteArc(CPoint point,CDC *pdc)
{
	/*
		This function delete an arc given by the point.
		It is used for manual erase an arc.
	*/
	//find id we had select a arc
	CArcs *parc;
	bool flag;
	int i;
	for(i=0;i<m_ArcsArray.GetSize();i++)
	{
		parc=(CArcs*)m_ArcsArray[i];
		flag=parc->DeleteArc(point,pdc);
		if(flag==true)
		{
			m_ArcsArray.RemoveAt(i,1);
			m_ArcsArray.FreeExtra();
			delete parc;
			break;
		}
	}
	for(i=0;i<m_ArcsArray.GetSize();i++)
		((CArcs*)m_ArcsArray[i])->pos=i;
}

CArcs * CPetriNetworkDoc::GetWArc()
{
	/*
		This function return the working arc to the caller.
		This function is used for adding points to a arc.
	*/
	return m_warc;
}

int CPetriNetworkDoc::GetCountArcs()
{
	/*
		This function return the number of arcs.
	*/
	return m_ArcsArray.GetSize();
}

CArcs * CPetriNetworkDoc::GetArc(int nIndex)
{
	/*
		This function return a reference to the arc class which has the nIndex 
		in the array.
	*/
	return (CArcs *)m_ArcsArray[nIndex];
}


void CPetriNetworkDoc::AddMark(CPoint point)
{
	/*
		This function adds a mark to a location specified by point.
	*/
	//find id we had select a location
	int nrloc=m_LocationArray.GetSize();
	CLocation *ploc;
	for(int i=0;i<nrloc;i++)
	{
		ploc=(CLocation*)m_LocationArray[i];
		if(abs(ploc->m_center.x-point.x)<=15 && abs(ploc->m_center.y-point.y)<=15)
		{
			ploc->m_Mark++;
			break;
		}
	}
}

void CPetriNetworkDoc::UnMark(CPoint point)
{
	/*
		This function decrements with 1 the mark of a location.
		It is called by user.
	*/
	//find id we had select a location
	int nrloc=m_LocationArray.GetSize();
	CLocation *ploc;
	for(int i=0;i<nrloc;i++)
	{
		ploc=(CLocation*)m_LocationArray[i];
		if(abs(ploc->m_center.x-point.x)<=15 && abs(ploc->m_center.y-point.y)<=15)
		{
			ploc->m_Mark--;
			if(ploc->m_Mark<0) ploc->m_Mark=0;
			break;
		}
	}
}

void CPetriNetworkDoc::SortLocation()
{
	/*
		This function sort the location Array in the order of position.
	*/
	CLocation *ploc;
	int min;
	for(int i=0;i<m_LocationArray.GetSize();i++)
	{
		min=i;
		for(int j=i;j<m_LocationArray.GetSize();j++)
			if(((CLocation *)m_LocationArray[min])->position>((CLocation *)m_LocationArray[j])->position) min=j;
		if(min!=i)
		{
			ploc=(CLocation *)m_LocationArray[i];
			m_LocationArray.SetAt(i,(CLocation *)m_LocationArray[min]);
			m_LocationArray.SetAt(min,ploc);
		}
	}
}

void CPetriNetworkDoc::SortTransition()
{
	/*
		This function sort the transition Array in the order of position.
	*/
	CTransition *ptran;
	int min;
	for(int i=0;i<m_TransitionArray.GetSize();i++)
	{
		min=i;
		for(int j=i;j<m_TransitionArray.GetSize();j++)
			if(((CTransition *)m_TransitionArray[min])->position>((CTransition *)m_TransitionArray[j])->position) min=j;
		if(min!=i)
		{
			ptran=(CTransition *)m_TransitionArray[i];
			m_TransitionArray.SetAt(i,(CTransition *)m_TransitionArray[min]);
			m_TransitionArray.SetAt(min,ptran);
		}
	}
}

void CPetriNetworkDoc::Generate()
{
	/*
		This function create the matrix necessary for simulation.
		This function is the oposite of Auto function.
		!!This function must be called before you start any simulation.
	*/
	int i,j;
	m_nLocation=m_LocationArray.GetSize();
	SortLocation();
	CLocation *ploc;
	if(m_Type>=0) //we have Petri Network
	{
		m_nTransition=m_TransitionArray.GetSize();
		SortTransition();
		AlocateMatrix();
		CLocation *ploc;
		CString message;
		//make the pre matrix
		for(i=0;i<m_nLocation;i++)
		{
			ploc=(CLocation *)m_LocationArray[i];
			if(ploc->m_OutputArcs.GetSize()>m_nTransition)
			{
				message.Empty();
				message.Format("Something is wrong with location %d",i);
				AfxMessageBox(message);
				return;
			}
			for(j=0;j<ploc->m_OutputArcs.GetSize();j++)
			{
				for(int k=0;k<m_nTransition;k++)
					if(((CTransition*)m_TransitionArray[k])->position==((CArcs *)(ploc->m_OutputArcs[j]))->m_EndTran->position)
					{
						m_Pre[i][k]=((CArcs *)(ploc->m_OutputArcs[j]))->val;
						break;
					}
			}
		}
		//make the post matrix
		for(i=0;i<m_nLocation;i++)
		{
			ploc=(CLocation *)m_LocationArray[i];
			if(ploc->m_InputArcs.GetSize()>m_nTransition)
			{
				message.Empty();
				message.Format("Something is wrong with location %d",i);
				AfxMessageBox(message);
				return;
			}
			for(j=0;j<ploc->m_InputArcs.GetSize();j++)
			{
				for(int k=0;k<m_nTransition;k++)
					if(((CTransition*)m_TransitionArray[k])->position==((CArcs *)(ploc->m_InputArcs[j]))->m_StartTran->position)
					{
						m_Post[i][k]=((CArcs *)(ploc->m_InputArcs[j]))->val;
						break;
					}
			}
		}
		//make the mark vector
		for(i=0;i<m_nLocation;i++)
			m_Mark[i]=((CLocation *)m_LocationArray[i])->m_Mark;
		//make the delay vector
		if(m_Type==1) 
			for(i=0;i<m_nTransition;i++)
			{
				for(int k=0;k<m_nTransition;k++)
					if(((CTransition*)m_TransitionArray[k])->position==((CTransition *)m_TransitionArray[i])->position)
					{
						m_Delay[k]=((CTransition *)m_TransitionArray[i])->m_delay;
						break;
					}
			}
		else m_Delay=NULL;
	
		//write the file to verify or for reload
		ofstream ofile;
		CValue1 tmpval;
		tmpval.m_info.Insert(0,"Input the name of generate file, default is generate.dat");
		tmpval.DoModal();
		if(tmpval.m_flag==true) ofile.open(tmpval.m_value);
		else ofile.open("generate.dat");
		for(i=0;i<m_nLocation;i++)
		{
			for(j=0;j<m_nTransition-1;j++)
				ofile<<m_Pre[i][j]<<" ";
			ofile<<m_Pre[i][m_nTransition-1]<<endl;
		}
		ofile<<endl;
		for(i=0;i<m_nLocation;i++)
		{
			for(j=0;j<m_nTransition-1;j++)
				ofile<<m_Post[i][j]<<" ";
			ofile<<m_Post[i][m_nTransition-1]<<endl;
		}
		ofile<<endl;
		for(i=0;i<m_nLocation;i++) ofile<<m_Mark[i]<<endl;
		switch(m_Type)
		{
			case 1:
			{
				ofile<<"\nDelay\n";
				for(i=0;i<m_nTransition;i++) ofile<<m_Delay[i]<<endl;
				break;
			}
			case 2:
			{
				//print the Jump relation
				for(i=0;i<m_JumpArray.GetSize();i++)
				{
					ofile<<"\nIn ";
					for(j=0;j<m_nLocation-1;j++)
						ofile<<((CJumpTable *)m_JumpArray[i])->input[j]<<",";
					ofile<<((CJumpTable *)m_JumpArray[i])->input[m_nLocation-1]<<" Out ";
					for(j=0;j<m_nLocation-1;j++)
						ofile<<((CJumpTable *)m_JumpArray[i])->output[j]<<",";
					ofile<<((CJumpTable *)m_JumpArray[i])->output[m_nLocation-1];
				}
				break;
			}
			default: break;
		}
		ofile.close();
	}
	else
	{
		int *temp;
		CString message;
		//create the matrix
		if(m_mat!=NULL)
		{
			free(*m_mat);
			free(m_mat);
			m_mat=NULL;
		}
		m_mat=(int **)calloc(m_nLocation,sizeof(int *));
		temp=(int *)calloc(m_nLocation*m_nLocation,sizeof(int));
		for(i=0;i<m_nLocation;i++)
		{
			m_mat[i]=temp;
			temp+=m_nLocation;
		}
		for(i=0;i<m_nLocation;i++)
			for(j=0;j<m_nLocation;j++)
				m_mat[i][j]=0;
		for(i=0;i<m_nLocation;i++)
		{
			ploc=(CLocation *)m_LocationArray[i];
			if(ploc->m_OutputArcs.GetSize()>m_nLocation)
			{
				message.Empty();
				message.Format("Something is wrong with location %d",i);
				AfxMessageBox(message);
				return;
			}
			for(j=0;j<ploc->m_OutputArcs.GetSize();j++)
			{
				for(int k=0;k<m_nLocation;k++)
					if(((CLocation*)m_LocationArray[k])->position==((CArcs *)(ploc->m_OutputArcs[j]))->m_EndLoc->position)
					{
						m_mat[i][k]=((CArcs *)(ploc->m_OutputArcs[j]))->val;
						if(m_Type==-1) m_mat[k][i]=((CArcs *)(ploc->m_OutputArcs[j]))->val;
						break;
					}
				
			}
		}
		//write the file to verify
		ofstream ofile;
		CValue1 tmpval;
		tmpval.m_info.Insert(0,"Input the name of generate file");
		tmpval.DoModal();
		if(tmpval.m_flag==true) ofile.open(tmpval.m_value);
		else ofile.open("generate.dat");
		for(i=0;i<m_nLocation;i++)
		{
			for(j=0;j<m_nLocation;j++)
				ofile<<m_mat[i][j]<<" ";
			ofile<<endl;
		}
		ofile.close();
	}
}

void CPetriNetworkDoc::Simulate()
{
	/*
		This function start the simulation for PN and graphs.
	*/
	m_CS=new CCriticalSection;
	m_StartStop=new CEvent;
	m_Oper=0;
	if(m_Type>=0)
	{
		simmark=new CMarked(m_Pre,m_Post,m_nLocation,m_nTransition,m_Mark,m_Delay,m_CS,&m_Oper,m_StartStop,this,m_Type,&m_JumpArray);
		simmark->CreateThread(0,0);
	}
	else
	{
		simdig=new CDigraph(m_nLocation,m_CS,&m_Oper,m_StartStop,this,m_Type,m_opgraph,m_mat,m_inf);
		simdig->CreateThread(0,0);
	}
}

void CPetriNetworkDoc::ContinueSim()
{
	/*
		This function gives to the simulator the signal for continuing 
		the simulation after user calls the StopSim function.
	*/
	m_CS->Lock();
	m_Oper=0;
	m_CS->Unlock();
	m_StartStop->SetEvent();
}

void CPetriNetworkDoc::StopSim()
{
	/*
		This function stop the simulator.
		In the stop time of the simulator the user can ajust the mark of the PN.
	*/
	m_CS->Lock();
	m_Oper=1;
	m_CS->Unlock();
}

void CPetriNetworkDoc::OnUpdateStop(CCmdUI* pCmdUI) 
{
	/*
		Update the request for stop the simulation.
	*/
	pCmdUI->SetCheck(m_Oper==1 ? 1 : 0);
}

void CPetriNetworkDoc::ExitSim()
{
	/*
		This function give the termination (exit) signal to the simulator.
	*/
	m_CS->Lock();
	m_Oper=2;
	m_CS->Unlock();
	m_StartStop->SetEvent();
}

void CPetriNetworkDoc::PutDoc(CDC *pdc, CPetriNetworkView *pv)
{
	/*
		Set the view and CDC for the document from view.
	*/
	pDC=pdc;
	m_View=pv;
}

void CPetriNetworkDoc::ReMark(bool flag)
{
	/*
		Remark the location with the data from simulation.
		It is call every step of the simulation.
	*/
	int i;
	if(flag==true)
		for(i=0;i<m_nLocation;i++)
			((CLocation *)m_LocationArray[i])->m_Mark=m_Mark[i];
	else
		for(i=0;i<m_nLocation;i++)
			m_Mark[i]=((CLocation *)m_LocationArray[i])->m_Mark;
	m_View->OnDraw(pDC);
}

bool CPetriNetworkDoc::TestState(int pos, int flag)
{
	/*
		Find a location or transition with position pos.
		The flag is 0 for location.
		The flag is 1 for transition.
	*/
	int i;
	if(flag==0)
	{
		for(i=0;i<m_LocationArray.GetSize();i++)
			if(((CLocation *)m_LocationArray[i])->position==pos) return true;
	}
	else if(flag==1)
	{
		for(i=0;i<m_TransitionArray.GetSize();i++)
			if(((CTransition *)m_TransitionArray[i])->position==pos) return true;	
	}
	return false;
}

void CPetriNetworkDoc::OnLoad() 
{
	/*
		Load a PN from a description file.
		After load you must call auto.
	*/
	CValue1 valstr;
	char loadstr[255];
	CStringArray strarray;
	char tempstr[10];
	int i,j,k,l;
	bool flag;
	valstr.m_info.Empty();
	valstr.m_info.Insert(0,"Name of file who have description of PN");
	flag=false;
	while(flag==false)
	{
		valstr.DoModal();
		if(valstr.m_flag==true) flag=true;
	}
	ifstream file(valstr.m_value);
	//load pre matrix
	while(1)
	{
		for(i=0;i<255;i++) loadstr[i]='\0';
		file.getline(loadstr,255);
		if(loadstr[0]=='\0') break;
		strarray.Add(loadstr);
	}
	m_nLocation=strarray.GetSize();
	m_nTransition=0;
	i=0;
	while(strarray[0][i]!='\0')
	{
		if(strarray[0][i]==' ') m_nTransition++;
		i++;
		if(i>=(strarray[0]).GetLength()) break;
	}
	m_nTransition++;
	AlocateMatrix();
	//make pre matrix
	for(i=0;i<m_nLocation;i++)
	{
		j=0;l=0;
		flag=true;
		while(flag==true)
		{
			for(k=0;k<10;k++) tempstr[k]='\0';
			k=0;
			while(1)
			{
				if(strarray[i][j]==' ')
				{
					j++;
					break;
				}
				else
				{
					if(strarray[i][j]=='\0')
					{
						flag=false;
						break;
					}
					tempstr[k]=strarray[i][j];
					k++;
					j++;
					if(j>=strarray[i].GetLength())
					{
						flag=false;
						break;
					}
				}
			}
			m_Pre[i][l]=atoi(tempstr);
			l++;
		}
	}
	strarray.RemoveAll();
	//load post matrix
	while(1)
	{
		for(i=0;i<255;i++) loadstr[i]='\0';
		file.getline(loadstr,255);
		if(loadstr[0]=='\0') break;
		strarray.Add(loadstr);
	}
	//make post matrix
	for(i=0;i<m_nLocation;i++)
	{
		j=0;l=0;
		flag=true;
		while(flag==true)
		{
			for(k=0;k<10;k++) tempstr[k]='\0';
			k=0;
			while(1)
			{
				if(strarray[i][j]==' ')
				{
					j++;
					break;
				}
				else
				{
					if(strarray[i][j]=='\0')
					{
						flag=false;
						break;
					}
					tempstr[k]=strarray[i][j];
					k++;
					j++;
					if(j>=strarray[i].GetLength())
					{
						flag=false;
						break;
					}
				}
			}
			m_Post[i][l]=atoi(tempstr);
			l++;
		}
	}
	strarray.RemoveAll();
	//load and make mark vector
	for(i=0;i<m_nLocation;i++)
		file>>m_Mark[i];
	if(m_Type==1)
		for(i=0;i<m_nTransition;i++)
			file>>m_Delay[i];
	if(m_Type==2) //load jump table
	{
		CString in,out;
		char str2[255];
		file>>str2[0];
		while(!file.eof())
		{
			for(i=0;i<255;i++)
			{
				loadstr[i]='\0';
				str2[i]='\0';
			}
			file.getline(loadstr,255);
			if(loadstr[0]=='\0') break;
			in.Empty();
			k=0;
			for(i=3;i<255;i++)
			{
				if(loadstr[i]=='O' && loadstr[i+1]=='u' && loadstr[i+2]=='t' && loadstr[i+3]==' ') break;
				else
				{
					str2[k]=loadstr[i];
					k++;
				}
			}
			in.Insert(0,str2);
			for(l=0;l<255;l++) str2[l]='\0';
			l=i+4;
			k=0;
			for(i=l;i<255;i++)
			{
				if(loadstr[i]=='\0') break;
				else
				{
					str2[k]=loadstr[i];
					k++;
				}
			}
			out.Empty();
			out.Insert(0,str2);
			CJumpTable *pjump=new CJumpTable(m_nLocation,in,out);
			try
			{
				m_JumpArray.Add(pjump);
				SetModifiedFlag();
			}
			catch (CMemoryException *perr)
			{
				// Display a message for the user, giving him or her the
				// bad news
				AfxMessageBox("Out of memory", MB_ICONSTOP | MB_OK);
				if (pjump)
				{
					// Delete it
					delete pjump;
					pjump = NULL;
				}
				// Delete the exception object
				perr->Delete();
			}
		}

	}
	file.close();
	m_load=true;
}

void CPetriNetworkDoc::AlocateMatrix()
{
	/*
		This function allocates the matrix for the simulator.
	*/
	int *temp;
	int i;
	//create the matrix
	if(m_Post!=NULL)
	{
		free(*m_Post);
		free(m_Post);
		m_Post=NULL;
	}
	if(m_Pre!=NULL)
	{
		free(*m_Pre);
		free(m_Pre);
		m_Pre=NULL;
	}
	if(m_Mark!=NULL)
	{
		free(m_Mark);
		m_Mark=NULL;
	}
	if(m_Delay!=NULL)
	{
		free(m_Delay);
		m_Delay=NULL;
	}
	m_Pre=(int **)calloc(m_nLocation,sizeof(int *));
	temp=(int *)calloc(m_nLocation*m_nTransition,sizeof(int));
	for(i=0;i<m_nLocation;i++)
	{
		m_Pre[i]=temp;
		temp+=m_nTransition;
	}
	m_Post=(int **)calloc(m_nLocation,sizeof(int *));
	temp=(int *)calloc(m_nLocation*m_nTransition,sizeof(int));
	for(i=0;i<m_nLocation;i++)
	{
		m_Post[i]=temp;
		temp+=m_nTransition;
	}
	m_Mark=(int *)calloc(m_nLocation,sizeof(int));
	if(m_Type==1) m_Delay=(int *)calloc(m_nTransition,sizeof(int));
}

void CPetriNetworkDoc::Auto(CDC *pdc, CPetriNetworkView *pv)
{
	/*
		This function create from a matrix the PN on display.
		This function is used to create a PN from a description file.
		This function in facts makes the conversion from matrix to 
		internal representation of PN.
		This function is the oposite of Generate function.
		!!This function must be called after loading a PN from a description file.
	*/
	m_View=pv;
	pDC=pdc;
	CPoint point;
	point.x=30;
	point.y=30;
	int i,j;
	if(m_load==true)
	{
		for(i=0;i<m_nLocation;i++)
		{
			AddLocation(point,false,i);
			point.x+=60;
		}
		point.y=120;
		point.x=30;
		for(i=0;i<m_nTransition;i++)
		{
			AddTransition(point,false,i);
			point.x+=60;
		}
		ReMark(true);
	}
	CTransition *ptran;
	CLocation *ploc;
	for(i=0;i<m_nLocation;i++)
	for(j=0;j<m_nTransition;j++)
	{
		if(m_Post[i][j]!=0)
		{
			ptran=(CTransition*)m_TransitionArray[j];
			CArcs *parc=new CArcs(ptran->m_center,pdc,m_Type,dimsgn,dim);
			parc->AddStart(ptran);
			parc->ConnectS();
			ptran->AddOutputArc(parc);
			ploc=(CLocation*)m_LocationArray[i];
			parc->AddPoint(ploc->m_center,pdc);
			parc->AddEnd(ploc,false,m_Post[i][j]);
			parc->ConnectE();
			ploc->AddInputArc(parc);
			try
			{
				parc->pos=m_ArcsArray.Add(parc);
				SetModifiedFlag();
			}
			catch (CMemoryException *perr)
			{
				// Display a message for the user, giving him or her the
				// bad news
				AfxMessageBox("Out of memory", MB_ICONSTOP | MB_OK);
				if (parc)
				{
					// Delete it
					parc->DeleteArc(pdc,2);
					delete parc;
				}
				// Delete the exception object
				perr->Delete();
			}
			parc=NULL;
		}
		if(m_Pre[i][j]!=0)
		{
			ploc=(CLocation*)m_LocationArray[i];
			CArcs *parc=new CArcs(ploc->m_center,pdc,m_Type,dimsgn,dim);
			parc->AddStart(ploc);
			parc->ConnectS();
			ploc->AddOutputArc(parc);
			ptran=(CTransition*)m_TransitionArray[j];
			parc->AddPoint(ptran->m_center,pdc);
			parc->AddEnd(ptran,false,m_Pre[i][j]);
			parc->ConnectE();
			ptran->AddInputArc(parc);			
			try
			{
				parc->pos=m_ArcsArray.Add(parc);
				SetModifiedFlag();
			}
			catch (CMemoryException *perr)
			{
				// Display a message for the user, giving him or her the
				// bad news
				AfxMessageBox("Out of memory", MB_ICONSTOP | MB_OK);
				if (parc)
				{
					// Delete it
					parc->DeleteArc(pdc,2);
					delete parc;
				}
				// Delete the exception object
				perr->Delete();
			}
			parc=NULL;
		}
	}
	pv->OnDraw(pdc);
	m_load=false;
}

void CPetriNetworkDoc::OnPn() 
{
	/*
		Set the type of the PN to mPN.
	*/
	m_Type=0;
}

void CPetriNetworkDoc::OnUpdatePn(CCmdUI* pCmdUI) 
{
	/*
		Update the type of the PN to mPN.
	*/
	pCmdUI->SetCheck(m_Type>=0 ? 1 : 0);
}

void CPetriNetworkDoc::OnmJPN() 
{
	/*
		Set the type of the PN to mJPN.
	*/
	m_Type=2;	
}

void CPetriNetworkDoc::OnUpdatemJPN(CCmdUI* pCmdUI) 
{
	/*
		Update the type of the PN to mJPN.
	*/
	pCmdUI->SetCheck(m_Type==2 ? 1 : 0);	
}

void CPetriNetworkDoc::OnmPN() 
{
	/*
		Set the type of the PN to mPN.
	*/
	m_Type=0;
}

void CPetriNetworkDoc::OnUpdatemPN(CCmdUI* pCmdUI) 
{
	/*
		Update the type of the PN to mPN.
	*/
	pCmdUI->SetCheck(m_Type==0 ? 1 : 0);
}

void CPetriNetworkDoc::OnmTPN() 
{
	/*
		Set the type of the PN to mTPN.
	*/
	m_Type=1;
}

void CPetriNetworkDoc::OnUpdatemTPN(CCmdUI* pCmdUI) 
{
	/*
		Update the type of the PN to mTPN.
	*/
	pCmdUI->SetCheck(m_Type==1 ? 1 : 0);
}

void CPetriNetworkDoc::OnGraph() 
{
	/*
		Set all arcs to type graph and also set the type of the design to
		graph.
	*/
	m_Type=-1;
	for(int i=0;i<m_ArcsArray.GetSize();i++)
		((CArcs *)m_ArcsArray[i])->m_Type=m_Type;
}

void CPetriNetworkDoc::OnUpdateGraph(CCmdUI* pCmdUI) 
{
	/*
		Update the type of the PN to Graph.
	*/
	pCmdUI->SetCheck(m_Type==-1 ? 1 : 0);
}

void CPetriNetworkDoc::OnDigraph() 
{
	/*
		Set all arcs to type digraph and also set the type of the design to
		digraph.
	*/
	m_Type=-2;
	for(int i=0;i<m_ArcsArray.GetSize();i++)
		((CArcs *)m_ArcsArray[i])->m_Type=m_Type;
}

void CPetriNetworkDoc::OnUpdateDigraph(CCmdUI* pCmdUI) 
{
	/*
		Update the type of the PN to digraph.
	*/
	pCmdUI->SetCheck(m_Type==-2 ? 1 : 0);
}

void CPetriNetworkDoc::OnJump() 
{
	/*
		Set the type of PN to mJPN an inputs the jump relation.
	*/
	m_Type=2;
	CInJump jumpdg;
	m_nLocation=m_LocationArray.GetSize();
	jumpdg.m_info.Insert(0,"Input the jumping relation");
	jumpdg.DoModal();
	while(jumpdg.m_flag==true)
	{
		CJumpTable *pjump=new CJumpTable(m_nLocation,jumpdg.m_in,jumpdg.m_out);
		try
		{
			m_JumpArray.Add(pjump);
			SetModifiedFlag();
		}
		catch (CMemoryException *perr)
		{
			// Display a message for the user, giving him or her the
			// bad news
			AfxMessageBox("Out of memory", MB_ICONSTOP | MB_OK);
			if (pjump)
			{
				// Delete it
				delete pjump;
				pjump = NULL;
			}
			// Delete the exception object
			perr->Delete();
		}
		jumpdg.m_in.Empty();
		jumpdg.m_out.Empty();
		jumpdg.DoModal();
	}
}


void CPetriNetworkDoc::DeleteContents() 
{
	/*
		This function delete the contents of the document.
	*/
	// TODO: Add your specialized code here and/or call the base class
	int count,i;
	count=m_JumpArray.GetSize();
	if(count)
	{
		for(i=0;i<count;i++) delete m_JumpArray[i];
		m_JumpArray.RemoveAll();
	}
	count=m_LocationArray.GetSize();
	if(count)
	{
		for(i=0;i<count;i++) delete m_LocationArray[i];
		m_LocationArray.RemoveAll();
	}
	count=m_TransitionArray.GetSize();
	if(count)
	{
		for(i=0;i<count;i++) delete m_TransitionArray[i];
		m_TransitionArray.RemoveAll();
	}
	count=m_ArcsArray.GetSize();
	if(count)
	{
		for(i=0;i<count;i++) delete m_ArcsArray[i];
		m_ArcsArray.RemoveAll();
	}
	CDocument::DeleteContents();
}
void CPetriNetworkDoc::Move(CPoint point, CDC *pdc)
{
	/*
		This function makes the movement of the entire drawing.
		It is called from pan command.
	*/
	int m_nLoc,m_nTran,m_nArcs;
	int i;
	CPoint wpoint;
	SetModifiedFlag();
	m_nLoc=m_LocationArray.GetSize();
	m_nTran=m_TransitionArray.GetSize();
	m_nArcs=m_ArcsArray.GetSize();
	for(i=0;i<m_nArcs;i++)
		((CArcs *)m_ArcsArray[i])->MoveArc(point,pdc);
	for(i=0;i<m_nLoc;i++)
	{
		wpoint=((CLocation *)m_LocationArray[i])->GetCenter();
		((CLocation *)m_LocationArray[i])->MoveLocation(wpoint+point,pdc);
	}
	for(i=0;i<m_nTran;i++)
	{
		wpoint=((CTransition *)m_TransitionArray[i])->GetCenter();
		((CTransition *)m_TransitionArray[i])->MoveTransition(wpoint+point,pdc);
	}
}


void CPetriNetworkDoc::Zoom(float zoom)
{
	/*
		This function realizes the zoom of the design.
	*/
	int m_nLoc,m_nTran,m_nArcs;
	int i;
	CPoint wpoint;
	SetModifiedFlag();
	m_nLoc=m_LocationArray.GetSize();
	m_nTran=m_TransitionArray.GetSize();
	m_nArcs=m_ArcsArray.GetSize();
	dim=dim*zoom;
	dimsgn=dimsgn*zoom;
	for(i=0;i<m_nArcs;i++)
		((CArcs *)m_ArcsArray[i])->ZoomArc(zoom,pDC);
	for(i=0;i<m_nLoc;i++)
		((CLocation *)m_LocationArray[i])->ZoomLocation(zoom,pDC);
	for(i=0;i<m_nTran;i++)
		((CTransition *)m_TransitionArray[i])->ZoomTransition(zoom,pDC);
}

void CPetriNetworkDoc::RemoveArc(int start, int stop)
{
	/*
		It remove an arc which have the starting point at start and the stoping point
		at stop.
		It is called by euler and min cost tree. Especially for digraph and graphs.
	*/
	CArcs *parc;
	int i;
	for(i=0;i<m_ArcsArray.GetSize();i++)
	{
		parc=(CArcs*)m_ArcsArray[i];
		if((parc->m_EndLoc->position==stop && parc->m_StartLoc->position==start)
			||
			(parc->m_EndLoc->position==start && parc->m_StartLoc->position==stop))
		{
			parc->DeleteArc(pDC,2);
			delete m_ArcsArray[i];
			m_ArcsArray.RemoveAt(i,1);
			m_ArcsArray.FreeExtra();
			break;
		}
	}
	for(i=0;i<m_ArcsArray.GetSize();i++)
		((CArcs*)m_ArcsArray[i])->pos=i;
}

void CPetriNetworkDoc::OnCnx() 
{
	/*
		Set the operation to the conexity for graph and digraph.
	*/
	if(m_Type>=0) AfxMessageBox("Please select first the type of graph!");
	else
	{
		if(m_fopgraph[0]==true)
		{
			m_fopgraph[0]=false;
			m_opgraph[0]=0;
		}
		else
		{
			m_opgraph[0]=1;
			m_fopgraph[0]=true;
		}
	}
}

void CPetriNetworkDoc::OnUpdateCnx(CCmdUI* pCmdUI) 
{
	/*
		Update the operation to the conexity for graph and digraph.
	*/
	pCmdUI->SetCheck(m_opgraph[0]==1 ? 1 : 0);	
}

void CPetriNetworkDoc::OnCiclicity() 
{
	/*
		Set the operation to the ciclicity for graph and digraph.
	*/
	if(m_Type>=0) AfxMessageBox("Please select first the type of graph!");
	else
	{
		if(m_fopgraph[1]==true)
		{
			m_fopgraph[1]=false;
			m_opgraph[1]=0;
		}
		else
		{
			m_opgraph[1]=1;
			m_fopgraph[1]=true;
		}
	}
}

void CPetriNetworkDoc::OnUpdateCiclicity(CCmdUI* pCmdUI) 
{
	/*
		Update the operation to ciclicity for digraph and graph.
	*/
	pCmdUI->SetCheck(m_opgraph[1]==1 ? 1 : 0);	
}

void CPetriNetworkDoc::OnMinCost() 
{
	/*
		Set the operation to Minimum Cost Tree for digraph and graph.
	*/
	if(m_opgraph[2]==1 || m_opgraph[4]==1 || m_opgraph[5]==1 || m_opgraph[6]==1)
		AfxMessageBox("There can be only one: min cost or Eulerian graph or Kruskal or Prim or Bellman Kalaba");
	else
		if(m_Type>=0) AfxMessageBox("Please select first the type of graph!");
		else
		{
			if(m_fopgraph[3]==true)
			{
				m_fopgraph[3]=false;
				m_opgraph[3]=0;
			}
			else
			{
				m_opgraph[3]=1;
				m_fopgraph[3]=true;
			}
		}
}

void CPetriNetworkDoc::OnUpdateMinCost(CCmdUI* pCmdUI) 
{
	/*
		Update the operation to minimum cost tree for digraph and graph.
	*/
	pCmdUI->SetCheck(m_opgraph[3]==1 ? 1 : 0);		
}


void CPetriNetworkDoc::OnEuler() 
{
	/*
		Set the operation to eulerian graph or digraph.
	*/
	if(m_opgraph[3]==1 || m_opgraph[4]==1 || m_opgraph[5]==1 || m_opgraph[6]==1)
		AfxMessageBox("There can be only one: min cost or Eulerian graph or Kruskal or Prim or Bellman Kalaba");
	else
		if(m_Type>=0) AfxMessageBox("Please select first the type of graph!");
		else
		{
			if(m_fopgraph[2]==true)
			{
				m_fopgraph[2]=false;
				m_opgraph[2]=0;
			}
			else
			{
				m_opgraph[2]=1;
				m_fopgraph[2]=true;
			}
		}
}

void CPetriNetworkDoc::OnUpdateEuler(CCmdUI* pCmdUI) 
{
	/*
		Update the operation to Eulerian cycle for graph and digraph.
	*/
	pCmdUI->SetCheck(m_opgraph[2]==1 ? 1 : 0);
}

void CPetriNetworkDoc::OnBk() 
{
	/*
		Set the operation to Bellman Kalaba for graph or digraph.
	*/
	if(m_opgraph[3]==1 || m_opgraph[4]==1 || m_opgraph[5]==1 || m_opgraph[2]==1)
		AfxMessageBox("There can be only one: min cost or Eulerian graph or Kruskal or Prim or Bellman Kalaba");
	else
		if(m_Type>=0) AfxMessageBox("Please select first the type of graph!");
		else
		{
			if(m_fopgraph[6]==true)
			{
				m_fopgraph[6]=false;
				m_opgraph[6]=0;
			}
			else
			{
				m_opgraph[6]=1;
				m_fopgraph[6]=true;
			}
		}

}

void CPetriNetworkDoc::OnUpdateBk(CCmdUI* pCmdUI) 
{
	/*
		Update the operation to Bellman Kalaba for graph and digraph.
	*/
	pCmdUI->SetCheck(m_opgraph[6]==1 ? 1 : 0);
}

void CPetriNetworkDoc::OnKruskal() 
{
	/*
		Set the operation to kruskal for graph or digraph.
	*/
	if(m_opgraph[3]==1 || m_opgraph[2]==1 || m_opgraph[5]==1 || m_opgraph[6]==1)
		AfxMessageBox("There can be only one: min cost or Eulerian graph or Kruskal or Prim or Bellman Kalaba");
	else
		if(m_Type>=0) AfxMessageBox("Please select first the type of graph!");
		else
		{
			if(m_fopgraph[4]==true)
			{
				m_fopgraph[4]=false;
				m_opgraph[4]=0;
			}
			else
			{
				m_opgraph[4]=1;
				m_fopgraph[4]=true;
			}
		}
}

void CPetriNetworkDoc::OnUpdateKruskal(CCmdUI* pCmdUI) 
{
	/*
		Update the operation to Kruskal for graph and digraph.
	*/
	pCmdUI->SetCheck(m_opgraph[4]==1 ? 1 : 0);
}

void CPetriNetworkDoc::OnPrim() 
{
	/*
		Set the operation to Prim for graph or digraph.
	*/
	if(m_opgraph[3]==1 || m_opgraph[4]==1 || m_opgraph[2]==1 || m_opgraph[6]==1)
		AfxMessageBox("There can be only one: min cost or Eulerian graph or Kruskal or Prim or Bellman Kalaba");
	else
		if(m_Type>=0) AfxMessageBox("Please select first the type of graph!");
		else
		{
			if(m_fopgraph[5]==true)
			{
				m_fopgraph[5]=false;
				m_opgraph[5]=0;
			}
			else
			{
				m_opgraph[5]=1;
				m_fopgraph[5]=true;
			}
		}
}

void CPetriNetworkDoc::OnUpdatePrim(CCmdUI* pCmdUI) 
{
	/*
		Update the operation to Prim for graph and digraph.
	*/
	pCmdUI->SetCheck(m_opgraph[5]==1 ? 1 : 0);	
}

void CPetriNetworkDoc::AddArc(int i, int j, int val)
{
	CLocation *ploc;
	ploc=(CLocation*)m_LocationArray[i];
	CArcs *parc=new CArcs(ploc->m_center,pDC,m_Type,dimsgn,dim);
	ploc->AddOutputArc(parc);
	parc->AddStart(ploc);
	parc->ConnectS();
	ploc=(CLocation*)m_LocationArray[j];
	parc->AddPoint(ploc->m_center,pDC);
	parc->AddEnd(ploc,false,val);
	parc->ConnectE();
	ploc->AddInputArc(parc);
	try
	{
		parc->pos=m_ArcsArray.Add(parc);
		SetModifiedFlag();
	}
	catch (CMemoryException *perr)
	{
		// Display a message for the user, giving him or her the
		// bad news
		AfxMessageBox("Out of memory", MB_ICONSTOP | MB_OK);
		if (parc)
		{
			// Delete it
			parc->DeleteArc(pDC,2);
			delete parc;
		}
		// Delete the exception object
		perr->Delete();
	}
	parc=NULL;
	m_View->OnDraw(pDC);
}


void CPetriNetworkDoc::SetDC(CDC *pdc)
{
	pDC=pdc;
}

void CPetriNetworkDoc::SetView(CPetriNetworkView *pv)
{
	m_View=pv;
}
