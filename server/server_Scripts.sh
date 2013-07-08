 #!/bin/bash
 rsync -avPz --delete --force --exclude error.*   /var/log/mysql/   /home/borja/pruebas/server

#  mysqlbinlog mysql-bin.00000[1-5]* >> today
