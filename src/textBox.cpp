/*
 * textBox.cpp
 *
 *  Created on: Dec 12, 2014
 *      Author: odellw
 */

#include <textBox.h>

unsigned int hPadAry[] = {
    0,                  /* Size 0: Placeholder only */
    0,                  /* Size 1 */
    S2_TB_H_PAD,        /* Size 2 */
    S3_TB_H_PAD,        /* Size 3 */
    0,                  /* Size 4 */
    0,                  /* Size 5 */
    0,                  /* Size 6 */
    0,                  /* Size 7 */
    0,                  /* Size 8 */
    0,                  /* Size 9 */
    0,                  /* Size 10 */
    0,                  /* Size 11 */
    0,                  /* Size 12 */
    0,                  /* Size 13 */
    0,                  /* Size 14 */
    S15_TB_H_PAD,  /* Size 15 */
};

unsigned int wPadAry[] = {
    0,                  /* Size 0: Placeholder only */
    0,                  /* Size 1 */
    S2_TB_W_PAD,        /* Size 2 */
    S3_TB_W_PAD,        /* Size 3 */
    0,                  /* Size 4 */
    0,                  /* Size 5 */
    0,                  /* Size 6 */
    0,                  /* Size 7 */
    0,                  /* Size 8 */
    0,                  /* Size 9 */
    0,                  /* Size 10 */
    0,                  /* Size 11 */
    0,                  /* Size 12 */
    0,                  /* Size 13 */
    0,                  /* Size 14 */
    S15_TB_W_PAD,  /* Size 15 */
};


unsigned int boxHAry[] = {
    0,                  /* Size 0: Placeholder only */
    0,                  /* Size 1 */
    S2_TB_H,            /* Size 2 */
    S3_TB_H,            /* Size 3 */
    0,                  /* Size 4 */
    0,                  /* Size 5 */
    0,                  /* Size 6 */
    0,                  /* Size 7 */
    0,                  /* Size 8 */
    0,                  /* Size 9 */
    0,                  /* Size 10 */
    0,                  /* Size 11 */
    0,                  /* Size 12 */
    0,                  /* Size 13 */
    0,                  /* Size 14 */
    S15_TB_H,      /* Size 15 */
};

unsigned int charWAry[] = {
    0,                  /* Size 0: Placeholder only */
    FONT_S1_W,          /* Size 1 */
    FONT_S2_W,          /* Size 2 */
    FONT_S3_W,          /* Size 3 */
    FONT_S4_W,          /* Size 4 */
    FONT_S5_W,          /* Size 5 */
    FONT_S6_W,          /* Size 6 */
    FONT_S7_W,          /* Size 7 */
    FONT_S8_W,          /* Size 8 */
    FONT_S9_W,          /* Size 9 */
    FONT_S10_W,         /* Size 10 */
    FONT_S11_W,         /* Size 11 */
    FONT_S12_W,         /* Size 12 */
    FONT_S13_W,         /* Size 13 */
    FONT_S14_W,         /* Size 14 */
    FONT_S15_W,         /* Size 15 */
};

//-------------------------------------------------------------------------------------------------
//
//   Initializes class instance member data to default values
//
//-------------------------------------------------------------------------------------------------
void textBoxObj::tboInitDef() {
  tboTFT = NULL;
  tboParamObj = NULL;
  tboIOChanObj = NULL;
  tboStrPtr = NULL;

  tboX = 0;
  tboY = 0;
  tboDx = 0;
  tboDy = 0;

  tboSize = SZ_2;

  tboStyle = STYLE_DEFAULT;

  tboEnable = 1;
  tboPriority = PRI_3;

  tboFontClr = 0;
  tboBGClr = 0;
  tboBoxClr = 0;
  tboScreenClr = 0;

  tboPrefix = "";
  tboStringCore = "StringCore";
  tboSuffix = "";
  tboStringShadow = tboString;

  //---Get the size specific values---
  tboHPad = hPadAry[tboSize];
  tboWPad = wPadAry[tboSize];
  tboH = boxHAry[tboSize];
  tboCharW = charWAry[tboSize];
  tboCharCount = 0;
  tboCharCountMax = 0;
  tboCharCountShadow = 0;
  tboStale = 1;
}


//-------------------------------------------------------------------------------------------------
textBoxObj::textBoxObj(ILI9341_t3* tft, String *nStrPrt, unsigned int x, unsigned int y, sizeType size,
                       styleType dispType, unsigned int fontClr, unsigned int bgClr) {

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
  tboRedraw();
  // tft->println("a---08");


}


/*-----------------------------------------------------------------------------
 *
 *---ioChan textbox
 *
 *---------------------------------------------------------------------------*/
textBoxObj::textBoxObj(ILI9341_t3* tft, ioChannel *ioChanObj, unsigned int x, unsigned int y, sizeType size,
                       styleType dispType, unsigned int fontClr, unsigned int bgClr) {

  tboInitDef();
  tboIOChanObj = ioChanObj;

  tboTFT = tft;
  tboX = x;
  tboY = y;
  tboTFT->setCursor(tboX, tboY);

  tboFontClr = fontClr;
  tboBGClr = bgClr;

  tboGetString();

  tboCalcPadding();
  tboRedraw();
}

//-------------------------------------------------------------------------------------------------
textBoxObj::textBoxObj(ILI9341_t3* tft, tbParam *paramObj, unsigned int x, unsigned int y, sizeType size,
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
void textBoxObj::tboCalcPadding() {
  //---Get the size specific values---
  tboHPad = hPadAry[tboSize];
  tboWPad = wPadAry[tboSize];
  tboH = boxHAry[tboSize];
  tboCharW = charWAry[tboSize];


}





//-------------------------------------------------------------------------------------------------
void textBoxObj::tboDrawBorder() {
  tboTFT->drawRect(tboX, tboY, tboW,  tboH, tboBoxClr);
}

//-------------------------------------------------------------------------------------------------
void textBoxObj::tboDrawContents() {
  tboTFT->fillRect(tboFillX, tboFillY, tboFillW , tboFillH, tboBGClr);

  tboTFT->setCursor(tboTextX, tboTextY);
  tboTFT->print(tboString);
}

//-------------------------------------------------------------------------------------------------
void textBoxObj::tboEraseTB() {
  if(tboDx != 0)
    tboTFT->fillRect(tboX - 5, tboY, tboW + 10 , tboH, tboBGClr);
  else
    tboTFT->fillRect(tboX, tboY, tboW , tboH, tboBGClr);
}

//-------------------------------------------------------------------------------------------------
void textBoxObj::tboGetString() {
  tboStringShadow = tboString;

  if(tboParamObj != NULL)
    tboStringCore = tboParamObj->tbpGetStr();
  else if(tboIOChanObj != NULL)
    tboStringCore =  String(tboIOChanObj->ioEngVal);

  tboString = tboPrefix + tboStringCore + tboSuffix;
}

//-------------------------------------------------------------------------------------------------
void textBoxObj::tboMove(int nX, int nY) {
  static int xShadow = tboX;
  static int yShadow = tboY;
  tboX = nX;
  tboY = nY;

  tboDx = tboX - xShadow;
  tboDy = tboY - yShadow;
  tboRedraw();
}


//-------------------------------------------------------------------------------------------------
void textBoxObj::tboRedraw() {
  // //tboTFT->println("b---01");
  tboUpdate();

  // //tboTFT->println("b---02");
  if(!tboStale) {
    //tboTFT->println("b---03");
    tboEraseTB();
    tboResize();
    //tboTFT->println("b---04");

    if(tboEnable == 1) {
      //tboTFT->println("b---05");
      tboTFT->setTextSize(tboSize);
      tboTFT->setTextColor(tboFontClr);
      //tboTFT->println("b---06");

      tboDrawBorder();
      tboDrawContents();
      //tboTFT->println("b---07");
    }
  }


  //tboTFT->println("b----08");
}

//-------------------------------------------------------------------------------------------------
void textBoxObj::tboRedraw(String nVal) {

  // //tboTFT->println("b---01");
  tboStringCore = nVal;
  tboUpdate();

  // //tboTFT->println("b---02");
  if(!tboStale) {
    //tboTFT->println("b---03");
    tboEraseTB();
    tboResize();
    //tboTFT->println("b---04");

    if(tboEnable == 1) {
      //tboTFT->println("b---05");
      tboTFT->setTextSize(tboSize);
      tboTFT->setTextColor(tboFontClr);
      //tboTFT->println("b---06");

      tboDrawBorder();
      tboDrawContents();
      //tboTFT->println("b---07");
    }
  }
}

//-------------------------------------------------------------------------------------------------
void textBoxObj::tboResize() {

  tboW = tboWPad + tboCharW * tboCharCount + tboWPad;

  tboTextX = tboX + tboWPad;
  tboTextY = tboY + tboHPad;

  tboFillX = tboX + FILL_LOC_OFFSET;
  tboFillY = tboY + FILL_LOC_OFFSET;
  tboFillH = tboH - FILL_SIZE_OFFSET;
  tboFillW = tboW - FILL_SIZE_OFFSET;

}

//-------------------------------------------------------------------------------------------------
void textBoxObj::tboSetString(String nPrf, String nStr, String nSuf) {
  tboStringShadow = tboString;

  tboPrefix = nPrf;
  tboStringCore = nStr;
  tboSuffix = nSuf;

  tboString = tboPrefix + tboStringCore + tboSuffix;

  tboRedraw();

}

//-------------------------------------------------------------------------------------------------
void textBoxObj::tboSetString(String nStr)
{
  tboStringCore = nStr;

  tboRedraw();
}

//-------------------------------------------------------------------------------------------------
void textBoxObj::tboSetString(int nInt) {
  tboStringCore = String(nInt);

  tboRedraw();
}

//-------------------------------------------------------------------------------------------------
void textBoxObj::tboSetString(float nFlt) {
  tboStringCore = String(nFlt);

  tboRedraw();
}

//-------------------------------------------------------------------------------------------------
void textBoxObj::tboSetStyle() {
  unsigned int tempColor = 0;

  switch(tboStyle) {
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
void textBoxObj::tboUpdate() {
  // tboTFT->println("c---01");

  //---Save the char count---
  tboCharCountShadow = tboCharCount;
  tboStringShadow = tboString;
  tboGetString();

  if(tboString != tboStringShadow) {
    tboCharCount = tboString.length();
    tboStale = 0;
  }
  else
    tboStale = 1;
}

