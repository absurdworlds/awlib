#!/usr/bin/sh
# Generate tags file
ctags --languages=C,C++ -R -o ./.tmp/tags ./include ./source
