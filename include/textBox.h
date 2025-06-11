/*
 * textBox.h
 *
 *  Created on: Dec 12, 2014
 *      Author: odellw
 */

#ifndef TEXTBOX_H_
#define TEXTBOX_H_

#include <Arduino.h>
#include <ILI9341_t3.h>
#include <String.h>
#include <tbParam.h>

#define FILL_LOC_OFFSET 7
#define FILL_SIZE_OFFSET 2
#define FONT_RATIO .714

//---Font is really 5x7, but we pad 1 pxl to both H and W to accommodate char
//---Spacing

//---Size 1 Font---
#define FONT_S1_H     8
#define FONT_S1_W     (int16_t)(FONT_S1_H * FONT_RATIO)
#define S1_TB_H       (int16_t)(FONT_S1_H + 2)
#define S1_TB_W       (int16_t)(FONT_S1_W + 2)
#define S1_TB_W_PAD   3
#define S1_TB_H_PAD   1

//---Size 2 Font---
#define FONT_S2_H     12
#define FONT_S2_W     (int16_t)(FONT_S2_H * FONT_RATIO)
#define S2_TB_H       (int16_t)(FONT_S2_H + 4)
#define S2_TB_W       (int16_t)(FONT_S2_H + 4)
#define S2_TB_W_PAD   5
#define S2_TB_H_PAD   2

//---Size 3 Font---
#define FONT_S3_H     18
#define FONT_S3_W     (int16_t)(FONT_S3_H * FONT_RATIO)
#define S3_TB_H       (int16_t)(FONT_S3_H + 4)
#define S3_TB_W       (int16_t)(FONT_S3_W + 4)
#define S3_TB_W_PAD   6
#define S3_TB_H_PAD   3

//---Size 4 Font---
#define FONT_S4_H     20
#define FONT_S4_W     (int16_t)(FONT_S4_H * FONT_RATIO)
#define S4_TB_H       (int16_t)(FONT_S4_H + 5)
#define S4_TB_W       (int16_t)(FONT_S4_W + 5)
#define S4_TB_W_PAD   7
#define S4_TB_H_PAD   3

//---Size 5 Font---
#define FONT_S5_H     24
#define FONT_S5_W     (int16_t)(FONT_S5_H*FONT_RATIO)
#define S5_TB_H       (int16_t)(FONT_S5_H + 3)
#define S5_TB_W       (int16_t)(FONT_S5_W + 3)
#define S5_TB_W_PAD   8
#define S5_TB_H_PAD   3

//---Size 6 Font---
#define FONT_S6_H     30
#define FONT_S6_W     (int16_t)(FONT_S6_H*FONT_RATIO)
#define S6_TB_H       (int16_t)(FONT_S6_H + 4)
#define S6_TB_W       (int16_t)(FONT_S6_W + 4)
#define S6_TB_W_PAD   9
#define S6_TB_H_PAD   3

//---Size 7 Font---
#define FONT_S7_H     35
#define FONT_S7_W     (int16_t)(FONT_S7_H*FONT_RATIO)
#define S7_TB_H       (int16_t)(FONT_S4_H + 3)
#define S7_TB_W       (int16_t)(FONT_S4_W + 3)
#define S7_TB_W_PAD   10
#define S7_TB_H_PAD   3


//ILI9341_BLACK   0x0000
//ILI9341_BLUE    0x001F  - 31
//ILI9341_RED     0xF800  - 248
//ILI9341_GREEN   0x07E0  - 126
//ILI9341_CYAN    0x07FF
//ILI9341_MAGENTA 0xF81F
//ILI9341_YELLOW  0xFFE0
//ILI9341_WHITE   0xFFFF  - 65535




#define tbBLK     ILI9341_BLACK
#define tbGRY     0x07BEF
#define tbBL      ILI9341_BLUE
#define tbRD      ILI9341_RED
#define tbMedRD   0x7800
#define tbGRN     ILI9341_GREEN
#define tbMedGRN  0x03E0
#define tbCY      ILI9341_CYAN
#define tbMAG     ILI9341_MAGENTA
#define tbYLW     ILI9341_YELLOW
#define tbORG     0xF920
#define tbWHT     ILI9341_WHITE

#define FONT2_MAX_CHAR 10

typedef enum fontSize {
  SZ_0,
  SZ_1,
  SZ_2,
  SZ_3,
  SZ_4,
  SZ_5,
  SZ_6,
  SZ_7,
  SZ_8,
  SZ_9,
  SZ_10,
  SZ_11,
  SZ_12,
  SZ_13,
  SZ_14,
  SZ_15
}sizeType;

typedef enum tboStyleEnum {
  STYLE_DEFAULT,
  STYLE_BOUNDED_BOX,
  STYLE_INVERSE,
  STYLE_CUSTOM
}styleType;

enum tboPriorityEnum {
  PRI_0,
  PRI_1,
  PRI_2,
  PRI_3,
  PRI_4,
  PRI_5,
  PRI_6,
  PRI_7
};


class textBoxObj {
  public:
    ILI9341_t3* tboTFT;
    ioChannel* tboIOChanObj;
    tbParam* tboParamObj;
    String* tboStrPtr;
    String tboPrefix;
    String tboStringCore;
    String tboSuffix;
    String tboString;
    String tboStringShadow;
    String tboErrStr;
    bool tboForceUpdate;

    int16_t tboDx;
    int16_t tboDy;
    int16_t tboX;
    int16_t tboY;
    int16_t tboH;
    int16_t tboW;

    unsigned int tboEnable;
    unsigned int tboStyle;
    unsigned int tboSize;
    unsigned int tboFontClr;
    unsigned int tboBGClr;
    unsigned int tboBoxClr;
    unsigned int tboScreenClr;

    unsigned int tboPriority;
    unsigned int tboInputMode;
    unsigned char tboStale;

    //---Static String textbox
    textBoxObj(ILI9341_t3* tft, String nStr, int16_t x, int16_t y, sizeType size,
               styleType dispType, unsigned int fontClr, unsigned int bgClr);

    //---String Referance textbox
    textBoxObj(ILI9341_t3* tft, String *nStr, int16_t x, int16_t y, sizeType size,
               styleType dispType, unsigned int fontClr, unsigned int bgClr);

    //---tbParam textbox with style param
    textBoxObj(ILI9341_t3* tft, tbParam *paramObj, int16_t x, int16_t y, sizeType size,
              styleType dispType, unsigned int fontClr, unsigned int bgClr);
              
    void tboInit();

    void tboCalcPadding();
    void tboDrawBorder();
    void tboDrawContents();
    void tboEraseTB();
    void tboInitDef();
    void tboGetString();
    void tboMove(int16_t nX, int16_t nY);
    void tboRedraw();
    void tboRedraw(String nVal);
    void tboResize();
    void tboSetString(String nPrf, String nStr, String nSuf);
    void tboSetString(String nStr);
    void tboSetString(int nInt);
    void tboSetString(float nFlt);
    void tboSetStyle();
    void tboUpdate();

    int16_t tboTextX;
    int16_t tboTextY;
  private:
    int16_t tboFillX;
    int16_t tboFillY;
    int16_t tboFillH;
    int16_t tboFillW;
    unsigned int tboCharCount;
    unsigned int tboCharCountShadow;
    unsigned int tboCharCountMax;
    unsigned int tboCharCountMin;
    int16_t tboFixedW;
    int16_t tboFixedH;
    int16_t tboHPad;
    int16_t tboWPad;
    int16_t tboCharW;

};

#endif /* TEXTBOX_H_ */
