#!/bin/bash

# Display a report showing the full name of all the users currently
# connected, and the number of processes belonging to each of them.

declare -A user_name
user_name=$(cat who.fake | awk '{print $1}')
# echo "$user_name"

for user in $user_name; do
	echo $user $(cat ps.fake | grep "^$user" | wc -l)
done


