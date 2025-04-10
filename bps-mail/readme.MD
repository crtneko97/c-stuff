
   VIM-MAIL — Battle Programmer Simon
 
   A simple terminal-based email sender using Vim, C, and libcurl.
 
   - Compose emails in Vim
   - Sends via Gmail SMTP (App Password required)
   - Tools: Bash, Vim, C, libcurl
 
   Requirements:
    - GCC
    - libcurl
    - make
    - vim
    - Gmail (with App Password)
    - Fish or Bash shell (I use fish)
 
   Setup:
    1. Run `make`
    2. Create a `.env` file in the project root:
 
       SMTP_USER=<your_email@gmail.com>
       SMTP_NAME=<your_name>
       SMTP_PASS=<your_app_password>   // Do NOT use your regular Gmail password
       SMTP_SERVER=smtp.gmail.com:465
 
   3. Load environment variables:
 
      For Bash/Zsh:
        bash scripts/load_env.sh
      For Fish:
      
       for line in (cat .env)
           if not string match -qr '^#' $line
               set parts (string split "=" $line)
               set -gx $parts[1] $parts[2]
           end
       end
 
   4. Send an email:
       ./scripts/new_email.sh
 
   License: MIT
 
   Created by Battle Programmer Simon (Simon Kern)
   Contact: simon.f.kern@gmail.com
