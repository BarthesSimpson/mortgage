.PHONY: all
all:
	mkdir -p build; cd build; cmake .. -DCMAKE_BUILD_TYPE=Debug -G "Unix Makefiles"; make all
