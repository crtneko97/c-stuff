chomd +x /your/path/run_work.sh
chomd +x /your/path/view_hours.sh

sudo ln -s /home/username/your/path/run_work.sh /usr/local/bin/work
sudo ln -s /home/username/your/path/view_hours.sh /usr/local/bin/view_hours

these steps are made so that i can more easily track the hours i work.

start by making the shellscripts executable with the first two examples.

second create symbolic links (i named them work & view_hours, but you can call them whatever you prefer)
inside your usr/local/bin directory so you can globaly run the scripts.



