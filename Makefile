.PHONY: all
all: 
	mkdir -p build; cd build; cmake .. -DCMAKE_BUILD_TYPE=Debug -G "Unix Makefiles"; make all

.PHONY: quick
quick:
	cd build; make all

.PHONY: test
test:
	cd build; make mortgage_tst; cd ..; ./build/test/mortgage_tst

.PHONY: clean
clean: 
	@rm -rf build

