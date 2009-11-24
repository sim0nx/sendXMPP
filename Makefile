CXX=g++
LDFLAGS =
INCLUDES =
LIBS = /usr/lib/libgloox.a /usr/lib/libgnutls.a /usr/lib/libtasn1.a /usr/lib/libz.a /usr/lib/libgcrypt.a /usr/lib/libgpg-error.a /usr/lib/libresolv.a /usr/lib/libidn.a
CXXFLAGS = -Wall -O3 -minline-stringops-dynamically -pipe -fomit-frame-pointer
#CXXFLAGS = -O3 -mtune=core2 -march=core2 -minline-stringops-dynamically -mssse3 -msse4 -mfpmath=sse -pipe -fomit-frame-pointer

OBJS = $(patsubst %.cpp,%.o,$(wildcard *.cpp))


all: sendXMPP

sendXMPP: $(OBJS)
	$(CXX) $(INCLUDES) $(LDFLAGS) $(CXXFLAGS) -o $@ $^ ${LIBS}

%.o: %.cpp
	$(CXX) $(INCLUDES) $(CXXFLAGS) -c -o "$@" "$<"


clean:
	@rm -f $(OBJS) $(DBGS) sendXMPP

docs:
	doxygen Doxyfile
