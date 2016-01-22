SEELIB=-I /data/see/include/ -L /data/see/lib/ -lsee -lgc -L/data/boehmgc/lib/

aims=jsstr jsfile jsfunc jsmodule drip

.PHONY:all

all:$(aims)

jsstr:js.c
	gcc -g -o jsstr js.c $(SEELIB)
jsfile:jsf.c
	gcc -g -o jsfile jsf.c $(SEELIB)
jsfunc:jsfunc.c addFunc.c
	gcc -g -o jsfunc jsfunc.c $(SEELIB)
jsmodule:jsmodule.c mod_File.c
	gcc -g -o jsmodule jsmodule.c $(SEELIB)

drip:drip.c
	gcc -g -o drip drip.c $(SEELIB)

test:all
	./jsstr	&& ./jsfunc && ./jsfile && ./jsmodule && ./drip

clean:
	rm $(aims) 
