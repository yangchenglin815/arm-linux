
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
    int LicType;//0 ���ԣ�1 ��ҵ
	int LicDays;//��Ȩ�������Բ�����Ȩ��Ч����ҵ��Ȩ��������Ȩ
	int LicDaysLeave;//��Ȩ�������Բ�����Ȩ��Ч����ҵ��Ȩ��������Ȩ
	char LicDate[100];//��Ȩ����
	char LicCompany[512];
	char LicRemark[512];//��Ȩ��ע
	
	
}KEYRESULT;

extern LINKKEY_API int nLinkkey;

LINKKEY_API int fnLinkkey(void);

LINKKEY_API int LoadLinkKEY(char*key,KEYRESULT*pResult);
LINKKEY_API int GetIpMac(char*ip,char*maccode);