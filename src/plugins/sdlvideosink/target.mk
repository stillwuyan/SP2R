PROJECT     := sdlvideosink
SRC         := $(wildcard $(PROJECT)/*.c)
EXTFLAGS    := -I$(ROOT)/include/plugins/$(PROJECT)
EXTFLAGS    += $(shell pkg-config --cflags sdl2)
EXTLDFLAGS  := $(shell pkg-config --libs gstreamer-video-1.0 sdl2)
$(eval $(call TARGET_plugin, $(SRC), $(PROJECT), $(EXTFLAGS), $(EXTLDFLAGS)))
