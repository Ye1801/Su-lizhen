#include "adxl345.h"
#include "i2c.h"
#include "math.h"

/****************************************功能说明****************************************

1.CS和SD0必须接到VCC

****************************************功能说明****************************************/
short xang=0;
short yang=0;
short zang=0;
	
//初始化ADXL345.
//返回值:0,初始化成功;1,初始化失败.
uint8_t ADXL345_Init(void)
{				  
	uint8_t id=0,val=0;
	HAL_I2C_Mem_Read(&hi2c1,ADXL_READ,DEVICE_ID,I2C_MEMADD_SIZE_8BIT,&id,1,0xff);	//读取器件ID
	if(id ==0XE5)	
	{  
		val = 0x2B;		//低电平中断输出,13位全分辨率,输出数据右对齐,16g量程 
		HAL_I2C_Mem_Write(&hi2c1,ADXL_WRITE,DATA_FORMAT,I2C_MEMADD_SIZE_8BIT,&val,1,0xFF);
		
		val = 0x0A;		//数据输出速度为100Hz
		HAL_I2C_Mem_Write(&hi2c1,ADXL_WRITE,BW_RATE,I2C_MEMADD_SIZE_8BIT,&val,1,0xFF);
			
		val = 0x28;		//链接使能,测量模式
		HAL_I2C_Mem_Write(&hi2c1,ADXL_WRITE,POWER_CTL,I2C_MEMADD_SIZE_8BIT,&val,1,0xFF);
		   	
		val = 0x00;
		HAL_I2C_Mem_Write(&hi2c1,ADXL_WRITE,INT_ENABLE,I2C_MEMADD_SIZE_8BIT,&val,1,0xFF);
		HAL_I2C_Mem_Write(&hi2c1,ADXL_WRITE,OFSX,I2C_MEMADD_SIZE_8BIT,&val,1,0xFF);
		HAL_I2C_Mem_Write(&hi2c1,ADXL_WRITE,OFSY,I2C_MEMADD_SIZE_8BIT,&val,1,0xFF);
		HAL_I2C_Mem_Write(&hi2c1,ADXL_WRITE,OFSZ,I2C_MEMADD_SIZE_8BIT,&val,1,0xFF);
	
		return 0;
	}			
	return 1;	   								  
} 



//读取ADXL的平均值
//x,y,z:读取10次后取平均值
void ADXL345_RD_Avval(short *x,short *y,short *z)
{
	short tx=0,ty=0,tz=0;	   
	uint8_t i;  
	for(i=0;i<10;i++)
	{
		ADXL345_RD_XYZ(x,y,z);
		HAL_Delay(10);
		tx+=(short)*x;
		ty+=(short)*y;
		tz+=(short)*z;	   
	}
	*x=tx/10;
	*y=ty/10;
	*z=tz/10;
}  

//读取3个轴的数据
//x,y,z:读取到的数据
void ADXL345_RD_XYZ(short *x,short *y,short *z)
{
	uint8_t buf[6];								  		   
	
	HAL_I2C_Mem_Read(&hi2c1,ADXL_READ,DATA_X0,I2C_MEMADD_SIZE_8BIT,&buf[0],1,0xFF);
	HAL_I2C_Mem_Read(&hi2c1,ADXL_READ,DATA_X1,I2C_MEMADD_SIZE_8BIT,&buf[1],1,0xFF);
	HAL_I2C_Mem_Read(&hi2c1,ADXL_READ,DATA_Y0,I2C_MEMADD_SIZE_8BIT,&buf[2],1,0xFF);
	HAL_I2C_Mem_Read(&hi2c1,ADXL_READ,DATA_Y1,I2C_MEMADD_SIZE_8BIT,&buf[3],1,0xFF);
	HAL_I2C_Mem_Read(&hi2c1,ADXL_READ,DATA_Z0,I2C_MEMADD_SIZE_8BIT,&buf[4],1,0xFF);
	HAL_I2C_Mem_Read(&hi2c1,ADXL_READ,DATA_Z1,I2C_MEMADD_SIZE_8BIT,&buf[5],1,0xFF);	
 
	*x=(short)(((uint16_t)buf[1]<<8)+buf[0]); 	    
	*y=(short)(((uint16_t)buf[3]<<8)+buf[2]); 	    
	*z=(short)(((uint16_t)buf[5]<<8)+buf[4]); 	   
}

//自动校准
//xval,yval,zval:x,y,z轴的校准值
void ADXL345_AUTO_Adjust(char *xval,char *yval,char *zval)
{
	short tx,ty,tz;
	uint8_t i, val;
	short offx=0,offy=0,offz=0;
	val = 0x00;		//先进入休眠模式.
	HAL_I2C_Mem_Write(&hi2c1,ADXL_WRITE,POWER_CTL,I2C_MEMADD_SIZE_8BIT,&val,1,0xFF);
	//ADXL345_WR_Reg(POWER_CTL,0x00);	   	
	HAL_Delay(100);
	
	val = 0x2B;		//低电平中断输出,13位全分辨率,输出数据右对齐,16g量程 
	HAL_I2C_Mem_Write(&hi2c1,ADXL_WRITE,DATA_FORMAT,I2C_MEMADD_SIZE_8BIT,&val,1,0xFF);	
	
	val = 0x0A;		//数据输出速度为100Hz
	HAL_I2C_Mem_Write(&hi2c1,ADXL_WRITE,BW_RATE,I2C_MEMADD_SIZE_8BIT,&val,1,0xFF);
	
	val = 0x28;		//链接使能,测量模式 
	HAL_I2C_Mem_Write(&hi2c1,ADXL_WRITE,POWER_CTL,I2C_MEMADD_SIZE_8BIT,&val,1,0xFF);	   	
	
	val = 0x00;
	HAL_I2C_Mem_Write(&hi2c1,ADXL_WRITE,INT_ENABLE,I2C_MEMADD_SIZE_8BIT,&val,1,0xFF);
	HAL_I2C_Mem_Write(&hi2c1,ADXL_WRITE,OFSX,I2C_MEMADD_SIZE_8BIT,&val,1,0xFF);
	HAL_I2C_Mem_Write(&hi2c1,ADXL_WRITE,OFSY,I2C_MEMADD_SIZE_8BIT,&val,1,0xFF);
	HAL_I2C_Mem_Write(&hi2c1,ADXL_WRITE,OFSZ,I2C_MEMADD_SIZE_8BIT,&val,1,0xFF);

	HAL_Delay(12);
	for(i=0;i<10;i++)
	{
		ADXL345_RD_Avval(&tx,&ty,&tz);
		offx+=tx;
		offy+=ty;
		offz+=tz;
	}	 		
	offx/=10;
	offy/=10;
	offz/=10;
	*xval=-offx/4;
	*yval=-offy/4;
	*zval=-(offz-256)/4;
	HAL_I2C_Mem_Write(&hi2c1,ADXL_WRITE,OFSX,I2C_MEMADD_SIZE_8BIT,(uint8_t *)xval,1,0xFF);
	HAL_I2C_Mem_Write(&hi2c1,ADXL_WRITE,OFSY,I2C_MEMADD_SIZE_8BIT,(uint8_t *)yval,1,0xFF);
	HAL_I2C_Mem_Write(&hi2c1,ADXL_WRITE,OFSZ,I2C_MEMADD_SIZE_8BIT,(uint8_t *)zval,1,0xFF);	
}

//读取ADXL345的数据times次,再取平均
//x,y,z:读到的数据
//times:读取多少次
void ADXL345_Read_Average(short *x,short *y,short *z,uint8_t times)
{
	uint8_t i;
	short tx,ty,tz;
	*x=0;
	*y=0;
	*z=0;
	if(times)//读取次数不为0
	{
		for(i=0;i<times;i++)//连续读取times次
		{
			ADXL345_RD_XYZ(&tx,&ty,&tz);
			*x+=tx;
			*y+=ty;
			*z+=tz;
			HAL_Delay(5);
		}
		*x/=times;
		*y/=times;
		*z/=times;
	}
} 

//得到角度
//x,y,z:x,y,z方向的重力加速度分量(不需要单位,直接数值即可)
//dir:要获得的角度.0,与Z轴的角度;1,与X轴的角度;2,与Y轴的角度.
//返回值:角度值.单位0.1°.
//res得到的是弧度值，需要将其转换为角度值也就是*180/3.14
short ADXL345_Get_Angle(float x,float y,float z,uint8_t dir)
{
	float temp;
 	float res=0;
	switch(dir)
	{
		case 0://与自然Z轴的角度
 			temp=sqrt((x*x+y*y))/z;
 			res=atan(temp);
 			break;
		case 1://与自然X轴的角度
 			temp=x/sqrt((y*y+z*z));
 			res=atan(temp);
 			break;
 		case 2://与自然Y轴的角度
 			temp=y/sqrt((x*x+z*z));
 			res=atan(temp);
 			break;
 	}
	return res*180/3.14;
}

uint8_t data_pros()	//数据处理函数
{
	uint8_t retval =0;
	static uint8_t value =50;
	
	short x,y,z;
	ADXL345_Read_Average(&x,&y,&z,10);  //读取x,y,z 3个方向的加速度值 总共10次
	xang=ADXL345_Get_Angle(x,y,z,1);
	yang=ADXL345_Get_Angle(x,y,z,2);
	zang=ADXL345_Get_Angle(x,y,z,0);

	if((xang>value)||(xang<-value)||(yang>value)||(yang<-value)||(zang>value)||(zang<-value))
	{
		retval=1;
	}
	return retval;
}

