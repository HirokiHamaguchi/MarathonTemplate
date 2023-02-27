# $ source init.sh

if [ -f src/cpp/viewer.hpp.gch ]; then
    echo "viewer.hpp.gch already exists"
else
    echo "now precompiling viewer.hpp..."
    /usr/bin/g++-10 -x c++-header -g -std=c++17 -Dhari64 -Wall -Wextra -fdiagnostics-color=always -D_GLIBCXX_DEBUG viewer.hpp
fi

export DISPLAY=:0.0
conda activate Marathon
alias cp='cp -i'
alias mv='mv -i'
alias rm='rm -i'
alias ..='cd ..'
alias ...='cd ../..'
alias ....='cd ../../..'
alias ..2='cd ../..'
alias ..3='cd ../../..'
alias B='bash'
alias P='python3'
cat src/bash/init.sh
