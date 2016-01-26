gcc -o httpd httpd.c pool.c ssp.c -I /data/see/include/ -L /data/see/lib/ -lsee -lpthread -lgc -L /data/boehmgc/lib/
