SHELL := /bin/bash

.PHONY: configure build clean run-game run-editor format install-formatter

configure:
	mkdir -p build
	cd build && cmake ..

build: configure
	cmake --build build -j

clean:
	@if [ -d build ]; then cmake --build build --target clean || true; fi
	rm -rf build

run-game: build
	cmake --build build --target run-game || ./build/game

run-editor: build
	cmake --build build --target run-editor || ./build/editor

install-formatter:
	sudo apt install clang-format

format:
	find . -regex '.*\.\(cpp\|hpp\|cu\|c\|h\)' -exec clang-format -style=file -i {} \;