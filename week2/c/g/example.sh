#!/bin/bash
cd ../..
pwd
find . -exec chmod u+x,g-x,o-x {} \;
ls -lR
