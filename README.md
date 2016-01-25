# drip.js

## Features

*  more little than node.js
*  more flexible than node.js
*  more extended than node.js

## NEED FILES 

*boehm-gc:* </br>
https://github.com/coapp-packages/boehm-gc </br>

*SEE:* </br>
https://www.adaptive-enterprises.com/~d/software/see/see-3.1.1424.tar.gz </br>
https://www.adaptive-enterprises.com/~d/software/see/ </br>
http://anyapi.sinaapp.com/USAGE.html

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

## Tips:

* Mac OSX You may need Change : 
```
FROM : 
293 CC = gcc 

TO 
293 CC = gcc -D _XOPEN_SOURCE=600 </br>
```

* On Mac With-GC may have some problems.
