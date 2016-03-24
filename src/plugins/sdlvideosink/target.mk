PROJECT := sdlvideosink
SRC     := $(wildcard $(PROJECT)/*.c)
EXTLIBS := $(shell pkg-config --libs gstreamer-video-1.0)

$(eval $(call TARGET_plugin, $(PROJECT), $(EXTLIBS)))
