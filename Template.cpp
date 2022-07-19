// Template.cpp

#include "Template.h"

// Global variables
HWND g_hWndListBox;
HWND g_hWndStatusBar;

int ShowAboutMessage( HWND hWnd )
{
	int nResult = 0;

	MSGBOXPARAMS mbp;

	// Clear message box parameter structure
	ZeroMemory( &mbp, sizeof( mbp ) );

	// Initialise message box parameter structure
	mbp.cbSize		= sizeof( MSGBOXPARAMS );
	mbp.hwndOwner	= hWnd;
	mbp.hInstance	= GetModuleHandle( NULL );
	mbp.lpszText	= ABOUT_MESSAGE_TEXT;
	mbp.lpszCaption	= ABOUT_MESSAGE_CAPTION;
	mbp.dwStyle		= ( MB_OK | MB_USERICON );
	mbp.lpszIcon	= MAKEINTRESOURCE( IDI_APPLICATION_ICON );

	// Show message box
	nResult = MessageBoxIndirect( &mbp );

	return nResult;

} // End of function ShowAboutMessage

LRESULT CALLBACK WndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	LRESULT lr = 0;

	// Select message
	switch( uMsg )
	{
		case WM_CREATE:
		{
			// A create message
			HINSTANCE hInstance;
			HFONT hFont;

			// Get instance
			hInstance = ( ( LPCREATESTRUCT )lParam )->hInstance;

			// Get font
			hFont = ( HFONT )GetStockObject( DEFAULT_GUI_FONT );

			// Create list box window
			g_hWndListBox = CreateWindowEx( LIST_BOX_WINDOW_EXTENDED_STYLE, WC_LISTBOX, LIST_BOX_WINDOW_TEXT, LIST_BOX_WINDOW_STYLE, 0, 0, 0, 0, hWnd, ( HMENU )NULL, hInstance, NULL );

			// Ensure that list box window was created
			if( g_hWndListBox )
			{
				// Successfully created list box window

				// Set list box window font
				SendMessage( g_hWndListBox, WM_SETFONT, ( WPARAM )hFont, ( LPARAM )TRUE );

				// Create status bar window
				g_hWndStatusBar = CreateWindowEx( STATUS_BAR_WINDOW_EXTENDED_STYLE, STATUSCLASSNAME, STATUS_BAR_WINDOW_TEXT, STATUS_BAR_WINDOW_STYLE, 0, 0, 0, 0, hWnd, ( HMENU )NULL, hInstance, NULL );

				// Ensure that status bar window was created
				if( g_hWndStatusBar )
				{
					// Successfully created status bar window

					// Set status bar window font
					SendMessage( g_hWndStatusBar, WM_SETFONT, ( WPARAM )hFont, ( LPARAM )TRUE );

				} // End of successfully created status bar window

			} // End of successfully created list box window

			// Break out of switch
			break;

		} // End of a create message
		case WM_SIZE:
		{
			// A size message
			int nClientWidth;
			int nClientHeight;
			RECT rcStatus;
			int nStatusWindowHeight;
			int nListBoxWindowHeight;

			// Store client width and height
			nClientWidth	= ( int )LOWORD( lParam );
			nClientHeight	= ( int )HIWORD( lParam );

			// Size status bar window
			SendMessage( g_hWndStatusBar, WM_SIZE, ( WPARAM )NULL, ( LPARAM )NULL );

			// Get status window size
			GetWindowRect( g_hWndStatusBar, &rcStatus );

			// Calculate window sizes
			nStatusWindowHeight		= ( rcStatus.bottom - rcStatus.top );
			nListBoxWindowHeight	= ( nClientHeight - nStatusWindowHeight );

			// Move list box window
			MoveWindow( g_hWndListBox, 0, 0, nClientWidth, nListBoxWindowHeight, TRUE );

			// Break out of switch
			break;

		} // End of a size message
		case WM_ACTIVATE:
		{
			// An activate message

			// Focus on list box window
			SetFocus( g_hWndListBox );

			// Break out of switch
			break;

		} // End of an activate message
		case WM_GETMINMAXINFO:
		{
			// A get min max info message
			MINMAXINFO FAR *lpMinMaxInfo;

			// Get min max info structure
			lpMinMaxInfo = ( MINMAXINFO FAR * )lParam;

			// Update min max info structure
			lpMinMaxInfo->ptMinTrackSize.x = MAIN_WINDOW_MINIMUM_WIDTH;
			lpMinMaxInfo->ptMinTrackSize.y = MAIN_WINDOW_MINIMUM_HEIGHT;

			// Break out of switch
			break;

		} // End of a get min max info message
		case WM_DROPFILES:
		{
			// A drop files message
			UINT uFileCount;
			HDROP hDrop;
			UINT uWhichFile;
			UINT uFileSize;

			// Allocate string memory
			LPTSTR lpszFilePath = new char[ STRING_LENGTH ];

			// Get drop handle
			hDrop = ( HDROP )wParam;

			// Count dropped files
			uFileCount = DragQueryFile( hDrop, ( UINT )-1, NULL, 0 );

			// Loop through dropped files
			for( uWhichFile = 0; uWhichFile < uFileCount; uWhichFile ++ )
			{
				// Get size of dropped file
				uFileSize = DragQueryFile( hDrop, uWhichFile, NULL, 0 );

				// Ensure that file size is valid
				if( uFileSize != 0 )
				{
					// File size is valid

					// Get file path
					if( DragQueryFile( hDrop, uWhichFile, lpszFilePath, ( uFileSize + sizeof( char ) ) ) )
					{
						// Successfully got file path

						// Add file path to list box window
						SendMessage( g_hWndListBox, LB_ADDSTRING, ( WPARAM )NULL, ( LPARAM )lpszFilePath );

					} // End of successfully got file path

				} // End of file size is valid

			}; // End of loop through dropped files

			// Free string memory
			delete [] lpszFilePath;

			// Break out of switch
			break;

		} // End of a drop files message
		case WM_COMMAND:
		{
			// A command message

			// Select command
			switch( LOWORD( wParam ) )
			{
				case IDM_FILE_EXIT:
				{
					// A file exit command

					// Destroy window
					DestroyWindow( hWnd );

					// Break out of switch
					break;

				} // End of a file exit command
				case IDM_HELP_ABOUT:
				{
					// A help about command

					// Show about message
					ShowAboutMessage( hWnd );

					// Break out of switch
					break;

				} // End of a help about command
				default:
				{
					// Default command

					// See if command message is from list box window
					if( ( HWND )lParam == g_hWndListBox )
					{
						// Command message is from list box window

						// Select list box window notification code
						switch( HIWORD( wParam ) )
						{
							case LBN_DBLCLK:
							{
								// A list box window double click notification code
								int nSelectedItem;

								// Allocate string memory
								LPTSTR lpszSelected = new char[ STRING_LENGTH ];

								// Get selected item
								nSelectedItem = SendMessage( g_hWndListBox, LB_GETCURSEL, ( WPARAM )NULL, ( LPARAM )NULL );

								// Get selected item text
								if( SendMessage( g_hWndListBox, LB_GETTEXT, ( WPARAM )nSelectedItem, ( LPARAM )lpszSelected ) )
								{
									// Successfully got selected item text

									// Display selected item text
									MessageBox( hWnd, lpszSelected, INFORMATION_MESSAGE_CAPTION, ( MB_OK | MB_ICONINFORMATION ) );

								} // End of successfully got selected item text

								// Free string memory
								delete [] lpszSelected;

								// Break out of switch
								break;

							} // End of a list box window double click notification code
							case LBN_SELCHANGE:
							{
								// A list box window selection change notification code
								int nSelectedItem;

								// Allocate string memory
								LPTSTR lpszSelected = new char[ STRING_LENGTH ];

								// Get selected item
								nSelectedItem = SendMessage( g_hWndListBox, LB_GETCURSEL, ( WPARAM )NULL, ( LPARAM )NULL );

								// Get selected item text
								if( SendMessage( g_hWndListBox, LB_GETTEXT, ( WPARAM )nSelectedItem, ( LPARAM )lpszSelected ) )
								{
									// Successfully got selected item text

									// Show selected item text on status bar window
									SendMessage( g_hWndStatusBar, SB_SETTEXT, ( WPARAM )NULL, ( LPARAM )lpszSelected );

								} // End of successfully got selected item text

								// Free string memory
								delete [] lpszSelected;

								// Break out of switch
								break;

							} // End of a list box window selection change notification code
							default:
							{
								// Default list box window notification code

								// Call default procedure
								lr = DefWindowProc( hWnd, uMsg, wParam, lParam );

								// Break out of switch
								break;

							} // End of default list box window notification code

						}; // End of selection for list box window notification code

					} // End of command message is from list box window
					else
					{
						// Command message is not from list box window

						// Call default procedure
						lr = DefWindowProc( hWnd, uMsg, wParam, lParam );

					} // End of command message is not from list box window

					// Break out of switch
					break;

				} // End of default command

			}; // End of selection for command

			// Break out of switch
			break;

		} // End of a command message
		case WM_SYSCOMMAND:
		{
			// A system command message

			// Select system command
			switch( LOWORD( wParam ) )
			{
				case IDM_HELP_ABOUT:
				{
					// A help about system command

					// Show about message
					ShowAboutMessage( hWnd );

					// Break out of switch
					break;

				} // End of a help about system command
				default:
				{
					// Default system command

					// Call default procedure
					lr = DefWindowProc( hWnd, uMsg, wParam, lParam );

					// Break out of switch
					break;

				} // End of default system command

			}; // End of selection for system command

			// Break out of switch
			break;

		} // End of a system command message
		case WM_NOTIFY:
		{
			// A notify message

			// Call default handler
			lr = DefWindowProc( hWnd, uMsg, wParam, lParam );

			// Break out of switch
			break;

		} // End of a notify message
		case WM_CONTEXTMENU:
		{
			// A context menu message
			HMENU hMenu;

			// Load context menu
			hMenu = LoadMenu( NULL, MAKEINTRESOURCE( IDR_CONTEXT_MENU ) );

			// Show context menu
			TrackPopupMenu( GetSubMenu( hMenu, 0 ), ( TPM_LEFTALIGN | TPM_LEFTBUTTON ), LOWORD( lParam ), HIWORD( lParam ), 0, hWnd, NULL );

			// Break out of switch
			break;

		} // End of a context menu message
		case WM_CLOSE:
		{
			// A close message

			// Destroy window
			DestroyWindow( hWnd );

			// Break out of switch
			break;

		} // End of a close message
		case WM_DESTROY:
		{
			// A destroy message

			// Terminate thread
			PostQuitMessage( 0 );

			// Break out of switch
			break;

		} // End of a destroy message
		default:
		{
			// Default message

			// Call default window procedure
			lr = DefWindowProc( hWnd, uMsg, wParam, lParam );

			// Break out of switch
			break;

		} // End of default message

	}; // End of selection for message

	return lr;

} // End of function WndProc

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow )
{
	MSG msg;

	WNDCLASSEX wc;

	// Clear message structure
	ZeroMemory( &msg, sizeof( msg ) );

	// Clear window class structure
	ZeroMemory( &wc, sizeof( wc ) );

	// Initialise window class structure
	wc.cbSize			= sizeof( WNDCLASSEX );
	wc.lpfnWndProc		= WndProc;
	wc.hInstance		= hInstance;
	wc.lpszClassName	= MAIN_WINDOW_CLASS_NAME;
	wc.style			= MAIN_WINDOW_CLASS_STYLE;
	wc.hIcon			= MAIN_WINDOW_CLASS_ICON;
	wc.hCursor			= MAIN_WINDOW_CLASS_CURSOR;
	wc.hbrBackground	= MAIN_WINDOW_CLASS_BACKGROUND;
	wc.lpszMenuName		= MAIN_WINDOW_CLASS_MENU_NAME;
	wc.hIconSm			= MAIN_WINDOW_CLASS_ICON_SMALL;

	// Register window class
	if( RegisterClassEx( &wc ) )
	{
		// Successfully registered window class
		HWND hWnd;

		// Create window
		hWnd = CreateWindowEx( MAIN_WINDOW_EXTENDED_STYLE, MAIN_WINDOW_CLASS_NAME, MAIN_WINDOW_TEXT, MAIN_WINDOW_STYLE, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL );

		// Ensure that window was created
		if( hWnd )
		{
			// Successfully created window
			HMENU hMenuSystem;
			LPWSTR *lpszArgumentList;
			int nArgumentCount;

			// Get system menu
			hMenuSystem = GetSystemMenu( hWnd, FALSE );

			// Add separator item to system menu
			InsertMenu( hMenuSystem, SYSTEM_MENU_SEPARATOR_ITEM_POSITION, ( MF_BYPOSITION | MF_SEPARATOR ), 0, NULL );

			// Add about item to system menu
			InsertMenu( hMenuSystem, SYSTEM_MENU_ABOUT_ITEM_POSITION, MF_BYPOSITION, IDM_HELP_ABOUT, SYSTEM_MENU_ABOUT_ITEM_TEXT );

			// Get argument list
			lpszArgumentList = CommandLineToArgvW( GetCommandLineW(), &nArgumentCount );

			// Ensure that argument list was got
			if( lpszArgumentList )
			{
				// Successfully got argument list
				int nWhichArgument;
				int nSizeNeeded;
				int nWideArgumentLength;

				// Allocate string memory
				LPTSTR lpszArgument = new char[ STRING_LENGTH ];

				// Loop through arguments
				for( nWhichArgument = 1; nWhichArgument < nArgumentCount; nWhichArgument ++ )
				{
					// Get wide argument length
					nWideArgumentLength = lstrlenW( lpszArgumentList[ nWhichArgument ] );

					// Get size required for argument
					nSizeNeeded = WideCharToMultiByte( CP_UTF8, 0, lpszArgumentList[ nWhichArgument ], nWideArgumentLength, NULL, 0, NULL, NULL );

					// Convert argument to ansi
					WideCharToMultiByte( CP_UTF8, 0, lpszArgumentList[ nWhichArgument ], nWideArgumentLength, lpszArgument, nSizeNeeded, NULL, NULL );

					// Terminate argument
					lpszArgument[ nSizeNeeded ] = ( char )NULL;

					// Add argument to list box window
					SendMessage( g_hWndListBox, LB_ADDSTRING, ( WPARAM )NULL, ( LPARAM )lpszArgument );

				}; // End of loop through arguments

				// Free string memory
				delete [] lpszArgument;

			} // End of successfully got argument list

			// Show window
			ShowWindow( hWnd, nCmdShow );

			// Update window
			UpdateWindow( hWnd );

			// Message loop
			while( GetMessage( &msg, NULL, 0, 0 ) > 0 )
			{
				// Translate message
				TranslateMessage( &msg );

				// Dispatch message
				DispatchMessage( &msg );

			}; // End of message loop

		} // End of successfully created window
		else
		{
			// Unable to create window

			// Display error message
			MessageBox( NULL, UNABLE_TO_CREATE_WINDOW_ERROR_MESSAGE, ERROR_MESSAGE_CAPTION, ( MB_OK | MB_ICONERROR ) );

		} // End of unable to create window

	} // End of successfully registered window class
	else
	{
		// Unable to register window class

		// Display error message
		MessageBox( NULL, UNABLE_TO_REGISTER_WINDOW_CLASS_ERROR_MESSAGE, ERROR_MESSAGE_CAPTION, ( MB_OK | MB_ICONERROR ) );

	} // End of unable to register window class

	return msg.wParam;

} // End of function WinMain