#!/bin/bash

if [ -z "$(which clang-format)" ]
then
    brew install clang-format
fi

DEST=.git/hooks/pre-commit

ln -s -f $(pwd)/hooks/pre-commit $DEST

