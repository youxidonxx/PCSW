/******************************************
����ֻ������Ҫʱ�򿪴��ڶ�ȡ/д�����ݣ��ʲ�����
�ձ�Ĵ����ֻ࣬��һ���򵥵Ĵ�������в���,
���ݽӿڶ��壬����Ҫ��������ݣ���ÿһ�����ݶ���
�̶���ģʽ���������ձ�Ĵ����࣬��Ϊ��Щ�����δ֪����
δ֪���ݵ����͸��ʺϣ�ʡ��ȥ�Դ������ݵĻ�ȡ��ʽ��רע
�ڶ����ݵĸ�ֵ�����ٹ�����
******************************************/

class	CSerial:public CObject
{
public:
	CSerial();
	virtual	~CSerial();
	BOOL	OpenComm(int nPort,LONG32	nPaud,char parity = 'N',
		DWORD dwCommEvents = EV_RXCHAR,UINT databits = 8, UINT stopbits = 1);
	BOOL	IsOpen();
	void	CloseComm();
	int		WriteComm(BYTE ch,int delay);
	int		WriteCommData(BYTE*	buff,int	len,int delay = 1,int flag = 0);
	int		ReadCommData(BYTE*	buff,int len,int timeout);
	int		ReadCommData(int  timeout);

	int		m_nPort;
	int		m_nPaud;
private:
	//int		m_hComm;
	HANDLE	m_hComm;
};