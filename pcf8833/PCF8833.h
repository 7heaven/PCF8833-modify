/*
 * PCF8833.h
 *
 * Created: 2013/8/14 21:03:14
 */ 


#ifndef PCF8833_H_
#define PCF8833_H_
#include <asf.h>
#include <types.h>

/*************************LCD端口定义****************************************/
//D0
#define Set_Cs    PORTC|=0x01;//0000 0001//高
#define Clr_Cs    PORTC&=0xFE;//1111 1110//低
//D1
#define Set_DC    PORTC|=0x02;//0000 0010//高
#define Clr_DC    PORTC&=0xFD;//1111 1101//低
//D2
#define Set_nWr   PORTC|=0x04;//0000 0100//高
#define Clr_nWr   PORTC&=0xFB;//1111 1011//低
//D3
#define Set_nRd   PORTC|=0x08;//0000 1000//高
#define Clr_nRd   PORTC&=0xF7;//1111 0111//低
//D4
#define Set_Rst   PORTC|=0x10;//0001 0000//高
#define Clr_Rst   PORTC&=0xEF;//1110 1111//低



void pcf8833_init( u8 vl_ContrastLevel);//初始化调用这个就可以了，vl_ContrastLevel对比度0到11级别
void pcf8833_set_contrast(u8 vl_ContrastLevel);
void pcf8833_register_init( u8 vl_ContrastLevel);//初始化
void pcf8833_update_screen( u8 v_x1, u8 v_y1, u8 v_x2, u8 v_y2);//更新使用这个
void MC_DSC_COMMAND_WRITE(u8 Data);
void MC_DSC_DATA_WRITE(u8 Data);
void LCDClearScreen(u16 colour );



#define CNTS  1     //时间延迟

/*************************寄存器定义****************************************/
#define DSC_PCF8833_REG_NOP                 0x00
#define DSC_PCF8833_REG_SWRESET             0x01
#define DSC_PCF8833_REG_BSTROFF             0x02
#define DSC_PCF8833_REG_BSTRON              0x03
#define DSC_PCF8833_REG_RDDIDIF             0x04
#define DSC_PCF8833_REG_RDDST               0x09
#define DSC_PCF8833_REG_SLEEP_IN            0x10
#define DSC_PCF8833_REG_SLEEP_OUT           0x11
#define DSC_PCF8833_REG_PTLON               0x12
#define DSC_PCF8833_REG_NORON               0x13
#define DSC_PCF8833_REG_INVOFF              0x20
#define DSC_PCF8833_REG_INVON               0x21
#define DSC_PCF8833_REG_ALL_PIXEL_OFF       0x22
#define DSC_PCF8833_REG_ALL_PIXEL_ON        0x23
#define DSC_PCF8833_REG_SETCON              0x25
#define DSC_PCF8833_REG_DISPOFF             0x28
#define DSC_PCF8833_REG_DISPON              0x29
#define DSC_PCF8833_REG_COLUMN_SET          0x2A
#define DSC_PCF8833_REG_PAGE_SET            0x2B
#define DSC_PCF8833_REG_RAMWR               0x2C
#define DSC_PCF8833_REG_COLOR_SET           0x2D
#define DSC_PCF8833_REG_PARTIAL_AREA        0x30
#define DSC_PCF8833_REG_VSCRDEF             0x33
#define DSC_PCF8833_REG_TEOFF               0x34
#define DSC_PCF8833_REG_TEON                0x35
#define DSC_PCF8833_REG_MADCTL              0x36
#define DSC_PCF8833_REG_SEP                 0x37
#define DSC_PCF8833_REG_IDMOFF              0x38
#define DSC_PCF8833_REG_IDMON               0x39
#define DSC_PCF8833_REG_COLMOD              0x3A
#define DSC_PCF8833_REG_SET_VOP             0xB0
#define DSC_PCF8833_REG_BRS                 0xB4
#define DSC_PCF8833_REG_TRS                 0xB6
#define DSC_PCF8833_REG_FINV                0xB8
#define DSC_PCF8833_REG_DATA_ORDER          0xBA
#define DSC_PCF8833_REG_TCDFE               0xBD
#define DSC_PCF8833_REG_TCVOPE              0xBF
#define DSC_PCF8833_REG_EC                  0xC0
#define DSC_PCF8833_REG_IO                  0xC1
#define DSC_PCF8833_REG_SETMUL              0xC2
#define DSC_PCF8833_REG_TCVOPAB             0xC3
#define DSC_PCF8833_REG_TCVOPCD             0xC4
#define DSC_PCF8833_REG_TCDF                0xC5
#define DSC_PCF8833_REG_DF8COLOUR           0xC6
#define DSC_PCF8833_REG_SETBS               0xC7
#define DSC_PCF8833_REG_RDTEMP              0xC8
#define DSC_PCF8833_REG_NLI                 0xC9
#define DSC_PCF8833_REG_RDID1               0xDA
#define DSC_PCF8833_REG_RDID2               0xDB
#define DSC_PCF8833_REG_RDID3               0xDC
#define DSC_PCF8833_REG_SFD                 0xEE
#define DSC_PCF8833_REG_EFD                 0xEF
#define DSC_PCF8833_REG_CALIBRATION_MODE    0xF0
#define DSC_PCF8833_REG_OTPSHTIN            0xF1

#define WHITE       0xFFF
#define BLACK       0x000
#define RED         0x00F
#define GREEN       0x0F0
#define BLUE        0xF00
#define CYAN        0xFF0
#define MAGENTA     0xF0F
#define YELLOW      0x0FF
#define BROWN       0x22B
#define ORANGE      0x0AF
#define PINK        0xA6F

#endif /* PCF8833_H_ */