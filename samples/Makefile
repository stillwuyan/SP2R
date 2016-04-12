ROOT        := ..
include $(strip $(ROOT))/build/common.mk

OUTPUT_PATH := $(strip $(ROOT))/$(strip $(OUTPUT))/sample
DIRS        := $(shell echo */)

# TARGET_template(SRC, TARGET)
define TARGET_template
.PHONY: $(2)
TARGETS += $(2)
$(2): $(1)
	$$(CC) $(1) $$(CFLAGS) $$(LDFLAGS) -o $$(strip $$(OUTPUT_PATH))/$$(strip $$@)
endef

.PHONY: help all clean
help:
	@echo 'Usage: make [options]'
	@echo 'Options:'
	@echo ' help            Display this information'
	@echo ' all             Build all samples'
	@echo ' clean           Clean all samples'

include $(addsuffix target.mk, $(strip $(DIRS)))

all: $(OUTPUT_PATH) $(TARGETS)

clean:
	rm -rf $(OUTPUT_PATH)

$(OUTPUT_PATH):
	mkdir -p $@
