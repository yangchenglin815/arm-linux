// IpxSocket.cpp: implementation of the CTcpAsyncSocket class.
//
//////////////////////////////////////////////////////////////////////
#include "StdAfx.h"

#include "tcpsocket.h"



//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CTcpAsyncSocket::CTcpAsyncSocket()
{
	m_hSocket = INVALID_SOCKET;  //设置为无效套接字
}

CTcpAsyncSocket::~CTcpAsyncSocket()
{
//	Close();
}

void CTcpAsyncSocket::Close()
{
	if (m_hSocket != INVALID_SOCKET)
	{
		#if defined(WIN32)
			closesocket(m_hSocket);
		#else
			close(m_hSocket);
		#endif
		m_hSocket = INVALID_SOCKET;
	}
	
}

BOOL CTcpAsyncSocket::Create(UINT nSocketPort,int nType,const char* szIPAddress)
{
	// Allocate socket handle
    m_hSocket = socket(PF_INET, nType, 0);
    if(m_hSocket == INVALID_SOCKET)
	{
		printf("socket:errno=[%d,%s]\n ",   errno,strerror(errno)   );
		return FALSE;
	}

	BOOL bOptVal = TRUE;
	/* Set to enable reuse the address,or the bind() will result an error*/
	int rc = setsockopt(m_hSocket, SOL_SOCKET, SO_REUSEADDR, (char *)&bOptVal, sizeof(int));
	if (rc == SOCKET_ERROR)
	{
		printf("setsockopt:errno=[%d,%s]\n ",   errno,strerror(errno)   );
		Close();
	
		return FALSE;
	}
    printf("creat success\n");
	if (Bind(nSocketPort,szIPAddress))
		return TRUE;
	else
	{
		printf("Bind:errno=[%d,%s]\n ",   errno,strerror(errno)   );
		Close();
		
		return FALSE;
	}
}

BOOL CTcpAsyncSocket::Bind(UINT nSocketPort, LPCTSTR lpszSocketAddress)
{
	SOCKADDR_IN sockAddr;
	memset(&sockAddr,0,sizeof(sockAddr));

	LPSTR lpszAscii = (LPTSTR)lpszSocketAddress;
	sockAddr.sin_family = AF_INET;

	if (lpszAscii == NULL)
		sockAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	else
	{
		DWORD lResult = inet_addr(lpszAscii);
		if (lResult == INADDR_NONE)
		{
			printf("inet_addr:errno=[%d,%s]\n ",   errno,strerror(errno)   );
			return FALSE;
		}
		sockAddr.sin_addr.s_addr = lResult;
	}

	sockAddr.sin_port = htons((u_short)nSocketPort);

    // Bind to socket address
    if(bind(m_hSocket, (SOCKADDR*)&sockAddr, sizeof(sockAddr)) == SOCKET_ERROR)
    {
		printf("bind:errno=[%d,%s]\n ",   errno,strerror(errno)   );
		Close();
		
		return FALSE;
    }
	#if defined(WIN32)
	int addrlen = sizeof(SOCKADDR);
	#else
	socklen_t addrlen = sizeof(SOCKADDR);
	#endif
    // Get full network.number.socket address
    getsockname(m_hSocket, (SOCKADDR*)&sockAddr, &addrlen) ;

	return TRUE;
}

int CTcpAsyncSocket::Receive(void* lpBuf, unsigned long nBufLen, int nFlags)
{
	unsigned long length;
	int ret;
/*
	ret = ioctlsocket(m_hSocket, FIONREAD, &length);
	if (ret == SOCKET_ERROR || length == 0)
		return 0;
	*/

	return recv(m_hSocket, (LPSTR)lpBuf, nBufLen, nFlags);
}

int CTcpAsyncSocket::Send(const void* lpBuf, unsigned long nBufLen, int nFlags)
{
	return send(m_hSocket, (LPSTR)lpBuf, nBufLen, nFlags);
}

int	CTcpAsyncSocket::SendTo( const void* lpBuf, unsigned long nBufLen, UINT nHostPort, LPCTSTR lpszHostAddress, int nFlags)
{
	return 1;
	/*
	SOCKADDR_IN sockAddr;
	memset(&sockAddr,0,sizeof(sockAddr));

	LPSTR lpszAscii = (LPTSTR)lpszHostAddress;
	sockAddr.sin_family = AF_INET;

	if (lpszAscii == NULL)
		sockAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	else
	{
		DWORD lResult = inet_addr(lpszAscii);
		if (lResult == INADDR_NONE)
		{
			printf("inet_addr:errno=[%d,%s]\n ",   errno,strerror(errno)   );
			return FALSE;
		}
		sockAddr.sin_addr.s_addr = lResult;
	}

	sockAddr.sin_port = htons((u_short)nHostPort);

	int nSendLen=sendto(m_hSocket, (LPSTR)lpBuf, nBufLen, nFlags, (const struct sockaddr *)&sockAddr, sizeof(sockAddr));
	if(nSendLen ==-1)
	{
		printf("inet_addr:errno=[%d,%s]\n ",   errno,strerror(errno)   );
	
	}

	return nSendLen;
	*/
}

int CTcpAsyncSocket::ReceiveFrom(void* lpBuf, unsigned long nBufLen, const char* rSocketAddress, UINT& rSocketPort, int nFlags,int nTimeOut)
{
	/*
	int nfds =1;
	int ret;
	fd_set readfds;
	timeval tTimeVal;
	FD_ZERO(&readfds);
	FD_SET(m_hSocket,&readfds);
	tTimeVal.tv_usec = nTimeOut;
	tTimeVal.tv_sec = nTimeOut;

	ret = select(nfds,&readfds,NULL,NULL,&tTimeVal);
	if(ret <= 0)
		return ret; //time out or socket error
	ret = ReceiveFrom(lpBuf,nBufLen,rSocketAddress,rSocketPort,nFlags);

	return ret;
	*/
	return 0;
}

int CTcpAsyncSocket::ReceiveFrom(void* lpBuf, unsigned long nBufLen, const char* rSocketAddress, UINT& rSocketPort, int nFlags)
{
	return 0;
	/*
	SOCKADDR_IN sockAddr;
	socklen_t buflen ;

	memset(&sockAddr, 0, sizeof(sockAddr));

	int nSockAddrLen = sizeof(sockAddr);
	int nResult = recvfrom(m_hSocket, (LPSTR)lpBuf, (socklen_t*)&buflen, nFlags, (SOCKADDR*)&sockAddr, &nSockAddrLen);
	if(nResult != SOCKET_ERROR)
	{
		rSocketPort = ntohs(sockAddr.sin_port);
		rSocketAddress = inet_ntoa(sockAddr.sin_addr);
	}
	else
	{
		printf("inet_addr:errno=[%d,%s]\n ",   errno,strerror(errno)   );
	}

	return nResult;
	
*/
}

BOOL CTcpAsyncSocket::Connect(LPCTSTR lpszHostAddress, UINT nHostPort)
{


	SOCKADDR_IN sockAddr;
	memset(&sockAddr,0,sizeof(sockAddr));

	LPSTR lpszAscii = (LPTSTR)lpszHostAddress;
	sockAddr.sin_family = AF_INET;
	sockAddr.sin_addr.s_addr = inet_addr(lpszAscii);
	
	if (sockAddr.sin_addr.s_addr == INADDR_NONE)
	{
		LPHOSTENT lphost;
		lphost = gethostbyname(lpszAscii);
		if (lphost != NULL)
			sockAddr.sin_addr.s_addr = ((LPIN_ADDR)lphost->h_addr)->s_addr;
		else
		{
			//printf("gethostbyname:errno=[%d,%s]\n ",   errno,strerror(errno)   );
			return FALSE;
		}
	}

	sockAddr.sin_port = htons((u_short)nHostPort);

	if(connect(m_hSocket,(SOCKADDR*)&sockAddr, sizeof(sockAddr)) == SOCKET_ERROR )
    {
		//printf("connect:errno=[%d,%s]\n ",   errno,strerror(errno)   );
		Close();
		
		return FALSE;
    }

	return TRUE;
}
/*
BOOL CTcpAsyncSocket::IOCtl(long lCommand, DWORD* lpArgument)
{ 
	
	#if defined(WIN32)
		return (SOCKET_ERROR != ioctlsocket(m_hSocket, lCommand, (unsigned long*)lpArgument)); 
	#else
		return true;
		//	return (SOCKET_ERROR != ioctl(m_hSocket, lCommand, lpArgument)); 
	#endif
}
*/

BOOL CTcpAsyncSocket::SetNonBlockingMode(BOOL flag)
{
	
	DWORD arg = flag;
//	return IOCtl(FIONBIO, &arg);
	
	return 0;
}

BOOL CTcpAsyncSocket::Listen(int nConnectionBacklog)
{
	return (SOCKET_ERROR != listen(m_hSocket, nConnectionBacklog)); 
}

BOOL CTcpAsyncSocket::Accept(CTcpAsyncSocket& rConnectedSocket,
	SOCKADDR* lpSockAddr, size_t* lpSockAddrLen)
{
	#if defined(WIN32)
		SOCKET hTemp = accept(m_hSocket, lpSockAddr, (int*)lpSockAddrLen);
	#else
		SOCKET hTemp = accept(m_hSocket, lpSockAddr, (socklen_t*)lpSockAddrLen);
	#endif
	if (hTemp == INVALID_SOCKET)
	{
		//printf("accept:errno=[%d,%s]\n ",   errno,strerror(errno)   );
		rConnectedSocket.m_hSocket = INVALID_SOCKET;
		
	}
	else
	{
		rConnectedSocket.m_hSocket = hTemp;
	}

	return (hTemp != INVALID_SOCKET);
}
