set -e

filename=./src/cpp/main
indir=in
outdir=out
num=100

echo "now compiling..."
/usr/bin/g++-10 -fdiagnostics-color=always $filename.cpp -o $filename -std=c++17 -Wall -Wextra -O3

echo "now running..."

for ((i=0; i < $num; i++)); do
    seed=`printf "%04d\n" "$i"`
    echo seed:$seed
    tools/target/release/tester $filename < $indir/$seed.txt > $outdir/$seed.txt
done