// Location.h: interface for the CLocation class.
//
//////////////////////////////////////////////////////////////////////
/*
	Copyright 2004 Gabriel Dimitriu

	This file is part of Petri Network.
	This class stores a location instance.

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

#if !defined(AFX_LOCATION_H__F37181F4_CC1A_4ED3_B60F_C82264DB238E__INCLUDED_)
#define AFX_LOCATION_H__F37181F4_CC1A_4ED3_B60F_C82264DB238E__INCLUDED_

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

class CLocation : public CObject  
{
	DECLARE_SERIAL(CLocation)
public:
	void ZoomLocation(float zoom,CDC *pdc);
	CPoint GetCenter(void);
	float dim;
	virtual void Serialize(CArchive &ar);
	int m_Mark;
	CPoint m_text;
	CString valstr;
	void AddOutputArc(CArcs *parc);
	void AddInputArc(CArcs *parc);
	void DeleteLocation(CDC *pdc,list<int> *plarc);
	void DeleteArc(int pos);
	void MoveLocation(CPoint point,CDC *pdc);
	void Draw(CDC *pdc);
	CLocation();
	CLocation(CPoint point,CPetriNetworkDoc *pdoc,bool flag,int pos,int type,float dim1);
	virtual ~CLocation();
	CPoint m_center;
	int position;
	int m_Type;
	CObArray m_InputArcs;
	CObArray m_OutputArcs;
};

#endif // !defined(AFX_LOCATION_H__F37181F4_CC1A_4ED3_B60F_C82264DB238E__INCLUDED_)
