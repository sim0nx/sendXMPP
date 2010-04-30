CXX=g++
LDFLAGS = -lgnutls -ltasn1 -lz -lgcrypt -lgpg-error -lresolv -lpthread
DLDFLAGS = -lgloox
INCLUDES =
SLIBS = /usr/lib/libgloox.a /usr/lib/libidn.a
#SLIBS = /usr/lib/libgloox.a /usr/lib/libgnutls.a /usr/lib/libtasn1.a /usr/lib/libz.a /usr/lib/libgcrypt.a /usr/lib/libgpg-error.a /usr/lib/libresolv.a /usr/lib/libidn.a
#CXXFLAGS = -Wall -O3 -minline-stringops-dynamically -pipe -fomit-frame-pointer
CXXFLAGS = -Wall -pedantic -ggdb -g3 -O

OBJS = $(patsubst %.cpp,%.o,$(wildcard *.cpp))


all: sendXMPP

sendXMPP: $(OBJS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(LDFLAGS) -o $@ $^ ${SLIBS}
	strip $@

dynamic: $(OBJS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(DLDFLAGS) $(LDFLAGS) -o sendXMPP $^
	#strip sendXMPP

%.o: %.cpp
	$(CXX) $(INCLUDES) $(CXXFLAGS) -c -o "$@" "$<"


clean:
	@rm -f $(OBJS) $(DBGS) sendXMPP
