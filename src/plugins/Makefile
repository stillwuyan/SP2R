ROOT        := ../..
include $(strip $(ROOT))/build/common.mk

OUTPUT_PATH := $(strip $(ROOT))/$(strip $(OUTPUT))/plugins
DIRS        := $(filter-out tools/, $(shell echo */))

CFLAGS      += -fPIC
LDFLAGS     += -shared

# TARGET_plugin(SRC, TARGET, CFLAGS, LDFLAGS)
define TARGET_plugin
.PHONY: $(1)
TARGETS     += $(2)
$(2): CFLAGS += $(3)
$(2): LDFLAGS += $(4)
$(2): $(1)
	$$(CXX) $(1) $$(CFLAGS) $$(LDFLAGS) -o $$(strip $$(OUTPUT_PATH))/lib$$(strip $$@).so
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
