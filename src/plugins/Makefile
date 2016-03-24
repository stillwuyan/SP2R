ROOT        := ../..
include $(strip $(ROOT))/build/common.mk

OUTPUT_PATH := $(strip $(ROOT))/$(strip $(OUTPUT))/plugins
DIRS        := $(filter-out tools/, $(shell echo */))

define TARGET_plugin
TARGET  := $(strip $(OUTPUT_PATH))/libgst$(strip $(1)).so
TARGETS += $$(TARGET)

CFLAGS  += -fPIC
LDFLAGS += -shared

$$(TARGET):
	$$(CC) $$(SRC) $$(CFLAGS) $$(LDFLAGS) $$(LIBS) -o $$@
endef

.PHONY: help all clean
help:
	@echo 'Usage: make [options]'
	@echo 'Options:'
	@echo ' help            Display this information'
	@echo ' all             Build all plugins'
	@echo ' clean           Clean all plugins'

include $(addsuffix target.mk, $(strip $(DIRS)))

all: $(OUTPUT_PATH) $(TARGETS)

clean:
	rm -rf $(TARGETS)

$(OUTPUT_PATH):
	mkdir -p $@
