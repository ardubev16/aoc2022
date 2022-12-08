#!/usr/bin/env bash

set -e

usage() {
    echo "Usage: $0 [day]"
}

if [ $# -ne 1 ]; then
    usage
    exit 1
fi

day=$(printf "day%02d" "$1")
mkdir "$day"
cp template.cc "$day/$day.cc"
