/*
 * textBox.cpp
 *
 *  Created on: Dec 12, 2014
 *      Author: odellw
 */

#include <iostream.h>
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



/*-----------------------------------------------------------------------------
 *
 *
 *
 *---------------------------------------------------------------------------*/
textBoxObj::textBoxObj(ILI9341_t3* tft, String str, unsigned int x, unsigned int y, sizeType size,
                       unsigned int fontClr, unsigned int boxClr, unsigned int bgClr, unsigned int defClr) {
  tboTFT = tft;
  tboParamObj = NULL;
  tboIOChanObj = NULL;
  tboX = x;
  tboY = y;
  tboDx = 0;
  tboDy = 0;

  tboSize = size;

  tboStyle = STYLE_CUSTOM;

  tboEnable = 1;
  tboPriority = PRI_3;

  tboFontClr = fontClr;
  tboBGClr = bgClr;
  tboBoxClr = boxClr;
  tboScreenClr = defClr;

  tboString = str;
  tboStringShadow = str;

  //---Get the size specific values---
  tboHPad = hPadAry[tboSize];
  tboWPad = wPadAry[tboSize];
  tboH = boxHAry[tboSize];
  tboCharW = charWAry[tboSize];
  tboCharCountMax = tboCharCount;
  tboCharCountShadow = tboCharCount;
  tboStale = 1;

  tboRedraw();

};

/*-----------------------------------------------------------------------------
 *
 *
 *
 *---------------------------------------------------------------------------*/
textBoxObj::textBoxObj(ILI9341_t3* tft, tbParam *paramObj, unsigned int x, unsigned int y, sizeType size,
    unsigned int fontClr, unsigned int boxClr, unsigned int bgClr, unsigned int defClr) {


  tboParamObj = paramObj;
  tboTFT = tft;
  tboDx = 0;
  tboDy = 0;
  tboX = x;
  tboY = y;

  tboSize = size;

  tboEnable = 1;
  tboPriority = PRI_3;
  tboStyle = STYLE_CUSTOM;

  tboFontClr = fontClr;
  tboBGClr = bgClr;
  tboBoxClr = boxClr;
  tboScreenClr = defClr;

  if(tboParamObj == NULL)
    tboString = "DefaultString";
  else
    tboString = tboParamObj->tbpGetStr();

  tboStringShadow = tboString;
  //---Get the size specific values---
  tboHPad = hPadAry[tboSize];
  tboWPad = wPadAry[tboSize];
  tboH = boxHAry[tboSize];
  tboCharW = charWAry[tboSize];
  tboCharCountMax = tboCharCount;
  tboCharCountShadow = tboCharCount;
  tboStale = 1;

  tboRedraw();
}

/*-----------------------------------------------------------------------------
 *
 *
 *
 *---------------------------------------------------------------------------*/
textBoxObj::textBoxObj(ILI9341_t3* tft, ioChannel *ioChanObj, unsigned int x, unsigned int y, sizeType size,
    unsigned int fontClr, unsigned int boxClr, unsigned int bgClr, unsigned int defClr) {


  tboParamObj = NULL;
  tboIOChanObj = ioChanObj;

  tboTFT = tft;
  tboDx = 0;
  tboDy = 0;
  tboX = x;
  tboY = y;

  tboSize = size;


  tboEnable = 1;
  tboPriority = PRI_3;

  tboStyle = STYLE_CUSTOM;

  tboFontClr = fontClr;
  tboBGClr = bgClr;
  tboBoxClr = boxClr;
  tboScreenClr = defClr;

  if(tboParamObj != NULL)
    tboString = tboParamObj->tbpGetStr();
  else if(tboIOChanObj != NULL)
    tboString = tboIOChanObj->getDispStr();
  else
    tboString = "Default";

  tboStringShadow = tboString;

  //---Get the size specific values---
  tboHPad = hPadAry[tboSize];
  tboWPad = wPadAry[tboSize];
  tboH = boxHAry[tboSize];
  tboCharW = charWAry[tboSize];
  tboCharCountMax = tboCharCount;
  tboCharCountShadow = tboCharCount;
  tboStale = 1;

  tboRedraw();
}

/*-----------------------------------------------------------------------------
 *
 *
 *
 *---------------------------------------------------------------------------*/
textBoxObj::textBoxObj(ILI9341_t3* tft, String str, unsigned int x, unsigned int y, sizeType size,
    styleType dispType, unsigned int fontClr, unsigned int bgClr) {


  tboParamObj = NULL;
  tboIOChanObj = NULL;

  tboTFT = tft;
  tboDx = 0;
  tboDy = 0;
  tboX = x;
  tboY = y;

  tboSize = size;
  tboString = str;
  tboEnable = 1;
  tboPriority = PRI_3;

  tboStyle = STYLE_CUSTOM;

  tboFontClr = fontClr;
  tboBGClr = bgClr;

  if(tboParamObj != NULL)
    tboString = tboParamObj->tbpGetStr();
  else if(tboIOChanObj != NULL)
    tboString = tboIOChanObj->getDispStr();
  else
    tboString = "Default";

  tboStringShadow = tboString;

  //---Get the size specific values---
  tboHPad = hPadAry[tboSize];
  tboWPad = wPadAry[tboSize];
  tboH = boxHAry[tboSize];
  tboCharW = charWAry[tboSize];
  tboCharCountMax = tboCharCount;
  tboCharCountShadow = tboCharCount;
  tboStale = 1;
  tboRedraw();
}

/*-----------------------------------------------------------------------------
 *
 *
 *
 *---------------------------------------------------------------------------*/
 textBoxObj::textBoxObj(ILI9341_t3* tft, tbParam *paramObj, unsigned int x, unsigned int y, sizeType size,
     styleType dispType, unsigned int fontClr, unsigned int bgClr) {


   tboParamObj = paramObj;
   tboIOChanObj = NULL;

   tboTFT = tft;
   tboDx = 0;
   tboDy = 0;
   tboX = x;
   tboY = y;
   tboEnable = 1;

   tboPriority = PRI_3;
   tboSize = size;

   tboStyle = STYLE_CUSTOM;

   tboFontClr = fontClr;
   tboBGClr = bgClr;

   if(tboParamObj != NULL)
     tboString = tboParamObj->tbpGetStr();
   else if(tboIOChanObj != NULL)
     tboString = tboIOChanObj->getDispStr();
   else
     tboString = "Default";

   tboStringShadow = tboString;

   //---Get the size specific values---
   tboHPad = hPadAry[tboSize];
   tboWPad = wPadAry[tboSize];
   tboH = boxHAry[tboSize];
   tboCharW = charWAry[tboSize];
   tboCharCountMax = tboCharCount;
   tboCharCountShadow = tboCharCount;
   tboStale = 1;

   tboRedraw();
 }
/*-----------------------------------------------------------------------------
 *
 *
 *
 *---------------------------------------------------------------------------*/
 textBoxObj::textBoxObj(ILI9341_t3* tft, ioChannel *ioChanObj, unsigned int x, unsigned int y, sizeType size,
     styleType dispType, unsigned int fontClr, unsigned int bgClr) {


   tboParamObj = NULL;
   tboIOChanObj = ioChanObj;

   tboTFT = tft;
   tboDx = 0;
   tboDy = 0;
   tboX = x;
   tboY = y;

   tboSize = size;
   tboEnable = 1;
   tboPriority = PRI_3;

   tboStyle = STYLE_CUSTOM;

   tboFontClr = fontClr;
   tboBGClr = bgClr;

   tboSetStyle();

   if(tboParamObj != NULL)
     tboString = tboParamObj->tbpGetStr();
   else if(tboIOChanObj != NULL)
     tboString = tboIOChanObj->getDispStr();
   else
     tboString = "Default";

   tboStringShadow = tboString;

   //---Get the size specific values---
   tboHPad = hPadAry[tboSize];
   tboWPad = wPadAry[tboSize];
   tboH = boxHAry[tboSize];
   tboCharW = charWAry[tboSize];
   tboCharCountMax = tboCharCount;
   tboCharCountShadow = tboCharCount;
   tboStale = 1;

   tboRedraw();
 }

/*-----------------------------------------------------------------------------
 *
 *
 *
 *---------------------------------------------------------------------------*/
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

/*-----------------------------------------------------------------------------
 *
 *
 *
 *---------------------------------------------------------------------------*/
void textBoxObj::tboEraseTB() {
  if(tboDx != 0)
    tboTFT->fillRect(tboX - 5, tboY, tboW + 10 , tboH, tboBGClr);
  else
    tboTFT->fillRect(tboX, tboY, tboW , tboH, tboBGClr);
}

/*-----------------------------------------------------------------------------
 *
 *
 *
 *---------------------------------------------------------------------------*/
void textBoxObj::tboDrawBorder() {
  tboTFT->drawRect(tboX, tboY, tboW,  tboH, tboBoxClr);
}

/*-----------------------------------------------------------------------------
 *
 *
 *
 *---------------------------------------------------------------------------*/
void textBoxObj::tboDrawContents() {
  tboTFT->fillRect(tboFillX, tboFillY, tboFillW , tboFillH, tboBGClr);

  tboTFT->setCursor(tboTextX, tboTextY);
  tboTFT->print(tboString);
}

/*-----------------------------------------------------------------------------
 *
 *
 *
 *---------------------------------------------------------------------------*/
void textBoxObj::tboRedraw() {
  tboUpdate();

//  if(!tboStale || tboCharCountShadow != tboCharCount) {
  if(!tboStale) {
//  if(!tboStale || (!staleShadow && tboStale)) {
    tboEraseTB();
    tboResize();

    if(tboEnable == 1) {
      tboTFT->setTextSize(tboSize);
      tboTFT->setTextColor(tboFontClr);

      tboDrawBorder();
      tboDrawContents();
    }
  }
}

/*-----------------------------------------------------------------------------
 *
 *
 *
 *---------------------------------------------------------------------------*/
void textBoxObj::tboResize() {

  tboW = tboWPad + tboCharW * tboCharCount + tboWPad;

  tboTextX = tboX + tboWPad;
  tboTextY = tboY + tboHPad;

  tboFillX = tboX + FILL_LOC_OFFSET;
  tboFillY = tboY + FILL_LOC_OFFSET;
  tboFillH = tboH - FILL_SIZE_OFFSET;
  tboFillW = tboW - FILL_SIZE_OFFSET;

}

/*-----------------------------------------------------------------------------
 *
 *
 *
 *---------------------------------------------------------------------------*/
void textBoxObj::tboUpdate() {
  static int xShadow = tboX;
  static int yShadow = tboY;

  if(tboParamObj != NULL) {
    if(tboParamObj->tbpGetStr() != tboStringShadow) {
      tboString = tboParamObj->tbpGetStr();
      tboCharCount = tboString.length();
      tboStale = 0;
    }
    else
      tboStale = 1;
  }
  else if(tboIOChanObj != NULL) {
    if(tboIOChanObj->getDispStr() != tboStringShadow) {
      tboString = tboIOChanObj->getDispStr();
      tboCharCount = tboString.length();
      tboStale = 0;
    }
    else
      tboStale = 1;

  }
  else {
    if(tboString != tboStringShadow) {
      tboCharCount = tboString.length();
      tboStale = 0;
    }
    else
      tboStale = 1;
  }
  //---Save the char count---
  tboCharCountShadow = tboCharCount;
  tboStringShadow = tboString;

  tboDx = tboX - xShadow;
  tboDy = tboY - yShadow;

  xShadow = tboX;
  yShadow = tboY;
}

/*-----------------------------------------------------------------------------
 *
 *
 *
 *---------------------------------------------------------------------------*/
void textBoxObj::tboSetString(String nStr) {
  tboStringShadow = tboString;

  tboString = nStr;

  tboRedraw();
}
