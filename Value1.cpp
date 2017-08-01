// Value1.cpp : implementation file
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
#include "Value1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CValue1 dialog


CValue1::CValue1(CWnd* pParent /*=NULL*/)
	: CDialog(CValue1::IDD, pParent)
{
	//{{AFX_DATA_INIT(CValue1)
	m_value = _T("");
	m_info = _T("");
	//}}AFX_DATA_INIT
}


void CValue1::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CValue1)
	DDX_Text(pDX, IDC_VALUE, m_value);
	DDX_Text(pDX, IDC_Info, m_info);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CValue1, CDialog)
	//{{AFX_MSG_MAP(CValue1)
	ON_BN_CLICKED(IDOK_Value1, OnOKValue1)
	ON_BN_CLICKED(IDCANCEL_Value1, OnCancelValue1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CValue1 message handlers

void CValue1::OnOKValue1() 
{
	// TODO: Add your control notification handler code here
	m_flag=true;
	CDialog::OnOK();
}

void CValue1::OnCancelValue1() 
{
	// TODO: Add your control notification handler code here
	m_flag=false;	
	CDialog::OnCancel();
}
