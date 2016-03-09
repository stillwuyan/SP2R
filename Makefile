.PHONY: samples cleansamples
samples: output
	make -C samples all
cleansamples:
	make -C samples clean
output:
	@mkdir -p output/release
	@mkdir -p output/debug
