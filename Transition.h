// Transition.h: interface for the CTransition class.
//
//////////////////////////////////////////////////////////////////////
/*
	Copyright 2004 Gabriel Dimitriu

	This file is part of Petri Network.
	This class implements the transition class.

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

#if !defined(AFX_TRansition_H__B932B7B3_FCC3_4194_9147_2681285BB559__INCLUDED_)
#define AFX_TRansition_H__B932B7B3_FCC3_4194_9147_2681285BB559__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include<list>
#include<string>
#include"Arcs.h"
#include "PetriNetworkDoc.h"

class CArcs;
class CPetriNetworkDoc;
using namespace std ;

class CTransition : public CObject  
{
	DECLARE_SERIAL(CTransition)
public:
	void ZoomTransition(float zoom,CDC *pdc);
	CPoint GetCenter(void);
	int m_delay;
	float dim;
	virtual void Serialize(CArchive &ar);
	void DeleteArc(int pos);
	void AddOutputArc(CArcs *parc);
	void AddInputArc(CArcs *parc);
	void DeleteTransition(CDC *pdc,list<int> *plarc);
	void MoveTransition(CPoint point,CDC *pdc);
	void Draw(CDC *pdc);
	CTransition();
	CTransition(CPoint point,CPetriNetworkDoc *pdoc,bool flag,int pos,int type,float dim1);
	CTransition(CPoint point,CPetriNetworkDoc *pdoc,int pos,int type,int delay,float dim1);
	virtual ~CTransition();
	CString valstr;
	CPoint m_text;
	CPoint m_center;
	int position;
	CString delay_str;
	CObArray m_InputArcs;
	CObArray m_OutputArcs;
	int m_type;
};

#endif // !defined(AFX_Transition_H__B932B7B3_FCC3_4194_9147_2681285BB559__INCLUDED_)
