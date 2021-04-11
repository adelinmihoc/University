#!/bin/bash

# Sa se scrie un fisier de comenzi care va afisa toate fisierele dintr-un director si din subdirectoarele acestuia
# asupra carora au drepturi de scriere toate cele trei categorii de utilizatori. Aceste fisiere vor fi apoi redenumite,
# adaugandu-se sufixul .all (comenzi: find -perm, mv).

for file in $(find dir -perm -ugo=w -type f); do
  $(mv "$file" $(echo "$file.all")) 
done 
