all: app libfoo.so
	mv app myapp/bin/
	mv libfoo.so myapp/lib/

clean:
	rm *.o

app: app.o libfoo.so
	# make sure the app file's RPATH='$ORIGIN'/../lib
	gcc -Wl,-rpath,'$$ORIGIN'/../lib -L. -lfoo -o app $<

libfoo.so: mod1.o mod2.o
	gcc -shared -o $@ -Wl,-rpath,'$$ORIGIN' $^

mod1.o: mod1.c
	gcc -c -fPIC $<
mod2.o: mod2.c
	gcc -c -fPIC $<

test: all
	objdump -p myapp/bin/app | grep RPATH
	ldd myapp/bin/app
	ldd myapp/lib/libfoo.so
	myapp/bin/app

