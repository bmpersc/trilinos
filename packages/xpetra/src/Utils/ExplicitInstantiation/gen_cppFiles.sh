#!/bin/bash

# internal field separator to figure out where to split words
IFS=$'\n'

classListDir=../ClassList/

for i in LO-GO-NO SC-LO-GO-NO GO-LO-GO-NO
  do

  classList=$classListDir/$i.classList
  tmpl=$i.tmpl

  for className in `cat $classList | grep -v ^\# | cut -d "-" -f1 | sed 's/ //'`
    do

    if ! grep -q -x $className $classListDir/EI-Exceptions.classList
        then

        condition=$(cat $classList | grep "^$className -" | cut -d "-" -f2-)

        if [ -n "$condition" ]; then
            conditionOpen1=$(echo "#include \\\"Xpetra_ConfigDefs.hpp\\\"")
            conditionOpen2=$(echo $condition | sed 's/^[ ]*//' | sed 's/\&/\\\&/g')
            conditionClose="#endif"
        else
            conditionOpen1=""
            conditionOpen2=""
            conditionClose=""
        fi
        
        if [ $i == "GO-LO-GO-NO" ]; then
            OUTFILE=Xpetra_${className}_go.cpp
        else
            OUTFILE=Xpetra_$className.cpp
        fi

        cat $tmpl \
            | sed "s/\$TMPL_CLASS/$className/g" \
            | sed "s/\$TMPL_CONDITION_OPEN1/$conditionOpen1/g" \
            | sed "s/\$TMPL_CONDITION_OPEN2/$conditionOpen2/g" \
            | sed "s/\$TMPL_CONDITION_CLOSE/$conditionClose/g" \
            > $OUTFILE
    fi

  done

done
