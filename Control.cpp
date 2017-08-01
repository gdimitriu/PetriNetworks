// Control.cpp : implementation file
//

#include "stdafx.h"
#include "PetriNetwork.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CControl dialog


CControl::CControl(CWnd* pParent /*=NULL*/)
	: CDialog(CControl::IDD, pParent)
{
	//{{AFX_DATA_INIT(CControl)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	Create(IDD_CONTROL,NULL);
	ShowWindow(0);
}

void CControl::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CControl)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


/////////////////////////////////////////////////////////////////////////////
// CControl message handlers

void CControl::OnControlOk() 
{
	// TODO: Add your control notification handler code here
	
}
