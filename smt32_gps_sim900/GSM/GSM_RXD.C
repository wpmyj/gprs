/*
�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~
�~    						  -��ͨ����ԭ������-          		          						                        �~
�~ ���ߣ�Ī����																					                                          �~
�~   QQ: 1695627698 																			                                        �~
�~ ������һ��ͨ���ӿƼ�һ 																		                                    �~
�~ ���䣺mojianlin2011@126.com																	                                  �~
�~ �Ա�ר���꣺etmcu.taobao.com																	                                  �~
�~ ����:�˳�����Ϊ��ͨ���߼����������д�ģ�����������ҵĿ�ģ���Ҫ�����븽���ҵ���ϵ��ʽ��		    �~
�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~*/

#include "includes.h"
#include "GSM.h"
#include "GSM_TypeDefine.h"

#if GSM_MODULE == DEF_ENABLED


GSM_RX_STATE  GSM_RX_nState;	//�������ݴ���״̬

INT16U    Rx_Index;	//����ָ��
INT8U	  GSM_pCommand[GSM_MAX_CMD_LEN];	//
INT8U     GSM_pData[GSM_MAX_DATA_LEN];	//

INT8U	  RX_RN_JP_NUM=0;

INT16U    Test_counter=0;
INT8U     Flag_CMT=0;
INT8U     Flag_CMGR=0;
INT8U     Flag_DATA=0;
INT8U     Flag_CIPGSMLOC=0;

extern GSM_CMT   CMT;
extern GSM_CSCA  CSCA;
extern GSM_IPD   IPD;
extern GSM_CLIP  CLIP;
/*
�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~
�~    						  GSM�жϽ�����ں��� 		          								  �~
�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~*/
void  GSM_RxHandler (INT8U rx_data)
{
	GSM_COM_ISR(rx_data);
	Test_counter++;
}	

/*
�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~
�~    						  GSM�����ж���������������		          							  �~
�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~*/
void GSM_COM_ISR(INT8U rxData)
{
	switch(GSM_RX_nState)
	{
		///////////////////////////////////////////////////////////////////////
		case RX_STATE_IDLE :  // �ȴ���\r\n��
			if((rxData == '\n')||(rxData == '+'))	  
			{
				Rx_Index = 0;  // ����ָ������
				GSM_RX_nState = RX_STATE_CMD; //ת������Э��ͷ��״̬
			}
		  break;
		///////////////////////////////////////////////////////////////////////
		//����Э��ͷ��Ϣ�����磺�յ���Ϣ���� ��+CMT:
		case RX_STATE_CMD :
			if(rxData != ','&&rxData != ':' && rxData != '\r')
			{
				GSM_pCommand[Rx_Index++] = rxData;  //����Э��ͷ����

				//���Э��ͷ�����Ƿ񳬳�Ԥ������
				if(Rx_Index >= GSM_MAX_CMD_LEN)
				{
				 GSM_RX_nState = RX_STATE_IDLE;

				}
			}
			else  //AT+CMGF=1\r\n\r\nOK\r\n
			{			
				if(Rx_Index==0){ GSM_RX_nState = RX_STATE_IDLE;}
				else 
				   {
				   	GSM_pCommand[Rx_Index] = '\0';	// �ַ���������
				    GSM_RX_nState = RX_STATE_DATA;		//����һ�����յ��ֽڿ�ʼ��ת��RX_STATE_DATA״̬����
				    Rx_Index = 0;
					if( strcmp((char *)GSM_pCommand, "+CMT") == NULL ) //���յ��µĶ�������
	                     { Flag_CMT=1;//�ڴ˱��һ�£���������л�ʱ�ظ��Ƚ�
						   RX_RN_JP_NUM=1;
	                     }
				    else if( strcmp((char *)GSM_pCommand, "+CMGR") == NULL ) //���յ��µĶ�������
					   {
						  Flag_CMGR=1;
						  RX_RN_JP_NUM=3;
						 }
						else if( strcmp((char *)GSM_pCommand, "+CIPGSMLOC") == NULL ) //���յ��µĶ�������
					     {
						    Flag_CIPGSMLOC=1;
						    RX_RN_JP_NUM=0;
						   } 
				    else   RX_RN_JP_NUM=0;
				   }
			} 
		break;	  
		///////////////////////////////////////////////////////////////////////
		//��������״̬
		case RX_STATE_DATA :
			if(rxData == '\r') 
			{				   
			   if(RX_RN_JP_NUM==0)
			   {									
				GSM_pData[Rx_Index] = '\0';
				GSM_Process_switch(GSM_pCommand, GSM_pData);
				GSM_RX_nState = RX_STATE_IDLE;
				return;
			   }
			 if(RX_RN_JP_NUM>0) RX_RN_JP_NUM-=1; 
			  //RX_RN_JP_NUM����Ҫ�����Ļس����з�����\r\n�����ĸ����������¶�������ڰ���һ���س����з�
			  //\r\n+CMT: "+8615990472896",,"10/07/29,19:24:56+32"\r\n��������\r\n	
			}
			else 
			{
				GSM_pData[Rx_Index] = rxData;
				if(++Rx_Index >= GSM_MAX_DATA_LEN) 
				{
					GSM_RX_nState = RX_STATE_IDLE;
				}
			}
		break;
		///////////////////////////////////////////////////////////////////////
		default : GSM_RX_nState = RX_STATE_IDLE;
	}
}
/*
�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~
�~   ������BOOLEAN GSM_Process_switch(INT8U *pCommand, INT8U *pData)      �~
�~	 ���ܣ����ݲ�ͬ������ͷ���л�����Ӧ�Ĵ�������												  �~		  
�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~*/
BOOLEAN GSM_Process_switch(INT8U *pCommand, INT8U *pData)
{

	if( Flag_CMGR) //���յ��µĶ�������
	 {
	  Flag_CMGR=0;
	  Process_CMGR(pData);
	 }
	if(Flag_CMT)
	 {
	  Flag_CMT=0;
	  Process_CMT(pData);
	  CMT.isNew=1; 
	  }
	if( strcmp((char *)pCommand, "+CSCA") == NULL ) //�����������ĺ�����Ϣ
	  {
	   Process_CSCA(pData);
	   CSCA.isNew=1;
	  }
	if( strcmp((char *)pCommand, "+IPD") == NULL ) //����TCP����
	  {
	   Process_IPD(pData);
	   IPD.isNew=1;
	  }

	if( strcmp((char *)pCommand, "+CLIP") == NULL ) //��������
	  {
	   //Process_CLIP(pData);
	   CLIP.RING=1;
	   CLIP.COUNT+=1;
	  }
	if(Flag_CIPGSMLOC) //������վ��λ����
	  {
	   Process_GSMLOC(pData);
     GSMLOC.isNew=1;
		 Flag_CIPGSMLOC=0;
	  }

	Flag_DATA=1;

	return TRUE;
}
/*
�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~
�~   ������GetField(INT8U *pData, INT8U *pField, INT32S nFieldNum, INT32S nMaxFieldLen) 		  �~
�~	 ���ܣ����ڽ�ȡָ���ֶε�����																  �~		  
�~																								  �~
�~	 *pData       ��ԭʼ����ָ�룻																  �~
�~	 *pField      ��Ŀ������ָ�룬Ҳ����Ҫ��ŵĵط���											  �~
�~	 nFieldNum    ���ֶα�ţ��μ���������														  �~
�~	 nMaxFieldLen �ֶε���󳤶ȣ�																  �~
�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~*/
BOOLEAN GSM_GetField(INT8U *pData, INT8U *pField, INT32S nFieldNum, INT32S nMaxFieldLen)
{
	INT32S i, i2, nField;
  
  	//��֤�����Ƿ���Ч
	if(pData == NULL || pField == NULL || nMaxFieldLen <= 0)
	{
		return FALSE;
	}

 	//ת��Ŀ���ֶ�
	i = 0;
	nField = 0;
	while(nField != nFieldNum && pData[i]!='\0')
	{
		if(pData[i] == ',')
		{
			nField++;
		}

		i++;

		if(pData[i] == NULL)
		{
			pField[0] = '\0';
			return FALSE;
		}
	}

	if(pData[i] == ',' )
	{
		pField[0] = '\0';
		return FALSE;
	}

 	//��������
	i2 = 0;
	while(pData[i] != ',' && pData[i]!='\0')
	{
		pField[i2] = pData[i];
		i2++; i++;

		//��������Ƿ����
		if(i2 >= nMaxFieldLen)
		{
			i2 = nMaxFieldLen-1;
			break;
		}
	}
	pField[i2] = '\0';

	return TRUE;
}


#endif //GSM_MODULE == DEF_ENABLED
















