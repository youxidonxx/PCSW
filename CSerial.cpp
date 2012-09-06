#include "stdafx.h"
#include "CSerial.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSerial
CSerial::CSerial()
{
	m_hComm	= INVALID_HANDLE_VALUE;
}

CSerial::~CSerial()
{
	CloseComm();
}
BOOL	CSerial::OpenComm(int nPort,LONG32 nPaud,char parity /* =  */, 
						  DWORD dwCommEvents /* = EV_RXCHAR */,UINT databits /* = 8 */, UINT stopbits /* = 1 */)
{
	COMMTIMEOUTS	tous;
	DCB		dcb;
	CString		strComm;
	memset(&tous,0,sizeof(tous));
	tous.ReadIntervalTimeout = MAXWORD;

	if (nPort >=10)
	{
		strComm.Format("\\\\.\\%d",nPort);
	}
	else
		strComm.Format("COM%d",nPort);

	m_hComm = CreateFile(strComm,GENERIC_READ|GENERIC_WRITE,0,NULL,OPEN_EXISTING,0,NULL);
	if (m_hComm!=INVALID_HANDLE_VALUE)
	{
		GetCommState(m_hComm,&dcb);
		dcb.BaudRate = nPaud;
		dcb.Parity = parity;
		dcb.fOutxCtsFlow = dcb.fOutxDsrFlow = 0;
		dcb.fOutX = dcb.fInX = 0;
		dcb.fRtsControl = RTS_CONTROL_ENABLE;
		dcb.fDtrControl = DTR_CONTROL_ENABLE;

		dcb.ByteSize = databits;
		dcb.StopBits = stopbits;

		SetCommState(m_hComm,&dcb);
		SetupComm(m_hComm,4096,4096);
		SetCommTimeouts(m_hComm,&tous);
		EscapeCommFunction(m_hComm,SETDTR);
		EscapeCommFunction(m_hComm,SETRTS);		

		m_nPaud = nPaud;
		m_nPort = nPort;
		return TRUE;
	}
	return FALSE;
}
int CSerial::WriteComm(BYTE ch,int delay)
{
	return(WriteCommData(&ch,1,delay));
}

int CSerial::WriteCommData(BYTE* buff,int len,int delay /* = 1 */,int flag /* = 0 */)
{
	int i=0;
	unsigned long number = 0;
	if (flag == 0)
	{
		if(delay!=0)
			Sleep(delay);
		WriteFile(m_hComm,buff,len,&number,NULL);
		return ((int)number);
	}
	//Ϊ��һ���ֽ�һ���ֽڵ�д��
	else
	{
		for (i=0;i<len;i++)
		{
			if(delay!=0)
				Sleep(delay);
			WriteFile(m_hComm,buff+i,1,&number,NULL);
			//������д������ʱ���˳�ѭ��
			if(number<1)
				break;
		}
		return i;
	}
}
//���ݽӿڶ����Ѿ���֪��Ҫ��ȡ�����ݴ�С
int CSerial::ReadCommData(BYTE* buff,int len,int timeout)
{
	DWORD	start;
	COMSTAT	stat;
	DWORD	dwError;

	int i=0;
	unsigned long number = 0;
	start = GetTickCount();
	do 
	{
		//���COMM��־
		int err = GetLastError();
		ClearCommError(m_hComm,&dwError,&stat);
		//����һ��readfile�����޷���ȫ��ȡ����Ҫ�����ݣ�
		//�ʶԸò����ĳ��Ƚ����޶����ж�
		ReadFile(m_hComm,buff+i,len-i,&number,NULL);
		//���Ǹô˶�ȡ���������ݴ�С��ʣ����Ҫ�Ĵ�С��ͬ����˵���Ѿ���ȡ���
		if(number == (unsigned long)(len-i))
			return len;
		//���ǻ����Զ�ȡ�����ݣ�˵�����У�����ȡ���������ݽ��е���
		else if(number>0)
			i+=number;
		else if(timeout>5)
			Sleep(1);
	} while (GetTickCount()-start <(unsigned int)timeout);
	return i;
}
int CSerial::ReadCommData(int timeout)
{
	BYTE	ch;
	DWORD	start;
	COMSTAT	stat;
	DWORD	dwError;
	unsigned long	number = 0;
	start = GetTickCount();
	do 
	{
		int err = GetLastError();

		ClearCommError(m_hComm,&dwError,&stat);
		//һ���ֽ�һ���ֽڽ��ж�ȡ
		ReadFile(m_hComm,&ch,1,&number,NULL);
		//˵���������Ǵ������ݵ�
		if(number>0)
			return (int)ch;
	} while (GetTickCount()-start <(unsigned int)timeout);
	return -1;
}
void CSerial::CloseComm()
{
	if (m_hComm!=INVALID_HANDLE_VALUE)
	{
		Sleep(5);
		CloseHandle(m_hComm);
		m_hComm = INVALID_HANDLE_VALUE;
	}
}
BOOL	CSerial::IsOpen()
{
	return (m_hComm!=INVALID_HANDLE_VALUE);
}
