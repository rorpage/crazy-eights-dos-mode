/////////////////////////////////////////////////////////////
// Crt.H
// The header file for the big library
//
// Written by Samuel Song
// ©1998 Samuel Song. All rights reserved.
//
// 1/6/99 Authorization given to Lakota East High School
/////////////////////////////////////////////////////////////

#ifndef CRT_H__
#define CRT_H__

#include <windows.h>

// color constants (PASCAL style)
enum COLOR { BLACK, BLUE, GREEN, CYAN, RED, MAGENTA, BROWN,
 						 LIGHTGRAY, DARKGRAY, LIGHTBLUE, LIGHTGREEN,
						 LIGHTCYAN, LIGHTRED, LIGHTMAGENTA, YELLOW, WHITE };

//Prototypes
extern void ClearScreen(void);
extern void SetTextColor(WORD textColor);
extern void SetTextBkColor(WORD textBkColor);
extern int  GetTextColor(void);
extern int  GetTextBkColor(void);
extern void GotoXY(int X, int Y);
extern int  WhereX(void);
extern int  WhereY(void);
extern void SetTitle(PCHAR szTitle);
extern int  GetMaxX(void);
extern int  GetMaxY(void);
extern BOOL KeyPressed(void);
extern void Pause(unsigned long WaitTime);
extern CHAR ReadKey(void);
extern void SimpleConsole(bool);
extern void CursorVisible(bool);

#endif // CRT_H__