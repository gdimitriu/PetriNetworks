// JumpTable.cpp: implementation of the CJumpTable class.
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
#include "JumpTable.h"
#include <stdlib.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_SERIAL(CJumpTable,CObject,1)
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CJumpTable::CJumpTable(int nloc,CString in,CString out)
{
	/*
		This function stores a jump relation.
	*/
	input=(int *)calloc(nloc,sizeof(int));
	output=(int *)calloc(nloc,sizeof(int));
	nrLoc=nloc;
	int i,j,k,l;
	bool flag;
	j=0;
	char temp[10];
	for(i=0;i<nloc;i++)
	{
		for(l=0;l<10;l++) temp[l]='\0';
		flag=false;
		k=0;
		while(flag==false)
		{
			if(in[j]<58 && in[j]>47)
			{
				temp[k]=in[j];
				k++;
			}
			else flag=true;
			j++;
		}
		input[i]=atoi(temp);
	}
	j=0;
	for(i=0;i<nloc;i++)
	{
		for(l=0;l<10;l++) temp[l]='\0';
		flag=false;
		k=0;
		while(flag==false)
		{
			if(out[j]<58 && out[j]>47)
			{
				temp[k]=out[j];
				k++;
			}
			else flag=true;
			j++;
		}
		output[i]=atoi(temp);
	}
}

CJumpTable::~CJumpTable()
{
	if(input!=NULL) free(input);
	if(output!=NULL) free(output);
}

CJumpTable::CJumpTable()
{
	input=NULL;
	output=NULL;
}
void CJumpTable::Serialize(CArchive &ar)
{
	/*
		This function serializes the CJumpTable class.
	*/
	CObject::Serialize(ar);
	int i;
	if(ar.IsStoring())
	{
		ar<<nrLoc;
		for(i=0;i<nrLoc;i++) ar<<input[i];
		for(i=0;i<nrLoc;i++) ar<<output[i];
	}
	else
	{
		ar>>nrLoc;
		input=(int *)calloc(nrLoc,sizeof(int));
		output=(int *)calloc(nrLoc,sizeof(int));
		for(i=0;i<nrLoc;i++) ar>>input[i];
		for(i=0;i<nrLoc;i++) ar>>output[i];
	}
}
