#include <stdio.h>
#include <stdlib.h>
#include "AdptArray.h"
#include <string.h>

//define the struct
typedef struct AdptArray_
{
	int ArrSize;
	PElement* pElemArr;
	DEL_FUNC delFunc;
	COPY_FUNC copyFunc;
	PRINT_FUNC printFunc; 

}AdptArray, *PAdptArray;

//create adapt array
PAdptArray CreateAdptArray(COPY_FUNC copyFunc_, DEL_FUNC delFunc_, PRINT_FUNC printFunc_ )
{
	PAdptArray pArr = (PAdptArray)malloc(sizeof(AdptArray));
	if (pArr == NULL)
		return NULL;
	pArr->ArrSize = 0;
	pArr->pElemArr = NULL;
	pArr->delFunc = delFunc_;
	pArr->copyFunc = copyFunc_;
	pArr->printFunc = printFunc_;
	return pArr;
}
// delete the adapat array
void DeleteAdptArray(PAdptArray pArr)
{
	int i;
	if (pArr == NULL)
		return;
	for(i = 0; i < pArr->ArrSize; ++i)
	{ 	
		if(!((pArr->pElemArr)[i]))
		{
			continue;
		}
		pArr->delFunc((pArr->pElemArr)[i]);
	}
	free(pArr->pElemArr);
	free(pArr);
}
// update the arry
Result SetAdptArrayAt(PAdptArray pArr, int index, PElement pNewElem)
{
	PElement* newpElemArr;
	if (pArr == NULL)
		return FAIL;

	if (index >= pArr->ArrSize)
	{
		
// Extend Array
		if ((newpElemArr = (PElement*)calloc((index + 1), sizeof(PElement))) == NULL)
			return FAIL;
		memcpy(newpElemArr, pArr->pElemArr, (pArr->ArrSize) * sizeof(PElement));
		free(pArr->pElemArr);
		pArr->pElemArr = newpElemArr;
	}

	// Delete Previous Elem
	if((pArr->pElemArr)[index])
	{
		 pArr->delFunc((pArr->pElemArr)[index]);
	}
	(pArr->pElemArr)[index] = pArr->copyFunc(pNewElem); 

	// Update Array Size
	pArr->ArrSize = (index >= pArr->ArrSize) ? (index + 1) : pArr->ArrSize;
	return SUCCESS;
}


// return the element in the given index.
PElement GetAdptArrayAt(PAdptArray pArr, int index)
{	PElement copyElement = NULL;
	if(!pArr)
	{
		return NULL;
	}
	if(index >= pArr->ArrSize || index < 0)
	{
		return NULL;
	}
	if(!((pArr->pElemArr)[index]))
	{
		 return NULL;
	}
	 copyElement = pArr->copyFunc(pArr->pElemArr[index]);
	return copyElement;
}
//get the suze of the array.
int GetAdptArraySize(PAdptArray pArr)
{
	if(!pArr)
	{
		return -1;
	}
	return pArr->ArrSize;
}
// print the array.
void PrintDB(PAdptArray pArr)
{
	if(!pArr)
	{
		return;
	}
	int i;
	for(i=0;i<pArr->ArrSize;i++)
	{
		if(pArr->pElemArr[i])
		{
			pArr->printFunc(pArr->pElemArr[i]);
		}
	}

}
