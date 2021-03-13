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
#include <ioChan.h>
#include <String.h>
#include <tbParam.h>

#define FILL_LOC_OFFSET 1
#define FILL_SIZE_OFFSET 2

//---Font is really 5x7, but we pad 1 pxl to both H and W to accommodate char
//---Spacing

//---Size 1 Font---
#define FONT_S1_H   8
#define FONT_S1_W   6

#define S1_TB_H     10
#define S1_TB_W_PAD 3
#define S1_TB_H_PAD 1

//---Size 2 Font---
#define FONT_S2_H   16
#define FONT_S2_W   12

#define S2_TB_H     20
#define S2_TB_W_PAD 5
#define S2_TB_H_PAD 3

//---Size 3 Font---
#define FONT_S3_H   32
#define FONT_S3_W   18

#define S3_TB_H     27
#define S3_TB_W_PAD 5
#define S3_TB_H_PAD 3

//---Size 4 Font---
#define FONT_S4_H   FONT_S3_H * 2
#define FONT_S4_W   FONT_S3_W * 2

#define S4_TB_H     20
#define S4_TB_W_PAD 5
#define S4_TB_H_PAD 3

//---Size 5 Font---
#define FONT_S5_H   FONT_S4_H * 2
#define FONT_S5_W   FONT_S4_W * 2

#define S5_TB_H     20
#define S5_TB_W_PAD 5
#define S5_TB_H_PAD 3

//---Size 6 Font---
#define FONT_S6_H   FONT_S4_H * 2
#define FONT_S6_W   FONT_S4_W * 2

#define S6_TB_H     20
#define S6_TB_W_PAD 5
#define S5_TB_H_PAD 3

//---Size 7 Font---
#define FONT_S7_H   FONT_S4_H * 2
#define FONT_S7_W   FONT_S4_W * 2

#define S7_TB_H     20
#define S7_TB_W_PAD 5
#define S7_TB_H_PAD 3

//---Size 8 Font---
#define FONT_S8_H   FONT_S4_H * 2
#define FONT_S8_W   FONT_S4_W * 2

#define S8_TB_H     20
#define S8_TB_W_PAD 5
#define S8_TB_H_PAD 3

//---Size 10 Font---
#define FONT_S9_H   FONT_S4_H * 2
#define FONT_S9_W   FONT_S4_W * 2

#define S9_TB_H     20
#define S9_TB_W_PAD 5
#define S9_TB_H_PAD 3

//---Size 10 Font---
#define FONT_S10_H   FONT_S4_H * 2
#define FONT_S10_W   FONT_S4_W * 2

#define S10_TB_H      20
#define S10_TB_W_PAD  5
#define S10_TB_H_PAD  3

//---Size 11 Font---
#define FONT_S11_H   8
#define FONT_S11_W   6

#define S11_TB_H      20
#define S11_TB_W_PAD  5
#define S11_TB_H_PAD  3

//---Size 12 Font---
#define FONT_S12_H   16
#define FONT_S12_W   12

#define S12_TB_H      20
#define S12_TB_W_PAD  5
#define S12_TB_H_PAD  3

//---Size 13 Font---
#define FONT_S13_H   FONT_S2_H * 2
#define FONT_S13_W   FONT_S2_W * 2

#define S13_TB_H      20
#define S13_TB_W_PAD  5
#define S13_TB_H_PAD  3

//---Size 14 Font---
#define FONT_S14_H   FONT_S3_H * 2
#define FONT_S14_W   FONT_S3_W * 2

#define S14_TB_H      20
#define S14_TB_W_PAD  5
#define S14_TB_H_PAD  3

//---Size 15 Font---
#define FONT_S15_H   105
#define FONT_S15_W   75

#define S15_TB_H      120
#define S15_TB_W_PAD  10
#define S15_TB_H_PAD  7

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
    int tboDx;
    int tboDy;
    unsigned int tboX;
    unsigned int tboY;
    unsigned int tboH;
    unsigned int tboW;

    unsigned int tboStyle;
    unsigned int tboSize;
    unsigned int tboFontClr;
    unsigned int tboBGClr;
    unsigned int tboBoxClr;
    unsigned int tboScreenClr;

    String tboString;
    String tboStringShadow;
    unsigned int tboPriority;
    unsigned char tboStale;

    textBoxObj(ILI9341_t3* tft, String str, unsigned int x, unsigned int y, sizeType size,
               unsigned int fontClr, unsigned int boxClr, unsigned int bgClr, unsigned int defClr);

    textBoxObj(ILI9341_t3* tft, tbParam *paramObj, unsigned int x, unsigned int y, sizeType size,
               unsigned int fontClr, unsigned int boxClr, unsigned int bgClr, unsigned int defClr);

    textBoxObj(ILI9341_t3* tft, ioChannel *ioChanObj, unsigned int x, unsigned int y, sizeType size,
               unsigned int fontClr, unsigned int boxClr, unsigned int bgClr, unsigned int defClr);

    textBoxObj(ILI9341_t3* tft, String str, unsigned int x, unsigned int y, sizeType size,
               styleType dispType, unsigned int fontClr, unsigned int bgClr);

    textBoxObj(ILI9341_t3* tft, tbParam *paramObj, unsigned int x, unsigned int y, sizeType size,
              styleType dispType, unsigned int fontClr, unsigned int bgClr);

    textBoxObj(ILI9341_t3* tft, ioChannel *ioChanObj, unsigned int x, unsigned int y, sizeType size,
               styleType dispType, unsigned int fontClr, unsigned int bgClr);

    void tboSetStyle();
    void tboEraseTB();
    void tboDrawBorder();
    void tboDrawContents();
    void tboRedraw();
    void tboResize();
    void tboUpdate();
    void tboSetString(String nStr);

  private:
    unsigned int tboFillX;
    unsigned int tboFillY;
    unsigned int tboFillH;
    unsigned int tboFillW;
    unsigned int tboCharCount;
    unsigned int tboCharCountShadow;
    unsigned int tboCharCountMax;
    unsigned int tboCharCountMin;
    unsigned int tboFixedW;
    unsigned int tboFixedH;
    unsigned int tboEnable;
    unsigned int tboHPad;
    unsigned int tboWPad;
    unsigned int tboTextX;
    unsigned int tboTextY;
    unsigned int tboCharW;

};

#endif /* TEXTBOX_H_ */
