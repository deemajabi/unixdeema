#!/bin/bash

git add .
git commit -m "F1n3lly"
git push origin main

us="deemajabi"
tk="119f829a6a3c30441dc780edb33c01a71e"
url="http://localhost:8080"
jname="deploy"

curl -u "$us:$tk" "$url/job/$jname/build?token=$tk"
