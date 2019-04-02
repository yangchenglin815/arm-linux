#include <stdio.h>
#include <stdlib.h>
#include "CSerial.h"
#include <string.h>
#include <malloc.h>
#include <memory.h>
#include <string>
#include <iostream>
#include <time.h>
//#include <process.h> 
//#include <winsock.h>
#include <fcntl.h>
#include "ucs2.h"
#include <assert.h>
#include <math.h>

using namespace std;

#ifdef WIN32
#define uint8_t  unsigned __int8
#define uint16_t unsigned __int16
#define uint32_t unsigned __int32
#define uint64_t unsigned __int64

#define int8_t  __int8
#define int16_t __int16
#define int32_t __int32
#endif

FILE *			 mlogfile =NULL;
CSerial          SMScom;
//int SerFd = -1;
void LogMesg(const char * szFormat, ...)
{
	
	int nThreadId = GetCurrentThreadId();
	char sbuf[100];
	char mbuf[100];
	char tbuf[100];
	char TmpStr[20480];
	SYSTEMTIME systemTime; //��ȡ����
	time_t ttime;
	(void) time(&ttime);   //��ȡ��
	struct tm *ltimeptr = localtime(&ttime);
	strftime(sbuf, 100, "%Y%m%d%H%M%S", ltimeptr);		
	GetLocalTime(&systemTime);
	sprintf(mbuf, ".%3.3ld", long( systemTime.wMilliseconds));
	
	sprintf(tbuf,"%s%s",sbuf,mbuf);//������ʱ�������
	
	if(mlogfile==NULL)//20k
	{
		char fbuf[512];
		time_t ttime;
		(void) time(&ttime);   //��ȡ��
		strftime(fbuf, 512, "d://vms//roms//xtsms//logfile//roms_%Y%m%d.log", ltimeptr);		
		mlogfile = fopen(fbuf,"a");
	}
   	if (mlogfile != NULL)
	{
		char msg[20480];
		va_list pArgs ;
		
		va_start (pArgs, szFormat) ;
		
		int iReturn = vsprintf (msg, szFormat, pArgs) ;
		
		va_end (pArgs) ;
		sprintf(TmpStr,"[%05d][%s], %s\n",nThreadId,tbuf,msg);
		
		
		
			printf(TmpStr);
		
		
		fseek(mlogfile ,0,SEEK_END);
		fwrite(TmpStr, strlen(TmpStr),1,mlogfile);
		fflush(mlogfile);
	}
	
	
	
}

string dump_unicode(uint16_t *utf16, int size)
{
	cout<<utf16<<endl;
    uint8_t *p = (uint8_t *)utf16;
	cout<<*p<<endl;
    char data1[1024];
    string data;

    int i = 0;
    printf("size=%d\n",size);
    for (i = 0; i < size; i++)
    {
	
        printf("i[%d]=%02X\n", i,*p);
		cout<<"p="<<*p<<endl;
	    sprintf(data1,"%02X",*p);
        data = data.append(data1);
        p++;
    }
    
    putchar('\n');
	return data;
}

string CountSMSLength(string _phoneNumber, int len)
        {
	        char data[1024];
            if (_phoneNumber.substr(0, 2) != "86")
            {
                _phoneNumber = _phoneNumber.insert(0,"86",2);     //����ֻ����Ƿ񰴱�׼��ʽ��д�����ǣ��Ͳ��ϡ���
            }
            int length = (8 + ((_phoneNumber.length() % 2) == 0 ? _phoneNumber.length() / 2 : (_phoneNumber.length() + 1) / 2) + len*2);
			//cout<<"size:"<<length<<endl;
			sprintf(data,"%d",length);
			string l = data;
			return l;
        }



string ReversalNumber(string _phone)
        {
            string _strResult;
            if (_phone.substr(0, 2) != "86")
            {
                _phone = _phone.insert(0,"86",2);     //����ֻ����Ƿ񰴱�׼��ʽ��д�����ǣ��Ͳ��ϡ���
            } 
			string eachnumber = (_phone.length() % 2 == 0) ? _phone : _phone.append("F");
            for (int i = 0; i<eachnumber.length() - 1; i += 2)
            {
                _strResult.append(eachnumber.substr(i+1,1));
				_strResult.append(eachnumber.substr(i,1));

            }
            return _strResult;
        }

string ContentEncoding(unsigned char *_srvContent)
        {
	unsigned short content[2048];
	string _content;
	int len=GB2UcsString(_srvContent,content);
	cout<<"llen="<<len<<endl;
	cout<<"buf="<<content<<endl;
	char data[1024];
	char buf[1024];
    string tmpp;
	for(int i=0;i<len;i++)
	{  
		sprintf(data,"%04X",content[i]);
		//	cout<<"data="<<data<<endl;
		string tmp = data;
		//	cout<<"date="<<tmp<<endl;
		_content.append(tmp);
		//	str1.Format ("%04X",uni_buf[i]);
		//	temp+=str1;
	}
	sprintf(buf,"%02X",len*2);
	string buff = buf;
	buff.append(_content);
	cout<<"len="<<buf<<endl;
	cout<<"date_send="<<buff<<endl;

	 
			
            return buff;
        }
 

string PDUEncodingSMS(string _cscaNumber, string _phoneNumber, unsigned char *_targetText)
        {
            if (_cscaNumber.substr(0, 2) != "86")
            {
                _cscaNumber = _cscaNumber.insert(0,"86",2);     //����ֻ����Ƿ񰴱�׼��ʽ��д�����ǣ��Ͳ��ϡ���
            }
            if (_phoneNumber.substr(0, 2) != "86")
            {
                _phoneNumber = _phoneNumber.insert(0,"86",2);     //����ֻ����Ƿ񰴱�׼��ʽ��д�����ǣ��Ͳ��ϡ���
            }
            //��ʼ����
            string _sb;
			char buf[1024];
            _sb.append("0891");
            //��������
            _sb.append(ReversalNumber(_cscaNumber));
            int len = _phoneNumber.length();
            sprintf(buf,"%02X",len);
			string phoneNumber = buf;
            _sb.append("1100" + phoneNumber + "91");
            //Ŀ�����
            _sb.append(ReversalNumber(_phoneNumber));
            //Э���ʶ��������Ϣ����Ч��
            _sb.append("000800");//+ String.Format("{0,2:X}", TargetText.Length * 2).Replace(' ', '0'));
           //���ų��Ⱥ�����
            _sb.append(ContentEncoding(_targetText));
            return _sb;
        }
char* substring(char* ch,int pos,int length)  
{  
	     char* pch=ch;  
	 //����һ���ַ�ָ�룬ָ�򴫵ݽ�����ch��ַ��  
		     char* subch=(char*)calloc(sizeof(char),length+1);  
	 //ͨ��calloc������һ��length���ȵ��ַ����飬���ص����ַ�ָ�롣  
		     int i;  
 //ֻ����C99��forѭ���вſ�����������������д�����棬��߼����ԡ�  
		    pch=pch+pos;  
	 //��pchָ��ָ��posλ�á�  
	     for(i=0;i<length;i++)  
		    {  
		         subch[i]=*(pch++);  
		 //ѭ��������ֵ���顣  
			    }  
	     subch[length]='\0';//�����ַ�����������  
	    return subch;       //���ط�����ַ������ַ��  
 } 

int StrLenU(const char* string)
{
	int len = 0 ;
	const char* p = string;
	while(*p++ != '\0')
	{
		if(*p > 0x80 || *p < 0)
		{
            p++;
		}
		len++;
	}
	return len;
}

char* StrSetPosU( char* string,int pos)
{
	char* result;
	result = string;
	while (result != NULL && *result != '\0' && pos > 1)
	{
		if(*result > 0x80 || *result < 0)
		{
			result++;
		}
		result++;
		pos--;
	}
	if(pos!=0)
		return result;
	return '\0';
}
char* StringSubU( char* string,int start,int number)
{
	int len = StrLenU(string) ;
	if(start>len)
	{
		printf("Start %d is too big than string length %d!\n",start,len);
		return NULL;
	}
	int bufsize = 0;
	int num = number;
	const char* p = string;
	const char* start_char =string;
	/*����ָ�룬��ȡָ����ʼλ��*/
	p = StrSetPosU(string,start);
	start_char = p;
	/*��ȡֵΪ��ֵʱ����ȡȫ��ֵ*/
	if(number < 0)
	{
		while(*p != '\0')
		{
            p++;
            bufsize++;
		}
	}
	else
	{
		while(1)
		{
            /*��ָ���Ƶ�ĩβ�����һ�û�л�ȡָ�������ַ�ʱ��˵����ʱָ���ַ������࣬����ȡʣ�µ�����ֵ*/
            if(*p == '\0' && num > 0)
            {
				printf("Number : %d is to big!\n",number);
				break;
            }
            /*��numΪ0ʱ��˵����ȡ�ַ��Ѿ�����Ҫ��*/
            else if(num ==0 )
				break;
            /*���ַ�ΪASCIIʱ��*/
            if(*p > 0x80 || *p < 0)
            {
				bufsize++;
				p++;
            }
            bufsize++;
            p++;
            num--;
		}
	}
	num = bufsize;
	/*��ʼ�����ڴ�*/
	char* result ;
	result = (char*)malloc(sizeof(char)*(bufsize+1));
	memset(result,0,sizeof(char)*(bufsize+1));
	/*��ʼ�����ַ���*/
	int i = 0;
	int j = 0;
	while(num != 0)
	{
		result[i++] = start_char[j++];
		num--;
	}
	/*β������*/
	result[bufsize] = '\0';
	return result;
}


int hex_char_value(char c)
{
	if(c >= '0' && c <= '9')
		return c - '0';
	else if(c >= 'a' && c <= 'f')
		return (c - 'a' + 10);
	else if(c >= 'A' && c <= 'F')
		return (c - 'A' + 10);
	assert(0);
	return 0;
}
int hex_to_decimal(const char* szHex, int len)
{
	int result = 0;
	for(int i = 0; i < len; i++)
	{
		result += (int)pow((float)16, (int)len-i-1) * hex_char_value(szHex[i]);
	}
	return result;
}

char *hextochs ( char* ascii )
{
    int len = strlen ( ascii ) ;
    if( len%2 != 0 )
        return NULL ;
    char *chs = NULL ;
    chs = (char*)calloc( len / 2 + 1, sizeof(char) );                // calloc chs
	
    int  i = 0 ;
    char ch[2] = {0};
    while( i < len )
    {
        ch[0] = ( (int)ascii[i] > 64 ) ? ( ascii[i]%16 + 9 ) : ascii[i]%16 ;
        ch[1] = ( (int)ascii[i + 1] > 64 ) ? ( ascii[i + 1]%16 + 9 ) : ascii[i + 1]%16 ;
        
        chs[i/2] = (char)( ch[0]*16 + ch[1] );
        i += 2;
    }
	
    return chs ;            // chs ����ǰδ�ͷ�
}

char *chstohex ( char* chs )
{
    char hex[16] = { '0', '1', '2', '3', '4', '5', '6', \
        '7', '8','9', 'A', 'B', 'C', 'D', 'E', 'F'
    };
	
    int len = strlen ( chs );
    char* ascii = NULL ;
    ascii = (char*)calloc ( len * 3 + 1, sizeof(char) );            // calloc ascii
    
    int i = 0;
    while( i < len )
    {
        ascii[i*2] = hex[(int)( (char)chs[i] / 16 )] ;
        ascii[i*2 + 1] = hex[(int)( (char)chs[i] % 16 )] ;
        ++i;
    }
	
    return ascii;                    // ascii ����֮ǰδ�ͷ�
}

int hexCharToValue(const char ch){
	int result = 0;
	//��ȡ16���Ƶĸ��ֽ�λ����
	if(ch >= '0' && ch <= '9'){
		result = (int)(ch - '0');
	}
	else if(ch >= 'a' && ch <= 'z'){
		result = (int)(ch - 'a') + 10;
	}
	else if(ch >= 'A' && ch <= 'Z'){
		result = (int)(ch - 'A') + 10;
	}
	else{
		result = -1;
	}
	return result;
}

//16����ת�ַ���
int hexToStr(char *hex, char *ch)
{
	int high,low;
	int tmp = 0;
	if(hex == NULL || ch == NULL){
		return -1;
	}
	
	if(strlen(hex) %2 == 1){
		return -2;
	}
	
	while(*hex){
		high = hexCharToValue(*hex);
		if(high < 0){
			*ch = '\0';
			return -3;
		}
		hex++; //ָ���ƶ�����һ���ַ���
		low = hexCharToValue(*hex);
		if(low < 0){
			*ch = '\0';
			return -3;
		}
		tmp = (high << 4) + low;
		*ch++ = (char)tmp;
		hex++;
	}
	*ch = '\0';
	return 0;
}

int main()
{
	char TMP[1024];
    char *context = "����վվ��2015��12��07�շ����ձ�:���ֵ4.746V/m,����ʱ��10:33:08;��Сֵ0.251V/m,����ʱ��08:15:50,��ֵ0.751V/m.���շ���762�α���";	
	//cout<<"size="<<strlen(context)<<endl;
	int k = StrLenU(context);
	for(int g=1;g<k;g+=50)
	{

       char *c = StringSubU(context,g,50);
	   cout<<"c="<<c<<endl;
	   LogMesg(c);
	unsigned char *_content = (unsigned char*)c;
	char *phone = "15268581191";
	string _mobileNumber = phone;
    string centerNo = "8613800512500";
    string length;
    string smstosendPDU;
	unsigned short buf[2048];
	int j =GB2UcsString(_content,buf);
	cout<<"j="<<j<<endl;
    length = CountSMSLength(_mobileNumber, j);
    cout<<"length="<<length<<endl;
    smstosendPDU = PDUEncodingSMS(centerNo, _mobileNumber, _content);
	cout<<"smstosendPDU="<<smstosendPDU<<endl;
    string str = "at+cmgs=" + length + "\r\n" + "\r\r\n" + "\r\n" + smstosendPDU +"\x01A";//ָ���ʽ
	string str1 = "at+cmgs="+ length + "\r\n";
	string str2 = smstosendPDU+"\x01A";
    if (SMScom.Open(1,9600,'N',8,1,EV_RXCHAR|EV_CTS,0))
	{
		LogMesg("SMS���ڴ򿪳ɹ�");
		printf("SMS���ڴ򿪳ɹ�\n");
	}
	else{
		LogMesg("SMS���ڴ�ʧ��");
		printf("SMS���ڴ�ʧ��\n");
	}

  //  char cmd[8] = {0x01,0x03,0x00,0x00,0x00,0x02,0xc4,0x0b};
	
	
//	char str[100];
   // hexToStr(cmd,str);
//	cout<<"cmd="<<cmd<<endl;
    //cout<<"cmd_size="<<strlen(cmd)<<endl;
//    SMScom.SendData(cmd,8);
   // for(i=0)
/*    while(1)
	{
		Sleep(1000);
		int mTotalsize = SMScom.ReadDataWaiting();
		cout<<"mTotalsize="<<mTotalsize<<endl;
		if (mTotalsize>0)
		{
			char readBuf[100];
			char tmp[1024];
			int  mRet= SMScom.ReadData(readBuf,100);
			cout<<"readBuf="<<readBuf<<endl;
            for(int i=0;i<9;i++)
			{
				printf("%02x\n",readBuf[i]);
			}
		}
	}*/


	char cmd[1024];
	char TmpStr[1024];
	char tmp[1024];
	char cmp[1024];
	char readBuf[1024]="";
	strcpy(cmd,"at\r\n");//��ʼ������è
//	cout<<strlen(cmd)<<endl;
    SMScom.SendData(cmd,strlen(cmd));
    while(1)
	{
		Sleep(1000);
    int mTotalsize = SMScom.ReadDataWaiting();
	//	cout<<"mTotalsize="<<mTotalsize<<endl;
	if (mTotalsize>0)
	{
      char readBuf[1024]={0};
	  int  mRet= SMScom.ReadData(readBuf,1024);
		//	LogMesg("result[%d]%s", mRet ,readBuf);
		

//	SMScom.ReadData(readBuf,strlen(readBuf));
	cout<<"readBuf="<<readBuf<<endl;
    string a = readBuf;

//	cout<<strlen(readBuf)<<endl;
	if(a.find("OK")<0)
	{
		printf("����èû����������\n");
	   	continue;
	//	break;
	}
	else 
	{
		printf("����è���ӳɹ�\n");
		break;
	}
	}
	}
	
	strcpy(TmpStr,"at+cmee=1\r\n");
	SMScom.SendData(TmpStr,strlen(TmpStr));
    while(1)
	{
		Sleep(1000);
		int mTotalsize = SMScom.ReadDataWaiting();
		if(mTotalsize>0)
		{
			char readBuf[1024]={0};
			int mRet = SMScom.ReadData(readBuf,1024);
			cout<<"readBuf="<<readBuf<<endl;
			string b = readBuf;
			// cout<<strlen(readBuf)<<endl;
			if(b.find("OK")<0)
			{
				printf("���ö���è����ģʽʧ��\n");
				continue;
				//	break;
			}
			else
			{
				printf("����è����Ϊ����ģʽ\n");
				break;
			}
			
		}
	}
	strcpy(tmp,"at+cmgf=0\r\n");//���ö���èΪPDUģʽ
    SMScom.SendData(tmp,strlen(tmp));
    while(1)
	{
    Sleep(1000);
    int mTotalsize = SMScom.ReadDataWaiting();
		if(mTotalsize>0)
		{
			char readBuf[1024]={0};
			int mRet = SMScom.ReadData(readBuf,1024);
			cout<<"readBuf="<<readBuf<<endl;
			string b = readBuf;
	       // cout<<strlen(readBuf)<<endl;
			if(b.find("OK")<0)
			{
				printf("���ö���èģʽʧ��\n");
				continue;
			//	break;
			}
			else
			{
				printf("����è����ΪPDUģʽ\n");
				break;
			}

		}
	}

	char *sendStr = (char *)str1.c_str();
	cout<<"sendStr:"<<sendStr<<endl;
   
	SMScom.SendData(sendStr,strlen(sendStr));
	while(1)
	{
		Sleep(1000);
        int mTotalsize = SMScom.ReadDataWaiting();
		if(mTotalsize>0)
		{
            char readBuf[1024]={0};
			int mRet = SMScom.ReadData(readBuf,1024);
			cout<<"readBuf="<<readBuf<<endl;
	       // cout<<strlen(readBuf)<<endl;

		}
		break;
	}
	char *sendStr1 = (char *)str2.c_str();
	cout<<"sendStr1:"<<sendStr1<<endl;
	
	SMScom.SendData(sendStr1,strlen(sendStr1));
	while(1)
	{
		Sleep(1000);
        int mTotalsize = SMScom.ReadDataWaiting();
		cout<<"mTotalsize="<<mTotalsize<<endl;
		if(mTotalsize>0)
		{
            char readBuf[1024]={0};
			int mRet = SMScom.ReadData(readBuf,1024);
			string respond = readBuf;
			cout<<"readBuf="<<readBuf<<endl;
			int ret = respond.find("+CMGS:");
				cout<<"ret="<<ret<<endl;
			if(ret>0)
			{
				cout<<"respond="<<respond<<endl;
				break;
			}
			else
			// cout<<strlen(readBuf)<<endl;
			continue;
			
		}
		
	}

//}
	return 1;

    
}
}