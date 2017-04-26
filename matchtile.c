#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "matchtile.h"

//Returns length of array
#define SIZE_OF_ARRAY(_array) (sizeof(_array) / sizeof(_array[0]))



//Arrays: X & Y Lines
int groupArrayX[4]={420, 421, 429, 420};
int groupArrayY[4]={100, 110, 120, 80};
	


//X lines
int lineArrayX[30]={-580, -540, -500, -460, -420, -380, -340, -300, -260, -220, -180, -140, -100, -60, -20,
20, 60, 100, 140, 180, 220, 260, 300, 340, 380, 420, 460, 500, 540, 580};
//Y lines
int lineArrayY[16]={-20, 20, 60, 100, 140, 180, 220, 260, 300, 340, 380, 420, 460, 500, 540, 580};

//Constants
int8_t maxAvgDist;
uint8_t noPoints;
uint8_t noXlines;
uint8_t noYlines;

//Test Variables
int testX;
int testY;
int matchtestX;
int matchtestY;
int matchtestXnext;
int matchtestYnext;
int testArrayMax;
int testArrayMin;
int testNoCorner;


//Assigning values to the constants
void init_const()
{
	maxAvgDist = 15;
	noPoints = SIZE_OF_ARRAY(groupArrayX);
	noXlines = SIZE_OF_ARRAY(lineArrayX);
	noYlines = SIZE_OF_ARRAY(lineArrayY);
}

//Returns the average value of the elements in an array: WORKS!
int avgArray(int a[], int num_elements)
{
	int32_t sum;
	int32_t i;
	int32_t avg;
	sum=0;
	avg=0;
	for (i=0; i<num_elements;i++)
	{
		sum=sum+a[i];
		avg=sum/(i+1);
	}
	return(avg);
}

//Matches a set/group of measured x or y values to the closest x or y line
int matchX(int a[])
{
	int16_t tempX;
	int32_t tempMinX;
	int32_t bestMatchX;
	int32_t avgPointGroupX;
	tempMinX=10000;
	bestMatchX = 11111;

	avgPointGroupX = avgArray(a,noPoints);

	for(unsigned int i=0; i<noXlines+1; ++i)
	{
		tempX = lineArrayX[i];
		if((tempMinX > abs(avgPointGroupX - tempX)) & (abs(avgPointGroupX - tempX) < maxAvgDist))
		{
			tempMinX=abs(avgPointGroupX-tempX);
			bestMatchX = tempX;
		}
	}
	if(bestMatchX!=11111)
	{
		return bestMatchX;
	}
	else
	{
		return 1;
	}
	
}

int matchY(int a[])
{
	int16_t tempY;
	int32_t tempMinY;
	int32_t bestMatchY;
	int32_t avgPointGroupY;
	tempMinY=10000;
	bestMatchY = 11111;

	avgPointGroupY = avgArray(a,noPoints);

	for(unsigned int i=0; i<noYlines+1; ++i)
	{
		tempY = lineArrayY[i];
		if((tempMinY > abs(avgPointGroupY - tempY)) & (abs(avgPointGroupY - tempY) < maxAvgDist))
		{
			tempMinY=abs(avgPointGroupY-tempY);
			bestMatchY = tempY;
		}
	}
	return bestMatchY;
}

//Matches a set of measured x or y values to the next closest x or y line

int matchXnext(int a[], int dontMatch)
{
	if(dontMatch!=1)
	{
		int16_t tempX;
		int32_t tempMinX;
		int32_t bestMatchX;
		int32_t avgPointGroupX;
		tempMinX=10000;
		bestMatchX = 11111;

		avgPointGroupX = avgArray(a,noPoints);

		for(unsigned int i=0; i<noXlines+1; ++i)
		{
			tempX = lineArrayX[i];
			if((tempMinX > abs(avgPointGroupX - tempX)) & (tempX!=dontMatch))
			{
				tempMinX=abs(avgPointGroupX-tempX);
				bestMatchX = tempX;
			}
		}
		return bestMatchX;
	}
	else
	{
		return 1;
	}
	
}

int matchYnext(int a[], int dontMatch)
{
	if(dontMatch!=1)
	{
		int16_t tempY;
		int32_t tempMinY;
		int32_t bestMatchY;
		int32_t avgPointGroupY;
		tempMinY=10000;
		bestMatchY = 11111;

		avgPointGroupY = avgArray(a,noPoints);

		for(unsigned int i=0; i<noYlines+1; ++i)
		{
			tempY = lineArrayY[i];
			if((tempMinY > abs(avgPointGroupY - tempY)) & (tempY!=dontMatch))
			{
				tempMinY=abs(avgPointGroupY-tempY);
				bestMatchY = tempY;
			}
		}
		return bestMatchY;
	}
	else
	{
		return 1;
	}
	
}

//Finds max or min value of array

int max_array(int a[], int num_elements)
{
	int i;
	int max=-32000;
	
	for (i=0; i<num_elements; i++)
	{
		if (a[i]>max)
		{
			max=a[i];
		}
	}
	return max;
}

int min_array(int a[], int num_elements)
{
	int i;
	int min=32000;
	for (i=0; i<num_elements; i++)
	{
		if (a[i]<min)
		{
			min=a[i];
		}
	}
	return min;
}

bool noCorner(int x[], int y[])
{
	int maxDiffAllowed = 10;
	int minX = min_array(x,noPoints);
	int maxX = max_array(x,noPoints);
	
	int minY = min_array(y,noPoints);
	int maxY = max_array(y,noPoints);
	
	int maxDiffX = abs(abs(maxX)-abs(minX));
	int maxDiffY = abs(abs(maxY)-abs(minY));
	
	if((maxDiffX > maxDiffAllowed) & (maxDiffY > maxDiffAllowed))
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool xLine(int x[], int y[])
{
	int maxDiffAllowed = 10;
	
	int minX = min_array(x,noPoints);
	int maxX = max_array(x,noPoints);
	
	int minY = min_array(y,noPoints);
	int maxY = max_array(y,noPoints);
	
	int maxDiffX = abs(abs(maxX)-abs(minX));
	int maxDiffY = abs(abs(maxY)-abs(minY));
	
	if((maxDiffX < maxDiffAllowed) & (maxDiffY > maxDiffAllowed))
	{
		return true;
	}
	else if((maxDiffX > maxDiffAllowed) & (maxDiffY < maxDiffAllowed))
	{
		return false;
	}
	else
	{
		return false;
	}
	
}

int matchTile(int x[],int y[])
{
	if ((xLine(x,y)) & (noCorner(x,y)))
	{
		return 1;
	}
	else if((!xLine(x,y)) & (noCorner(x,y)))
	{
		return 2;
	}
	else
	{
		return 3;
	}
}


int main()
{
	init_const();
	
	testX = avgArray(groupArrayX,noPoints);
	testY = avgArray(groupArrayY,noPoints);
	
	matchtestX=matchX(groupArrayX); 
	matchtestY=matchY(groupArrayY);
	
	matchtestXnext=matchXnext(groupArrayX,matchtestX);
	matchtestYnext=matchYnext(groupArrayY,matchtestY);
	
	testArrayMax=max_array(groupArrayX,noPoints);
	testArrayMin=min_array(groupArrayX,noPoints);
	
	testNoCorner=matchTile(groupArrayX,groupArrayY);
	
}