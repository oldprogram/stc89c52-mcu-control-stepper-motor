/*-------------------------------------------
简单的串口通信
-------------------------------------------*/
#include"stepper_motor.h"
#include<reg52.h>

#define uint unsigned int
#define uchar unsigned char

sbit ADDO = P3^3;
sbit ADSK = P3^2;

unsigned int  speed1,speed2,speed3,speed4,speed5;//控制5个点机的速度
unsigned int  dang[8]={2,3,4,5,6,7,8,9};//8个档位
unsigned char num1,num2,num3,num4,num5;//控制5个电机的8个相轮转
unsigned char go1,go2,go3,go4,go5;//控制5个电机的正反转
uint time;

uchar flag,a,i;                    //标志接收串口中断标志，接收SBUF内容
uchar table[26];
/*--------------------------------------------
USAR初始函数 
---------------------------------------------*/
void USRT_init()
{
    TMOD|=0x20;            //设置T1定时器工作方式2
    TH1=0xfd;            //T1定时器装初值
    TL1=0xfd;
    TR1=1;                //启动T1定时器
    REN=1;                //允许串口中断接收
    SM0=0;                //设定串口工作方式
    SM1=1;
    EA=1;                //开总中断
    ES=1;                //开串口中断
}
/*--------------------------------------------
串口发送
---------------------------------------------*/	
void USRT_Send(uchar send)
{	
	SBUF=send;
    while(!TI);        //每次等待发送完毕，再执行下一条
    TI=0;            //手动清0
}
/*--------------------------------------------
串口中断程序
---------------------------------------------*/
void ser()interrupt 4
{
    RI=0;
    a=SBUF;
    flag=1;
}
/*--------------------------------------------
读取重力信息
---------------------------------------------*/
unsigned long ReadCount(void)
{
	unsigned long Count;
	unsigned char i;
	ADSK=0;
	Count=0;
	while(ADDO);
	for (i=0;i<24;i++){
		ADSK=1;
		Count=Count<<1;
		ADSK=0;
		if(ADDO)Count++;
	}
	ADSK=1;
	if((Count&0x800000)!=0)//最高位为1说明为负数
	{
		table[0]='-';
		Count=16777217-Count;//转变为对应负数
	}
	else table[0]='+';
	Count=Count*50000/16777216;
	table[1]='0'+Count%10000/1000;
	table[2]='0'+Count%1000/100;
	table[3]='0'+Count%100/10;
	table[4]='0'+Count%10;
	table[5]=0x0d;
	table[6]=0x0a;
	ADSK=0;
	return(Count);
}
/*--------------------------------------------
主函数
---------------------------------------------*/
void main()
{
	time=0;
	speed1=speed2=speed3=speed4=speed5=2;
	num1=num2=num3=num4=num5=0;
	go1=go2=go3=go4=go5=1;
	USRT_init();
    while(1)
    {
		time++;
		if(time==200000)time=0;
		if(time%speed1==0)
		{
			//if(num1==0)Coil_OFF1;
			switch(num1){
			case 0:num1++;
			if(go1==0)Coil_A1
			else Coil_A1
			break;
			case 1:num1++;
			if(go1==0)Coil_AB1
			else Coil_DA1
		 	break;
			case 2:num1++;
			if(go1==0)Coil_B1 
			else Coil_D1
			break;
			case 3:num1++;
			if(go1==0)Coil_BC1
			else Coil_CD1
			break;
			case 4:num1++;
			if(go1==0)Coil_C1	
			else Coil_C1
			break;
			case 5:num1++;
			if(go1==0)Coil_CD1
			else Coil_BC1
			break;
			case 6:num1++;
			if(go1==0)Coil_D1
			else Coil_B1 
			break;
			case 7:num1=0;
			if(go1==0)Coil_DA1
			else Coil_AB1
			break;
			default:break;
			}
		}
		if(time%speed2==0)
		{
			//if(num2==0)Coil_OFF2;
			switch(num2){
			case 0:num2++;
			if(go2==0)Coil_A2
			else Coil_A2
			break;
			case 1:num2++;
			if(go2==0)Coil_AB2
			else Coil_DA2
		 	break;
			case 2:num2++;
			if(go2==0)Coil_B2 
			else Coil_D2
			break;
			case 3:num2++;
			if(go2==0)Coil_BC2
			else Coil_CD2
			break;
			case 4:num2++;
			if(go2==0)Coil_C2	
			else Coil_C2
			break;
			case 5:num2++;
			if(go2==0)Coil_CD2
			else Coil_BC2
			break;
			case 6:num2++;
			if(go2==0)Coil_D2
			else Coil_B2 
			break;
			case 7:num2=0;
			if(go2==0)Coil_DA2
			else Coil_AB2
			break;
			default:break;
			}
		}
		if(time%speed3==0)
		{
			//if(num3==0)Coil_OFF3;
			switch(num3){
			case 0:num3++;
			if(go3==0)Coil_A3
			else Coil_A3
			break;
			case 1:num3++;
			if(go3==0)Coil_AB3
			else Coil_DA3
		 	break;
			case 2:num3++;
			if(go3==0)Coil_B3 
			else Coil_D3
			break;
			case 3:num3++;
			if(go3==0)Coil_BC3
			else Coil_CD3
			break;
			case 4:num3++;
			if(go3==0)Coil_C3	
			else Coil_C3
			break;
			case 5:num3++;
			if(go3==0)Coil_CD3
			else Coil_BC3
			break;
			case 6:num3++;
			if(go3==0)Coil_D3
			else Coil_B3 
			break;
			case 7:num3=0;
			if(go3==0)Coil_DA3
			else Coil_AB3
			break;
			default:break;
			}
		}
		if(time%speed4==0)
		{
			//if(num4==0)Coil_OFF4;
			switch(num4){
			case 0:num4++;
			if(go4==0)Coil_A4
			else Coil_A4
			break;
			case 1:num4++;
			if(go4==0)Coil_AB4
			else Coil_DA4
		 	break;
			case 2:num4++;
			if(go4==0)Coil_B4 
			else Coil_D4
			break;
			case 3:num4++;
			if(go4==0)Coil_BC4
			else Coil_CD4
			break;
			case 4:num4++;
			if(go4==0)Coil_C4	
			else Coil_C4
			break;
			case 5:num4++;
			if(go4==0)Coil_CD4
			else Coil_BC4
			break;
			case 6:num4++;
			if(go4==0)Coil_D4
			else Coil_B4 
			break;
			case 7:num4=0;
			if(go4==0)Coil_DA4
			else Coil_AB4
			break;
			default:break;
			}
		}
		if(time%speed5==0)
		{
			//if(num5==0)Coil_OFF5;
			switch(num5){
			case 0:num5++;
			if(go5==0)Coil_A5
			else Coil_A5
			break;
			case 1:num5++;
			if(go5==0)Coil_AB5
			else Coil_DA5
		 	break;
			case 2:num5++;
			if(go5==0)Coil_B5 
			else Coil_D5
			break;
			case 3:num5++;
			if(go5==0)Coil_BC5
			else Coil_CD5
			break;
			case 4:num5++;
			if(go5==0)Coil_C5	
			else Coil_C5
			break;
			case 5:num5++;
			if(go5==0)Coil_CD5
			else Coil_BC5
			break;
			case 6:num5++;
			if(go5==0)Coil_D5
			else Coil_B5 
			break;
			case 7:num5=0;
			if(go5==0)Coil_DA5
			else Coil_AB5
			break;
			default:break;
			}
		}
		if(flag==1)                //检测到串口中断。表示有数据传过来了
	    {
	        ES=0;  					//关闭串口中断，接下来要发送数据，如果不关闭每次发送之后串口中断都会执行又进入if(flag==1)那里，然后死循环
			if(a=='0'){
				ReadCount();
				for(i=0;i<8;i++)    //将table[]中的前6个发送出去
		        {
		            USRT_Send(table[i]);
		        }
			}else{
				if((a & 0xE0) == 0x80){//第5号
					if((a & 0x18) == 0x00){//停
						speed5=200001;															
					}else if((a & 0x18) == 0x08){//前
						go5=1;
						speed5=dang[a&0x07];
					}else if((a & 0x18) == 0x10){//后
						go5=0;
						speed5=dang[a&0x07];
					}
					USRT_Send(a);
				}else if(a & 0xE0 == 0x60){//第4号
					if((a & 0x18) == 0x00){//停
						speed4=200001;															
					}else if((a & 0x18) == 0x08){//前
						go4=1;
						speed4=dang[a&0x07];
					}else if((a & 0x18) == 0x10){//后
						go4=0;
						speed4=dang[a&0x07];
					}
					USRT_Send(a);
				}else if(a & 0xE0 == 0x40){//第3号
					if((a & 0x18) == 0x00){//停
						speed3=200001;															
					}else if((a & 0x18) == 0x08){//前
						go3=1;
						speed3=dang[a&0x07];
					}else if((a & 0x18) == 0x10){//后
						go3=0;
						speed3=dang[a&0x07];
					}
					USRT_Send(a);
				}else if(a & 0xE0 == 0x20){//第2号
					if((a & 0x18) == 0x00){//停
						speed2=200001;															
					}else if((a & 0x18) == 0x08){//前
						go2=1;
						speed2=dang[a&0x07];
					}else if((a & 0x18) == 0x10){//后
						go2=0;
						speed2=dang[a&0x07];
					}
					USRT_Send(a);
				}else if(a & 0xE0 == 0x00){//第1号
					if((a & 0x18) == 0x00){//停
						speed1=200001;															
					}else if((a & 0x18) == 0x08){//前
						go1=1;
						speed1=dang[a&0x07];
					}else if((a & 0x18) == 0x10){//后
						go1=0;
						speed1=dang[a&0x07];
					}
					USRT_Send(a);
				}
			}	
	        TI=0;
	        ES=1;
	        flag=0;
	    }
    }
}

/*
采用帧格式为
a=='0'表示要重量数据
其他的为步进电机控制命令
0000 0000
前3位表示选择第几个步进电机的：000(1);001(2);010(3);011(4);100(5)
接下来2位表示控制方向命令：00(stop);01(go);10(back)
接下来3位表示档位：000(0档);001(1);002(2);003(3);...
*/
