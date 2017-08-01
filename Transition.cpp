// Transition.cpp: implementation of the CTransition class.
//
//////////////////////////////////////////////////////////////////////
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
#include "Transition.h"
#include "Value.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
IMPLEMENT_SERIAL(CTransition,CObject,1)
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTransition::CTransition()
{

}

CTransition::~CTransition()
{

}

CTransition::CTransition(CPoint point,CPetriNetworkDoc *pdoc,bool flag,int pos,int type,float dim1)
{
	/*
		This is the constructor for the class.
		If flag is true we have manual mode.
		If flag is false we have automatic mode.
		This constructor is used for all PN except mTPN.
	*/
	m_center=point;
	m_type=type;
	dim=dim1;
	if(flag==true)
	{
		//get the name of location
		if(m_type==1)
		{
			CValue valtemp;
			bool flag1;
			flag1=false;
			while(flag1==false)
			{
				valtemp.m_info.Empty();
				valtemp.m_info.Insert(0,"Name of transition in order 0...");
				valtemp.m_info2.Empty();
				valtemp.m_info2.Insert(0,"Delay of transition (only for mTPN");
				valtemp.DoModal();
				if(valtemp.m_flag==true)
				{
					valstr.Empty();
					valstr.Insert(0,valtemp.m_value);
					m_text.x=m_center.x+dim;
					m_text.y=m_center.y+dim;
					position=atoi(valstr.GetBuffer(valstr.GetLength()));
					valstr.ReleaseBuffer();
					delay_str.Empty();
					delay_str.Insert(0,valtemp.m_delay);
					m_delay=atoi(delay_str.GetBuffer(delay_str.GetLength()));
					delay_str.ReleaseBuffer();
					if(pdoc->TestState(position,1)==false) flag1=true;
				}
			}
		}
		else
		{
			CValue1 valtemp;
			bool flag1;
			flag1=false;
			while(flag1==false)
			{
				valtemp.m_info.Empty();
				valtemp.m_info.Insert(0,"Name of transition");
				valtemp.DoModal();
				if(valtemp.m_flag==true)
				{
					valstr.Empty();
					valstr.Insert(0,valtemp.m_value);
					m_text.x=m_center.x+dim;
					m_text.y=m_center.y+dim;
					position=atoi(valstr.GetBuffer(valstr.GetLength()));
					valstr.ReleaseBuffer();
					if(pdoc->TestState(position,1)==false) flag1=true;
				}
			}
		}
	}
	else
	{
		m_text.x=m_center.x+dim;
		m_text.y=m_center.y+dim;
		position=pos;
		valstr.Empty();
		char temp[10];
		for(int i=0;i<10;i++) temp[i]='\0';
		_itoa(pos,temp,10);
		valstr.Insert(0,temp);
	}
}

CTransition::CTransition(CPoint point,CPetriNetworkDoc *pdoc,int pos,int type,int delay,float dim1)
{
	/*
		This is the constructor for the class.
		If flag is true we have manual mode.
		If flag is false we have automatic mode.
		This constructor is used for mTPN because it has delay.
	*/
	dim=dim1;
	m_center=point;
	m_type=type;
	m_text.x=m_center.x+dim;
	m_text.y=m_center.y+dim;
	position=pos;
	valstr.Empty();
	char temp[10];
	for(int i=0;i<10;i++) temp[i]='\0';
	itoa(pos,temp,10);
	valstr.Insert(0,temp);
	m_delay=delay;
	itoa(delay,temp,10);
	delay_str.Insert(0,temp);
}

void CTransition::Draw(CDC *pdc)
{
	/*
		This function draws the transition.
	*/
	pdc->Rectangle(m_center.x-dim,m_center.y-dim,m_center.x+dim,m_center.y+dim);
	pdc->TextOut(m_text.x,m_text.y,valstr);
	if(m_type==1) pdc->TextOut(m_center.x,m_center.y,delay_str);
}

void CTransition::MoveTransition(CPoint point,CDC *pdc)
{
	/*
		This function move the transition at point (the center of the transition).
	*/
	//erase the old transition
	CPen lpen(PS_SOLID,1,RGB(255,255,255));
	CPen *pOldPen=pdc->SelectObject(&lpen);
	COLORREF oldcolor=pdc->SetTextColor(RGB(255,255,255));
	if(m_type==1) pdc->TextOut(m_center.x,m_center.y,delay_str);
	pdc->TextOut(m_text.x,m_text.y,valstr);
	pdc->SetTextColor(oldcolor);
	pdc->Rectangle(m_center.x-dim,m_center.y-dim,m_center.x+dim,m_center.y+dim);
	//update points
	m_center=point;
	m_text.x=m_center.x+dim;
	m_text.y=m_center.y+dim;
	//draw the new transition
	pdc->SelectObject(pOldPen);
	pdc->Rectangle(m_center.x-dim,m_center.y-dim,m_center.x+dim,m_center.y+dim);
	if(m_type==1) pdc->TextOut(m_center.x,m_center.y,delay_str);
	pdc->TextOut(m_text.x,m_text.y,valstr);
	//notify the input arcs
	int i;
	for(i=0;i<m_InputArcs.GetSize();i++)
		((CArcs *)m_InputArcs[i])->MoveArc(m_center,1,pdc);
	//notify the output arcs
	for(i=0;i<m_OutputArcs.GetSize();i++)
		((CArcs *)m_OutputArcs[i])->MoveArc(m_center,0,pdc);
}

void CTransition::DeleteTransition(CDC *pdc,list<int> *plarc)
{
	/*
		This function delete the transition.
	*/
	int i;
	//erase the transition
	CPen lpen(PS_SOLID,1,RGB(255,255,255));
	CPen *pOldPen=pdc->SelectObject(&lpen);
	pdc->Rectangle(m_center.x-dim,m_center.y-dim,m_center.x+dim,m_center.y+dim);
	pdc->SelectObject(pOldPen);
	COLORREF oldcolor=pdc->SetTextColor(RGB(255,255,255));
	if(m_type==1) pdc->TextOut(m_center.x,m_center.y,delay_str);
	pdc->TextOut(m_text.x,m_text.y,valstr);
	pdc->SetTextColor(oldcolor);
	//delete the input arcs
	for(i=0;i<m_InputArcs.GetSize();i++)
	{
		plarc->insert(plarc->end(),((CArcs *)m_InputArcs[i])->pos);
		((CArcs *)m_InputArcs[i])->DeleteArc(pdc,1);
	}
	m_InputArcs.RemoveAll();
	//delete the output arcs
	for(i=0;i<m_OutputArcs.GetSize();i++)
	{
		plarc->insert(plarc->end(),((CArcs *)m_OutputArcs[i])->pos);
		((CArcs *)m_OutputArcs[i])->DeleteArc(pdc,0);
	}
	m_OutputArcs.RemoveAll();
	plarc->sort();
	plarc->unique();
}

void CTransition::AddInputArc(CArcs *parc)
{
	/*
		This function add an input arc to transition.
	*/
	try
	{
		m_InputArcs.Add(parc);
	}
	catch (CMemoryException *perr)
	{
		// Display a message for the user, giving him or her the
		// bad news
		AfxMessageBox("Out of memory", MB_ICONSTOP | MB_OK);
		// Delete the exception object
		perr->Delete();
	}
}

void CTransition::AddOutputArc(CArcs *parc)
{
	/*
		This function adds an output arc to the transition.
	*/
	try
	{
		m_OutputArcs.Add(parc);
	}
	catch (CMemoryException *perr)
	{
		// Display a message for the user, giving him or her the
		// bad news
		AfxMessageBox("Out of memory", MB_ICONSTOP | MB_OK);
		// Delete the exception object
		perr->Delete();
	}
}

void CTransition::DeleteArc(int pos)
{
	/*
		This function delete an arc.
	*/
	bool flag;
	flag=false;
	int i;
	for(i=0;i<m_InputArcs.GetSize();i++)
		if(((CArcs *)m_InputArcs[i])->pos==pos)
		{
			flag=true;
			m_InputArcs.RemoveAt(i,1);
			m_InputArcs.FreeExtra();
			break;
		}
	if(flag==false)
	for(i=0;i<m_OutputArcs.GetSize();i++)
		if(((CArcs *)m_OutputArcs[i])->pos==pos)
		{
			flag=true;
			m_OutputArcs.RemoveAt(i,1);
			m_OutputArcs.FreeExtra();
			break;
		}
}

void CTransition::Serialize(CArchive &ar)
{
	/*
		This function serializes the transtion class.
	*/
	CObject::Serialize(ar);
	if(ar.IsStoring())
	{
		ar<<m_center.x<<m_center.y<<m_text.x<<m_text.y<<position<<valstr<<m_type<<dim;
		if(m_type==1) ar<<delay_str<<m_delay;
	}
	else
	{
		ar>>m_center.x>>m_center.y>>m_text.x>>m_text.y>>position>>valstr>>m_type>>dim;
		if(m_type==1) ar>>delay_str>>m_delay;
	}
}

CPoint CTransition::GetCenter()
{
	/*
		This function return the center of the transition.
	*/
	return m_center;
}

void CTransition::ZoomTransition(float zoom, CDC *pdc)
{
	/*
		This function makes the zoom of the transition.
	*/
	//erase the old transition
	CPen lpen(PS_SOLID,1,RGB(255,255,255));
	CPen *pOldPen=pdc->SelectObject(&lpen);
	COLORREF oldcolor=pdc->SetTextColor(RGB(255,255,255));
	if(m_type==1) pdc->TextOut(m_center.x,m_center.y,delay_str);
	pdc->TextOut(m_text.x,m_text.y,valstr);
	pdc->SetTextColor(oldcolor);
	pdc->Rectangle(m_center.x-dim,m_center.y-dim,m_center.x+dim,m_center.y+dim);
	//update points
	dim=dim*zoom;
	m_center.x=(int)(m_center.x*zoom);
	m_center.y=(int)(m_center.y*zoom);
	m_text.x=m_center.x+dim;
	m_text.y=m_center.y+dim;
	//draw the new transition
	pdc->SelectObject(pOldPen);
	pdc->Rectangle(m_center.x-dim,m_center.y-dim,m_center.x+dim,m_center.y+dim);
	if(m_type==1) pdc->TextOut(m_center.x,m_center.y,delay_str);
	pdc->TextOut(m_text.x,m_text.y,valstr);
	//notify the input arcs
	int i;
	for(i=0;i<m_InputArcs.GetSize();i++)
		((CArcs *)m_InputArcs[i])->MoveArc(m_center,1,pdc);
	//notify the output arcs
	for(i=0;i<m_OutputArcs.GetSize();i++)
		((CArcs *)m_OutputArcs[i])->MoveArc(m_center,0,pdc);
}
