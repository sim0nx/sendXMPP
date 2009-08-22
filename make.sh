CFLAGS="-O3 -mtune=core2 -march=core2 -minline-stringops-dynamically -mssse3 -msse4 -mfpmath=sse -pipe -fomit-frame-pointer"
LIBS="/usr/lib/libgloox.a /usr/lib/libgnutls.a /usr/lib/libtasn1.a /usr/lib/libz.a /usr/lib/libgcrypt.a /usr/lib/libgpg-error.a /usr/lib/libresolv.a /usr/lib/libidn.a"

g++ ${CFLAGS} -o SendXMPP main.cpp ${LIBS}

strip SendXMPP
