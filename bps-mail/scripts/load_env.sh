#!/bin/bash
# Load environment variables from .env safely

ENV_PATH="$(dirname "$0")/../.env"

if [ -f "$ENV_PATH" ]; then
    export $(grep -v '^#' "$ENV_PATH" | xargs)
else
    echo ".env file not found at $ENV_PATH"
    exit 1
fi

