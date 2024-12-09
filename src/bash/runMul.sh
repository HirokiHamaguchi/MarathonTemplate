set -e

filename=./src/cpp/main
indir=tools/in
outdir=out
num=100
now=`date "+%Y%m%d%H%M%S"`
scoreFile=./data/$now.txt
cppFile=./data/$now.cpp

cp $filename.cpp $cppFile

echo "now compiling..."
/usr/bin/g++-10 -fdiagnostics-color=always $filename.cpp -o $filename -std=c++17 -Wall -Wextra -DLOCAL -O3

echo "now running..."
for ((i=0; i < $num; i++)); do
    seed=`printf "%04d\n" "$i"`
    echo seed:$seed
    ./tools/target/release/tester $filename < $indir/$seed.txt > $outdir/$seed.txt 2>> $scoreFile
done