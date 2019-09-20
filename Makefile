run-game:
	cd Game && make && ./game

run-editor:
	cd TrackEditor && make && ./trackeditor

clean:
	cd Game && make clean
	cd TrackEditor && make clean
	cd Common && make clean