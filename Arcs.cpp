// Arcs.cpp: implementation of the CArcs class.
//
//////////////////////////////////////////////////////////////////////
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
#include "Arcs.h"
#include "Value1.h"
#include<stdio.h>
#include<math.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
IMPLEMENT_SERIAL(CArcs,CObject,1)
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CArcs::CArcs()
{
	/*
		Default constructor for the class CArcs.
		It is used only for serialization.
	*/
	dimsgn=3.0;
	dim=20.0;
	m_points.clear();
	m_EndLoc=NULL;
	m_EndTran=NULL;
	m_StartLoc=NULL;
	m_StartTran=NULL;
}

CArcs::CArcs(CPoint point,CDC *pdc,int type,float dim1,float dim2)
{
	/*
		This is the constructor for the class CArcs.
		This function put the starting point of arc.
	*/
	dimsgn=dim1;
	dim=dim2;
	m_points.clear();
	m_points.insert(m_points.end(),point);
	m_EndLoc=NULL;
	m_EndTran=NULL;
	m_StartLoc=NULL;
	m_StartTran=NULL;
	m_Type=type;
}

CArcs::~CArcs()
{
	/*
		This is the default destructor for the class CArcs.
	*/
	m_points.clear();
}

void CArcs::AddPoint(CPoint point,CDC *pdc)
{
	/*
		This function adds a point to the arc.
		This function is used in manual input of the network or graph.
	*/
	m_points.insert(m_points.end(),point);
}

void CArcs::Draw(CDC *pdc)
{
	/*
		This function draws the arc.
	*/
	pdc->MoveTo(*m_points.begin());
	for(m_pit=m_points.begin();m_pit!=m_points.end();++m_pit)
		pdc->LineTo(*m_pit);
	if(m_EndLoc!=NULL || m_EndTran!=NULL)
	{
		m_pit=m_points.end();
		m_pit--;
		if(m_Type!=-1) pdc->Ellipse((*m_pit).x-dimsgn,(*m_pit).y-dimsgn,(*m_pit).x+dimsgn,(*m_pit).y+dimsgn);
	}
	pdc->TextOut(m_text.x,m_text.y,valstr);
}

void CArcs::AddStart(CLocation *ploc)
{
	/*	
		This function adds the start location to the arc. 
		This function is use in manual creation of the network
	*/
	m_StartLoc=ploc;
	m_StartTran=NULL;
}

void CArcs::AddStart(CTransition *ptran)
{
	/*	
		This function adds the start transition to the arc. 
		This function is use in manual creation of the network
	*/
	m_StartTran=ptran;
	m_StartLoc=NULL;
}

void CArcs::AddLocTrn(CLocation *ploc,CTransition *ptran)
{
	/*	
		This function adds the start location and the end transition to the arc. 
		This function is use in atomatic creation of the network
	*/
	m_StartLoc=ploc;
	m_StartTran=NULL;
	m_EndLoc=NULL;
	m_EndTran=ptran;
}

void CArcs::AddTrnLoc(CTransition *ptran,CLocation *ploc)
{
	/*	
		This function adds the start transition and the end location to the arc. 
		This function is use in atomatic creation of the network
	*/
	m_StartLoc=NULL;
	m_StartTran=ptran;
	m_EndLoc=ploc;
	m_EndTran=NULL;
}
void CArcs::AddLocLoc(CLocation *ploc1,CLocation *ploc2)
{
	/*	
		This function adds the start and the end location to the arc. 
		This function is use in atomatic creation of the graph
	*/
	m_StartLoc=ploc1;
	m_StartTran=NULL;
	m_EndLoc=ploc2;
	m_EndTran=NULL;
}
void CArcs::AddEnd(CLocation *ploc,bool flag,int vals)
{
	/*	
		This function adds the End of the arc if this End instance is a location.
		flag=true if we have manual
		flag=false if we have auto
	*/
	m_EndLoc=ploc;
	m_EndTran=NULL;
	//compute the pozition of label
	int x,y;
	if(m_points.size()==2)
	{
		CPoint temp;
		temp=*(++m_points.begin());
		if(m_points.begin()->x<temp.x) x=m_points.begin()->x;
		else x=temp.x;
		if(m_points.begin()->y<temp.y) y=m_points.begin()->y;
		else y=temp.y;
		m_text.x=x+abs(m_points.begin()->x-temp.x)/2;
		m_text.y=y+abs(m_points.begin()->y-temp.y)/2;
	}
	else
	{
		CPoint ptmp1,ptmp2;
		m_pit=m_points.begin();
		for(int i=0;i<(m_points.size()-1)/2;i++) m_pit++;
		ptmp1=*m_pit;
		ptmp2=*(++m_pit);
		if(ptmp1.x<ptmp2.x) x=ptmp1.x;
		else x=ptmp2.x;
		if(ptmp1.y<ptmp2.y) y=ptmp1.y;
		else y=ptmp2.y;
		m_text.x=x+abs(ptmp1.x-ptmp2.x)/2;
		m_text.y=y+abs(ptmp1.y-ptmp2.y)/2;
	}
	//get the value of arc
	if(flag==true)
	{
		CValue1 valtemp;
		valtemp.m_info.Empty();
		valtemp.m_info.Insert(0,"Value of Arc");
		valtemp.DoModal();
		if(valtemp.m_flag==true)
		{
			valstr.Empty();
			valstr.Insert(0,valtemp.m_value);
			val=atoi(valstr.GetBuffer(valstr.GetLength()));
			valstr.ReleaseBuffer();
		}
		else
		{
			val=1;
			valstr.Empty();
			valstr.Insert(0,"1");
		}
	}
	else
	{
		val=vals;
		valstr.Empty();
		char temp[10];
		for(int i=0;i<10;i++) temp[i]='\0';
		_itoa(val,temp,10);
		valstr.Insert(0,temp);
	}
}

void CArcs::AddEnd(CTransition *ptran,bool flag,int vals)
{
	/*	
		This function adds the End of the arc if this End instance is a transition.
		flag=true if we have manual
		flag=false if we have auto
	*/
	m_EndTran=ptran;
	m_EndLoc=NULL;
	int x,y;
	if(m_points.size()==2)
	{
		CPoint temp;
		temp=*(++m_points.begin());
		if(m_points.begin()->x<temp.x) x=m_points.begin()->x;
		else x=temp.x;
		if(m_points.begin()->y<temp.y) y=m_points.begin()->y;
		else y=temp.y;
		m_text.x=x+abs(m_points.begin()->x-temp.x)/2;
		m_text.y=y+abs(m_points.begin()->y-temp.y)/2;
	}
	else
	{
		CPoint ptmp1,ptmp2;
		m_pit=m_points.begin();
		for(int i=0;i<(m_points.size()-1)/2;i++) m_pit++;
		ptmp1=*m_pit;
		ptmp2=*(++m_pit);
		if(ptmp1.x<ptmp2.x) x=ptmp1.x;
		else x=ptmp2.x;
		if(ptmp1.y<ptmp2.y) y=ptmp1.y;
		else y=ptmp2.y;
		m_text.x=x+abs(ptmp1.x-ptmp2.x)/2;
		m_text.y=y+abs(ptmp1.y-ptmp2.y)/2;
	}
	//get value of the arc
	if(flag==true)
	{
		CValue1 valtemp;
		valtemp.m_info.Empty();
		valtemp.m_info.Insert(0,"Value of Arc");
		valtemp.DoModal();
		if(valtemp.m_flag==true)
		{
			valstr.Empty();
			valstr.Insert(0,valtemp.m_value);
			val=atoi(valstr.GetBuffer(valstr.GetLength()));
			valstr.ReleaseBuffer();
		}
		else
		{
			val=1;
			valstr.Empty();
			valstr.Insert(0,"1");
		}
	}
	else
	{
		val=vals;
		valstr.Empty();
		char temp[10];
		for(int i=0;i<10;i++) temp[i]='\0';
		_itoa(val,temp,10);
		valstr.Insert(0,temp);
	}

}

void CArcs::ConnectS()
{
	/*
		This function creates the connection for the arc to the start instance.
	*/
	int xcs,ycs;
	int xc,yc;
	//if starting point is a location
	m_pit=m_points.begin();
	if(m_StartLoc!=NULL)
	{
		xcs=m_StartLoc->m_center.x;
		ycs=m_StartLoc->m_center.y;
		ComputePos(xcs,ycs,(*m_pit).x,(*m_pit).y,&xc,&yc,true);
	}
	else
	{
		xcs=m_StartTran->m_center.x;
		ycs=m_StartTran->m_center.y;
		ComputePos(xcs,ycs,(*m_pit).x,(*m_pit).y,&xc,&yc,false);
	}
	(*m_points.begin()).x=xc;
	(*m_points.begin()).y=yc;
	xps=xc-xcs;
	yps=yc-ycs;
}

void CArcs::ConnectE()
{
	/*
		This function creates the connection for the arc to the end instance.
	*/
	m_pit=m_points.end();
	m_pit--;
	int xcs,ycs;
	int xc,yc;
	//if starting point is a location
	if(m_EndLoc!=NULL)
	{
		xcs=m_EndLoc->m_center.x;
		ycs=m_EndLoc->m_center.y;
		ComputePos(xcs,ycs,(*m_pit).x,(*m_pit).y,&xc,&yc,true);
	}
	else
	{
		xcs=m_EndTran->m_center.x;
		ycs=m_EndTran->m_center.y;
		ComputePos(xcs,ycs,(*m_pit).x,(*m_pit).y,&xc,&yc,false);
	}
	xps=xc-xcs;
	yps=yc-ycs;
	(*m_pit).x=xc;
	(*m_pit).y=yc;
}


void CArcs::ComputePos(int x1, int y1, int x2, int y2, int *xc, int *yc,bool flag)
{
	/*
		This function computes the position of the link point in instance.
		This funtion is called by ConnectE and ConnectS.
		If flag is true we have location else we have transition.
	*/
	int x[8],y[8];
	x[0]=x1;y[0]=y1-dim;
	x[2]=x1+dim; y[2]=y1;
	x[4]=x1; y[4]=y1+dim;
	x[6]=x1-dim; y[6]=y1;
	if(flag==true)
	{
		x[1]=x1+dim*0.707; y[1]=y1-dim*0.707;
		x[3]=x1+dim*0.707; y[3]=y1+dim*0.707;	
		x[5]=x1-dim*0.707; y[5]=y1+dim*0.707;
		x[7]=x1-dim*0.707; y[7]=y1-dim*0.707;
	}
	else
	{
		x[1]=x1+dim; y[1]=y1-dim;
		x[3]=x1+dim; y[3]=y1+dim;	
		x[5]=x1-dim; y[5]=y1+dim;
		x[7]=x1-dim; y[7]=y1-dim;
	}
	//make connection to ending point
	int min=0;
	double valmin,valmint;
	valmin=(x[0]-x2)*(x[0]-x2)+(y[0]-y2)*(y[0]-y2);
	for(int i=1;i<8;i++)
	{
		valmint=(x[i]-x2)*(x[i]-x2)+(y[i]-y2)*(y[i]-y2);
		if(valmin>valmint)
		{
			valmin=valmint;
			min=i;
		}
	}
	*xc=x[min];
	*yc=y[min];
}

void CArcs::MoveArc(CPoint point,int flag,CDC *pdc)
{
	/*
		This function moves the arc.
		This function is called in case of instance movement.
		If flag is 0 is an output arc.
		If flag is 1 is an input arc.
	*/
	//erase the old arc
	CPen lpen(PS_SOLID,1,RGB(255,255,255));
	CPen *pOldPen=pdc->SelectObject(&lpen);
	pdc->MoveTo(*m_points.begin());
	for(m_pit=m_points.begin();m_pit!=m_points.end();++m_pit)
		pdc->LineTo(*m_pit);
	m_pit=m_points.end();
	m_pit--;
	if(m_Type!=-1) pdc->Ellipse((*m_pit).x-dimsgn,(*m_pit).y-dimsgn,(*m_pit).x+dimsgn,(*m_pit).y+dimsgn);
	COLORREF oldcolor=pdc->SetTextColor(RGB(255,255,255));
	pdc->TextOut(m_text.x,m_text.y,valstr);
	pdc->SetTextColor(oldcolor);
	pdc->SelectObject(pOldPen);
	//set the new points
	if(m_points.size()==2)
	{
		int xcs,ycs;
		int xce,yce;
		int xs[8],ys[8];
		int xe[8],ye[8];
		//if ending point is a location
		if(m_EndLoc!=NULL)
		{
			xce=m_EndLoc->m_center.x;
			yce=m_EndLoc->m_center.y;
			xe[1]=xce+dim*0.707; ye[1]=yce-dim*0.707;
			xe[3]=xce+dim*0.707; ye[3]=yce+dim*0.707;
			xe[5]=xce-dim*0.707; ye[5]=yce+dim*0.707;		
			xe[7]=xce-dim*0.707; ye[7]=yce-dim*0.707;
		}
		else
		{
			xce=m_EndTran->m_center.x;
			yce=m_EndTran->m_center.y;
			xe[1]=xce+dim; ye[1]=yce-dim;
			xe[3]=xce+dim; ye[3]=yce+dim;
			xe[5]=xce-dim; ye[5]=yce+dim;		
			xe[7]=xce-dim; ye[7]=yce-dim;
		}
		//if starting point is a location
		if(m_StartLoc!=NULL)
		{
			xcs=m_StartLoc->m_center.x;
			ycs=m_StartLoc->m_center.y;
			xs[1]=xcs+dim*0.707; ys[1]=ycs-dim*0.707;		
			xs[3]=xcs+dim*0.707; ys[3]=ycs+dim*0.707;		
			xs[5]=xcs-dim*0.707; ys[5]=ycs+dim*0.707;
			xs[7]=xcs-dim*0.707; ys[7]=ycs-dim*0.707;
		}
		else
		{
			xcs=m_StartTran->m_center.x;
			ycs=m_StartTran->m_center.y;
			xs[1]=xcs+dim; ys[1]=ycs-dim;		
			xs[3]=xcs+dim; ys[3]=ycs+dim;		
			xs[5]=xcs-dim; ys[5]=ycs+dim;
			xs[7]=xcs-dim; ys[7]=ycs-dim;
		}
		xe[0]=xce;ye[0]=yce-dim;
		xe[2]=xce+dim; ye[2]=yce;
		xe[4]=xce; ye[4]=yce+dim;
		xe[6]=xce-dim; ye[6]=yce;
		xs[0]=xcs;ys[0]=ycs-dim;
		xs[2]=xcs+dim; ys[2]=ycs;
		xs[4]=xcs; ys[4]=ycs+dim;
		xs[6]=xcs-dim; ys[6]=ycs;
		int i,j;
		//make connection of starting and ending point
		int min[8];
		double valmin[8],valmint;
		for(j=0;j<8;j++)
		{
			valmin[j]=(xe[j]-xs[0])*(xe[j]-xs[0])+(ye[j]-ys[0])*(ye[j]-ys[0]);
			min[j]=0;
			for(i=1;i<8;i++)
			{
				valmint=(xe[j]-xs[i])*(xe[j]-xs[i])+(ye[j]-ys[i])*(ye[j]-ys[i]);
				if(valmin[j]>valmint)
				{
					valmin[j]=valmint;
					min[j]=i;
				}
			}
		}
		int mint=0;
		valmint=valmin[0];
		for(i=1;i<8;i++)
		{
			if(valmint>valmin[i])
			{
				valmint=valmin[i];
				mint=i;
			}
		}
		m_pit=m_points.end();
		m_pit--;
		(*m_pit).x=xe[mint];;
		(*m_pit).y=ye[mint];
		(*m_points.begin()).x=xs[min[mint]];
		(*m_points.begin()).y=ys[min[mint]];
	}
	else if(m_points.size()==4)
	{
		int xcs,ycs;
		int xce,yce;
		int xc,yc;
		m_pit=m_points.begin();
		m_pit++;
		//if starting point is a location
		if(m_StartLoc!=NULL)
		{
			xcs=m_StartLoc->m_center.x;
			ycs=m_StartLoc->m_center.y;
			ComputePos(xcs,ycs,(*m_pit).x,(*m_pit).y,&xc,&yc,true);
		}
		else
		{
			xcs=m_StartTran->m_center.x;
			ycs=m_StartTran->m_center.y;
			ComputePos(xcs,ycs,(*m_pit).x,(*m_pit).y,&xc,&yc,false);
		}
		(*m_points.begin()).x=xc;
		(*m_points.begin()).y=yc;
		m_pit++;
		//if ending point is a location
		if(m_EndLoc!=NULL)
		{
			xce=m_EndLoc->m_center.x;
			yce=m_EndLoc->m_center.y;
			ComputePos(xce,yce,(*m_pit).x,(*m_pit).y,&xc,&yc,true);
		}
		else
		{
			xce=m_EndTran->m_center.x;
			yce=m_EndTran->m_center.y;
			ComputePos(xce,yce,(*m_pit).x,(*m_pit).y,&xc,&yc,false);
		}
		m_pit=m_points.end();
		m_pit--;		
		(*m_pit).x=xc;
		(*m_pit).y=yc;
	}
	else
	{
		if(flag==0)//output arc
		{
			(*m_points.begin()).x=point.x+xps;
			(*m_points.begin()).y=point.y+yps;
		}
		else//input arc
		{
			m_pit=m_points.end();
			m_pit--;
			(*m_pit).x=point.x+xpe;
			(*m_pit).y=point.y+ype;

		}
	}
	//update the new value for label
	int x,y;
	if(m_points.size()==2)
	{
		CPoint temp;
		temp=*(++m_points.begin());
		if(m_points.begin()->x<temp.x) x=m_points.begin()->x;
		else x=temp.x;
		if(m_points.begin()->y<temp.y) y=m_points.begin()->y;
		else y=temp.y;
		m_text.x=x+abs(m_points.begin()->x-temp.x)/2;
		m_text.y=y+abs(m_points.begin()->y-temp.y)/2;
	}
	//draw new arc
	pdc->MoveTo(*m_points.begin());
	for(m_pit=m_points.begin();m_pit!=m_points.end();++m_pit)
		pdc->LineTo(*m_pit);
	m_pit=m_points.end();
	m_pit--;
	if(m_Type!=-1) pdc->Ellipse((*m_pit).x-dimsgn,(*m_pit).y-dimsgn,(*m_pit).x+dimsgn,(*m_pit).y+dimsgn);
	pdc->TextOut(m_text.x,m_text.y,valstr);
}

void CArcs::MoveArc(CPoint point, CDC *pdc)
{	
	/*
		This function moves the arc.
		This function is called is case of pan.
	*/
	//erase the old arc
	CPen lpen(PS_SOLID,1,RGB(255,255,255));
	CPen *pOldPen=pdc->SelectObject(&lpen);
	pdc->MoveTo(*m_points.begin());
	for(m_pit=m_points.begin();m_pit!=m_points.end();++m_pit)
		pdc->LineTo(*m_pit);
	m_pit=m_points.end();
	m_pit--;
	if(m_Type!=-1) pdc->Ellipse((*m_pit).x-dimsgn,(*m_pit).y-dimsgn,(*m_pit).x+dimsgn,(*m_pit).y+dimsgn);
	COLORREF oldcolor=pdc->SetTextColor(RGB(255,255,255));
	pdc->TextOut(m_text.x,m_text.y,valstr);
	pdc->SetTextColor(oldcolor);
	pdc->SelectObject(pOldPen);
	//set the new values
	for(m_pit=m_points.begin();m_pit!=m_points.end();++m_pit)
		(*m_pit)+=point;
	m_text.x+=point.x;
	m_text.y+=point.y;
	//draw new arc
	pdc->MoveTo(*m_points.begin());
	for(m_pit=m_points.begin();m_pit!=m_points.end();++m_pit)
		pdc->LineTo(*m_pit);
	m_pit=m_points.end();
	m_pit--;
	if(m_Type!=-1) pdc->Ellipse((*m_pit).x-dimsgn,(*m_pit).y-dimsgn,(*m_pit).x+dimsgn,(*m_pit).y+dimsgn);
	pdc->TextOut(m_text.x,m_text.y,valstr);
}

void CArcs::DeleteArc(CDC *pdc,int flag)
{
	/*
		This function deletes the arc.
		This function is used in manual delete when it is called by DeleteArc.
		This function is used also in automatic delete.
		If flag is 0 the request comes from the start of the arc.
		If flag is 1 the request comes from the end of the arc.
		If flag is 2 the request comes from the main document.
	*/
	CPen lpen(PS_SOLID,1,RGB(255,255,255));
	CPen *pOldPen=pdc->SelectObject(&lpen);
	CPoint point;
	pdc->MoveTo(*m_points.begin());
	for(m_pit=m_points.begin();m_pit!=m_points.end();++m_pit)
		pdc->LineTo(*m_pit);
	m_pit=m_points.end();
	m_pit--;
	if(m_Type!=-1) pdc->Ellipse((*m_pit).x-dimsgn,(*m_pit).y-dimsgn,(*m_pit).x+dimsgn,(*m_pit).y+dimsgn);
	COLORREF oldcolor=pdc->SetTextColor(RGB(255,255,255));
	pdc->TextOut(m_text.x,m_text.y,valstr);
	pdc->SelectObject(pOldPen);
	pdc->SetTextColor(oldcolor);
	if(flag==0) //this requst come from the start of the line
	{
		//notify the end of the line
		if(m_EndLoc!=NULL) m_EndLoc->DeleteArc(pos);
		else if(m_EndTran!=NULL) m_EndTran->DeleteArc(pos);
	}
	else if(flag==1) //this request come from the end of the line
	{
		//notify the start of the line
		if(m_StartLoc!=NULL) m_StartLoc->DeleteArc(pos);
		else if(m_StartTran!=NULL) m_StartTran->DeleteArc(pos);
	}
	else if(flag==2) //this request come from main document
	{
		//notify the start of the line
		if(m_StartLoc!=NULL) m_StartLoc->DeleteArc(pos);
		else if(m_StartTran!=NULL) m_StartTran->DeleteArc(pos);
		//notify the end of the line
		if(m_EndLoc!=NULL) m_EndLoc->DeleteArc(pos);
		else if(m_EndTran!=NULL) m_EndTran->DeleteArc(pos);
	}
	m_EndTran=NULL;
	m_EndLoc=NULL;
	m_StartLoc=NULL;
	m_StartTran=NULL;
	m_points.clear();
}


int CArcs::GetEnd()
{
	/*
		This function gives to the caller a pointer the end instance.
	*/
	if(m_EndLoc!=NULL) return m_EndLoc->position;
	else return m_EndTran->position;
}

bool CArcs::DeleteArc(CPoint point, CDC *pdc)
{
	/*
		This function deletes the arc.
		This function is used in manual delete or when we what to delete
		an arc at a given position.
	*/
	int x1,x2,y1,y2,x,y;
	double dist1,dist2,dist3;
	x=point.x;
	y=point.y;
	int i,nr_arcs;
	nr_arcs=m_points.size();
	if(nr_arcs==2)
	{
		x1=m_points.begin()->x;
		y1=m_points.begin()->y;
		m_pit=m_points.end();
		m_pit--;
		x2=(*m_pit).x;
		y2=(*m_pit).y;
		dist1=sqrt((double)abs((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)));
		dist2=sqrt((double)abs((x-x2)*(x-x2)+(y-y2)*(y-y2)));
		dist3=sqrt((double)abs((x-x1)*(x-x1)+(y-y1)*(y-y1)));
		if(x!=x1 && x2!=x1)
		{
			if(fabs((double)(y-y1)/(double)(x-x1)-(double)(y2-y1)/(double)(x2-x1))<0.5 && fabs((double)dist1-(double)(dist2+dist3))<2)
			{
				DeleteArc(pdc,2);
				return true;
			}
		}
		else if(x==x1) 
		if(fabs(dist1-(dist2+dist3))<2)
		{
			DeleteArc(pdc,2);
			return true;
		}
	}
	else if(nr_arcs==4)
	{
		m_pit=m_points.begin();
		for(i=0;i<3;i++)
		{
			x1=(*m_pit).x;
			y1=(*m_pit).y;
			m_pit++;
			x2=(*m_pit).x;
			y2=(*m_pit).y;
			dist1=sqrt((double)((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)));
			dist2=sqrt((double)((x-x2)*(x-x2)+(y-y2)*(y-y2)));
			dist3=sqrt((double)((x-x1)*(x-x1)+(y-y1)*(y-y1)));
			if(fabs((double)(y-y1)/(double)(x-x1)-(double)(y2-y1)/(double)(x2-x1))<0.5 && fabs(dist1-(dist2+dist3))<2)
			{
				DeleteArc(pdc,2);
				return true;
			}
		}
	}
	return false;
}

void CArcs::Serialize(CArchive &ar)
{
	/*
		This function serializes the class CArcs.
	*/
	CObject::Serialize(ar);
	int listdim,i;
	CPoint tpoint;
	if(ar.IsStoring())
	{
		ar<<pos<<val<<valstr<<xpe<<xps<<ype<<yps<<m_text.x<<m_text.y<<dim<<dimsgn;
		listdim=0;
		for(m_pit=m_points.begin();m_pit!=m_points.end();++m_pit) listdim++;
		ar<<listdim;
		for(m_pit=m_points.begin();m_pit!=m_points.end();++m_pit)
			ar<<(*m_pit).x<<(*m_pit).y;
		if(m_EndLoc==NULL) ar<<-1;
		else ar<<m_EndLoc->position;
		if(m_EndTran==NULL) ar<<-1;
		else ar<<m_EndTran->position;
		if(m_StartLoc==NULL) ar<<-1;
		else ar<<m_StartLoc->position;
		if(m_StartTran==NULL) ar<<-1;
		else ar<<m_StartTran->position;
	}
	else
	{
		ar>>pos>>val>>valstr>>xpe>>xps>>ype>>yps>>m_text.x>>m_text.y>>dim>>dimsgn;
		ar>>listdim;
		for(i=0;i<listdim;i++)
		{
			ar>>tpoint.x>>tpoint.y;
			m_points.insert(m_points.end(),tpoint);
		}
		ar>>reuse[0]>>reuse[1]>>reuse[2]>>reuse[3];
	}
}



void CArcs::ZoomArc(float zoom, CDC *pdc)
{
	/*
		This function moves the arc in case of zoom.
	*/
	//erase the old arc
	CPen lpen(PS_SOLID,1,RGB(255,255,255));
	CPen *pOldPen=pdc->SelectObject(&lpen);
	pdc->MoveTo(*m_points.begin());
	for(m_pit=m_points.begin();m_pit!=m_points.end();++m_pit)
		pdc->LineTo(*m_pit);
	m_pit=m_points.end();
	m_pit--;
	if(m_Type!=-1) pdc->Ellipse((*m_pit).x-dimsgn,(*m_pit).y-dimsgn,(*m_pit).x+dimsgn,(*m_pit).y+dimsgn);
	COLORREF oldcolor=pdc->SetTextColor(RGB(255,255,255));
	pdc->TextOut(m_text.x,m_text.y,valstr);
	pdc->SetTextColor(oldcolor);
	pdc->SelectObject(pOldPen);
	//set the new values
	for(m_pit=m_points.begin();m_pit!=m_points.end();++m_pit)
	{
		(*m_pit).x=(int)((*m_pit).x*zoom);
		(*m_pit).y=(int)((*m_pit).y*zoom);
	}
	dim=dim*zoom;
	dimsgn*=zoom;
	m_text.x=(int)(m_text.x*zoom);
	m_text.y=(int)(m_text.y*zoom);
	//draw new arc
	pdc->MoveTo(*m_points.begin());
	for(m_pit=m_points.begin();m_pit!=m_points.end();++m_pit)
		pdc->LineTo(*m_pit);
	m_pit=m_points.end();
	m_pit--;
	if(m_Type!=-1) pdc->Ellipse((*m_pit).x-dimsgn,(*m_pit).y-dimsgn,(*m_pit).x+dimsgn,(*m_pit).y+dimsgn);
	pdc->TextOut(m_text.x,m_text.y,valstr);
}
