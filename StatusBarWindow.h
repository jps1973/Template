// StatusBarWindow.h

#pragma once

#include <windows.h>
#include <commctrl.h>

#include "Ascii.h"
#include "Common.h"

#define STATUS_BAR_WINDOW_CLASS_NAME											STATUSCLASSNAME

#define STATUS_BAR_WINDOW_EXTENDED_STYLE										0
#define STATUS_BAR_WINDOW_STYLE													( WS_CHILD | WS_VISIBLE | SBARS_SIZEGRIP )
#define STATUS_BAR_WINDOW_TEXT													NULL

BOOL IsStatusBarWindow( HWND hWnd );

BOOL StatusBarWindowCreate( HWND hWndParent, HINSTANCE hInstance );

BOOL StatusBarWindowGetRect( LPRECT lpRect );

BOOL StatusBarWindowSize();

HWND StatusBarWindowSetFocus();

BOOL StatusBarWindowSetText( LPCTSTR lpszStatusText );

void StatusBarWindowSetFont( HFONT hFont );
