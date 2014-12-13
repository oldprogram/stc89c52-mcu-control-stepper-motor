/*-----------------------------------------------
内容：本程序用于测试4相步进电机常规驱动 
使用1-2相励磁
1-2相激励功率增倍，步进角度减半，抖动减少
顺序如下 a-ab-b-bc-c-cd-d-da   又称4相8拍
------------------------------------------------*/

#include <reg52.h>


sbit A1=P1^0; //定义步进电机连接端口
sbit B1=P1^1;
sbit C1=P1^2;
sbit D1=P1^4;
sbit A2=P1^4; //定义步进电机连接端口
sbit B2=P1^5;
sbit C2=P1^6;
sbit D2=P1^7;
sbit A3=P3^4; //定义步进电机连接端口
sbit B3=P3^5;
sbit C3=P3^6;
sbit D3=P3^7;
sbit A4=P2^4; //定义步进电机连接端口
sbit B4=P2^5;
sbit C4=P2^6;
sbit D4=P2^7;
sbit A5=P2^0; //定义步进电机连接端口
sbit B5=P2^1;
sbit C5=P2^2;
sbit D5=P2^3;

#define Coil_AB1 {A1=1;B1=1;C1=0;D1=0;}//AB相通电，其他相断电
#define Coil_BC1 {A1=0;B1=1;C1=1;D1=0;}//BC相通电，其他相断电
#define Coil_CD1 {A1=0;B1=0;C1=1;D1=1;}//CD相通电，其他相断电
#define Coil_DA1 {A1=1;B1=0;C1=0;D1=1;}//D相通电，其他相断电
#define Coil_A1 {A1=1;B1=0;C1=0;D1=0;}//A相通电，其他相断电
#define Coil_B1 {A1=0;B1=1;C1=0;D1=0;}//B相通电，其他相断电
#define Coil_C1 {A1=0;B1=0;C1=1;D1=0;}//C相通电，其他相断电
#define Coil_D1 {A1=0;B1=0;C1=0;D1=1;}//D相通电，其他相断电
#define Coil_OFF1 {A1=0;B1=0;C1=0;D1=0;}//全部断电

#define Coil_AB2 {A2=1;B2=1;C2=0;D2=0;}//AB相通电，其他相断电
#define Coil_BC2 {A2=0;B2=1;C2=1;D2=0;}//BC相通电，其他相断电
#define Coil_CD2 {A2=0;B2=0;C2=1;D2=1;}//CD相通电，其他相断电
#define Coil_DA2 {A2=1;B2=0;C2=0;D2=1;}//D相通电，其他相断电
#define Coil_A2 {A2=1;B2=0;C2=0;D2=0;}//A相通电，其他相断电
#define Coil_B2 {A2=0;B2=1;C2=0;D2=0;}//B相通电，其他相断电
#define Coil_C2 {A2=0;B2=0;C2=1;D2=0;}//C相通电，其他相断电
#define Coil_D2 {A2=0;B2=0;C2=0;D2=1;}//D相通电，其他相断电
#define Coil_OFF2 {A2=0;B2=0;C2=0;D2=0;}//全部断电

#define Coil_AB3 {A3=1;B3=1;C3=0;D3=0;}//AB相通电，其他相断电
#define Coil_BC3 {A3=0;B3=1;C3=1;D3=0;}//BC相通电，其他相断电
#define Coil_CD3 {A3=0;B3=0;C3=1;D3=1;}//CD相通电，其他相断电
#define Coil_DA3 {A3=1;B3=0;C3=0;D3=1;}//D相通电，其他相断电
#define Coil_A3 {A3=1;B3=0;C3=0;D3=0;}//A相通电，其他相断电
#define Coil_B3 {A3=0;B3=1;C3=0;D3=0;}//B相通电，其他相断电
#define Coil_C3 {A3=0;B3=0;C3=1;D3=0;}//C相通电，其他相断电
#define Coil_D3 {A3=0;B3=0;C3=0;D3=1;}//D相通电，其他相断电
#define Coil_OFF3 {A3=0;B3=0;C3=0;D3=0;}//全部断电

#define Coil_AB4 {A4=1;B4=1;C4=0;D4=0;}//AB相通电，其他相断电
#define Coil_BC4 {A4=0;B4=1;C4=1;D4=0;}//BC相通电，其他相断电
#define Coil_CD4 {A4=0;B4=0;C4=1;D4=1;}//CD相通电，其他相断电
#define Coil_DA4 {A4=1;B4=0;C4=0;D4=1;}//D相通电，其他相断电
#define Coil_A4 {A4=1;B4=0;C4=0;D4=0;}//A相通电，其他相断电
#define Coil_B4 {A4=0;B4=1;C4=0;D4=0;}//B相通电，其他相断电
#define Coil_C4 {A4=0;B4=0;C4=1;D4=0;}//C相通电，其他相断电
#define Coil_D4 {A4=0;B4=0;C4=0;D4=1;}//D相通电，其他相断电
#define Coil_OFF4 {A4=0;B4=0;C4=0;D4=0;}//全部断电

#define Coil_AB5 {A5=1;B5=1;C5=0;D5=0;}//AB相通电，其他相断电
#define Coil_BC5 {A5=0;B5=1;C5=1;D5=0;}//BC相通电，其他相断电
#define Coil_CD5 {A5=0;B5=0;C5=1;D5=1;}//CD相通电，其他相断电
#define Coil_DA5 {A5=1;B5=0;C5=0;D5=1;}//D相通电，其他相断电
#define Coil_A5 {A5=1;B5=0;C5=0;D5=0;}//A相通电，其他相断电
#define Coil_B5 {A5=0;B5=1;C5=0;D5=0;}//B相通电，其他相断电
#define Coil_C5 {A5=0;B5=0;C5=1;D5=0;}//C相通电，其他相断电
#define Coil_D5 {A5=0;B5=0;C5=0;D5=1;}//D相通电，其他相断电
#define Coil_OFF5 {A5=0;B5=0;C5=0;D5=0;}//全部断电

unsigned char Speed;
bit Flag;
/*------------------------------------------------
uS延时函数，含有输入参数 unsigned char t，无返回值
unsigned char 是定义无符号字符变量，其值的范围是
0~255 这里使用晶振12M，精确延时请使用汇编,大致延时
长度如下 T=tx2+5 uS 
------------------------------------------------*/
void DelayUs2x(unsigned char t)
{   
	while(--t);
}
/*------------------------------------------------
mS延时函数，含有输入参数 unsigned char t，无返回值
unsigned char 是定义无符号字符变量，其值的范围是
0~255 这里使用晶振12M，精确延时请使用汇编
------------------------------------------------*/
void DelayMs(unsigned char t)
{
	
	while(t--)
	{
		//大致延时1mS
		DelayUs2x(245);
		DelayUs2x(245);
	}
}
/*------------------------------------------------
主函数
------------------------------------------------*/
main()
{
	unsigned int i=512;//旋转一周时间
	
	EA=1;          //全局中断开
	EX0=1;         //外部中断0开
	IT0=1;         //1表示边沿触发
	
	Speed=2;
	while(1){
		Coil_OFF1
		Coil_OFF2
		Coil_OFF3
		Coil_OFF4
		Coil_OFF5
		while((i--)&&Flag)  //正向
		{ 
			Coil_A1   
			Coil_A2  
			Coil_A3
			Coil_A4
   			Coil_A5
			DelayMs(Speed);
			Coil_AB1                //遇到Coil_AB1  用{A1=1;B1=1;C1=0;D1=0;}代替
			Coil_AB2
			Coil_AB3
			Coil_AB4
			Coil_AB5
			DelayMs(Speed);         //改变这个参数可以调整电机转速 ,
			//数字越小，转速越大,力矩越小
			Coil_B1 
			Coil_B2 
			Coil_B3 
			Coil_B4 
			Coil_B5
			DelayMs(Speed);
			Coil_BC1
			Coil_BC2
			Coil_BC3
			Coil_BC4
			Coil_BC5
			DelayMs(Speed);
			Coil_C1	
			Coil_C2 
			Coil_C3	
			Coil_C4 
			Coil_C5
			DelayMs(Speed);
			Coil_CD1
			Coil_CD2
			Coil_CD3
			Coil_CD4
			Coil_CD5
			DelayMs(Speed);
			Coil_D1      
 		    Coil_D2  
			Coil_D3      
 		    Coil_D4 
 		    Coil_D5
			DelayMs(Speed);
			Coil_DA1
			Coil_DA2
			Coil_DA3
			Coil_DA4
			Coil_DA5
			DelayMs(Speed);
		}
		Coil_OFF1
		Coil_OFF2
		Coil_OFF3
		Coil_OFF4
		Coil_OFF5
		i=512;
		while((i--)&&(!Flag))//反向
		{  
			Coil_A1   
			Coil_A2  
			Coil_A3
			Coil_A4    
    		Coil_A5 
			DelayMs(Speed);
			Coil_DA1
			Coil_DA2
			Coil_DA3
			Coil_DA4   
            Coil_DA5 
			DelayMs(Speed);      
			Coil_D1      
 		    Coil_D2  
			Coil_D3      
 		    Coil_D4  
			Coil_D5 
			DelayMs(Speed);
			Coil_CD1
			Coil_CD2
			Coil_CD3
			Coil_CD4
			Coil_CD5
			DelayMs(Speed);
			Coil_C1	
			Coil_C2 
			Coil_C3	
			Coil_C4 
			Coil_C5
			DelayMs(Speed);
			Coil_BC1
			Coil_BC2
			Coil_BC3
			Coil_BC4
			Coil_BC5
			DelayMs(Speed);
			Coil_B1 
			Coil_B2 
			Coil_B3 
			Coil_B4
     	    Coil_B5
			DelayMs(Speed);
			Coil_AB1                //遇到Coil_AB1  用{A1=1;B1=1;C1=0;D1=0;}代替
			Coil_AB2
			Coil_AB3
			Coil_AB4
			Coil_AB5
			DelayMs(Speed);
		}
	}
}

/*------------------------------------------------
外部中断程序
------------------------------------------------*/
void ISR_INT0(void) interrupt 0 
{
	
	if(!INT0)
	{
		DelayMs(10);//在此处可以添加去抖动程序，防止按键抖动造成错误
		if(!INT0)
			//while(!INT1);//等待按键释放
		{
			Flag=!Flag;   
		}
	}
}
