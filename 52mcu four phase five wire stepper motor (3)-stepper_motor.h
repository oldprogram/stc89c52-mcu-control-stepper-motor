#include<reg52.h>

sbit A1=P1^0; //定义步进电机连接端口
sbit B1=P1^1;
sbit C1=P1^2;
sbit D1=P1^3;
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
