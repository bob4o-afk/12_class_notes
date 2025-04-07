#include "LCD_Driver.h"
#include "Touch_Driver.h"
#include "GUI_Paint.h"
#include "image.h"


UBYTE flag = 0,flgh = 0;
UWORD x,y,l = 0;

void setup()
{  
    Touch_1IN28_XY XY;
    XY.mode = 0;
    XY.x_point = 0;
    XY.y_point = 0;
    Config_Init();
    LCD_Init();
    if(Touch_1IN28_init(XY.mode) == true)
        Serial.println("OK!");
    else
        Serial.println("NO!");

    LCD_SetBacklight(1000);
    Paint_NewImage(LCD_WIDTH, LCD_HEIGHT, 0, BLACK);
    Paint_Clear(WHITE);
    attachInterrupt(1,Touch_INT_callback,LOW);
    pinMode(TP_INT_PIN, INPUT_PULLUP);
    Paint_DrawString_EN(35, 90, "Gesture test", &Font20, BLACK, WHITE);
    Paint_DrawString_EN(10, 120, "Complete as prompted", &Font16, BLACK, WHITE);
    DEV_Delay_ms(500);
}

void loop()
{   
    Paint_ClearWindows(10,90,230,137,WHITE);  
    Paint_DrawString_EN(105, 100, "Up", &Font24, 0X647C, WHITE);
    while(XY.Gesture != UP)
    {    
        if (flag == TOUCH_IRQ)
        {
            XY.Gesture = DEV_I2C_Read_Byte(address,0x01);
            flag = TOUCH_DRAW;
        }      
        DEV_Delay_ms(10);   
    }

    Paint_ClearWindows(105,100,160,155,WHITE);  
    Paint_DrawString_EN(85, 100, "Down", &Font24, 0X647C, WHITE);
    while(XY.Gesture != Down)
    {
        if (flag == TOUCH_IRQ)
        {
            XY.Gesture = DEV_I2C_Read_Byte(address,0x01);
            flag = TOUCH_DRAW;
        }    
        DEV_Delay_ms(10);     
    }

    Paint_ClearWindows(85, 100,160,155,WHITE);
    Paint_DrawString_EN(85, 100, "Left", &Font24, 0X647C, WHITE);
    while(XY.Gesture != LEFT)
    {
        if (flag == TOUCH_IRQ)
        {
            XY.Gesture = DEV_I2C_Read_Byte(address,0x01);
            flag = TOUCH_DRAW;
        }    
        DEV_Delay_ms(10);     
    }

    Paint_ClearWindows(85, 100,160,155,WHITE);
    Paint_DrawString_EN(80, 100, "Right", &Font24, 0X647C, WHITE);
    while(XY.Gesture != RIGHT)
    {
        if (flag == TOUCH_IRQ)
        {
            XY.Gesture = DEV_I2C_Read_Byte(address,0x01);
            flag = TOUCH_DRAW;
        }     
        DEV_Delay_ms(10);    
    }

    Paint_ClearWindows(80, 100,165,160,WHITE);
    Paint_DrawString_EN(47, 100, "Long Press", &Font20, 0X647C, WHITE);
    while(XY.Gesture != LONG_PRESS)
    {
        if (flag == TOUCH_IRQ)
        {
            XY.Gesture = DEV_I2C_Read_Byte(address,0x01);
            flag = TOUCH_DRAW;
        }     
        DEV_Delay_ms(10);    
    }

    Paint_ClearWindows(47, 100,200,155,WHITE);
    Paint_DrawString_EN(35, 100, "Double Click", &Font20, 0X647C, WHITE);
    while(XY.Gesture != DOUBLE_CLICK)
    {
        if (flag == TOUCH_IRQ)
        {
            XY.Gesture = DEV_I2C_Read_Byte(address,0x01);
            flag = TOUCH_DRAW;
        } 
        DEV_Delay_ms(10);        
    }

    XY.mode = 1;
    Touch_1IN28_init(XY.mode);
    Paint_ClearWindows(10,90,230,137,WHITE);  
    Paint_DrawRectangle(0, 0, 35, 208,RED,DOT_PIXEL_1X1,DRAW_FILL_FULL);
    Paint_DrawRectangle(0, 0, 208, 35,GREEN,DOT_PIXEL_1X1,DRAW_FILL_FULL);
    Paint_DrawRectangle(206, 0, 240, 240,BLUE,DOT_PIXEL_1X1,DRAW_FILL_FULL);
    Paint_DrawRectangle(0, 206, 240, 240,GRAY,DOT_PIXEL_1X1,DRAW_FILL_FULL);
    while (1)
    {
        if (flag == TOUCH_IRQ)
        {
            XY = Touch_1IN28_Get_Point();
            if(flgh == TOUCH_INIT && XY.x_point != TOUCH_INIT)
            {
                    flgh = 1; 
                    //Get the coordinates of the first point    获取第一次点的坐标
                    x = XY.x_point;
                    y = XY.y_point;
            }
            if ((XY.x_point > 35 && XY.x_point < 205) && (XY.y_point > 35 && XY.y_point < 208))
            {
                flgh = TOUCH_DRAW;//Permit painting     允许画
            }
            else
            {
                if ((XY.x_point > 0 && XY.x_point < 33) && (XY.y_point > 0 && XY.y_point < 208))
                    XY.color = RED;

                if ((XY.x_point > 0 && XY.x_point < 208) && (XY.y_point > 0 && XY.y_point < 33))
                    XY.color = GREEN;

                if ((XY.x_point > 208 && XY.x_point < 240) && (XY.y_point > 0 && XY.y_point < 240))
                        XY.color = BLUE;

                if ((XY.x_point > 0 && XY.x_point < 240) && (XY.y_point > 208 && XY.y_point < 240))
                        Paint_ClearWindows(35,35,205,205,WHITE);

                flgh = TOUCH_NO_DRAW; //No painting     禁止画
                flag = TOUCH_DRAW; //Change interrupt bit      改变中断位
            }
            

            if (flgh == TOUCH_DRAW)
            {
                XY.x_point = (XY.x_point > 37)? XY.x_point : 37;
                XY.y_point = (XY.y_point > 37)? XY.y_point : 37;

                XY.x_point = (XY.x_point < 205)? XY.x_point : 205;
                XY.y_point = (XY.y_point < 203)? XY.y_point : 203;    
                
                if (l<10350) //Continuous drawing    连续画
                {
                    flag = TOUCH_DRAW;
                    Paint_DrawLine(x,y,XY.x_point, XY.y_point, XY.color, DOT_PIXEL_2X2, LINE_STYLE_SOLID);

                    l=0;
                }
                else//Draw Point    画点
                {
                    flag = TOUCH_DRAW; 
                    Paint_DrawPoint(XY.x_point, XY.y_point, XY.color, DOT_PIXEL_2X2, DOT_FILL_AROUND);
                    l = 0; 
                }
                x = XY.x_point;
                y = XY.y_point;
            }
        }
        l++;
        if (l>10600) //Decide whether to draw dots or lines   判断画点还是画线
        {
            l=10500;
        }
    }
    
    
    
}

void Touch_INT_callback()
{
    flag = TOUCH_IRQ;
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/

