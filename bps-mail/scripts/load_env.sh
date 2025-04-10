#!/bin/bash

# FULL path to your .env file
ENV_PATH="/home/dunaken/.bps/dev/bps/bps-work/bps-c/bps-mail/.env"

if [ -f "$ENV_PATH" ]; then
  export $(grep -v '^#' "$ENV_PATH" | xargs)
else
  echo ".env file not found at $ENV_PATH"
  exit 1
fi
