// Ask.cpp : implementation file
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
#include "Ask.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAsk dialog


CAsk::CAsk(CWnd* pParent /*=NULL*/)
	: CDialog(CAsk::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAsk)
	m_info = _T("");
	//}}AFX_DATA_INIT
}


void CAsk::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAsk)
	DDX_Text(pDX, IDC_Info, m_info);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAsk, CDialog)
	//{{AFX_MSG_MAP(CAsk)
	ON_BN_CLICKED(ID_YES, OnYes)
	ON_BN_CLICKED(ID_NO, OnNo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAsk message handlers

void CAsk::OnYes() 
{
	m_value=true;
	OnOK();
}

void CAsk::OnNo() 
{
	m_value=false;	
	OnOK();
}
