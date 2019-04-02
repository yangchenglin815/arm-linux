
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the LINKKEY_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// LINKKEY_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
#ifdef LINKKEY_EXPORTS
#define LINKKEY_API __declspec(dllexport)
#else
#define LINKKEY_API __declspec(dllimport)
#endif

// This class is exported from the linkkey.dll
class LINKKEY_API CLinkkey {
public:
	CLinkkey(void);
	// TODO: add your methods here.
};

typedef struct KEYRESULT
{
    int LicType;//0 测试，1 商业
	int LicDays;//授权天数，对测试授权有效。商业授权，永久授权
	int LicDaysLeave;//授权天数，对测试授权有效。商业授权，永久授权
	char LicDate[100];//授权日期
	char LicCompany[512];
	char LicRemark[512];//授权备注
	
	
}KEYRESULT;

extern LINKKEY_API int nLinkkey;

LINKKEY_API int fnLinkkey(void);

LINKKEY_API int LoadLinkKEY(char*key,KEYRESULT*pResult);
LINKKEY_API int GetIpMac(char*ip,char*maccode);