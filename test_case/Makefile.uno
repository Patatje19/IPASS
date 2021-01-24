#############################################################################
#
# makefile.due common settings for Arduino Uno projects
#
# (c) Wouter van Ooijen (www.voti.nl) 2017
#
# This file is in the public domain.
#
#############################################################################

# SETTINGS FOR ARDUINO ARDUINO DUE PROJECTS
TARGET            := arduino_uno
SERIAL_PORT       ?= COM4
CONSOLE_BAUDRATE  := 2400

# DEFER TO THE MAKEFILE.LINK
include           $(RELATIVE)/Makefile.link
