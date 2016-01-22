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
tar zxvf see-3.1.1424.tar.gz
unzip boehm-gc.zip
cd boehm-gc
./configure --prefix=/your/boehm-gc 
make
make install
cd ..
cd see-3.1.1424
./configure --prefix=/your/see --with-boehm-gc=/your/boehm-gc/
make 
make install
```
