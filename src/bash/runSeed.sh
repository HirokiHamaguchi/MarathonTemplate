set -e

filename=./src/cpp/main
input=in
output=out/out.txt

echo "now compiling..."
/usr/bin/g++-10 -fdiagnostics-color=always $filename.cpp -o $filename -std=c++17 -Wall -Wextra -D_GLIBCXX_DEBUG -Dhari64

YELLOW="\033[33m"
RESET="\033[0m"
read -p "$(echo -e $YELLOW"seed: "$RESET)" seed
seed=$(( seed ? seed : 0 ))
seed=`printf "%04d\n" "${seed}"`

echo "now running..."
tools/target/release/tester $filename < $indir/$seed.txt > $output