HXCMOD_MOD_DIR := $(USERMOD_DIR)

# Add all C files to SRC_USERMOD.
SRC_USERMOD += $(HXCMOD_MOD_DIR)/hxcmod.c
SRC_USERMOD += $(HXCMOD_MOD_DIR)/hxcmod_mp.c

# We can add our module folder to include paths if needed
# This is not actually needed in this example.
CFLAGS_USERMOD += -I$(HXCMOD_MOD_DIR)
CHXCMOD_MOD_DIR := $(USERMOD_DIR)
