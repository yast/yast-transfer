// ============================================================================
//	curlutilscpp.cp
//	(c) 2001 - Eric Lavigne
// ============================================================================

#include "curlcpp.h"
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

// ============================================================================
// ============================================================================

curlBuffer::curlBuffer() :
	mBuffer(NULL),
	mLength(0)
{
}

// ============================================================================

curlBuffer::~curlBuffer()
{
	if (mBuffer != NULL)
		free((void*) mBuffer);
}

// ============================================================================

void curlBuffer::Set(const char *aBuffer, size_t aLength)
{
	Reset();

	if (aBuffer != NULL)
		if ((mBuffer = (char*) malloc(aLength + 1)) != NULL)
		{
			mLength = aLength;
			memcpy(mBuffer, aBuffer, mLength);
			mBuffer[mLength] = 0;
		}
}

// ============================================================================

void curlBuffer::Reset()
{
	mLength = 0;
	if (mBuffer != NULL)
	{
		free((void*) mBuffer);
		mBuffer = NULL;		
	}
}

// ============================================================================
// ============================================================================

void curlString::Set(const char *aStr)
{
	Reset();
	
	if (aStr != NULL)
	{
		if ((mBuffer = strdup(aStr)) != NULL)
			mLength = strlen(aStr);
	}
}

// ============================================================================

void curlString::Set(const char *aName, const char *aValue, const char *aSep)
{
	Reset();
	
		//	Never build a string with only a separator
	if ((aName == NULL) && (aValue == NULL))
		return;
		
		//	Compute the new string length
	size_t	theLength = 0;

	if (aName != NULL)
		theLength += strlen(aName);
	if (aSep != NULL)
		theLength += strlen(aSep);
	if (aValue != NULL)
		theLength += strlen(aValue);

		//	String is empty, we are done
	if (theLength == 0)
		return;
		
		//	Allocate the buffer and copy strings into it
	if ((mBuffer = (char*) malloc(theLength + 1)) != NULL)
	{
		mBuffer[0] = 0;
		if (aName != NULL)
			strcat(mBuffer, aName);
		if (aSep != NULL)
			strcat(mBuffer, aSep);
		if (aValue != NULL)
			strcat(mBuffer, aValue);
			
		mLength = strlen(mBuffer);
	}
}

// ============================================================================
// ============================================================================

curlStrList::curlStrList() : 
	mStrList(NULL)
{
}

// ============================================================================

curlStrList::~curlStrList() 
{ 
	curl_slist_free_all(mStrList); 
}

// ============================================================================

bool curlStrList::Add(const char *aStr)
{
	curl_slist	*theNewStrList;
	
		//	Use a local variable to preserve list content in case this call fails
	if ((theNewStrList = curl_slist_append(mStrList, aStr)) == NULL)
		return false;
		
		//	Everything went OK, we can update the instance variable
	mStrList = theNewStrList;
	return true;
}

// ============================================================================

void curlStrList::Reset()
{
	curl_slist_free_all(mStrList);
	mStrList = NULL;
}

// ============================================================================

void curlStrList::Setup(CURL *aData, CURLoption anOptionID)
{
		//	We cast to void because this is supposed to never fail
	(void) curl_easy_setopt(aData, anOptionID, mStrList);
}
