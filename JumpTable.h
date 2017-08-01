// JumpTable.h: interface for the CJumpTable class.
//
//////////////////////////////////////////////////////////////////////
/*
	Copyright 2004 Gabriel Dimitriu

	This file is part of Petri Network.
	This class stores an element of Jump Table for mJPN.

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

#if !defined(AFX_JUMPTABLE_H__7E4F3273_FE8A_4BBC_A610_83C15967B1C9__INCLUDED_)
#define AFX_JUMPTABLE_H__7E4F3273_FE8A_4BBC_A610_83C15967B1C9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CJumpTable : public CObject  
{
	DECLARE_SERIAL(CJumpTable)
public:
	virtual void Serialize(CArchive &ar);
	int nrLoc;
	CJumpTable(int nloc,CString in,CString out);
	CJumpTable();
	virtual ~CJumpTable();
	int *input;
	int *output;
};

#endif // !defined(AFX_JUMPTABLE_H__7E4F3273_FE8A_4BBC_A610_83C15967B1C9__INCLUDED_)
