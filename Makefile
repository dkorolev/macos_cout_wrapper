.PHONY: debug release clean

debug:
	./run.sh debug

release:
	./run.sh release

clean:
	rm -rf .debug .release
