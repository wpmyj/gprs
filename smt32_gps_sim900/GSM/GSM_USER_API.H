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

#define  MMA7660  0x98	 //����������MMA7660��IIC������ַ

extern INT32U My_Key_Number;


void MMC7660_Init(void);
void Key_Number_Init(void);
void Key_Number_Store(void);
void Key_Number_Renew(void);
INT8S Get_Temperature(void);


unsigned char SPI_WriteByte(unsigned char data);
void   SpiDelay(unsigned int DelayCnt);
void   Gsenser_SHOW_REG(void);
void   ADXL345_Init(void);
void   Gsenser_SHOW_REG(void);
void   Gsenser_WriteREG(INT8U REG,INT8U DATA);
INT8U  Gsenser_ReadREG(INT8U REG);
INT16U Gsenser_ReadREG2(INT8U REG);
void   SHOW_SPI_REG(void);
void   Gsenser_SHOW_XYZ(void);
void   ADXL345_Test(void);




