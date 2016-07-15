#pragma once

#include "AbstractVendor.h"

#include <string>
#include <vector>
#include <cassert>
#include <iostream>


/*
Please make sure type of vendor before you create a Device Object
*/

typedef enum
{
	Login_Status_No = 0,
	Login_Status_Yes

}DeviceLoginStatus;

class AbstractVendor;

class Device
{
public:
	Device(const AbstractVendor* sdk);
	//Device &= (const Device* pDev);
	Device();
	~Device();

	void setSDK(AbstractVendor* sdk);
	void Init();
	bool LoginChain(const NET_DEVICE_INFO_SIMPLE* pDevInfoSimple, int& indexVendor);
	bool Login(const std::string& ip, size_t port, const std::string& userName = "", const std::string& password = "");
	void Logout();
	void SetDownloadPath(const std::string& root);

	void SearchAll();
	void Search(const size_t channel, const time_range& range);
	void Download(const size_t channel, const time_range& range);
	void PlayVideo(const HWND hWnd, const size_t channel, const time_range& range);
	void Download(const size_t channel, const std::string& fileName);
	void PlayVideo(const HWND hWnd, const size_t channel, const std::string& fileName);

	// Device Search Model
	void StartSearchDevice();
	void StopSearchDevice();
	DEVICE_INFO_LIST& GetDeviceInfoList(){ return m_pVendor->GetDeviceInfoList(); }

	// Get Max Channel
	size_t getMaxChannel(){ return m_iMaxChannel; }
	// Get IP
	std::string getIP(){ return m_sIP; } 
	// Get Login Status (Unused)
	DeviceLoginStatus getLoginStatus(){ return m_eLoginStatus; } 

	// Chain of Responsibility Pattern
	void SetNextDevice(Device* pDev) { m_pNextDev = pDev; }
	Device* GetNextDevice() { return m_pNextDev; }
	
	NET_SDK_TYPE GetSDKType(){ return m_pVendor->GetSDKType(); }
	AbstractVendor* GetSDK(){ return m_pVendor; }

protected:
	RECORD_FILE_LIST GetRecordFileList(){ return m_pVendor->GetRecordFileList(); }
	
private:
	AbstractVendor* m_pVendor;
	Device* m_pNextDev;
	
	std::string m_sIP;
	size_t m_iPort;
	std::string m_sUserName;
	std::string m_sPassword;

	size_t m_iMaxChannel;

	long m_lLoginHandle;
	DeviceLoginStatus m_eLoginStatus;
};