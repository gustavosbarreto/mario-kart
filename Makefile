run-game:
	cd Game && make && ./game

run-editor:
	cd TrackEditor && make && ./editor

clean:
	cd Game && make clean
	cd TrackEditor && make clean
	cd Common && make clean

install-formatter:
	sudo apt-get install clang-format

format:
	find . -regex '.*\.\(cpp\|hpp\|cu\|c\|h\)' -exec clang-format -style=file -i {} \;