#!/bin/bash

# This is a script to populate the db container with the sql table data.
# Author: James

MARIADB_HOST=db
MARIADB_DATABASE=evemu
MARIADB_PASSWORD=evemu
MARIADB_USER=evemu

# Get script path:
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )"

# Function to determine health of MariaDB container
function waitContainer {
    #Checking if we can actually connect to the container
    while ! mysql -h $MARIADB_HOST -u $MARIADB_USER -p$MARIADB_PASSWORD -e "use evemu;show tables;">/dev/null 2>&1; do
        printf .
        sleep 1
    done
}

# Wait for container to be up and running...
echo "Waiting for DB to start..."
waitContainer evemu_db

# Check if database has already been initialized
numberOfTables=$(mysql -s -N -h $MARIADB_HOST -u $MARIADB_USER -p$MARIADB_PASSWORD -e "SELECT COUNT(DISTINCT table_name) FROM information_schema.columns WHERE table_schema = '$MARIADB_DATABASE';")

if [ $numberOfTables != 0 ]
then
    echo "Database has already been initialized."
    exit
fi

# Install DB tables
tables=(`find /src/sql/tables/. -name "*.sql.gz"`)
for i in ${!tables[*]}
do
    echo " >> Installing.. ($(($i+1))/${#tables[@]})  ${tables[$i]}"
    
    #Check if we were successful executing the query
    success=0
    while [ $success == 0 ];
    
    do
        if zcat ${tables[$i]} | mysql -h ${MARIADB_HOST} --user=${MARIADB_USER} --port=3306 --password=${MARIADB_PASSWORD} ${MARIADB_DATABASE}; then
            echo "Table installed successfully!"
            success=1
        else
            echo "ERROR: Failed to install table, retrying"
            sleep 1
        fi
    done
    
done
