CXXFLAGS=-Wall -O3 -g
OBJECTS= Menu_main.o reversi-interface.o demo-main.o demo-main2.o minimal-example.o text-example.o led-image-viewer.o
BINARIES= Menu_main reversi-interface led-matrix led-matrix2 minimal-example text-example
ALL_BINARIES=$(BINARIES) led-image-viewer

# Where our library resides. It is split between includes and the binary
# library in lib
RGB_INCDIR=include
RGB_LIBDIR=lib
RGB_LIBRARY_NAME=rgbmatrix
RGB_LIBRARY=$(RGB_LIBDIR)/lib$(RGB_LIBRARY_NAME).a
LDFLAGS+=-L$(RGB_LIBDIR) -l$(RGB_LIBRARY_NAME) -lrt -lm -lpthread

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

led-matrix : demo-main.o $(RGB_LIBRARY)
	$(CXX) $(CXXFLAGS) demo-main.o -o $@ $(LDFLAGS)

led-matrix2 : demo-main2.o $(RGB_LIBRARY)
	$(CXX) $(CXXFLAGS) demo-main2.o -o $@ $(LDFLAGS)

minimal-example : minimal-example.o $(RGB_LIBRARY)
	$(CXX) $(CXXFLAGS) minimal-example.o -o $@ $(LDFLAGS)

text-example : text-example.o $(RGB_LIBRARY)
	$(CXX) $(CXXFLAGS) text-example.o -o $@ $(LDFLAGS)

led-image-viewer: led-image-viewer.o $(RGB_LIBRARY)
	$(CXX) $(CXXFLAGS) led-image-viewer.o -o $@ $(LDFLAGS) $(MAGICK_LDFLAGS)

%.o : %.cc
	$(CXX) -I$(RGB_INCDIR) $(CXXFLAGS) -c -o $@ $<

led-image-viewer.o : led-image-viewer.cc
	$(CXX) -I$(RGB_INCDIR) $(CXXFLAGS) $(MAGICK_CXXFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJECTS) $(ALL_BINARIES)
	$(MAKE) -C lib clean
