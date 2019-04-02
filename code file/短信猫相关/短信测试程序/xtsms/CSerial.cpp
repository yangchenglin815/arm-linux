//    Serial.cpp   
//#include "stdafx.h"
#include "windows.h"
#include    "CSerial.h"
#include  <stdio.h>
  

CSerial::CSerial()   
{   
	memset(&m_OverlappedRead, 0, sizeof(OVERLAPPED)); 
	memset(&m_OverlappedWrite, 0, sizeof(OVERLAPPED)); 
	memset(&m_sendcmd,0,sizeof(m_sendcmd));
	
	m_hIDComDev = NULL;   
	m_bOpened = FALSE;   
}   

CSerial::~CSerial()   
{   
	Close();   
}   

//40G
BOOL CSerial::Open(int nPort, LONG nBaud,char Parity,LONG DataBits,LONG StopBits,LONG dwCommEvents,LONG writebuffersize)   
{   

	if(m_bOpened)    
		return TRUE;

	char szPort[100];   
	char szBaud[100];
	char szComParams[50];   
	DCB dcb;   

	sprintf(szPort,"COM%d",nPort);   
	sprintf(szBaud, "baud=%d parity=%c data=%d stop=%d", nBaud, Parity, DataBits, StopBits);
	LogMesg(szBaud);
//	wsprintf(szBaud,"%d",nBaud);
//	m_hIDComDev = CreateFile(szPort,GENERIC_READ|GENERIC_WRITE,0,NULL,   
//	    OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL|FILE_FLAG_OVERLAPPED,NULL);   
	m_hIDComDev = CreateFile(szPort,GENERIC_READ|GENERIC_WRITE,0,NULL,   
	    OPEN_EXISTING,FILE_FLAG_OVERLAPPED,NULL);   

	if(m_hIDComDev == NULL) 
	{
		LogMesg("%s CreateFile err",szPort);
		return FALSE; 
	}
	COMMTIMEOUTS CommTimeOuts;   
	
	CommTimeOuts.ReadIntervalTimeout = 1000;
	CommTimeOuts.ReadTotalTimeoutMultiplier = 1000;
	CommTimeOuts.ReadTotalTimeoutConstant = 1000;
	CommTimeOuts.WriteTotalTimeoutMultiplier = 1000;
	CommTimeOuts.WriteTotalTimeoutConstant = 1000;
	
	if (SetCommTimeouts(m_hIDComDev, &CommTimeOuts))
	{						   
		if (SetCommMask(m_hIDComDev, dwCommEvents))
		{
			if (GetCommState(m_hIDComDev, &m_dcb))
			{
			
			//	m_dcb.fRtsControl = RTS_CONTROL_ENABLE;		// set RTS bit high!
			
			m_dcb.fRtsControl = RTS_CONTROL_DISABLE;		// set RTS bit high!
			m_dcb.fDtrControl = DTR_CONTROL_ENABLE;
				
			//	m_dcb.fRtsControl = RTS_CONTROL_ENABLE;		// set RTS bit high!
			//	m_dcb.fDtrControl = DTR_CONTROL_ENABLE;
	
				if (BuildCommDCB(szBaud, &m_dcb))
				{
					if (SetCommState(m_hIDComDev, &m_dcb))
						; // normal operation... continue
					else
						LogMesg("SetCommState() err");
				}
				else
					LogMesg("BuildCommDCB() err");
			}
			else
				LogMesg("GetCommState() err");
		}
		else
			LogMesg("SetCommMask() err");
	}
	else{
		LogMesg("SetCommTimeouts() err");
		return FALSE;
	}

	//设置缓冲区大小
	SetupComm(m_hIDComDev,20000,20000);

	PurgeComm(m_hIDComDev, PURGE_RXCLEAR | PURGE_TXCLEAR | PURGE_RXABORT | PURGE_TXABORT);

	

//	PurgeComm(m_hIDComDev, PURGE_RXCLEAR | PURGE_TXCLEAR | PURGE_RXABORT | PURGE_TXABORT);
	memset(&m_OverlappedRead, 0, sizeof(OVERLAPPED)); 
	memset(&m_OverlappedWrite, 0, sizeof(OVERLAPPED));
	memset(&m_sendcmd,0,sizeof(m_sendcmd));


	/*
	CommTimeOuts.ReadIntervalTimeout = 0xFFFFFFFF;   
	CommTimeOuts.ReadTotalTimeoutMultiplier = 0;   
	CommTimeOuts.ReadTotalTimeoutConstant = 0;   
	CommTimeOuts.WriteTotalTimeoutMultiplier = 0;   
	CommTimeOuts.WriteTotalTimeoutConstant = 5000;
	*/
	SetCommTimeouts(m_hIDComDev, &CommTimeOuts);   

	//wsprintf(szComParams, "COM%d:%d,n,8,1", nPort, nBaud); 

	m_OverlappedRead.hEvent = CreateEvent(NULL,TRUE, FALSE, NULL);   
	m_OverlappedWrite.hEvent = CreateEvent(NULL,TRUE,FALSE, NULL);   

	/*
	dcb.DCBlength = sizeof(DCB);   
	GetCommState(m_hIDComDev,&dcb);   
//	dcb.BaudRate = nBaud;   
//	dcb.ByteSize = DataBits;   
//	dcb.StopBits = StopBits;
	dcb.fRtsControl = RTS_CONTROL_DISABLE;		// set RTS bit high!
//	dcb.fRtsControl = DTR_CONTROL_DISABLE;
	dcb.fDtrControl = DTR_CONTROL_ENABLE;
//	dcb.fParity=Parity;
*/
	/*
	unsigned char ucSet;   
	ucSet = (unsigned char)((FC_RTSCTS& FC_DTRDSR) != 0);   
	ucSet = (unsigned char)((FC_RTSCTS& FC_RTSCTS) != 0);   
	ucSet = (unsigned char)((FC_RTSCTS& FC_XONXOFF) != 0);  
	*/
	/*
	//if(!SetCommState(m_hIDComDev, &dcb) || !SetupComm(m_hIDComDev,10000,10000)||  
	if(!SetCommState(m_hIDComDev, &dcb) || 
	   m_OverlappedRead.hEvent == NULL || m_OverlappedWrite.hEvent == NULL )   
	{   
		DWORD dwError = GetLastError();   
		if(m_OverlappedRead.hEvent != NULL)    
			CloseHandle(m_OverlappedRead.hEvent);   
		if(m_OverlappedWrite.hEvent != NULL)    
			CloseHandle(m_OverlappedWrite.hEvent);   
		CloseHandle(m_hIDComDev);   
		return FALSE;   
	}   
	

	m_bOpened = TRUE;   
	PurgeComm(m_hIDComDev, PURGE_RXCLEAR | PURGE_TXCLEAR | PURGE_RXABORT | PURGE_TXABORT);
*/
		m_bOpened = TRUE; 
	return m_bOpened;   
	
}   

BOOL CSerial::Close( )   
{   
	if(!m_bOpened || m_hIDComDev == NULL)   
		return TRUE;   

	if(m_OverlappedRead.hEvent != NULL)   
		CloseHandle(m_OverlappedRead.hEvent);   

	if(m_OverlappedWrite.hEvent != NULL)   
		CloseHandle(m_OverlappedWrite.hEvent);   

	CloseHandle(m_hIDComDev);   
	m_bOpened = FALSE;   
	m_hIDComDev = NULL;   

	return TRUE;   
}   

BOOL CSerial::WriteCommByte(unsigned char ucByte)   
{   
	BOOL bWriteStat;   
	DWORD dwBytesWritten;   

	bWriteStat = WriteFile(m_hIDComDev,(LPSTR)&ucByte,1, &dwBytesWritten, &m_OverlappedWrite);   //返回0，调用不成功
//	printf("stat=%d\n",bWriteStat);
    
	if(!bWriteStat && (GetLastError() == ERROR_IO_PENDING))   
	{   
		if(WaitForSingleObject(m_OverlappedWrite.hEvent,1000))  
		{
			dwBytesWritten = 0;   
		}
		else   
		{  
		    GetOverlappedResult(m_hIDComDev, &m_OverlappedWrite, &dwBytesWritten,FALSE);
			m_OverlappedWrite.Offset += dwBytesWritten;  
		}   
	}   
	return TRUE;   
}   

int CSerial::SendData(const char* buffer, int size)   
{   
	sprintf(m_sendcmd,"%s",buffer);
	if(!m_bOpened || m_hIDComDev == NULL)   
		return 0;   
	SendDataWaiting();
	DWORD dwBytesWritten = 0;   
  	PurgeComm(m_hIDComDev, PURGE_RXCLEAR | PURGE_TXCLEAR | PURGE_RXABORT | PURGE_TXABORT);//清空缓冲区
	for(int i=0; i < size; i++)   
	{   
		WriteCommByte(buffer[i]);   
		dwBytesWritten++;
	}   

	return (int)dwBytesWritten;   
}   

int CSerial::ReadDataWaiting()   
{   
	if(!m_bOpened || m_hIDComDev == NULL)   
	return 0;   

	DWORD dwErrorFlags;   
	COMSTAT ComStat;   

	ClearCommError(m_hIDComDev,&dwErrorFlags,&ComStat);   

	return (int) ComStat.cbInQue;  
}   

int CSerial::ReadData(void* buffer, int limit)   
{   
	if(!m_bOpened || m_hIDComDev == NULL)   
		return 0;   


	BOOL bReadStatus;   
	DWORD dwBytesRead,dwErrorFlags;   
	COMSTAT ComStat;   

	ClearCommError(m_hIDComDev, &dwErrorFlags, &ComStat);   

	if(!ComStat.cbInQue)   
	return 0;   

	dwBytesRead = (DWORD)ComStat.cbInQue;   

	if(limit < (int)dwBytesRead)  
		
		dwBytesRead = (DWORD)limit;  
	
	//printf("m_hIDComDev=%d,dwBytesRead=%d\n",m_hIDComDev,dwBytesRead);

	bReadStatus = ReadFile(m_hIDComDev,buffer,dwBytesRead, &dwBytesRead,   
							&m_OverlappedRead);   

//	printf("m_hIDComDev=%d,bReadStatus=%d dwBytesRead=%d limit=%d ComStat.cbInQue=%d\n",m_hIDComDev,bReadStatus,dwBytesRead,limit,ComStat.cbInQue);

	if(!bReadStatus)   
	{   
		if(GetLastError() == ERROR_IO_PENDING)   
		{   
			WaitForSingleObject(m_OverlappedRead.hEvent, 2000);   
			return (int)dwBytesRead;   
		}   
		return 0;   
	}   

	return (int)dwBytesRead;   
}   

int CSerial::SendDataWaiting()
{
	if(!m_bOpened || m_hIDComDev == NULL)   
	return 0;   

	DWORD dwErrorFlags;   
	COMSTAT ComStat;   

	ClearCommError(m_hIDComDev, &dwErrorFlags, &ComStat);   

	return (int)ComStat.cbOutQue;  
}