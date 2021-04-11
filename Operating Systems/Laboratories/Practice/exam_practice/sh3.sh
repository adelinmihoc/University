#!/bin/bash

# Afisati primele 5 linii si ultimele 5 linii din fisierele de tip text
# din directorul curent; daca un fisier are mai putin de 10 linii, 
# afisati fisierul complet (comenzi: head, tail, find, file, wc)


for F in `ls`; do
  if [ `cat $F | wc -l` -le 10 ]; then
    cat $F
    echo ""
  else 
    cat $F | head
    cat $F | tail
  fi
done
