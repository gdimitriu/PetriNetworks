// Value1.h : header file
//
/////////////////////////////////////////////////////////////////////////////
/*
	Copyright 2004 Gabriel Dimitriu

	This file is part of Petri Network.
	This is the class behind Value Dialog. It is used for ask one value from the user..

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

#if !defined(AFX_VALUE1_H__04B48936_DD80_47E9_890D_90B69968A365__INCLUDED_)
#define AFX_VALUE1_H__04B48936_DD80_47E9_890D_90B69968A365__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CValue1 dialog

class CValue1 : public CDialog
{
// Construction
public:
	bool m_flag;
	CValue1(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CValue1)
	enum { IDD = IDD_VALUE1 };
	CString	m_value;
	CString	m_info;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CValue1)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CValue1)
	afx_msg void OnOKValue1();
	afx_msg void OnCancelValue1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VALUE1_H__04B48936_DD80_47E9_890D_90B69968A365__INCLUDED_)
