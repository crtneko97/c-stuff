#!/bin/bash

# Get absolute path to project root
ROOT_DIR="$(cd "$(dirname "$0")/.." && pwd)"

# Load env
source "$ROOT_DIR/.env"

# Prompt for recipient
read -p "Send to: " RECIPIENT

# Make sure emails folder exists inside bps-mail
mkdir -p "$ROOT_DIR/emails"

# Email filename
FILENAME="$ROOT_DIR/emails/email_$(date +%Y%m%d_%H%M%S).txt"

# Current date
DATE=$(date -R)

# Create the email file
cat > "$FILENAME" <<EOF
Date: $DATE
From: $SMTP_NAME <$SMTP_USER>
To: $RECIPIENT
Subject: 

<Write your message here>

EOF

# Open in Vim
vim "$FILENAME"

# Auto-send
echo ""
echo "Sending email..."
"$ROOT_DIR/bin/send_mail" "$RECIPIENT" "$FILENAME"

