#include "DZPLIBTEST.h"
#include "Poco/CppUnit/TestCaller.h"
#include "Poco/CppUnit/TestSuite.h"



DZPLIBTEST::DZPLIBTEST(const std::string& name) : CppUnit::TestCase(name)
{

}

DZPLIBTEST::~DZPLIBTEST()
{
}



void DZPLIBTEST::testlogin()
{
	DVR::DZPLite::DVRSessionImpl session("192.168.0.32:34567", 5000);
	session.login("admin", "");

 	/*DVR::DZPLite::Utility::TIMEINFO time1 = { 0 };
	time1.ch = 1;
	
	time1.stEndTime = _time64(NULL);
	struct tm *ptm = _localtime64(&time1.stEndTime);
	ptm->tm_mday--;
	time1.stBeginTime = _mktime64(ptm);
	DVR::DZPLite::Utility::FindFile(handle, time1, 5000);*/
	

	session.logout();
}

void DZPLIBTEST::testSession()
{
	std::cout << "test Session" << std::endl;
	int i = 0;
	assert(i > 0);
}

CppUnit::Test* DZPLIBTEST::suite()
{
	CppUnit::TestSuite* pSuite = new CppUnit::TestSuite("DZPLIBTEST");
	
	CppUnit_addTest(pSuite, DZPLIBTEST, testlogin);
	//CppUnit_addTest(pSuite, DZPLIBTEST, testSession);

	return pSuite;
}