CC          := gcc
CFLAGS      := -Wall -Werror $(shell pkg-config --cflags gstreamer-1.0)
LDFLAGS     := $(shell pkg-config --libs gstreamer-1.0)

ifdef DEBUG
CFLAGS      += -g
OUTPUT      := output/debug
else
OUTPUT      := output/release
endif
