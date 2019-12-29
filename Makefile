ifeq ($(prefix),)
	prefix=/usr/local
endif
ifeq ($(shell which $(CXX)),)
	CXX=g++
endif
all:
	$(CXX) $(CXXFLAGS) -o dum4 dum4.cpp
	strip -S dum4
install:
	if [ ! -d "$(DESTDIR)$(prefix)/games" ]; then mkdir -p $(DESTDIR)$(prefix)/games; fi
	install -m755 dum4 $(DESTDIR)$(prefix)/games
clean:
	rm dum4
