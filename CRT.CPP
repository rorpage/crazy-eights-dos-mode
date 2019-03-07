//////////////////////////////////////////////////////////////
// Crt.Cpp
// A console library
// 
// Written by Samuel Song
// ©1998 Samuel Song. All rights reserved.
//
// 1/6/99 Authorization given to Lakota East High School
//////////////////////////////////////////////////////////////

#include <windows.h>
#include <stdio.h>
#include <time.h>
#include <iostream.h>

/*
Beta Highlights:
(works only for main console window)
(Programmer''s Notice: Modifying the code can produce UNEXPECTED
						results because of the nature of the
						console window!
*/

// handle to standard output console window
HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

// handle to standard input handle for console window
HANDLE hStdIn  = GetStdHandle(STD_INPUT_HANDLE);

// master print error function
#define PERR(bSuccess, api) {if (!(bSuccess)) perr(__FILE__, __LINE__, \
						 api, GetLastError());}

/************************************************************************
* FUNCTION: perr(PCHAR szFileName, int line, PCHAR szApiName,						*
*				 DWORD dwError)																									*
*																																				*
* PURPOSE: report API errors. Allocate a new console buffer, display		*
* 		   error number and error text, restore previous console buffer		*
*																																				*
* INPUT: current source file name, current line number, name of the API	*
*		 that failed, and the error number																	*
*																																				*
* RETURNS: none																													*
************************************************************************/

// maximum size of the buffer to be returned from FormatMessage
#define MAX_MSG_BUF_SIZE 512

void perr(PCHAR szFileName, int line, PCHAR szApiName, DWORD dwError)
{
	CHAR szTemp[1024];
	DWORD cMsgLen;
	CHAR *msgBuf; // buffer for message text from system
	int iButtonPressed; // receives button pressed in the error box

	// format our error message
	sprintf(szTemp, "%s: Error %d from %s on line %d:\n", szFileName, dwError,
			szApiName, line);

	// get the text description for that error number from the system
	cMsgLen = FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_ALLOCATE_BUFFER | 40, NULL, dwError,
		MAKELANGID(0, SUBLANG_ENGLISH_US), (LPTSTR) &msgBuf, 
		MAX_MSG_BUF_SIZE, NULL);

	if (!cMsgLen)
		sprintf(szTemp + strlen(szTemp), "Unable to obtain error message text! \n"
				"%s: Error %d from %s on line %d", __FILE__,
				GetLastError(), "FormatMessage", __LINE__);
	else
		strcat(szTemp, msgBuf);

	strcat(szTemp, "\n\nContinue execution?");
	MessageBeep(MB_ICONEXCLAMATION);
	iButtonPressed = MessageBox(NULL, szTemp, "Console API Error",
		MB_ICONEXCLAMATION | MB_YESNO | MB_SETFOREGROUND);

	// free the message buffer returned to us by the system
	if (cMsgLen)
		LocalFree((HLOCAL) msgBuf);
	if (iButtonPressed == IDNO)
		exit(1);

	return;
}

/************************************************************************
* FUNCTION: cls (HANDLE hConsole)																				*
*																																				*
* PURPOSE: clear the screen by filling it with blanks, then home cursor *
*																																				*
* INPUT: the console buffer to clear																		*
*																																				*
* RETURNS: none																													*
************************************************************************/

void cls(HANDLE hConsole)
{
	COORD coordScreen = { 0,0 }; // here's where we'll home the cursor
	BOOL bSuccess;
	DWORD cCharsWritten;
	CONSOLE_SCREEN_BUFFER_INFO csbi; // to get buffer into
	DWORD dwConSize; // number of character cells in the current buffer

	// get the number of character cells in the current buffer
	bSuccess = GetConsoleScreenBufferInfo(hConsole, &csbi);
	PERR(bSuccess, "GetConsoleScreenBufferInfo");
	dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

	// fill the entire screen with blanks
	bSuccess = FillConsoleOutputCharacter(hConsole, (TCHAR) ' ',
		dwConSize, coordScreen, &cCharsWritten);
	PERR(bSuccess, "FillConsoleOutputCharacter");

	// get the current text attribute
	bSuccess = GetConsoleScreenBufferInfo(hConsole, &csbi);
	PERR(bSuccess, "ConsoleScreenBufferInfo");

	// now set the buffer's attributes accordingly
	bSuccess = FillConsoleOutputAttribute(hConsole, csbi.wAttributes,
		dwConSize, coordScreen, &cCharsWritten);
	PERR(bSuccess, "FillConsoleOutputAttribute");

	// put the cursor at (0,0)
	bSuccess = SetConsoleCursorPosition(hConsole, coordScreen);
	PERR(bSuccess, "SetConsoleCursorPosition");

	return;
}

/************************************************************************
* FUNCTION: ClearScreen (void)																					*
*																																				*
* PURPOSE: clear the screen by filling it with blanks                   *
*																																				*
* INPUT: none                        																		*
*																																				*
* RETURNS: none																													*
************************************************************************/

extern void ClearScreen(void)
{
	cls(hStdOut); // overhead for cls for now
}

/************************************************************************
* FUNCTION: SetTextColor (WORD textColor)								*
*																		*
* PURPOSE: changes text output color                                    *
*																		*
* INPUT: the color for the text											*
*																		*
* RETURNS: none															*
************************************************************************/

extern void SetTextColor (WORD textColor)
{
	CONSOLE_SCREEN_BUFFER_INFO csbi; // to get buffer into
	BOOL bSuccess; // whether operation was successful

	textColor %= 16; // put color within range 0-15

	// get the current text attribute
	bSuccess = GetConsoleScreenBufferInfo(hStdOut, &csbi);
	PERR(bSuccess, "GetConsoleScreenBufferInfo");

	// stamp over foreground color only (preserve background)
	csbi.wAttributes = (csbi.wAttributes >> 4) << 4;
	textColor = textColor | csbi.wAttributes;
	
	// set foreground text attribute
	bSuccess = SetConsoleTextAttribute(hStdOut, textColor);
	PERR(bSuccess, "SetConsoleTextAttribute");	

	return;
}

/************************************************************************
* FUNCTION: SetTextBkColor (WORD textBkColor)							*
*																		*
* PURPOSE: sets the background color for text							*				
*																		*
* INPUT: the background color for text									*
*																		*
* RETURNS: none															*
************************************************************************/

extern void SetTextBkColor (WORD textBkColor)
{
	CONSOLE_SCREEN_BUFFER_INFO csbi; // to get buffer into
	BOOL bSuccess; // successful operation

	// put background color within 0-15 range
	textBkColor %= 16;

	// get the current text attribute
	bSuccess = GetConsoleScreenBufferInfo(hStdOut, &csbi);
	PERR(bSuccess, "GetConsoleScreenBufferInfo");

	// shift normal color left 4 bits for background color
	csbi.wAttributes = csbi.wAttributes & 15; //00001111
	textBkColor = (textBkColor << 4) | csbi.wAttributes;

	// set background text attributes
	bSuccess = SetConsoleTextAttribute(hStdOut, textBkColor);
	PERR(bSuccess, "SetConsoleTextBkAttribute");

	return;
}

/************************************************************************
* FUNCTION: GetTextColor (void)											*
*																		*
* PURPOSE: retrieves the current text color								*		
*																		*
* INPUT: none                      										*
*																		*
* RETURNS: current text color											*
************************************************************************/

extern int GetTextColor(void)
{
	CONSOLE_SCREEN_BUFFER_INFO csbi; // to get buffer into
	BOOL bSuccess; // operation successful

	// get the current text attribute
	bSuccess = GetConsoleScreenBufferInfo(hStdOut, &csbi);
	PERR(bSuccess, "GetConsoleScreenBufferInfo");

	// retrieve foreground color only
	csbi.wAttributes = csbi.wAttributes & 15; //00001111

	return csbi.wAttributes;
}

/************************************************************************
* FUNCTION: GetTextBkColor (void)										*
*																		*
* PURPOSE: retrieves the current text background color					*
*																		*
* INPUT: none                         									*
*																		*
* RETURNS: text background color										*
************************************************************************/

extern int GetTextBkColor(void)
{
	CONSOLE_SCREEN_BUFFER_INFO csbi; // to get buffer into
	BOOL bSuccess; // operation successful

	// get the current text attribute
	bSuccess = GetConsoleScreenBufferInfo(hStdOut, &csbi);
	PERR(bSuccess, "GetConsoleScreenBufferInfo");

	// retrieve bk color only
	csbi.wAttributes = (csbi.wAttributes >> 4);

	return csbi.wAttributes;
}

/************************************************************************
* FUNCTION: WhereX (void)         										*
*																		*
* PURPOSE: returns the cursor's X postition on the screen               *
*																		*
* INPUT: none                       									*
*																		*
* RETURNS: cursor's X position											*
************************************************************************/

extern int WhereX (void)
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	BOOL bSuccess;

	bSuccess = GetConsoleScreenBufferInfo(hStdOut, &csbi);
	PERR(bSuccess, "GetConsoleScreenBufferInfo");

	return csbi.dwCursorPosition.X;
}

/************************************************************************
* FUNCTION: WhereY (void)          										*
*																		*
* PURPOSE: returns the current Y coordinate of the cursor               *
*																		*
* INPUT: none                         									*
*																		*
* RETURNS: returns the cursor's Y position								*
************************************************************************/

extern int WhereY (void)
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	BOOL bSuccess; // operation successful

	// retrieve console screen buffer info
	bSuccess = GetConsoleScreenBufferInfo(hStdOut, &csbi);
	PERR(bSuccess, "GetConsoleScreenBufferInfo");

	// return cursor's Y spot
	return csbi.dwCursorPosition.Y;
}

/************************************************************************
* FUNCTION: GotoXY (int X, int Y)										*
*																		*
* PURPOSE: moves cursor to a specified point                            *
*																		*
* INPUT: coordinates to go to on screen									*
*																		*
* RETURNS: none															*
************************************************************************/

extern void GotoXY (int X, int Y)
{
	COORD coordScreen = { X,Y }; // point to move cursor to
	BOOL bSuccess; // operation successful

	// put cursor at X,Y
	bSuccess = SetConsoleCursorPosition(hStdOut, coordScreen);
	PERR(bSuccess, "SetConsoleCursorPosition");
}

/************************************************************************
* FUNCTION: SetTitle (PCHAR szTitle)									*
*																		*
* PURPOSE: sets the title of the console window                         *
*																		*
* INPUT: title for the window        									*
*																		*
* RETURNS: none															*
************************************************************************/

extern void SetTitle(PCHAR szTitle)
{
	BOOL bSuccess; // operation successful

	// set the console title to the input string parameter
	bSuccess = SetConsoleTitle(szTitle);
	PERR(bSuccess, "SetConsoleTitle");

	return;
}

/************************************************************************
* FUNCTION: GetMaxX (void)         										*
*																		*
* PURPOSE: returns the maximum X for the window                         *
*																		*
* INPUT: none                        									*
*																		*
* RETURNS: returns the maximum X for the window							*
************************************************************************/

extern int GetMaxX(void)
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	BOOL bSuccess; // operation successful

	// retrieve console screen buffer info
	bSuccess = GetConsoleScreenBufferInfo(hStdOut, &csbi);
	PERR(bSuccess, "GetConsoleScreenBufferInfo");
	
	// return window's maximum X
	return (csbi.dwSize.X);
}

/************************************************************************
* FUNCTION: GetMaxY (void)       										*
*																		*
* PURPOSE: gets the maximum Y for the window                            *
*																		*
* INPUT: none                        									*
*																		*
* RETURNS: returns the maximum Y for the window							*
************************************************************************/

extern int GetMaxY(void)
{
	CONSOLE_SCREEN_BUFFER_INFO csbi; 
	BOOL bSuccess; // operation successful

	// get console screen buffer info
	bSuccess = GetConsoleScreenBufferInfo(hStdOut, &csbi);
	PERR(bSuccess, "GetConsoleScreenBufferInfo");

	// return size of window specified for Y
	return (csbi.dwSize.Y);
}

/************************************************************************
* FUNCTION: KeyPressed (void)																						*
*																																				*
* PURPOSE: determines whether a key was pressed only										*
*		   (does not return key)																						*
*																																				*
* INPUT: none                        																		*
*																																				*
* RETURNS: returns whether a key was pressed														*
************************************************************************/

extern BOOL KeyPressed(void)
{
	#define INPUT_RECS 10
/* array of records to store peeked events from the input queue */
	INPUT_RECORD aInputBuffer[INPUT_RECS];

	BOOL bSuccess; // successful operation
	DWORD EventsPeeked; // events -- window, keyboard, mouse
	DWORD NumEvents; /* number of events in the input queue */

// See how many input events we have in the queue.
	bSuccess = GetNumberOfConsoleInputEvents(hStdIn, &NumEvents);
	PERR(bSuccess, "GetNumberOfConsoleInputEvents");

// See if one of the events is a keyboard event.
	bSuccess = PeekConsoleInput(hStdIn, aInputBuffer, min(NumEvents,
						INPUT_RECS), &EventsPeeked);
	PERR(bSuccess, "PeekConsoleInput");

	for (unsigned int i = 0; i < EventsPeeked; i++)
	{
		if (aInputBuffer[i].EventType == KEY_EVENT)
		{
			return TRUE;
		}
	}

	return FALSE;
}

/************************************************************************
* FUNCTION: Pause (float WaitTime)																			*
*																																				*
* PURPOSE: How long to pause execution of the program										*
*																																				*
* INPUT: WaitTime -- how long to delay or pause execution               *
*																																				*
* RETURNS: none																													*
************************************************************************/

extern void Pause(unsigned long WaitTime)
{
	Sleep(WaitTime);
}

extern CHAR ReadKey(void)
{
	HANDLE hStdIn; /* standard input */
	BOOL bSuccess;

	INPUT_RECORD inputBuffer;
	DWORD dwInputEvents; /* number of events actually read */

  /* get the standard input handle to read from. There is only one */
  /* instance of standard input per process at any given time */
	hStdIn = GetStdHandle(STD_INPUT_HANDLE);
	PERR(hStdIn != INVALID_HANDLE_VALUE, "GetStdHandle");

	
	do
	{
		bSuccess = ReadConsoleInput(hStdIn, 
					&inputBuffer, 1, &dwInputEvents);
		PERR(bSuccess, "ReadConsoleInput");
	} while (inputBuffer.EventType != KEY_EVENT ||
		inputBuffer.Event.KeyEvent.bKeyDown);

	return inputBuffer.Event.KeyEvent.uChar.AsciiChar;
}

extern void SimpleConsole(bool On)
{
// Turn off mouse events, line input, echo input and window input.
	BOOL bSuccess;
	DWORD dwStdInMode; /* save the input mode here */
	HANDLE hStdIn;

	hStdIn = GetStdHandle(STD_INPUT_HANDLE);
	bSuccess = GetConsoleMode(hStdIn, &dwStdInMode);
	PERR(bSuccess, "GetConsoleMode");
  /* when turning off ENABLE_LINE_INPUT, you MUST also turn off */
  /* ENABLE_ECHO_INPUT. */
	if (On)
		bSuccess = SetConsoleMode(hStdIn, (dwStdInMode & ~(ENABLE_LINE_INPUT |
			ENABLE_ECHO_INPUT | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT)));
	else
		bSuccess = SetConsoleMode(hStdIn, (dwStdInMode | ENABLE_LINE_INPUT |
			ENABLE_ECHO_INPUT | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT));

	PERR(bSuccess, "SetConsoleMode");
}

extern void CursorVisible(bool Val)
{
	CONSOLE_CURSOR_INFO cci;
	HANDLE hConTemp;
	BOOL bSuccess;

	hConTemp = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE,
		  FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CONSOLE_TEXTMODE_BUFFER,
			NULL);
	PERR(hConTemp != INVALID_HANDLE_VALUE,
				  "CreateConsoleScreenBuffer");
  /* make it the active buffer */
	bSuccess = SetConsoleActiveScreenBuffer(hConTemp);
	PERR(bSuccess, "SetConsoleActiveScreenBuffer");

	bSuccess = GetConsoleCursorInfo(hConTemp, &cci);
	PERR(bSuccess, "GetConsoleCursorInfo");

	cci.bVisible = Val;
    bSuccess = SetConsoleCursorInfo(hConTemp, &cci);
    PERR(bSuccess, "SetConsoleCursorInfo");
}


	


