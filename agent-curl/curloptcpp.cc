// ============================================================================
//	curloptcpp.cp
//	(c) 2001 - Eric Lavigne
// ============================================================================

#include "curlcpp.h"
#include <stdlib.h>
#include <string>
#include <stdarg.h>

// ============================================================================
// ============================================================================

curlInfo::curlInfo()
{
	Reset();
}

// ============================================================================

curlInfo::~curlInfo()
{
}

// ============================================================================

void curlInfo::Reset()
{
	mURL.Reset();
	mHTTPCode = 0;
	mTotalTime = mNameLookupTime = mConnectTime = mSizeUpload = mSizeDownload = mSpeedDownload = mSpeedUpload = mPreTransferTime = 0;
	mHeaderSize = mRequestSize = mVerifyResult = mFileTime = 0;
	mContentLengthDownload = mContentLengthUpload = mStartTransferTime = 0;
}

// ============================================================================

void curlInfo::Update(CURL *aData)
{
	char	*theStr;
	long	theLong;
	double	theDouble;
	
	Reset();
	
	if (curl_easy_getinfo(aData, CURLINFO_EFFECTIVE_URL, &theStr) == CURLE_OK)
		mURL.Set(theStr);

	if (curl_easy_getinfo(aData, CURLINFO_HTTP_CODE, &theLong) == CURLE_OK)
		mHTTPCode = theLong;

	if (curl_easy_getinfo(aData, CURLINFO_TOTAL_TIME, &theDouble) == CURLE_OK)
		mTotalTime = theDouble;

	if (curl_easy_getinfo(aData, CURLINFO_NAMELOOKUP_TIME, &theDouble) == CURLE_OK)
		mNameLookupTime = theDouble;

	if (curl_easy_getinfo(aData, CURLINFO_CONNECT_TIME, &theDouble) == CURLE_OK)
		mConnectTime = theDouble;

	if (curl_easy_getinfo(aData, CURLINFO_SIZE_UPLOAD, &theDouble) == CURLE_OK)
		mSizeUpload = theDouble;

	if (curl_easy_getinfo(aData, CURLINFO_SIZE_DOWNLOAD, &theDouble) == CURLE_OK)
		mSizeDownload= theDouble;

	if (curl_easy_getinfo(aData, CURLINFO_SPEED_DOWNLOAD, &theDouble) == CURLE_OK)
		mSpeedDownload = theDouble;

	if (curl_easy_getinfo(aData, CURLINFO_SPEED_UPLOAD, &theDouble) == CURLE_OK)
		mSpeedUpload = theDouble;

	if (curl_easy_getinfo(aData, CURLINFO_PRETRANSFER_TIME, &theDouble) == CURLE_OK)
		mPreTransferTime = theDouble;

	if (curl_easy_getinfo(aData, CURLINFO_HEADER_SIZE, &theLong) == CURLE_OK)
		mHeaderSize = theLong;

	if (curl_easy_getinfo(aData, CURLINFO_REQUEST_SIZE, &theLong) == CURLE_OK)
		mRequestSize = theLong;

	if (curl_easy_getinfo(aData, CURLINFO_SSL_VERIFYRESULT, &theLong) == CURLE_OK)
		mVerifyResult = theLong;

	if (curl_easy_getinfo(aData, CURLINFO_FILETIME, &theLong) == CURLE_OK)
		mFileTime = theLong;

	if (curl_easy_getinfo(aData, CURLINFO_CONTENT_LENGTH_DOWNLOAD, &theDouble) == CURLE_OK)
		mContentLengthDownload = theDouble;

	if (curl_easy_getinfo(aData, CURLINFO_CONTENT_LENGTH_UPLOAD, &theDouble) == CURLE_OK)
		mContentLengthUpload = theDouble;

	if (curl_easy_getinfo(aData, CURLINFO_STARTTRANSFER_TIME, &theDouble) == CURLE_OK)
		mStartTransferTime = theDouble;
}

// ============================================================================
// ============================================================================

void curlHeaders::AddHeader(const char *aName, const char *aValue)
{
	curlString	theStr;
	
	theStr.Set(aName, aValue, ": ");
	mStrList = curl_slist_append(mStrList, theStr.Get());
}

void curlHeaders::Setup(CURL *aData, CURLoption anOptionID)
{
	(void) curl_easy_setopt(aData, anOptionID, mStrList);
}

// ============================================================================
// ============================================================================

curlProgressCallBack::curlProgressCallBack() :
	mProgressFunc(NULL),
	mData(NULL)
{
}	

void curlProgressCallBack::Set(curl_progress_callback aCallBack, void *aData)
{
	mProgressFunc = aCallBack;
	mData = aData;
}	

void curlProgressCallBack::Setup(CURL *aData)
{
	(void) curl_easy_setopt(aData, CURLOPT_PROGRESSFUNCTION, mProgressFunc);
	(void) curl_easy_setopt(aData, CURLOPT_PROGRESSDATA, mData);
}

// ============================================================================
// ============================================================================

curlPasswordCallBack::curlPasswordCallBack() :
	mPasswordFunc(NULL),
	mData(NULL)
{
}	

void curlPasswordCallBack::Set(curl_passwd_callback aCallBack, void *aData)
{
	mPasswordFunc = aCallBack;
	mData = aData;
}	

void curlPasswordCallBack::Setup(CURL *aData)
{
	(void) curl_easy_setopt(aData, CURLOPT_PASSWDFUNCTION, mPasswordFunc);
	(void) curl_easy_setopt(aData, CURLOPT_PASSWDDATA, mData);
}

// ============================================================================
// ============================================================================

curlHTTPProxy::curlHTTPProxy() :
	mPort(0),
	mfTunnel(false)
{
}	

curlHTTPProxy::~curlHTTPProxy()
{
}

void curlHTTPProxy::Set(const char *aProxyName, long aPort, bool afTunnel)
{
	mProxyName.Set(aProxyName); 
	mPort = aPort;
	mfTunnel = afTunnel;
}	

void curlHTTPProxy::Setup(CURL *aData)
{
	(void) curl_easy_setopt(aData, CURLOPT_PROXY, mProxyName.Get());
	(void) curl_easy_setopt(aData, CURLOPT_PROXYPORT, mPort);
	(void) curl_easy_setopt(aData, CURLOPT_HTTPPROXYTUNNEL, (long) mfTunnel);
	
	mUserPassword.Setup(aData, CURLOPT_PROXYUSERPWD);
}

// ============================================================================
// ============================================================================

curlUserPassword::curlUserPassword(const char *aUserPassword)
{
	SetUserAndPassword(aUserPassword);
}

curlUserPassword::curlUserPassword(const char *aUser, const char *aPassword)
{
	SetUser(aUser);
	SetPassword(aPassword);
}

curlUserPassword::~curlUserPassword()
{
}

void curlUserPassword::SetUserAndPassword(const char *aUserPassword)
{
	mUser.Reset();
	mPassword.Reset();
	
	if (aUserPassword == NULL)
		return;
		
	char	*theSep = strchr(aUserPassword, ':');
	
	if (theSep == NULL)
	{
		mUser.Set(aUserPassword); 
	}
	else
	{
		mUser.curlBuffer::Set(aUserPassword, (size_t) (theSep - aUserPassword)); 
		mPassword.Set(&theSep[1]); 
	}
}

void curlUserPassword::SetUser(const char *aUser)
{ 
	mUser.Set(aUser); 
}

void curlUserPassword::SetPassword(const char *aPassword)
{
	mPassword.Set(aPassword); 
}

void curlUserPassword::Setup(CURL *aData, CURLoption anOptionID)
{
	mUserPassword.Set(mUser.Get(), mPassword.Get(), ":");
	(void) curl_easy_setopt(aData, anOptionID, mUserPassword.Get());
}

// ============================================================================
// ============================================================================

curlHTTPPost::~curlHTTPPost()
{
}

void curlHTTPPost::Set(const char *aPostData)
{
	mPostData.Set(aPostData);
}

void curlHTTPPost::Set(const void *aPostData, size_t aLength)
{
	mPostData.curlBuffer::Set((const char*) aPostData, aLength);
}

void curlHTTPPost::Setup(CURL *aData)
{
	(void) curl_easy_setopt(aData, CURLOPT_POSTFIELDS, mPostData.Get());
	(void) curl_easy_setopt(aData, CURLOPT_POSTFIELDSIZE, mPostData.GetLength());
}

// ============================================================================
// ============================================================================

curlHTTPPostMultiPart::curlHTTPPostMultiPart() :
	mFormPost(NULL),
	mLastPtr(NULL)
{
}

curlHTTPPostMultiPart::~curlHTTPPostMultiPart()
{
	curl_formfree(mFormPost);
}

void curlHTTPPostMultiPart::Reset()
{
	curl_formfree(mFormPost);
	mFormPost = mLastPtr = NULL;
}

void curlHTTPPostMultiPart::Add(const char *aName, const char *aValue)
{
	curl_formadd(&mFormPost, &mLastPtr, 
 					CURLFORM_COPYNAME, aName,
					CURLFORM_COPYCONTENTS, aValue,
					CURLFORM_END);
}

void curlHTTPPostMultiPart::AddFile(const char *aName, const char *aFileName)//, const char *aContentType)
{
	curl_formadd(&mFormPost, &mLastPtr, 
 					CURLFORM_COPYNAME, aName,
					CURLFORM_FILE, aFileName,
//					CURLFORM_CONTENTTYPE, aContentType,
					CURLFORM_END);
}

/*
void curlHTTPPostMultiPart::AddFileContent(const char *aName, const char *aFileName)//, const char *aContentType)
{
	mPostData.Set(NULL);
	curl_formadd(&mFormPost, &mLastPtr, 
 					CURLFORM_COPYNAME, aName,
					CURLFORM_FILECONTENT, aFileName,
//					CURLFORM_CONTENTTYPE, aContentType,
					CURLFORM_END);
}
*/
void curlHTTPPostMultiPart::Setup(CURL *aData)
{
	(void) curl_easy_setopt(aData, CURLOPT_HTTPPOST, mFormPost);
}

// ============================================================================
// ============================================================================

/*void curlClosePolicy::curlClosePolicy(curl_closepolicy aPolicy) :
	mPolicy(aPolicy)
{
}

curl_closepolicy curlClosePolicy::SetCallBackPolicy(aCallBack)
{

	return theOldPolicy;
}

void curlClosePolicy::Setup(CURL *aData)
{
}*/
