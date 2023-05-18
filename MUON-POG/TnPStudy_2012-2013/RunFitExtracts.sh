#!bin/bash

rm -rf fitPlots
mkdir fitPlots
export dir=`pwd`
echo $dir
sed -i "s?DIRPATH?$dir?g" ExtractFitCanvas.C
root.exe -l -b -q ExtractFitCanvas.C+
source ReNameFitCanvasses.sh
