#!/bin/sh
# BASEDIR="/home/borja/Desktop/tiff";
BASEDIR="/home/borja/pruebas/server";
IndexFile="mysql-bin.index";
BCKDIR="/home/borja/workspace/wx-beta/server"
cd $BASEDIR;

TEMPLIST=./ListOfBins.`date +%s`_$RANDOM;

BackFile="IncBck".`date +%F#%H-%M`;

# cat $IndexFile > $TEMPLIST;
cut -d'/' -f5 $IndexFile > $TEMPLIST;

while read FileBin
	do
		mysqlbinlog $FileBin >> $BCKDIR"/"$BackFile
# 		echo $BackFile
	done < $TEMPLIST

rm -f $TEMPLIST
cd $BCKDIR
# sleep 150
tar czvf $BackFile".tar.gz" $BackFile

