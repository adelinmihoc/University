#!/bin/bash

# 1. Display a report showing the full name of all the users currently connected, and the number of processes belonging to each of them.

echo "$(cat who.fake | awk '{print$1}')"
