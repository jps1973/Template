// ListBoxWindow.h

#pragma once

#include <windows.h>
#include <commctrl.h>

#include "Ascii.h"
#include "Common.h"

#define LIST_BOX_WINDOW_CLASS_NAME												WC_LISTBOX

#define LIST_BOX_WINDOW_EXTENDED_STYLE											0
#define LIST_BOX_WINDOW_STYLE													( WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL | WS_BORDER | LBS_NOINTEGRALHEIGHT | LBS_NOTIFY )
#define LIST_BOX_WINDOW_TEXT													NULL

BOOL IsListBoxWindow( HWND hWnd );

int ListBoxWindowAddString( LPCTSTR lpszString );

BOOL ListBoxWindowCreate( HWND hWndParent, HINSTANCE hInstance );

BOOL ListBoxWindowGetRect( LPRECT lpRect );

BOOL ListBoxWindowHandleCommandMessage( WPARAM wParam, LPARAM lParam, BOOL( *lpStatusFunction )( LPCTSTR lpszItemText ) );

BOOL ListBoxWindowHandleNotifyMessage( WPARAM wParam, LPARAM lParam, BOOL( *lpStatusFunction )( LPCTSTR lpszItemText ) );

BOOL ListBoxWindowMove( int nX, int nY, int nWidth, int nHeight, BOOL bRepaint = TRUE );

HWND ListBoxWindowSetFocus();

void ListBoxWindowSetFont( HFONT hFont );
