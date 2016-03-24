PROJECT := sdlvideosink
SRC     := $(wildcard $(PROJECT)/*.c)

$(eval $(call TARGET_plugin, $(PROJECT)))
