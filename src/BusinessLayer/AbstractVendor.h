#pragma once
#include <string>
#include <ctime>
#include <list>
#include <vector>
#include <Windows.h>

#ifndef _TIME_RANGE
#define _TIME_RANGE
typedef struct _time_range
{
	std::time_t start;
	std::time_t end;
} time_range, *ptime_range;
#endif

#define  MAX_IPADDR_LEN				16       //ip address length    
#define  MAX_MACADDR_LEN			32		 //mac address length

typedef enum tagSDK_TYPE
{
	NONE_SDK = 0,
	JXJ_SDK,
	DZP_SDK,
	DH_SDK,
	HK_SDK,
}NET_SDK_TYPE;

class AbstractVendor;

struct NET_DEVICE_INFO
{
	int					nSDKType;							//device type 
	char				szIp[MAX_IPADDR_LEN];				//ip address
	int					nPort;								//port
	char				szSubmask[MAX_IPADDR_LEN];			//subnet mask
	char				szMac[MAX_MACADDR_LEN];				//mac address
	//int                 iIPVersion;							//ip version 4:ipv4 ; 6:ipv6

	AbstractVendor*		pVendor;
};

struct NET_DEVICE_INFO_SIMPLE
{
	char				szIP[MAX_IPADDR_LEN];
	int					nPort;
};

struct RecordFile
{
	RecordFile()
	{
		channel = 0;
		size = 0;
		pPrivateData = nullptr;
		PrivateDataDataSize = 0;
	}
	~RecordFile()
	{
		if (nullptr != pPrivateData)
		{
			delete pPrivateData;
			pPrivateData = nullptr;
			PrivateDataDataSize = 0;
		}
	}
	RecordFile(const RecordFile& other)
	{
		channel = other.channel;
		size = other.size;
		name = other.name;
		strTimeSection = other.strTimeSection;
		beginTime = other.beginTime;
		endTime = other.endTime;
		duration = other.duration;
		pPrivateData = nullptr;
		PrivateDataDataSize = 0;
		setPrivateData(other.pPrivateData, other.PrivateDataDataSize);
	}

	RecordFile& operator= (const RecordFile& other)
	{
		if (&other == this)
		{
			return *this;
		}
		channel = other.channel;
		size = other.size;
		name = other.name;
		strTimeSection = other.strTimeSection;
		beginTime = other.beginTime;
		endTime = other.endTime;
		duration = other.duration;
		setPrivateData(other.pPrivateData, other.PrivateDataDataSize);
		return *this;
	}
	// Set Private Data
	void setPrivateData(void* pData, int size)
	{
		if (nullptr != pPrivateData)
		{
			delete pPrivateData;
			pPrivateData = nullptr;
			PrivateDataDataSize = 0;
		}
		if (size > 0)
		{
			pPrivateData = new char[size];
			PrivateDataDataSize = size;
			memcpy(pPrivateData, pData, size);
		}
	}
	// Get Private Data
	void* getPrivateData() const
	{
		return pPrivateData;
	}
	// Get Private Data Size
	__int32 getPrivateDataSize() const
	{
		return PrivateDataDataSize;
	}
	void deletePrivateData()
	{
		delete pPrivateData;
		pPrivateData = nullptr;
	}

	int channel;
	int size;
	std::string name;
	std::string strTimeSection;
	std::time_t beginTime;
	std::time_t endTime;
	unsigned long duration;
	char* pPrivateData;   //Private Data
	__int32 PrivateDataDataSize;//Private Data Size
};

typedef std::vector<NET_DEVICE_INFO*> DEVICE_INFO_LIST;
typedef std::vector<NET_DEVICE_INFO_SIMPLE*> DEVICE_INFO_SIMPLE_LIST;
typedef std::vector<AbstractVendor*> VENDOR_LIST;
typedef std::vector<RecordFile> RECORD_FILE_LIST;

class AbstractVendor
{
public:
	virtual void Init() = 0;
	virtual long Login(const std::string& ip, size_t port, const std::string& user, const std::string& password) = 0;
	virtual void Logout(const long loginHandle) = 0;

	virtual void SearchAll(const long loginHandle) = 0;
	virtual void Search(const long loginHandle, const size_t channel, const time_range& range) = 0;
	virtual void Download(const long loginHandle, const size_t channel, const time_range& range) = 0;
	virtual void PlayVideo(const long loginHandle, const size_t channel, const time_range& range) = 0;
	virtual void Download(const long loginHandle, const size_t channel, const std::string& filename) = 0;
	virtual void PlayVideo(const long loginHandle, const size_t channel, const std::string& filename) = 0;

	virtual void SetHWnd(const HWND& hWnd) = 0;
	virtual void SetDownloadPath(const std::string& Root) = 0;
	virtual void throwException() = 0;

	virtual std::string GetDefUsearName() = 0;
	virtual std::string GetDefPassword() = 0;
	virtual NET_SDK_TYPE GetSDKType() = 0;

	virtual void StartSearchDevice() = 0;
	virtual DEVICE_INFO_LIST& GetDeviceInfoList() = 0;
	virtual void StopSearchDevice() = 0;
	virtual size_t GetMaxChannel() = 0;

	virtual RECORD_FILE_LIST GetRecordFileList() = 0;

};