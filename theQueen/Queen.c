//��֪����ô������һ��
#include <reg52.h>
#include <intrins.h>
typedef unsigned char uchar;
typedef unsigned char uint;	
unsigned char TxBuf[20]={0};
unsigned char RxBuf[20]={0};
//****************************************NRF24L01�˿ڶ���***************************************
sbit 	MISO	=P1^3;
sbit 	MOSI	=P1^4;
sbit	SCK	    =P1^2;
sbit	CE	    =P1^1;
sbit	CSN		=P3^2;
sbit	IRQ		=P3^3;
//************************************����***************************************************
sbit	KEY1=P3^6;
sbit	KEY2=P3^7;
//************************************�����λѡ*********************************************
sbit	led3=P2^0;
sbit	led2=P2^1;
sbit	led1=P2^2;
sbit	led0=P2^3;
//************************************������***************************************************
sbit 	BELL=P3^4;
//***********************************�����0-9����*******************************************
uchar seg[10]={0xC0,0xCF,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90};         //0~~9����
//*********************************************NRF24L01*************************************
#define TX_ADR_WIDTH    5   	// 5 uints TX address width
#define RX_ADR_WIDTH    5   	// 5 uints RX address width
#define TX_PLOAD_WIDTH  20  	// 20 uints TX payload
#define RX_PLOAD_WIDTH  20  	// 20 uints TX payload
uint const TX_ADDRESS[TX_ADR_WIDTH]= {0x34,0x43,0x10,0x10,0x01};	//���ص�ַ
uint const RX_ADDRESS[RX_ADR_WIDTH]= {0x34,0x43,0x10,0x10,0x01};	//���յ�ַ
//***************************************NRF24L01�Ĵ���ָ��*******************************************************
#define READ_REG        0x00  	// ���Ĵ���ָ��
#define WRITE_REG       0x20 	// д�Ĵ���ָ��
#define RD_RX_PLOAD     0x61  	// ��ȡ��������ָ��
#define WR_TX_PLOAD     0xA0  	// д��������ָ��
#define FLUSH_TX        0xE1 	// ��ϴ���� FIFOָ��
#define FLUSH_RX        0xE2  	// ��ϴ���� FIFOָ��
#define REUSE_TX_PL     0xE3  	// �����ظ�װ������ָ��
#define NOP             0xFF  	// ����
//*************************************SPI(nRF24L01)�Ĵ�����ַ****************************************************
#define CONFIG          0x00  // �����շ�״̬��CRCУ��ģʽ�Լ��շ�״̬��Ӧ��ʽ
#define EN_AA           0x01  // �Զ�Ӧ��������
#define EN_RXADDR       0x02  // �����ŵ�����
#define SETUP_AW        0x03  // �շ���ַ�������
#define SETUP_RETR      0x04  // �Զ��ط���������
#define RF_CH           0x05  // ����Ƶ������
#define RF_SETUP        0x06  // �������ʡ����Ĺ�������
#define STATUS          0x07  // ״̬�Ĵ���
#define OBSERVE_TX      0x08  // ���ͼ�⹦��
#define CD              0x09  // ��ַ���           
#define RX_ADDR_P0      0x0A  // Ƶ��0�������ݵ�ַ
#define RX_ADDR_P1      0x0B  // Ƶ��1�������ݵ�ַ
#define RX_ADDR_P2      0x0C  // Ƶ��2�������ݵ�ַ
#define RX_ADDR_P3      0x0D  // Ƶ��3�������ݵ�ַ
#define RX_ADDR_P4      0x0E  // Ƶ��4�������ݵ�ַ
#define RX_ADDR_P5      0x0F  // Ƶ��5�������ݵ�ַ
#define TX_ADDR         0x10  // ���͵�ַ�Ĵ���
#define RX_PW_P0        0x11  // ����Ƶ��0�������ݳ���
#define RX_PW_P1        0x12  // ����Ƶ��0�������ݳ���
#define RX_PW_P2        0x13  // ����Ƶ��0�������ݳ���
#define RX_PW_P3        0x14  // ����Ƶ��0�������ݳ���
#define RX_PW_P4        0x15  // ����Ƶ��0�������ݳ���
#define RX_PW_P5        0x16  // ����Ƶ��0�������ݳ���
#define FIFO_STATUS     0x17  // FIFOջ��ջ��״̬�Ĵ�������
//**************************************************************************************
#define NUM 1
//*************************************************************************************************************************************************************
//LCD_Definitions
//*************************************************************************************************************************************************************
#ifndef __LCD_H_
#define __LCD_H_
/**********************************
��ʹ�õ���4λ���ݴ����ʱ���壬
ʹ��8λȡ���������
**********************************/
#define LCD1602_4PINS

/**********************************
����ͷ�ļ�
**********************************/
//#include<reg51.h>

//---�ض���ؼ���---//
//#ifndef uchar
//#define uchar unsigned char
//#endif
//
//#ifndef uint 
//#define uint unsigned int
//#endif

/**********************************
PIN�ڶ���
**********************************/
#define LCD1602_DATAPINS P0
sbit LCD1602_E=P2^7;
sbit LCD1602_RW=P2^5;
sbit LCD1602_RS=P2^6;

/**********************************
��������
**********************************/
/*��51��Ƭ��12MHZʱ���µ���ʱ����*/
void Lcd1602_Delay1ms(uint c);   //��� 0us
/*LCD1602д��8λ�����Ӻ���*/
void LcdWriteCom(uchar com);
/*LCD1602д��8λ�����Ӻ���*/	
void LcdWriteData(uchar dat)	;
/*LCD1602��ʼ���ӳ���*/		
void LcdInit();						  
#endif
//*************************************************************************************************************************************************************






void Delay(unsigned int s);
void inerDelay_us(unsigned char n);
void init_NRF24L01(void);
uint SPI_RW(uint uchar);
uchar SPI_Read(uchar reg);
void SetRX_Mode(void);
uint SPI_RW_Reg(uchar reg, uchar value);
uint SPI_Read_Buf(uchar reg, uchar *pBuf, uchar uchars);
uint SPI_Write_Buf(uchar reg, uchar *pBuf, uchar uchars);
unsigned char nRF24L01_RxPacket(unsigned char* rx_buf);
void nRF24L01_TxPacket(unsigned char * tx_buf);
//*****************************************����ʱ*****************************************
void Delay(unsigned int s)
{
	unsigned int i;
	for(i=0; i<s; i++);
	for(i=0; i<s; i++);
}
//******************************************************************************************
uint 	bdata sta;   //״̬��־
sbit	RX_DR	=sta^6;
sbit	TX_DS	=sta^5;
sbit	MAX_RT	=sta^4;
/******************************************************************************************
/*��ʱ����
/******************************************************************************************/
void inerDelay_us(unsigned char n)
{
	for(;n>0;n--)
		_nop_();
}
//****************************************************************************************
/*NRF24L01��ʼ��
//***************************************************************************************/
void init_NRF24L01(void)
{
    inerDelay_us(100);
 	CE=0;    // chip enable
 	CSN=1;   // Spi  disable 
 	SCK=0;   // 
	SPI_Write_Buf(WRITE_REG + TX_ADDR, TX_ADDRESS, TX_ADR_WIDTH);    // д���ص�ַ	
	SPI_Write_Buf(WRITE_REG + RX_ADDR_P0, RX_ADDRESS, RX_ADR_WIDTH); // д���ն˵�ַ
	SPI_RW_Reg(WRITE_REG + EN_AA, 0x01);      //  Ƶ��0�Զ�	ACKӦ������	
	SPI_RW_Reg(WRITE_REG + EN_RXADDR, 0x01);  //  ������յ�ַֻ��Ƶ��0�������Ҫ��Ƶ�����Բο�Page21  
	SPI_RW_Reg(WRITE_REG + RF_CH, 0);        //   �����ŵ�����Ϊ2.4GHZ���շ�����һ��
	SPI_RW_Reg(WRITE_REG + RX_PW_P0, RX_PLOAD_WIDTH); //���ý������ݳ��ȣ���������Ϊ32�ֽ�
	SPI_RW_Reg(WRITE_REG + RF_SETUP, 0x07);   		//���÷�������Ϊ1MHZ�����书��Ϊ���ֵ0dB
}
/****************************************************************************************************
/*������uint SPI_RW(uint uchar)
/*���ܣ�NRF24L01��SPIдʱ��
/****************************************************************************************************/
uint SPI_RW(uint uchar)
{
	uint bit_ctr;
   	for(bit_ctr=0;bit_ctr<8;bit_ctr++) // output 8-bit
   	{
		MOSI = (uchar & 0x80);         // output 'uchar', MSB to MOSI
		uchar = (uchar << 1);           // shift next bit into MSB..
		SCK = 1;                      // Set SCK high..
		uchar |= MISO;       		  // capture current MISO bit
		SCK = 0;            		  // ..then set SCK low again
   	}
    return(uchar);           		  // return read uchar
}
/****************************************************************************************************
/*������uchar SPI_Read(uchar reg)
/*���ܣ�NRF24L01��SPIʱ��
/****************************************************************************************************/
uchar SPI_Read(uchar reg)
{
	uchar reg_val;
	
	CSN = 0;                // CSN low, initialize SPI communication...
	SPI_RW(reg);            // Select register to read from..
	reg_val = SPI_RW(0);    // ..then read registervalue
	CSN = 1;                // CSN high, terminate SPI communication
	
	return(reg_val);        // return register value
}
/****************************************************************************************************/
/*���ܣ�NRF24L01��д�Ĵ�������
/****************************************************************************************************/
uint SPI_RW_Reg(uchar reg, uchar value)
{
	uint status;
	
	CSN = 0;                   // CSN low, init SPI transaction
	status = SPI_RW(reg);      // select register
	SPI_RW(value);             // ..and write value to it..
	CSN = 1;                   // CSN high again
	
	return(status);            // return nRF24L01 status uchar
}
/****************************************************************************************************/
/*������uint SPI_Read_Buf(uchar reg, uchar *pBuf, uchar uchars)
/*����: ���ڶ����ݣ�reg��Ϊ�Ĵ�����ַ��pBuf��Ϊ���������ݵ�ַ��uchars���������ݵĸ���
/****************************************************************************************************/
uint SPI_Read_Buf(uchar reg, uchar *pBuf, uchar uchars)
{
	uint status,uchar_ctr;
	
	CSN = 0;                    		// Set CSN low, init SPI tranaction
	status = SPI_RW(reg);       		// Select register to write to and read status uchar
	
	for(uchar_ctr=0;uchar_ctr<uchars;uchar_ctr++)
		pBuf[uchar_ctr] = SPI_RW(0);    // 
	
	CSN = 1;                           
	
	return(status);                    // return nRF24L01 status uchar
}
/*********************************************************************************************************
/*������uint SPI_Write_Buf(uchar reg, uchar *pBuf, uchar uchars)
/*����: ����д���ݣ�Ϊ�Ĵ�����ַ��pBuf��Ϊ��д�����ݵ�ַ��uchars��д�����ݵĸ���
/*********************************************************************************************************/
uint SPI_Write_Buf(uchar reg, uchar *pBuf, uchar uchars)
{
	uint status,uchar_ctr;
	
	CSN = 0;            //SPIʹ��       
	status = SPI_RW(reg);   
	for(uchar_ctr=0; uchar_ctr<uchars; uchar_ctr++) //
		SPI_RW(*pBuf++);
	CSN = 1;           //�ر�SPI
	return(status);    // 
}
/****************************************************************************************************/
/*������void SetRX_Mode(void)
/*���ܣ����ݽ������� 
/****************************************************************************************************/
void SetRX_Mode(void)
{
	CE=0;
	SPI_RW_Reg(WRITE_REG + CONFIG, 0x0f);   		// IRQ�շ�����ж���Ӧ��16λCRC	��������
	CE = 1; 
	inerDelay_us(130);
}
/******************************************************************************************************/
/*������unsigned char nRF24L01_RxPacket(unsigned char* rx_buf)
/*���ܣ����ݶ�ȡ�����rx_buf���ջ�������
/******************************************************************************************************/
unsigned char nRF24L01_RxPacket(unsigned char* rx_buf)
{
    unsigned char revale=0;
	sta=SPI_Read(STATUS);	// ��ȡ״̬�Ĵ������ж����ݽ���״��
	if(RX_DR)				// �ж��Ƿ���յ�����
	{
	    CE = 0; 			//SPIʹ��
		SPI_Read_Buf(RD_RX_PLOAD,rx_buf,TX_PLOAD_WIDTH);// read receive payload from RX_FIFO buffer
		revale =1;			//��ȡ������ɱ�־
	}
	SPI_RW_Reg(WRITE_REG+STATUS,sta);   //���յ����ݺ�RX_DR,TX_DS,MAX_PT���ø�Ϊ1��ͨ��д1������жϱ�־
	return revale;
}
/***********************************************************************************************************
/*������void nRF24L01_TxPacket(unsigned char * tx_buf)
/*���ܣ����� tx_buf������
/**********************************************************************************************************/
void nRF24L01_TxPacket(unsigned char * tx_buf)
{
	CE=0;			//StandBy Iģʽ	
	SPI_Write_Buf(WRITE_REG + RX_ADDR_P0, TX_ADDRESS, TX_ADR_WIDTH); // װ�ؽ��ն˵�ַ
	SPI_Write_Buf(WR_TX_PLOAD, tx_buf, TX_PLOAD_WIDTH); 			 // װ������	
	SPI_RW_Reg(WRITE_REG + CONFIG, 0x0e);   		 // IRQ�շ�����ж���Ӧ��16λCRC��������
	CE=1;		 //�ø�CE���������ݷ���
	inerDelay_us(10);
}
//*************************************************************************************************************************************************************
//LCD_Functions
//*************************************************************************************************************************************************************
/*******************************************************************************
* �� �� ��         : Lcd1602_Delay1ms
* ��������		   : ��ʱ��������ʱ1ms
* ��    ��         : c
* ��    ��         : ��
* ˵    ��         : �ú�������12MHZ�����£�12��Ƶ��Ƭ������ʱ��
*******************************************************************************/

void Lcd1602_Delay1ms(uint c)   //��� 0us
{
    uchar a,b;
	for (; c>0; c--)
	{
		 for (b=199;b>0;b--)
		 {
		  	for(a=1;a>0;a--);
		 }      
	}
    	
}

/*******************************************************************************
* �� �� ��         : LcdWriteCom
* ��������		   : ��LCDд��һ���ֽڵ�����
* ��    ��         : com
* ��    ��         : ��
*******************************************************************************/
#ifndef 	LCD1602_4PINS	 //��û�ж������LCD1602_4PINSʱ
void LcdWriteCom(uchar com)	  //д������
{
	LCD1602_E = 0;     //ʹ��
	LCD1602_RS = 0;	   //ѡ��������
	LCD1602_RW = 0;	   //ѡ��д��
	
	LCD1602_DATAPINS = com;     //��������
	Lcd1602_Delay1ms(1);		//�ȴ������ȶ�

	LCD1602_E = 1;	          //д��ʱ��
	Lcd1602_Delay1ms(5);	  //����ʱ��
	LCD1602_E = 0;
}
#else 
void LcdWriteCom(uchar com)	  //д������
{
	LCD1602_E = 0;	 //ʹ������
	LCD1602_RS = 0;	 //ѡ��д������
	LCD1602_RW = 0;	 //ѡ��д��

	LCD1602_DATAPINS = com;	//����4λ�Ľ����ǽӵ�P0�ڵĸ���λ�����Դ��͸���λ���ø�
	Lcd1602_Delay1ms(1);

	LCD1602_E = 1;	 //д��ʱ��
	Lcd1602_Delay1ms(5);
	LCD1602_E = 0;

//	Lcd1602_Delay1ms(1);
	LCD1602_DATAPINS = com << 4; //���͵���λ
	Lcd1602_Delay1ms(1);

	LCD1602_E = 1;	 //д��ʱ��
	Lcd1602_Delay1ms(5);
	LCD1602_E = 0;
}
#endif
/*******************************************************************************
* �� �� ��         : LcdWriteData
* ��������		   : ��LCDд��һ���ֽڵ�����
* ��    ��         : dat
* ��    ��         : ��
*******************************************************************************/		   
#ifndef 	LCD1602_4PINS		   
void LcdWriteData(uchar dat)			//д������
{
	LCD1602_E = 0;	//ʹ������
	LCD1602_RS = 1;	//ѡ����������
	LCD1602_RW = 0;	//ѡ��д��

	LCD1602_DATAPINS = dat; //д������
	Lcd1602_Delay1ms(1);

	LCD1602_E = 1;   //д��ʱ��
	Lcd1602_Delay1ms(5);   //����ʱ��
	LCD1602_E = 0;
}
#else
void LcdWriteData(uchar dat)			//д������
{
	LCD1602_E = 0;	  //ʹ������
	LCD1602_RS = 1;	  //ѡ��д������
	LCD1602_RW = 0;	  //ѡ��д��

	LCD1602_DATAPINS = dat;	//����4λ�Ľ����ǽӵ�P0�ڵĸ���λ�����Դ��͸���λ���ø�
	Lcd1602_Delay1ms(1);

	LCD1602_E = 1;	  //д��ʱ��
	Lcd1602_Delay1ms(5);
	LCD1602_E = 0;

	LCD1602_DATAPINS = dat << 4; //д�����λ
	Lcd1602_Delay1ms(1);

	LCD1602_E = 1;	  //д��ʱ��
	Lcd1602_Delay1ms(5);
	LCD1602_E = 0;
}
#endif
/*******************************************************************************
* �� �� ��       : LcdInit()
* ��������		 : ��ʼ��LCD��
* ��    ��       : ��
* ��    ��       : ��
*******************************************************************************/		   
#ifndef		LCD1602_4PINS
void LcdInit()						  //LCD��ʼ���ӳ���
{
 	LcdWriteCom(0x38);  //����ʾ
	LcdWriteCom(0x0c);  //����ʾ����ʾ���
	LcdWriteCom(0x06);  //дһ��ָ���1
	LcdWriteCom(0x01);  //����
	LcdWriteCom(0x80);  //��������ָ�����
}
#else
void LcdInit()						  //LCD��ʼ���ӳ���
{
	LcdWriteCom(0x32);	 //��8λ����תΪ4λ����
	LcdWriteCom(0x28);	 //����λ���µĳ�ʼ��
	LcdWriteCom(0x0c);  //����ʾ����ʾ���
	LcdWriteCom(0x06);  //дһ��ָ���1
	LcdWriteCom(0x01);  //����
	LcdWriteCom(0x80);  //��������ָ�����
}
#endif
//************************************������************************************************************
void main(void)
{
	int Asking,Quizing,QzFn,i;
	unsigned char tf =0;
	char Ans[NUM];
	unsigned char AskSt[9]="Ask Start";
	unsigned char AskStu[17]="Student No.XX Ask";
	unsigned char AskFnsh[10]="Ask Finish";
	unsigned char QzSt[10]="Quiz Start";
	unsigned char QzFnsh[11]="Quiz Finish";
							   
	Asking = Quizing = QzFn = 0;

    init_NRF24L01() ;
	LcdWriteCom(0x32);	 //��8λ����תΪ4λ����
	LcdWriteCom(0x28);	 //����λ���µĳ�ʼ��
	LcdWriteCom(0x0c);  //����ʾ����ʾ���
	LcdWriteCom(0x06);  //дһ��ָ���1
	//P0 = 0xBF;
	while(1)
	{
		if(KEY1 == 0 && Asking){
			Asking = 0;	 
			//P0 = 0xBF;
			LcdWriteCom(0x01);  //����
			LcdWriteCom(0x80);  //��������ָ�����
			for(i=0;i<4;i++)
				LcdWriteData(AskFnsh[i]);	   
			LcdWriteCom(0xC0); //���������ڵڶ���  
			for(i=4;i<10;i++)
				LcdWriteData(AskFnsh[i]);	   
		    TxBuf[1] = 0x02;
		    tf = 1; 
	    }
	    if(KEY2==0 && !Quizing && !Asking){ 
			Quizing = 1;
			for(i = 0;i<NUM;i++)
				Ans[i] = 0;
			//P0 = seg[2];
			LcdWriteCom(0x01);  //����
			LcdWriteCom(0x80);  //��������ָ�����
			for(i=0;i<5;i++)
				LcdWriteData(QzSt[i]);	   
			LcdWriteCom(0xC0); //���������ڵڶ���  
			for(i=5;i<10;i++)
				LcdWriteData(QzSt[i]);
			TxBuf[1] = 0x03;
			tf = 1 ;
	    }
//		if(Quizing){
//		    TxBuf[1] = 0x03;
//			tf = 1 ; 
//		}
//		if(QzFn){
//		    TxBuf[1] = 0x04;
//			tf = 1 ; 
//		}
	    if (tf==1){	
			nRF24L01_TxPacket(TxBuf);	
			TxBuf[1] = 0x00;
			tf = 0;
			Delay(1000);
	    }
		SetRX_Mode();
		nRF24L01_RxPacket(RxBuf);
   		if(RxBuf[1]){					
			if(RxBuf[1]>=0x10 && RxBuf[1]<=0x3f){
				Asking = 1;		   	
				//P0 = seg[RxBuf[1]-0x10+1];
				AskStu[11]=(RxBuf[1]-0x10+1)/10+'0';
				AskStu[12]=(RxBuf[1]-0x10+1)%10+'0'; 
				LcdWriteCom(0x01);  //����
				LcdWriteCom(0x80);  //��������ָ�����
				for(i=14;i<17;i++)
					LcdWriteData(AskStu[i]);	   
				LcdWriteCom(0xC0); //���������ڵڶ���  
				for(i=0;i<14;i++)
					LcdWriteData(AskStu[i]);
			}	
			if(Quizing){
				QzFn = 1;
				if(RxBuf[1]>=0x40 && RxBuf[1]<=0x6f){
				//if(RxBuf[1]==0x06){
					Ans[RxBuf[1]-0x40] = 'a';
					//Ans[0] = 'a';   		
				}
				if(RxBuf[1]>=0x70 && RxBuf[1]<=0x9f){
					Ans[RxBuf[1]-0x70] = 'b';
				}
				if(RxBuf[1]>=0xa0 && RxBuf[1]<=0xcf){
					Ans[RxBuf[1]-0xa1] = 'c';
				}
				if(RxBuf[1]>=0xd0 && RxBuf[1]<=0xff){
					Ans[RxBuf[1]-0xd1] = 'd';
				} 
				for(i = 0;i<NUM;i++){
					if(Ans[i] == 0)
						QzFn = 0;	
				}
				if(QzFn){
//					LcdWriteCom(0x01);  //����
//					LcdWriteCom(0x80);  //��������ָ�����
//					LcdWriteData('1');
//					while(1);
					Quizing = 0; 
					//P0 = 0xBF;   
					LcdWriteCom(0x01);  //����
					LcdWriteCom(0x80);  //��������ָ�����
					for(i=0;i<5;i++)
						LcdWriteData(QzFnsh[i]);	   
					LcdWriteCom(0xC0); //���������ڵڶ���  
					for(i=5;i<11;i++)
						LcdWriteData(QzFnsh[i]);
				}	
			}
			Delay(1000);
		}
//		if(QzFn && !RxBuf[1]){
//			QzFn = 0;
//		}
		RxBuf[1] = 0x00;
	}
}
