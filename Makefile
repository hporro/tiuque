CC=gcc
CXX=g++
CFLAGS=-std=c++11
SRCDIR=src
OBJDIR=obj
BINDIR=bin
CXXINCLUDES=`pkg-config --cflags gtkmm-2.4 glibmm-2.4 gtkglextmm-1.2` -I /usr/local/include/cleap-0.3.2
LDFLAGS=`pkg-config --libs gtkmm-2.4 glibmm-2.4 gtkglextmm-1.2` -lGLEW -L /usr/local/lib -lcleap
OBJFILES := $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(wildcard $(SRCDIR)/*.cpp))
EXECUTABLE=tiuque

$(shell [ -d "$(OBJDIR)" ] || mkdir -p $(OBJDIR))
$(shell [ -d "$(BINDIR)" ] || mkdir -p $(BINDIR))

make: app

app: $(OBJFILES)
	$(CXX) $(CFLAGS) $(CXXINCLUDES) -o $(BINDIR)/$(EXECUTABLE) $(OBJFILES) $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) -c -o $@ $< $(LDFLAGS) $(CFLAGS) $(CXXINCLUDES) 

clean:
	rm -f $(OBJFILES)
