/*
�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~
�~    						  -��ͨ����ԭ������-          		          						  �~
�~ ���ߣ�Ī����																					  �~
�~   QQ: 1695627698 																			  �~
�~ ������һ��ͨ���ӿƼ�һ 																		  �~
�~ ���䣺mojianlin2011@126.com																	  �~
�~ �Ա�ר���꣺etmcu.taobao.com																	  �~
�~ ����:�˳�����Ϊ��ͨ���߼����������д�ģ�����������ҵĿ�ģ���Ҫ�����븽���ҵ���ϵ��ʽ��		  �~
�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~*/

                        
void    GSM_RxISRHandler(void); 

void    GSM_COM_ISR(INT8U rxData);
BOOLEAN GSM_GetField(INT8U *pData, INT8U *pField, INT32S nFieldNum, INT32S nMaxFieldLen);
BOOLEAN GSM_Process_switch(INT8U *pCommand, INT8U *pData);
void GSM_Send_GB_SMS(INT8U *phone,unsigned  char *str);
void GSM_Send_MyStatus(INT8U *phone);
void GSM_Configuration(void);
void GSM_CALL(INT8U *phone);
void GSM_Answer_CALL(void);
void GSM_Hang_UP(void);
