PROJECT := playogg
SRC     := $(wildcard $(PROJECT)/*.c)
TARGET  := $(OUTPUT_PATH)/$(PREFIX)$(PROJECT)

$(TARGET):
	echo $(SRC)
	$(CC) $(SRC) $(CFLAGS) $(LIBS) -o $@
