// App.cpp : Defines the entry point for the application.
//
#include "stdafx.h"
#include "MainWnd.h"
#include "resource.h"

#include "portscan.h"
#include "QMFileSqlite.h"
#include "QMSqlite.h"

#include "SearchDevice.h"
#include "DeviceManager.h"

#include "JXJVendor.h"
#include "DZPVendor.h"
#include "DHVendor.h"
#include "HKVendor.h"

#include "ipset.h"

#include <fstream>

#include "MessagePump.h"

static VENDOR_LIST pVendorList;

void HideTaskBar()
{
	LPARAM lParam;
	lParam = ABS_AUTOHIDE | ABS_ALWAYSONTOP;
	HWND task = FindWindow(_T("Shell_TrayWnd"), NULL);
	::ShowWindow(task, SW_HIDE);

	APPBARDATA apBar;
	memset(&apBar, 0, sizeof(apBar));
	apBar.cbSize = sizeof(apBar);
	apBar.hWnd = task;
	if (apBar.hWnd != NULL)
	{
		apBar.lParam = lParam;
		SHAppBarMessage(ABM_SETSTATE, &apBar);
	}
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPSTR /*lpCmdLine*/, int nCmdShow)
{
	MessagePump pump;
	pump.start();

	CPaintManagerUI::SetInstance(hInstance);
	CPaintManagerUI::SetResourcePath(CPaintManagerUI::GetInstancePath() + _T("skins\\Min"));
	
	HRESULT Hr = ::CoInitialize(NULL);
	if (FAILED(Hr)) return 0;

	std::auto_ptr<CMainWnd> pFrame(new CMainWnd);
	assert(pFrame.get());
	pFrame->Create(NULL, NULL, UI_WNDSTYLE_DIALOG, WS_EX_WINDOWEDGE | WS_EX_ACCEPTFILES);
	pFrame->SetIcon(IDI_ICON1);
	pFrame->CenterWindow();
	pFrame->ShowWindow(true);

//	HideTaskBar();

	/************************* ��ʼ�����ݿ� **********************/
	//��ȡָ��
	fstream _file;
	_file.open("phoenix.db", ios::in);
	if (!_file)
	{
		QFileSqlite *pFileDb = QFileSqlite::getInstance();
		//ɾ����
		pFileDb->dropTable(DROP_LOGIN_DEVICE_INFO_TABLE);
		//������¼��
		pFileDb->createTable(CREATE_LOGIN_DEVICE_INFO_TABLE);
	}

	//��ȡָ��
	QMSqlite *pDb = QMSqlite::getInstance();
	//ɾ����
	pDb->dropTable(DROP_SEARCH_VIDEO_TABLE);
	//������¼��
	pDb->createTable(CREATE_SEARCH_VIDEO_TABLE);

	/************************* ��ʼ��SDK���� **********************/
	VENDOR_LIST pVendorList;
	CJXJVendor* jxjVendor = new CJXJVendor();
	//CDZPVendor* dzpVendor = new CDZPVendor();
	//DHVendor* dhVendor = new DHVendor();
	//HKVendor* hkVendor = new HKVendor();

	pVendorList.push_back(jxjVendor);
	//pVendorList.push_back(dzpVendor);
	/*	pVendorList.push_back(dhVendor);
	pVendorList.push_back(hkVendor);*/

	/************************* IP setting **************************/
	std::cout << CCommonUtrl::getInstance().GetCurTime() << "ip setting Start!" << std::endl;
	IPSet ipset;
	ipset.run();
	Sleep(5000);

	/************************* ��ʼ��IP�б� **********************/
	DEVICE_INFO_SIMPLE_LIST listDeviceSimpleInfo;
	//std::cout << CCommonUtrl::getInstance().GetCurTime() << "Scan Port Start!" << std::endl;
	//NotificationQueue queuePortScan;	
	//PortScan portScan(queuePortScan);
	////��ʼɨ��
	//ThreadPool::defaultPool().start(portScan);

	//while (true)
	//{
	//	Notification::Ptr pNf(queuePortScan.waitDequeueNotification());
	//	if (pNf)
	//	{
	//		ScanNotification::Ptr pWorkNf = pNf.cast<ScanNotification>();
	//		if (pWorkNf)
	//		{
	//			listDeviceSimpleInfo = CSearchDevice::GetDeviceInfoSimpleList();
	//			std::cout << CCommonUtrl::getInstance().GetCurTime() << "Scan Port Stop!" << std::endl;
	//			break;
	//		}
	//	}
	//}

	/************************* �豸��������� **********************/
	std::cout << CCommonUtrl::getInstance().GetCurTime() << "Search Device Start!" << std::endl;
	NotificationQueue queueSearchDevice; // �豸������Ϣ����
	CSearchDevice sd(pVendorList, listDeviceSimpleInfo, queueSearchDevice);
	ThreadPool::defaultPool().start(sd);
	//queueSearchDevice.enqueueNotification(new CNotificationSearchDevice(Notification_Type_Search_Device_Cancel));

	/************************* �豸��������� **********************/
	NotificationQueue queueDeviceManager; // �豸������Ϣ����
	CDeviceManager dm(pVendorList, queueDeviceManager);
	ThreadPool::defaultPool().start(dm);
	//queueDeviceManager.enqueueNotification(new CNotificationDeviceManager(Notification_Type_Device_Manager_Cancel));

	while (true)
	{
		Notification::Ptr pNf(NotificationQueue::defaultQueue().waitDequeueNotification());
		if (pNf)
		{
			CNotificationSearchDevice::Ptr pWorkNf = pNf.cast<CNotificationSearchDevice>();
			//CNotificationDeviceManager::Ptr pWorkNf = pNf.cast<CNotificationDeviceManager>();
			if (pWorkNf)
			{
				if (pWorkNf->GetNotificationType() == Notification_Type_Search_Device_Finish)
				{
					break;
				}
			}
		}
	}

	DEVICE_INFO_LIST devInfoList = CSearchDevice::GetDeviceInfoList();

	CPaintManagerUI::MessageLoop();

	::CoUninitialize();
	
	pump.stop();

	return 0;
}


