#!/bin/sh
# BASEDIR="/home/borja/Desktop/tiff";
BASEDIR="/home/borja/pruebas/server";
IndexFile="mysql-bin.index";
BCKDIR="/home/borja/workspace/wx-beta/server"
cd $BASEDIR;

TEMPLIST=./ListOfBins.`date +%s`_$RANDOM;

BackFolder="IncBck".`date  +%F`;

mkdir $BCKDIR"/"$BackFolder

# cat $IndexFile > $TEMPLIST;
cut -d'/' -f5 $IndexFile > $TEMPLIST;

while read FileBin
	do
		cp $FileBin  $BCKDIR"/"$BackFolder
# 		echo $BackFile
	done < $TEMPLIST

rm -f $TEMPLIST
cd $BCKDIR
# sleep 150
tar czvf $BackFolder".tar.gz" $BackFolder
rm -rf  $BackFolder
# date --date='+7 day'


