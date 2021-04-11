.PHONY: build clean

all: build

build:
	mkdir -p build && \
	cd build && \
	cmake .. && \
	make

test: build
	build/libevconfig_test


clean:
	rm -rf build
