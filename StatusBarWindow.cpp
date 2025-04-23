// StatusBarWindow.cpp

#include "StatusBarWindow.h"

// Global variables
static HWND g_hWndStatusBar;

BOOL IsStatusBarWindow( HWND hWnd )
{
	// See if supplied window is template window
	return( hWnd == g_hWndStatusBar );

} // End of function IsStatusBarWindow

BOOL StatusBarWindowCreate( HWND hWndParent, HINSTANCE hInstance )
{
	BOOL bResult = FALSE;

	// Create template window
	g_hWndStatusBar = CreateWindowEx( STATUS_BAR_WINDOW_EXTENDED_STYLE, STATUS_BAR_WINDOW_CLASS_NAME, STATUS_BAR_WINDOW_TEXT, STATUS_BAR_WINDOW_STYLE, 0, 0, 0, 0, hWndParent, ( HMENU )NULL, hInstance, NULL );

	// Ensure that template window was created
	if( g_hWndStatusBar )
	{
		// Successfully created template window

		// Update return value
		bResult = TRUE;

	} // End of successfully created template window
	return bResult;

} // End of function StatusBarWindowCreate

BOOL StatusBarWindowGetRect( LPRECT lpRect )
{
	// Get template window rect
	return GetWindowRect( g_hWndStatusBar, lpRect );

} // End of function StatusBarWindowGetRect

BOOL StatusBarWindowMove( int nX, int nY, int nWidth, int nHeight, BOOL bRepaint )
{
	// Move template window
	return MoveWindow( g_hWndStatusBar, nX, nY, nWidth, nHeight, bRepaint );

} // End of function StatusBarWindowMove

HWND StatusBarWindowSetFocus()
{
	// Focus on template window
	return SetFocus( g_hWndStatusBar );

} // End of function StatusBarWindowSetFocus

void StatusBarWindowSetFont( HFONT hFont )
{
	// Set template window font
	SendMessage( g_hWndStatusBar, WM_SETFONT, ( WPARAM )hFont, ( LPARAM )TRUE );

} // End of function StatusBarWindowSetFont

BOOL StatusBarWindowSetText( LPCTSTR lpszStatusText )
{
	// Set status bar window text
	return SendMessage( g_hWndStatusBar, SB_SETTEXT, ( WPARAM )NULL, ( LPARAM )lpszStatusText );

} // End of function StatusBarWindowSetText

LRESULT StatusBarWindowSize()
{
	// Size status bar window
	return SendMessage( g_hWndStatusBar, WM_SIZE, ( WPARAM )NULL, ( LPARAM )NULL );

} // End of function StatusBarWindowSize
