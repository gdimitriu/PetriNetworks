// Arcs.h: interface for the CArcs class.
//
//////////////////////////////////////////////////////////////////////
/*
	Copyright 2004 Gabriel Dimitriu

	This file is part of Petri Network.
	This class contain the information about arc. It also makes the link between
	different instances.

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

#if !defined(AFX_ARCS_H__976BA959_4F71_48F8_B82D_0AA9046C909C__INCLUDED_)
#define AFX_ARCS_H__976BA959_4F71_48F8_B82D_0AA9046C909C__INCLUDED_

#include "Location.h"	// Added by ClassView
#include "Transition.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include<list>
#include<string>

class CTransition;
class CLocation;
using namespace std ;

class CArcs : public CObject  
{
	DECLARE_SERIAL(CArcs)
public:
	float dimsgn;
	void ZoomArc(float zoom,CDC *pdc);
	float dim;
	void MoveArc(CPoint point,CDC *pdc);
	int m_Type;
	virtual void Serialize(CArchive &ar);
	bool DeleteArc(CPoint point,CDC *pdc);
	int GetEnd();
	void MoveArc(CPoint point,int flag,CDC *pdc);
	void DeleteArc(CDC *pdc,int flag);
	void ConnectS();
	void ConnectE();
	void AddEnd(CTransition *ptran,bool flag,int vals);
	void AddTrnLoc(CTransition *ptran,CLocation *ploc);
	void AddLocTrn(CLocation *ploc,CTransition *ptran);
	void AddLocLoc(CLocation *ploc1,CLocation *ploc2);
	void AddEnd(CLocation *ploc,bool flag,int vals);
	void AddStart(CTransition *ptran);
	void AddStart(CLocation *ploc);
	void Draw(CDC *pdc);
	void AddPoint(CPoint point,CDC *pdc);
	CArcs();
	CArcs(CPoint point,CDC *pdc,int type,float dim1,float dim2);
	virtual ~CArcs();
	CString valstr;
	CPoint m_text;
	int val;
	int pos;
	CTransition * m_EndTran;
	CTransition * m_StartTran;
	CLocation * m_EndLoc;
	CLocation * m_StartLoc;
	int reuse[4];
private:
	void ComputePos(int x1, int y1, int x2, int y2, int *xc, int *yc,bool flag);
	int yps,ype;
	int xps,xpe;
	list<CPoint> m_points;
	list<CPoint>::iterator m_pit;
};

#endif // !defined(AFX_ARCS_H__976BA959_4F71_48F8_B82D_0AA9046C909C__INCLUDED_)
