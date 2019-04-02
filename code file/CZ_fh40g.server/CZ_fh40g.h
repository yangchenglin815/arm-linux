

#if !defined(AFX_CLINKASERVER_H__15A555C8_15AD_46EF_982B_FB15F0709E46__INCLUDED_)
#define AFX_CLINKASERVER_H__15A555C8_15AD_46EF_982B_FB15F0709E46__INCLUDED_
#define  HDRLENGTHA 8
#define  HDRLENGTH 20



#define	DBTYPE_SQLSERVER	0 //
#define DBTYPE_ORACLE		1
#define DBTYPE_MYSQL		2

/*
#define SYSINFO_AGENT_FREE 1
#define SYSINFO_AGENT_YA 2
#define SYSINFO_AGENT_ONHOOK 3
#define SYSINFO_AGENT_OFFHOOK 4
#define SYSINFO_CALLOUT_NOFREECHAN 5
#define SYSINFO_SWITCH_SUCCESS 6
#define SYSINFO_SWITCH_DESTNOTFREE 7
#define SYSINFO_SWITCH_DESTINVALID 8
#define SYSINFO_AGENT_NOFREEVOICE 9
#define SYSINFO_CALLOUT_AGENTNOCALLOUTFLOW 10
#define SYSINFO_MUTEON_DESTHANGUP 11
#define SYSINFO_MUTEON_NOTINCONF 12
#define SYSINFO_MUTEON_SUCCESS 13
#define SYSINFO_MUTEOFF_DESTHANGUP 13
#define SYSINFO_MUTEOFF_NOTINCONF 14
#define SYSINFO_MUTEOFF_SUCCESS 14
#define SYSINFO_SPEAK_DESTINVALID 15
#define SYSINFO_SPEAK_SUCCESS 16
#define SYSINFO_EVENT_DESTHANGUP 17
#define SYSINFO_EVENT_NOTFLOW 18
#define SYSINFO_HZ_DESTHANGUP 19
#define SYSINFO_HZCANCEL_ERROR 20
#define SYSINFO_HZ_FAILED 21
#define SYSINFO_LISTEN_DESTINVALED 22
#define SYSINFO_LISTEN_SUCCESS 23
#define SYSINFO_BREAK_DESTINVALID 24
#define SYSINFO_BREAK_DESTHANGUP 25
#define SYSINFO_BREAK_SUCCESS 26
#define SYSINFO_BREAK_NOTINCONF 27
#define SYSINFO_LISTEN_NOTINCONF 28

*/

#define SYSINFO_WORK_STATE //示闲错误，状态错误
#define SYSINFO_YA_STATE //哑席错误，状态错误
#define SYSINFO_SWTICH_STATE //跳转错误，状态错误
#define SYSINFO_DIAL_STATE //外呼错误，状态错误
#define SYSINFO_SWITCH_CALLER //跳转错误，主叫通道不允许跳转
#define SYSINFO_DIAL_NOCHAN //外呼错误，无线路外呼
#define SYSINFO_ONOFF_OFCLOSE //摘挂机错误，常闭话机不支持
#define SYSINFO_ONOFF_LINE  //摘挂机错误，线号非法
#define SYSINFO_SWITCH_NOFLOW //跳转失败 无跳转流程
#define SYSINFO_EVENT_HANGUP //满意度失败,对方通道已挂机
#define SYSINFO_EVENT_NOCHAN //满意度失败,无流程
#define SYSINFO_HZ_HANGUP //呼转失败,对方通道已挂机
#define SYSINFO_HZ_ERROR //呼转失败,参数错误
#define SYSINFO_RECORD_OPENFILE //录音错误，打开文件失败
#define SYSINFO_DIAL_WLINEERROR //外呼错误，外线故障
#define SYSINFO_DIAL_INOUT //外呼错误，呼入呼出冲突
#define SYSINFO_RECORD_NOCONF //录音错误，无会议资源
#define SYSINFO_IP_CLOSE //IP通道话路关闭

#define MODULE_MAX 512
#define DBC_MAX 100

#define T_NET_USERJOIN  1
#define T_NET_USERQUIT  2
#define T_NET_BYANOTHER 3
#define T_NET_LINESTATEUPDATE 4

#define T_NET_MUTE   6
#define T_NET_LISTEN  7
#define T_NET_SWITCH 8
#define T_NET_BREAK 9
#define T_NET_REFRESH 10
#define T_NET_WORK 11
#define T_NET_YA 12
#define T_NET_HZ 13
#define T_NET_DIALOUT 14
#define T_NET_ONOFF 15
#define T_NET_EVENT 16


#define T_NET_LOADING_SID 30
#define T_NET_LOADING_LINENO 31
#define T_NET_LOADING_LEVEL 32
#define T_NET_LOADING_SUBLEVEL 33
#define T_NET_UPDATE_ACCOUNT 34
#define T_NET_AWAY    35
#define T_NET_TEST    36
#define T_NET_CALLIN  37

#define T_NET_RELOADING 39
#define T_NET_RELOADINFO 40


#define T_NET_REQUESTSERVICE 44
#define T_NET_DIALOUTNEW 45
#define T_NET_KEEPLIVE 46

#define T_NET_SYSINFO    48
#define T_NET_SPEAK      50
#define T_NET_REQUESTAGENT    52
#define T_NET_CALLOUT  53
#define T_NET_SENDEFAX  54
#define T_NET_DIALAGENTFA      55
#define T_NET_DIALAGENTFG     56
#define T_NET_SWITCHTOFA  57
#define T_NET_SWITCHTOFG  58
#define	T_NET_SWITCHTOBACK 59
#define T_NET_CALLREPORT 60
#define T_NET_SETCONFMODE 61
#define T_NET_HANGUPONE 62
#define T_NET_HANGUPALL 63
#define T_NET_HOLDOFF 64
#define T_NET_HOLDON 65
#define T_NET_VOIPUSERJOIN 101
#define T_NET_VOIPUSERJOINCONFIRM 102
#define T_NET_SENDDTMF 103
#define T_NET_SIPMESSAGE 104
#define T_NET_CONNECT 105
#define T_NET_FASTUSERJOIN 106
#define T_NET_CHANOPEN 107

#define LINESTATE_OFFHOOKNA -2 //摘即
#define LINESTATE_WAITOPEN -1 //没有安装
#define LINESTATE_XIABAN 99 //下班
#define LINESTATE_AWAY 17 //上班
#define LINESTATE_UNAVAILABLE 0 //未登录
#define LINESTATE_FREE 1 //空闲
#define LINESTATE_OFFHOOK 2// 摘机
#define LINESTATE_CALLIN 3 //用户呼入
#define LINESTATE_CALLOUT 4 //坐席呼出
#define LINESTATE_SELECT 5 //被选择
#define LINESTATE_CALLOUTOK 6// 外呼成功
#define LINESTATE_CALLOUTFAILED 7 //外呼失败
#define LINESTATE_USERHANGUP 8 //用户挂机
#define LINESTATE_CALLINOK 9 //呼入成功
#define LINESTATE_INCONF 10 //会议中
#define LINESTATE_SWITCH 11 //被跳转
#define LINESTATE_LISTEN 12
#define LINESTATE_BREAK 13 
#define LINESTATE_LITTLE 14
#define LINESTATE_YA 15
#define LINESTATE_SUSPAND 16
#define LINESTATE_MUTE 18

#define LINESTATE_SWITCHER 19 //跳转
#define LINESTATE_LISTENER 20 //监听
#define LINESTATE_HUZHUAN 21 //跳转
#define LINESTATE_HUZHUANOK 22 //监听
#define LINESTATE_SPEAKER 23 //强插



#define LOADERR_SYSTEM    -1
#define LOADERR_NONEXIST  1
#define LOADERR_PASSWORD  2
#define LOADERR_LINENO    3
#define LOADERR_IPCONFIG    4
#define LOADERR_VER    5
#define LOADERR_OK        0


struct LINE_INFO
{
	int m_nSktIndex;
};

typedef struct DBC_INFO 
{
	otl_connect		*m_db; // connect object
	int   m_nStatus;
}DBC_INFO;


typedef struct CFG{
	CTcpAsyncSocket tcp_client;
	int  m_nCheckUser;
	int  m_nDBType;
	int  m_nLoginCtrl;
	int  m_nCheckAcd;
	char m_sAppPath[512];
	char m_sIniPath[512];
	char m_sIniPathCLINKASERVER[512];
	int m_nTip;
	int m_nSrcTermNo;
	int m_nLogLine;
	char m_szServerIP[256];
	char m_szServerPort[256];
	int m_nPort;
	int m_nLines;
	char m_szDsn[256];
	char m_szUser[256];
	char m_szPwd[256];
	char m_szDialDsn[256];
	char m_szDialUser[256];
	char m_szDialPwd[256];
	char m_szCaller[256];
	char m_sLogTime[256];
	char m_sVer[100];
	char m_sVer2[100];
	char m_sOTL[200];
	
	int  m_nMessageId;
	FILE *g_fpLogFile;
	int m_iUnitID;
	int m_iCheckIP;
	int m_nRequestService;
	char		m_sIVRIP[256];/*keygoe 流程 ip*/
	char		m_sDBIP[256];/*keygoe 流程 ip*/
	char		m_sAGTIP[256];/*keygoe 流程 ip*/
	int			m_nIVRPort;
	int			m_nAGTPort;
	int			m_nDBPort;
	int			m_nMaxLogLine;
	int         m_nRequestMsg;
	int         m_nSearchAddr;
	int			m_keeplive ;
	int			m_keeplivealarm ;
	char        rcvbuf[10240];
	int			m_nDBConnNum;
	int			m_nTimerSeconds300;//5
	time_t		m_timer300;//5分钟定
	int			m_nIndex;//
	int			m_nNoticeID;//当前公告ID
	char		m_sIP[1024];
	char		m_sMacCode[1024];
	int         m_nLog;
}CFG;
int InitDB(int i);
void InitDBCfg();
int SearchDB();
void ReleaseDB(int i);
#define CHECKINDEX() \
	if(nDBIndex<0)\
{ \
	char s[1024];\
	sprintf(s,"错误：数据库连接已使用完");\
	LogMesg(-1,s);\
	return;\
}
#define CHECKINDEX0() \
	if(nDBIndex<0)\
{ \
	char s[1024];\
	sprintf(s,"错误：数据库连接已使用完");\
	LogMesg(-1,s);\
	return 0;\
}
#define CHECKINDEX1() \
	if(nDBIndex<0)\
{ \
	char s[1024];\
	sprintf(s,"错误：数据库连接已使用完");\
	LogMesg(-1,s);\
	return 1;\
}



class CDBIndex 
{
public:
	CDBIndex();
	~CDBIndex();
	int GetDBIndex();
	int m_nDBIndex ;
};


typedef struct NET_MESSHDR
{
	int   m_nMessLength;
	int   m_nMessType;

}NET_MESSHDR;

typedef struct NET_USERJOIN
{
	NET_MESSHDR m_stMHdr;
	int   m_nCmdResult;
	char  m_sCmdDesc[200];
	int   m_nUserId;
	int   m_nCompanyID;
	int   m_nLineNo;
	char  m_sID[100];
	char  m_sPwd[100];
	char  m_sName[100];
	int   m_nLevel;
	int   m_nStyle;
	char  m_sLevelName[100];
	int   m_nSubLevel;
	char  m_sSubLevelName[100];
	char  m_sExtension[100];
	int   m_nAuthMute;
	int   m_nAuthEvent;
	int   m_nAuthSwitch;
	int   m_nAuthListen;
	int   m_nAuthYa;
	int   m_nAuthBreak;
	int   m_nAuthDialOut;
	int   m_nAuthHz;
	int   m_nAuthInfo;
	int   m_nAuthState;
	int   m_nAuthSpeak;
	char  m_sVer[100];
	char  m_sState[100];
}NET_USERJOIN;





typedef struct NET_USERQUIT
{
	NET_MESSHDR m_stMHdr;
	int   m_nCmdResult;
	int   m_nLineNo;
	int   m_nLevel;
	char  m_sID[100];
}NET_USERQUIT;
typedef struct NET_BYANOTHER
{
	NET_MESSHDR m_stMHdr;
	int   m_nLineNo;
	int   m_nLevel;
	char  m_sID[100];
}NET_BYANOTHER;

typedef struct NET_LINESTATEUPDATE
{
	NET_MESSHDR m_stMHdr;
	int   m_nLineNo;
	char  m_sLineState[100];
	char  m_sCaller[100];
	char  m_sCalled[100];
	char  m_sOriCalled[100];
	char  m_sAddress[100];
}NET_LINESTATEUPDATE;

typedef struct NET_MUTE
{
	NET_MESSHDR m_stMHdr;
	int   m_nCmdResult;
	char  m_sCmdResult[200];
	int   m_nLineNo;
	int   m_nCode;
	char  m_sWaitFile[200];	
}NET_MUTE;
typedef struct NET_LISTEN
{
	NET_MESSHDR m_stMHdr;
	int   m_nCmdResult;
	char  m_sCmdResult[200];
	int   m_nLineNo;
	int   m_nDLineNo;
	char  m_sID[100];
	char  m_sDID[100];
	char  m_sCaller[100];
	char  m_sCallee[100];

}NET_LISTEN;
typedef struct NET_SPEAK
{
	NET_MESSHDR m_stMHdr;
	int   m_nCmdResult;
	char  m_sCmdResult[200];
	int   m_nLineNo;
	int   m_nDLineNo;
	char  m_sID[100];
	char  m_sDID[100];
	char  m_sCaller[100];
	char  m_sCallee[100];

}NET_SPEAK;
typedef struct NET_SWITCH
{
	NET_MESSHDR m_stMHdr;
	int   m_nCmdResult;
	char  m_sCmdResult[200];
	int   m_nLineNo;
	int   m_nDLineNo;
	char  m_sID[100];
	char  m_sDID[100];
	char  m_sCaller[100];
	char  m_sCallee[100];
	char  m_sWaitFile[1024];
}NET_SWITCH;
typedef struct NET_BREAK
{
	NET_MESSHDR m_stMHdr;
	int   m_nCmdResult;
	char  m_sCmdResult[200];
	int   m_nLineNo;
	int   m_nDLineNo;
	char  m_sID[100];
	char  m_sDID[100];
	char  m_sCaller[100];
	char  m_sCallee[100];
	
}NET_BREAK;



typedef struct NET_REFRESH
{
	NET_MESSHDR m_stMHdr;
	int m_nItemCount;
}NET_REFRESH;
typedef struct NET_WORK
{
	NET_MESSHDR m_stMHdr;
	int   m_nCmdResult;
	char  m_sCmdResult[200];
	int   m_nLineNo;

}NET_WORK;

typedef struct NET_CALLREPORT
{
	NET_MESSHDR m_stMHdr;
	int   m_nCmdResult;
	char  m_sCmdResult[200];
	int   m_nLineNo;
	int   m_nChanNo;//
	int   m_nChanType;//0 中继，1坐席
	char  m_szStatus[100];
	char  m_szAgentID[100];//要外呼工号
	char  m_szCaller[100];
	char  m_szCalled[100];
	char  m_szChanMobile[100];
	char  m_szConfName[100];
	char  m_szSeq[100];
	char  m_szData[100];

	
}NET_CALLREPORT;

typedef struct NET_YA
{
	NET_MESSHDR m_stMHdr;
	int   m_nCmdResult;
	char  m_sCmdResult[200];
	int   m_nLineNo;
	
}NET_YA;
typedef struct NET_HZ
{
	NET_MESSHDR m_stMHdr;
	int   m_nCmdResult;
	char  m_sCmdResult[200];
	int   m_nLineNo;
	int   m_nChanNo;//呼转通道号
	int   m_nLinkID;
	char  m_sCaller[200];
	char  m_sCallee[200];
	char  m_sHzCallee[200];
	char  m_sHzFlowName[200];
	
}NET_HZ;
typedef struct NET_DIALOUT
{
	NET_MESSHDR m_stMHdr;
	int   m_nChanNo;
	int   m_nLineNo;
	int   m_nLinkID;
	char  m_sCaller[100];
	char  m_sCallee[100];
	char  m_sOriCallee[100];
}NET_DIALOUT;
typedef struct NET_ONOFF
{
	NET_MESSHDR m_stMHdr;
	int   m_nCmdResult;
	char  m_sCmdResult[200];
	int   m_nLineNo;
	int   m_nOnOffCode;
}NET_ONOFF;

typedef struct NET_SETCONFMODE
{
	NET_MESSHDR m_stMHdr;
	int   m_nCmdResult;
	char  m_sCmdResult[200];
	int   m_nLineNo;
	int   m_nMode;
}NET_SETCONFMODE;
typedef struct NET_LINEEVENT
{
	NET_MESSHDR m_stMHdr;
	int   m_nCmdResult;
	char  m_sCmdResult[200];
	int   m_nLineNo;
	int   m_nLineEventCode;
	int   m_nOpedLineNo;
	char  m_sOpedAgentID[200];
	
}NET_LINEEVENT;


typedef  struct NET_LOADING_LINENO
{
	NET_MESSHDR m_stMHdr;
	int  m_nLineCount;
}NET_LOADING_LINENO;
typedef  struct NET_LOADING_LINENOITEM
{
	NET_MESSHDR m_stMHdr;
	int  m_nLineNo;
}NET_LOADING_LINENOITEM;
typedef  struct NET_LOADING_SID
{
	NET_MESSHDR m_stMHdr;
	int  m_nsIdCount;
}NET_LOADING_SID;
typedef  struct NET_LOADING_SIDITEM
{
	NET_MESSHDR m_stMHdr;
	char  m_sId[100];
	char  m_sName[100];
}NET_LOADING_SIDITEM;
typedef  struct NET_LOADING_LEVEL
{
	NET_MESSHDR m_stMHdr;
	int  m_nLevelCount;
}NET_LOADING_LEVEL;
typedef  struct NET_LOADING_LEVELITEM
{
	NET_MESSHDR m_stMHdr;
	int   m_nLevel;
	char  m_sLevel[100];
}NET_LOADING_LEVELITEM;
typedef  struct NET_LOADING_SUBLEVEL
{
	NET_MESSHDR m_stMHdr;
	int  m_nSubLevelCount;
}NET_LOADING_SUBLEVEL;
typedef  struct NET_LOADING_SUBLEVELITEM
{
	NET_MESSHDR m_stMHdr;
	int m_nSubLevel;
	char  m_sSubLevel[100];
}NET_LOADING_SUBLEVELITEM;


typedef  struct NET_UPDATE_ACCOUNT
{
	NET_MESSHDR m_stMHdr;
	int   m_nResult;
	char  m_sId[100];
	char  m_sOldPass[100];
	char  m_sNewPass[100];
}NET_UPDATE_ACCOUNT;

typedef  struct NET_TEST
{
	NET_MESSHDR m_stMHdr;
	int   m_nLineNo;
	char  m_sId[100];
}NET_TEST;
typedef  struct NET_CALLIN
{
	NET_MESSHDR m_stMHdr;
	int   m_nLineNo;
	int   m_nChanNo;
	int   m_nInfoID;
	int   m_nInfoData;
	int   m_nQHID;
	int   m_nConfMode;
	char  m_sId[100];
	char  m_sCaller[100];
	char  m_sCalled[100];
	char  m_sSeqNum[100];
	char  m_sConfData[200];
}NET_CALLIN;

typedef  struct NET_CALLOUT
{
	NET_MESSHDR m_stMHdr;
	int   m_nCmdResult;
	char  m_sCmdResult[200];
	int   m_nLineNo;
	int   m_nChanNo;
	int   m_nInfoID;
	int   m_nInfoData;
	int   m_nQHID;
	char  m_sId[100];
	char  m_sCaller[100];
	char  m_sCalled[100];
	char  m_sSeqNum[100];
	char  m_sConfData[200];
}NET_CALLOUT;


typedef  struct NET_RELOADING
{
	NET_MESSHDR m_stMHdr;
	int nResult;
}NET_RELOADING;
typedef struct NET_RELOADINFO
{
	NET_MESSHDR m_stMHdr;
	int   m_nUserId;
	int   m_nLineNo;
	char  m_sID[100];
	char  m_sPwd[100];
	char  m_sName[100];
	int   m_nLevel;
	int   m_nStyle;
	char  m_sLevelName[100];
	int   m_nSubLevel;
	char  m_sSubLevelName[100];
	int   m_nResult;
	char  m_sDes[100];
	char  m_sExtension[100];
	int   m_nAuthMute;
	int   m_nAuthEvent;
	int   m_nAuthSwitch;
	int   m_nAuthListen;
	int   m_nAuthYa;
	int   m_nAuthBreak;
	int   m_nAuthDialOut;
	int   m_nAuthHz;
	int   m_nAuthInfo;
	int   m_nAuthState;
	int   m_nAuthSpeak;
	char  m_sVer[100];
}NET_RELOADINFO;
typedef  struct NET_REDIALCALL
{
	NET_MESSHDR m_stMHdr;
	char  m_sRowID[100];
	char  m_sMobile[100];
	char  m_sWorkFlow[100];
	
}NET_REDIALCALL;


typedef struct NET_VOIPUSERJOIN
{
	NET_MESSHDR m_stMHdr;
	int   m_nCmdResult;
	char  m_sCmdDesc[200];
	int   m_nUserId;
	int   m_nCompanyID;
	int   m_nLineNo;
	char  m_sID[100];
	char  m_sPwd[100];
	char  m_sName[100];
	int   m_nLevel;
	int   m_nStyle;
	char  m_sLevelName[100];
	int   m_nSubLevel;
	char  m_sSubLevelName[100];
	char  m_sExtension[100];
	int   m_nAuthMute;
	int   m_nAuthEvent;
	int   m_nAuthSwitch;
	int   m_nAuthListen;
	int   m_nAuthYa;
	int   m_nAuthBreak;
	int   m_nAuthDialOut;
	int   m_nAuthHz;
	int   m_nAuthInfo;
	int   m_nAuthState;
	int   m_nAuthSpeak;
	char  m_sVer[100];
	
}NET_VOIPUSERJOIN;

typedef  struct NET_VOIPUSERJOINCONFIRM
{
	NET_MESSHDR m_stMHdr;
	int   m_nLineNo;
	
}NET_VOIPUSERJOINCONFIRM;

typedef  struct NET_CHANOPEN
{
	NET_MESSHDR m_stMHdr;
	int   m_nLineNo;
	
}NET_CHANOPEN;
typedef  struct NET_SENDDTMF
{
	NET_MESSHDR m_stMHdr;
	int   m_nCmdResult;
	char  m_sCmdResult[200];
	int   m_nLineNo;
	char  m_sDtmf[100];
	
}NET_SENDDTMF;
typedef  struct NET_REQUESTSERVICE
{
	NET_MESSHDR m_stMHdr;
	int   m_nRequstService;
}NET_REQUESTSERVICE;
typedef struct NET_DIALOUTNEW
{
	NET_MESSHDR m_stMHdr;
	int   m_nLineNo;
	int   m_nToLinkID;
	int   m_nID;
	char  m_sCaller[100];
	char  m_sCallee[100];
	char  m_sOriCallee[100];
	char  m_sFlowName[500];
	char  m_sCompanyID[100];
	char  m_sWorkFlow[100];
	char  m_sPrivateData[100];
	char  m_sImportTime[100];
	char  m_sImportFlag[100];
	int   m_nFlag;
	int   m_nChannelID;
	int   m_nItemCount;
	
}NET_DIALOUTNEW;
typedef  struct NET_KEEPLIVE
{	
	NET_MESSHDR m_stMHdr;
	int m_nKeepValue;
	
}NET_KEEPLIVE;

typedef struct NET_SYSINFO
{
	NET_MESSHDR m_stMHdr;
	int   m_nLineNo;
	int   m_nError;
	char  m_sError[500];
}NET_SYSINFO;
typedef struct NET_REQUESTAGENT
{
	NET_MESSHDR m_stMHdr;
	int   m_nLineNo;
	int   m_nChanNo;
	int   m_nType;
	int   m_nResult;
	int		m_nInfoID;
	int		m_nInfoData;
	char m_sCaller[100];
	char m_sCallee[100];
	char m_sOriCallee[100];
}NET_REQUESTAGENT;
typedef struct NET_DIALAGENTFA
{
	NET_MESSHDR m_stMHdr;
	int   m_nLineNo;
	int   m_nResult;
	char  m_sFlwName[100];
	char  m_sDialAgentID[100];
}NET_DIALAGENTFA;
typedef struct NET_DIALAGENTFG
{
	NET_MESSHDR m_stMHdr;
	int   m_nLineNo;
	int   m_nLevel;
	int   m_nSubLevel;
	int   m_nResult;
	char  m_sFlwName[100];
	char  m_sDialAgentID[100];

}NET_DIALAGENTFG;



typedef struct NET_SENDEFAX
{
	NET_MESSHDR m_stMHdr;
	int   m_nChanNo;
	int   m_nLineNo;
	int   m_nResult;
	char  m_sResult[500];
	char  m_sFaxFile[500];
	
}NET_SENDEFAX;


typedef struct NET_SWITCHTOFA
{
	NET_MESSHDR m_stMHdr;
	int   m_nCmdResult;
	char  m_sCmdResult[200];
	int   m_nLineNo;
	int   m_nChanNo;
	int   m_nResult;
	char  m_sFlwName[100];
	char m_sSwitchID[100];
}NET_SWITCHTOFA;
typedef struct NET_SWITCHTOFG
{
	NET_MESSHDR m_stMHdr;
	int   m_nCmdResult;
	char  m_sCmdResult[200];
	int   m_nLineNo;
	int   m_nChanNo;
	int   m_nLevel;
	int   m_nSubLevel;
	int   m_nResult;
	char  m_sFlwName[100];
	char m_sSwitchID[100];
}NET_SWITCHTOFG;

typedef struct NET_SWITCHTOBACK
{
	NET_MESSHDR m_stMHdr;
	int   m_nCmdResult;
	char  m_sCmdResult[200];
	int   m_nLineNo;
	int   m_nDLineNo;
	int   m_nResult;
}NET_SWITCHTOBACK;

typedef struct NET_HANGUPONE
{
	NET_MESSHDR m_stMHdr;
	int   m_nCmdResult;
	char  m_sCmdResult[200];
	int   m_nLineNo;
	int   m_nDLineNo;
}NET_HANGUPONE;

typedef struct NET_HANGUPALL
{
	NET_MESSHDR m_stMHdr;
	int   m_nCmdResult;
	char  m_sCmdResult[200];
	int   m_nLineNo;
	
}NET_HANGUPALL;

typedef struct NET_HOLDOFF
{
	NET_MESSHDR m_stMHdr;
	int   m_nCmdResult;
	char  m_sCmdResult[200];
	int   m_nLineNo;
	int   m_nDLineNo;
}NET_HOLDOFF;

typedef struct NET_HOLDON
{
	NET_MESSHDR m_stMHdr;
	int   m_nCmdResult;
	char  m_sCmdResult[200];
	int   m_nLineNo;
	int   m_nDLineNo;
	
}NET_HOLDON;

struct SKT_CLIENT_INFO 
{
	
	unsigned char m_szRecvBuf[10240];//'' socket数据
	unsigned char m_szSendBuf[10240];//'' socket数据
	CTcpAsyncSocket skt_client;
	time_t		 m_keeplivetime;
	
	char			 m_sTermNo[100];//终端编号
	char		 m_sSerialNo[100]; //任务序号
	int          m_nBorrowFlag;//
	char		 m_sBorrowerip[100];
	char		 m_sBorrowerport[100];
	char         m_sID[100];
	char         m_sName[100];
	char         m_sPeerAddress[100];
	char         m_sPort[100];
	char		 m_sNotice[1024];
	int			 m_nKeepSeconds ;
	char		 m_sTestMan[100];
	char		 m_sPhone[100];//
	char		 m_sTermName[100];
	DList*			 recv_dlist ;
	DList*			 send_dlist ;
	time_t			m_lastsendtime;
	int				m_nownerflag;
	int			 m_seqnum;//数据id
	int          m_id;//历史id
	char			m_nTaskName[100];
	char            m_nTaskID[100];
	char			 m_nTermID[100];//终端ID
	int			m_gpsflag;
	int         count;
	int         count1;
	int         count2;
	
}SKT_CLIENT_INFO;


typedef struct {
    double lng;
    double lat;
} Location;

struct ACD_INFO 
{
	int			 m_nRequest;
}ACD_INFO;

struct Q850ERRORINFO
{
	char m_sReason[100];
	char m_sFinishCode[100];
};

void  LogErrorSysInfo(int errtype,char*pInfo);
void LogMesg(int nIndex,const char *szLogMesg);
void Sql_UpdateSocketInfo(int nIndex);

void  GetMessName(int nState,char*state);
void Sql_Updatelinkagent(int nIndex);
void Sql_Deletelinkagent(int nIndex);

void SendCCCount(int nIndex);


void  CheckState();
void CheckRequestService();
int   CheckPeerAddress(char* sPeerAddress);

void Sql_InsertLog_Logout(int nUserId);
void Sql_DeleteAgentInfo(int nIndex);
void Sql_UpdateAgentInfo(int nIndex);
void Sql_InsertLog_Login(int nUserId);
void Sql_InsertAgentInfo(int nIndex);
void Sql_InsertMusicSendInfo(int nIndex,int nCmd);
void Sql_BakSocketInfo(int nIndex);

void NET_SetConfMode_Send(int nIndex,int nResult,char*sResult,int nMode);
int  GetLineNoByAttach(int nIndex);
int  CheckUser(int nIndex ,int nLineAttach );
int  VoipCheckUser(int nIndex);



int  CheckAuth(int nIndex);
int  CheckSubLevel(int nIndex);
void Sql_InsertVoipAgentInfo(int nIndex);

void NET_Reloading_Send(int nIndex);
void NET_UserJoin_Send(int nIndex);
void NET_UserJoin_Recv(int nIndex);
void NET_KeepLive_Send(int nIndex);
void NET_VoipUserJoin_Send(int nIndex);
void NET_VoipUserJoin_Recv(int nIndex);
void NET_ReloadInfo_Recv(int nIndex);
void NET_ReloadInfo_Send(int nIndex);


int  FastCheckUser(int nIndex);
int  cclinestateupdate(int nIndex);
int   proclinestate(int nIndex);
int   proclinestate_onlystate(int nLineNo,char *sID,char*sLineState,int nLineState,char*sCaller,char*sCallee);
void NET_SysInfo_Send(int nIndex,int nError,char*sError);
void NET_Refresh_Send( );

void NET_ReloadInfo_Send(int nIndex);
void NET_SendDtmf_Recv(int nIndex);

void NET_FastUserJoin_Recv(int nIndex);
void NET_FastUserJoin_Send(int nIndex);

void NET_Work_Recv(int nIndex);
void NET_Work_Send(int nIndex,int nResult,char*sResult);

void NET_SendDtmf_Send(int nIndex,int nResult,char*sResult);
void NET_Listen_Recv(int nIndex);
void NET_Listen_Send(int nIndex,int nResult,char*sResult);
void NET_Break_Recv(int nIndex);
void NET_Break_Send(int nIndex,int nResult,char*sResult);
void NET_Speak_Recv(int nIndex);
void NET_Speak_Send(int nIndex,int nResult,char*sResult);
void NET_Mute_Recv(int nIndex);
void NET_Mute_Send(int nIndex,int nResult,char*sResult);
void NET_YA_Recv(int nIndex);
void NET_YA_Send(int nIndex,int nResult,char*sResult);
void NET_Event_Recv(int nIndex);
void NET_Event_Send(int nIndex,int nResult,char*sResult);
void NET_Switch_Recv(int nIndex);
void NET_SwitchToFa_Recv(int nIndex);
void NET_SwitchToFg_Recv(int nIndex);
void NET_SwitchToBack_Recv(int nIndex);
void NET_Switch_Send(int nIndex,int nResult,char*sResult);
void NET_HZ_Recv(int nIndex);
void NET_HZ_Send(int nIndex,int nResult,char*sResult,int nChanNo);
void NET_SwitchToFa_Send(int nIndex,int nChanNo,int nResult,char*sResult,char*sSwitchID);
void NET_SwitchToFg_Send(int nIndex,int nChanNo,int nResult,char*sResult,char*sSwitchID);
void NET_SwitchToBack_Send(int nIndex,int nResult,char*sResult);
void NET_OnOff_Send(int nIndex,int nResult,char*sResult,int ncode);

void NET_CallReport_Send(int nIndex,int nChan,int nChanType,char*sCaller,char*sCallee,char*sChanMobile,char*sStatus,char*sConfName,int nResult,char*sResult,char*sData);
void NET_UserQuit_Recv(int nIndex);
void NET_UserQuit_Send(int nIndex);
void NET_HangUpOne_Send(int nIndex,int nResult,char*sResult);
void NET_HangUpAll_Send(int nIndex,int nResult,char*sResult);

void NET_RequestAgent_Recv(int nIndex);


void NET_DialOut_Recv(int nIndex);
void NET_DialOutNew_Recv(int nIndex);
void NET_DialAgentFg_Recv(int nIndex);
void NET_DialAgentFa_Recv(int nIndex);

void NET_OnOff_Recv(int nIndex);


void NET_UpdateAccount_Recv(int nIndex);

void NET_CallIn_Send(int nIndex,int nChanNo,char*sCaller,char*sCalled,int nInfoID,int nInfoData,int nQHID,char*sSeqNum,int nConfMode,char*sConfData);
void NET_CallOut_Send(int nIndex,int nChanNo,char*sCaller,char*sCalled,int nInfoID,int nInfoData,int nQHID,char*sSeqNum,int nCmdResult,char*sCmdResult,char*sConfData);
void NET_RequestAgent_Send(int nIndex,int nChanID,int nType,int nInfoID,int nInfoData,char*Caller,char*Callee,char*OriCallee);
int   GetUserIDFromAgentID(char *sId);

void NET_VoipUserJoinConfirm_Send(int nIndex);
void NET_ChanOpen_Send(int nIndex);
void NET_LineStateUpdate_Send(int nIndex,NET_LINESTATEUPDATE *lsu);
void NET_LineStateUpdate_Send(NET_LINESTATEUPDATE *lsu);
void NET_RequestService_Send(int nCount);
void NET_ByAnother_Send(int nIndex);

void NET_SendEFax_Recv(int nIndex);
void NET_SendFax_Send(int nIndex,int nResult,char*sResult);

void NETIVR_OnOff_Send(int nIndex);
void NETIVR_SendDtmf_Send(int nIndex);
void NETIVR_Mute_Send(int nIndex);
void NETIVR_Listen_Send(int nIndex);
void NETIVR_Speak_Send(int nIndex);
void NETIVR_Break_Send(int nIndex);
void NETIVR_Switch_Send(int nIndex);
void NETIVR_DialOut_Send(int nIndex);
void NETIVR_HZ_Send(int nIndex);
void NETIVR_Event_Send(int nIndex);
void NETIVR_SwitchToFa_Send(int nIndex,char*szAgentID);
void NetIVR_TrunkSelect_Send(int nLineNo,int nChanNo,char*AgentID,int nFaOrFg,int nJumpOrSwitch);
void NETIVR_AgentUpdateState_Send();
void NETIVR_AgentUpdateState_Send(int nIndex,char*sState,int nLineState);
void NETIVR_RequestAgent(int nIndex,int nChan,int nLine,int nResult);
void NETIVR_SendEFax_Send(int nIndex);
void NETIVR_SwitchToFg_Send(int nIndex,int nLevel,int nSubLevel);
void NETIVR_SwitchToBack_Send(int nIndex,int nDLineNo);
void NETIVR_HangUpOne(int nIndex,int nLine,int nDLineNo);
void NETIVR_HangUpAll(int nIndex,int nLine);
void NET_HangUpOne_Recv(int nIndex);
void NET_HangUpAll_Recv(int nIndex);
void NETIVR_HoldOff(int nIndex,int nLine,int nDLineNo);
void NETIVR_HoldOn(int nIndex,int nLine,int nDLineNo);
void NET_HoldOn_Recv(int nIndex);
void NET_HoldOff_Recv(int nIndex);
void NET_HoldOn_Send(int nIndex,int nResult,char*sResult);
void NET_HoldOff_Send(int nIndex,int nResult,char*sResult);
int  GetLineNo(int nIndex,char* sIP);
int  SaveAgentTime(int nIndex,int sec);
int   CheckUpdate();
int  Checkq850info();
void Sql_Insertlinkagent(int nIndex);
void DeleteAllUser();
void do_connect();
int tcpclient_receivedata();
BOOL tcpclient_receive();
void tcpclient_proc();
int   tcpclient_ivrmsg(PkgHdr *pRcvPkgHdr);
int RecvFromClient(int nIndex);
void SetTimeInterval(TimeInterval &stPtval);
TimeInterval GetTimeInterval(TimeInterval &stPtval);
void NETIVR_SetConfMode_Send(int nIndex,int nMode);

void NET_SetConfMode_Recv(int nIndex);
long  GetStateSeconds(int nIndex);
void SetStateTime(int nIndex);
int  GetLineNoBySID(char* DSID);
int  CheckCtrl(int nIndex);

void UpdateGPS(char lng,char lat,char& mlng,char& mlat);
//int NetSet_Send(int nIndex,void*data,int datalen);
int hdrDecode(const char *pszPDU, PkgHdr *pMsg);
#if defined(WIN32)
UINT  __stdcall  ThreadProc(LPVOID lpParam);
#else
void * ThreadProc(void * lpParam);
#endif
#endif