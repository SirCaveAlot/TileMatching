#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "matchtile.h"

//Returns length of array
#define SIZE_OF_ARRAY(_array) (sizeof(_array) / sizeof(_array[0]))	


int getTile(int xcoord, int ycoord, int m, int n, int a[m][n])
{
	if((xcoord<0) || (ycoord<0) || (xcoord>29) || (ycoord>29))
	{
		return 1111;
	}
	else
	{
		return a[ycoord][xcoord];
	}
}

int setTile(int xcoord, int ycoord, int newTile, int m, int n, int a[m][n])
{
	if((xcoord<0) || (ycoord<0) || (xcoord>29) || (ycoord>29))
	{
		return 1111;
	}
	else
	{
		a[ycoord][xcoord]=newTile;
	}
	
	return 0;
}

int convertRobLoc_MapGlob(int coordRobot)
{
	int result;
	if(coordRobot==-560)
	{
		result = 0;
	}
	else if(coordRobot==-520)
	{
		result = 1;
	}
	else if(coordRobot==-480)
	{
		result = 2;
	}
	else if(coordRobot==-440)
	{
		result = 3;
	}
	else if(coordRobot==-400)
	{
		result = 4;
	}
	else if(coordRobot==-360)
	{
		result = 5;
	}
	else if(coordRobot==-320)
	{
		result = 6;
	}
	else if(coordRobot==-280)
	{
		result = 7;
	}
	else if(coordRobot==240)
	{
		result = 8;
	}
	else if(coordRobot==-200)
	{
		result = 9;
	}
	else if(coordRobot==-160)
	{
		result = 10;
	}
	else if(coordRobot==-120)
	{
		result = 11;
	}
	else if(coordRobot==-80)
	{
		result = 12;
	}
	else if(coordRobot==-40)
	{
		result = 13;
	}
	else if(coordRobot==0)
	{
		result = 14;
	}
	
	else if(coordRobot==40)
	{
		result = 15;
	}
	else if(coordRobot==80)
	{
		result = 16;
	}
	else if(coordRobot==120)
	{
		result = 17;
	}
	else if(coordRobot==160)
	{
		result = 18;
	}
	else if(coordRobot==200)
	{
		result = 19;
	}
	else if(coordRobot==240)
	{
		result = 20;
	}
	else if(coordRobot==280)
	{
		result = 21;
	}
	else if(coordRobot==320)
	{
		result = 22;
	}
	else if(coordRobot==360)
	{
		result = 23;
	}
	else if(coordRobot==400)
	{
		result = 24;
	}
	else if(coordRobot==440)
	{
		result = 25;
	}
	else if(coordRobot==480)
	{
		result = 26;
	}
	else if(coordRobot==520)
	{
		result = 27;
	}
	else if(coordRobot==560)
	{
		result = 28;
	}
	else
	{
		result = 1111;
	}
	return result;
}




//Assigning values to the constants
void init_const()
{
	maxAvgDist = 40;
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
	
	if((maxDiffX >= maxDiffAllowed) & (maxDiffY > maxDiffAllowed))
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
	
	if((maxDiffX <= maxDiffAllowed) & (maxDiffY > maxDiffAllowed))
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


//Returns the x tile coordinate. If it returns 3, the data window is bad and no tile should be added to the map
int matchTileX(int x[],int y[])
{
	int coordX;
	
	int bestMatchX = matchX(x);
	int nextBestMatchX = matchXnext(x,bestMatchX);
	int avgBestX = (bestMatchX+nextBestMatchX)/2;
	
	if ((xLine(x,y)) & (noCorner(x,y)))
	{
		//Put tile on the correct side of the detected line
		if(robPosX<bestMatchX)
		{
			coordX = bestMatchX + 20; 
		}
		else if(robPosX>bestMatchX)
		{
			coordX = bestMatchX - 20;
		}
		else
		{
			return 1; //Shouldn't happen #1
		}
	}
	else if((!xLine(x,y)) & (noCorner(x,y)))
	{
		if(avgBestX > bestMatchX)
		{
			coordX = bestMatchX + 20;
		}
		else if(avgBestX < bestMatchX)
		{
			coordX = bestMatchX - 20;
		}
		else
		{
			return 2; //Shouldn't happen #2
		}
	}
	else
	{
		return 3; //This can happen: bad data, corner etc. 
	}
	
	return coordX;
}

//Returns the y tile coordinate. If it returns 3, the data window is bad and no tile should be added to the map
int matchTileY(int x[],int y[])
{
	int coordY;
	
	int bestMatchY = matchY(y);
	int nextBestMatchY = matchYnext(y,bestMatchY);
	int avgBestY = (bestMatchY+nextBestMatchY)/2;
	
	if ((xLine(x,y)) & (noCorner(x,y)))
	{
		//Put tile on the correct side of the detected line
		if(avgBestY > bestMatchY)
		{
			coordY = bestMatchY + 20;
		}
		else if(avgBestY < bestMatchY)
		{
			coordY = bestMatchY - 20;
		}
		else
		{
			return 2; //Shouldn't happen #2
		}
	}
	else if((!xLine(x,y)) & (noCorner(x,y)))
	{
		if(robPosY<bestMatchY)
		{
			coordY = bestMatchY + 20;
		}
		else if(robPosY>bestMatchY)
		{
			coordY = bestMatchY - 20;
		}
		else
		{
			return 1; //Shouldn't happen #1
		}
	}
	else
	{
		return 3; //Shouldn't happen #3. Bad data, corner etc.
	}
	
	return coordY;
}

void updateMap(int x[],int y[], int m, int n, int a[m][n])
{
	int xTileRob=matchTileX(x,y);
	int yTileRob=matchTileY(x,y);
	
	if((xTileRob!=3)||(yTileRob!=3)||(xTileRob!=2)||(yTileRob!=2)||(xTileRob!=1)||(yTileRob!=1))
	{
		int xTileGlob=convertRobLoc_MapGlob(xTileRob);
		int yTileGlob=convertRobLoc_MapGlob(yTileRob);
		
		//Add +1 for each time the tile is detected
		int newVal=getTile(xTileGlob,yTileGlob,29,29,a) + 1;
		setTile(xTileGlob,yTileGlob,newVal,29,29,a);	
	}
}


int main()
{
	init_const();
	/*
	AvgTestX = avgArray(groupArrayX,noPoints);
	AvgTestY = avgArray(groupArrayY,noPoints);
	
	matchtestX=matchX(groupArrayX); 
	matchtestY=matchY(groupArrayY);
	
	matchtestXnext=matchXnext(groupArrayX,matchtestX);
	matchtestYnext=matchYnext(groupArrayY,matchtestY);
	
	testArrayMax=max_array(groupArrayX,noPoints);
	testArrayMin=min_array(groupArrayX,noPoints);
	
	xTile=matchTileX(groupArrayX,groupArrayY);
	yTile=matchTileY(groupArrayX,groupArrayY);*/
	
	
	//testMapArrayTileSet = setTile(14,14,1,29,29,mapArray);
	//testMapArrayTileGet = getTile(14,14,29,29,mapArray);
	/*
	updateMap(groupArrayX,groupArrayY,29,29,mapArray);
	updateMap(groupArrayX,groupArrayY,29,29,mapArray);
	*/
	updateMap(groupArrayX,groupArrayY,29,29,mapArray);
	updateMap(groupArrayX,groupArrayY,29,29,mapArray);
	
	testMapArrayTileGet = getTile(26,22,29,29,mapArray);
	
}