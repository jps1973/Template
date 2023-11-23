// ListBoxWindow.cpp

#include "ListBoxWindow.h"

// Global variables
HWND g_hWndListBox;

BOOL IsListBoxWindow( HWND hWnd )
{
	// See if supplied window is list box window
	return( hWnd == g_hWndListBox );

} // End of function IsListBoxWindow

int ListBoxWindowAddString( LPCTSTR lpszString )
{
	// Add string to list box window
	return ::SendMessage( g_hWndListBox, LB_ADDSTRING, ( WPARAM )NULL, ( LPARAM )lpszString );

} // End of function ListBoxWindowAddString

BOOL ListBoxWindowCreate( HWND hWndParent, HINSTANCE hInstance )
{
	BOOL bResult = FALSE;

	// Create list box window
	g_hWndListBox = ::CreateWindowEx( LIST_BOX_WINDOW_EXTENDED_STYLE, LIST_BOX_WINDOW_CLASS_NAME, LIST_BOX_WINDOW_TEXT, LIST_BOX_WINDOW_STYLE, 0, 0, 0, 0, hWndParent, ( HMENU )NULL, hInstance, NULL );

	// Ensure that list box window was created
	if( g_hWndListBox )
	{
		// Successfully created list box window

		// Update return value
		bResult = TRUE;

	} // End of successfully created list box window
	return bResult;

} // End of function ListBoxWindowCreate

int ListBoxWindowGetCurrentSelection()
{
	// Get current selection item
	return ::SendMessage( g_hWndListBox, LB_GETCURSEL, ( WPARAM )NULL, ( LPARAM )NULL );

} // End of function ListBoxWindowGetCurrentSelection

int ListBoxWindowGetItemText( int nWhichItem, LPTSTR lpszItemText )
{
	// Get item text
	return::SendMessage( g_hWndListBox, LB_GETTEXT, ( WPARAM )nWhichItem, ( LPARAM )lpszItemText );

} // End of function ListBoxWindowGetItemText

BOOL ListBoxWindowGetRect( LPRECT lpRect )
{
	// Get list box window rect
	return ::GetWindowRect( g_hWndListBox, lpRect );

} // End of function ListBoxWindowGetRect

BOOL ListBoxWindowMove( int nX, int nY, int nWidth, int nHeight, BOOL bRepaint )
{
	// Move list box window
	return ::MoveWindow( g_hWndListBox, nX, nY, nWidth, nHeight, bRepaint );

} // End of function ListBoxWindowMove

HWND ListBoxWindowSetFocus()
{
	// Focus on list box window
	return ::SetFocus( g_hWndListBox );

} // End of function ListBoxWindowSetFocus

void ListBoxWindowSetFont( HFONT hFont )
{
	// Set list box window font
	::SendMessage( g_hWndListBox, WM_SETFONT, ( WPARAM )hFont, ( LPARAM )TRUE );

} // End of function ListBoxWindowSetFont
