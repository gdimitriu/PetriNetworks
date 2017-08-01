// Location.cpp: implementation of the CLocation class.
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
#include "Location.h"
#include "Value.h"
#include "Value1.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
IMPLEMENT_SERIAL(CLocation,CObject,1)
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLocation::CLocation()
{

}

CLocation::~CLocation()
{

}
CLocation::CLocation(CPoint point,CPetriNetworkDoc *pdoc,bool flag,int pos,int type,float dim1)
{
	/*
		This is the constructor for the CLocation class.
		If flag is true we have manual mode.
		If flag is false we have automatic mode.
	*/
	m_center=point;
	m_Type=type;
	dim=dim1;
	if(flag==true)
	{
		//get the name of location
		bool flag1;
		flag1=false;
		while(flag1==false)
		{
			if(m_Type>=0)
			{
				CValue valtemp;
				valtemp.m_info.Empty();
				valtemp.m_info.Insert(0,"Name of location");
				valtemp.m_info2.Empty();
				valtemp.m_info2.Insert(0,"Mark of location");
				valtemp.DoModal();
				if(valtemp.m_flag==true)
				{
					if(valtemp.m_delay.IsEmpty()==0)
					{
						valstr.Empty();
						valstr.Insert(0,valtemp.m_delay);
						m_Mark=atoi(valstr.GetBuffer(valstr.GetLength()));
					}
					else m_Mark=0;
					valstr.Empty();
					valstr.Insert(0,valtemp.m_value);
					m_text.x=m_center.x+dim;
					m_text.y=m_center.y+dim;
					position=atoi(valstr.GetBuffer(valstr.GetLength()));
					valstr.ReleaseBuffer();
					if(pdoc->TestState(position,0)==false)
					{
						flag1=true;
					}
				}
			}
			else
			{
				CValue1 valtemp;
				valtemp.m_info.Empty();
				valtemp.m_info.Insert(0,"Name of location in order 0...");
				valtemp.DoModal();
				if(valtemp.m_flag==true)
				{
					valstr.Empty();
					valstr.Insert(0,valtemp.m_value);
					m_text.x=m_center.x+dim;
					m_text.y=m_center.y+dim;
					position=atoi(valstr.GetBuffer(valstr.GetLength()));
					valstr.ReleaseBuffer();
					if(pdoc->TestState(position,0)==false)
					{
						flag1=true;
					}
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
		itoa(pos,temp,10);
		valstr.Insert(0,temp);
	}
}
void CLocation::Draw(CDC *pdc)
{
	/*
		This function draws the location.
	*/
	pdc->Ellipse(m_center.x-dim,m_center.y-dim,m_center.x+dim,m_center.y+dim);
	if(m_Type>=0)
	{
		pdc->TextOut(m_text.x,m_text.y,valstr);
		CString temp;
		temp.Empty();
		temp.Format("%d",m_Mark);
		COLORREF oldcolor=pdc->SetTextColor(RGB(0,0,255));
		pdc->TextOut(m_center.x-dim/2,m_center.y-dim/2,temp);
		pdc->SetTextColor(oldcolor);
	}
	else pdc->TextOut(m_center.x-dim/2,m_center.y-dim/2,valstr);
}

void CLocation::MoveLocation(CPoint point, CDC *pdc)
{
	/*
		This function moves the location to the point.
	*/
	//erase the old location
	CPen lpen(PS_SOLID,1,RGB(255,255,255));
	CPen *pOldPen=pdc->SelectObject(&lpen);
	COLORREF oldcolor=pdc->SetTextColor(RGB(255,255,255));
	if(m_Type>=0)
	{
		pdc->TextOut(m_text.x,m_text.y,valstr);
		CString temp;
		temp.Empty();
		temp.Format("%d",m_Mark);
		pdc->TextOut(m_center.x-dim/2,m_center.y-dim/2,temp);
	}
	else pdc->TextOut(m_center.x-dim/2,m_center.y-dim/2,valstr);
	pdc->SetTextColor(oldcolor);
	pdc->Ellipse(m_center.x-dim,m_center.y-dim,m_center.x+dim,m_center.y+dim);
	//update points
	m_center=point;
	m_text.x=m_center.x+dim;
	m_text.y=m_center.y+dim;
	//draw the new location
	pdc->SelectObject(pOldPen);
	pdc->Ellipse(m_center.x-dim,m_center.y-dim,m_center.x+dim,m_center.y+dim);
	if(m_Type>=0)
	{
		pdc->TextOut(m_text.x,m_text.y,valstr);
		CString temp;
		temp.Empty();
		temp.Format("%d",m_Mark);
		pdc->SetTextColor(RGB(0,0,255));
		pdc->TextOut(m_center.x-dim/2,m_center.y-dim/2,temp);
		pdc->SetTextColor(oldcolor);
	}
	else pdc->TextOut(m_center.x-dim/2,m_center.y-dim/2,valstr);
	//notify the input arcs
	int i;
	for(i=0;i<m_InputArcs.GetSize();i++)
		((CArcs *)m_InputArcs[i])->MoveArc(m_center,1,pdc);
	//notify the output arcs
	for(i=0;i<m_OutputArcs.GetSize();i++)
		((CArcs *)m_OutputArcs[i])->MoveArc(m_center,0,pdc);
}

void CLocation::DeleteLocation(CDC *pdc,list<int> *plarc)
{
	/*
		This function deletes this location.
		In plarc we have the arcs attached to this location.
		This arcs must be removed in the document.
	*/
	int i;
	//erase the location
	CPen lpen(PS_SOLID,1,RGB(255,255,255));
	CPen *pOldPen=pdc->SelectObject(&lpen);
	pdc->Ellipse(m_center.x-dim,m_center.y-dim,m_center.x+dim,m_center.y+dim);
	pdc->SelectObject(pOldPen);
	COLORREF oldcolor=pdc->SetTextColor(RGB(255,255,255));
	if(m_Type>=0)
	{
		pdc->TextOut(m_text.x,m_text.y,valstr);
		CString temp;
		temp.Empty();
		temp.Format("%d",m_Mark);
		pdc->TextOut(m_center.x-dim/2,m_center.y-dim/2,temp);
	}
	else pdc->TextOut(m_center.x-dim/2,m_center.y-dim/2,valstr);
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
void CLocation::AddInputArc(CArcs *parc)
{
	/*
		This function adds an input arc to this location.
		The arc is pointed by parc.
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

void CLocation::AddOutputArc(CArcs *parc)
{
	/*
		This function adds an output arc to this location.
		The arc is pointed by parc.
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

void CLocation::DeleteArc(int pos)
{
	/*
		This function deletes an arc given by its position in the array.
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

void CLocation::Serialize(CArchive &ar)
{
	/*
		This function serializes the CLocation class.
	*/
	CObject::Serialize(ar);
	if(ar.IsStoring())
	{
		ar<<m_Type;
		if(m_Type>=0) ar<<m_center.x<<m_center.y<<m_text.x<<m_text.y<<position<<m_Mark<<dim;
		else ar<<m_center.x<<m_center.y<<m_text.x<<m_text.y<<position<<dim;
	}
	else
	{
		ar>>m_Type;
		if(m_Type>=0)
		{
			ar>>m_center.x>>m_center.y>>m_text.x>>m_text.y>>position>>m_Mark>>dim;
			valstr.Empty();
			char temp[10];
			for(int i=0;i<10;i++) temp[i]='\0';
			itoa(position,temp,10);
			valstr.Insert(0,temp);
		}
		else
		{
			ar>>m_center.x>>m_center.y>>m_text.x>>m_text.y>>position>>dim;
			valstr.Empty();
			char temp[10];
			for(int i=0;i<10;i++) temp[i]='\0';
			itoa(position,temp,10);
			valstr.Insert(0,temp);
		}
	}
}

CPoint CLocation::GetCenter()
{
	/*
		This function returns the center of the location to the caller.
	*/
	return m_center;
}

void CLocation::ZoomLocation(float zoom, CDC *pdc)
{
	/*
		This function makes the zoom of the location.
	*/
	//erase the old location
	CPen lpen(PS_SOLID,1,RGB(255,255,255));
	CPen *pOldPen=pdc->SelectObject(&lpen);
	COLORREF oldcolor=pdc->SetTextColor(RGB(255,255,255));
	if(m_Type>=0)
	{
		pdc->TextOut(m_text.x,m_text.y,valstr);
		CString temp;
		temp.Empty();
		temp.Format("%d",m_Mark);
		pdc->TextOut(m_center.x-dim/2,m_center.y-dim/2,temp);
	}
	else pdc->TextOut(m_center.x-dim/2,m_center.y-dim/2,valstr);
	pdc->SetTextColor(oldcolor);
	pdc->Ellipse(m_center.x-dim,m_center.y-dim,m_center.x+dim,m_center.y+dim);
	//update points
	m_center.x=(int)(m_center.x*zoom);
	m_center.y=(int)(m_center.y*zoom);
	dim=dim*zoom;
	m_text.x=m_center.x+dim;
	m_text.y=m_center.y+dim;
	//draw the new location
	pdc->SelectObject(pOldPen);
	pdc->Ellipse(m_center.x-dim,m_center.y-dim,m_center.x+dim,m_center.y+dim);
	if(m_Type>=0)
	{
		pdc->TextOut(m_text.x,m_text.y,valstr);
		CString temp;
		temp.Empty();
		temp.Format("%d",m_Mark);
		pdc->SetTextColor(RGB(0,0,255));
		pdc->TextOut(m_center.x-dim/2,m_center.y-dim/2,temp);
		pdc->SetTextColor(oldcolor);
	}
	else pdc->TextOut(m_center.x-dim/2,m_center.y-dim/2,valstr);
	//notify the input arcs
	int i;
	for(i=0;i<m_InputArcs.GetSize();i++)
		((CArcs *)m_InputArcs[i])->MoveArc(m_center,1,pdc);
	//notify the output arcs
	for(i=0;i<m_OutputArcs.GetSize();i++)
		((CArcs *)m_OutputArcs[i])->MoveArc(m_center,0,pdc);
}
