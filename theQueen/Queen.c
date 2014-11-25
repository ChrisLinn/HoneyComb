//不知道怎么样测试一下
#include <reg52.h>
#include <intrins.h>
typedef unsigned char uchar;
typedef unsigned char uint;	
unsigned char TxBuf[20]={0};
unsigned char RxBuf[20]={0};
//****************************************NRF24L01端口定义***************************************
sbit 	MISO	=P1^3;
sbit 	MOSI	=P1^4;
sbit	SCK	    =P1^2;
sbit	CE	    =P1^1;
sbit	CSN		=P3^2;
sbit	IRQ		=P3^3;
//************************************按键***************************************************
sbit	KEY1=P3^6;
sbit	KEY2=P3^7;
//************************************数码管位选*********************************************
sbit	led3=P2^0;
sbit	led2=P2^1;
sbit	led1=P2^2;
sbit	led0=P2^3;
//************************************蜂明器***************************************************
sbit 	BELL=P3^4;
//***********************************数码管0-9编码*******************************************
uchar seg[10]={0xC0,0xCF,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90};         //0~~9段码
//*********************************************NRF24L01*************************************
#define TX_ADR_WIDTH    5   	// 5 uints TX address width
#define RX_ADR_WIDTH    5   	// 5 uints RX address width
#define TX_PLOAD_WIDTH  20  	// 20 uints TX payload
#define RX_PLOAD_WIDTH  20  	// 20 uints TX payload
uint const TX_ADDRESS[TX_ADR_WIDTH]= {0x34,0x43,0x10,0x10,0x01};	//本地地址
uint const RX_ADDRESS[RX_ADR_WIDTH]= {0x34,0x43,0x10,0x10,0x01};	//接收地址
//***************************************NRF24L01寄存器指令*******************************************************
#define READ_REG        0x00  	// 读寄存器指令
#define WRITE_REG       0x20 	// 写寄存器指令
#define RD_RX_PLOAD     0x61  	// 读取接收数据指令
#define WR_TX_PLOAD     0xA0  	// 写待发数据指令
#define FLUSH_TX        0xE1 	// 冲洗发送 FIFO指令
#define FLUSH_RX        0xE2  	// 冲洗接收 FIFO指令
#define REUSE_TX_PL     0xE3  	// 定义重复装载数据指令
#define NOP             0xFF  	// 保留
//*************************************SPI(nRF24L01)寄存器地址****************************************************
#define CONFIG          0x00  // 配置收发状态，CRC校验模式以及收发状态响应方式
#define EN_AA           0x01  // 自动应答功能设置
#define EN_RXADDR       0x02  // 可用信道设置
#define SETUP_AW        0x03  // 收发地址宽度设置
#define SETUP_RETR      0x04  // 自动重发功能设置
#define RF_CH           0x05  // 工作频率设置
#define RF_SETUP        0x06  // 发射速率、功耗功能设置
#define STATUS          0x07  // 状态寄存器
#define OBSERVE_TX      0x08  // 发送监测功能
#define CD              0x09  // 地址检测           
#define RX_ADDR_P0      0x0A  // 频道0接收数据地址
#define RX_ADDR_P1      0x0B  // 频道1接收数据地址
#define RX_ADDR_P2      0x0C  // 频道2接收数据地址
#define RX_ADDR_P3      0x0D  // 频道3接收数据地址
#define RX_ADDR_P4      0x0E  // 频道4接收数据地址
#define RX_ADDR_P5      0x0F  // 频道5接收数据地址
#define TX_ADDR         0x10  // 发送地址寄存器
#define RX_PW_P0        0x11  // 接收频道0接收数据长度
#define RX_PW_P1        0x12  // 接收频道0接收数据长度
#define RX_PW_P2        0x13  // 接收频道0接收数据长度
#define RX_PW_P3        0x14  // 接收频道0接收数据长度
#define RX_PW_P4        0x15  // 接收频道0接收数据长度
#define RX_PW_P5        0x16  // 接收频道0接收数据长度
#define FIFO_STATUS     0x17  // FIFO栈入栈出状态寄存器设置
//**************************************************************************************
#define NUM 1
//*************************************************************************************************************************************************************
//LCD_Definitions
//*************************************************************************************************************************************************************
#ifndef __LCD_H_
#define __LCD_H_
/**********************************
当使用的是4位数据传输的时候定义，
使用8位取消这个定义
**********************************/
#define LCD1602_4PINS

/**********************************
包含头文件
**********************************/
//#include<reg51.h>

//---重定义关键词---//
//#ifndef uchar
//#define uchar unsigned char
//#endif
//
//#ifndef uint 
//#define uint unsigned int
//#endif

/**********************************
PIN口定义
**********************************/
#define LCD1602_DATAPINS P0
sbit LCD1602_E=P2^7;
sbit LCD1602_RW=P2^5;
sbit LCD1602_RS=P2^6;

/**********************************
函数声明
**********************************/
/*在51单片机12MHZ时钟下的延时函数*/
void Lcd1602_Delay1ms(uint c);   //误差 0us
/*LCD1602写入8位命令子函数*/
void LcdWriteCom(uchar com);
/*LCD1602写入8位数据子函数*/	
void LcdWriteData(uchar dat)	;
/*LCD1602初始化子程序*/		
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
//*****************************************长延时*****************************************
void Delay(unsigned int s)
{
	unsigned int i;
	for(i=0; i<s; i++);
	for(i=0; i<s; i++);
}
//******************************************************************************************
uint 	bdata sta;   //状态标志
sbit	RX_DR	=sta^6;
sbit	TX_DS	=sta^5;
sbit	MAX_RT	=sta^4;
/******************************************************************************************
/*延时函数
/******************************************************************************************/
void inerDelay_us(unsigned char n)
{
	for(;n>0;n--)
		_nop_();
}
//****************************************************************************************
/*NRF24L01初始化
//***************************************************************************************/
void init_NRF24L01(void)
{
    inerDelay_us(100);
 	CE=0;    // chip enable
 	CSN=1;   // Spi  disable 
 	SCK=0;   // 
	SPI_Write_Buf(WRITE_REG + TX_ADDR, TX_ADDRESS, TX_ADR_WIDTH);    // 写本地地址	
	SPI_Write_Buf(WRITE_REG + RX_ADDR_P0, RX_ADDRESS, RX_ADR_WIDTH); // 写接收端地址
	SPI_RW_Reg(WRITE_REG + EN_AA, 0x01);      //  频道0自动	ACK应答允许	
	SPI_RW_Reg(WRITE_REG + EN_RXADDR, 0x01);  //  允许接收地址只有频道0，如果需要多频道可以参考Page21  
	SPI_RW_Reg(WRITE_REG + RF_CH, 0);        //   设置信道工作为2.4GHZ，收发必须一致
	SPI_RW_Reg(WRITE_REG + RX_PW_P0, RX_PLOAD_WIDTH); //设置接收数据长度，本次设置为32字节
	SPI_RW_Reg(WRITE_REG + RF_SETUP, 0x07);   		//设置发射速率为1MHZ，发射功率为最大值0dB
}
/****************************************************************************************************
/*函数：uint SPI_RW(uint uchar)
/*功能：NRF24L01的SPI写时序
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
/*函数：uchar SPI_Read(uchar reg)
/*功能：NRF24L01的SPI时序
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
/*功能：NRF24L01读写寄存器函数
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
/*函数：uint SPI_Read_Buf(uchar reg, uchar *pBuf, uchar uchars)
/*功能: 用于读数据，reg：为寄存器地址，pBuf：为待读出数据地址，uchars：读出数据的个数
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
/*函数：uint SPI_Write_Buf(uchar reg, uchar *pBuf, uchar uchars)
/*功能: 用于写数据：为寄存器地址，pBuf：为待写入数据地址，uchars：写入数据的个数
/*********************************************************************************************************/
uint SPI_Write_Buf(uchar reg, uchar *pBuf, uchar uchars)
{
	uint status,uchar_ctr;
	
	CSN = 0;            //SPI使能       
	status = SPI_RW(reg);   
	for(uchar_ctr=0; uchar_ctr<uchars; uchar_ctr++) //
		SPI_RW(*pBuf++);
	CSN = 1;           //关闭SPI
	return(status);    // 
}
/****************************************************************************************************/
/*函数：void SetRX_Mode(void)
/*功能：数据接收配置 
/****************************************************************************************************/
void SetRX_Mode(void)
{
	CE=0;
	SPI_RW_Reg(WRITE_REG + CONFIG, 0x0f);   		// IRQ收发完成中断响应，16位CRC	，主接收
	CE = 1; 
	inerDelay_us(130);
}
/******************************************************************************************************/
/*函数：unsigned char nRF24L01_RxPacket(unsigned char* rx_buf)
/*功能：数据读取后放如rx_buf接收缓冲区中
/******************************************************************************************************/
unsigned char nRF24L01_RxPacket(unsigned char* rx_buf)
{
    unsigned char revale=0;
	sta=SPI_Read(STATUS);	// 读取状态寄存其来判断数据接收状况
	if(RX_DR)				// 判断是否接收到数据
	{
	    CE = 0; 			//SPI使能
		SPI_Read_Buf(RD_RX_PLOAD,rx_buf,TX_PLOAD_WIDTH);// read receive payload from RX_FIFO buffer
		revale =1;			//读取数据完成标志
	}
	SPI_RW_Reg(WRITE_REG+STATUS,sta);   //接收到数据后RX_DR,TX_DS,MAX_PT都置高为1，通过写1来清楚中断标志
	return revale;
}
/***********************************************************************************************************
/*函数：void nRF24L01_TxPacket(unsigned char * tx_buf)
/*功能：发送 tx_buf中数据
/**********************************************************************************************************/
void nRF24L01_TxPacket(unsigned char * tx_buf)
{
	CE=0;			//StandBy I模式	
	SPI_Write_Buf(WRITE_REG + RX_ADDR_P0, TX_ADDRESS, TX_ADR_WIDTH); // 装载接收端地址
	SPI_Write_Buf(WR_TX_PLOAD, tx_buf, TX_PLOAD_WIDTH); 			 // 装载数据	
	SPI_RW_Reg(WRITE_REG + CONFIG, 0x0e);   		 // IRQ收发完成中断响应，16位CRC，主发送
	CE=1;		 //置高CE，激发数据发送
	inerDelay_us(10);
}
//*************************************************************************************************************************************************************
//LCD_Functions
//*************************************************************************************************************************************************************
/*******************************************************************************
* 函 数 名         : Lcd1602_Delay1ms
* 函数功能		   : 延时函数，延时1ms
* 输    入         : c
* 输    出         : 无
* 说    名         : 该函数是在12MHZ晶振下，12分频单片机的延时。
*******************************************************************************/

void Lcd1602_Delay1ms(uint c)   //误差 0us
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
* 函 数 名         : LcdWriteCom
* 函数功能		   : 向LCD写入一个字节的命令
* 输    入         : com
* 输    出         : 无
*******************************************************************************/
#ifndef 	LCD1602_4PINS	 //当没有定义这个LCD1602_4PINS时
void LcdWriteCom(uchar com)	  //写入命令
{
	LCD1602_E = 0;     //使能
	LCD1602_RS = 0;	   //选择发送命令
	LCD1602_RW = 0;	   //选择写入
	
	LCD1602_DATAPINS = com;     //放入命令
	Lcd1602_Delay1ms(1);		//等待数据稳定

	LCD1602_E = 1;	          //写入时序
	Lcd1602_Delay1ms(5);	  //保持时间
	LCD1602_E = 0;
}
#else 
void LcdWriteCom(uchar com)	  //写入命令
{
	LCD1602_E = 0;	 //使能清零
	LCD1602_RS = 0;	 //选择写入命令
	LCD1602_RW = 0;	 //选择写入

	LCD1602_DATAPINS = com;	//由于4位的接线是接到P0口的高四位，所以传送高四位不用改
	Lcd1602_Delay1ms(1);

	LCD1602_E = 1;	 //写入时序
	Lcd1602_Delay1ms(5);
	LCD1602_E = 0;

//	Lcd1602_Delay1ms(1);
	LCD1602_DATAPINS = com << 4; //发送低四位
	Lcd1602_Delay1ms(1);

	LCD1602_E = 1;	 //写入时序
	Lcd1602_Delay1ms(5);
	LCD1602_E = 0;
}
#endif
/*******************************************************************************
* 函 数 名         : LcdWriteData
* 函数功能		   : 向LCD写入一个字节的数据
* 输    入         : dat
* 输    出         : 无
*******************************************************************************/		   
#ifndef 	LCD1602_4PINS		   
void LcdWriteData(uchar dat)			//写入数据
{
	LCD1602_E = 0;	//使能清零
	LCD1602_RS = 1;	//选择输入数据
	LCD1602_RW = 0;	//选择写入

	LCD1602_DATAPINS = dat; //写入数据
	Lcd1602_Delay1ms(1);

	LCD1602_E = 1;   //写入时序
	Lcd1602_Delay1ms(5);   //保持时间
	LCD1602_E = 0;
}
#else
void LcdWriteData(uchar dat)			//写入数据
{
	LCD1602_E = 0;	  //使能清零
	LCD1602_RS = 1;	  //选择写入数据
	LCD1602_RW = 0;	  //选择写入

	LCD1602_DATAPINS = dat;	//由于4位的接线是接到P0口的高四位，所以传送高四位不用改
	Lcd1602_Delay1ms(1);

	LCD1602_E = 1;	  //写入时序
	Lcd1602_Delay1ms(5);
	LCD1602_E = 0;

	LCD1602_DATAPINS = dat << 4; //写入低四位
	Lcd1602_Delay1ms(1);

	LCD1602_E = 1;	  //写入时序
	Lcd1602_Delay1ms(5);
	LCD1602_E = 0;
}
#endif
/*******************************************************************************
* 函 数 名       : LcdInit()
* 函数功能		 : 初始化LCD屏
* 输    入       : 无
* 输    出       : 无
*******************************************************************************/		   
#ifndef		LCD1602_4PINS
void LcdInit()						  //LCD初始化子程序
{
 	LcdWriteCom(0x38);  //开显示
	LcdWriteCom(0x0c);  //开显示不显示光标
	LcdWriteCom(0x06);  //写一个指针加1
	LcdWriteCom(0x01);  //清屏
	LcdWriteCom(0x80);  //设置数据指针起点
}
#else
void LcdInit()						  //LCD初始化子程序
{
	LcdWriteCom(0x32);	 //将8位总线转为4位总线
	LcdWriteCom(0x28);	 //在四位线下的初始化
	LcdWriteCom(0x0c);  //开显示不显示光标
	LcdWriteCom(0x06);  //写一个指针加1
	LcdWriteCom(0x01);  //清屏
	LcdWriteCom(0x80);  //设置数据指针起点
}
#endif
//************************************主函数************************************************************
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
	LcdWriteCom(0x32);	 //将8位总线转为4位总线
	LcdWriteCom(0x28);	 //在四位线下的初始化
	LcdWriteCom(0x0c);  //开显示不显示光标
	LcdWriteCom(0x06);  //写一个指针加1
	//P0 = 0xBF;
	while(1)
	{
		if(KEY1 == 0 && Asking){
			Asking = 0;	 
			//P0 = 0xBF;
			LcdWriteCom(0x01);  //清屏
			LcdWriteCom(0x80);  //设置数据指针起点
			for(i=0;i<4;i++)
				LcdWriteData(AskFnsh[i]);	   
			LcdWriteCom(0xC0); //设置坐标在第二行  
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
			LcdWriteCom(0x01);  //清屏
			LcdWriteCom(0x80);  //设置数据指针起点
			for(i=0;i<5;i++)
				LcdWriteData(QzSt[i]);	   
			LcdWriteCom(0xC0); //设置坐标在第二行  
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
				LcdWriteCom(0x01);  //清屏
				LcdWriteCom(0x80);  //设置数据指针起点
				for(i=14;i<17;i++)
					LcdWriteData(AskStu[i]);	   
				LcdWriteCom(0xC0); //设置坐标在第二行  
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
//					LcdWriteCom(0x01);  //清屏
//					LcdWriteCom(0x80);  //设置数据指针起点
//					LcdWriteData('1');
//					while(1);
					Quizing = 0; 
					//P0 = 0xBF;   
					LcdWriteCom(0x01);  //清屏
					LcdWriteCom(0x80);  //设置数据指针起点
					for(i=0;i<5;i++)
						LcdWriteData(QzFnsh[i]);	   
					LcdWriteCom(0xC0); //设置坐标在第二行  
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
