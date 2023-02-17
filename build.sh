#!/bin/bash

mkdir build
cd build


echo "============ BUILD START ============"
cmake3 ../
make -j4

echo "============ BUILD END ============"
echo ""

cd src/
cp mtfind ../../

cd ../../config
cp config.txt ../

cd ../
rm -r build
echo ""

echo "============ MTFIND START ============"
./mtfind -n config.txt

echo "============ MTFIND END ============"
echo ""

echo "============ RESULT ============"
cat output.txt

