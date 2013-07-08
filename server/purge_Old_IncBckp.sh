 #!/bin/bash

 BCKDIR="/home/borja/workspace/wx-beta/server"
 cd $BCKDIR;

 BackFile="IncBck".`date --date='-21 day' +%F`;

 rm $BackFile".tar.gz"