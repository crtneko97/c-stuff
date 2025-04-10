#!/bin/bash

# Set the absolute path to your project
PROJECT_PATH="/home/dunaken/.bps/dev/bps/bps-work/bps-c/bps-mail"

# Move to that directory
cd "$PROJECT_PATH" || {
  echo "❌ Could not cd into $PROJECT_PATH. Exiting."
  exit 1
}

# Load environment variables
bash scripts/load_env.sh || {
  echo "❌ Failed to load environment variables."
  exit 1
}

# Run the email composer
./scripts/new_email.sh
