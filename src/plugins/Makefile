ROOT        := ../..
include $(strip $(ROOT))/build/common.mk

OUTPUT_PATH := $(strip $(ROOT))/$(strip $(OUTPUT))/plugins
DIRS        := $(filter-out tools/, $(shell echo */))

CFLAGS      += -fPIC
LDFLAGS     += -shared

# TARGET_plugin(SRC, TARGET, CFLAGS, LDFLAGS)
define TARGET_plugin
TARGET      := $$(strip $$(OUTPUT_PATH))/lib$$(strip $(2)).so
TARGETS     += $$(strip $$(OUTPUT_PATH))/lib$$(strip $(2)).so
$$(TARGET): CFLAGS += $(3)
$$(TARGET): LDFLAGS += $(4)
$$(TARGET): $(1)
	$$(CXX) $(1) $$(CFLAGS) $$(LDFLAGS) -o $$@
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
	rm -rf $(OUTPUT_PATH)

$(OUTPUT_PATH):
	mkdir -p $@
