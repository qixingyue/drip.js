SEELIB=-I /data/see/include/ -L /data/see/lib/ -lsee

aims=jsstr jsfile jsfunc jsmodule

.PHONY:all

all:$(aims)

jsstr:js.c
	gcc -g -o jsstr js.c $(SEELIB)
jsfile:jsf.c
	gcc -g -o jsfile jsf.c -I /data/see/include/ -L /data/see/lib/ -lsee
jsfunc:jsfunc.c addFunc.c
	gcc -g -o jsfunc jsfunc.c -I /data/see/include/ -L /data/see/lib/ -lsee
jsmodule:jsmodule.c mod_File.c
	gcc -g -o jsmodule jsmodule.c -I /data/see/include/ -L /data/see/lib/ -lsee

clean:
	rm $(aims) 
