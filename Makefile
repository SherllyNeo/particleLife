CFLAGS = -g -O -Wall -W -pedantic -std=c99 -O0 -I. -I/raylib/src -I../src -DPLATFORM_RPI
CFLAGS_WEB = -g -O -Wall -W -pedantic -std=c99 -O0 -I. -I/raylib/src/web -I../src/web  -DPLATFORM_WEB
CWEB =-Wall -std=c99 -Wno-missing-braces -O3 -s USE_GLFW=3 -s FORCE_FILESYSTEM=1 -s ASYNCIFY  -I. -I$(HOME)/git/raylib/src -I$(HOME)/git/raylib/src/external -L. -L$(HOME)/git/raylib/src -L$(HOME)/git/raylib/src $(HOME)/git/raylib/src/web/libraylib.a -DPLATFORM_WEB 


LDFLAGS = -L/raylib/src -L/opt/vc/lib
LDFLAGS_WEB = -L/raylib/src/web
LDLIBS = -lraylib -lm 

life src/main.c:
	gcc $(CFLAGS) $(LDFLAGS) src/main.c -o bin/life $(LDLIBS)
install: src/main.c 
	gcc $(CFLAGS) $(LDFLAGS) src/main.c -o bin/life $(LDLIBS) && cp -f ./bin/life $(HOME)/.local/bin/
web: src/main.c 
	emcc src/main.c -o bin/life.html $(CWEB) -lm
