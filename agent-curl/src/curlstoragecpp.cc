// ============================================================================
//	curlstoragecpp.cp
//	(c) 2001 - Eric Lavigne
// ============================================================================

#include "curlcpp.h"
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

// ============================================================================
// ============================================================================

curlStorageTrait::curlStorageTrait()
{
}

// ============================================================================

curlStorageTrait::~curlStorageTrait()
{
}

// ============================================================================
// ============================================================================

	static size_t sMemoryWriteFunc(void *ptr, size_t , size_t nmemb, void *data)
	{
		curlMemoryTrait	*theTrait = (curlMemoryTrait*) data;
		
		return theTrait->Write(ptr, nmemb);
	}

	static size_t sMemoryReadFunc(void *ptr, size_t , size_t nmemb, void *data)
	{
		curlMemoryTrait	*theTrait = (curlMemoryTrait*) data;
		
		return theTrait->Read(ptr, nmemb);
	}

// ============================================================================

curlMemoryTrait::curlMemoryTrait() :
	mBuffer(NULL),
	mLength(NULL),
	mSize(0),
	mPos(0),
	mZeroPos((size_t) -1),
	mfOwn(true)
{
}


// ============================================================================

curlMemoryTrait::curlMemoryTrait(void *aBuffer, size_t aLength, bool afOwn) :
	mBuffer(aBuffer),
	mLength(aLength),
	mSize(aLength),
	mPos(0),
	mZeroPos((size_t) -1),
	mfOwn(afOwn)
{
}
	
// ============================================================================

curlMemoryTrait::~curlMemoryTrait()
{
	if (mfOwn && (mBuffer != NULL))
		free(mBuffer);
}
	
// ============================================================================

void curlMemoryTrait::Reset()
{
	if (mfOwn && (mBuffer != NULL))
		free(mBuffer);
		
	mBuffer = NULL;
	mfOwn = true;
	mLength = mSize = mPos = 0;
	mZeroPos = (size_t) -1;
}
	
// ============================================================================

bool curlMemoryTrait::Realloc(size_t aLength)
{
	void	*theBuffer;
	size_t	theSize = ((size_t) (((mLength + aLength) / 2048) + 1)) * 2048;
	
	if (mBuffer == 0)
	{
		if ((theBuffer = malloc(theSize)) == NULL)
			return false;
	}
	else if ((theBuffer = realloc(mBuffer, theSize)) == NULL)
		return false;
	
	mBuffer = theBuffer;
	mSize = theSize;
	return true;
}

// ============================================================================

size_t curlMemoryTrait::Write(void *aBuffer, size_t aLength)
{
	if ((mLength + aLength) > mSize)
		if (!Realloc(aLength))
			return 0;
			
	memcpy((char*) mBuffer + mLength, aBuffer, aLength);
	mLength += aLength;
	
	return aLength;
}

// ============================================================================

size_t curlMemoryTrait::Read(void *aBuffer, size_t aLength)
{
	if (mBuffer == NULL)
		return 0;
		
	if ((aLength + mPos) > mLength)
		aLength = (mLength - mPos);
		
	memcpy(aBuffer, (char*) mBuffer + mPos, aLength);
	mPos += aLength;
	
	return aLength;
}

// ============================================================================

const char *curlMemoryTrait::GetBufferAsString()
{
	char	theZero = 0;
	
		// Add a terminating zero if not already done
	if (mZeroPos != mLength)
	{
		if (!Write(&theZero, 1))
			return (char*) NULL;
			
		mZeroPos = --mLength;
	}
	
	return (char*) mBuffer;
}

// ============================================================================

bool curlMemoryTrait::Setup(CURL *aData, CURLoption anOptionID)
{
	if (anOptionID == CURLOPT_FILE)
	{
		(void) curl_easy_setopt(aData, CURLOPT_FILE, this);
		(void) curl_easy_setopt(aData, CURLOPT_WRITEFUNCTION, sMemoryWriteFunc);
	}
	else if (anOptionID == CURLOPT_WRITEHEADER)
	{
		(void) curl_easy_setopt(aData, CURLOPT_WRITEHEADER, this);
		(void) curl_easy_setopt(aData, CURLOPT_HEADERFUNCTION, sMemoryWriteFunc);
		(void) curl_easy_setopt(aData, CURLOPT_NOPROGRESS, (long) false);
	}
	else if (anOptionID == CURLOPT_STDERR)
		;	/* #### Cannot be done */
	else if (anOptionID == CURLOPT_INFILE)
	{
		(void) curl_easy_setopt(aData, CURLOPT_INFILE, this);
		(void) curl_easy_setopt(aData, CURLOPT_READFUNCTION, sMemoryReadFunc);
		(void) curl_easy_setopt(aData, CURLOPT_INFILESIZE, mLength);
	}

	return true;
}

// ============================================================================
// ============================================================================

curlStorage::curlStorage() :
	mTrait(NULL),
	mfOwn(false)
{
}

curlStorage::~curlStorage()
{
	if (mfOwn && (mTrait != NULL))
		delete mTrait;
}

void curlStorage::SetTrait(curlStorageTrait *aTrait, bool afOwn)
{
	if (mfOwn && (mTrait != NULL))
		delete mTrait;

	mTrait = aTrait;
	mfOwn = afOwn;
}

bool curlStorage::Setup(CURL *aData, CURLoption anOptionID)
{
	if (mTrait == NULL)
		return true;
	
	return mTrait->Setup(aData, anOptionID);
}

// ============================================================================
// ============================================================================

curlFileTrait::curlFileTrait(FILE *aFile) :
	mFile(aFile)
{
}

// ============================================================================

curlFileTrait::curlFileTrait(const char *aFileName) :
	mFile(NULL)
{
	mFileName.Set(aFileName);
}

// ============================================================================

curlFileTrait::~curlFileTrait()
{
	(void) Close();
}

// ============================================================================

bool curlFileTrait::GetSize(long &aSize)
{
	long	thePos;
	
	if (mFile != NULL)
		if ((thePos = ftell(mFile)) != -1)
			if (fseek(mFile, 0, SEEK_END) == 0)
			{
				aSize = ftell(mFile);
				(void) fseek(mFile, thePos, SEEK_SET);				
				return true;
			}
	
	aSize = 0;
	return false;
}

// ============================================================================

bool curlFileTrait::Open(const char *anOpenMode)
{
	if (mFile != NULL)
		return true;		
	if (mFileName.Get() == NULL)
		return false;
		
	return ((mFile = fopen(mFileName.Get(), anOpenMode)) != NULL);
}

// ============================================================================

bool curlFileTrait::Close()
{
	if (mFile == NULL)
		return true;
	if (mFileName.Get() == NULL)
		return false;
		
	(void) fclose(mFile);
	mFile = NULL;
	return true;
}

// ============================================================================
// ============================================================================

	static size_t sFILEReadFunc(void *ptr, size_t size, size_t nmemb, void *stream)
	{
		if (stream == NULL)
			return 0;
		return fread(ptr, size, nmemb, (FILE *) stream);
	}

// ============================================================================

curlInputFileTrait::curlInputFileTrait(FILE *aFile) :
	curlFileTrait(aFile)
{
}

// ============================================================================

curlInputFileTrait::curlInputFileTrait(const char *aFileName) :
	curlFileTrait(aFileName)
{
}

// ============================================================================

bool curlInputFileTrait::Setup(CURL *aData, CURLoption anOptionID)
{
	long	theSize;
	
	if ((mFile == NULL) && (mFileName.Get() != NULL))
		if (!Open("rb"))
			return false;

	if (mFile != NULL)
	{
		(void) curl_easy_setopt(aData, CURLOPT_INFILE, mFile);
		(void) curl_easy_setopt(aData, CURLOPT_READFUNCTION, sFILEReadFunc);
	
		if (GetSize(theSize))
			(void) curl_easy_setopt(aData, CURLOPT_INFILESIZE, theSize);
	}
	
	return true;
}

// ============================================================================
// ============================================================================

	static size_t sFILEWriteFunc(void *ptr, size_t size, size_t nmemb, void *stream)
	{
		if (stream == NULL)
			return 0;
		return fwrite(ptr, size, nmemb, (FILE *) stream);
	}

// ============================================================================

curlOutputFileTrait::curlOutputFileTrait(FILE *aFile) :
	curlFileTrait(aFile)
{
}

// ============================================================================

curlOutputFileTrait::curlOutputFileTrait(const char *aFileName) :
	curlFileTrait(aFileName)
{
}

// ============================================================================

bool curlOutputFileTrait::Setup(CURL *aData, CURLoption anOptionID)
{
	if ((mFile == NULL) && (mFileName.Get() != NULL))
		if (!Open("wb"))
			return false;
		
	if (mFile != NULL)
	{
		if (anOptionID == CURLOPT_FILE)
		{
			(void) curl_easy_setopt(aData, CURLOPT_FILE, mFile);
			(void) curl_easy_setopt(aData, CURLOPT_WRITEFUNCTION, sFILEWriteFunc);
		}
		else if (anOptionID == CURLOPT_WRITEHEADER)
		{
			(void) curl_easy_setopt(aData, CURLOPT_WRITEHEADER, mFile);
			(void) curl_easy_setopt(aData, CURLOPT_HEADERFUNCTION, sFILEWriteFunc);
			(void) curl_easy_setopt(aData, CURLOPT_NOPROGRESS, (long) false);
		}
		else if (anOptionID == CURLOPT_STDERR)
			(void) curl_easy_setopt(aData, CURLOPT_STDERR, mFile);
	}
	
	return true;
}
