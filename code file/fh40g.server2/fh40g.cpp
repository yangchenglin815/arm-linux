



#include "StdAfx.h"
#include <string>
#include <iostream>
using namespace std;
#if defined(WIN32)
#include <winsock.h>

#include <time.h>
#include <process.h> 
#else
#include<stdio.h>
#include <time.h>
#include <sys/time.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<sys/fcntl.h>
#include<stdlib.h>
#include<string.h>
#include<netdb.h>
#include<errno.h>
#include<arpa/inet.h>
#include<sys/stat.h>
#include <syslog.h>  
#include <signal.h> 
#include<unistd.h> //to use read and write
#include<termios.h>
#include <iostream> 
#include <dlfcn.h>
#include <unistd.h>
#endif
#include<list>

#include "dlist.h"
#include "math.h"
#include "TAesClass.h"
//#include "linkkey.h"

#define OTL_ODBC // Compile OTL 4.0/ODBC
// The following #define is required with MyODBC 3.51.11 and higher
#define OTL_ODBC_SELECT_STM_EXECUTE_BEFORE_DESCRIBE
#define OTL_ODBC_UNIX // uncomment this line if UnixODBC is used
//#define OTL_UNICODE


/*
#define OTL_ODBC_MYSQL // Compile OTL 4.0/ODBC
// The following #define is required with MyODBC 3.51.11 and higher
#define OTL_ODBC_SELECT_STM_EXECUTE_BEFORE_DESCRIBE
#define OTL_ODBC_UNIX // uncomment this line if UnixODBC is used
//#define OTL_UNICODE
*/

/*
//oracle
#define OTL_ORA10G_R2 // Compile OTL 4.0/OCI10gR2
*/

#include "otlv4.h" // include the OTL 4.0 header file
#include "netpubstr.h"
#include"cini.h"
#include"tools.h"
#include "tcpsocket.h"
#include "fh40g.h"


#if defined(WIN32) 
CRITICAL_SECTION mutex_db;
CRITICAL_SECTION mutex_log;
CRITICAL_SECTION mutex_flw;
#else
pthread_mutex_t mutex_db = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_log = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_flw = PTHREAD_MUTEX_INITIALIZER;
#endif

/*
cmd_start:@@1|cmd_start|终端编号|终端密码|任务序号|@@0
cmd_set:@@1|cmd_set|终端名称|发送频率|name|mobile|是否本部|外部标志|外呼IP|外部端口|平台时间|@@0
cmd_keep:@@1|cmd_keep|@@0
cmd_notice:@@1|cmd_notice|公告内容|@@0
cmd_msg:@@1|cmd_msg|消息时间|消息内容|@@0
cmd_data:@@1|cmd_data|经度|纬度|测量值|NBR|采集时间|路径编号serial|电压值|@@0
cmd_error:@@1|cmd_error|错误消息|@@0
cmd_serial:@@1|cmd_serial|新任务序号|@@0
*/
//int GetTermInfo(int nTerm);
const char * base64char = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
int GetSpeed();
int   InitTerm(int nIndex);
int GetNotice(int nIndex);
int UpdateMsg(int ID );
int TermOnline(int nIndex,int on);
int UpdateNbr(int nIndex,int nbr);
int UpdateTermNbr(int nIndex);
int update_term(int nIndex,string lat,string lng,string termbattery,string testvalue);
void UpdateGPS(string lng,string lat,string& mlng,string& mlat);
int GetTermInfo(int nIndex);
int NoticeCheck();
int GetNoticeID();
int MsgCheck();
int TermCheckNewTask(int nIndex,string taskname,char * taskid);
int Updategps(int nIndex,string lng,string lat,int gpsflag);
string * SplitString(string str, char split, int& iSubStrs);
CFG g_stCfg;
bool bStop =false;
DBC_INFO g_dbCfg[DBC_MAX];
struct SKT_CLIENT_INFO skt_client_info[MODULE_MAX];
struct LINE_INFO line_info[MODULE_MAX];
//struct ACD_INFO acd_info[100][1000]; 
//void ConvertGBKToUtf8(char &strGBK);
void Init();
BOOL IsInstalled();
BOOL Install();
BOOL Uninstall();
//void LogEvent(LPCTSTR pszFormat, ...);
void ServiceMain();
void ServiceStrl(DWORD dwOpcode);
int CmdSet_Send(int nIndex);
int TermNewTask(int nIndex, string humidity, string lat, string lng, string testtime, string taskname, string templ, char * taskid,int nbr);
int NetStart_Send(int nIndex);
int CmdKeep_Send(int nIndex);
int TermUpdate(int nIndex, string workway, string vnumber);
//int TermCheckNewTask(int nIndex,string testtime);
int TermCheck(int nIndex,string sNumber,char * tID);
char * base64_encode(/* const unsigned*/ char * bindata, char * base64, int binlength );
int base64_decode( const char * base64, /*unsigned*/ char * bindata );
int TermSave(int nIndex,char seq,char sLng,char sLat,char sValue,char sNBR,char sGetTime,char serial,char powerval,char fh40gpowerval );
int TermSavew(int nIndex,string testvalue,string testtime,string lng,string lat,string templ,string humidity,string termbattery,string devbattery,string unit,int gpsflag,int rssi,int nbr);
TCHAR szServiceName[] = "xtoems";
BOOL bInstall;
//SERVICE_STATUS_HANDLE hServiceStatus;
//SERVICE_STATUS status;
struct Q850ERRORINFO q850_info[128];



#define SYSERR_IVR_START				101 // IVR启动
#define SYSERR_IVR_DEVICE_CLOSE			102 // IVR收到关闭设备事件
#define SYSERR_IVR_TIMEINTERVAL			103 // 收包超时
#define SYSERR_IVR_DEVICE_UNIFAILURE	104 // 设备不可用
#define SYSERR_IVR_IPDUP				105 // IP重入
#define SYSERR_IVR_CALLCLASH			106 // 呼入呼出冲突
#define SYSERR_IVR_RECORDERR			107 // 录音错误
#define SYSERR_IVR_READFLOWERR  		108 // 读流程错误错误
#define SYSERR_IVR_REQVOCERR  		    109 // 请求语音资源错误
#define SYSERR_IVR_REQCHANERR  		    110 // 请求通道资源错误
#define SYSERR_IVR_SCRIPTERR  		    111 // 解析脚本错误
#define SYSERR_IVR_REQCONFERR  		    112 // 请求会议错误
#define SYSERR_IVR_SENDAGTERR  		    113 // 发送AGT包错误
#define SYSERR_IVR_SENDDBERR  		    114 // 发送DB包错误

#define SYSERR_AGT_CLIENTEXCEPTION      201 //客户端异常
#define SYSERR_AGT_TIMEINTERVAL			202 // 收包超时
#define SYSERR_AGT_SENDCLIENTERR  		203 // 发送CLIENT包错误
#define SYSERR_AGT_SENDIVRERR  			204 // 发送IVR包错误
typedef struct _CmdData
{
	int		type;
	int		status;
	time_t	sendtime;
	char	cmd[10240];
} CmdData;

int UpdateOffline();
int Updateonline();
//..
int InitDB(int i)
{
	char TmpStr[1024];
	try
	{
	
		if(g_dbCfg[i].m_db==NULL)
		{
			g_dbCfg[i].m_db = new otl_connect();
		}
		g_dbCfg[i].m_db->rlogon(g_stCfg.m_sOTL); // connect to Oracle
		g_dbCfg[i].m_nStatus = 0;
		//if(g_stCfg.m_nDBType==DBTYPE_MYSQL)
			g_dbCfg[i].m_db->auto_commit_on();
		sprintf(TmpStr,"InitDB %d 连接成功 ",i);
		LogMesg(0,TmpStr);
		return 1;
	}
	catch (otl_exception& p) { // intercept OTL exceptions
	
		sprintf(TmpStr,"%s 连接错误",g_stCfg.m_sOTL);
		LogMesg(0,TmpStr);
		LogMesg(0,(char*)p.msg); // print out error message
		LogMesg(0,(char*)p.stm_text); // print out SQL that caused the error
		LogMesg(0,(char*)p.var_info); // print out the variable that caused the error
		g_dbCfg[i].m_db->logoff();
		delete g_dbCfg[i].m_db;
		g_dbCfg[i].m_db = NULL;
		return 0;  
	}
	
	
}




void ReConnect(int i)
{
	//return ;
	char TmpStr[1024];
	
	
	//Retry:
	try
	{
		if (g_dbCfg[i].m_db!=NULL && 1 == g_dbCfg[i].m_db->connected)
		{
			g_dbCfg[i].m_db->logoff();
			delete g_dbCfg[i].m_db ;
			g_dbCfg[i].m_db = NULL;
			g_dbCfg[i].m_nStatus = -2;
			sprintf(TmpStr,"logoff %d",i);
			LogMesg(0,TmpStr);
		}
		if(	g_dbCfg[i].m_db == NULL)
			g_dbCfg[i].m_db = new otl_connect();
		g_dbCfg[i].m_db->rlogon(g_stCfg.m_sOTL); // connect to Oracle
		g_dbCfg[i].m_nStatus = 0;
		sprintf(TmpStr,"ReConnect %d 成功 ",i);
		LogMesg(0,TmpStr);
	}
	catch (otl_exception &e)
	{
		sprintf(TmpStr,"ReConnect %d 失败 ",i);
		LogMesg(0,TmpStr);
		e;
	}
}

//..
void InitDBCfg()
{
	int i = 0;
	for(i=0;i<DBC_MAX;i++)
	{
		g_dbCfg[i].m_nStatus = -1;
	}
	InitDB(0);
}

int SearchDB()
{
	char TmpStr[1024];
#if defined(WIN32)
	EnterCriticalSection(&mutex_db);
#else
	pthread_mutex_lock(&mutex_db);
#endif
	int nIndex = -1;
	for(int i=0;i<DBC_MAX;i++)
	{
		if(g_dbCfg[i].m_nStatus==0||g_dbCfg[i].m_nStatus==-1)
		{
			if(g_dbCfg[i].m_nStatus==-1)
			{
				int ret = InitDB(i);
				if(ret==1)
				{
					g_dbCfg[i].m_nStatus=1;
					nIndex= i;
					sprintf(TmpStr,"InitDB (%d) 连接成功",i);
					LogMesg(0,TmpStr);
					break;
				}
				else
				{
					sprintf(TmpStr,"InitDB (%d) 连接失败",i);
					LogMesg(0,TmpStr);
					break;
				}
			}
			else
			{
				g_dbCfg[i].m_nStatus=1;
				nIndex= i;
				break;
			}
			
		}
	}
#if defined(WIN32)
	LeaveCriticalSection(&mutex_db);
#else
	pthread_mutex_unlock(&mutex_db);
#endif
	return nIndex;
	
}
void ReleaseDB(int i)
{
#if defined(WIN32)
	EnterCriticalSection(&mutex_db);
#else
	pthread_mutex_lock(&mutex_db);
#endif
	if(g_dbCfg[i].m_nStatus==1)
	{
		g_dbCfg[i].m_nStatus=0;
	}

#if defined(WIN32)
	LeaveCriticalSection(&mutex_db);
#else
	pthread_mutex_unlock(&mutex_db);
#endif
}
CDBIndex::CDBIndex()
{
	m_nDBIndex = SearchDB();
	
};
CDBIndex::~CDBIndex()
{
	
	ReleaseDB(m_nDBIndex);
	if(m_nDBIndex>g_stCfg.m_nDBConnNum)
	{
		g_dbCfg[m_nDBIndex].m_db->logoff();
		g_dbCfg[m_nDBIndex].m_nStatus = -1;
		char TmpStr[1024];
		sprintf(TmpStr,"InitDB DBIndex=%d 断开连接",m_nDBIndex);
		LogMesg(-1,TmpStr);
		
	}
	
}
int   ProcData(int nIndex,string data);

int CDBIndex::GetDBIndex()
{
	return m_nDBIndex;
}


int   ProcData(int nIndex,string data)
{   //cout<<"procdata"<<endl;
    string* pStr;
	int iSubStrs;
	char TmpStr[1024];

	pStr = SplitString(data, '|', iSubStrs);

	//如果子字符串的数量为1
	if (iSubStrs >0 )
	{   
		if(pStr[1]=="CMD_START")
		{   
	        char tID[1024];
			int cc = TermCheck(nIndex,pStr[2],tID);
            
			sprintf(TmpStr,"TermCheck(%s,%s) id=%s ",pStr[2].c_str(),pStr[3].c_str(),tID);
			
			LogMesg(nIndex,TmpStr);
			strcpy(skt_client_info[nIndex].m_nTermID,tID);
			if(cc>0)
			{
	
				TermUpdate(nIndex,pStr[4],pStr[5]);
				TermOnline(nIndex,1);
				CmdSet_Send(nIndex);
				/*
				sprintf(skt_client_info[nIndex].m_sSerialNo,"%s",pStr[4]);
				
				
				if(TermCheckSerial(nIndex)==1)
				{
					//
					TermNewTask(nIndex);
				}
				*/
				
				
				return 1;
			}
			else
			{
				sprintf(TmpStr,"终端不存在");
				LogMesg(nIndex,TmpStr);
			}
	
		}
		else if(pStr[1]=="CMD_DATA")
		{
		
			//@@1|CMD_DATA|nj1001|00000.0000|0000.0000|127|nbr|gettime|serial|powerval|@@0 
			/*if(skt_client_info[nIndex].m_nTermID==0)
			{
					//终端若没有发送start 直接发送data，请重新发送start
					NetStart_Send(nIndex);
					return -1;
			}*/
            //@@1|CMD_DATA|id|termname|taskname|testvalue|testtime|lng|lat|templ|humidity|termbattery|devbattery|unit|gpsflag|rssi|nbr|gpscnt|@@0
			skt_client_info[nIndex].m_seqnum = atoi(pStr[2].c_str());
			int gpsflag = atoi(pStr[14].c_str());
			int rssi = atoi(pStr[15].c_str());
			int nbr = atoi(pStr[16].c_str());
            
            //避免数据重复插入
			if(skt_client_info[nIndex].m_seqnum > skt_client_info[nIndex].m_id)
			{
            if(skt_client_info[nIndex].m_seqnum-skt_client_info[nIndex].m_id>1)
			{
				char TmpStr[1024];
				sprintf(TmpStr,"count1=%d",++skt_client_info[nIndex].count1);
             	LogMesg(nIndex,TmpStr);
			}
			else
			{
                char TmpStr[1024];
				sprintf(TmpStr,"count2=%d",++skt_client_info[nIndex].count2);
             	LogMesg(nIndex,TmpStr);

			}
			if(gpsflag==1)
				{
				   Updategps(nIndex,pStr[7],pStr[8],gpsflag);
				}
			CmdKeep_Send(nIndex);
            update_term(nIndex,pStr[8],pStr[7],pStr[11],pStr[5]);
			if(pStr[5]=="---")
				return 0;
			
			char taskid[100];
			if(TermCheckNewTask(nIndex,pStr[4],taskid)==0)
			{
				
					TermNewTask(nIndex,pStr[10],pStr[8],pStr[7],pStr[6],pStr[4],pStr[9],taskid,nbr);
			}
			
            strcpy(skt_client_info[nIndex].m_nTaskID, taskid);
			if(nbr==1)
			{
                UpdateNbr(nIndex,nbr);

			}
			else
				UpdateTermNbr(nIndex);
			LogMesg(-1,"update termNBR");		
			TermSavew(nIndex,pStr[5],pStr[6],pStr[7],pStr[8],pStr[9],pStr[10],pStr[11],pStr[12],pStr[13],gpsflag,rssi,nbr);
			skt_client_info[nIndex].m_id = atoi(pStr[2].c_str());
			}
			else
			{
				char TmpStr[1024];
				sprintf(TmpStr,"count=%d",++skt_client_info[nIndex].count);
             	LogMesg(nIndex,TmpStr);

			}
		
		}
	
	}
	
	if(pStr!=NULL)
			delete []pStr;
	
	return 0;
}

int UpdateTermNbr(int nIndex)
{
    CDBIndex DBIndex;
	int nDBIndex = DBIndex.GetDBIndex();
	CHECKINDEX0()
		char sql[1024];
	char TmpStr[1024];
	sprintf(sql,"update ROMS200_TERM set nbr = 0 where id = '%s' ",skt_client_info[nIndex].m_nTermID);
	LogMesg(-1,sql);
	try
	{
		otl_stream otl_update(1, sql,*g_dbCfg[nDBIndex].m_db);
		otl_update.set_commit(0);
		int sqlrpc = otl_update.get_rpc();
		sprintf(TmpStr,"sqlrpc=%d,sql=%s",sqlrpc,sql);
		LogMesg(-1,TmpStr);
		otl_update.flush();
		g_dbCfg[nDBIndex].m_db->commit();
	}
	catch (otl_exception& p) { // intercept OTL exceptions
		LogMesg(-1,(char*)p.msg); // print out error message
		LogMesg(-1,(char*)p.stm_text); // print out SQL that caused the error
		LogMesg(-1,(char*)p.var_info); // print out the variable that caused the error
		ReConnect(nDBIndex);
		return 0;
	}
	return 0;
}

int UpdateNbr(int nIndex,int nbr)
{
	CDBIndex DBIndex;
	int nDBIndex = DBIndex.GetDBIndex();
	CHECKINDEX0()
    char sql[1024];
	char TmpStr[1024];
	sprintf(sql,"update ROMS200_TASK set nbr = %d where id = '%s' ",nbr,skt_client_info[nIndex].m_nTaskID);
	LogMesg(-1,sql);
	try
	{
		otl_stream otl_update(1, sql,*g_dbCfg[nDBIndex].m_db);
		otl_update.set_commit(0);
		int sqlrpc = otl_update.get_rpc();
		sprintf(TmpStr,"sqlrpc=%d,sql=%s",sqlrpc,sql);
		LogMesg(-1,TmpStr);
		otl_update.flush();
		g_dbCfg[nDBIndex].m_db->commit();
	}
	catch (otl_exception& p) { // intercept OTL exceptions
		LogMesg(-1,(char*)p.msg); // print out error message
		LogMesg(-1,(char*)p.stm_text); // print out SQL that caused the error
		LogMesg(-1,(char*)p.var_info); // print out the variable that caused the error
		ReConnect(nDBIndex);
		return 0 ;
	}
	sprintf(sql,"update ROMS200_TERM set nbr = %d where id = '%s' ",nbr,skt_client_info[nIndex].m_nTermID);
	LogMesg(-1,sql);
	try
	{
		otl_stream otl_update(1, sql,*g_dbCfg[nDBIndex].m_db);
		otl_update.set_commit(0);
		int sqlrpc = otl_update.get_rpc();
		sprintf(TmpStr,"sqlrpc=%d,sql=%s",sqlrpc,sql);
		LogMesg(-1,TmpStr);
		otl_update.flush();
		g_dbCfg[nDBIndex].m_db->commit();
	}
	catch (otl_exception& p) { // intercept OTL exceptions
		LogMesg(-1,(char*)p.msg); // print out error message
		LogMesg(-1,(char*)p.stm_text); // print out SQL that caused the error
		LogMesg(-1,(char*)p.var_info); // print out the variable that caused the error
		ReConnect(nDBIndex);
		return 0 ;
	}
		return 0;
}

int TermUpdate(int nIndex, string workway, string vnumber)
{
	CDBIndex DBIndex;
	int nDBIndex = DBIndex.GetDBIndex();
	CHECKINDEX0()
    char sql[1024];
	char TmpStr[1024];
	sprintf(sql,"update ROMS200_TERM  set vnumber = '%s' and workway = '%s' where id = '%s'  ",vnumber.c_str(),workway.c_str(),skt_client_info[nIndex].m_nTermID);
		LogMesg(-1,sql);
		try
		{
			otl_stream otl_update(1, sql,*g_dbCfg[nDBIndex].m_db);
			otl_update.set_commit(0);
			int sqlrpc = otl_update.get_rpc();
			sprintf(TmpStr,"sqlrpc=%d,sql=%s",sqlrpc,sql);
			LogMesg(-1,TmpStr);
			otl_update.flush();
			g_dbCfg[nDBIndex].m_db->commit();
		}
		catch (otl_exception& p) { // intercept OTL exceptions
			LogMesg(-1,(char*)p.msg); // print out error message
			LogMesg(-1,(char*)p.stm_text); // print out SQL that caused the error
			LogMesg(-1,(char*)p.var_info); // print out the variable that caused the error
			ReConnect(nDBIndex);
			return 0 ;
		}
		return 0;
}

string * SplitString(string str, char split, int& iSubStrs)
{  // cout<<"SplitString"<<endl;
    int iPos = 0; //分割符位置
    int iNums = 0; //分割符的总数
	// 	/LogMesg("old["+str+"]");
	//str.replace("  "," ");
	//	LogMesg("new["+str+"]");
    string strTemp = str;
    string strRight;
    //先计算子字符串的数量
	
    while (iPos != -1)
    {
        iPos = strTemp.find(split);
        if (iPos == -1)
        {
            break;
        }
        strRight = strTemp.substr(iPos + 1, str.length());
        strTemp = strRight;
        iNums++;
    }
    if (iNums == 0) //没有找到分割符
    {
        //子字符串数就是字符串本身
        iSubStrs = 1; 
        return NULL;
    }
    //子字符串数组
    iSubStrs = iNums + 1; //子串的数量 = 分割符数量 + 1
    string* pStrSplit;
    pStrSplit = new string[iSubStrs];
    strTemp = str;
    string strLeft;
    for (int i = 0; i < iNums; i++)
    {
        iPos = strTemp.find(split);
        //左子串
        strLeft = strTemp.substr(0, iPos);
        //右子串
        strRight = strTemp.substr(iPos + 1, strTemp.length());
        strTemp = strRight;

        pStrSplit[i] = strLeft;
		
    }
    pStrSplit[iNums] = strTemp;
    return pStrSplit;
}
void LogMesg(int nSessionID ,const char *szLogMesg)
{
#if defined(WIN32)
	int nThreadId = GetCurrentThreadId();
	SYSTEMTIME systemTime;
	char szLogStr[10240];
	char szDateBuf[256];

	const unsigned int datebufSize = 256;
	struct { int tv_sec; int tv_usec; } tv = {0,0};
	time((time_t *)(&tv.tv_sec));
	GetLocalTime(&systemTime);
	tv.tv_usec = systemTime.wMilliseconds * 1000; 
	
	const time_t timeInSeconds = (time_t) tv.tv_sec;
	strftime (szDateBuf,
		datebufSize,
		"%Y%m%d%H%M%S",
		localtime (&timeInSeconds));
	char msbuf[5];
	sprintf(msbuf, ".%3.3ld", long(tv.tv_usec / 1000));
	int datebufCharsRemaining = datebufSize - strlen (szDateBuf);
	strncat (szDateBuf, msbuf, datebufCharsRemaining - 1);
	szDateBuf[datebufSize - 1] = '\0'; 
	g_stCfg.m_nLogLine ++;
	if(g_stCfg.g_fpLogFile==NULL||g_stCfg.m_nLogLine>=g_stCfg.m_nMaxLogLine)//20k
	{
		if(g_stCfg.g_fpLogFile!=NULL)
			fclose(g_stCfg.g_fpLogFile);
		g_stCfg.m_nLogLine=0;
		char logfile[512];
		char tmpbuf[1024];
		sprintf(logfile,"d://roms//logfile//%s_","CZfh40g");
		time_t the_time;
		struct tm *tm_ptr;
		(void) time(&the_time);
		tm_ptr = localtime(&the_time);
		strftime(tmpbuf, 50, "%Y%m%d%H%M%S", tm_ptr);
		strcat(tmpbuf,".log");
		strcat(logfile,tmpbuf);
		g_stCfg.g_fpLogFile = fopen(logfile,"w");
	}
   	if (g_stCfg.g_fpLogFile != NULL)
	{
		sprintf(szLogStr,"[%05d]T[%03d][%s], %s\n",nThreadId,nSessionID,szDateBuf,szLogMesg);
		printf(szLogStr);
		fseek(g_stCfg.g_fpLogFile ,0,SEEK_END);
		fwrite(szLogStr, strlen(szLogStr),1,g_stCfg.g_fpLogFile);
		fflush(g_stCfg.g_fpLogFile);
	}
#else
	struct tm *tm_ptr, timestruct;
    time_t the_time;
	char strmsg[10240];
    char tmpbuf[1024];
	char timebuf[1024];
	char prototype[100];
	char seq[100];
	char way[100];
    char *result;
	int  usec ;
	pthread_mutex_lock(&mutex_log); 
	if(!g_stCfg.g_fpLogFile || g_stCfg.m_nLogLine++>200000)
	{
		if(g_stCfg.g_fpLogFile)
		{
			fclose(g_stCfg.g_fpLogFile);
		}
		char logfile[512];
		sprintf(logfile,"/usr/roms/logfile/CZfh40g_");
		(void) time(&the_time);
		tm_ptr = localtime(&the_time);
		strftime(tmpbuf, 50, "%Y%m%d%H%M%S", tm_ptr);
		strcat(tmpbuf,".log");
		
		strcat(logfile,tmpbuf);
		g_stCfg.m_nLogLine = 0;
		g_stCfg.g_fpLogFile = fopen(logfile,"w");
		
		if(!g_stCfg.g_fpLogFile)
		{
			//printf("can not open logfile:%s\n",logfile);
			pthread_mutex_unlock(&mutex_log);
			
			return;
		}
	}
	(void) time(&the_time);
    tm_ptr = localtime(&the_time);
	struct timeval tv;
	gettimeofday (&tv , NULL);
	sprintf(strmsg,"%08x",pthread_self());
	strftime( tmpbuf, 1024,"%Y-%m-%d %H:%M:%S", tm_ptr );
	sprintf(timebuf,"[%s.%06d]",tmpbuf,tv.tv_usec);
	

	strcat(strmsg,timebuf);
	//strcat(strmsg,prototype);
	strcat(strmsg,szLogMesg);
	strcat(strmsg,"\n");
	
	
	fseek(g_stCfg.g_fpLogFile ,0,SEEK_END);
	fwrite(strmsg, strlen(strmsg),1,g_stCfg.g_fpLogFile);
	fflush(g_stCfg.g_fpLogFile);
	//printf(strmsg);
	pthread_mutex_unlock(&mutex_log);
#endif

    return;
}


Location		transformFromWGSToGCJ(Location wgLoc);
Location		transformFromGCJToWGS(Location gcLoc);
Location		bd_encrypt(Location gcLoc);
Location		bd_decrypt(Location bdLoc);

inline Location
LocationMake(double lng, double lat) {
    Location loc; loc.lng = lng, loc.lat = lat; return loc;
}

///
///  Transform WGS-84 to GCJ-02 (Chinese encrypted coordination system)
///

const double pi = 3.14159265358979324;

//
// Krasovsky 1940
//
// a = 6378245.0, 1/f = 298.3
// b = a * (1 - f)
// ee = (a^2 - b^2) / a^2;
const double a = 6378245.0;
const double ee = 0.00669342162296594323;

int outOfChina(double lat, double lon)
{
    if (lon < 72.004 || lon > 137.8347)
        return 1;
    if (lat < 0.8293 || lat > 55.8271)
        return 1;
    return 0;
}

double transformLat(double x, double y)
{
    double ret = -100.0 + 2.0 * x + 3.0 * y + 0.2 * y * y + 0.1 * x * y + 0.2 * sqrt(x > 0 ? x:-x);
    ret += (20.0 * sin(6.0 * x * pi) + 20.0 *sin(2.0 * x * pi)) * 2.0 / 3.0;
    ret += (20.0 * sin(y * pi) + 40.0 * sin(y / 3.0 * pi)) * 2.0 / 3.0;
    ret += (160.0 * sin(y / 12.0 * pi) + 320 * sin(y * pi / 30.0)) * 2.0 / 3.0;
    return ret;
}

double transformLon(double x, double y)
{
    double ret = 300.0 + x + 2.0 * y + 0.1 * x * x + 0.1 * x * y + 0.1 * sqrt(x > 0 ? x:-x);
    ret += (20.0 * sin(6.0 * x * pi) + 20.0 * sin(2.0 * x * pi)) * 2.0 / 3.0;
    ret += (20.0 * sin(x * pi) + 40.0 * sin(x / 3.0 * pi)) * 2.0 / 3.0;
    ret += (150.0 * sin(x / 12.0 * pi) + 300.0 * sin(x / 30.0 * pi)) * 2.0 / 3.0;
    return ret;
}

Location transformFromWGSToGCJ(Location wgLoc)
{
    Location mgLoc;
    if (outOfChina(wgLoc.lat, wgLoc.lng))
    {
        mgLoc = wgLoc;
        return mgLoc;
    }
    double dLat = transformLat(wgLoc.lng - 105.0, wgLoc.lat - 35.0);
    double dLon = transformLon(wgLoc.lng - 105.0, wgLoc.lat - 35.0);
    double radLat = wgLoc.lat / 180.0 * pi;
    double magic = sin(radLat);
    magic = 1 - ee * magic * magic;
    double sqrtMagic = sqrt(magic);
    dLat = (dLat * 180.0) / ((a * (1 - ee)) / (magic * sqrtMagic) * pi);
    dLon = (dLon * 180.0) / (a / sqrtMagic * cos(radLat) * pi);
    mgLoc.lat = wgLoc.lat + dLat;
    mgLoc.lng = wgLoc.lng + dLon;

    return mgLoc;
}

///
///  Transform GCJ-02 to WGS-84
///  Reverse of transformFromWGSToGC() by iteration.
///
///  Created by Fengzee (fengzee@fengzee.com) on 13-11-9.
///
Location transformFromGCJToWGS(Location gcLoc)
{
    Location wgLoc = gcLoc;
    Location currGcLoc, dLoc;
    while (1) {
        currGcLoc = transformFromWGSToGCJ(wgLoc);
        dLoc.lat = gcLoc.lat - currGcLoc.lat;
        dLoc.lng = gcLoc.lng - currGcLoc.lng;
        if (fabs(dLoc.lat) < 1e-7 && fabs(dLoc.lng) < 1e-7) {  // 1e-7 ~ centimeter level accuracy
          // Result of experiment:
          //   Most of the time 2 iterations would be enough for an 1e-8 accuracy (milimeter level).
          //
            return wgLoc;
        }
        wgLoc.lat += dLoc.lat;
        wgLoc.lng += dLoc.lng;
    }

    return wgLoc;
}

///
///  Transform GCJ-02 to BD-09
///
const double x_pi = 3.14159265358979324 * 3000.0 / 180.0;
Location bd_encrypt(Location gcLoc)
{
    double x = gcLoc.lng, y = gcLoc.lat;
    double z = sqrt(x * x + y * y) + 0.00002 * sin(y * x_pi);
    double theta = atan2(y, x) + 0.000003 * cos(x * x_pi);
    return LocationMake(z * cos(theta) + 0.0065, z * sin(theta) + 0.006);
}

///
///  Transform BD-09 to GCJ-02
///
Location bd_decrypt(Location bdLoc)
{
    double x = bdLoc.lng - 0.0065, y = bdLoc.lat - 0.006;
    double z = sqrt(x * x + y * y) - 0.00002 * sin(y * x_pi);
    double theta = atan2(y, x) - 0.000003 * cos(x * x_pi);
    return LocationMake(z * cos(theta), z * sin(theta));
}
//..
BOOL SockVarInit()
{
#if defined(WIN32)
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;
	
	wVersionRequested = MAKEWORD( 2, 0 );
	
	err = WSAStartup( wVersionRequested, &wsaData );
	if ( err != 0 )
	{
		/* Tell the user that we could not find a usable */
		/* WinSock DLL.                                  */
		return FALSE;
	}
	
	/* Confirm that the WinSock DLL supports 2.2.*/
	/* Note that if the DLL supports versions greater    */
	/* than 2.2 in addition to 2.2, it will still return */
	/* 2.2 in wVersion since that is the version we      */
	/* requested.                                        */
	
	if ( LOBYTE( wsaData.wVersion ) != 2 ||
        HIBYTE( wsaData.wVersion ) != 0 ) 
	{
		/* Tell the user that we could not find a usable */
		/* WinSock DLL.                                  */
		WSACleanup( );
		return FALSE;
	}
    return TRUE; 
#else
	return TRUE;
#endif
}


void proc(CTcpAsyncSocket* skt_server)
{
	char TmpStr[10240];
	struct timeval  stWaitTime;//发送和接受的等待时间结构
//	fd_set fdAll;//socket集合
	fd_set fdread;//socket集合
	stWaitTime.tv_sec = 0;
	stWaitTime.tv_usec = 5;
	FD_ZERO(&fdread);
	FD_SET(skt_server->m_hSocket,&fdread);
	int maxfd = skt_server->m_hSocket+1;
	if (select(maxfd,&fdread,0,0,&stWaitTime) < 1)
	{
	
		return ;
	}
	sprintf(TmpStr,"skt_server selected...");
	LogMesg(-1,TmpStr);
	if (FD_ISSET(skt_server->m_hSocket,&fdread))
	{
		sprintf(TmpStr,"skt_server recv connected...");
		LogMesg(-1,TmpStr);
		CTcpAsyncSocket tmpsocket;
		if (!skt_server->Accept(tmpsocket))
		{
		
			skt_server->Close();
			return ;
		}
		SOCKADDR_IN sockAddr;
		memset(&sockAddr, 0, sizeof(sockAddr));
		
	
#if defined(WIN32)
		int nSockAddrLen = sizeof(SOCKADDR_IN);
#else
		socklen_t nSockAddrLen = sizeof(SOCKADDR_IN);
#endif
		
		char rPeerAddress[100];
		int rPeerPort;
		BOOL bResult = getpeername(tmpsocket.m_hSocket,(SOCKADDR*)&sockAddr, &nSockAddrLen);
		if (bResult!=SOCKET_ERROR)
		{
			rPeerPort = ntohs(sockAddr.sin_port);
			strcpy(rPeerAddress , inet_ntoa(sockAddr.sin_addr));
			sprintf(TmpStr,"connected from %s:%d",rPeerAddress,rPeerPort);
			LogMesg(-1,TmpStr);
			
		}

		if(1)
		{
			if(g_stCfg.m_nIndex>=MODULE_MAX-1)
				g_stCfg.m_nIndex = 0;
			int i = g_stCfg.m_nIndex ;
			for(;i<MODULE_MAX;i++)
			{
				if(skt_client_info[i].skt_client.m_hSocket==INVALID_SOCKET)
					break;
			}
			g_stCfg.m_nIndex = i+1;
			sprintf(TmpStr,"获得新ID nIndex =%d  socket=%d",i,tmpsocket.m_hSocket);
			LogMesg(i,TmpStr);
			InitTerm(i);
			skt_client_info[i].skt_client.m_hSocket = tmpsocket.m_hSocket;
			strcpy(skt_client_info[i].m_sPeerAddress,rPeerAddress);
			sprintf(skt_client_info[i].m_sPort,"%d",rPeerPort);
		
			
			
#if defined(WIN32)
			HANDLE   hThread;
			unsigned   threadid; 
			hThread   =   (HANDLE)_beginthreadex(   NULL,   0,   &ThreadProc,   (void*)i,   0,   &threadid   );   //NULL表示无传递参数
#else
			pthread_t hThread;
			pthread_create(&hThread, NULL, ThreadProc, (void*)i);
#endif
			
		}
		tmpsocket.m_hSocket = INVALID_SOCKET;
		
		return ;
		
	}
}

 /*void  ServiceStrl(DWORD dwOpcode)
{
    switch (dwOpcode)
    {
    case SERVICE_CONTROL_STOP:
		status.dwCurrentState = SERVICE_STOP_PENDING;
        SetServiceStatus(hServiceStatus, &status);
			
       // PostThreadMessage(dwThreadID, WM_CLOSE, 0, 0);
		LogMesg(-1,("SERVICE_CONTROL_STOP"));
		//exit(0);
		bStop = true;
        break;
    case SERVICE_CONTROL_PAUSE:
			LogMesg(-1,("SERVICE_CONTROL_PAUSE"));
        break;
    case SERVICE_CONTROL_CONTINUE:
			LogMesg(-1,("SERVICE_CONTROL_CONTINUE"));
        break;
    case SERVICE_CONTROL_INTERROGATE:
			LogMesg(-1,("SERVICE_CONTROL_INTERROGATE"));
        break;
    case SERVICE_CONTROL_SHUTDOWN:
			LogMesg(-1,("SERVICE_CONTROL_SHUTDOWN"));
        break;
    default:
        LogMesg(-1,("Bad service request"));
    }
}
*/
int ms = 100;


#if defined(WIN32)
UINT  __stdcall  ThreadProc(LPVOID lpParam)
#else
void*  ThreadProc(void* lpParam)
#endif
{

int nIndex =(int) lpParam;
	struct timeval  stWaitTime;//发送和接受的等待时间结构
	fd_set fdread;//socket集合
	char TmpStr[10240];
	sprintf(TmpStr,"创建线程%d",nIndex);
	LogMesg(nIndex,TmpStr);
	skt_client_info[nIndex].recv_dlist = dlist_create();
	skt_client_info[nIndex].send_dlist = dlist_create();
	skt_client_info[nIndex].m_gpsflag = 0;
	
	char databuf[10240]="";
    char buf[10240]="";
	time_t		 killtime;
	(void) time(&killtime);
	(void) time(&skt_client_info[nIndex].m_keeplivetime);
	(void) time(&skt_client_info[nIndex].m_lastsendtime);

	while(1)
	{
			
#if defined(WIN32)
		Sleep(10);
#else
		usleep(100);
#endif
	
		skt_client_info[nIndex].m_nKeepSeconds++;
		time_t tNowTime;
		(void) time(&tNowTime);
		
		
		int esptime =  tNowTime - skt_client_info[nIndex].m_keeplivetime ;
	
		if(esptime>60)
		{
			TermOnline(nIndex,0);
			//Updateonline();
			skt_client_info[nIndex].skt_client.Close();
			skt_client_info[nIndex].skt_client.m_hSocket=INVALID_SOCKET;
			skt_client_info[nIndex].m_nKeepSeconds =0;
			skt_client_info[nIndex].m_gpsflag = 0;
			char TmpStr[10240];
			
			sprintf(TmpStr,"60秒到，主动线程退出%d",nIndex);
			LogMesg(nIndex,TmpStr);
			dlist_destroy(skt_client_info[nIndex].recv_dlist);
			sprintf(TmpStr,"destroy recv_dlist",nIndex);
			LogMesg(nIndex,TmpStr);
			return 1;
		}
		

	
		
	
	//	esptime =  tNowTime - skt_client_info[nIndex].m_lastsendtime ;

		//if(dlist_length(skt_client_info[nIndex].send_dlist)>0&&esptime>=1)
		if(dlist_length(skt_client_info[nIndex].send_dlist)>0)
		{
			
			CmdData* data=NULL;
			//char buf[10240]={};
			dlist_get_by_index(skt_client_info[nIndex].send_dlist,0,(void**)&data);
			//strcat(databuf, data->cmd);
			stWaitTime.tv_sec = 0;
			stWaitTime.tv_usec = 5;
			if(skt_client_info[nIndex].skt_client.m_hSocket==INVALID_SOCKET)
			{
				LogMesg(nIndex,"skt_client is invalid ");
				return 0;
			}
			struct timeval  stWaitTime;//发送和接受的等待时间结构
			
//			fd_set fdAll;//socket集合
			fd_set fdwrite;//socket集合
			FD_ZERO(&fdwrite);
			FD_SET(skt_client_info[nIndex].skt_client.m_hSocket,&fdwrite);
			int maxfd = skt_client_info[nIndex].skt_client.m_hSocket+1;
			int sret = select(maxfd,0,&fdwrite,0,&stWaitTime);
			if (sret >= 1)
			{	
				if(FD_ISSET(skt_client_info[nIndex].skt_client.m_hSocket,&fdwrite))
				{
					char* buf = data->cmd;
		
					//ConvertGBKToUtf8(*buf);
					int len = skt_client_info[nIndex].skt_client.Send(buf,strlen(buf));
					(void) time(&skt_client_info[nIndex].m_lastsendtime);

					LogMesg(nIndex, data->cmd);
				//	return len;
					
				}
			}
			else
			{
				strcpy(skt_client_info[nIndex].m_nTermID,"");
				skt_client_info[nIndex].skt_client.Close();
				char TmpStr[10240];
				sprintf(TmpStr,"发送CLIENT包错误 IP %s:%s 工号:%s",skt_client_info[nIndex].m_sPeerAddress,skt_client_info[nIndex].m_sPort,skt_client_info[nIndex].m_sID);
				LogErrorSysInfo(SYSERR_AGT_SENDCLIENTERR,TmpStr); 
				LogMesg(nIndex,"skt_client.close");
			}
			free(data);
			dlist_delete(skt_client_info[nIndex].send_dlist,0);
		}

		if(dlist_length(skt_client_info[nIndex].recv_dlist)>0)
		{
			(void) time(&skt_client_info[nIndex].m_keeplivetime);
			CmdData* data=NULL;
			dlist_get_by_index(skt_client_info[nIndex].recv_dlist,0,(void**)&data);
			strcpy(databuf, data->cmd);
		//	sprintf(TmpStr,"databuf0=%s",databuf);
		//	LogMesg(nIndex,TmpStr);
		/*	sprintf(TmpStr,"databuf0=%s",strlen(databuf));
			LogMesg(nIndex,TmpStr);*/
		//	cout<<"databuf0="<<strlen(databuf)<<endl;
           // cout<<"databuf0:"<<databuf<<endl;
           
		/*	sprintf(TmpStr,"databuf1_size=%s",strlen(databuf));
			LogMesg(nIndex,TmpStr);*/
			//cout<<"databuf1="<<strlen(databuf)<<endl;
			
		
			while(1)
			{
				//cout<<"while"<<endl;
				//cout<<"databuf1:"<<databuf<<endl;
				string tcpdata = databuf;
               	//cout<<"tcpdata:"<<tcpdata;			
				int start = tcpdata.find("@@1");
				int end = tcpdata.find("@@0",start);
				
				if(start!=-1&&end!=-1)
				{
					string subdata = tcpdata.substr(start,end-start+3);
					//cout<<"subdata:"<<subdata<<endl;
					strcpy(databuf,(tcpdata.substr(end+3)).c_str());

			        int s = subdata.find("@@1");
					int e = subdata.find("@@0",s);
					if(s!=-1&&e!=-1)
					{
						string base64 = subdata.substr(s+3,e-(s+3));
					 
                        TAesClass *aes = new TAesClass;                
                       
			            char miwen[1024]={0};
                        char jiemi[1024]={0};
	                    UCHAR key[1024] = "xiangting";
                        UCHAR *p = key;
                        aes->InitializePrivateKey(16, p); 
                        //解码
	                    base64_decode(base64.c_str(),miwen);
			
	                    //cout<<"miwen:"<<miwen<<endl;
	                    //解密
                        aes->OnAesUncrypt((LPVOID)miwen, (DWORD)sizeof(miwen),(LPVOID)jiemi);
			            free(aes);
                       // char TmpStr[10240];
					//	sprintf(TmpStr,"jiemi=%s",jiemi);
			          //  LogMesg(nIndex,TmpStr);
						ProcData(nIndex,jiemi);
						
					}
				
				
			       // cout<<"str_databuf:"<<databuf<<endl;
				//	ProcData(nIndex,data1);
				
				}
				else
				{
					break;
				}
				//CString tcpdata = databuf;
				//LogMesg(-1,tcpdata);
			}
			free(data);
			dlist_delete(skt_client_info[nIndex].recv_dlist,0);
		}

	
		FD_ZERO(&fdread);
		stWaitTime.tv_sec = 0;
		stWaitTime.tv_usec = 5;
		
		FD_SET(skt_client_info[nIndex].skt_client.m_hSocket,&fdread);
		int maxfd = skt_client_info[nIndex].skt_client.m_hSocket+1;
	//	if (select(0,&fdread,0,0,&stWaitTime) < 1)
		int s = select(maxfd,&fdread,0,0,&stWaitTime);
		if (s< 1)
		{
			continue;
		}
		


		if (FD_ISSET(skt_client_info[nIndex].skt_client.m_hSocket,&fdread))
		{
			int ThreadNum = (int)lpParam;
			char TmpStr[10240];
			sprintf(TmpStr,"接收到数据from %s:%s",skt_client_info[nIndex].m_sPeerAddress,skt_client_info[nIndex].m_sPort);
			LogMesg(nIndex,TmpStr);
		}

		
		//int length = skt_client[i].Receive(skt_client_info[i].m_mess);
		memset(skt_client_info[nIndex].m_szRecvBuf,'\0',1024);
		int messtype = RecvFromClient(nIndex);
		sprintf(TmpStr,"messtype=%d",nIndex);
		LogMesg(nIndex,TmpStr);
		if (messtype==0)
		{
		
			//GetString_WSAError();
			sprintf(TmpStr,"[termtype]=%d Receive ret = -1",nIndex);

			LogMesg(nIndex,TmpStr);
			TermOnline(nIndex,0);
			strcpy(skt_client_info[nIndex].m_nTermID,"");
			skt_client_info[nIndex].skt_client.Close();
			skt_client_info[nIndex].skt_client.m_hSocket=INVALID_SOCKET;
			
			InitTerm(nIndex);
			char TmpStr[10240];
		
			sprintf(TmpStr,"线程退出%d",nIndex);
			LogMesg(nIndex,TmpStr);
			dlist_destroy(skt_client_info[nIndex].recv_dlist);
			#if defined(WIN32)
			return 1;
			#else
			return (void*)1;
			#endif

		}

	//	sprintf(TmpStr,"[%s:%s][socket client]recv =%s ",skt_client_info[nIndex].m_sPeerAddress,skt_client_info[nIndex].m_sPort,skt_client_info[nIndex].m_szRecvBuf);
	//	LogMesg(nIndex,TmpStr);
		
		CmdData* data = (CmdData*)malloc(sizeof(CmdData));
		data->type = 0;
		data->status = 0;
		strcpy(data->cmd,(char*)skt_client_info[nIndex].m_szRecvBuf);
	//	sprintf(TmpStr,"data=%s",data->cmd);
	//	LogMesg(nIndex,TmpStr);
		/*	sprintf(TmpStr,"cmd_size=%s",strlen(data->cmd));
			LogMesg(nIndex,TmpStr);*/
        //cout<<"cmdsize="<<strlen(data->cmd)<<endl;
		dlist_append(skt_client_info[nIndex].recv_dlist, (void*)data);
	
	}
	dlist_destroy(skt_client_info[nIndex].recv_dlist);
	dlist_destroy(skt_client_info[nIndex].send_dlist);
}



char * base64_encode(/* const unsigned*/ char * bindata, char * base64, int binlength )
{
    int i, j;
    unsigned char current;
	
    for ( i = 0, j = 0 ; i < binlength ; i += 3 )
    {
        current = (bindata[i] >> 2) ;
        current &= (unsigned char)0x3F;
        base64[j++] = base64char[(int)current];
		
        current = ( (unsigned char)(bindata[i] << 4 ) ) & ( (unsigned char)0x30 ) ;
        if ( i + 1 >= binlength )
        {
            base64[j++] = base64char[(int)current];
            base64[j++] = '=';
            base64[j++] = '=';
            break;
        }
        current |= ( (unsigned char)(bindata[i+1] >> 4) ) & ( (unsigned char) 0x0F );
        base64[j++] = base64char[(int)current];
		
        current = ( (unsigned char)(bindata[i+1] << 2) ) & ( (unsigned char)0x3C ) ;
        if ( i + 2 >= binlength )
        {
            base64[j++] = base64char[(int)current];
            base64[j++] = '=';
            break;
        }
        current |= ( (unsigned char)(bindata[i+2] >> 6) ) & ( (unsigned char) 0x03 );
        base64[j++] = base64char[(int)current];
		
        current = ( (unsigned char)bindata[i+2] ) & ( (unsigned char)0x3F ) ;
        base64[j++] = base64char[(int)current];
    }
    base64[j] = '\0';
    return base64;
}

int base64_decode( const char * base64, /*unsigned*/ char * bindata )
{
    int i, j;
    unsigned char k;
    unsigned char temp[4];
    for ( i = 0, j = 0; base64[i] != '\0' ; i += 4 )
    {
        memset( temp, 0xFF, sizeof(temp) );
        for ( k = 0 ; k < 64 ; k ++ )
        {
            if ( base64char[k] == base64[i] )
                temp[0]= k;
        }
        for ( k = 0 ; k < 64 ; k ++ )
        {
            if ( base64char[k] == base64[i+1] )
                temp[1]= k;
        }
        for ( k = 0 ; k < 64 ; k ++ )
        {
            if ( base64char[k] == base64[i+2] )
                temp[2]= k;
        }
        for ( k = 0 ; k < 64 ; k ++ )
        {
            if ( base64char[k] == base64[i+3] )
                temp[3]= k;
        }
		
        bindata[j++] = ((unsigned char)(((unsigned char)(temp[0] << 2))&0xFC)) |
			((unsigned char)((unsigned char)(temp[1]>>4)&0x03));
        if ( base64[i+2] == '=' )
            break;
		
        bindata[j++] = ((unsigned char)(((unsigned char)(temp[1] << 4))&0xF0)) |
			((unsigned char)((unsigned char)(temp[2]>>2)&0x0F));
        if ( base64[i+3] == '=' )
            break;
		
        bindata[j++] = ((unsigned char)(((unsigned char)(temp[2] << 6))&0xF0)) |
			((unsigned char)(temp[3]&0x3F));
    }
    return j;
}
/*void GetStatus()   
{   
	LogMesg(-1,"GetStatus");
	
	SC_HANDLE hSCM = ::OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
    if (hSCM == NULL)
    {
		LogMesg(-1,"Couldn't open service manager");
        return ;
    }
	
    // Get the executable file path
    TCHAR szFilePath[MAX_PATH];
    ::GetModuleFileName(NULL, szFilePath, MAX_PATH);
	
	//创建服务
    SC_HANDLE hService  = OpenService(hSCM, szServiceName, SERVICE_ALL_ACCESS);   
	/*
	SC_HANDLE hService = ::CreateService(
	hSCM, szServiceName, szServiceName,
	SERVICE_ALL_ACCESS, SERVICE_WIN32_OWN_PROCESS,
	SERVICE_DEMAND_START, SERVICE_ERROR_NORMAL,
	szFilePath, NULL, NULL, _T(""), NULL, NULL);
	*/
	
    /*if (hService == NULL)
    {
        ::CloseServiceHandle(hSCM);
		LogMesg(-1,"Couldn't open service");
        return ;
    }
	
	
	
    BOOL SUCCESS;   
    SERVICE_STATUS status;     
    DWORD CurrentState;   
	
    SUCCESS = QueryServiceStatus(hService, &status);   
	
    switch(status.dwCurrentState)   
    {   
	case SERVICE_RUNNING:   
		CurrentState = SERVICE_RUNNING;   
		LogMesg(-1,"Service RUNNING.");   
		break;   
	case SERVICE_STOPPED:   
		CurrentState = SERVICE_STOPPED;   
		LogMesg(-1,"Service STOPPED." );   
		break;   
	case SERVICE_PAUSED:   
		CurrentState = SERVICE_PAUSED;   
		LogMesg(-1,"Service PAUSED.");   
		break;   
	case SERVICE_CONTINUE_PENDING:   
		CurrentState = SERVICE_CONTINUE_PENDING;   
		LogMesg(-1,"Service is resuming...");   
		break;   
	case SERVICE_PAUSE_PENDING:   
		CurrentState = SERVICE_PAUSE_PENDING;   
		LogMesg(-1, "Service is pausing..." );   
		break;   
	case SERVICE_START_PENDING:   
		CurrentState = SERVICE_START_PENDING;   
		LogMesg(-1,"Service is starting..." );   
		break;   
	case SERVICE_STOP_PENDING:   
		CurrentState = SERVICE_STOP_PENDING;   
		LogMesg( -1,"Service is stopping..." );   
		break;   
	default:   
		break;   
    }   
	::CloseServiceHandle(hService);
    ::CloseServiceHandle(hSCM);
	//  SendStatusToSCM(CurrentState, NO_ERROR, 0, 0, 0);   
} */
/*void ConvertGBKToUtf8(char &strGBK)
{
	int len=MultiByteToWideChar(CP_ACP, 0, (LPCTSTR)strGBK, -1, NULL,0);
	wchar_t * wszUtf8 = new wchar_t [len];
	memset(wszUtf8, 0, len);
	MultiByteToWideChar(CP_ACP, 0, (LPCTSTR)strGBK, -1, wszUtf8, len);
	
	len = WideCharToMultiByte(CP_UTF8, 0, wszUtf8, -1, NULL, 0, NULL, NULL);
	char *szUtf8=new char[len + 1];
	memset(szUtf8, 0, len + 1);
	WideCharToMultiByte (CP_UTF8, 0, wszUtf8, -1, szUtf8, len, NULL,NULL);
	
	strGBK = *szUtf8;
	delete[] szUtf8;
	delete[] wszUtf8;
}*/
//int main(int argc,char** argv)
int main(int argc, TCHAR* argv[], TCHAR* envp[])
{
	
	ServiceMain();
 
	return 0;
}

int Updategps(int nIndex,string lng,string lat,int gpsflag)
{
    char TmpStr[1024];
	sprintf(TmpStr,"Updategps()");
	LogMesg(-1,TmpStr);
	CDBIndex DBIndex;
	int nDBIndex = DBIndex.GetDBIndex();
	CHECKINDEX0()
			char sql[1024];	
	string newLat;
	string newLng;
	
	UpdateGPS(lng,lat,newLng,newLat);
	sprintf(sql,"update ROMS200_TASKVALUE  set lng = '%s',lat = '%s',gpsflag = 1 where gpsflag = 0",newLng.c_str(),newLat.c_str());
	LogMesg(-1,sql);
	try
	{
		otl_stream otl_update(1, sql,*g_dbCfg[nDBIndex].m_db);
		otl_update.set_commit(0);
		int sqlrpc = otl_update.get_rpc();
		sprintf(TmpStr,"sqlrpc=%d,sql=%s",sqlrpc,sql);
		LogMesg(-1,TmpStr);
		otl_update.flush();
		g_dbCfg[nDBIndex].m_db->commit();
	}
	catch (otl_exception& p) { // intercept OTL exceptions
		LogMesg(-1,(char*)p.msg); // print out error message
		LogMesg(-1,(char*)p.stm_text); // print out SQL that caused the error
		LogMesg(-1,(char*)p.var_info); // print out the variable that caused the error
		ReConnect(nDBIndex);
		return 0 ;
	}
	return 0;
}

int Updateonline()
{
   char TmpStr[1024];
	sprintf(TmpStr,"Updateonline()");
	LogMesg(-1,TmpStr);
	CDBIndex DBIndex;
	int nDBIndex = DBIndex.GetDBIndex();
	CHECKINDEX0()
		
		char sql[1024];	
	sprintf(sql,"update CZ_TERM  set testvalue = 0  ");
	LogMesg(-1,sql);
	try
	{
		otl_stream otl_update(1, sql,*g_dbCfg[nDBIndex].m_db);
		otl_update.set_commit(0);
		int sqlrpc = otl_update.get_rpc();
		sprintf(TmpStr,"sqlrpc=%d,sql=%s",sqlrpc,sql);
		LogMesg(-1,TmpStr);
		otl_update.flush();
		g_dbCfg[nDBIndex].m_db->commit();
	}
	catch (otl_exception& p) { // intercept OTL exceptions
		LogMesg(-1,(char*)p.msg); // print out error message
		LogMesg(-1,(char*)p.stm_text); // print out SQL that caused the error
		LogMesg(-1,(char*)p.var_info); // print out the variable that caused the error
		ReConnect(nDBIndex);
		return 0 ;
	}
	return 0;
}

int UpdateOffline( )
{
	char TmpStr[1024];
	sprintf(TmpStr,"UpdateOffline()");
	LogMesg(-1,TmpStr);
	CDBIndex DBIndex;
	int nDBIndex = DBIndex.GetDBIndex();
	CHECKINDEX0()
		
		char sql[1024];	
	sprintf(sql,"update ROMS200_TERM  set online = 0  ");
	LogMesg(-1,sql);
	try
	{
		otl_stream otl_update(1, sql,*g_dbCfg[nDBIndex].m_db);
		otl_update.set_commit(0);
		int sqlrpc = otl_update.get_rpc();
		sprintf(TmpStr,"sqlrpc=%d,sql=%s",sqlrpc,sql);
		LogMesg(-1,TmpStr);
		otl_update.flush();
		g_dbCfg[nDBIndex].m_db->commit();
	}
	catch (otl_exception& p) { // intercept OTL exceptions
		LogMesg(-1,(char*)p.msg); // print out error message
		LogMesg(-1,(char*)p.stm_text); // print out SQL that caused the error
		LogMesg(-1,(char*)p.var_info); // print out the variable that caused the error
		ReConnect(nDBIndex);
		return 0 ;
	}
	return 0;
}

/*void CheckAuth()
{
	char key[1024];
	sprintf(key,"license");
//	printf("key=%s",key);
	KEYRESULT result;
	int ret = LoadLinkKEY(key,&result);
	//if(result.LicType)
//	printf("ret=%d\n",ret);
//	printf("LicType:%d\n",result.LicType);
//	printf("LicDays:%d\n",result.LicDays);
//	printf("LicDaysLeave:%d\n",result.LicDaysLeave);
	
	if(ret==0)
	{
		exit(0);
	}
}*/

void ServiceMain()
{
    

	LogMesg(0,"程序启动");
	//	g_stGlb.g_fpLogFile = NULL;
#if defined(WIN32)
	InitializeCriticalSection(&mutex_db);
	InitializeCriticalSection(&mutex_flw);
	InitializeCriticalSection(&mutex_log);
#endif
	g_stCfg.m_nMaxLogLine = 200000;
	TIni cfg;
#if defined(WIN32)
	cfg.OpenIniFile("d:\\roms\\bin\\config.ini");
#else
	cfg.OpenIniFile("/usr/roms/config/fh40g.ini");
#endif
	char TmpStr[1024];
	
	read_int(cfg, "XTOEMS", "PORT",(int&)g_stCfg.m_nPort );
	
	if(g_stCfg.m_nPort==0)
		g_stCfg.m_nPort = 6789;
	
	sprintf(TmpStr,"PORT=%d",g_stCfg.m_nPort);
	LogMesg(-1,TmpStr);
	
	read_int(cfg, "XTOEMS", "DBTYPE",(int&)g_stCfg.m_nDBType );
	sprintf(TmpStr,"DBTYPE=%d",g_stCfg.m_nDBType);
	LogMesg(-1,TmpStr);
	
	read_string(cfg, "XTOEMS", "OTL",  g_stCfg.m_sOTL, sizeof(g_stCfg.m_sOTL));
	sprintf(TmpStr,"OTL=%s len%d",g_stCfg.m_sOTL,strlen(g_stCfg.m_sOTL));
	LogMesg(-1,TmpStr);
	
	read_int(cfg, "XTOEMS", "KEEPLIVETIME",(int&)g_stCfg.m_keeplive );
	sprintf(TmpStr,"KEEPLIVETIME=%d",g_stCfg.m_keeplive);
	LogMesg(-1,TmpStr);

	read_string(cfg, "XTOEMS", "IP",  g_stCfg.m_sIP, sizeof(g_stCfg.m_sIP));
	sprintf(TmpStr,"IP=%s len%d",g_stCfg.m_sIP,strlen(g_stCfg.m_sIP));
	LogMesg(-1,TmpStr);
     
	read_int(cfg, "XTOEMS", "FLAG",(int&)g_stCfg.m_nLog );
	sprintf(TmpStr,"FLAG=%d",g_stCfg.m_nLog);
	LogMesg(-1,TmpStr);
	//char macode [1024];

	/************
	GetIpMac(g_stCfg.m_sIP,g_stCfg.m_sMacCode);

	printf("mac:%s",g_stCfg.m_sMacCode);
	if(strlen(g_stCfg.m_sMacCode)==0)
	{
	//	printf("授权错误\n");
		exit(0);
		//	return ;
	}
	

	CheckAuth();
	*************/
	
	g_stCfg.m_nDBConnNum =5;
	if(g_stCfg.m_keeplive<10)
		g_stCfg.m_keeplive = 10;
	
	g_stCfg.m_nTimerSeconds300=300;//5分钟300秒
	
	SockVarInit();
	
	CTcpAsyncSocket skt_server;
	if(!skt_server.Create(g_stCfg.m_nPort))//用指定端口创建套接字
	{
		sprintf(TmpStr,"create socket error port %d !",g_stCfg.m_nPort);
		LogMesg(-1,TmpStr);
	}
	if(!skt_server.Listen())
	{
		sprintf(TmpStr,"listen socket error port %d !",g_stCfg.m_nPort);
		return ;
	}
	
	
	
	otl_connect::otl_initialize(1); // initialize OCI environmentA
	InitDBCfg();
	
	sprintf(TmpStr,"xtvms系统启动");
	LogErrorSysInfo(SYSERR_IVR_START,TmpStr);
	
	
	
//	struct timeval  stWaitTime;//发送和接受的等待时间结构
	
	for(int nIndex=0;nIndex<MODULE_MAX;nIndex++)
	{
		skt_client_info[nIndex].skt_client.m_hSocket = INVALID_SOCKET;
		InitTerm(nIndex);
	//	sprintf(TmpStr,"nIndex=%d",nIndex);
	//	LogMesg(-1,TmpStr);
	}
	//GetNoticeID();
	(void) time(&g_stCfg.m_timer300);
	UpdateOffline();
	//Updateonline();
	while(1)
	{


		struct tm *tm_ptr = NULL;
		time_t tt;
		(void) time(&tt);
		tm_ptr = localtime(&tt);
		char date[100];
		strftime(date, 50, "%Y-%m-%d", tm_ptr);
		
		int nResult = strcmp(g_stCfg.m_sLogTime,date);
		if(nResult!=0)
		{
			//每天零点处理
			sprintf(g_stCfg.m_sLogTime,"%s",date);

			//CheckAuth();
		
		}
			
		
		proc(&skt_server);
		if(bStop==true)
			break;
	}
	
    //status.dwCurrentState = SERVICE_STOPPED;
    //SetServiceStatus(hServiceStatus, &status);
    //LogMesg(-1,_T("Service stopped"));
}



int CmdSet_Send(int nIndex)
{
//	cout<<"CMD_SET"<<endl;
//	struct timeval  stWaitTime;//发送和接受的等待时间结构
//	fd_set fdAll;//socket集合
//	fd_set fdwrite;//socket集合
	//@@1|CMD_SET||@@0"
	int speed = GetSpeed();
	GetTermInfo(nIndex);
	char buf[1024];
//	char logdata[1024];
//	char TmpStr[1024];

	struct tm *tm_ptr;
	time_t the_time;
	char systime[1024];
	(void) time(&the_time);
    tm_ptr = localtime(&the_time);
	skt_client_info[nIndex].m_nownerflag = 1;
	strftime( systime, 1024,"%Y-%m-%d %H:%M:%S", tm_ptr );
	sprintf(buf,"@@1|CMD_SET|%s|@@0",systime);
	
//	cout<<"buf:"<<buf<<endl;
	CmdData* data = (CmdData*)malloc(sizeof(CmdData));
	data->type = 0;
	data->status = 0;
	strcpy(data->cmd,buf);
	dlist_append(skt_client_info[nIndex].send_dlist, (void*)data);
	

	
	return 0;
}

int CmdSerial_Send(int nIndex)
{
	
//	struct timeval  stWaitTime;//发送和接受的等待时间结构
//	fd_set fdAll;//socket集合
//	fd_set fdwrite;//socket集合
	

	char buf[1024];
//	char logdata[1024];
//	char TmpStr[1024];
	
	struct tm *tm_ptr;
	time_t the_time;
	char systime[1024];
	(void) time(&the_time);
    tm_ptr = localtime(&the_time);

	strftime( systime, 1024,"%Y-%m-%d %H:%M:%S", tm_ptr );
	sprintf(buf,"@@1|CMD_SERIAL|%s|@@0",skt_client_info[nIndex].m_sSerialNo);
	
	CmdData* data = (CmdData*)malloc(sizeof(CmdData));
	data->type = 0;
	data->status = 0;
	strcpy(data->cmd,buf);
	dlist_append(skt_client_info[nIndex].send_dlist, (void*)data);
	
	return 0;
}
int TermNewTask(int nIndex, string humidity, string lat, string lng, string testtime, string taskname, string templ,char * taskid,int nbr)
{
	//cout<<"TERMNEWTASK"<<endl;

//	char buf[1024];
//	char logdata[1024];
	char TmpStr[1024];


	CDBIndex DBIndex;
	int nDBIndex = DBIndex.GetDBIndex();
	CHECKINDEX0()

	char sql[1024];
  //  char companyid[100];
    char termnumber[100]="";

	string newLat;
	string newLng;
	
	UpdateGPS(lng,lat,newLng,newLat);
/*	sprintf(sql,"select companyid from ROMS200_TERM where id = '%s' ", skt_client_info[nIndex].m_nTermID);
	LogMesg(nIndex,sql);
	try
	{
		otl_stream otl_selectcc(1, sql,*g_dbCfg[nDBIndex].m_db);
		
		if(!otl_selectcc.eof()) 
		{ 
			otl_selectcc>>companyid;
		}
		else
		{			
			return 0;
		}
	}
	catch (otl_exception& p) { // intercept OTL exceptions
		LogMesg(-1,(char*)p.msg); // print out error message
		LogMesg(-1,(char*)p.stm_text); // print out SQL that caused the error
		LogMesg(-1,(char*)p.var_info); // print out the variable that caused the error
		ReConnect(nDBIndex);
	}*/

    //sprintf(sql,"INSERT INTO XT_XLTASK(taskname,createtime,nbr,synflag) values('%s',getdate(),0,0)",skt_client_info[nIndex].m_sSerialNo);
	//sprintf(sql,"INSERT INTO CZ_TASK(id,createtime,humidity,lat,lng,measuretime,taskname,temperature,companyid,termid) values(uuid(),now(),'%s','%s','%s','%s','%s','%s','%s','%s')",humidity.c_str(),newLat.c_str(),newLng.c_str(),testtime.c_str(),taskname.c_str(),templ.c_str(),companyid,skt_client_info[nIndex].m_nTermID);
	  sprintf(sql,"INSERT INTO ROMS200_TASK(id,createtime,taskname,termid,nbr) values(uuid(),now(),'%s','%s',%d)",taskname.c_str(),skt_client_info[nIndex].m_nTermID,nbr);
    //cout<<"insert into xt_task"<<endl;
	LogMesg(nIndex,sql);
	try
	{
		otl_stream otl_update(1, sql,*g_dbCfg[nDBIndex].m_db);
		otl_update.set_commit(0);
		int sqlrpc = otl_update.get_rpc();
		sprintf(TmpStr,"sqlrpc=%d,sql=%s",sqlrpc,sql);
		LogMesg(-1,TmpStr);
		otl_update.flush();
		g_dbCfg[nDBIndex].m_db->commit();
	}
	catch (otl_exception& p) { // intercept OTL exceptions
		LogMesg(-1,(char*)p.msg); // print out error message
		LogMesg(-1,(char*)p.stm_text); // print out SQL that caused the error
		LogMesg(-1,(char*)p.var_info); // print out the variable that caused the error
		ReConnect(nDBIndex);
		return 0 ;
	}
	sprintf(sql,"select id from ROMS200_TASK where taskname= '%s' ", taskname.c_str());
	LogMesg(nIndex,sql);
	try
	{
		otl_stream otl_selectcc(1, sql,*g_dbCfg[nDBIndex].m_db);
		
		if(!otl_selectcc.eof()) 
		{ 
			otl_selectcc>>taskid;
			return 1;
		}
		else
		{			
			return 0;
		}
	}
	catch (otl_exception& p) { // intercept OTL exceptions
		LogMesg(-1,(char*)p.msg); // print out error message
		LogMesg(-1,(char*)p.stm_text); // print out SQL that caused the error
		LogMesg(-1,(char*)p.var_info); // print out the variable that caused the error
		ReConnect(nDBIndex);
	}
	
	return 0;
}
int  b = 0;
int CmdKeep_Send(int nIndex)
{
	//cout<<"CMD_KEEP"<<endl;
	struct timeval  stWaitTime;//发送和接受的等待时间结构
//	fd_set fdAll;//socket集合
//	fd_set fdwrite;//socket集合
	
	char buf[1024];
	char tmp[1024]="";
    char TmpStr[1024];

	sprintf(buf,"@@1|CMD_KEEP|%d|@@0", skt_client_info[nIndex].m_seqnum);
		sprintf(TmpStr,"buf=%s",buf);
			LogMesg(nIndex,TmpStr);
//	cout<<"buf:"<<buf<<endl;
//	LogMesg(-1,buf);
	stWaitTime.tv_sec = 0;
	stWaitTime.tv_usec = 5;

	CmdData* data = (CmdData*)malloc(sizeof(CmdData));
	data->type = 0;
	data->status = 0;
	strcpy(data->cmd,buf);
	dlist_append(skt_client_info[nIndex].send_dlist, (void*)data);
	return 0;
}

int CmdError_Send(int nIndex,char  msg)
{
	
//	struct timeval  stWaitTime;//发送和接受的等待时间结构
//	fd_set fdAll;//socket集合
//	fd_set fdwrite;//socket集合
	//@@1|CMD_SET||@@0"
	int speed = GetSpeed();
	char buf[1024];
	//char logdata[1024];

	//sprintf(logdata,"@@1|CMD_ERROR|%s|@@0",msg);
	//ConvertGBKToUtf8(msg);
	sprintf(buf,"@@1|CMD_ERROR|%s|@@0",msg);

	/*
	stWaitTime.tv_sec = 0;
	stWaitTime.tv_usec = 5;
	if(skt_client_info[nIndex].skt_client.m_hSocket==INVALID_SOCKET)
	{
		LogMesg(nIndex,"skt_client is invalid ");
		return 0;
	}
	
	FD_ZERO(&fdwrite);
	FD_SET(skt_client_info[nIndex].skt_client.m_hSocket,&fdwrite);
	int maxfd = skt_client_info[nIndex].skt_client.m_hSocket+1;
	int sret = select(maxfd,0,&fdwrite,0,&stWaitTime);
	if (sret >= 1)
	{	
		if(FD_ISSET(skt_client_info[nIndex].skt_client.m_hSocket,&fdwrite))
		{
			int len = skt_client_info[nIndex].skt_client.Send(data,strlen(data));
			LogMesg(nIndex, logdata);
		//	skt_client_info[nIndex].skt_client.Close();
			//	skt_client_info[nIndex].m_nTermID = 0;
			return len;
			
		}
	}
	else
	{
		skt_client_info[nIndex].m_nTermID = 0;
		skt_client_info[nIndex].skt_client.Close();
		char TmpStr[1024];
		sprintf(TmpStr,"发送CLIENT包错误 IP %s:%s 工号:%s",skt_client_info[nIndex].m_sPeerAddress,skt_client_info[nIndex].m_sPort,skt_client_info[nIndex].m_sID);
		LogErrorSysInfo(SYSERR_AGT_SENDCLIENTERR,TmpStr); 
		LogMesg(nIndex,"skt_client.close");
	}
	*/
	CmdData* data = (CmdData*)malloc(sizeof(CmdData));
	data->type = 0;
	data->status = 0;
	strcpy(data->cmd,buf);
	dlist_append(skt_client_info[nIndex].send_dlist, (void*)data);

	return 0;
}

int CmdNotice_Send(int nIndex)
{
	
//	struct timeval  stWaitTime;//发送和接受的等待时间结构
//	fd_set fdAll;//socket集合
//	fd_set fdwrite;//socket集合
	//@@1|CMD_SET||@@0"
	int speed = GetSpeed();

	char buf[1024];
	//CString notice = skt_client_info[nIndex].m_sNotice;
	sprintf(buf,"@@1|CMD_NOTICE|%s|@@0",skt_client_info[nIndex].m_sNotice);
	/*
	ConvertGBKToUtf8(notice);
	
	sprintf(data,"@@1|CMD_NOTICE|%s|@@0",notice);
	sprintf(logdata,"@@1|CMD_NOTICE|%s|@@0",skt_client_info[nIndex].m_sNotice);
	stWaitTime.tv_sec = 0;
	stWaitTime.tv_usec = 5;
	if(skt_client_info[nIndex].skt_client.m_hSocket==INVALID_SOCKET)
	{
		LogMesg(nIndex,"skt_client is invalid ");
		return 0;
	}
	
	FD_ZERO(&fdwrite);
	FD_SET(skt_client_info[nIndex].skt_client.m_hSocket,&fdwrite);
	int maxfd = skt_client_info[nIndex].skt_client.m_hSocket+1;
	int sret = select(maxfd,0,&fdwrite,0,&stWaitTime);
	if (sret >= 1)
	{	
		if(FD_ISSET(skt_client_info[nIndex].skt_client.m_hSocket,&fdwrite))
		{
			int len = skt_client_info[nIndex].skt_client.Send(data,strlen(data));
			LogMesg(nIndex, logdata);
			return len;
			
		}
	}
	else
	{
		skt_client_info[nIndex].m_nTermID = 0;
		skt_client_info[nIndex].skt_client.Close();
		char TmpStr[1024];
		sprintf(TmpStr,"发送CLIENT包错误 IP %s:%s 工号:%s",skt_client_info[nIndex].m_sPeerAddress,skt_client_info[nIndex].m_sPort,skt_client_info[nIndex].m_sID);
		LogErrorSysInfo(SYSERR_AGT_SENDCLIENTERR,TmpStr); 
		LogMesg(nIndex,"skt_client.close");
	}
	*/
	CmdData* data = (CmdData*)malloc(sizeof(CmdData));
	data->type = 0;
	data->status = 0;
	strcpy(data->cmd,buf);
	dlist_append(skt_client_info[nIndex].send_dlist, (void*)data);

	return 0;
}
int NetStart_Send(int nIndex)
{
	
//	struct timeval  stWaitTime;//发送和接受的等待时间结构
//	fd_set fdAll;//socket集合
//	fd_set fdwrite;//socket集合
	//@@1|CMD_SET||@@0"
	char buf[1024] = "@@1|CMD_START|@@0";
	/*
	stWaitTime.tv_sec = 0;
	stWaitTime.tv_usec = 5;
	if(skt_client_info[nIndex].skt_client.m_hSocket==INVALID_SOCKET)
	{
		LogMesg(nIndex,"skt_client is invalid ");
		return 0;
	}
	
	FD_ZERO(&fdwrite);
	FD_SET(skt_client_info[nIndex].skt_client.m_hSocket,&fdwrite);
	int maxfd = skt_client_info[nIndex].skt_client.m_hSocket+1;
	int sret = select(maxfd,0,&fdwrite,0,&stWaitTime);
	if (sret >= 1)
	{	
		if(FD_ISSET(skt_client_info[nIndex].skt_client.m_hSocket,&fdwrite))
		{
			int len = skt_client_info[nIndex].skt_client.Send(data,strlen(data));
			LogMesg(nIndex, data);
			return len;
			
		}
	}
	else
	{
		skt_client_info[nIndex].m_nTermID = 0;
		skt_client_info[nIndex].skt_client.Close();
		char TmpStr[1024];
		sprintf(TmpStr,"发送CLIENT包错误 IP %s:%s 工号:%s",skt_client_info[nIndex].m_sPeerAddress,skt_client_info[nIndex].m_sPort,skt_client_info[nIndex].m_sID);
		LogErrorSysInfo(SYSERR_AGT_SENDCLIENTERR,TmpStr); 
		LogMesg(nIndex,"skt_client.close");
	}
	*/
	CmdData* data = (CmdData*)malloc(sizeof(CmdData));
	data->type = 0;
	data->status = 0;
	strcpy(data->cmd,buf);
	dlist_append(skt_client_info[nIndex].send_dlist, (void*)data);

	return 0;
}


int TermCheck(int nIndex,string sNumber,char * tID)
{
	
	CDBIndex DBIndex;
	int nDBIndex = DBIndex.GetDBIndex();
	CHECKINDEX0()
	
    char sql[1024];
	sprintf(sql,"select id  from ROMS200_TERM where termnumber = '%s' ",sNumber.c_str());
	LogMesg(nIndex,sql);
	try
	{
		otl_stream otl_selectcc(1, sql,*g_dbCfg[nDBIndex].m_db);
		//char CC[100]="";	
		if(!otl_selectcc.eof()) 
		{ 
			otl_selectcc>>tID;	
         
			return 1;
		}
		else
		{
			
			return 0;
		}
	}
	catch (otl_exception& p) { // intercept OTL exceptions
		LogMesg(-1,(char*)p.msg); // print out error message
		LogMesg(-1,(char*)p.stm_text); // print out SQL that caused the error
		LogMesg(-1,(char*)p.var_info); // print out the variable that caused the error
		ReConnect(nDBIndex);
	}

	return 0;
}


int TermCheckNowFlag(int nIndex)
{
	
	CDBIndex DBIndex;
	int nDBIndex = DBIndex.GetDBIndex();
	CHECKINDEX0()
		
	char sql[1024];	
	
	sprintf(sql,"select count(*)  from XT_TERM where id = '%s' and newflag = 1 ",skt_client_info[nIndex].m_nTermID);
	//LogMesg(nIndex,sql);
	try
	{
		otl_stream otl_selectcc(1, sql,*g_dbCfg[nDBIndex].m_db);
		int  CC=0;	
		if(!otl_selectcc.eof()) 
		{ 
			otl_selectcc>>CC;				
			return CC;
		}
		else
		{		
			return 0;
		}
	}
	catch (otl_exception& p) { // intercept OTL exceptions
		LogMesg(-1,(char*)p.msg); // print out error message
		LogMesg(-1,(char*)p.stm_text); // print out SQL that caused the error
		LogMesg(-1,(char*)p.var_info); // print out the variable that caused the error
		ReConnect(nDBIndex);
	}
	
	return 0;
}

int TermCheckSerial(int nIndex)
{
	char serialno[1024]={0};
	CDBIndex DBIndex;
	int nDBIndex = DBIndex.GetDBIndex();
	CHECKINDEX0()
		
	char sql[1024];	
	
	sprintf(sql,"select serialno from XT_TERM where id = %d  ",skt_client_info[nIndex].m_nTermID);
	LogMesg(nIndex,sql);
	try
	{
		otl_stream otl_selectcc(1, sql,*g_dbCfg[nDBIndex].m_db);
		int  CC=0;	
		if(!otl_selectcc.eof()) 
		{ 
			otl_selectcc>>serialno;	
			
			if(strcmp(serialno,skt_client_info[nIndex].m_sSerialNo)==0)
			{
				return 0;
			}
			else
			{
				return 1;
			}
		}
		else
		{
			
			return 0;
		}
	}
	catch (otl_exception& p) { // intercept OTL exceptions
		LogMesg(-1,(char*)p.msg); // print out error message
		LogMesg(-1,(char*)p.stm_text); // print out SQL that caused the error
		LogMesg(-1,(char*)p.var_info); // print out the variable that caused the error
		ReConnect(nDBIndex);
	}
	
	return 0;
}
int update_term(int nIndex,string lat,string lng,string termbattery,string testvalue)
{
	char TmpStr[1024];
    CDBIndex DBIndex;
	int nDBIndex = DBIndex.GetDBIndex();
	CHECKINDEX0()
	char sql[1024];
	string newLat;
	string newLng;
	
	UpdateGPS(lng,lat,newLng,newLat);
	sprintf(sql,"update ROMS200_TERM SET lat='%s', lng='%s', powervalue='%s', testvalue='%s' where id = '%s'",newLat.c_str(),newLng.c_str(),termbattery.c_str(),testvalue.c_str(),skt_client_info[nIndex].m_nTermID);
	
	LogMesg(nIndex,sql);
	try
	{
		otl_stream otl_update(1, sql,*g_dbCfg[nDBIndex].m_db);
		otl_update.set_commit(0);
		int sqlrpc = otl_update.get_rpc();
		sprintf(TmpStr,"sqlrpc=%d,sql=%s",sqlrpc,sql);
		LogMesg(-1,TmpStr);
		otl_update.flush();
		g_dbCfg[nDBIndex].m_db->commit();
	}
	catch (otl_exception& p) { // intercept OTL exceptions
		LogMesg(-1,(char*)p.msg); // print out error message
		LogMesg(-1,(char*)p.stm_text); // print out SQL that caused the error
		LogMesg(-1,(char*)p.var_info); // print out the variable that caused the error
		ReConnect(nDBIndex);
		return 0 ;
	}
	return 0;
}

int TermCheckNewTask(int nIndex,string taskname,char * taskid)
{   //cout<<"TERMCHECKNEWTASK"<<endl;
	char serialno[1024]={0};
	CDBIndex DBIndex;
	int nDBIndex = DBIndex.GetDBIndex();
	CHECKINDEX0()
    int time;	
	char sql[1024];	
    char str[1024];

	
	sprintf(sql,"select id from ROMS200_TASK where taskname = '%s' ",taskname.c_str());
	LogMesg(nIndex,sql);
	try
	{
		otl_stream otl_selectcc(1, sql,*g_dbCfg[nDBIndex].m_db);
	
		if(!otl_selectcc.eof()) 
		{ 
			otl_selectcc>>taskid;	
			//判断时间是否在同一天
			sprintf(sql,"SELECT  TO_DAYS(NOW())- TO_DAYS(createtime) FROM ROMS200_TASK where taskname = '%s' order by createtime desc limit 0,1 ",taskname.c_str());
			LogMesg(nIndex,sql);
			try
			{
				otl_stream otl_selectcc(1, sql,*g_dbCfg[nDBIndex].m_db);
				
				if(!otl_selectcc.eof()) 
				{ 
					otl_selectcc>>time;

					sprintf(str,"time=%d",time);
					LogMesg(nIndex,str);
					if(time>=1)
					return 0;
					else
						return 1;
					
				}
				
				
				
			}
			catch (otl_exception& p) { // intercept OTL exceptions
				LogMesg(-1,(char*)p.msg); // print out error message
				LogMesg(-1,(char*)p.stm_text); // print out SQL that caused the error
				LogMesg(-1,(char*)p.var_info); // print out the variable that caused the error
				ReConnect(nDBIndex);
	}
				return 1;
						
		}
		else
		{
			return 0;
		}
	}
	catch (otl_exception& p) { // intercept OTL exceptions
		LogMesg(-1,(char*)p.msg); // print out error message
		LogMesg(-1,(char*)p.stm_text); // print out SQL that caused the error
		LogMesg(-1,(char*)p.var_info); // print out the variable that caused the error
		ReConnect(nDBIndex);
	}

	
	return 0;
}
int TermUpdateNowFlag(int nIndex)
{
	char TmpStr[1024];
	CDBIndex DBIndex;
	int nDBIndex = DBIndex.GetDBIndex();
	CHECKINDEX0()
		
	char sql[1024];	
	
	sprintf(sql,"update XT_TERM  set newflag = 0,serialno=%s where id = '%s'  ",skt_client_info[nIndex].m_sSerialNo,skt_client_info[nIndex].m_nTermID);
	LogMesg(-1,sql);
	try
	{
		otl_stream otl_update(1, sql,*g_dbCfg[nDBIndex].m_db);
		otl_update.set_commit(0);
		int sqlrpc = otl_update.get_rpc();
		sprintf(TmpStr,"sqlrpc=%d,sql=%s",sqlrpc,sql);
		LogMesg(-1,TmpStr);
		otl_update.flush();
		g_dbCfg[nDBIndex].m_db->commit();
	}
	catch (otl_exception& p) { // intercept OTL exceptions
		LogMesg(-1,(char*)p.msg); // print out error message
		LogMesg(-1,(char*)p.stm_text); // print out SQL that caused the error
		LogMesg(-1,(char*)p.var_info); // print out the variable that caused the error
		ReConnect(nDBIndex);
		return 0 ;
	}
	
	return 0;
}
int GetTermInfo(int nIndex)
{
	/*
	CDBIndex DBIndex;
	int nDBIndex = DBIndex.GetDBIndex();
	CHECKINDEX0()
		
	char sql[1024];	

	
	sprintf(sql,"select termname, testman,phone,ownerflag,  borrowflag,borrowerip,borrowerport from XT_TERM where id =%d  ",skt_client_info[nIndex].m_nTermID);
	LogMesg(nIndex,sql);
	try
	{
		otl_stream otl_selectcc(1, sql,*g_dbCfg[nDBIndex].m_db);
	
		if(!otl_selectcc.eof()) 
		{ 
			otl_selectcc>>skt_client_info[nIndex].m_sTermName>>skt_client_info[nIndex].m_sTestMan>>skt_client_info[nIndex].m_sPhone>>skt_client_info[nIndex].m_nownerflag>>skt_client_info[nIndex].m_nBorrowFlag>>skt_client_info[nIndex].m_sBorrowerip>>skt_client_info[nIndex].m_sBorrowerport;	
			
			
		}
		else
		{
			
			return 0;
		}
	}
	catch (otl_exception& p) { // intercept OTL exceptions
		LogMesg(-1,(char*)p.msg); // print out error message
		LogMesg(-1,(char*)p.stm_text); // print out SQL that caused the error
		LogMesg(-1,(char*)p.var_info); // print out the variable that caused the error
		ReConnect(nDBIndex);
	}
	*/
	return 0;
}



int TermOnline(int nIndex,int on)
{   //cout<<"TermOnline"<<endl;
	char TmpStr[1024];
	CDBIndex DBIndex;
	int nDBIndex = DBIndex.GetDBIndex();
	CHECKINDEX0()
		
		char sql[1024];	
	LogMesg(-1,"TermOnline");
	//判断是否有相同的终端在连
	if(on==1)
	{
		for(int n=0;n<MODULE_MAX;n++)
		{
			if(n!=nIndex&&strcmp(skt_client_info[n].m_nTermID,skt_client_info[nIndex].m_nTermID)==0)
			{
				strcpy(skt_client_info[n].m_nTermID,"");
			}
		}
	}
	int id = strlen(skt_client_info[nIndex].m_nTermID);
	sprintf(TmpStr,"id=%d",id);
	LogMesg(nIndex,TmpStr);
	if(strlen(skt_client_info[nIndex].m_nTermID)!=0)
	{
		sprintf(sql,"update ROMS200_TERM  set online = %d where id = '%s'  ",on,skt_client_info[nIndex].m_nTermID);
		LogMesg(-1,sql);
		try
		{
			otl_stream otl_update(1, sql,*g_dbCfg[nDBIndex].m_db);
			otl_update.set_commit(0);
			int sqlrpc = otl_update.get_rpc();
			sprintf(TmpStr,"sqlrpc=%d,sql=%s",sqlrpc,sql);
			LogMesg(-1,TmpStr);
			otl_update.flush();
			g_dbCfg[nDBIndex].m_db->commit();
		}
		catch (otl_exception& p) { // intercept OTL exceptions
			LogMesg(-1,(char*)p.msg); // print out error message
			LogMesg(-1,(char*)p.stm_text); // print out SQL that caused the error
			LogMesg(-1,(char*)p.var_info); // print out the variable that caused the error
			ReConnect(nDBIndex);
			return 0 ;
		}
	}
	return 0;
}



int MsgSendAll(int ID,char*sender,char*msgcontent,char*createtime)
{
	
	struct timeval  stWaitTime;//发送和接受的等待时间结构
//	fd_set fdAll;//socket集合
//	fd_set fdwrite;//socket集合
	//@@1|CMD_SET||@@0"
	char buf[1024];
//	char logdata[1024];
//	CString msg = msgcontent;
//	CString s = sender;
//	ConvertGBKToUtf8(msg);
//	ConvertGBKToUtf8(s);

//	sprintf(data,"@@1|CMD_MSG|%d|%s|%s|%s|@@0",ID,s,msg,createtime);
	sprintf(buf,"@@1|CMD_MSG|%d|%s|%s|%s|@@0",ID,sender,msgcontent,createtime);
	
	stWaitTime.tv_sec = 0;
	stWaitTime.tv_usec = 5;

	for(int nIndex=0;nIndex<MODULE_MAX;nIndex++)
	{
		if(skt_client_info[nIndex].skt_client.m_hSocket != INVALID_SOCKET)
		{
			CmdData* data = (CmdData*)malloc(sizeof(CmdData));
			data->type = 0;
			data->status = 0;
			strcpy(data->cmd,buf);
			dlist_append(skt_client_info[nIndex].send_dlist, (void*)data);

			/*
			
			FD_ZERO(&fdwrite);
			FD_SET(skt_client_info[nIndex].skt_client.m_hSocket,&fdwrite);
			int maxfd = skt_client_info[nIndex].skt_client.m_hSocket+1;
			int sret = select(maxfd,0,&fdwrite,0,&stWaitTime);
			if (sret >= 1)
			{	
				if(FD_ISSET(skt_client_info[nIndex].skt_client.m_hSocket,&fdwrite))
				{
					int len = skt_client_info[nIndex].skt_client.Send(data,strlen(data));
					LogMesg(nIndex, logdata);
				
					return len;
					
				}
			}
			else
			{
				skt_client_info[nIndex].m_nTermID = 0;
				skt_client_info[nIndex].skt_client.Close();
				char TmpStr[1024];
				sprintf(TmpStr,"发送CLIENT包错误 IP %s:%s 工号:%s",skt_client_info[nIndex].m_sPeerAddress,skt_client_info[nIndex].m_sPort,skt_client_info[nIndex].m_sID);
				LogErrorSysInfo(SYSERR_AGT_SENDCLIENTERR,TmpStr); 
				LogMesg(nIndex,"skt_client.close");
			}
			return 0;
			*/
		}
	}
	return 0;

}

int MsgSend(int nIndex,char*buf)
{
	
	struct timeval  stWaitTime;//发送和接受的等待时间结构
//	fd_set fdAll;//socket集合
//	fd_set fdwrite;//socket集合
	//@@1|CMD_SET||@@0"
//	char data[1024];
//	char logdata[1024];
//	CString msg =buf;
//	CString s = sender;
//	ConvertGBKToUtf8(msg);
//	sprintf(data,"%s",msg);
//	ConvertGBKToUtf8(s);
//	sprintf(data,"@@1|CMD_MSG|%d|%s|%s|%s|@@0",ID,s,msg,createtime);
//	sprintf(logdata,"@@1|CMD_MSG|%d|%s|%s|%s|@@0",ID,sender,msgcontent,createtime);
	stWaitTime.tv_sec = 0;
	stWaitTime.tv_usec = 5;
	CmdData* data = (CmdData*)malloc(sizeof(CmdData));
	data->type = 0;
	data->status = 0;
	strcpy(data->cmd,buf);
	dlist_append(skt_client_info[nIndex].send_dlist, (void*)data);
	/*
	if(skt_client_info[nIndex].skt_client.m_hSocket != INVALID_SOCKET)
	{
		
		FD_ZERO(&fdwrite);
		FD_SET(skt_client_info[nIndex].skt_client.m_hSocket,&fdwrite);
		int maxfd = skt_client_info[nIndex].skt_client.m_hSocket+1;
		int sret = select(maxfd,0,&fdwrite,0,&stWaitTime);
		if (sret >= 1)
		{	
			if(FD_ISSET(skt_client_info[nIndex].skt_client.m_hSocket,&fdwrite))
			{
				int len = skt_client_info[nIndex].skt_client.Send(data,strlen(data));
				LogMesg(nIndex, buf);
				return len;
				
			}
		}
		else
		{
			skt_client_info[nIndex].m_nTermID = 0;
			skt_client_info[nIndex].skt_client.Close();
			char TmpStr[1024];
			sprintf(TmpStr,"发送CLIENT包错误 IP %s:%s 工号:%s",skt_client_info[nIndex].m_sPeerAddress,skt_client_info[nIndex].m_sPort,skt_client_info[nIndex].m_sID);
			LogErrorSysInfo(SYSERR_AGT_SENDCLIENTERR,TmpStr); 
			LogMesg(nIndex,"skt_client.close");
		}
		return 0;
	}
	*/
	return 0;
	
}

int MsgSendOne(int nIndex,int ID,char*sender,char*msgcontent,char*createtime)
{
	
	struct timeval  stWaitTime;//发送和接受的等待时间结构
//	fd_set fdAll;//socket集合
//	fd_set fdwrite;//socket集合
	//@@1|CMD_SET||@@0"
	char buf[1024];
//	char logdata[1024];
//	CString msg = msgcontent;
//	CString s = sender;
//	ConvertGBKToUtf8(msg);
//	ConvertGBKToUtf8(s);
//	sprintf(data,"@@1|CMD_MSG|%d|%s|%s|%s|@@0",ID,s,msg,createtime);
	sprintf(buf,"@@1|CMD_MSG|%d|%s|%s|%s|@@0",ID,sender,msgcontent,createtime);
	stWaitTime.tv_sec = 0;
	stWaitTime.tv_usec = 5;

	CmdData* data = (CmdData*)malloc(sizeof(CmdData));
	data->type = 0;
	data->status = 0;
	strcpy(data->cmd,buf);
	dlist_append(skt_client_info[nIndex].send_dlist, (void*)data);
	/*

	if(skt_client_info[nIndex].skt_client.m_hSocket != INVALID_SOCKET)
	{
		
		FD_ZERO(&fdwrite);
		FD_SET(skt_client_info[nIndex].skt_client.m_hSocket,&fdwrite);
		int maxfd = skt_client_info[nIndex].skt_client.m_hSocket+1;
		int sret = select(maxfd,0,&fdwrite,0,&stWaitTime);
		if (sret >= 1)
		{
			if(FD_ISSET(skt_client_info[nIndex].skt_client.m_hSocket,&fdwrite))
			{
				int len = skt_client_info[nIndex].skt_client.Send(data,strlen(data));
				LogMesg(nIndex, logdata);
				return len;
				
			}
		}
		else
		{
			skt_client_info[nIndex].m_nTermID = 0;
			skt_client_info[nIndex].skt_client.Close();
			char TmpStr[1024];
			sprintf(TmpStr,"发送CLIENT包错误 IP %s:%s 工号:%s",skt_client_info[nIndex].m_sPeerAddress,skt_client_info[nIndex].m_sPort,skt_client_info[nIndex].m_sID);
			LogErrorSysInfo(SYSERR_AGT_SENDCLIENTERR,TmpStr); 
			LogMesg(nIndex,"skt_client.close");
		}
		return 0;
	}
*/
	return 0;
	
}


int MsgCheck()
{
	
	CDBIndex DBIndex;
	int nDBIndex = DBIndex.GetDBIndex();
	CHECKINDEX0()
		
	char sql[1024];	
	
	int ID;
	char sender[1024];
	char msgcontent[1024];
	char createtime[1024];
	sprintf(sql,"select id,sender,msgcontent,CONVERT(varchar, createtime, 120 )  from xt_sendmsg where sendflag = 0  order by id ");
	//LogMesg(-1,sql);
	try
	{
		otl_stream otl_selectcc(1, sql,*g_dbCfg[nDBIndex].m_db);
		int  CC=0;	
		while(!otl_selectcc.eof()) 
		{ 
			otl_selectcc>>ID>>sender>>msgcontent>>createtime;	
			MsgSendAll(ID,sender,msgcontent,createtime);
			UpdateMsg(ID);
	
		}
		
	}
	catch (otl_exception& p) { // intercept OTL exceptions
		LogMesg(-1,(char*)p.msg); // print out error message
		LogMesg(-1,(char*)p.stm_text); // print out SQL that caused the error
		LogMesg(-1,(char*)p.var_info); // print out the variable that caused the error
		ReConnect(nDBIndex);
	}
	
	return 0;
}


int TimeoutCheck()
{
	
	for(int nIndex=0;nIndex<MODULE_MAX;nIndex++)
	{
		if(skt_client_info[nIndex].skt_client.m_hSocket != INVALID_SOCKET)
		{
			time_t tNowTime;
			(void) time(&tNowTime);
			int esptime =  tNowTime - skt_client_info[nIndex].m_keeplivetime ;
			if(esptime>60)
			{
				skt_client_info[nIndex].skt_client.Close();
			}
		}
	}
	return 0;
}

int GetNoticeID()
{
	CDBIndex DBIndex;
	int nDBIndex = DBIndex.GetDBIndex();
	CHECKINDEX0()		
	char sql[1024];	
	sprintf(sql,"select top 1 id  from xt_notice  order by id desc ");
	try
	{
		otl_stream otl_selectcc(1, sql,*g_dbCfg[nDBIndex].m_db);
		int  CC=0;	
		if(!otl_selectcc.eof()) 
		{ 
			otl_selectcc>>g_stCfg.m_nNoticeID;		
		}	
	}
	catch (otl_exception& p) { // intercept OTL exceptions
		LogMesg(-1,(char*)p.msg); // print out error message
		LogMesg(-1,(char*)p.stm_text); // print out SQL that caused the error
		LogMesg(-1,(char*)p.var_info); // print out the variable that caused the error
		ReConnect(nDBIndex);
	}
	return 0;
}


int NoticeCheck()
{
	
	CDBIndex DBIndex;
	int nDBIndex = DBIndex.GetDBIndex();
	CHECKINDEX0()
		
	char sql[1024];	
	
//	int ID;
//	char sender[1024];
	char msgcontent[1024];
//	char createtime[1024];
	sprintf(sql,"select top 1  id ,syscontent from xt_notice where id>%d  order by id desc ",g_stCfg.m_nNoticeID);
	//LogMesg(-1,sql);
	try
	{
		otl_stream otl_selectcc(1, sql,*g_dbCfg[nDBIndex].m_db);
		int  CC=0;	
		if(!otl_selectcc.eof()) 
		{ 
			otl_selectcc>>g_stCfg.m_nNoticeID>>msgcontent;	
			for(int nIndex=0;nIndex<MODULE_MAX;nIndex++)
			{
				if(skt_client_info[nIndex].skt_client.m_hSocket!=INVALID_SOCKET)
				{
					strcpy(skt_client_info[nIndex].m_sNotice,msgcontent);
					CmdNotice_Send(nIndex);
				}
			
			}
			
			
		}
		
	}
	catch (otl_exception& p) { // intercept OTL exceptions
		LogMesg(-1,(char*)p.msg); // print out error message
		LogMesg(-1,(char*)p.stm_text); // print out SQL that caused the error
		LogMesg(-1,(char*)p.var_info); // print out the variable that caused the error
		ReConnect(nDBIndex);
	}
	
	return 0;
}


int GetSpeed()
{
	return 2;
	/*
	CDBIndex DBIndex;
	int nDBIndex = DBIndex.GetDBIndex();
	CHECKINDEX0()
		
		char sql[1024];	
	
	int ID;
	int speed = 2;
	char sender[1024];
	char msgcontent[1024];
	char createtime[1024];
	sprintf(sql,"select speed from XT_SYSCONFIG  ");
	LogMesg(-1,sql);
	try
	{
		otl_stream otl_selectcc(1, sql,*g_dbCfg[nDBIndex].m_db);
		int  CC=0;	
		while(!otl_selectcc.eof()) 
		{ 
			otl_selectcc>>speed;	
			
			
		}
		
	}
	catch (otl_exception& p) { // intercept OTL exceptions
		LogMesg(-1,(char*)p.msg); // print out error message
		LogMesg(-1,(char*)p.stm_text); // print out SQL that caused the error
		LogMesg(-1,(char*)p.var_info); // print out the variable that caused the error
		ReConnect(nDBIndex);
	}
	
	return speed;
	*/
}

int GetNotice(int nIndex)
{
	
	CDBIndex DBIndex;
	int nDBIndex = DBIndex.GetDBIndex();
	CHECKINDEX0()
	char sql[1024];	
	sprintf(sql,"select top 1 syscontent  from xt_notice order by id desc  ");
//	LogMesg(-1,sql);
	try
	{
		otl_stream otl_selectcc(1, sql,*g_dbCfg[nDBIndex].m_db);
		int  CC=0;	
		while(!otl_selectcc.eof()) 
		{ 
			otl_selectcc>>skt_client_info[nIndex].m_sNotice;		
		}
	}
	catch (otl_exception& p) { // intercept OTL exceptions
		LogMesg(-1,(char*)p.msg); // print out error message
		LogMesg(-1,(char*)p.stm_text); // print out SQL that caused the error
		LogMesg(-1,(char*)p.var_info); // print out the variable that caused the error
		ReConnect(nDBIndex);
	}
	
	return 1;
}

int MsgSendList(int nIndex)
{
	return 0;
	CDBIndex DBIndex;
	int nDBIndex = DBIndex.GetDBIndex();
	CHECKINDEX0()
		
	char sql[1024];	
	
	int ID;
	char sender[1024];
	char msgcontent[1024];
	char createtime[1024];
	char tmp[1024]="";
	char buf[1024]="";
	
	
	sprintf(sql,"select top 10 id,sender,msgcontent,CONVERT(varchar, createtime, 120 )  from xt_sendmsg  order by id  ");
	//LogMesg(-1,sql);
	try
	{
		otl_stream otl_selectcc(1, sql,*g_dbCfg[nDBIndex].m_db);
		int  CC=0;	
		while(!otl_selectcc.eof()) 
		{ 
			otl_selectcc>>ID>>sender>>msgcontent>>createtime;	
			MsgSendOne(nIndex,ID,sender,msgcontent,createtime);
		//	sprintf(tmp,"@@1|CMD_MSG|%d|%s|%s|%s|@@0",ID,sender,msgcontent,createtime);	
		//	strcat(buf , tmp);
		}
	//	MsgSend(nIndex,buf);
		
	}
	catch (otl_exception& p) { // intercept OTL exceptions
		LogMesg(-1,(char*)p.msg); // print out error message
		LogMesg(-1,(char*)p.stm_text); // print out SQL that caused the error
		LogMesg(-1,(char*)p.var_info); // print out the variable that caused the error
		ReConnect(nDBIndex);
	}
	
	return 0;
}

int UpdateMsg(int ID )
{
	char TmpStr[1024];
	sprintf(TmpStr,"UpdateMsg(%d)",ID);
	LogMesg(-1,TmpStr);
	CDBIndex DBIndex;
	int nDBIndex = DBIndex.GetDBIndex();
	CHECKINDEX0()
		
	char sql[1024];	
	

	
	
	sprintf(sql,"update xt_sendmsg  set sendflag = 1 where id = %d  ",ID);
	LogMesg(-1,sql);
	try
	{
		otl_stream otl_update(1, sql,*g_dbCfg[nDBIndex].m_db);
		otl_update.set_commit(0);
		int sqlrpc = otl_update.get_rpc();
		sprintf(TmpStr,"sqlrpc=%d,sql=%s",sqlrpc,sql);
		LogMesg(-1,TmpStr);
		otl_update.flush();
		g_dbCfg[nDBIndex].m_db->commit();
	}
	catch (otl_exception& p) { // intercept OTL exceptions
		LogMesg(-1,(char*)p.msg); // print out error message
		LogMesg(-1,(char*)p.stm_text); // print out SQL that caused the error
		LogMesg(-1,(char*)p.var_info); // print out the variable that caused the error
		ReConnect(nDBIndex);
		return 0 ;
	}
	return 0;
}



int RecvFromClient(int nIndex)
{
	char TmpStr[1024];
	int offset = 0;
	int cc = 1;
	int pklen = 0;

	memset(skt_client_info[nIndex].m_szRecvBuf,'\0',1024);
	cc = skt_client_info[nIndex].skt_client.Receive(skt_client_info[nIndex].m_szRecvBuf,1024);
	
	sprintf(TmpStr,"收取%d",cc);
	LogMesg(nIndex,TmpStr);
	if (cc == 0 || cc == -1) 
	{
			
			return FALSE;
	}
	return cc;
	


}



void SetTimeInterval(TimeInterval &stPtval)
{
#if defined(WIN32)
	SYSTEMTIME systemTime;
	GetLocalTime(&systemTime);
	time((time_t *)(&stPtval.m_nSec));
	stPtval.m_nuSec =systemTime.wMilliseconds  ;
#else
	struct timeval tv;
	gettimeofday (&tv , NULL);
	stPtval.m_nSec = tv.tv_sec;
	stPtval.m_nuSec = tv.tv_usec;
#endif
}
void  LogErrorSysInfo(int errtype,char*pInfo)
{

	/*
	char sql[1024];
	
	char TmpStr[1024];
	CDBIndex DBIndex;
	int nDBIndex = DBIndex.GetDBIndex();
	CHECKINDEX()	
	sprintf(sql,"insert into  TAGA_TALKIN_SYSERROR (errtype, errinfo,flag,appid)  values (%d,'%s',0,%d)",errtype,pInfo,g_stCfg.m_iUnitID);	
	try
	{
		otl_stream otl_update(1, sql,*g_dbCfg[nDBIndex].m_db);
	otl_update.set_commit(0);
	int sqlrpc = otl_update.get_rpc();
	sprintf(TmpStr,"sqlrpc=%d,sql=%s",sqlrpc,sql);
	LogMesg(-1,TmpStr);
	otl_update.flush();
	g_dbCfg[nDBIndex].m_db->commit();
	}
	catch (otl_exception& p) { // intercept OTL exceptions
		LogMesg(-1,(char*)p.msg); // print out error message
		LogMesg(-1,(char*)p.stm_text); // print out SQL that caused the error
		LogMesg(-1,(char*)p.var_info); // print out the variable that caused the error
		ReConnect(nDBIndex);
		return ;
	}
	*/
}

TimeInterval GetTimeInterval(TimeInterval &stPtval)
{
#if defined(WIN32)
	TimeInterval ti;
	SYSTEMTIME systemTime;
	GetLocalTime(&systemTime);
	time((time_t *)(&ti.m_nSec));
	ti.m_nuSec =systemTime.wMilliseconds  ;

//	ti.m_nSec = tv.tv_sec;
//	ti.m_nuSec = tv.tv_usec;
	ti.m_nSec = ti.m_nSec-stPtval.m_nSec;
	ti.m_nuSec = ti.m_nuSec - stPtval.m_nuSec;
	

	if(ti.m_nSec>2)
	{
		char TmpStr[1024];
		sprintf(TmpStr,"TimeInterval=%d.%03d ",ti.m_nSec,ti.m_nuSec);
		LogErrorSysInfo(SYSERR_AGT_TIMEINTERVAL,TmpStr);
	}

	return ti;

#else	
	TimeInterval ti;
	struct timeval tv;
	gettimeofday (&tv , NULL);
	ti.m_nSec = tv.tv_sec;
	ti.m_nuSec = tv.tv_usec;
	ti.m_nSec = ti.m_nSec-stPtval.m_nSec;
	ti.m_nuSec = ti.m_nuSec - stPtval.m_nuSec;
	if(ti.m_nSec>2)
	{
		char TmpStr[1024];
		sprintf(TmpStr,"TimeInterval=%d.%03d ",ti.m_nSec,ti.m_nuSec);
		LogErrorSysInfo(SYSERR_AGT_TIMEINTERVAL,TmpStr);
	}
	return ti;
#endif
}


/*int TermSave(int nIndex,char *seq,char sLng,char sLat,char sValue,char sNBR,char sGetTime,char serial,char powerval,char fh40gpowerval )
{
	char TmpStr[1024];
	sprintf(TmpStr,"TermSave(%d,%s,%s,%s,%s,%s,%s,%s,%s,%s)",nIndex,seq,sLng,sLat,sValue,sNBR,sGetTime,serial,powerval,fh40gpowerval);
	LogMesg(nIndex,TmpStr);
	CDBIndex DBIndex;
	int nDBIndex = DBIndex.GetDBIndex();
	CHECKINDEX0()
		
		char sql[1024];	
	skt_client_info[nIndex].m_seqnum = atoi(seq);
	int nbr = 0;
	if(&sNBR=="10")
		nbr = 1;
	
	if(&sValue=="---")
		return 0;
	
	

	//插入历史表
	sprintf(sql,"insert into XT_TASKVALUE(seqnum,lng,lat,testvalue,nbr,serial,powerval,fh40gpowerval,createtime,termid,gpsflag,gpsupdate)values (%d,'%s','%s',%s,%d,'%s','%s','%s','%s',%d,1,1) ",skt_client_info[nIndex].m_seqnum,newLng,newLat,sValue,nbr,serial,powerval,fh40gpowerval,sGetTime,skt_client_info[nIndex].m_nTermID);
	LogMesg(nIndex,sql);
	try
	{
		otl_stream otl_update(1, sql,*g_dbCfg[nDBIndex].m_db);
		otl_update.set_commit(0);
		int sqlrpc = otl_update.get_rpc();
		sprintf(TmpStr,"sqlrpc=%d,sql=%s",sqlrpc,sql);
		LogMesg(-1,TmpStr);
		otl_update.flush();
		g_dbCfg[nDBIndex].m_db->commit();
	}
	catch (otl_exception& p) { // intercept OTL exceptions
		LogMesg(-1,(char*)p.msg); // print out error message
		LogMesg(-1,(char*)p.stm_text); // print out SQL that caused the error
		LogMesg(-1,(char*)p.var_info); // print out the variable that caused the error
		ReConnect(nDBIndex);
		return 0 ;
	}

	sprintf(TmpStr,"m_gpsflag=%d",skt_client_info[nIndex].m_gpsflag);
	LogMesg(-1,TmpStr);
	if (skt_client_info[nIndex].m_gpsflag == 0)
	{
		
		sprintf(sql,"update XT_TASKVALUE  set lng='%s',lat = '%s',gpsupdate = 1 where gpsflag=0 and gpsupdate=0 and termid=%d "
			,newLng,newLat,skt_client_info[nIndex].m_nTermID);
		LogMesg(nIndex,sql);
		
		try
		{
			otl_stream otl_update(1, sql,*g_dbCfg[nDBIndex].m_db);
			otl_update.set_commit(0);
			int sqlrpc = otl_update.get_rpc();
			sprintf(TmpStr,"sqlrpc=%d,sql=%s",sqlrpc,sql);
			LogMesg(-1,TmpStr);
			otl_update.flush();
			g_dbCfg[nDBIndex].m_db->commit();
		}
		catch (otl_exception& p) { // intercept OTL exceptions
			LogMesg(-1,(char*)p.msg); // print out error message
			LogMesg(-1,(char*)p.stm_text); // print out SQL that caused the error
			LogMesg(-1,(char*)p.var_info); // print out the variable that caused the error
			ReConnect(nDBIndex);
			return 0 ;
		}
		skt_client_info[nIndex].m_gpsflag = 1;
	}

	return 0;
}*/


int TermSavew(int nIndex,string testvalue,string testtime,string lng,string lat,string templ,string humidity,string termbattery,string devbattery,string unit,int gpsflag,int rssi,int nbr)
{  // cout<<"TERMSAVEW"<<endl;


	char TmpStr[1024];
	//sprintf(TmpStr,"TermSave(%d,,%s,%s,%s,%s,%s,%s,%s)",nIndex,testtime.c_str(),humidity.c_str(),lat.c_str(),lng.c_str(),templ.c_str(),testvalue.c_str(),termbattery.c_str());
	LogMesg(-1,"termsave w");
	CDBIndex DBIndex;
	int nDBIndex = DBIndex.GetDBIndex();
	CHECKINDEX0()
		
	char sql[1024];	

	//skt_client_info[nIndex].m_seqnum = atoi(id.c_str());
	
	
	if(testvalue=="---")
		return 0;
	
    string newLat;
	string newLng;
	
	UpdateGPS(lng,lat,newLng,newLat);
    
	//插入历史表
	sprintf(sql,"insert into ROMS200_TASKVALUE(id,createtime,devpower,humidity,lat,lng,temperature,termpower,testvalue,taskid,pieces,gpsflag,nbr,currenttime)values (uuid(),'%s','%s','%s','%s','%s','%s','%s',%s,'%s','%s',%d,%d,now())",testtime.c_str(),devbattery.c_str(),humidity.c_str(),newLat.c_str(),newLng.c_str(),templ.c_str(),termbattery.c_str(),testvalue.c_str(),skt_client_info[nIndex].m_nTaskID,unit.c_str(),gpsflag,nbr);
	//cout<<"insert into xt_taskvalue"<<endl;
	LogMesg(nIndex,sql);
	try
	{
		otl_stream otl_update(1, sql,*g_dbCfg[nDBIndex].m_db);
		otl_update.set_commit(0);
		int sqlrpc = otl_update.get_rpc();
		sprintf(TmpStr,"sqlrpc=%d,sql=%s",sqlrpc,sql);
		LogMesg(-1,TmpStr);
		otl_update.flush();
		g_dbCfg[nDBIndex].m_db->commit();
	}
	catch (otl_exception& p) { // intercept OTL exceptions
		LogMesg(-1,(char*)p.msg); // print out error message
		LogMesg(-1,(char*)p.stm_text); // print out SQL that caused the error
		LogMesg(-1,(char*)p.var_info); // print out the variable that caused the error
		ReConnect(nDBIndex);
		return 0 ;
	}


	return 0;
}




int   CheckPeerAddress(char* sPeerAddress)
{
	return  -1;
	char TmpStr[1024];
	
	for(int i=0;i<MODULE_MAX;i++)
	{
		
		if(strcmp(skt_client_info[i].m_sPeerAddress,sPeerAddress)==0)
		{
			sprintf(TmpStr,"CheckPeerAddress %s ret = %d",sPeerAddress,i);
			LogMesg(-1,TmpStr);
			return i;
		}
		
	}
	sprintf(TmpStr,"CheckPeerAddress %s ret = %d",sPeerAddress,-1);
	LogMesg(-1,TmpStr);
	
	return -1;
}





int   InitTerm(int nIndex)
{
	skt_client_info[nIndex].m_keeplivetime = 0;
	skt_client_info[nIndex].m_nBorrowFlag = 0;
	skt_client_info[nIndex].m_nKeepSeconds = 0;
	strcpy(skt_client_info[nIndex].m_sBorrowerip,"");
	strcpy(skt_client_info[nIndex].m_sBorrowerport,"");
	strcpy(skt_client_info[nIndex].m_sID,"");
	strcpy(skt_client_info[nIndex].m_sName,"");
	strcpy(skt_client_info[nIndex].m_sPeerAddress,"");
	strcpy(skt_client_info[nIndex].m_sPort,"");
	strcpy(skt_client_info[nIndex].m_sSerialNo,"");
	strcpy(skt_client_info[nIndex].m_sTermNo,"");
	strcpy(skt_client_info[nIndex].m_sNotice,"");
	strcpy(skt_client_info[nIndex].m_sTermName,"");
	strcpy(skt_client_info[nIndex].m_nTaskName,"");
	strcpy(skt_client_info[nIndex].m_nTaskID,"");
	strcpy(skt_client_info[nIndex].m_nTermID,"");
	skt_client_info[nIndex].skt_client.m_hSocket = INVALID_SOCKET;
	LogMesg(nIndex,"InitTerm");
	
	return -1;
}


void UpdateGPS(string lng,string lat,string& mlng,string& mlat)
{
	
	
	if(lng.length()<3)
	{
		lng = "0.00000";
	}
	if(lat.length()<2)
	{
		lat = "0.0000";
	}
	
	if(lng!="0.00000")
	{
		string lng1 = lng.substr(0,3);
		string lng2 = lng.substr(3);
		
		string lat1 = lat.substr(0,2);
		string lat2 = lat.substr(2);
		
		float lng3 = atof(lng2.c_str())/60.0;
		string lng4;
		char str[100];
		sprintf(str,"%.6f",lng3);
		lng4 = str;
		//lng4.Format("%.6f",lng3);
		string lng0 ;
		char str1[100];
		sprintf(str1,"%.6f",atof(lng1.c_str()) + atof(lng4.c_str()));
		lng0 = str1;
		//lng0.Format("%.6f", atof(lng1.c_str()) + atof(lng4.c_str())) ;
		
		float lat3 = atof(lat2.c_str())/60.0;
		string lat4;
		char str2[100];
		sprintf(str2,"%.6f",lat3);
		lat4 = str2;
	//	lat4.Format("%.6f",lat3);
		//CString lat0 = lat1 + lat4;
		
		string lat0 ;
		char str3[100];
		sprintf(str3,"%.6f",atof(lat1.c_str())+atof(lat4.c_str()));
		lat0 = str3;
		//lat0.Format("%.6f",atof(lat1.c_str())+atof(lat4.c_str()));//	= lat1 + lat4;
		
		Location a;
		Location b;
		
		a.lng = atof(lng0.c_str());
		a.lat = atof(lat0.c_str());
		b= transformFromWGSToGCJ(a);
		Location c=	bd_encrypt(b);
		//	printf("x=%f,y=%f",c.lng,c.lat);
		char str4[100];
		char str5[100];
		sprintf(str4,"%.6f",c.lat);
		sprintf(str5,"%.6f",c.lng);
		mlat = str4;
		mlng = str5;
	//	mlat.Format("%.6f",c.lat);
	//	mlng.Format("%.6f",c.lng);
		
		
	}
	else
	{
		mlat = lat;
		mlng = lng;
	}

} 





