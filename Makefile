.PHONY: all clean samples cleansamples

all: output
	make -C src all
clean:
	make -C src clean

samples: output
	make -C samples all
cleansamples:
	make -C samples clean

output:
	@mkdir -p output/release
	@mkdir -p output/debug
