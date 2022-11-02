NAME = SCITOOLS
ICON = icon.png
DESCRIPTION = "Scientific and general purpose tools"
COMPRESSED = NO
ARCHIVED = YES

CFLAGS = -Wall -Wextra -Oz
CXXFLAGS = -Wall -Wextra -Oz

include $(shell cedev-config --makefile)
