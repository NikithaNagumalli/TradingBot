#!/bin/bash

# Get the directory of the *symlink* (not where it's called from)
SCRIPT_DIR=$(dirname "$0")

# Extract the project directory from the symlink path
TARGET_PATH=$(readlink -f "$SCRIPT_DIR/run")
PROJECT_DIR=$(dirname "$TARGET_PATH")
cd "$PROJECT_DIR" || exit 1

make "$@"
