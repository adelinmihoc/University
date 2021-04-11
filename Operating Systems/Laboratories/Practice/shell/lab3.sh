#!/bin/bash

# Afișați primele 5 linii și ultimele 5 linii din fișierele de tip text din directorul curent; 
# dacă un fișier are mai puțin de 10 linii, afișați fișierul complet (comenzi: head, tail, find, file, wc).

for file in $(find -maxdepth 1); do
  is_text=$(file -b "$file" | grep -c "text")
  if [ $is_text -eq 1 ]; then
    echo "$(cat "$file" | head -n 5)"
    echo "$(cat "$file" | tail -n 5)"
  fi
done
