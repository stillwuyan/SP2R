.PHONY: samples cleansamples
samples: build
	make -C samples all
cleansamples:
	make -C samples clean
build:
	@mkdir -p build
