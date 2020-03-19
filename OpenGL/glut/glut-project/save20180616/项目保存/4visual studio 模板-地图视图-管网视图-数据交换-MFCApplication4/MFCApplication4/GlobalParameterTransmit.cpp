#include "stdafx.h"
#pragma once

#include "GlobalParameterTransmit.h"

CGlobalParameterTransmit::CGlobalParameterTransmit()
{
	gfp.iStorey = 0;
	gfp.bPiple = 1;
	gfp.iNum = 0;
	gfp.iHead = 0;
	gfp.iTail = 0;
	gfp.iMiddle = 0;

	
}

CGlobalParameterTransmit::~CGlobalParameterTransmit()
{

}

void CGlobalParameterTransmit::FileViewParameterVoluation(int iStorey , bool bPiple , int iNum , int iHead , int iTail , int iMiddle)
{
	if (!bPiple)
	{

		this->gfp.iStorey = iStorey;
		this->gfp.bPiple = bPiple;
		this->gfp.iNum = iNum;
		this->gfp.iHead = iHead;
		this->gfp.iTail = iTail;
		this->gfp.iMiddle = iMiddle;
	}
}

void CGlobalParameterTransmit::FileViewParameterVoluation(int iStorey , bool bPiple , int iNum , int iHead , int iTail)
{
	if (bPiple)
	{

		this->gfp.iStorey = iStorey;
		this->gfp.bPiple = bPiple;
		this->gfp.iNum = iNum;
		this->gfp.iHead = iHead;
		this->gfp.iTail = iTail;
		this->gfp.iMiddle = 0;
	}
}