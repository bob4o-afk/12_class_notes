/*****************************************************************************
* | File      	:   Touch_1IN28.c
* | Author      :   Waveshare team
* | Function    :   Hardware underlying interface
* | Info        :
*                Used to shield the underlying layers of each master
*                and enhance portability
*----------------
* |	This version:   V1.0
* | Date        :   2022-12-02
* | Info        :   Basic version
*
******************************************************************************/
#include "Touch_Driver.h"

Touch_1IN28_XY XY;
/******************************************************************************
function :	read ID 读取ID
parameter:  CST816T : 0xB5
******************************************************************************/
UBYTE Touch_1IN28_WhoAmI()
{
    if (DEV_I2C_Read_Byte(address,0xA7) == 0xB5)   
        return true;
    else
        return false;
}

/******************************************************************************
function :	reset touch 复位触摸
parameter: 
******************************************************************************/
void Touch_1IN28_Reset()
{
    DEV_Digital_Write(TP_RST_PIN, 0);
    DEV_Delay_ms(100);
    DEV_Digital_Write(TP_RST_PIN, 1);
    DEV_Delay_ms(100);
}

/******************************************************************************
function :	Read software version number 读取软件版本号
parameter:  
******************************************************************************/
UBYTE Touch_1IN28_Read_Revision()
{
    return DEV_I2C_Read_Byte(address,0xA9);
}

/******************************************************************************
function :	exit sleep mode 退出休眠模式
parameter:  
******************************************************************************/
void Touch_1IN28_Stop_Sleep()
{
    DEV_I2C_Write_Byte(address,DisAutoSleep,0x01);
}

/******************************************************************************
function :	Set touch mode 设置触摸模式
parameter:  
        mode = 0 gestures mode 
        mode = 1 point mode
        mode = 2 mixed mode
******************************************************************************/
void Touch_1IN28_Set_Mode(UBYTE mode)
{
    if (mode == 1)
    {
        DEV_I2C_Write_Byte(address,IrqCtl,0X41);
        DEV_I2C_Write_Byte(address,NorScanPer,0X01);//Normal fast detection cycle unit 10ms
        DEV_I2C_Write_Byte(address,IrqPluseWidth,0x0f); //Interrupt low pulse output width 1.5MS
    }       
    else if(mode == 2)
        DEV_I2C_Write_Byte(address,IrqCtl,0X71);
    else
        {
            DEV_I2C_Write_Byte(address,IrqCtl,0X11);
            DEV_I2C_Write_Byte(address,NorScanPer,0X01);
            DEV_I2C_Write_Byte(address,IrqPluseWidth,0x01);//Interrupt low pulse output width 1.5MS
            DEV_I2C_Write_Byte(address,MotionMask,EnDClick);//Enable double-tap mode
        }

}

/******************************************************************************
function :	wake up touchscreen 唤醒触摸屏
parameter:  
******************************************************************************/
void Touch_1IN28_Wake_up()
{
    DEV_Digital_Write(TP_RST_PIN, 0);
    DEV_Delay_ms(10);
    DEV_Digital_Write(TP_RST_PIN, 1);
    DEV_Delay_ms(50);
    DEV_I2C_Write_Byte(address,0xFE,0x01);
}


/******************************************************************************
function :	screen initialization 屏幕初始化
parameter:  
******************************************************************************/
UBYTE Touch_1IN28_init(UBYTE mode)
{
    UBYTE bRet,Rev;
    Touch_1IN28_Reset();
    
    bRet = Touch_1IN28_WhoAmI();
    if (bRet)
    {
        // Serial.println("Success:Detected CST816T.");
        Rev = Touch_1IN28_Read_Revision();
        // Serial.print("CST816T Revision = ");
        // Serial.println(Rev);
        Touch_1IN28_Stop_Sleep();
    }
    else
    {
        Serial.println("Error: Not Detected CST816T.");
        return false;
    }
    XY.mode = mode;
    Touch_1IN28_Set_Mode(mode);

    XY.x_point = 0;
    XY.y_point = 0;
    return true;
}

/******************************************************************************
function :	Get the corresponding point coordinates 获取对应的点坐标
parameter:  
******************************************************************************/
Touch_1IN28_XY Touch_1IN28_Get_Point()
{
    UBYTE data[4];
    DEV_I2C_Read_nByte(address, 0x03, data, 4);
    
    XY.x_point = ((data[0] & 0x0f)<<8) + data[1];
    XY.y_point = ((data[2] & 0x0f)<<8) + data[3];
    
    return XY;
}












