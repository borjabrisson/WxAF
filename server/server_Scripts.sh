 #!/bin/bash
 rsync -avPz --delete --force --exclude error.*   /var/log/mysql/   /home/borja/pruebas/server
Bck_DIR="/home/borja/pruebas/bck"
week=`date +%Y`-`date +%V`;
#  if [ "$$(ls ${Build} | grep $${week}  )" ]; then mkdir $Bck_DIR/$week; fi


 if [ -d  $Bck_DIR/$week ];
then

else
	mkdir $Bck_DIR/$week
fi


#  Obtención de sentencias SQL a través de ficheros binarios.
#  mysqlbinlog mysql-bin.00000[1-5]* >> today

# Ralización de copia de seguridad completa, privia fusión de binarios, y reseteo de ficheros binarios.
# mysqldump --single-transaction  --flush-logs --master-data=2  --all-databases --delete-master-logs --add-locks --dump-date > backup_sunday_1_PM.sql