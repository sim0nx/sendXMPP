#--- BUILD ---
CXX=g++
LDFLAGS= -lgnutls -lpthread -lz
DLDFLAGS = -lgloox
INCLUDES =
SLIBS = /usr/lib/libgloox.a /usr/lib/x86_64-linux-gnu/libidn.a
CXXFLAGS = -Wall -O3 -minline-stringops-dynamically -pipe -fomit-frame-pointer
#CXXFLAGS = -Wall -pedantic -ggdb -g3 -O
OBJS = $(patsubst %.cpp,%.o,$(wildcard *.cpp))

#--- INSTALL ---

INSTALL=install
bindir=/usr/bin
mandir=/usr/share/man/man1

#--- TARGETS ---

all: sendxmpp++

sendxmpp++: $(OBJS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(LDFLAGS) -o $@ $^ ${SLIBS}
	strip $@

dynamic: $(OBJS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(DLDFLAGS) $(LDFLAGS) -o sendxmpp++ $^
	strip sendxmpp++

debug: $(OBJS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(DLDFLAGS) $(LDFLAGS) -o sendxmpp++ $^

%.o: %.cpp
	$(CXX) $(INCLUDES) $(CXXFLAGS) -c -o "$@" "$<"

install:
	$(INSTALL) -D "sendxmpp++" "$(DESTDIR)$(bindir)/sendxmpp++"
	$(INSTALL) -D "sendxmpp++.1" "$(DESTDIR)$(mandir)/sendxmpp++.1"

clean:
	@rm -f $(OBJS) $(DBGS) sendxmpp++
