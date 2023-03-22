#!/bin/bash
git add .
# git commit . -m  $( [[ $1 = "" ]] && echo -ne "update sample code" || echo -ne $1 )
git commit . -m "update"
git push origin master 
