#!/bin/sh

# Usage: split_by_words.sh <text-file>

INFILE=$1
MINCHARS=4

#
# Split file by words | remove words <= MINCHARS | upper case to lower case | sort | remove duplicated words
#
cat $INFILE | tr -s '[[:punct:][:space:]]' '\n' | grep -E ".{$MINCHARS}" | sed 's/[[:upper:]]*/\L&/' | sort | uniq


