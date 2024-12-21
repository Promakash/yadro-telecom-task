build:
	mkdir build && cd build && cmake .. && make

rebuild:
	rm -rf build
	$(MAKE) build
