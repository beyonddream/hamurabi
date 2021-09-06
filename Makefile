all:
	@./build.sh r
.PHONY: all

clean:
	@$(MAKE) -s -C build -j clean
.PHONY: clean

distclean: clean
	@rm -rf build
.PHONY: distclean
