build:
	mkdir -p build && cd build && cmake .. && make

rebuild:
	rm -rf build && mkdir build && cd build && cmake .. && make

run:
	./build/task $(ARGS)

test_validator:
	./build/test_validator

test_club:
	./build/test_club

clean:
	rm -rf build
