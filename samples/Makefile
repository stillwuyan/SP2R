include ../common.mk

PREFIX      := sample_
OUTPUT_PATH := ../build
DIRS        := $(shell echo */)
TARGETS     := $(patsubst %/, $(OUTPUT_PATH)/$(PREFIX)%, $(DIRS))

define TARGET_template
SRC     := $(wildcard $(1)/*.c)
TARGET  := $(strip $(OUTPUT_PATH))/$(strip $(PREFIX))$(strip $(1))
$$(TARGET):
	$$(CC) $$(SRC) $$(CFLAGS) $$(LIBS) -o $$@
endef

.PHONY: all clean
all: $(TARGETS)
clean:
	@rm -rf $(TARGETS)

include $(addsuffix target.mk, $(DIRS))
