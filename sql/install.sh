#!/bin/bash

host="localhost"    #Database Host
port="3306"     #Database Port
user="evemu"     #Database Username
pass="evemu"     #Database Password

database="evemu"   #Database name

tables=(`find tables/. -name "*.sql.gz"`)
for i in ${!tables[*]}
do
    echo " >> Installing.. ($(($i+1))/${#tables[@]})  ${tables[$i]}"
    zcat ${tables[$i]} | mysql -h ${host} --user=${user} --port=${port} --password=${pass} ${database}

done