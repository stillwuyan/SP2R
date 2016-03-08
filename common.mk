CC          = gcc
CFLAGS      = $(shell pkg-config --cflags gstreamer-1.0)
LIBS        = $(shell pkg-config --libs gstreamer-1.0)
