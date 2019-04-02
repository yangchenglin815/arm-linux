// TcpSocket.h: interface for the CTcpAsyncSocket class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TCPSOCKET_H__B06292E1_54AA_11D3_A1BD_0000E83E4191__INCLUDED_)
#define AFX_TCPSOCKET_H__B06292E1_54AA_11D3_A1BD_0000E83E4191__INCLUDED_



#include <sys/types.h>

#if defined(WIN32)
#include <winsock.h>
#else
#include <sys/types.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <pthread.h>
#include <signal.h>
#include <iconv.h>
#include <errno.h> 
//#include <stropts.h>
//#include <stropts.h>
#endif

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <time.h>


#define SOCKET			int
#define UINT			unsigned int
#define LPCTSTR			const char*
#define LPSTR           char*
#define LPTSTR           char*
#define BOOL			int
#define DWORD			int
#define INVALID_SOCKET  (SOCKET)(~0)
#define SOCKET_ERROR            (-1)
#define	FALSE			0
#define TRUE			1
#define SOCKADDR_IN     sockaddr_in
#define SOCKADDR        sockaddr
#define LPHOSTENT		struct hostent*
#define LPIN_ADDR		struct in_addr*
//#define NULL			0

class CTcpAsyncSocket  
{
public:
	SOCKET m_hSocket;
	
	
public:
	CTcpAsyncSocket();
	virtual ~CTcpAsyncSocket();
	void	Close();
	BOOL	Bind(UINT nSocketPort, LPCTSTR lpszSocketAddress);
	BOOL	Create(UINT nSocketPort = 0, int nType=SOCK_STREAM,const char* szIPAddress=NULL);
	int		Receive(void* lpBuf, unsigned long nBufLen, int nFlags = 0);
	int		ReceiveFrom(void* lpBuf, unsigned long nBufLen, const char* rSocketAddress, UINT& rSocketPort, int nFlags =0);
	int		ReceiveFrom(void* lpBuf, unsigned long nBufLen, const char* rSocketAddress, UINT& rSocketPort, int nFlags ,int nTimeOut);
	int		Send(const void* lpBuf, unsigned long nBufLen, int nFlags = 0);
	int		SendTo( const void* lpBuf, unsigned long nBufLen, UINT nHostPort, LPCTSTR lpszHostAddress = NULL, int nFlags = 0 );
	BOOL	Connect(LPCTSTR lpszHostAddress, UINT nHostPort);
//	BOOL	IOCtl(long lCommand, int* lpArgument);
	BOOL	SetNonBlockingMode(BOOL flag);
	BOOL	Listen(int nConnectionBacklog=5);
	BOOL	Accept(CTcpAsyncSocket& rConnectedSocket,
		SOCKADDR* lpSockAddr = NULL, size_t* lpSockAddrLen = NULL);
	
};

#endif // !defined(AFX_TCPSOCKET_H__B06292E1_54AA_11D3_A1BD_0000E83E4191__INCLUDED_)
