#if !defined (_NETPUBSTR_H_)
#define _NETPUBSTR_H_

/*以下通用包数据定义*/
#define		MAX_PKG_LEN		4080
#define		MAX_HDR_LEN		17	


/*以下模块类型定义*/
#define		M_CTI		1/*cti 模块*/
#define		M_MSI		2/*msi 模块*/
#define		M_FAX		3/*fax 模块*/
#define		M_CSL		4/*console 模块*/
#define		M_SS7		5/*ss7 模块*/
#define		M_AGT		6/*agent ocx 模块*/
#define		M_IVR		7/*ivr 模块*/
#define		M_FSR		8/*fax server 模块*/
#define		M_ASR		9/*asr 模块*/
#define		M_SQL		10/*sql 模块*/
#define		M_TTS		11/*sql 模块*/
#define		M_EVT		12/*sql 模块*/
/* 以下通用结构定义 */

/*网络地址结构*/
typedef struct 
{
	u_char m_cContryNo;//国家号
	u_char m_cProvinceNo;//省份号
	u_char m_cCityNo;//城市号
	u_char m_cDepartNo;//单位号
	u_char m_cTermType;//模块类型
	u_char m_cTermNo;//模块号
}NetAddr;

/*网络包头结构*/
typedef struct
{
	u_int  m_cPkgLen;
	u_int  m_nMsgType;
	u_int  m_nSendModType;//模块类型
	u_int  m_nRecvModType;//模块类型
	u_int  m_nPkgType;
}PkgHdr;
typedef struct
{
      u_int m_nSec;
	  u_int m_nuSec;
}TimeInterval;


/*ivr 发给sql gateway*/
#define NET_IVR_SQL_SQLSELECTREQ		840
#define NET_IVR_SQL_SQLSELECTRESULT		841
#define NET_IVR_SQL_SQLCOMMANDREQ		842
#define NET_IVR_SQL_SQLCOMMANDRESULT	843
#define NET_IVR_SQL_SQLEXECCALLREQ 687
#define NET_IVR_SQL_SQLEXECCALLRESULT 688

#define NET_AGT_IVR_LISTENAGENT 873
#define NET_AGT_IVR_BREAKAGENT 874
#define NET_AGT_IVR_SWITCHAGENT 876
#define NET_AGT_IVR_MUTEAGENT  889
#define	NET_AGT_IVR_AGENTEVENTPROC	 894

#define NET_AGT_IVR_INTERSERVICE 667
#define NET_AGT_IVR_TRUNKHZ 671
#define NET_IVR_TTS_TTSREQ  674
#define NET_AGT_IVR_ONOFFHOOK 675
#define NET_AGT_IVR_ADIALOUT 676
#define NET_IVR_TTS_SYNTHPICTEXTREQ 677
#define NET_IVR_AGT_AGENTLOAD 678
#define NET_AGT_IVR_AGENTUPDATESTATE 679
#define NET_IVR_AGT_USERCALLIN 681
#define NET_IVR_AGT_USERCALLOUTOK 682
#define NET_AGT_IVR_VOIPDTMF 683
#define NET_IVR_AGT_SYSINFO  684
#define NET_AGT_IVR_SPEAKAGENT 685
#define NET_EVT_IVR_LINKEVENT 686

#define NET_IVR_EVT_SENDUSSD 689
#define NET_IVR_AGT_REQUESTAGENT 690
#define NET_IVR_AGT_USERCALLOUT 691
#define NET_AGT_IVR_SENDEFAX 692
#define NET_IVR_EVT_USSDRESULT 693
#define NET_IVR_AGT_LINESTATE 694
#define NET_AGT_IVR_SWITCHTOFA 695
#define NET_AGT_IVR_SWITCHTOFG 696
#define NET_AGT_IVR_SWITCHTOBACK 697
#define NET_AGT_IVR_MUSICSENDINFO 698
#define NET_IVR_AGT_CALLREPORT  699
#define NET_AGT_IVR_SETCONFMODE 700
#define NET_IVR_AGT_CHANCLOSE 701
#define NET_AGT_IVR_HANGUPONE 702
#define NET_AGT_IVR_HANGUPALL 703
#define NET_AGT_IVR_HOLDOFF 704
#define NET_AGT_IVR_HOLDON 705
#define NET_IVR_AGT_DIALAGENTFA 706
#define NET_IVR_AGT_DIALAGENTFG 707
#define NET_IVR_AGT_CHANOPEN 708
/*以下各种结构体的定义*/



/*跳转结构体*/
typedef struct{
	TimeInterval m_stPtval;
	int m_nChan;
	int m_nLine;
	int m_nEventCode;
	int m_nOpedLineNo;
	char m_szOpedAgentID[200];
}AGENTEVENT;


/*数据库结果结构体*/
typedef struct {
	TimeInterval m_stPtval;
	u_int m_nChan;//ivr中的通道号码
	u_int m_nConnID;//知道连接ID就知道使用什么连接了
	u_int m_nMsgID;
	u_int m_nSrcID;
	u_int  m_nFieldCols;//列数据类型,0结束1字符串2整型
	#define FIELDNAMELEN	200
	#define FIELDVALUELEN	500
	u_char m_szFieldName[FIELDNAMELEN];//列名
	u_char m_szFieldValue[FIELDVALUELEN];//列值
	u_int  m_nFieldValue;
	u_char m_cRetCode;//0失败，1成功
	
}SQLSELECTRESULT;
/*数据库请求结构体*/
typedef struct {
	TimeInterval m_stPtval;
	u_int m_nChan;//ivr中的通道号码
	u_int m_nConnID;//知道连接ID就知道使用什么连接了
	u_int m_nMsgID;
	u_int m_nSrcID;
	#define SQLLEN	1024

	u_char m_szSQL[SQLLEN];//SQL语句
	u_char m_cRetCode;//0失败，1成功

}SQLSELECTREQ;
typedef struct {
	TimeInterval m_stPtval;
	u_int  m_nChan;//ivr中的通道号码
	u_int m_nConnID;//知道连接ID就知道使用什么连接了
	u_int m_nMsgID;
	u_int	m_nSrcID;
	#define SQLERRLEN	300
	#define SQLLEN	1024
	u_char m_szSQLError[SQLERRLEN];//错误描述
	u_char m_szSQL[SQLLEN];//SQL限制500个字符
	u_char m_cAffectedRows;
	u_char m_cRetCode;//0失
	
}SQLCOMMANDRESULT;
/*数据库请求结构体*/
typedef struct {
	TimeInterval m_stPtval;
	u_int m_nChan;//ivr中的通道号码
	u_int m_nConnID;//知道连接ID就知道使用什么连接了
	u_int m_nMsgID;
	#define SQLLEN	1024
	u_char m_szSQL[SQLLEN];//SQL语句
	u_char m_cRetCode;//0失
	
}SQLCOMMANDREQ;
typedef struct
{
	int  m_nParaWay;
	char m_szPara[200];
}SQLPARA;
typedef struct {
	TimeInterval m_stPtval;
	u_int m_nChan;//ivr中的通道号码
	u_int m_nConnID;//知道连接ID就知道使用什么连接了
	u_int m_nMsgID;
	u_int m_nSrcID;
	u_int m_nParaCount;

	SQLPARA m_stSqlPara[10];
#define SQLLEN	1024
	u_char m_szSQL[SQLLEN];//SQL语句
	u_char m_cRetCode;//0失
	
}SQLEXECCALLREQ;

typedef struct {
	TimeInterval m_stPtval;
	u_int m_nChan;//ivr中的通道号码
	u_int m_nConnID;//知道连接ID就知道使用什么连接了
	u_int m_nMsgID;
	u_int m_nSrcID;
	u_int  m_nFieldCols;//列数据类型,0结束1字符串2整型
#define FIELDNAMELEN	200
#define FIELDVALUELEN	500
	u_char m_szFieldName[FIELDNAMELEN];//列名
	u_char m_szFieldValue[FIELDVALUELEN];//列值
	u_int  m_nFieldValue;
	u_char m_cRetCode;//0失败，1成功
	
}SQLEXECCALLRESULT;







/*发送给坐席的摘机请求*/
typedef struct {
	TimeInterval m_stPtval;
	u_int m_nChan;//通道号码
	u_int m_nLine;//呼叫id
	u_int m_nInfoID;
	u_int m_nInfoData;
	u_int m_nQHID;
	u_char m_szCalled[20];
	u_char m_szUserNum[20];//主叫号码
	u_char  m_cRetCode;//成功或失败 1为成功，0为失败
	u_char  m_sSessID[50];
	u_char  m_sSeqNum[50];
	u_int   m_nConfMode;
	u_char  m_sConfData[200];
}USERCALLIN;

/*发送给坐席的摘机请求*/
typedef struct {
	TimeInterval m_stPtval;
	int m_nResult;
	char m_szResult[500];
	u_int m_nChan;//通道号码
	u_int m_nLine;//呼叫id
	u_int m_nInfoID;
	u_int m_nInfoData;
	u_int m_nQHID;
	u_char m_szCalled[20];
	u_char m_szUserNum[20];//主叫号码
	u_char  m_cRetCode;//成功或失败 1为成功，0为失败
	u_char  m_sSeqNum[50];
	u_char  m_sConfData[200];
}USERCALLOUT;




typedef struct{
	TimeInterval m_stPtval;
	u_int	m_nLine;//获取的线号 -1是表示坐席都在忙，得不到空闲线号
	u_int	m_nChan;//ivr通道号码
	u_int	m_nDestLine;//获取的线号 -1是表示坐席都在忙，得不到空闲线号
	u_int	m_nLineLevel;//线号级别 是班长还是话务员
	u_char m_szAgentID[20];
	u_int	m_nResult;//获取的线号 -1是表示坐席都在忙，得不到空闲线号
	u_char m_szCallerNum[20];//主叫号码
	u_char m_szCalledNum[20];//主叫号码
	u_char m_szResult[500];//主叫号码
	u_char m_cRetCode;//成功或失败
}SWITCHAGENT;



typedef struct{
	TimeInterval m_stPtval;
	u_int	m_nLine;//ivr通道号码
	u_int   m_nChan;
	u_int	m_nDestLine;//获取的线号 -1是表示坐席都在忙，得不到空闲线号
	u_int	m_nResult;//获取的线号 -1是表示坐席都在忙，得不到空闲线号
	u_char m_szCallerNum[20];//主叫号码
	u_char m_szCalledNum[20];//主叫号码
	u_char m_szResult[500];//主叫号码
	u_char m_cRetCode;//成功或失败
	
}LISTENAGENT;

typedef struct{
	TimeInterval m_stPtval;
	u_int	m_nLine;//ivr通道号码
	u_int   m_nChan;
	u_int	m_nResult;//获取的线号 -1是表示坐席都在忙，得不到空闲线号
	u_char m_szFaxFile[300];//主叫号码
	u_char m_szResult[500];//主叫号码
	u_char m_cRetCode;//成功或失败
	
}SENDEFAXAGENT;
typedef struct{
	TimeInterval m_stPtval;
	u_int	m_nLine;//ivr通道号码
	u_int   m_nChan;
	u_int	m_nDestLine;//获取的线号 -1是表示坐席都在忙，得不到空闲线号
	u_int	m_nResult;//获取的线号 -1是表示坐席都在忙，得不到空闲线号
	u_char m_szCallerNum[20];//主叫号码
	u_char m_szCalledNum[20];//主叫号码
	u_char m_szResult[500];//主叫号码
	u_char m_cRetCode;//成功或失败
}SPEAKAGENT;
typedef struct{
	TimeInterval m_stPtval;
	u_int	m_nLine;//ivr通道号码
	u_int	m_nDestLine;//获取的线号 -1是表示坐席都在忙，得不到空闲线号
	u_int   m_nChan;
	u_int	m_nResult;//获取的线号 -1是表示坐席都在忙，得不到空闲线号
	u_char m_szCallerNum[20];//主叫号码
	u_char m_szCalledNum[20];//主叫号码
	u_char m_szResult[500];//主叫号码
	u_char m_cRetCode;//成功或失败
}BREAKAGENT;


typedef struct{
	TimeInterval m_stPtval;
	u_int	m_nLine;//ivr通道号码
	u_int   m_nChan;
	u_int	m_nResult;//获取的线号 -1是表示坐席都在忙，得不到空闲线号
	u_char m_szResult[500];//主叫号码
	u_char m_cRetCode;//成功或失败
	u_char m_szSwitchID[100];//要调整的工号
}SWITCHTOFA;

typedef struct{
	TimeInterval m_stPtval;
	u_int	m_nLine;//ivr通道号码
	u_int   m_nChan;
	u_int	m_nResult;//获取的线号 -1是表示坐席都在忙，得不到空闲线号
    u_int   m_nLevel;
	u_int   m_nSubLevel;
	u_char m_szResult[500];//主叫号码
	u_char m_cRetCode;//成功或失败
	u_char m_szSwitchID[100];

}SWITCHTOFG;
typedef struct{
	TimeInterval m_stPtval;
	u_int	m_nLine;//ivr通道号码
	u_int   m_nDLineNo;
	u_int   m_nChan;
	u_int	m_nResult;//获取的线号 -1是表示坐席都在忙，得不到空闲线号
	u_char m_szResult[500];//主叫号码
	u_char m_cRetCode;//成功或失败
}SWITCHTOBACK;

typedef struct{
	TimeInterval m_stPtval;
	u_int	m_nLine;//ivr通道号码
	u_int   m_nMode;
	u_int	m_nResult;//获取的线号 -1是表示坐席都在忙，得不到空闲线号
	u_char m_szResult[500];//主叫号码
	u_char m_cRetCode;//成功或失败
}SETCONFMODE;

typedef struct{
	TimeInterval m_stPtval;
	u_int	m_nLine;//ivr通道号码
	u_int   m_nChan;
	u_int	m_nCode;
	u_int	m_nResult;//获取的线号 -1是表示坐席都在忙，得不到空闲线号
	u_char m_cRetCode;//成功或失败
	u_char m_szWaitFile[200];
	u_char m_szResult[500];//主叫号码
		
}MUTEAGENT;

typedef struct 
{
	TimeInterval m_stPtval;
	u_int	m_nLine;//ivr通道号码
	u_char  m_sID[100];

}CHANCLOSE;

typedef struct 
{
	TimeInterval m_stPtval;
	u_int   m_nType;
	u_int	m_nLine;//ivr通道号码
	u_char  m_sID[100];
}CHANOPEN;

typedef struct
{
	TimeInterval m_stPtval;
	u_int  m_nChan;
	u_int  m_nFlag;//0
	u_char m_szCallerNum[100];//主叫号码
	u_char m_szCalledNum[100];//主叫号码
	u_char m_szOriCalledNum[100];
	u_char m_szAddress[100];
	u_int  m_nResult;
	u_char m_cRetCode;
}
REQUESTSERVICE;
typedef struct
{
	TimeInterval m_stPtval;
	u_int  m_nTermType;
	u_int  m_nLineNo;
	u_int  m_nChan;

	u_int  m_nFaOrFg;
	u_int  m_nJumpOrSwitch;
	u_char m_szAgentID[100];
	u_char m_szAddress[100];
	u_int  m_nResult;
	u_char m_cRetCode;
}
TRUNKSELECT;
typedef struct
{
	TimeInterval m_stPtval;
	u_int  m_nLineNo;
	u_int  m_nChan;
	u_int  m_nDestChan;
	u_char m_szCaller[100];
	u_char m_szHzCalled[100];
	u_char m_szFlwName[100];
	u_int  m_nResult;
	u_char m_cRetCode;
	u_int  m_nLinkID;
	u_char m_szResult[100];  
}
TRUNKHZ;
typedef struct
{
	TimeInterval m_stPtval;
	u_int  m_nChan;
	u_char m_szKey[100];
	u_char m_szText[800];
	u_int  m_nResult;
	u_char m_cRetCode;
}
TTSREQ;

typedef struct
{
	TimeInterval m_stPtval;
	u_int  m_nTermType;
	u_int  m_nLineNo;
	u_int  m_nOnOffCode;
	u_int  m_nResult;
	u_char m_szResult[500];//主叫号码
	u_char m_cRetCode;
}
ONOFFHOOK;



typedef struct
{
	TimeInterval m_stPtval;
	u_int   m_nTermType;
	u_int  m_nLineNo;
	u_int  m_nLinkID;
	u_char  m_sCallee[100];
	u_int  m_nResult;
	u_char m_cRetCode;
}
ADIALOUT;


typedef struct
{
	TimeInterval m_stPtval;
	u_int  m_nChanNo;
	u_char  m_sPicPath[100];
	u_char  m_sText[100];
	u_char  m_sSynthPath[100];
	u_char  m_sFont[100];
	u_int   m_nX;
	u_int   m_nY;
	u_int   m_nSize;
	u_int	m_nR;
	u_int	m_nG;
	u_int	m_nB;
	u_int	m_nItalic;
	u_int	m_nBold;
	u_int  m_nResult;
	u_char m_cRetCode;
}
PICTEXTREQ;
typedef struct
{
	TimeInterval m_stPtval;
	u_int m_nLineNo;
	u_int m_nTermType;
	u_char m_sId[100];
	
}
AGENTLOAD;
typedef struct AGENTUPDATESTATE
{
	TimeInterval m_stPtval;
	u_int   m_nTermType;
	u_int	m_nLineNo;
    u_int   m_nLineState;
	u_char  m_sState[100];
}
AGENTUPDATESTATE;

typedef struct USERCALLOUTOK
{
	TimeInterval m_stPtval;
	u_int   m_nChanNo;
	u_int	m_nLineNo;
   // u_int   m_nLineState;
	u_char  m_sSessID[100];
}
USERCALLOUTOK;
typedef struct
{
	TimeInterval m_stPtval;
	u_int m_nLineNo;
	u_int m_nTermType;
	u_char m_sDtmf[100];
	
}
SENDDTMF;

/*跳转结构体*/
typedef struct{
	TimeInterval m_stPtval;
	int m_nChanNo;
	int m_nLineNo;
	int m_nType;
	int m_nSysCode;
	char m_szSysInfo[500];
}SYSINFO;
typedef struct
{
	TimeInterval m_stPtval;
	u_int  m_nTermType;
	u_int  m_nInfoID;
	u_int  m_nChanNo;
	u_int  m_nEventID;
	u_char m_szEventResult[100];
	u_int  m_nResult;
	u_char m_cRetCode;
}
LINKEVENT;
typedef struct
{
	TimeInterval m_stPtval;
	u_int  m_nChanNo;
	u_int  m_nCmdID;
	u_int  m_nInfoID;
	u_char m_szCaller[100];
	u_char m_szCalled[100];
	u_char m_szUssdText[500];
	u_char m_szUssdResult[100];
	u_int  m_nResult;
	u_char m_cRetCode;
}
SENDUSSD;
/*跳转结构体*/
typedef struct{
	TimeInterval m_stPtval;
	int m_nChanNo;
	int m_nLineNo;
	int m_nType;
	int m_nResult;
	int m_nInfoID;
	int m_nInfoData;
	char m_sCaller[100];
	char m_sCallee[100];
	char m_sOriCallee[100];
}REQUESTAGENT;
typedef struct
{
	TimeInterval m_stPtval;
	u_int  m_nTermType;
	u_int  m_nChanNo;
	u_int  m_nLineState;
	u_int  m_nAcdFlag;
	u_char m_szLineState[100];
	u_char m_szAgentID[100];
	u_char m_sCaller[100];
	u_char m_sCalled[100];
	u_char m_sOriCalled[100];
	u_char m_szAddress[100];
	u_int  m_nResult;
	u_char m_cRetCode;
}
LINESTATE;


typedef struct{
	TimeInterval m_stPtval;
	u_int   m_nCompanyID;
	u_int	m_nLine;//发起外呼的坐席
	u_int   m_nToLinkID;
	u_int  m_nQunhuID;
	u_int  m_nFlag;
	u_int  m_nChannelID;
	u_int  m_nItemCount;
	u_int  m_nFgLevel;
	u_int  m_nFgSubLevel;
	u_char m_szWorkFlow[100];
	u_char m_szImportTime[100];
	u_char m_szImportFlag[100];
	u_char m_szAgentID[100];//要外呼工号
	u_char m_szCaller[100];
	u_char m_szCalled[100];
	u_char m_szOriCalled[100];
	u_char m_szFlowName[100];
	u_char m_szPrivateData[100];
	u_int  m_nCmd;
	u_int  m_nTermType;
	//u_char m_szResult[500];//主叫号码
	u_char m_cRetCode;//成功或失败
}MUSICSENDINFO;


typedef struct{
	TimeInterval m_stPtval;
	u_int   m_nCompanyID;
	u_int	m_nLine;//发起外呼的坐
	u_int   m_nChan;//
	u_int   m_nChanType;
	u_int   m_nToLinkID;
	u_char  m_szStatus[100];
	u_char  m_szAgentID[100];//要外呼工号
	u_char  m_szCaller[100];
	u_char  m_szCalled[100];
	u_char  m_szChanMobile[100];
	u_char  m_szConfName[100];
	u_char  m_szSeq[100];
	u_char  m_szData[1024];
	u_int	m_nResult;
	u_char m_szResult[200];//主叫号码
	u_char m_cRetCode;//成功或失败
}CALLREPORT;

typedef struct{
	TimeInterval m_stPtval;
	int m_nLineNo;
	int m_nDLineNo;
	int m_nResult;
	char m_szResult[500];
}HANGUPONE;

typedef struct{
	TimeInterval m_stPtval;
	int m_nLineNo;
	int m_nResult;
	char m_szResult[500];
}HANGUPALL;

typedef struct{
	TimeInterval m_stPtval;
	int m_nLineNo;
	int m_nDLineNo;
	int m_nResult;
	char m_szResult[500];
}HOLDOFF;

typedef struct{
	TimeInterval m_stPtval;
	int m_nLineNo;
	int m_nDLineNo;
	int m_nResult;
	char m_szResult[500];
}HOLDON;
#define SQL_RETURN  80
#define SQL_NO_CONNECTION  SQL_RETURN+1
#define SQL_NO_AFFECTEDROW  SQL_RETURN+2
#define SQL_SQLERROR  SQL_RETURN+3
#define SQL_SUCCESS_NOFINISH SQL_RETURN+4
#define SQL_SUCCESS_FINISH SQL_RETURN+5
#endif

