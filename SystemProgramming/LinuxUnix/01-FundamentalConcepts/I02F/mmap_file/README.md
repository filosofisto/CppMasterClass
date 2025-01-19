# Instructions

## Create the file with 1024 bytes with zeros

dd if=/dev/zero of=./myfile bs=1 count=1024

## Execute program

./app ./myfile hello

## Check file

od -c -w8 ./myfile

