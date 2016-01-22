# drip.js

## more little than node.js
## more flexible than node.js
## more extended than node.js


## NEED FILES 

*boehm-gc:*
https://github.com/coapp-packages/boehm-gc

*SEE:*
https://www.adaptive-enterprises.com/~d/software/see/see-3.1.1424.tar.gz
https://www.adaptive-enterprises.com/~d/software/see/

## INSTALL

```
gcpath=/your/boehm-gc
seepath=/your/seepath

tar zxvf see-3.1.1424.tar.gz
unzip boehm-gc.zip
cd boehm-gc
./configure --prefix=$gcpath
make
make install
cd ..
cd see-3.1.1424
./configure --prefix=$seepath --with-boehm-gc=$gcpath
make 
make install
```
