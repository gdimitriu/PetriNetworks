// Marked.cpp : implementation file
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
#include "Marked.h"
#include "JumpTable.h"
#include "Value1.h"
#include <stdlib.h>
#include <fstream>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMarked

IMPLEMENT_DYNCREATE(CMarked, CWinThread)

CMarked::CMarked()
{
}

CMarked::~CMarked()
{
	/*
		This is the destructor for the CMarked class.
	*/
	if(m_Delta!=NULL)
	{
		free(m_Delta);
		m_Delta=NULL;
	}
}

BOOL CMarked::InitInstance()
{
	// TODO:  perform and per-thread initialization here
	return TRUE;
}

CMarked::CMarked(int **Pre,int **Post,int nrL,int nrT,int *mark,int *delay,CCriticalSection *sec,int *oper,CEvent *event,CPetriNetworkDoc *pdoc,int type,CObArray *jump)
{
	/*
		This is the constructor for the CMarked class.
	*/
	m_Pre=Pre;
	m_Post=Post;
	m_nrLoc=nrL;
	m_nrTran=nrT;
	m_mark=mark;
	m_Sincro=sec;
	m_oper=oper;
	m_StartStop=event;
	m_pDoc=pdoc;
	m_Type=type;
	JumpRel=jump;
	m_delay=delay;
	int *temp;
	int i,j;
	if(m_Type!=1)
	{
		m_Delta=(int **)calloc(m_nrLoc,sizeof(int *));
		temp=(int *)calloc(m_nrLoc*m_nrTran,sizeof(int));
		for(i=0;i<m_nrLoc;i++)
		{
			m_Delta[i]=temp;
			temp+=m_nrTran;
		}
		for(i=0;i<m_nrLoc;i++)
			for(j=0;j<m_nrTran;j++)
				m_Delta[i][j]=m_Post[i][j]-m_Pre[i][j];
	}
	else m_Delta=NULL;
	if(m_nrTran<m_nrLoc) m_max=m_nrLoc;
	else m_max=m_nrTran;
	execc=(int *)calloc(m_max,sizeof(int));
	m_Pret=(int *)calloc(m_nrTran,sizeof(int));
	if(m_Type==2) m_jump=(int *)calloc(m_nrLoc,sizeof(int));
	else m_jump=NULL;
	if(m_Type==1)
	{
		m_Ro=(int *)calloc(m_nrTran,sizeof(int));
		for(i=0;i<m_nrTran;i++) m_Ro[i]=0;
	}
	else m_Ro=NULL;
	concurent=0;
}

int CMarked::ExitInstance()
{
	/*
		This is the function for clean up.
	*/
	if(m_Type!=1)
	{
		free(*m_Delta);
		free(m_Delta);
	}
	free(execc);
	free(m_Pret);
	if(m_Type==1) free(m_Ro);
	if(m_Type==2) free(m_jump);
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CMarked, CWinThread)
	//{{AFX_MSG_MAP(CMarked)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMarked message handlers

int CMarked::Run()
{
	/*
		This is the main function for the PN simulator.
	*/
	valtemp.m_info.Empty();
	valtemp.m_info.Insert(0,"Step of simulation in ms, default 1000ms");
	valtemp.DoModal();
	if(valtemp.m_flag==true)
	{
		valstr.Empty();
		valstr.Insert(0,valtemp.m_value);
		val=atol(valstr.GetBuffer(valstr.GetLength()));
		valstr.ReleaseBuffer();
	}
	else val=1000L;
	m_Oper=0; //set for run
	while(m_Oper!=2)
	{
		if(m_Oper==1) //we want stop
		{
			m_handlepriv=m_StartStop->m_hObject;
			::WaitForSingleObject(m_handlepriv,INFINITE);
			m_StartStop->ResetEvent();
			m_pDoc->ReMark(false);
		}
		else
		{
			Sleep(val);
			m_Sincro->Lock();
			m_Oper=*m_oper;
			m_Sincro->Unlock();
			if(m_Oper==0)
			{
				concurent=0;
				switch(m_Type)
				{
					case 0:
						mPN();
						break;
					case 1:
						mTPN();
						break;
					case 2:
						mJPN();
						break;
					default:
						mPN();
				}
				m_pDoc->ReMark(true);
			}
		}
		m_Sincro->Lock();
		m_Oper=*m_oper;
		m_Sincro->Unlock();
	}
	AfxMessageBox("Simulation is finished");
	return 0;
}

void CMarked::mPN()
{
	/*
		This is the function who simulate a step of mPN.
		It is called every slice of time from Run.
	*/
	int i,j;
	for(i=0;i<m_max;i++) execc[i]=0;
	for(i=0;i<m_nrTran;i++)
	{
		flag=true;
		for(j=0;j<m_nrLoc;j++)
		{
			if(m_mark[j]<m_Pre[j][i])
			{
				flag=false;
				break;
			}
		}
		if(flag==true)
		{
			execc[concurent]=i;
			concurent++;
		}
	}
	if(concurent>1)
	{
		for(j=0;j<m_nrLoc;j++)
		{
			m_Pret[j]=0;
			for(i=0;i<concurent;i++) m_Pret[j]+=m_Pre[j][execc[i]];
		}
		flag=true;
		for(j=0;j<m_nrLoc;j++)
		{
			if(m_mark[j]<m_Pret[j])
			{
				flag=false;
				break;
			}
		}
		if(flag==true) //we have parallel execution
		{
			for(i=0;i<concurent;i++)
			for(j=0;j<m_nrLoc;j++) m_mark[j]+=m_Delta[j][execc[i]];
		}
		else //we haven't parallel execution
		{
			if(concurent==2) //we  have 2 location in conflict
			{
				valtemp.m_info.Empty();
				valtemp.m_info.Format("Concurent at %d %d who have priority (0/1)",execc[0],execc[1]);
				bool flag=false;
				int priority;
				while(flag==false)
				{
					valtemp.m_value.Empty();
					valtemp.DoModal();
					if(valtemp.m_flag==true)
					{
						valstr.Empty();
						valstr.Insert(0,valtemp.m_value);
						priority=atoi(valstr.GetBuffer(valstr.GetLength()));
						valstr.ReleaseBuffer();
						if(priority==execc[0] || priority==execc[1]) flag=true;
					}
					else
					{
						priority=0;
						flag=true;
					}
				}
				for(j=0;j<m_nrLoc;j++) m_mark[j]+=m_Delta[j][execc[priority]];
			}
			else //we have more than 2 location in conflict
			{
				flag=false;
				while(flag==false)
				{
					for(j=0;j<m_nrLoc;j++)
						m_Pret[j]-=m_Pre[j][execc[concurent-1]];
					concurent--;
					flag=true;
					for(j=0;j<m_nrLoc;j++)
					{
						if(m_mark[j]<m_Pret[j])
						{
							flag=false;
							break;
						}
					}
				}
				for(i=0;i<concurent;i++)
				for(j=0;j<m_nrLoc;j++) m_mark[j]+=m_Delta[j][execc[i]];
			}
		}
	}
	else if(concurent==1) for(j=0;j<m_nrLoc;j++) m_mark[j]+=m_Delta[j][execc[0]];
}

void CMarked::mJPN()
{
	/*
		This is the function who simulate a step of mJPN.
		It is called every slice of time from Run.
	*/
	int i,j,k;
	bool flag;
	CValue1 valdlg;
	//find the input jump
	for(i=0;i<m_nrLoc;i++) m_jump[i]=-1;
	k=0;
	for(i=0;i<JumpRel[0].GetSize();i++)
	{
		flag=true;
		for(j=0;j<m_nrLoc;j++)
			if(((CJumpTable *)JumpRel[0][i])->input[j]!=m_mark[j])
			{
				flag=false;
				break;
			}
		if(flag==true)
		{
			m_jump[k]=i;
			k++;
			concurent++;
		}
	}
	if(concurent==1)
	{
		for(i=0;i<m_nrLoc;i++)
			m_mark[i]=((CJumpTable *)JumpRel[0][m_jump[0]])->output[i];
	}
	else if(concurent==2)
	{
		int temp;
		char strtmp[10];
		valdlg.m_info.Empty();
		temp=valdlg.m_info.Insert(0,"Jump from (");
		for(j=0;j<m_nrLoc;j++)
		{
			for(i=0;i<10;i++) strtmp[i]='\0';
			_itoa(((CJumpTable *)JumpRel[0][m_jump[0]])->input[j],strtmp,10);
			temp=valdlg.m_info.Insert(temp,strtmp);
			temp=valdlg.m_info.Insert(temp,",");
		}
		temp=valdlg.m_info.Insert(temp,") to (");
		for(j=0;j<m_nrLoc;j++)
		{
			for(i=0;i<10;i++) strtmp[i]='\0';
			_itoa(((CJumpTable *)JumpRel[0][m_jump[0]])->output[j],strtmp,10);
			temp=valdlg.m_info.Insert(temp,strtmp);
			temp=valdlg.m_info.Insert(temp,",");
		}
		temp=valdlg.m_info.Insert(temp,") or (");
		for(j=0;j<m_nrLoc;j++)
		{
			for(i=0;i<10;i++) strtmp[i]='\0';
			_itoa(((CJumpTable *)JumpRel[0][m_jump[1]])->output[j],strtmp,10);
			temp=valdlg.m_info.Insert(temp,strtmp);
			temp=valdlg.m_info.Insert(temp,",");
		}
		temp=valdlg.m_info.Insert(temp,") 0/1");
		valdlg.DoModal();
		if(valdlg.m_flag==true)
		{
			temp=atoi(valdlg.m_value.GetBuffer(valdlg.m_value.GetLength()));
			valdlg.m_value.ReleaseBuffer();
		}
		else temp=0;
		if(!(temp==0 || temp==1)) temp=0;
		for(i=0;i<m_nrLoc;i++)
			m_mark[i]=((CJumpTable *)JumpRel[0][m_jump[temp]])->output[i];
	}
	mPN();
	//find the output jump
	for(i=0;i<m_nrLoc;i++) m_jump[i]=-1;
	k=0;
	concurent=0;
	for(i=0;i<JumpRel[0].GetSize();i++)
	{
		flag=true;
		for(j=0;j<m_nrLoc;j++)
			if(((CJumpTable *)JumpRel[0][i])->input[j]!=m_mark[j])
			{
				flag=false;
				break;
			}
		if(flag==true)
		{
			m_jump[k]=i;
			k++;
			concurent++;
		}
	}
	if(concurent==1)
	{
		for(i=0;i<m_nrLoc;i++)
			m_mark[i]=((CJumpTable *)JumpRel[0][m_jump[0]])->output[i];
	}
	else if(concurent==2)
	{
		int temp;
		char strtmp[10];
		valdlg.m_info.Empty();
		temp=valdlg.m_info.Insert(0,"Jump from (");
		for(j=0;j<m_nrLoc;j++)
		{
			for(i=0;i<10;i++) strtmp[i]='\0';
			_itoa(((CJumpTable *)JumpRel[0][m_jump[0]])->input[j],strtmp,10);
			temp=valdlg.m_info.Insert(temp,strtmp);
			temp=valdlg.m_info.Insert(temp,",");
		}
		temp=valdlg.m_info.Insert(temp,") to (");
		for(j=0;j<m_nrLoc;j++)
		{
			for(i=0;i<10;i++) strtmp[i]='\0';
			_itoa(((CJumpTable *)JumpRel[0][m_jump[0]])->output[j],strtmp,10);
			temp=valdlg.m_info.Insert(temp,strtmp);
			temp=valdlg.m_info.Insert(temp,",");
		}
		temp=valdlg.m_info.Insert(temp,") or (");
		for(j=0;j<m_nrLoc;j++)
		{
			for(i=0;i<10;i++) strtmp[i]='\0';
			_itoa(((CJumpTable *)JumpRel[0][m_jump[1]])->output[j],strtmp,10);
			temp=valdlg.m_info.Insert(temp,strtmp);
			temp=valdlg.m_info.Insert(temp,",");
		}
		temp=valdlg.m_info.Insert(temp,") 0/1");
		valdlg.DoModal();
		if(valdlg.m_flag==true)
		{
			temp=atoi(valdlg.m_value.GetBuffer(valdlg.m_value.GetLength()));
			valdlg.m_value.ReleaseBuffer();
		}
		else temp=0;
		if(!(temp==0 || temp==1)) temp=0;
		for(i=0;i<m_nrLoc;i++)
			m_mark[i]=((CJumpTable *)JumpRel[0][m_jump[temp]])->output[i];
	}
}

void CMarked::mTPN()
{
	/*
		This is the function who simulate a step of mTPN.
		It is called every slice of time from Run.
	*/
	int i,j;
	concurent=0;
	for(i=0;i<m_max;i++) execc[i]=0;
	//find which transition have ended
	for(i=0;i<m_nrTran;i++)
		if(m_Ro[i]>0)
		{
			if(m_Ro[i]==1)
			{
				execc[concurent]=i;
				concurent++;
			}
			m_Ro[i]--;
			if(m_Ro[i]<0) m_Ro[i]=0;
		}
	if(concurent>0)
	{
		for(i=0;i<concurent;i++)
			for(j=0;j<m_nrLoc;j++)
				m_mark[j]+=m_Post[j][execc[i]];
	}
	for(i=0;i<m_max;i++) execc[i]=0;
	concurent=0;
	for(i=0;i<m_nrTran;i++)
	{
		flag=true;
		for(j=0;j<m_nrLoc;j++)
		{
			if(m_mark[j]<m_Pre[j][i])
			{
				flag=false;
				break;
			}
		}
		if(flag==true && m_Ro[i]==0)
		{
			execc[concurent]=i;
			concurent++;
		}
	}
	if(concurent>1)
	{
		for(j=0;j<m_nrLoc;j++)
		{
			m_Pret[j]=0;
			for(i=0;i<concurent;i++) m_Pret[j]+=m_Pre[j][execc[i]];
		}
		flag=true;
		for(j=0;j<m_nrLoc;j++)
		{
			if(m_mark[j]<m_Pret[j])
			{
				flag=false;
				break;
			}
		}
		if(flag==true) //we have parallel execution
		{
			for(i=0;i<concurent;i++)
			for(j=0;j<m_nrLoc;j++)
			{
				m_mark[j]-=m_Pre[j][execc[i]];
				m_Ro[i]=m_delay[i];
			}
		}
		else //we haven't parallel execution
		{
			if(concurent==2) //we  have 2 location in conflict
			{
				valtemp.m_info.Empty();
				valtemp.m_info.Format("Concurent at %d %d who have priority (0/1)",execc[0],execc[1]);
				bool flag=false;
				int priority;
				while(flag==false)
				{
					valtemp.m_value.Empty();
					valtemp.DoModal();
					if(valtemp.m_flag==true)
					{
						valstr.Empty();
						valstr.Insert(0,valtemp.m_value);
						priority=atoi(valstr.GetBuffer(valstr.GetLength()));
						valstr.ReleaseBuffer();
						if(priority==execc[0] || priority==execc[1]) flag=true;
					}
					else
					{
						priority=0;
						flag=true;
					}
				}
				for(j=0;j<m_nrLoc;j++)
				{
					m_mark[j]-=m_Pre[j][execc[priority]];
					m_Ro[execc[priority]]=m_delay[execc[priority]];
				}
			}
			else //we have more than 2 location in conflict
			{
				flag=false;
				while(flag==false)
				{
					for(j=0;j<m_nrLoc;j++)
						m_Pret[j]-=m_Pre[j][execc[concurent-1]];
					concurent--;
					flag=true;
					for(j=0;j<m_nrLoc;j++)
					{
						if(m_mark[j]<m_Pret[j])
						{
							flag=false;
							break;
						}
					}
				}
				for(i=0;i<concurent;i++)
				for(j=0;j<m_nrLoc;j++)
				{
					m_mark[j]-=m_Pre[j][execc[i]];
					m_Ro[execc[i]]=m_delay[execc[i]];
				}
			}
		}
	}
	else 
		if(concurent==1) 
			for(j=0;j<m_nrLoc;j++)
			{
				m_mark[j]-=m_Pre[j][execc[0]];
				m_Ro[execc[0]]=m_delay[execc[0]];
			}
}
