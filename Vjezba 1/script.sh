for i in {1..20}
do
    echo -e "\n\n $1 - $i:"
    time ./$1 $2 $3 $4;
done