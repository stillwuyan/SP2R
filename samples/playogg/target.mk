PROJECT := playogg
SRC     := $(wildcard $(PROJECT)/*.c)
$(eval $(call TARGET_template, $(PROJECT)))
