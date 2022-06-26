#!/usr/bin/env bash

CLANG_FORMAT_DESIRED_VERSION=11

binary=$(command -v clang-format-$CLANG_FORMAT_DESIRED_VERSION 2>/dev/null)
if [ $? -ne 0 ]; then
    binary=$(command -v clang-format-mp-$CLANG_FORMAT_DESIRED_VERSION 2>/dev/null)
fi
if [ $? -ne 0 ]; then
    binary=$(command -v clang-format 2>/dev/null)
    if [ $? -ne 0 ]; then
        echo "Please install clang-format version $CLANG_FORMAT_DESIRED_VERSION and re-run this script."
        exit 1
    fi
    version=$(clang-format --version)
    if [[ ! $version == *"clang-format version $CLANG_FORMAT_DESIRED_VERSION"* ]]; then
        echo "Please install clang-format version $CLANG_FORMAT_DESIRED_VERSION and re-run this script."
        exit 1
    fi
fi

cd "$(dirname $0)/../"
if [ "$1" = "verify" ] ; then
    if [ $($binary --output-replacements-xml $(find api cli lib | grep -E '\.([hc](pp)?|mm?)$' | grep -v '\#') | grep '</replacement>' | wc -l) -ne 0 ] ; then
        exit 2
    fi
else
    $binary -i $(find api cli lib | grep -E '\.([hc](pp)?|mm)$' | grep -v '\#') &> /dev/null
fi
