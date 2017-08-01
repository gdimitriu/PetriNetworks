// InJump.cpp : implementation file
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
#include "InJump.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInJump dialog


CInJump::CInJump(CWnd* pParent /*=NULL*/)
	: CDialog(CInJump::IDD, pParent)
{
	//{{AFX_DATA_INIT(CInJump)
	m_in = _T("");
	m_info = _T("");
	m_out = _T("");
	//}}AFX_DATA_INIT
}


void CInJump::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInJump)
	DDX_Text(pDX, IDC_IN, m_in);
	DDX_Text(pDX, IDC_Message, m_info);
	DDX_Text(pDX, IDC_OUT, m_out);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CInJump, CDialog)
	//{{AFX_MSG_MAP(CInJump)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInJump message handlers

void CInJump::OnOK() 
{
	m_flag=true;	
	CDialog::OnOK();
}

void CInJump::OnCancel() 
{
	m_flag=false;	
	CDialog::OnCancel();
}

