#!/bin/bash

git add .
git commit -m "F1n3lly"
git push origin main

us="your-user"
tk="your-token"
url="your-url"
jname="your-job"

curl -u "$us:$tk" "$url/job/$jname/build=token?$tk"
