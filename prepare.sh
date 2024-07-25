#!/bin/bash
version="1.3.13"
rm -rf deneyapkart-$version.zip
mkdir deneyapkart-$version
cp -r cores/ deneyapkart-$version
cp -r libraries/ deneyapkart-$version
cp -r tools/ deneyapkart-$version
cp -r variants/ deneyapkart-$version
cp boards.txt platform.txt programmers.txt  deneyapkart-$version

zip -r deneyapkart-$version.zip deneyapkart-$version/

rm -rf deneyapkart-$version/