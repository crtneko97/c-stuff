f*** the ascii banner

A simple terminal-based email sender using Vim, C, and libcurl.

- Compose emails in Vim
- Sends emails using gmail SMTP (with App password)
- Bash, Vim, C, and libCurl





Requirements

- GCC
- `libcurl`
- `make`
- `vim`
- Gmail account with [App Password]
- Fish or Bash shell, in my case i use fish.

run make.



Create your own .env file in the root of the project,
SMTP_USER=<your_email@gmail.com>
SMTP_NAME=<your_name>
SMTP_PASS=<you_app_pass>   ***Don't use yourt gmail password, Use a Gmail app password***
SMTP_SERVER=//smtp.gmail.com:465



Load enviorment variables

if your using Bash or Zsh:

bash scripts/load_env.sh


if you're using Fish:

for line in (cat .env)
    if not string match -qr '^#' $line
        set parts (string split "=" $line)
        set -gx $parts[1] $parts[2]
    end
end



run the script to send an email.

./scripts/new_email.sh



---


This project is licensed under the [MIT License](./LICENSE).

Created by **Battle Programmer Simon** (Simon Kern) — [simon.f.kern@gmail.com](mailto:simon.f.kern@gmail.com)

