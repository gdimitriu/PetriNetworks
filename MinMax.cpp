// MinMax.cpp : implementation file
//

#include "stdafx.h"
#include "PetriNetwork.h"
#include "MinMax.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMinMax dialog


CMinMax::CMinMax(int nrL)
	: CDialog(CMinMax::IDD, NULL)
{
	//{{AFX_DATA_INIT(CMinMax)
	m_end = nrL-1;
	m_start = 0;
	//}}AFX_DATA_INIT
}

CMinMax::CMinMax(CWnd* pParent /*=NULL*/)
	: CDialog(CMinMax::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMinMax)
	m_end = 0;
	m_start = 0;
	//}}AFX_DATA_INIT
}

void CMinMax::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMinMax)
	DDX_Text(pDX, IDC_end, m_end);
	DDX_Text(pDX, IDC_start, m_start);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMinMax, CDialog)
	//{{AFX_MSG_MAP(CMinMax)
	ON_BN_CLICKED(IDC_CANCEL, OnCancel)
	ON_BN_CLICKED(IDC_OK, OnOk)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMinMax message handlers

void CMinMax::get(int &start, int &stop, bool &type)
{
	start=m_start;
	stop=m_end;
	type=m_type;
}

void CMinMax::OnCancel() 
{
	m_type=true;
	CDialog::OnCancel();
}

void CMinMax::OnOk() 
{
	UpdateData(TRUE);
	if(this->GetCheckedRadioButton(IDC_min,IDC_max)==IDC_min)
		m_type=true;
	else m_type=false;
	CDialog::OnOK();
}
