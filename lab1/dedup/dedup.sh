#!/bin/bash

# TODO: Type your shell script here

input_directory=$1
declare -A regular_files
# declare -A dups
# declare -A originals

if [ $# == 0 ]
then
    # If there are no arguments given, then we will search for the files in current directory
       set -- *
else
       set -- $@/*
fi

# go through all the files in the directory
for file in "$@"
do
    # iterate through only the regular files
    if [[ -f "$file" ]] 
    then
    # cksum represents the checksum of a file, it has alphanumeric value that uniquely represents the contents of a file.(shown in terminal, but here cksum is a command which takes in an input file)
    # If two file have the same content, then the numerical value of checksum for both the file will be same

        cksum=$(cksum<"$file" | sed 's/ /_/g')                                           
        if [[ ${regular_files[$cksum]} != "" ]] && [[ "${regular_files[$cksum]}" != "$file" ]]
        then
                echo "'$file' is a duplicate of '${regular_files[$cksum]}'" >&2
                temp=`echo ${regular_files[$cksum]}`
                # create soft links of the original file
                rm -f $file # remove the original file as it needs to be replaced by a soft link
                echo ${regular_files[$cksum]} | awk -F'/' '{print $NF}' > tempest
                # temp1 will have the file name of the original file
                temp1=`cat tempest`
                rm tempest
                ln -s $temp1 "$file" # The file names of the duplicates remains same as it was
        else
                regular_files[$cksum]="$file"
                
        fi
    else
        continue
    fi
done

# to create soft links - command below:
# ln -s file_name link_name