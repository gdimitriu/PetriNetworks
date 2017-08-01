// Digraph.cpp : implementation file
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

#pragma warning(disable:4786)
#include "stdafx.h"
#include "PetriNetwork.h"
#include "Digraph.h"
#include <stack>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
using namespace std ;
/////////////////////////////////////////////////////////////////////////////
// CDigraph

IMPLEMENT_DYNCREATE(CDigraph, CWinThread)

CDigraph::CDigraph()
{
	m_L=NULL;
}

CDigraph::~CDigraph()
{
	if(m_L!=NULL) free(m_L);
}

CDigraph::CDigraph(int nrL,CCriticalSection *sec,int *oper,CEvent *event,CPetriNetworkDoc *pdoc,int type,int *oper1,int **mat,int inf)
{
	/*
		This is the constructor for the CDigraph class.
	*/
	m_nrLoc=nrL;
	m_Sincro=sec;
	m_oper=oper;
	m_StartStop=event;
	m_pDoc=pdoc;
	m_Type=type;
	m_opgraph=oper1;
	m_mat=mat;
	m_conex=false;
	m_cyclic=false;
	element=0;
	teaching=false;
	m_afisaj.Empty();
	m_file=false;
	stepe=0;
	m_L=NULL;
}

BOOL CDigraph::InitInstance()
{
	// TODO:  perform and per-thread initialization here
	return TRUE;
}

int CDigraph::ExitInstance()
{
	// TODO:  perform any per-thread cleanup here
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CDigraph, CWinThread)
	//{{AFX_MSG_MAP(CDigraph)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDigraph message handlers

int CDigraph::Run()
{
	/*
		This is the main function for the simulator in case of graph or digrah.
	*/
	int i;
	bool stop;
	askYN.m_info.Empty();
	askYN.m_info.Insert(0,"Teaching");
	askYN.DoModal();
	teaching=askYN.m_value;
	if(teaching==true)
	{
		valtemp.m_info.Empty();
		if(m_opgraph[2]==0 && m_opgraph[3]==0)
			valtemp.m_info.Insert(0,"Step of simulation in ms, default 1000ms");
		else
		{
			if(m_opgraph[3]==1)
				valtemp.m_info.Insert(0,"Step of simulation in ms, default 1000ms");
			if(m_opgraph[2]==1)
				valtemp.m_info.Insert(0,"Step of simulation in ms, default 100ms");
		}
		valtemp.m_value.Empty();
		valtemp.DoModal();
		if(valtemp.m_flag==true)
		{
			valstr.Empty();
			valstr.Insert(0,valtemp.m_value);
			val=atol(valstr.GetBuffer(valstr.GetLength()));
			valstr.ReleaseBuffer();
		}
		else
		{
			if(m_opgraph[2]==0 && m_opgraph[3]==0 && m_opgraph[4]==0 && m_opgraph[5]==0 && m_opgraph[6]==0)
				val=1000L;
			else 
			{
				val=100L;
			}
		}
	}
	else val=1L;
	bool testop=true;
	for(i=OPNSIM;i<OPDIM;i++)
		if(m_opgraph[i]!=0)
		{
			testop=false;
			break;
		}
	if(m_opgraph[0]==1)
	{
		m_conex=Conexity(false);
		if(m_Type==-1)
		{
			if(m_conex==true) AfxMessageBox("This graph is conex");
			else AfxMessageBox("This graph is not conex");
		}
		else
		{
			AfxMessageBox("This function is not implemented");
		}
	}
	if(m_opgraph[1]==1)
	{
		m_cyclic=Merimont();
		if(m_Type==-2)
		{
			if(m_cyclic==true) AfxMessageBox("This digraph is cyclic");
			else AfxMessageBox("This digraph is not cyclic");
		}
		else
		{
			if(m_cyclic==true) AfxMessageBox("This graph is cyclic");
			else AfxMessageBox("This graph is not cyclic");
		}
	}
	if(testop==true) m_Oper=2; //set for stop
	else m_Oper=0; //set for run
	if(m_opgraph[2]==1)
		init_eulerian();
	if(m_opgraph[3]==1) //min cost tree
		init_min_cost();
	if(m_opgraph[4]==1) //Kruskal
	{
		stop=init_kruskal();
		if(stop==false)
		{
			m_Sincro->Lock();
			m_Oper=2;
			m_Sincro->Unlock();
		}
	}
	if(m_opgraph[5]==1) //Prim
	{
		stop=init_prim();
		if(stop==false)
		{
			m_Sincro->Lock();
			m_Oper=2;
			m_Sincro->Unlock();
		}
	}
	if(m_opgraph[6]==1) //Bellman Kalaba
	{
		stop=init_bk();
		if(stop==false)
		{
			m_Sincro->Lock();
			m_Oper=2;
			m_Sincro->Unlock();
		}
	}
	while(m_Oper!=2)
	{
		if(m_Oper==1) //we want stop
		{
			m_handlepriv=m_StartStop->m_hObject;
			::WaitForSingleObject(m_handlepriv,INFINITE);
			m_StartStop->ResetEvent();
		}
		else
		{
			Sleep(val);
			m_Sincro->Lock();
			m_Oper=*m_oper;
			m_Sincro->Unlock();
			if(m_Oper==0)
			{
				if(m_opgraph[2]==1)
					run_eulerian();
				if(m_opgraph[3]==1)
					run_min_cost();
				if(m_opgraph[4]==1)
				{
					stop=run_kruskal();
					if(stop==false)
					{
						m_Sincro->Lock();
						m_Oper=2;
						m_Sincro->Unlock();
					}
				}
				if(m_opgraph[5]==1)
				{
					stop=run_prim();
					if(stop==false)
					{
						m_Sincro->Lock();
						m_Oper=2;
						m_Sincro->Unlock();
					}
				}
				if(m_opgraph[6]==1)
				{
					stop=run_bk();
					if(stop==false)
					{
						m_Sincro->Lock();
						m_Oper=2;
						m_Sincro->Unlock();
					}
				}
			}
		}
		if(m_Oper!=2)
		{
			m_Sincro->Lock();
			m_Oper=*m_oper;
			m_Sincro->Unlock();
		}
	}
	if(testop==false && m_opgraph[2]!=1) AfxMessageBox("Simulation is finished");
	if(m_opgraph[2]==1 && m_Type==-1)
	{
		free(*m_emat);
		free(m_emat);
	}
	if(m_opgraph[3]==1 && m_Type==-1)
	{
		free(*m_tmat);
		free(m_tmat);
		free(tempm);
	}
	if(m_opgraph[2]==1 || m_file==true) ofile.close();
	return 0;
}

bool CDigraph::Merimont(void)
{
	/*
		This function implements the Merimont algorithm.
		This function finds if a graph or digrap is ciclic.
		This function is called from Run.
	*/
	int i,j,contor,**mat,*temp,inf;
	stack<int> opstack;
	int *gradint,extras;
	gradint=(int *)calloc(m_nrLoc,sizeof(int));
	mat=(int **)calloc(m_nrLoc,sizeof(int *));
	temp=(int *)calloc(m_nrLoc*m_nrLoc,sizeof(int));
	for(i=0;i<m_nrLoc;i++)
	{
		mat[i]=temp;
		temp+=m_nrLoc;
	}
	for(i=0;i<m_nrLoc;i++)
		for(j=0;j<m_nrLoc;j++)
			mat[i][j]=m_mat[i][j];
	if(m_Type==-2)
	{
		inf=0;
		for(i=0;i<m_nrLoc;i++)
			for(j=0;j<m_nrLoc;j++)
				if(mat[i][j]!=0) inf+=mat[i][j];
		for(i=0;i<m_nrLoc;i++)
			for(j=0;j<m_nrLoc;j++)
				if(mat[i][j]==0) mat[i][j]=inf;
		//compute interior degree
		for(i=0;i<m_nrLoc;i++)
		{
			gradint[i]=0;
			for(j=0;j<m_nrLoc;j++)
				if(mat[j][i]!=inf) gradint[i]++;
		}
		contor=m_nrLoc;
		for(i=0;i<m_nrLoc;i++) 
			if(gradint[i]==0)
			{
   				opstack.push(i);
				gradint[i]=-1;
			}
		while(opstack.empty()==false)
		{
			int& temp=opstack.top();
			extras=temp;
			opstack.pop();
			contor--;
			for(i=0;i<m_nrLoc;i++)
				if(mat[extras][i]!=inf)
				{
		  			gradint[i]--;
					if(gradint[i]==0)
					{
        				opstack.push(i);
						gradint[i]=-1;
					}
				}
		}
		free(gradint);
		free(*mat);
		free(mat);
		if(contor!=0) return true;
		else return false;
	}
	else
	{
	   //compute degree
		for(i=0;i<m_nrLoc;i++)
			for(j=0;j<m_nrLoc;j++) if(mat[j][i]==1) gradint[i]++;
		contor=m_nrLoc;
		for(i=0;i<m_nrLoc;i++) 
			if(gradint[i]==1)
			{
				opstack.push(i);
				gradint[i]--;
			}
		while(opstack.empty()==false)
		{
			int& temp=opstack.top();
			extras=temp;
			opstack.pop();
			contor--;
			for(i=0;i<m_nrLoc;i++)
				if(mat[extras][i]==1)
				{
					gradint[i]--;
					if(gradint[i]==1)
					{
						opstack.push(i);
						gradint[i]--;
					}
				}
		}
		free(gradint);
		free(*mat);
		free(mat);
		if(contor!=0) return true;
		else return false;
	}
}

bool CDigraph::Conexity(bool automata)
{
	/*
		This function give an answer about the connexity of a graph or digraph.
		If automata is true this call is made by another function in a specific process.
		Ia automata is false this call is made by the user from Run.
	*/
	bool rezultat;
	int nod,i,j,k;
	if(m_Type==-1)
	{
		int *y,*y1;
		int contor,temp;
		int nr_muchii[2];
		int **mat,*temporar;
		mat=(int **)calloc(m_nrLoc,sizeof(int *));
		temporar=(int *)calloc(m_nrLoc*m_nrLoc,sizeof(int));
		for(i=0;i<m_nrLoc;i++)
		{
   			mat[i]=temporar;
			temporar+=(m_nrLoc);
		}
		for(i=0;i<m_nrLoc;i++) for(j=0;j<m_nrLoc;j++) mat[i][j]=m_mat[i][j];
		y=(int *)calloc(m_nrLoc,sizeof(int));
		y1=(int *)calloc(m_nrLoc,sizeof(int));
		for(i=0;i<m_nrLoc;i++) {y[i]=-1;y1[i]=-1;}
		if(automata==false)
		{
			valtemp.m_info.Empty();
			valtemp.m_info.Insert(0,"Please input the starting node");
			valtemp.DoModal();
			if(valtemp.m_flag==true)
			{
				valstr.Empty();
				valstr.Insert(0,valtemp.m_value);
				nod=atoi(valstr.GetBuffer(valstr.GetLength()));
				valstr.ReleaseBuffer();
			}
			else nod=0;
		}
		else nod=element;
		contor=0;
		nr_muchii[0]=0;
		for(i=0;i<m_nrLoc;i++) for(j=0;j<m_nrLoc;j++) if(mat[i][j]>1) nr_muchii[0]++;
		nr_muchii[1]=nr_muchii[0];
		y[contor]=nod;y1[contor]=nod;
		contor++;
		while(1)
		{
   			temp=contor;
			for(i=0;i<contor;i++)
			{
      			for(j=0;j<m_nrLoc;j++)
					if(mat[y[i]][j]==1)
					{
         				for(k=0;k<temp;k++) if(y[k]==j) break;
						if(k==temp)
						{
            				y[temp]=j;
	  						temp++;
							if(temp>m_nrLoc) { AfxMessageBox("Something is wrong");}
						}
						mat[y[i]][j]=mat[j][y[i]]=0;
					}
			}
			contor=temp;
			for(i=0;i<contor;i++) if(y[i]!=y1[i]) break;
			if(i!=contor) rezultat=false;
			else rezultat=true;
			nr_muchii[0]=0;
			for(i=0;i<m_nrLoc;i++) for(j=0;j<m_nrLoc;j++) if(mat[i][j]>1) nr_muchii[0]++;
			if(nr_muchii[0]==nr_muchii[1] && rezultat==true) break;
			else
			{
      			nr_muchii[1]=nr_muchii[0];
				for(i=0;i<m_nrLoc;i++) y1[i]=y[i];
			}
		}
		nod=0;
		for(i=0;i<m_nrLoc;i++) for(j=0;j<m_nrLoc;j++) if(y[i]==j){ nod++; break;}
		if (nod==nr_ram) rezultat=true; //it is conex
		else rezultat=false; //it is not conex
		//free memory
		free(y);
		free(y1);
		free(*mat);
		free(mat);
		return rezultat;
	}
	else return false;
}

void CDigraph::Eulerian_Cycle(int i)
{
	/*
		This function finds an Eulerian Cycle from a graph or digraph.
		This function is called from Run.
	*/
	int k,j;
	if(m_Type==-1)
	{
		//select an arc
		if(m_emat[element][i]>0)
		{
			int tbridge;
			tbridge=m_emat[element][i];
			m_emat[element][i]=m_emat[i][element]=0;
			if(Conexity(true)==true)
			{
				if(m_file==true)
				{
					ofile<<i<<" ";
					ofile.flush();
				}
				valstr.Empty();
				char temp[10];
				for(j=0;j<10;j++) temp[j]='\0';
				itoa(i,temp,10);
				valstr.Insert(0,temp);
				m_afisaj+=valstr;
				m_afisaj+=' ';
				if(teaching==true)
				{
					m_queues->add(element,i,m_mat[element][i]);
					m_pDoc->RemoveArc(element,i);
				}
				element=i;
			}
			else
			{
				if(flag==true)
				{
					if(m_file==true)
					{
						ofile<<i<<" ";
						ofile.flush();
					}
					valstr.Empty();
					char temp[10];
					for(j=0;j<10;j++) temp[j]='\0';
					itoa(i,temp,10);
					valstr.Insert(0,temp);
					m_afisaj+=valstr;
					m_afisaj+=' ';
					if(teaching==true)
					{
						m_pDoc->RemoveArc(element,i);
						m_queues->add(element,i,m_mat[element][i]);
					}
					element=i;
					nr_ram=m_nrLoc;
					for(j=0;j<m_nrLoc;j++)
					{
						for(k=0;k<m_nrLoc;k++) if(m_emat[j][k]>0) break;
						if(k==m_nrLoc) nr_ram--;
					}
					flag=false;
				}
				else
				{
					//restore the data
					m_emat[element][i]=m_emat[i][element]=tbridge;
				}
			}
		}
	}
}

CDigraph::qelement *CDigraph::createQ(int nr,int **mat)
{
	/*
		This function creates a queue of qelement structure.
		It is called in case of min cost tree.
	*/
	CDigraph::qelement *nod,*lista,*curent,*temp;
	int i,j;
	lista=NULL;
	for(i=0;i<nr;i++)
		for(j=i;j<nr;j++)
		{
			if(mat[i][j]!=0)
			{
      			if(lista==NULL)
				{
         			lista=(struct qelement *)calloc(1,sizeof(struct qelement));
					lista->next=NULL;
					lista->i=i;
					lista->j=j;
					lista->val=mat[i][j];
				}
				else
				{
         			nod=(struct qelement *)calloc(1,sizeof(struct qelement));
					nod->i=i;
					nod->j=j;
					nod->val=mat[i][j];
					curent=lista;
					temp=NULL;
					nod->next=NULL;
					while(curent!=NULL)
					{
						if(nod->val<=curent->val)
						{
               				if(temp==NULL)
							{
	               				nod->next=lista;
   								lista=nod;
								break;
							}
							else
							{
                  				temp->next=nod;
								nod->next=curent;
								break;
							}
						}
						else
						{
							temp=curent;
							curent=curent->next;
						}
					}
					if(curent==NULL) temp->next=nod;
				}
			}
		}
	return lista;
}

CDigraph::qelement *CDigraph::getQ(CDigraph::qelement *coada,int *i,int *j,int *val)
{
	/*
		This function gets an element from a queue of qelement structure.
		It is called in case of min cost tree.
	*/
	CDigraph::qelement *lista;
	*i=coada->i;
	*j=coada->j;
	*val=coada->val;
	lista=coada->next;
	free(coada);
	return lista;
}

void CDigraph::run_eulerian()
{
	//this is the function from the loop
	int i,j,val;
	Eulerian_Cycle(stepe);
	stepe++;
	if(stepe==m_nrLoc)
	{
		if(old==element) flag=true;
		else flag=false;
		grad=0;
		if(m_Type==-1)
			for(j=0;j<m_nrLoc;j++) if(m_emat[element][j]>0) grad++;
		stepe=0;
		old=element;
		if(grad==0)
		{
			m_Oper=2;
			AfxMessageBox(m_afisaj);
			for(i=0;i<m_nrLoc;i++)
				for(j=0;j<m_nrLoc;j++)
					if(m_emat[i][j]!=0) m_pDoc->RemoveArc(i,j);
			while(m_queues->empty()!=true)
			{
				m_queues->get(&i,&j,&val);
				m_pDoc->AddArc(i,j,val);
			}
			m_StartStop->ResetEvent();
		}
	}
}

void CDigraph::init_eulerian()
{
	//this is the initialization function
	int i,j;
	char temp[10];
	if(m_Type==-1)
	{
		m_emat=(int **)calloc(m_nrLoc,sizeof(int *));
		tempm=(int *)calloc(m_nrLoc*m_nrLoc,sizeof(int));
		for(j=0;j<m_nrLoc;j++)
		{
			m_emat[j]=tempm;
			tempm+=m_nrLoc;
		}
		for(i=0;i<m_nrLoc;i++) for(j=0;j<m_nrLoc;j++) m_emat[i][j]=m_mat[i][j];
		for(j=0;j<m_nrLoc;j++)
		{
			grad=0;
			for(i=0;i<m_nrLoc;i++) if(m_mat[j][i]>0) grad++;
			if(grad%2==1)
			{
				AfxMessageBox("This graph hasn't an eulerian cycle");
				m_Oper=2;
				break;
			}
		}
		valtemp.m_info.Empty();
		valtemp.m_value.Empty();
		valtemp.m_info.Insert(0,"Input the name of eulerian cycle file");
		valtemp.DoModal();
		if(valtemp.m_flag==true)
		{
			ofile.open(valtemp.m_value);
			m_file=true;
		}
		else m_file=false;
		element=0;
		m_afisaj.Insert(0,"The eulerian cycle is: ");
		valstr.Empty();
		for(i=0;i<10;i++) temp[i]='\0';
		itoa(element,temp,10);
		valstr.Insert(0,temp);
		m_afisaj+=valstr;
		m_afisaj+=' ';
		if(m_file==true)
		{
			ofile<<element<<" ";
			ofile.flush();
		}
		grad=0;
		for(i=0;i<m_nrLoc;i++) if(m_emat[0][i]>0) grad++;
		flag=false;
		nr_ram=m_nrLoc;
		if(grad==0) m_Oper=2;
		else m_Oper=0;
		stepe=0;
		old=element;
		m_queues=new CQueue();
	}
	else
	{
		AfxMessageBox("This function is not yet implemented");
		m_Oper=2;
	}
}

void CDigraph::run_min_cost()
{
	int i,j;
	char temp[10];
	if(queue!=NULL)
	{
		queue=getQ(queue,&i,&j,&m_tval);
		if(tempm[i]==tempm[j])
		{
			m_tmat[i][j]=m_tmat[j][i]=0;
			if(teaching==true) m_pDoc->RemoveArc(j,i);
		}
		else
		{
			m_cost+=m_tval;
			m_tval=tempm[j];
			tempm[j]=tempm[i];
			for(j=0;j<m_nrLoc;j++) if(tempm[j]==m_tval) tempm[j]=tempm[i];
		}
	}
	else
	{
		m_Oper=2;
		m_afisaj.Insert(0,"The cost is: ");
		valstr.Empty();
		for(i=0;i<10;i++) temp[i]='\0';
		itoa(m_cost,temp,10);
		valstr.Insert(0,temp);
		m_afisaj+=valstr;
		m_afisaj+=' ';
		if(m_file==true)
		{
			ofile<<"The matrix for minimum cost is:\n";
			for(i=0;i<m_nrLoc;i++)
			{
				for(j=0;j<m_nrLoc;j++)
					ofile<<m_tmat[i][j]<<" ";
				ofile<<endl;
			}
			ofile<<"The cost is: "<<m_cost;
			ofile.flush();
			ofile.close();
		}
		AfxMessageBox(m_afisaj);
		m_StartStop->ResetEvent();
	}
}

void CDigraph::init_min_cost()
{
	int i,j;
	if(m_Type==-1)
	{
		m_tmat=(int **)calloc(m_nrLoc,sizeof(int *));
		tempm=(int *)calloc(m_nrLoc*m_nrLoc,sizeof(int));
		for(i=0;i<m_nrLoc;i++)
		{
			m_tmat[i]=tempm;
			tempm+=m_nrLoc;
		}
		for(i=0;i<m_nrLoc;i++)
			for(j=0;j<m_nrLoc;j++) m_tmat[i][j]=m_mat[i][j];
		valtemp.m_info.Empty();
		valtemp.m_value.Empty();
		valtemp.m_info.Insert(0,"Input the name of minimun cost tree file");
		valtemp.DoModal();
		if(valtemp.m_flag==true)
		{
			ofile.open(valtemp.m_value);
			m_file=true;
		}
		else m_file=false;
		tempm=(int *)calloc(m_nrLoc,sizeof(int));
		for(i=0;i<m_nrLoc;i++) tempm[i]=i;
		queue=createQ(m_nrLoc,m_tmat);
		m_cost=0;
	}
	else
	{
		AfxMessageBox("This function is not yet implemented");
		m_Oper=2;
	}
}

bool CDigraph::init_kruskal()
{
	m_queues=new CQueue[2];
	if(m_Type==-1)
		m_queues[0].create(m_nrLoc,m_mat,false);
	else
	{
		AfxMessageBox("For digraf Kruskal is not defined yet !");
		return false;
	}
	m_L=(int *)calloc(m_nrLoc,sizeof(int));
	for(int i=0;i<m_nrLoc;i++)
		m_L[i]=i;
	return true;
}

bool CDigraph::run_kruskal()
{
	int i,j,k,val;
	if(m_Type==-1)
	{
		if(m_queues[0].empty()==false)
		{
			m_queues[0].get(&i,&j,&val);
			if(m_L[i]!=m_L[j])
			{
				m_queues[1].add(i,j,val);
				for(k=0;k<m_nrLoc;k++)
					if(k!=i)
						if(m_L[k]==m_L[i])
							m_L[k]=m_L[j];
				m_L[i]=m_L[j];
			}
			else
				if(teaching==true) m_pDoc->RemoveArc(i,j);
			return true;
		}
		else
		{
			CString message;
			m_cost=0;
			while(m_queues[1].empty()==false)
			{
				m_queues[1].get(&i,&j,&val);
				m_cost+=val;
			}
			message.Format("The cost is : %d",m_cost);
			AfxMessageBox(message);
			free(m_L);
			m_L=NULL;
			delete[] m_queues;
			return false;
		}
	}
	return false;
}

bool CDigraph::init_prim()
{
	if(m_Type!=-1)
	{
		AfxMessageBox("Prim is only defined for graphs !");
		return false;
	}
	m_L=(int *)calloc(m_nrLoc,sizeof(int));//X-A
	for(int i=0;i<m_nrLoc;i++)
		m_L[i]=1;
	m_L[0]=-1;
	m_queues=new CQueue[2];
	m_queues[1].create(m_nrLoc,m_mat,false);
	return true;
}

bool CDigraph::run_prim()
{
	int i,j,val;
	if(m_Type==-1)
	{
		CQueue qu;
		if(m_queues[1].empty()==false)
		{
			while(m_queues[1].empty()==false)
			{
				m_queues[1].get(&i,&j,&val);
				if(m_L[i]==-1 && m_L[j]==-1)
				{
					if(teaching==true) m_pDoc->RemoveArc(i,j);
				}
				else
				{
					if(m_L[i]!=-1 && m_L[j]!=-1)
						qu.add(i,j,val);
					else
					{
						m_queues[0].add(i,j,val);
						m_L[i]=-1;
						m_L[j]=-1;
						//redone the initial queue
						while(qu.empty()==false)
						{
							qu.get(&i,&j,&val);
							m_queues[1].add(i,j,val);
						}
						return true;
					}
				}
			}
		}
		else
		{
			CString message;
			m_cost=0;
			while(m_queues[0].empty()==false)
			{
				m_queues[0].get(&i,&j,&val);
				m_cost+=val;
			}
			message.Format("The cost is : %d",m_cost);
			AfxMessageBox(message);
			free(m_L);
			m_L=NULL;
			delete[] m_queues;
			return false;
		}
		return false;
	}
	else return false;
}

bool CDigraph::init_bk()
{
	//find the inifinite
	long i,j;
	int maxl,maxc,temp;
	CMinMax minmax(m_nrLoc);
	minmax.DoModal();
	minmax.get(m_start,m_end,m_minmax);
	maxl=0;
	for(j=0;j<m_nrLoc;j++)
		maxl+=abs(m_mat[0][j]);
	for(i=1;i<m_nrLoc;i++)
	{
		temp=0;
		for(j=0;j<m_nrLoc;j++)
			temp+=abs(m_mat[i][j]);
		if(temp>maxl) maxl=temp;
	}
	maxc=0;
	for(j=0;j<m_nrLoc;j++)
		maxc+=abs(m_mat[j][0]);
	for(i=1;i<m_nrLoc;i++)
	{
		temp=0;
		for(j=0;j<m_nrLoc;j++)
			temp+=abs(m_mat[j][i]);
		if(temp>maxc) maxc=temp;
	}
	if(maxc<maxl) m_infinite=maxl;
	else m_infinite=maxc;
	m_tmat=(int **)calloc(m_nrLoc,sizeof(int *));
	tempm=(int *)calloc(m_nrLoc*m_nrLoc,sizeof(int));
	for(i=0;i<m_nrLoc;i++)
	{
		m_tmat[i]=tempm;
		tempm+=m_nrLoc;
	}
	m_L=(int *)calloc(m_nrLoc,sizeof(int));
	m_L1=(int *)calloc(m_nrLoc,sizeof(int));
	for(i=0;i<m_nrLoc;i++)
		for(j=0;j<m_nrLoc;j++)
			if(m_mat[i][j]==0)
			{
				if(i==j) m_tmat[i][j]=0;
				else
				{
					if(m_minmax==true)
						m_tmat[i][j]=m_infinite;
					else m_tmat[i][j]=-m_infinite;
				}
			}
			else m_tmat[i][j]=m_mat[i][j];
	for(i=0;i<m_nrLoc;i++)
		m_L[i]=m_tmat[m_nrLoc-1][i];
	//find the 2 identical lines
	bool stop;
	int *tempL;
	stop=false;
	while(stop==false)
	{
		for(i=0;i<m_nrLoc;i++)
		{
			if(m_L[0]!=m_infinite && m_tmat[i][0]!=m_infinite)
				temp=m_L[0]+m_tmat[i][0];
			else temp=m_infinite;
			for(j=1;j<m_nrLoc;j++)
			{
				if(m_L[j]!=m_infinite && m_tmat[i][j]!=m_infinite)
					maxc=m_L[j]+m_tmat[i][j];
				else maxc=m_infinite;
				if(m_minmax==true && maxc<temp) //min
					temp=maxc;
				else if(m_minmax==false && maxc>temp) //max
					temp=maxc;
			}
			m_L1[i]=temp;
		}
		stop=true;
		for(i=0;i<m_nrLoc;i++)
			if(m_L1[i]!=m_L[i]) stop=false;
		if(stop==false)
		{
			//change the vectors
			tempL=m_L1;
			m_L1=m_L;
			m_L=tempL;
		}
	}
	//erase all arcs
	if(teaching==true)
	{
		for(i=0;i<m_nrLoc;i++)
			for(j=0;j<m_nrLoc;j++)
				m_pDoc->RemoveArc(i,j);
	}
	m_i=m_start;
	m_result.Empty();
	return true;
}

bool CDigraph::run_bk()
{
	int i;
	for(i=0;i<m_nrLoc;i++)
	{
		if(m_L[i]!=m_infinite && m_tmat[m_i][i]!=m_infinite)
			m_L1[i]=m_L[i]+m_tmat[m_i][i];
		else m_L1[i]=m_infinite;
	}
	for(i=0;i<m_nrLoc;i++)
	{
		if(i!=m_i && m_L1[i]==m_L1[m_i])
		{
			m_j=i;
			break;
		}
	}
	if(teaching==true)
		m_pDoc->AddArc(m_i,m_j,m_mat[m_i][m_j]);
	CString temp;
	if(m_i==m_start)
		temp.Format("%d%d",m_i,m_j);
	else temp.Format(";%d%d",m_i,m_j);
	m_i=m_j;
	m_result.Insert(m_result.GetLength(),temp);
	if(m_j==m_end)
	{
		AfxMessageBox(m_result,IDOK);
		free(*m_tmat);
		free(m_tmat);
		m_tmat=NULL;
		free(m_L);
		m_L=NULL;
		free(m_L1);
		m_L1=NULL;
		return false;
	}
	else return true;
}
