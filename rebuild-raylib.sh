#!/bin/bash
cd ./raylib && find | cpio -o -H newc | gzip -9 > ../raylib.gz
