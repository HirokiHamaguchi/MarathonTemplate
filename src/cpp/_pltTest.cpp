// https://github.com/lava/matplotlib-cpp
// ../bash/_runPltTest.sh

#include <bits/stdc++.h>
using namespace std;

#ifdef VIS
#include "matplotlibcpp.h"
namespace plt = matplotlibcpp;
#endif

#define vis(...) _vis(__LINE__, #__VA_ARGS__, __VA_ARGS__)
void _vis([[maybe_unused]] int lineNum, [[maybe_unused]] string name,
          [[maybe_unused]] vector<int> As) {
#ifdef VIS
    cerr << "\033[1;32m" << lineNum << "\033[0m: now plotting '" << name
         << "'..." << endl;
    plt::title(name);
    plt::plot(As);
    plt::show();
    // plt::save("img/imshow.png");
#endif
}

int main() {
    vector<int> target = {1, 3, 2, 4};
    vis(target);
    return 0;
}
