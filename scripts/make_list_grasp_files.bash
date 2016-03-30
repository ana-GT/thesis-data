#!/bin/bash

DATA_DIR="/home/ana/Research/thesis-data/ch3_9_data"
DIR="${DATA_DIR}/${1}"

cd $DATA_DIR;

ALL_OBJECTS_OUTPUT_FILE="${DATA_DIR}/all_objects_graspfiles.txt"

for i in $( ls ); do

    # Each folder with shape
    if [ -d "${i}" ]; then

      FOLDER="$DATA_DIR/$i"
      OUTPUT_FILE="$DATA_DIR/${i}_graspfiles.txt"

      echo "Folder: $FOLDER"
      cd $FOLDER;
      for file in `find . -type f -name "${i}_*.txt"`; do
          each_file=$(echo "$file" | cut -f 2 -d '/');
          each_file_fullpath="$FOLDER/$each_file";
          echo "$each_file_fullpath" >> $OUTPUT_FILE
      done
      cd ..

      echo "${i} ${OUTPUT_FILE}" >> ${ALL_OBJECTS_OUTPUT_FILE}
    fi
done 
