include ../common.mk

PREFIX      := sample_
OUTPUT_PATH := ../build
DIRS        := $(shell echo */)
TARGETS     := $(patsubst %/, $(OUTPUT_PATH)/$(PREFIX)%, $(DIRS))

.PHONY: all clean
all: $(TARGETS)
clean:
	@rm -rf $(TARGETS)

include $(addsuffix target.mk, $(DIRS))
