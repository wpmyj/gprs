


typedef enum _GSM_RX_STATE 
{
	RX_STATE_IDLE =	0,	       	        // �ȴ���\r\n���ַ���״̬
	RX_STATE_CMD,						// ����Э��ͷ��״̬�����磺�յ���\r\n���ַ���ȴ����ա�GPRMC��
	RX_STATE_DATA,						// ��ȡЭ�����ݵ�״̬
} GSM_RX_STATE;


typedef	struct GSM_CMT_Info      //����	"\r\n+CMT: "+8615990472896",,"10/07/29,19:24:56+32"\r\n��������\r\n
{ 
  INT8U    isNew; //��Ƕ����Ƿ�Ϊ���յ��Ķ��ţ�
  INT8U    PhoneNum[20]; //���ͷ��ĺ��룻
  INT8U	   Date_Time[25];//�ַ��͵����ں�ʱ��
  INT8U	   Content[300]; //�����������70�����֣�һ������ռ4���ֽ�
  INT8U	   OP_CDM[10];   //���Ų�������
  char	   OP_Key_ASCII[8];//��������,�ַ���ʽ��
  INT32U   OP_Key;       //��������,�����ͣ�
}GSM_CMT;


typedef	struct GSM_CSCA_Info      //���� "\r\n+CMT: "+8615990472896",,"10/07/29,19:24:56+32"\r\n��������\r\n
{ 
 INT8U    isNew;
 INT8U    isOK;
 INT8U    Phone[20]; //�������ĺ��룻
}GSM_CSCA;















