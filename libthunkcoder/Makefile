####### Compiler, tools and options

CC            = cl
CXX           = cl
DEFINES       = /D "WIN32" /D "NDEBUG" /D "_LIB" /D "MS_VER"
DBGFLAG		  = /Zi
CFLAGS        = /O2 /Oi /GL /EHsc /MT /Gy /W3 /nologo /c $(DEFINES) $(DBGFLAG)
CXXFLAGS      = $(CFLAGS) /TP
INCPATH       = /I "..\..\..\winsdk\include" /I "..\..\..\winsdk\v6.0A\include"
LIB        	  = lib /NOLOGO /LTCG
COPY          = copy /y
COPY_FILE     = $(COPY)
COPY_DIR      = xcopy /s /q /y /i
DEL_FILE      = del
DEL_DIR       = rmdir
MOVE          = move
CHK_DIR_EXISTS= if not exist
MKDIR         = mkdir
INSTALL_FILE    = $(COPY_FILE)
INSTALL_PROGRAM = $(COPY_FILE)
INSTALL_DIR     = $(COPY_DIR)

####### Output directory

OBJECTS_DIR   = .

####### Files

SOURCES       = decode.c input.c itab.c syn-att.c\
				syn-intel.c syn.c udis86.c
OBJECTS       = decode.obj input.obj itab.obj syn-att.obj\
				syn-intel.obj syn.obj udis86.obj
DESTDIR        = ..\..\bin\
TARGET         = libudis86.lib
DESTDIR_TARGET = ..\..\bin\libudis86.lib

####### Build rules

all: $(OBJECTS) 
	$(LIB) /OUT:$(DESTDIR_TARGET) $(OBJECTS)

clean: compiler_clean
	-$(DEL_FILE) $(OBJECTS)

distclean: clean
	-$(DEL_FILE) $(DESTDIR_TARGET)

####### Compile

decode.obj: decode.c types.h itab.h input.h decode.h
	$(CC) $(CFLAGS) $(INCPATH) decode.c

input.obj: input.c extern.h types.h input.h
	$(CC) $(CFLAGS) $(INCPATH) input.c

itab.obj: itab.c types.h decode.h itab.h
	$(CC) $(CFLAGS) $(INCPATH) itab.c

syn-att.obj: syn-att.c types.h extern.h decode.h itab.h syn.h
	$(CC) $(CFLAGS) $(INCPATH) syn-att.c

syn-intel.obj: syn-intel.c types.h extern.h decode.h itab.h syn.h
	$(CC) $(CFLAGS) $(INCPATH) syn-intel.c

syn.obj: syn.c
	$(CC) $(CFLAGS) $(INCPATH) syn.c

udis86.obj: udis86.c input.h extern.h
	$(CC) $(CFLAGS) $(INCPATH) udis86.c

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:

