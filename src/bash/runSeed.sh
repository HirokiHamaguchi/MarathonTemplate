set -e

filename=./src/cpp/main
indir=tools/in
outdir=out

echo "now compiling..."
/usr/bin/g++-10 -fdiagnostics-color=always $filename.cpp -o $filename -std=c++17 -Wall -Wextra -O3 -I/usr/include/eigen3

YELLOW="\033[33m"
RESET="\033[0m"
read -p "$(echo -e $YELLOW"seed: "$RESET)" seed
seed=$(( seed ? seed : 0 ))
seed=`printf "%04d\n" "${seed}"`

echo "now running..."
./tools/target/release/tester $filename < $indir/$seed.txt > $outdir/$seed.txt