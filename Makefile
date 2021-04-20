.PHONY: build clean

all: build

build:
	mkdir -p build && \
	cd build && \
	cmake -GNinja .. && \
	ninja

test: build
	build/libevconfig_test


clean:
	rm -rf build
