#!/bin/bash

# Sa se scrie un fisier de comenzi care va afisa toate fisierele dintr-un director
# si din subdirecoarele acestuia asupra carora au drepturi de scriere toate cele
# trei categorii de utilizatori.
# Aceste fisiere vor fi apoi redenumite, adaugandu-se sufixul .all (comenzi: find, mv)


find dir -type f | while read F; do
if [ $(ls -l $F | grep "^..w..w..w." | wc -l) -gt 0 ]; then
    mv $F $F.all
  fi
done
