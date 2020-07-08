#!/bin/bash
pwd
find . -exec chmod u+rwx,g-rwx,o-rwx {} \;
ls -lR






