#!/bin/bash

if [ -z "$(which clang-format)" ]
then
    if [[ "$OSTYPE" == "darwin"* ]]; then
            brew install clang-format
    elif [[ "$OSTYPE" == "linux-gnu"* ]]; then
            sudo apt install clang-format
    else
            echo "Unsupported OS!"
    fi
fi

DEST=.git/hooks/pre-commit

ln -s -f $(pwd)/hooks/pre-commit $DEST

