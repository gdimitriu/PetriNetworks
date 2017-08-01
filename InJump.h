// InJump.h : header file
//
/////////////////////////////////////////////////////////////////////////////
/*
	Copyright 2004 Gabriel Dimitriu

	This file is part of Petri Network.
	This is the class behind the InJump dialog.
	It is used for input the Jump realtion for mJPN.

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

#if !defined(AFX_INJUMP_H__36A54156_B6A9_4F90_9F27_2F6807E89F29__INCLUDED_)
#define AFX_INJUMP_H__36A54156_B6A9_4F90_9F27_2F6807E89F29__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CInJump dialog

class CInJump : public CDialog
{
// Construction
public:
	bool m_flag;
	CInJump(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CInJump)
	enum { IDD = IDD_INJUMP };
	CString	m_in;
	CString	m_info;
	CString	m_out;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInJump)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CInJump)
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INJUMP_H__36A54156_B6A9_4F90_9F27_2F6807E89F29__INCLUDED_)
