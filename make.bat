cls

del *.exe

windres Resource.rc -o Resource.o

g++ -mwindows -m64 -static -Wall -Wextra Template.cpp ListBoxWindow.cpp Resource.o -o Template.exe
