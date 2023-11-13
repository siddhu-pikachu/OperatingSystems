#!/bin/bash

# give the first argumenent as responses.csv and second one as students_list.csv
# The output file is output_file.csv
responses_csv=$1
students_list_csv=$2

if [ $# == 2 ]
then
        # part-1

	cut -d"," -f 3,4 ${responses_csv} | sed 's/",""//g' | sed 's/"//g' | sed 1d | sed 's/,/_/g' > lab_groups.csv
	awk -F'_' '{
                    if ($NF == $1) print $1 > "lab_groups.csv";
                    else if ($1 < $2) print $1"_"$2 > "lab_groups.csv"; 
                    else print $2"_"$1 > "lab_groups.csv";
                    }' lab_groups.csv

        # part-2
        echo "">&2
        echo "Duplicate roll numbers :" >&2
        awk -F'_' '
                        BEGIN {
                                print "" > "new_lab_groups.csv";
                                print "" > "dups_id.csv";
                        }
                        {
                                rollNos[$1]++;
                                if($NF!=$1)
                                {
                                        rollNos[$2]++;
                                }
                        }
                        {
                                if($NF!=$1)
                                {
                                        if(rollNos[$1]>1 && rollNos[$2]>1)
                                        {
                                                next;
                                        }
                                        else if(rollNos[$1]>1)
                                        {
                                                print $2 >> "new_lab_groups.csv";
                                        }
                                        else if(rollNos[$2]>1)
                                        {
                                                print $1 >> "new_lab_groups.csv";
                                        }
                                        else
                                        {
                                                print $1"_"$2 >> "new_lab_groups.csv";
                                        }
                                }
                                else
                                {
                                        if(rollNos[$1]>1)
                                        {
                                                next;
                                        }
                                        else
                                        {
                                                print $1 >> "new_lab_groups.csv";
                                        }
                                }
                        }
                        END {
                                flag=0
                                for(i in rollNos)
                                {
                                        if(rollNos[i]>1)
                                        {
                                                print ERROR i;
                                                print i >> "dups_id.csv";
                                                flag++;
                                        }
                                        print i > "freq.csv";
                                }
                                if(flag > 0) print ERROR "The above are duplicate roll number(s) (there can be only one group in which a student can be put)";
                        }
        ' lab_groups.csv
        # remove lab_groups.csv file
        sed '/^$/d' new_lab_groups.csv > new_lab_groups_temp.csv # removing whitespaces using sed from new_lab_groups.csv file
        mv new_lab_groups_temp.csv new_lab_groups.csv

        sed '/^$/d' dups_id.csv > dups_id_temp.csv
        mv dups_id_temp.csv dups_id.csv

        # lab_groups.csv has duplicates and new_lab_groups.csv does not have duplicates

        # part-3 finding student roll numbers who have not registered for the course but still have filled the form
        echo "">&2
        echo "Invalid group ids :">&2
        awk '
        BEGIN {
                print "" > "checker.csv";
        }
        FNR==NR {
                check[$1]++;
        }
        FNR!=NR {
                if(check[$1]==0)
                {
                        print $1 >> "checker.csv";
                }
        }
        ' ${students_list_csv} freq.csv
        sed '/^$/d' checker.csv > checker_temp.csv
        mv checker_temp.csv checker.csv

        # part-3 printing the group-id

        awk -F'_' '
        FNR==NR {
                unregistered[$1]++;
        }
        FNR!=NR {
                if($NF==$1)
                {
                        if(unregistered[$1]==0)
                        {
                                print $1 >> "new_temp.csv";
                        }
                        else
                        {
                                # print "Not valid : "$1;
                                next;
                        }
                }
                else
                {
                        if(unregistered[$1]>0 || unregistered[$2]>0)
                        {
                                # print $1"_"$2;
                                next;
                        }
                        else
                        {
                                print $1"_"$2 >> "new_temp.csv";
                        }
                }
        }
        ' checker.csv lab_groups.csv
        mv new_temp.csv lab_groups.csv


        awk -F'_' '
        BEGIN {
                flag=0;
        }
        FNR==NR {
                unregistered[$1]++;
        }
        FNR!=NR {
                if($NF==$1)
                {
                        if(unregistered[$1]==0)
                        {
                                print $1 >> "new_temp.csv";
                        }
                        else
                        {
                                print ERROR $1" ("$1" is invalid (unregistered for the course))";
                                next;
                        }
                }
                else
                {
                        if(unregistered[$1]>0 && unregistered[$2]>0)
                        {
                                print ERROR $1"_"$2" ("$1" and "$2" are invalid (unregistered for the course))";
                                flag++;
                                next;
                        }
                        else if(unregistered[$1]>0)
                        {
                                print ERROR $1"_"$2" ("$1" is invalid (unregistered for the course))";
                                flag++;
                        }
                        else if(unregistered[$2]>0)
                        {
                                print ERROR $1"_"$2" ("$2" is invalid (unregistered for the course))";
                                flag++;
                        }
                        else
                        {
                                print $1"_"$2 >> "new_temp.csv";
                        }
                }
        }
        END {
                if(flag>0) print ERROR "The above group id(s) are invalid";
                else print ERROR "There are no invalid group ids";
        }
        ' checker.csv new_lab_groups.csv
        mv new_temp.csv new_lab_groups.csv
        
        # part-4 finding the students who have registered but have not filled the form

        echo "">&2
        echo "Student roll numbers of who have registered but have not filled the form">&2

        awk '
                FNR==NR {
                        registered[$1]++;
                }
                FNR!=NR {
                        temp_registered[$1]++;
                }
                END {
                        flag=0;
                        for(i in registered)
                        {
                                if(registered[i]>0 && temp_registered[i]==0)
                                {
                                        print i;
                                        flag++;
                                }
                        }
                        if(flag>0) print ERROR "The above student(s) have registered for the course but have not filled the form (not part of any group)";
                        else print ERROR "There is no student who have registered for the course but have not filled the form (not part of any group)";
                }
        ' ${students_list_csv} freq.csv

elif [ $# -gt 2 ]
then
        echo "too many arguments!"
else
        echo "not enough arguments!"
fi

rm -f checker.csv
rm -f freq.csv
awk -F'_' '
BEGIN {
        print "" > "output_file.csv"
}
FNR==NR {
        dups[$1]++;
}
FNR!=NR {
        if($NF==$1)
        {
                if(dups[$1]>0)
                {
                        print $1"                       ("$1" is a duplicate Roll number id)" >> "output_file.csv";
                }
                else if(dups[$1]==0)
                {
                        print $1 >> "output_file.csv";
                }
        }
        else
        {
                if(dups[$1]>0 && dups[$2]>0) print $1"_"$2 "            ("$1" and "$2" are duplicate Roll number ids)" >> "output_file.csv";
                else if(dups[$1]>0) print $1"_"$2 "             ("$1" is a duplicate Roll number id)" >> "output_file.csv";
                else if(dups[$2]>0) print $1"_"$2 "             ("$2" is a duplicate Roll number id)" >> "output_file.csv";
                else print $1"_"$2 >> "output_file.csv";
        }
}
' dups_id.csv lab_groups.csv
sed '/^$/d' output_file.csv > output_file_temp.csv
mv output_file_temp.csv output_file.csv
rm -f dups_id.csv
rm -f lab_groups.csv
rm -f new_lab_groups.csv 

# The output file is output_file.csv