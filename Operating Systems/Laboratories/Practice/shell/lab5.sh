#!/bin/bash

# Pentru fiecare parametru din linia de comandă: dacă e fișier, se vor afișa numele, numărul de caractere și de linii din el 
# (�n această ordine), iar dacă e director, numele și c�te fișiere conține (inclusiv �n subdirectoare). (comenzi: test, wc, awk, find).

while [ $# -gt 0 ]; do
  if [[ -d $1 ]]; then
    echo "directory $1 has $(find "$1" | wc -l) file and subdirectories"
  elif [[ -f $1 ]]; then
    echo " file $1 has $(cat "$1" | wc -m) characters and $(cat "$1" | wc -l) lines "
  else
    echo "not a file nor directory"
  fi
  shift 1
done
