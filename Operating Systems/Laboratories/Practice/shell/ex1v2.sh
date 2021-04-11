#!/bin/bash


# Display a report showing the full name of all the users currently connected, and the number of processes belonging to each of them.

usernames=$(cat who.fake | cat who.fake | awk '{print $1}')

for user in $usernames; do
  echo "$user $(cat ps.fake | grep -o "^$user" | wc -l)"
#  echo "$(cat ps.fake | grep "^$user" | wc -l)"
done
