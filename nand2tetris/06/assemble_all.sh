#!/bin/bash
find . -type f -name "*asm" -print|./assembler/cmake-build-debug/assembler
find . -type f -name "*hack" -exec cp {} ~/Downloads/archived/ \;
