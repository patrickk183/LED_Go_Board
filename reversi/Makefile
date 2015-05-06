CXXFLAGS=-Wall -O3 -g
OBJECTS= Menu_main.o reversi-interface.o led-image-viewer.o
BINARIES= Menu_main 
ALL_BINARIES=$(BINARIES) led-image-viewer

# Where our library resides. It is split between includes and the binary
# library in lib
RGB_INCDIR=include
RGB_LIBDIR=lib
RGB_LIBRARY_NAME=rgbmatrix
RGB_LIBRARY=$(RGB_LIBDIR)/lib$(RGB_LIBRARY_NAME).a
LDFLAGS+=-L$(RGB_LIBDIR) -l$(RGB_LIBRARY_NAME) -lrt -lm -lpthread -lbcm2835

# Imagemagic flags, only needed if actually compiled.
MAGICK_CXXFLAGS=`GraphicsMagick++-config --cppflags --cxxflags`
MAGICK_LDFLAGS=`GraphicsMagick++-config --ldflags --libs`

all : $(BINARIES)

$(RGB_LIBRARY):
	$(MAKE) -C $(RGB_LIBDIR)
	
Menu_main : Menu_main.o $(RGB_LIBRARY)
	$(CXX) $(CXXFLAGS) Menu_main.o -o $@ $(LDFLAGS)

reversi-interface : reversi-interface.o $(RGB_LIBRARY)
	$(CXX) $(CXXFLAGS) reversi-interface.o -o $@ $(LDFLAGS)

led-image-viewer: led-image-viewer.o $(RGB_LIBRARY)
	$(CXX) $(CXXFLAGS) led-image-viewer.o -o $@ $(LDFLAGS) $(MAGICK_LDFLAGS)

%.o : %.cc
	$(CXX) -I$(RGB_INCDIR) $(CXXFLAGS) -c -o $@ $<

led-image-viewer.o : led-image-viewer.cc
	$(CXX) -I$(RGB_INCDIR) $(CXXFLAGS) $(MAGICK_CXXFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJECTS) $(ALL_BINARIES)
	$(MAKE) -C lib clean
