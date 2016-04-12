PROJECT := playavi
SRC     := $(wildcard $(PROJECT)/*.c)
$(eval $(call TARGET_template, $(SRC), $(PROJECT)))
