
#!/bin/bash

host="localhost"    #Database Host
port="3306"     #Database Port
user="allan"     #Database Username
pass="none"     #Database Password
database="evemu"   #Database name



tables=(`find tables/. -name "*.sql"`)
for i in ${!tables[*]}
do
    echo " >> Installing.. ($(($i+1))/${#tables[@]})  ${tables[$i]}"
    mysql -h ${host} --user=${user} --port=${port} --password=${pass} ${database} < ${tables[$i]}
done