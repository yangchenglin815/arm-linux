#ifndef _UCS2_H_
#define _UCS2_H_


#define MAXLENGTH_GSM0338	128
#define MAXLENGTH_GBK		23940

int GB2UcsString(unsigned char *gbkString, unsigned short *ucs2String);

unsigned short Gb2Unicode(unsigned short gbkCode);

unsigned short Gsm0338ToUcs2(unsigned char gsm);
unsigned short UniCode2GBK(unsigned short UniCode);
void UniCodeStr2GBK(int len,unsigned short *UniCodeStr,unsigned short *gbkStr);

#endif
