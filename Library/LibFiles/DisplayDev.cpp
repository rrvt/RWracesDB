// Display Device Data


#include "stdafx.h"
#include "DisplayDev.h"


//#define DebugDD

#ifdef DebugDD
static String dbgLastLine[10];
static void   saveDbgLine(String& line);
static void   saveDbgWrap(Wrap& w);
static void   rippleDbgLine();
#endif


void DisplayDev::startDev()
             {note = notePadLp.start(); lastPageNo = 0; lastLeftMargin = 0;  endDoc = debugging = false;}


// Output to Device (Display or Printer)

void DisplayDev::operator() () {
bool endLoop = false;

  for ( ; note && !endLoop; note = notePadLp.nextNode()) {

    if (note->beginLine)    {dev << dBeginLine;                 if (dev.doEndPageChk()) break;}
    if (note->leftMargin != lastLeftMargin)
                            {dev << dSetLMargin(note->leftMargin); lastLeftMargin = note->leftMargin;}
    if (note->clrTabs)       dev << dClrTabs;
    if (note->tabValue)      dev << dSetTab(note->tabValue);
    if (note->rTabValue)     dev << dSetRTab(note->rTabValue);

    if (note->fSize)         {dev << dFSize(note->fSize);       if (dev.doEndPageChk()) break;}
    if (note->prevFont)      {dev << dPrevFont;                 if (dev.doEndPageChk()) break;}
    if (note->bold)          {dev << dBoldFont;                 if (dev.doEndPageChk()) break;}
    if (note->italic)        {dev << dItalicFont;               if (dev.doEndPageChk()) break;}
    if (note->underline)     {dev << dUnderLineFont;            if (dev.doEndPageChk()) break;}
    if (note->strikeOut)     {dev << dStrikeOutFont;            if (dev.doEndPageChk()) break;}

    if (note->tab == true)   {dev << dTab;                      if (dev.doEndPageChk()) break;}
    if (note->center)        {dev << dCenter;                   if (dev.doEndPageChk()) break;}
    if (note->right)         {dev << dRight;                    if (dev.doEndPageChk()) break;}

    if (note->editBoxX >= 0) {dev << dEditBox(note->editBoxX);  if (dev.doEndPageChk()) break;}

#ifdef DebugDD
saveDbgLine(note->line);
saveDbgWrap(note->wrap);
#endif
                              dev << note->line;                if (dev.doEndPageChk()) break;

                              dev << note->wrap;                if (dev.doEndPageChk()) break;


    if (note->endLine)       {dev << dEndLine;                  if (dev.doEndPageChk()) break;}

    if (note->crlf)          {dev << dCrlf;                     if (dev.doEndPageChk()) break;}

    if (note->endPage)       {dev << dEndPage;                  dev.atEndPageCond(); endLoop = true;}

    if (note->debug)         debugging = true;
    }

  endDoc = note == 0;
  }




#ifdef DebugDD
void saveDbgWrap(Wrap& w) {
String* s;

  if (w.isEmpty()) return;

  for (s = w.startLoop(); s; s = w.nextLine()) saveDbgLine(*s);
  }


void saveDbgLine(String& line) {

  if (line.isEmpty()) return;

  rippleDbgLine();

  dbgLastLine[noElements(dbgLastLine)-1] = line;
  }



void rippleDbgLine() {
int n = noElements(dbgLastLine);
int i;

  for (i = 1; i < n; i++) dbgLastLine[i-1] = dbgLastLine[i];
  }
#endif