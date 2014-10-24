#!/bin/bash
#######################
# Edit Settings Below #
#######################

x
    THIS SHOULD TAKE COMMAND LINE ARGS FOR THESE:igh ghf hgh

host="localhost"    #Database Host
port="3306"        #Database Port
user="evemu"        #Database Username
pass="changeme"        #Database Password
database="evemu"    #Database name

#######################
# Dont Edit Past Here #
#######################


#######################
#      Main Loop      #
#######################
until [ "${option}" = "x" ]; do
    clear
    echo "EVEMU Database Setup"
    echo " i - Install Clean Database"
    echo " u - More Options Soon"
    echo " x - Exit"
    echo
    read -p " Enter option:  " option

    if [ "${option}" = "i" ]; then
        echo "UNZIP ALL .ZIP archives in /ofic-updates directory,"
        read -p "then press any key to continue..."
        echo "[+] Entering database setup.."
        
	echo "Droping database 'evemu'..."
	mysql -h ${host} --user=${user} --password=${pass} -v -e "drop database ${database};"
	echo "Creating database 'evemu'..."
	mysql -h ${host} --user=${user} --password=${pass} -v -e "create database ${database};"

	echo "[+] Searching for base database files.."

        filearray=(`find . -name "*mysql5-v1.sql"`)

        if [ ${#filearray[@]} -gt 0 ]; then
        echo
        echo "[+] Select the base database to use"
        for index in ${!filearray[*]}
        do
        printf "%4d: %s\n" $index ${filearray[$index]}
        done
        read -p " Enter option:  " basefile

        if [ ${#filearray[@]} -gt ${basefile} ]; then
            echo 
        echo "[+] [1] Importing base database (${filearray[$basefile]}) please wait.."
        
        #TODO Add a check for gzip

        mysql -h ${host} --user=${user} --port=${port} --password=${pass} ${database} < "${filearray[$basefile]}"

        echo "[+] [1] Base database complete"
        
        echo "[+] [2] Importing dynamic dump"
        mysql -h ${host} --user=${user} --port=${port} --password=${pass} ${database} < "evemu_dynamic-dump.sql"
        echo "[+] [2] Importing dynamic dump Complete"

        echo "[+] [3] Importing static dump"
        mysql -h ${host} --user=${user} --port=${port} --password=${pass} ${database} < "evemu_static-dump.sql"
        echo "[+] [3] Importing static dump Complete"

        echo "[+] [4] Importing ofic dump"
        oficarray=(`find ofic-updates/. -name "*.sql"`)
        for index in ${!oficarray[*]}
        do
            echo "[+] [4] Ofic Dumps ($(($index+1))/${#oficarray[@]}) - ${oficarray[$index]}"
            mysql -h ${host} --user=${user} --port=${port} --password=${pass} ${database} < "${oficarray[$index]}"
        done

        echo "[+] [4] Importing ofic dump Complete"

        echo "[+] [5] Primeing Database"
        mysql -h ${host} --user=${user} --port=${port} --password=${pass} ${database} < "prime_db.sql"
        echo "[+] [5] Primeing Database Complete"

        echo "[+] [5] Live updates Database"
        mysql -h ${host} --user=${user} --port=${port} --password=${pass} ${database} < "liveupdates.sql"
        echo "[+] [5] Live updates Database Complete"

        else
            echo 
            echo "[-] The number you selected was not found"
            echo 
        fi

    else
        echo
        echo "[-] Please download a base database"
        echo
    fi
    fi

    if [ "${option}" != "x" ]; then
        echo
    read -p " Press any key to continue..."
    echo
    fi
done
