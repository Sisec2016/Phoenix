#include "stdafx.h"
#include "LogUI.h"
#include "CalendarUI.h"
#include "CommDlg.h"

#include "Poco/Observer.h"
#include <Poco/NotificationCenter.h>

#include "NotificationNetworkStatus.h"
using Poco::NotificationCenter;
using Poco::Observer;

CLogUI::CLogUI()
{
	m_bInit = TRUE;
}

CLogUI::~CLogUI()
{
	NotificationCenter& nc = NotificationCenter::defaultCenter();
	nc.removeObserver(Observer<CLogUI, CNotificationNetworkStatus>(*this, &CLogUI::HandleNotificationNetworkStatus));
}

DUI_BEGIN_MESSAGE_MAP(CLogUI, WindowImplBase)
DUI_ON_CLICK_CTRNAME(BT_SearchLog, OnBeginSearch)
DUI_ON_CLICK_CTRNAME(BT_OnStartTime, OnSelectStartTime)
DUI_ON_CLICK_CTRNAME(BT_OnStopTime, OnSelectStopTime)
DUI_END_MESSAGE_MAP()

LPCTSTR CLogUI::GetWindowClassName() const
{
	return _T("CLogUI");
}

CDuiString CLogUI::GetSkinFolder()
{
	return _T("skin");
}

CDuiString CLogUI::GetSkinFile()
{
	return _T("xml\\LogUI.xml");
}

void CLogUI::OnFinalMessage(HWND hWnd)
{
	WindowImplBase::OnFinalMessage(hWnd);
}

void CLogUI::Notify(TNotifyUI& msg)
{
	if (m_bInit)
	{
		InitTime();
		m_bInit = FALSE;
	}
	if (msg.sType == DUI_MSGTYPE_CLICK)	{
		if (msg.pSender->GetName() == _T("LogType1")){
			CreateLogList();
		}
		if (msg.pSender->GetName() == _T("LogType2")){
			CreateCaseList();
		}
		if (msg.pSender->GetName() == _T("export")){
			exportLog();
		}
	}
	WindowImplBase::Notify(msg);
}

void CLogUI::InitWindow()
{
	NotificationCenter& nc = NotificationCenter::defaultCenter();
	nc.addObserver(Observer<CLogUI, CNotificationNetworkStatus>(*this, &CLogUI::HandleNotificationNetworkStatus));
}

void CLogUI::HandleNotificationNetworkStatus(CNotificationNetworkStatus* pNf)
{
	if (pNf == nullptr)
		return;
	if (pNf->name().compare("class CNotificationNetworkStatus"))
		return;

	NOTIFICATION_TYPE eNotify;
	eNotify = pNf->GetNotificationType();
	SetNetWorkState(eNotify);
}

void CLogUI::SetNetWorkState(NOTIFICATION_TYPE& eNotify)
{
	CControlUI* NetWorkUI = dynamic_cast<CControlUI*>(m_PaintManager.FindControl(_T("Network")));
	if (eNotify == Notification_Type_Network_status_Connect)
		NetWorkUI->SetBkImage(_T("skin/network_online.png"));
	else if (eNotify == Notification_Type_Network_status_Disconnect)
		NetWorkUI->SetBkImage(_T("skin/network_offline.png"));
}

void CLogUI::OnBeginSearch(TNotifyUI& msg)
{
	COptionUI* Option1 = static_cast<COptionUI*>(m_PaintManager.FindControl(_T("LogType1")));
	if (Option1->IsSelected())
	{
		OnSearchLog();
		InsertLogInfoToList();
	}
	else
	{
		OnSearchCaseLog();
		InsertCaseInfoToList();
	}
}

void CLogUI::OnSearchLog()
{
	m_LogInfo.clear();
	//Search Log infomaton
}

void CLogUI::OnSearchCaseLog()
{
	m_CaseInfo.clear();
	//Search case information
}

void CLogUI::CreateLogList()
{
	//create log list

	CDialogBuilder builder;
	CListUI* pList = static_cast<CListUI*>(m_PaintManager.FindControl(_T("domainlist")));

	CListUI* SubList = (CListUI*)(builder.Create(_T("xml//LogList.xml"), (UINT)0, NULL, &m_PaintManager));
	CVerticalLayoutUI* Lyt = static_cast<CVerticalLayoutUI*>(m_PaintManager.FindControl(_T("ListLyt")));
	Lyt->Remove(pList, true);
	Lyt->Add(SubList);
	
}

void CLogUI::CreateCaseList()
{
	//create case list
	CListUI* pList = static_cast<CListUI*>(m_PaintManager.FindControl(_T("domainlist")));
//	pList->RemoveAll();
	CDialogBuilder builder;
	CListUI* SubList = (CListUI*)(builder.Create(_T("xml//CaseList.xml"), (UINT)0, NULL, &m_PaintManager));
	CVerticalLayoutUI* Lyt = static_cast<CVerticalLayoutUI*>(m_PaintManager.FindControl(_T("ListLyt")));
	Lyt->Remove(pList, true);
	Lyt->Add(SubList);
}

void CLogUI::InsertLogInfoToList()
{
	//m_pList->RemoveAll();
	CListUI* pList = static_cast<CListUI*>(m_PaintManager.FindControl(_T("domainlist")));

	for (int i = 0; i < 10; i++)
	{
		CListTextElementUI* pListElement = new CListTextElementUI;
		pListElement->SetTag(i);
		pList->Add(pListElement);
		pListElement->SetAttribute(_T("font"), _T("1"));
		pListElement->SetFixedHeight(30);
		pListElement->SetText(0, _T("WHO1753"));
		pListElement->SetText(1, _T("�������"));
		pListElement->SetText(2, _T("100"));		
	}
	
	//for (UINT i = 0; i < m_LogInfo.size(); i++)
	//{
	//	CListTextElementUI* pListElement = new CListTextElementUI;
	//	pListElement->SetTag(i);
	//	m_pList->Add(pListElement);
	//	pListElement->SetFixedHeight(30);
	//	pListElement->SetText(0, m_LogInfo[i].Time.c_str());
	//	pListElement->SetText(1, m_LogInfo[i].Handle.c_str());
	//	pListElement->SetText(2, m_LogInfo[i].Description.c_str());
	//}
}

void CLogUI::InsertCaseInfoToList()
{
	CListUI* pList = static_cast<CListUI*>(m_PaintManager.FindControl(_T("domainlist")));
	TListInfoUI* List_Info = pList->GetListInfo();
	for (int i = 0; i < 10; i++)
	{
		CListTextElementUI* pListElement = new CListTextElementUI;
		pListElement->SetTag(i);
		pList->Add(pListElement);
		pListElement->SetFixedHeight(30);
		pListElement->SetText(0, _T("WHO1753"));
		pListElement->SetText(1, _T("�������"));
		pListElement->SetText(2, _T("100"));
		pListElement->SetText(3, _T("WHO1753"));
		pListElement->SetText(4, _T("�������"));
		pListElement->SetText(5, _T("100"));
		pListElement->SetText(6, _T("100"));
	}
}


void CLogUI::exportLog()
{
	TCHAR szBuffer[MAX_PATH] = { 0 };
	 
	OPENFILENAME  ofn = { 0 };
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = m_hWnd;
	ofn.lpstrFilter = _T("TXT�ļ�(*.txt)\0*.txt\0�����ļ�(*.*)\0*.*\0");//Ҫѡ����ļ���׺   
	ofn.lpstrInitialDir = _T("D:\\");//Ĭ�ϵ��ļ�·��   
	ofn.lpstrFile = szBuffer;//����ļ��Ļ�����   
	ofn.nMaxFile = sizeof(szBuffer) / sizeof(*szBuffer);
	ofn.nFilterIndex = 0;
	ofn.Flags = OFN_CREATEPROMPT | OFN_OVERWRITEPROMPT ;//��־����Ƕ�ѡҪ����OFN_ALLOWMULTISELECT  
	BOOL bSel = GetOpenFileName(&ofn);

}

void CLogUI::OnSelectStartTime(TNotifyUI& msg)
{
	std::auto_ptr<CalendarUI> pDlg(new CalendarUI);
	assert(pDlg.get());
	pDlg->Create(this->GetHWND(), NULL, UI_WNDSTYLE_EX_DIALOG, 0L, 0, 0, 350, 380);
	pDlg->CenterWindow();
	pDlg->ShowModal();
	STDSTRING strData = pDlg->GetData();
	CLabelUI* Lab_time = static_cast<CLabelUI*>(m_PaintManager.FindControl(_T("DatatimeText1")));
	Lab_time->SetText(strData.c_str());
	STDSTRING day = strData.substr(strData.length() - 2);
	SetBtDataImage(STDSTRING(_T("DataTime1")), day);
}

void CLogUI::OnSelectStopTime(TNotifyUI& msg)
{
	std::auto_ptr<CalendarUI> pDlg(new CalendarUI);
	assert(pDlg.get());
	pDlg->Create(this->GetHWND(), NULL, UI_WNDSTYLE_EX_DIALOG, 0L, 0, 0, 350, 380);
	pDlg->CenterWindow();
	pDlg->ShowModal();
	STDSTRING strData = pDlg->GetData();
	CLabelUI* Lab_time = static_cast<CLabelUI*>(m_PaintManager.FindControl(_T("DatatimeText2")));
	Lab_time->SetText(strData.c_str());
	STDSTRING day = strData.substr(strData.length() - 2);
	SetBtDataImage(STDSTRING(_T("DataTime2")), day);
}

void CLogUI::InitTime()
{
	::GetLocalTime(&m_sysTime);
	char strData[100] = { 0 };
	sprintf_s(strData, "%d-%02d-%02d", m_sysTime.wYear, m_sysTime.wMonth, m_sysTime.wDay);
	STDSTRING ShowData(strData);
	STDSTRING day = to_string(m_sysTime.wDay);

	SetBtDataImage(STDSTRING(_T("DataTime1")), day);
	SetBtDataImage(STDSTRING(_T("DataTime2")), day);

	CLabelUI* Lab_time1 = static_cast<CLabelUI*>(m_PaintManager.FindControl(_T("DatatimeText1")));
	CLabelUI* Lab_time2 = static_cast<CLabelUI*>(m_PaintManager.FindControl(_T("DatatimeText2")));
	Lab_time1->SetText(ShowData.c_str());
	Lab_time2->SetText(ShowData.c_str());
}

void CLogUI::SetBtDataImage(STDSTRING& BT_Name, STDSTRING& day)
{
	if (day[0] == '0')
		day = day.substr(1);
	char strValue[200] = { 0 };
	sprintf_s(strValue, _T("file='skin/Data/%s.png' dest='15,8,39,39'"), day.c_str());
	STDSTRING pictureInfo(strValue);
	CButtonUI* btn_data = static_cast<CButtonUI*>(m_PaintManager.FindControl(BT_Name.c_str()));
	btn_data->SetAttribute(_T("foreimage"), pictureInfo.c_str());
}
