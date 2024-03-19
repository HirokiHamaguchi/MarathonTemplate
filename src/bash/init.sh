# $ source init.sh

if [ -f src/cpp/viewer.hpp.gch ]; then
    echo "viewer.hpp.gch already exists"
else
    echo "now precompiling viewer.hpp..."
    /usr/bin/g++-10 -x c++-header -g -std=c++17 -Dhari64 -Wall -Wextra -fdiagnostics-color=always -D_GLIBCXX_DEBUG src/cpp/viewer.hpp
fi

export DISPLAY=:0.0
alias ojt='bash src/bash/runSeed.sh'
cat src/bash/init.sh
