#include "includes.h"
#include "ASCII_Option.h"

 
/*********************************************************************
 * Function:		void uitoa(INT16U Value, INT8U *Buffer)
 *
 * PreCondition:	�޷���16λ������ת��ΪASCII����㷨�����磺123456==>��123456��
 *
 * Input:			Value: 16Ϊ������
 *					Buffer: ת�����ASCII�ַ�����ŵ�λ��
 ********************************************************************/
void uitoa(INT16U Value, INT8U *Buffer)
{
	INT8U i;
	INT16U Digit;
	INT16U Divisor;
	INT8U Printed = 0;

	if(Value)
	{
		for(i = 0, Divisor = 10000; i < 5; i++)
		{
			Digit = Value/Divisor;
			if(Digit || Printed)
			{
				*Buffer++ = '0' + Digit;
				Value -= Digit*Divisor;
				Printed = 1;
			}
			Divisor /= 10;
		}
	}
	else
	{
		*Buffer++ = '0';
	}

	*Buffer = '\0';
}			    

// �޷���32λ������ת��ΪASCII����㷨�����磺12345678==>��12345678�� ,ת��������浽Buffer
void ultoa(INT32U Value, INT8U *Buffer)
{
	INT8U i;
	INT32U Digit;
	INT32U Divisor;
	INT8U Printed = 0;

	if(Value)
	{
		for(i = 0, Divisor = 1000000000; i < 10; i++)
		{
			Digit = Value/Divisor;
			if(Digit || Printed)
			{
				*Buffer++ = '0' + Digit;
				Value -= Digit*Divisor;
				Printed = 1;
			}
			Divisor /= 10;
		}
	}
	else
	{
		*Buffer++ = '0';
	}

	*Buffer = '\0';
}

//��һ��8λ�������ĸ�4λת��Ϊ��0��~��F�����ַ���
INT8U btohexa_high(INT8U b)
{
	b >>= 4;
	return (b>0x9u) ? b+'A'-10:b+'0';
}

//��һ��8λ�������ĵ�4λת��Ϊ��0��~��F�����ַ���
INT8U btohexa_low(INT8U b)
{
	b &= 0x0F;
	return (b>9u) ? b+'A'-10:b+'0';
}















