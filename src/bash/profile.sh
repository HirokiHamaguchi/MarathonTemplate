set -e

filename=./src/cpp/main
input=in/in.txt
output=out/out.txt

echo "now compiling..."
/usr/bin/g++-10 -pg -g -fdiagnostics-color=always $filename.cpp -o $filename -std=c++17 -Wall -Wextra -O3

echo "now running..."
# tools/target/release/tester $filename < $input > $output
$filename < $input > $output
gprof $filename gmon.out # -A
rm gmon.out
