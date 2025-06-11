/*
 * textBox.cpp
 *
 *  Created on: Dec 12, 2014
 *      Author: odellw
 */

#include <textBox.h>

int16_t hPadAry[] = {
    0,           /* Size 0: Placeholder only */
    S1_TB_H_PAD, /* Size 1 */
    S2_TB_H_PAD, /* Size 2 */
    S3_TB_H_PAD, /* Size 3 */
    S4_TB_H_PAD, /* Size 4 */
    S5_TB_H_PAD, /* Size 5 */
    S6_TB_H_PAD, /* Size 6 */
    S7_TB_H_PAD  /* Size 7 */

};

int16_t wPadAry[] = {
    0,           /* Size 0: Placeholder only */
    S1_TB_W_PAD, /* Size 1 */
    S2_TB_W_PAD, /* Size 2 */
    S3_TB_W_PAD, /* Size 3 */
    S4_TB_W_PAD, /* Size 4 */
    S5_TB_W_PAD, /* Size 5 */
    S6_TB_W_PAD, /* Size 6 */
    S7_TB_W_PAD  /* Size 7 */

};

int16_t boxHAry[] = {
    0,       /* Size 0: Placeholder only */
    S1_TB_H, /* Size 1 */
    S2_TB_H, /* Size 2 */
    S3_TB_H, /* Size 3 */
    S4_TB_H, /* Size 4 */
    S5_TB_H, /* Size 5 */
    S6_TB_H, /* Size 6 */
    S7_TB_H, /* Size 7 */
};

int16_t boxWAry[] = {
    0,       /* Size 0: Placeholder only */
    S1_TB_W, /* Size 1 */
    S2_TB_W, /* Size 2 */
    S3_TB_W, /* Size 3 */
    S4_TB_W, /* Size 4 */
    S5_TB_W, /* Size 5 */
    S6_TB_W, /* Size 6 */
    S7_TB_W  /* Size 7 */

};

int16_t charWAry[] = {
    0,         /* Size 0: Placeholder only */
    FONT_S1_W, /* Size 1 */
    FONT_S2_W, /* Size 2 */
    FONT_S3_W, /* Size 3 */
    FONT_S4_W, /* Size 4 */
    FONT_S5_W, /* Size 5 */
    FONT_S6_W, /* Size 6 */
    FONT_S7_W  /* Size 7 */

};

//-------------------------------------------------------------------------------------------------
//
//   Initializes class instance member data to default values
//
//-------------------------------------------------------------------------------------------------
void textBoxObj::tboInitDef()
{
  tboTFT = NULL;
  tboParamObj = NULL;
  tboIOChanObj = NULL;
  tboStrPtr = NULL;

  tboX = 0;
  tboY = 0;
  tboDx = 0;
  tboDy = 0;
  tboW = 0;
  tboH = 0;

  tboSize = SZ_2;

  tboStyle = STYLE_DEFAULT;

  tboEnable = 1;
  tboPriority = PRI_3;

  tboFontClr = 0;
  tboBGClr = 0;
  tboBoxClr = 0;
  tboScreenClr = 0;

  tboPrefix = "";
  tboStringCore = "";
  tboSuffix = "";
  tboString = "";
  tboStringShadow = tboString;
  tboErrStr = "None";

  //---Get the size specific values---
  tboHPad = hPadAry[tboSize];
  tboWPad = wPadAry[tboSize];
  tboH = boxHAry[tboSize];
  tboW = boxWAry[tboSize];
  tboCharW = charWAry[tboSize];
  tboCharCount = 0;
  tboCharCountMax = 0;
  tboCharCountShadow = 0;
  tboStale = 1;
  tboForceUpdate = false;
}

//-------------------------------------------------------------------------------------------------
textBoxObj::textBoxObj(ILI9341_t3 *tft, String *nStrPrt, int16_t x, int16_t y, sizeType size,
                       styleType dispType, unsigned int fontClr, unsigned int bgClr)
{

  // tft->println("a---01");
  tboInitDef();
  tboTFT = tft;
  tboX = x;
  tboY = y;
  tboTFT->setCursor(tboX, tboY);
  // tft->println("a---02");
  tboSize = size;

  tboFontClr = fontClr;
  tboBGClr = bgClr;
  // tft->println("a---03");

  tboStrPtr = nStrPrt;
  tboString = *nStrPrt;
  // tft->println("a00---tboString:" + tboString);
  // tft->println("a---tboStrPtr:"+ *tboStrPtr);
  tboGetString();
  // tft->println("a01---tboString:"+ tboString);

  tboSetStyle();
  // tft->println("a---06");

  //---Get the size specific values---
  tboCalcPadding();
  // tft->println("a---07");
  // tboRedraw();
  // tft->println("a---08");
}


//-------------------------------------------------------------------------------------------------
textBoxObj::textBoxObj(ILI9341_t3 *tft, tbParam *paramObj, int16_t x, int16_t y, sizeType size,
                       styleType dispType, unsigned int fontClr, unsigned int bgClr) {

  tboInitDef();
  tboParamObj = paramObj;
  tboTFT = tft;
  tboX = x;
  tboY = y;
  tboTFT->setCursor(tboX, tboY);
  tboSize = size;
  tboStyle = dispType;
  tboFontClr = fontClr;
  tboBGClr = bgClr;

  tboGetString();

  tboCalcPadding();

  tboRedraw();
}

//-------------------------------------------------------------------------------------------------
void textBoxObj::tboInit() {
  tboGetString();
  tboCalcPadding();
  tboRedraw();
}

//-------------------------------------------------------------------------------------------------
void textBoxObj::tboCalcPadding() {
  //---Get the size specific values---
  tboHPad = hPadAry[tboSize];
  tboWPad = wPadAry[tboSize];
  tboH = boxHAry[tboSize];
  tboW = boxWAry[tboSize];
  tboCharW = charWAry[tboSize];
}

//-------------------------------------------------------------------------------------------------
void textBoxObj::tboDrawBorder() {
  tboTFT->drawRect(tboX, tboY, tboW, tboH, tboBGClr);
}

//-------------------------------------------------------------------------------------------------
void textBoxObj::tboDrawContents() {
  tboTFT->fillRect(tboFillX, tboFillY, tboFillW, tboFillH, ILI9341_PINK);

  tboTFT->setCursor(tboTextX, tboTextY);
  tboTFT->print(tboString);
  // tboErrStr = "draw";
}

//-------------------------------------------------------------------------------------------------
void textBoxObj::tboEraseTB() {
  if (tboDx != 0)
  {
    tboTFT->fillRect(tboX - 5, tboY, tboW + 10, tboH, tboBGClr);
    tboErrStr = "fill0";
  }
  else
  {
    tboTFT->fillRect(tboX, tboY, tboW, tboH, ILI9341_CYAN);
    tboErrStr = "fill1";
  }
}

//-------------------------------------------------------------------------------------------------
void textBoxObj::tboGetString() {
  tboStringShadow = tboString;
  tboCharCountShadow = tboCharCount;

  if (tboParamObj != NULL) {
    tboStringCore = tboParamObj->tbpGetStr();
    tboErrStr = "PramObj";
  }
  else if (tboIOChanObj != NULL) {
    tboStringCore = String(tboIOChanObj->ioEngVal);
    tboErrStr = "IO Chan";
  }
  else if (tboStrPtr != NULL) {
    tboStringCore = *tboStrPtr;
    // tboErrStr = "String*";
  }
  else {
    tboStringCore = "ERROR";
    tboErrStr = "Error";
  }

  tboString = tboPrefix + tboStringCore + tboSuffix;
}

//-------------------------------------------------------------------------------------------------
void textBoxObj::tboMove(int16_t nX, int16_t nY)
{
  static int xShadow = tboX;
  static int yShadow = tboY;
  tboX = nX;
  tboY = nY;

  tboDx = tboX - xShadow;
  tboDy = tboY - yShadow;
  tboRedraw();
}

//-------------------------------------------------------------------------------------------------
void textBoxObj::tboRedraw()
{
  // //tboTFT->println("b---01");
  tboUpdate();

  // //tboTFT->println("b---02");
  if (!tboStale)
  {
    //tboTFT->println("b---03");
    tboEraseTB();
    tboResize();
    //tboTFT->println("b---04");

    if (tboEnable == 1)
    {
      //tboTFT->println("b---05");
      tboTFT->setTextSize(tboSize);
      tboTFT->setTextColor(tboFontClr);
      //tboTFT->println("b---06");

      // tboDrawBorder();
      tboDrawContents();
      //tboTFT->println("b---07");
    }
  }

  //tboTFT->println("b----08");
}

//-------------------------------------------------------------------------------------------------
void textBoxObj::tboRedraw(String nVal)
{

  // //tboTFT->println("b---01");
  tboStringCore = nVal;
  tboRedraw();
}

//-------------------------------------------------------------------------------------------------
void textBoxObj::tboResize()
{

  tboW = tboWPad + (tboCharW * tboCharCount) + tboWPad;

  tboTextX = tboX + tboWPad;
  tboTextY = tboY + tboHPad;

  tboFillX = tboX + FILL_LOC_OFFSET;
  tboFillY = tboY + FILL_LOC_OFFSET;
  tboFillH = tboH - FILL_SIZE_OFFSET;
  tboFillW = tboW - FILL_SIZE_OFFSET;
}

//-------------------------------------------------------------------------------------------------
void textBoxObj::tboSetString(String nPrf, String nStr, String nSuf)
{

  tboPrefix = nPrf;
  tboStringCore = nStr;
  tboSuffix = nSuf;

  tboRedraw();
}

//-------------------------------------------------------------------------------------------------
void textBoxObj::tboSetString(String nStr)
{
  tboStringCore = nStr;

  tboRedraw();
}

//-------------------------------------------------------------------------------------------------
void textBoxObj::tboSetString(int nInt)
{
  tboStringCore = String(nInt);

  tboRedraw();
}

//-------------------------------------------------------------------------------------------------
void textBoxObj::tboSetString(float nFlt)
{
  tboStringCore = String(nFlt);

  tboRedraw();
}

//-------------------------------------------------------------------------------------------------
void textBoxObj::tboSetStyle()
{
  unsigned int tempColor = 0;

  switch (tboStyle)
  {
  default:
  case STYLE_DEFAULT:
    tboBoxClr = tboScreenClr;
    tboScreenClr = tboBGClr;
    break;

  case STYLE_BOUNDED_BOX:
    tboBGClr = tboScreenClr;
    tboBoxClr = tboFontClr;
    break;

  case STYLE_INVERSE:
    tempColor = tboFontClr;
    tboFontClr = tboScreenClr;
    tboBGClr = tempColor;
    tboBoxClr = tempColor;
    tboScreenClr = tbBLK;
    break;

  case STYLE_CUSTOM:
    break;
  }
}

//-------------------------------------------------------------------------------------------------
void textBoxObj::tboUpdate()
{
  tboGetString();

  if (tboString != tboStringShadow) {
    tboCharCount = tboString.length();
    tboStale = 0;
  }
  else
    tboStale = 1;
}
