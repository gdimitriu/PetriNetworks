#if !defined(AFX_MINMAX_H__1CB35CC1_39A7_11DB_B910_E46737E98D0C__INCLUDED_)
#define AFX_MINMAX_H__1CB35CC1_39A7_11DB_B910_E46737E98D0C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MinMax.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMinMax dialog

class CMinMax : public CDialog
{
// Construction
public:
	bool m_type;
	void get(int &start,int &stop,bool &type);
	CMinMax(CWnd* pParent = NULL);// standard constructor
	CMinMax(int nrL);   
	

// Dialog Data
	//{{AFX_DATA(CMinMax)
	enum { IDD = IDD_minmax };
	int	m_end;
	int	m_start;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMinMax)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMinMax)
	afx_msg void OnCancel();
	afx_msg void OnOk();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MINMAX_H__1CB35CC1_39A7_11DB_B910_E46737E98D0C__INCLUDED_)
