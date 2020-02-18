include premake

.PHONY : all

OBJS = yymine.o gamestruct.o gamewindow.o
OBJS += drawcubic.o drawface.o drawscreen.o
OBJS += cubicwndproc.o timescreenwndproc.o facewndproc.o counterscreenwndproc.o

all : 1.exe

1.exe : $(OBJS) libwinstart.a yymine.res
	$(CC) $(CFLAGS) -g -o $@ $^ $(YYINCLUDE) -lwinmm -lgdi32

$(OBJS) : %.o : %.c
	$(CC) -o $@ -c $< $(YYINCLUDE)

yymine.res : yymine.rc
	windres $< -O coff -o $@

.PHONY : clean

clean :
	$(RM) *.exe *.o *.res