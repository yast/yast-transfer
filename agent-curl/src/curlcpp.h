// ============================================================================
//	curlcpp.h
//	(c) 2001 - Eric Lavigne
// ============================================================================

#ifndef curlcpp_h
#define curlcpp_h

// ============================================================================

#include <curl/curl.h>

// ============================================================================
//	This class takes care of cleaning up cURL. If you want to cleanup cURL before
//	your application quits just call curlCleanup::Cleanup()
// ============================================================================

class curlCleanup
{
public:
	static void	Cleanup() { curl_global_cleanup(); }
	
protected:
	~curlCleanup() { Cleanup(); }
	
	static curlCleanup scurlCleanup;
};

// ============================================================================
//	Very simple class to manage a char buffer.
// ============================================================================

class curlBuffer
{
public:
		//	Default constructor. Creates an invalid buffer.
	curlBuffer();
	
		//	Destructor. Frees the buffer.
	virtual ~curlBuffer();

		//	Returns a pointer to the buffer data. Retruns NULL if the buffer 
		//	is not valid.
	const char	*Get() { return mBuffer; }
	
		//	Returns the buffer length.
	size_t		GetLength() { return mLength; }

		//	Sets the buffer content. Passing NULL to 'aBuffer' will result in
		//	an invalid buffer.
	void		Set(const char *aBuffer, size_t aLength);
	
		//	Free the buffer and set its size to zero. The buffer becomes 
		//	invalid.
	void		Reset();
	
		//	Returns true if the buffer is valid (ie: the buffer is allocated)
		//	This can be used to test if a call to 'Set' has failed due to
		//	a memory allocation failure.
	bool		IsValid()	{ return mBuffer != NULL; }
	
protected:
	char		*mBuffer;
	size_t		mLength;	
};

// ============================================================================
//	Very simple class to manage a C string.
// ============================================================================

class curlString : public curlBuffer
{
public:
		//	Default constructor. Creates an invalid string.
	curlString() {}

		//	Sets the string.
	void		Set(const char *aStr);
	
		//	Sets the string by concatening 'aName', 'aSep' and 'aValue'.
		//	Any (and even all) of these can be a NULL string. But if 'aName' 
		//	and 'aValue' is NULL, 'aSep' will be ignored and the result is an 
		//	invalid string.
	void		Set(const char *aName, const char *aValue, const char *aSep);
};

// ============================================================================
//	Very simple class used to manage a list of strings.
//	Implementation is based on cURL 'curl_slist' set of functions.
// ============================================================================

class curlStrList
{
public:
	friend class curlEasyFTP;

		//	Default constructor. Creates an empty list.
	curlStrList();
	
		//	Destructor. Frees the list and its content.
	virtual ~curlStrList();

		//	Adds a string to the list. Returns true if the string was added, false
		//	if not.
	bool		Add(const char *aStr);
	
		//	Frees the list and its content.
	void		Reset();
	
protected:
	curl_slist	*mStrList;
	
	virtual void Setup(CURL *aData, CURLoption anOptionID);
};

// ============================================================================
// ============================================================================

class curlInfo
{
public:
	friend class curlEasy;
	
	curlInfo();
	~curlInfo();

	void	Reset();
	
	curlString	mURL;
	long		mHTTPCode;
	double		mTotalTime;
	double		mNameLookupTime;
	double		mConnectTime;
	double		mSizeUpload;
	double		mSizeDownload;
	double		mSpeedDownload;
	double		mSpeedUpload;
	double		mPreTransferTime;
	long		mHeaderSize;
	long		mRequestSize;
	long		mVerifyResult;
	long		mFileTime;
	double		mContentLengthDownload;
	double		mContentLengthUpload;
	double		mStartTransferTime;

protected:
	void		Update(CURL *aData);
};

// ============================================================================
// ============================================================================

class curlUserPassword
{
public:
	friend class curlHTTPProxy;
	friend class curlEasy;

	curlUserPassword(const char *aUserPassword = NULL);
	curlUserPassword(const char *aUser, const char *aPassword);
	virtual ~curlUserPassword();

	void	SetUserAndPassword(const char *aUserPassword);
	void	SetUser(const char *aUser);
	void	SetPassword(const char *aPassword);

protected:
	curlString	mUser;
	curlString	mPassword;
	curlString	mUserPassword;

	virtual void Setup(CURL *aData, CURLoption anOptionID);
};

// ============================================================================
// ============================================================================

class curlHTTPPost
{
public:
	friend class curlEasyHTTP;

	curlHTTPPost() {}
	virtual ~curlHTTPPost();
	
	void		Set(const char *aPostData);
	void		Set(const void *aPostData, size_t aLength);

protected:
	curlString		mPostData;
	
	virtual void Setup(CURL *aData);
};

// ============================================================================
// ============================================================================

class curlHTTPPostMultiPart
{
public:
	friend class curlEasyHTTP;

	curlHTTPPostMultiPart();
	virtual ~curlHTTPPostMultiPart();

	void		Add(const char *aName, const char *aValue);
	void		AddFile(const char *aName, const char *aFileName);

	void		Reset();
	
protected:
	struct HttpPost	*mFormPost;
	struct HttpPost	*mLastPtr;
	
	virtual void Setup(CURL *aData);
};

// ============================================================================
// ============================================================================

class curlProgressCallBack
{
public:
	friend class curlEasy;

	curlProgressCallBack();

	void	Set(curl_progress_callback aCallBack, void *aData = NULL);
	
protected:
	curl_progress_callback	mProgressFunc;
	void					*mData;
	
	virtual void Setup(CURL *aData);
};

// ============================================================================
// ============================================================================

class curlPasswordCallBack
{
public:
	friend class curlEasy;

	curlPasswordCallBack();
	
	void	Set(curl_passwd_callback aCallBack, void *aData = NULL);
	
protected:
	curl_passwd_callback	mPasswordFunc;
	void					*mData;
	
	virtual void Setup(CURL *aData);
};

// ============================================================================
// ============================================================================

class curlHeaders : public curlStrList
{
public:
	friend class curlEasyHTTP;

	curlHeaders() {}
	virtual ~curlHeaders() {}

	void		AddHeader(const char *aName, const char *aValue);

protected:
	virtual void Setup(CURL *aData, CURLoption anOptionID);
};

// ============================================================================
// ============================================================================

class curlHTTPProxy
{
public:
    friend class curlEasy;

    curlHTTPProxy();
    virtual ~curlHTTPProxy();

    //	Set the proxy name, the proxy port and the tunneling mode.
    void Set(const char *aProxyName, long aPort = 0, bool afTunnel = false);
	
    curlUserPassword	mUserPassword;

protected:
	long		mPort;
	bool		mfTunnel;
	curlString	mProxyName;
	
	virtual void	Setup(CURL *aData);
};

// ============================================================================
//	This is the virtual class that has to be used as the base class to specify 
//	any kind of storage trait. Subclasses need to implement the 'Setup' method.
//	Storage traits can be used for input (read) or output (write).
// ============================================================================

class curlStorageTrait
{
public:
	friend class curlStorage;
	
protected:
	curlStorageTrait();
	virtual ~curlStorageTrait();

	virtual bool	Setup(CURL *aData, CURLoption anOptionID) = 0;
};

// ============================================================================
//	Storage trait using memory to store its content. Memory allocation and 
//	deallocation is done using the standard 'malloc', 'realloc' and 'free' 
//	functions.
// ============================================================================
	
class curlMemoryTrait : public curlStorageTrait
{
public:
		//	Default constructor, the buffer will be allocated when 'Write'
		//	will be called and deallocated by the destructor. This is the 
		//	constructor to use for output (write).
	curlMemoryTrait();
	
		//	Input (read) constructor. If 'afOwn' is true the buffer will be 
		//	deallocated (using 'free') in the destructor. If not it's the caller 
		//	responsibility to deallocate the buffer.
	curlMemoryTrait(void *aBuffer, size_t aLength, bool afOwn);
	
		//	Free the buffer if owned.
	virtual 	~curlMemoryTrait();

	size_t		Write(void *aBuffer, size_t aLength);
	size_t		Read(void *aBuffer, size_t aLength);
	
		//	Free the buffer, set buffer to NULL and size to zero.
	void		Reset();
	
		//	Returns a pointer to the buffer (for read only). Returns NULL
		//	after a call to the default constructor or to 'Reset'.
	void		*GetBuffer()	{ return mBuffer; }	
	
		//	Returns the buffer size
	size_t		GetLength()		{ return mLength; }

		//	Convert the buffer into a C string (zero terminated). If the buffer
		//	contains binary data, the string will be only made of the data
		//	before the first zero in the buffer.
	const char	*GetBufferAsString();
	
protected:	
	void			*mBuffer;
	size_t			mLength;
	size_t			mSize;
	size_t			mPos;
	size_t			mZeroPos;
	bool			mfOwn;
	
	bool			Realloc(size_t aLength);

	virtual bool	Setup(CURL *aData, CURLoption anOptionID);
};

// ============================================================================
//	Base class for 'FILE' storage trait.
// ============================================================================
	
class curlFileTrait : public curlStorageTrait
{
public:
		//	Close the file if it has been specified using a file name and has not 
		//	already been closed by a call to 'Close'.
	virtual ~curlFileTrait();
	
		//	Returns the file size. The file has to be opened before for this to 
		//	succeed.
	bool		GetSize(long &aSize);
	
		// 	Returns file name. Returns NULL if the file xas specified using the 'FILE'
		//	constructor. If the file is not open or an error occured, false is returned.
	const char	*GetName() { return mFileName.Get(); }

		//	Open the file using 'anOpenMode'. Returns true if the file was already 
		//	open or has been open successfully.
	bool		Open(const char *anOpenMode);
	
		//	Close the file. Returns true if the file was already closed or closed 
		//	successfully. Returns false if the file was specified using the 'FILE' 
		//	constructor.
	bool		Close();
	
protected:	
	FILE		*mFile;
	curlString	mFileName;

		// 'FILE' constructor. The file will never be closed. It's the caller 
		//	responsibility to close it.
	curlFileTrait(FILE *aFile);
	
		//	File name constructor. The file will be opened and closed when needed.
	curlFileTrait(const char *aFileName);	
};

// ============================================================================
// ============================================================================
	
class curlOutputFileTrait : public curlFileTrait
{
public:
	curlOutputFileTrait(FILE *aFile);
	curlOutputFileTrait(const char *aFileName);
	
protected:	
	virtual bool	Setup(CURL *aData, CURLoption anOptionID);
};

// ============================================================================

class curlInputFileTrait : public curlFileTrait
{
public:
	curlInputFileTrait(FILE *aFile);
	curlInputFileTrait(const char *aFileName);
	
protected:	
	virtual bool	Setup(CURL *aData, CURLoption anOptionID);
};

// ============================================================================
// ============================================================================

class curlStorage
{
public:	
	friend class curlEasy;
	
	void		SetTrait(curlStorageTrait *aTrait, bool afOwn);

protected:
	curlStorage();	
	virtual ~curlStorage();
	
	bool		Setup(CURL *aData, CURLoption anOptionID);
	
	curlStorageTrait	*mTrait;
	bool				mfOwn;
};

// ============================================================================
// ============================================================================

class curlEasy
{
public:
	curlEasy();
	virtual ~curlEasy();

	CURLcode	Perform();

	void		GetInfo(curlInfo &anInfo);
	
	void		SetURL(const char *anURL);
	void		SetPort(long aPort = 0);

	void		SetConnectTimeOut(unsigned long aTimeOut);
	void		SetOverallTimeOut(unsigned long aTimeOut);
	void		SetLowSpeedAbort(unsigned long aByteLimit, unsigned long aTimeLimit);
	
	void		SetVerbose(bool afVerbose = true);
	void		SetUseNETRC(bool afUseNETRC = true);
	
	const char	*GetErrorStr() { return mErrorBuffer; }
	
	curlUserPassword		mUserPassword;
	curlPasswordCallBack	mPasswordCallBack;
	
	curlProgressCallBack	mProgressCallBack;
	
	curlHTTPProxy			mHTTPProxy;
	
	curlStorage				mOutputStorage;
	curlStorage				mHeaderStorage;
	curlStorage				mErrorStorage;
	
protected:	
	CURL		*mData;
	char		mErrorBuffer[CURL_ERROR_SIZE];
	curlString	mURL;
	
	virtual bool		Setup();
};

// ============================================================================
// ============================================================================

class curlEasyHTTP : public curlEasy
{
public:
	curlEasyHTTP();
	virtual ~curlEasyHTTP();

	void					SetReferer(const char *aReferer);
	void					SetUserAgent(const char *aUserAgent);
	void					SetMaxRedirect(unsigned long aCount);
	void					SetHTTPVersion(long aVersion = CURL_HTTP_VERSION_NONE);
	
	curlHTTPPostMultiPart	mPostMultiPart;
	curlHTTPPost			mPost;
	
	curlHeaders				mHeaders;

protected:	
	curlString				mReferer;
	curlString				mUserAgent;

	virtual bool			Setup();
};

// ============================================================================
// ============================================================================

class curlEasyFTP : public curlEasy
{
public:
	curlEasyFTP();
	virtual ~curlEasyFTP();

	void				SetUseEPSV(bool afUse = true);
	void				SetListFileNamesOnly(bool afListFileNameOnly = true);
	
	curlStrList			mCommandsBeforeTransfer;
	curlStrList			mCommandsAfterTransfer;

protected:	
	virtual bool		Setup();
};

// ============================================================================
// ============================================================================

#endif
