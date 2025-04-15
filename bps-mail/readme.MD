# VIM MAIL – Terminal Email Client

A simple terminal-based email sender built with **Vim**, **C**, and **libcurl**.

## Features

- Compose emails using Vim.
- Send emails via Gmail SMTP (using an App Password).
- Built with Bash, Vim, C, and libcurl.

## Requirements

Before running the project, ensure you have the following installed:

- [GCC](https://gcc.gnu.org/)
- `libcurl`
- `make`
- [Vim](https://www.vim.org/)
- A Gmail account with an [App Password](https://support.google.com/accounts/answer/185833)
- A compatible shell (Bash or [Fish](https://fishshell.com/); I personally use Fish).

## Installation & Setup

1. **Clone and Build:**
   - Clone the repository and navigate to the project root.
   - Build the project by running:
   
     ```bash
     make
     ```

2. **Create the Environment File:**
   - In the project root, create a `.env` file with the following content:
   
     ```env
     SMTP_USER=<your_email@gmail.com>
     SMTP_NAME=<your_name>
     SMTP_PASS=<your_app_pass>   # Use a Gmail app password instead of your regular Gmail password!
     SMTP_SERVER=smtp.gmail.com:465
     ```

3. **Load Environment Variables:**
   - **For Bash or Zsh Users:**
     
     Run the following command to load the environment variables:
     
     ```bash
     bash scripts/load_env.sh
     ```
     
   - **For Fish Shell Users:**
     
     Use the following snippet in your terminal to load the environment variables:
     
     ```fish
     for line in (cat .env)
         if not string match -qr '^#' $line
             set parts (string split "=" $line)
             set -gx $parts[1] $parts[2]
         end
     end
     ```

## Usage

After completing the setup and loading your environment variables, run the following script to compose and send an email:

```bash
./scripts/new_email.sh

License

This project is licensed under the MIT License.
Author

Battle Programmer Simon (Simon Kern)
simon.f.kern@gmail.com
