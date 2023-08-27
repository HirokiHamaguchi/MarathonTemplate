#ifndef hari64
#include <bits/stdc++.h>
#pragma GCC target("avx2")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#define debug(...)
#else
#include "viewer.hpp"
#define debug(...) viewer::_debug(__LINE__, #__VA_ARGS__, __VA_ARGS__)
#endif
// clang-format off
using namespace std;
template <typename T> using vc = vector<T>;
template <typename T> using vvc = vector<vc<T>>;
template <typename T> using vvvc = vector<vvc<T>>;
using ll = long long; using ld = long double;
using pii = pair<int, int>; using pll = pair<ll, ll>;
using tiii = tuple<int, int, int>; using tlll = tuple<ll, ll, ll>;
using vi = vc<int>; using vvi = vvc<int>; using vvvi = vvvc<int>;
using vll = vc<ll>; using vvll = vvc<ll>; using vvvll = vvvc<ll>;
using vb = vc<bool>; using vvb = vvc<bool>; using vvvb = vvvc<bool>;
using vpii = vc<pii>; using vvpii = vvc<pii>; using vpll = vc<pll>; using vvpll = vvc<pll>;
using vtiii = vc<tiii>; using vvtiii = vvc<tiii>; using vtlll = vc<tlll>; using vvtlll = vvc<tlll>;
#define ALL(x) begin(x), end(x)
#define RALL(x) (x).rbegin(), (x).rend()
constexpr int INF = 1001001001; constexpr long long INFll = 1001001001001001001;
template <class T> bool chmax(T& a, const T& b) { return a < b ? a = b, 1 : 0; }
template <class T> bool chmin(T& a, const T& b) { return a > b ? a = b, 1 : 0; }

struct Timer{
    void start(){_start=chrono::system_clock::now();}
    void stop(){_end=chrono::system_clock::now();sum+=chrono::duration_cast<chrono::nanoseconds>(_end-_start).count();}
    inline int ms()const{const chrono::system_clock::time_point now=chrono::system_clock::now();return static_cast<int>(chrono::duration_cast<chrono::microseconds>(now-_start).count()/1000);}
    inline int ns()const{const chrono::system_clock::time_point now=chrono::system_clock::now();return static_cast<int>(chrono::duration_cast<chrono::microseconds>(now-_start).count());}
    string report(){return to_string(sum/1000000)+"[ms]";}
    void reset(){_start=chrono::system_clock::now();sum=0;}
    private: chrono::system_clock::time_point _start,_end;long long sum=0;
}timer;

struct Xor128{// period 2^128 - 1
    uint32_t x,y,z,w;
    static constexpr uint32_t min(){return 0;}
    static constexpr uint32_t max(){return UINT32_MAX;}
    Xor128(uint32_t seed=0):x(123456789),y(362436069),z(521288629),w(88675123+seed){}
    uint32_t operator()(){uint32_t t=x^(x<<11);x=y;y=z;z=w;return w=(w^(w>>19))^(t^(t>>8));}
    uint32_t operator()(uint32_t l,uint32_t r){return((*this)()%(r-l))+l;}
    uint32_t operator()(uint32_t r){return(*this)()%r;}
};

struct Rand{// https://docs.python.org/ja/3/library/random.html
    Rand(){};
    Rand(int seed):gen(seed){};
    // シードを変更します
    inline void set_seed(int seed){Xor128 _gen(seed);gen=_gen;}
    // ランダムな浮動小数点数（範囲は[0.0, 1.0)) を返します
    inline double random(){return(double)gen()/(double)gen.max();}
    // a <= b であれば a <= N <= b 、b < a であれば b <= N <= a であるようなランダムな浮動小数点数 N を返します
    inline double uniform(double a,double b){if(b<a)swap(a,b);return a+(b-a)*double(gen())/double(gen.max());}
    // range(0, stop) の要素からランダムに選ばれた要素を返します
    inline uint32_t randrange(uint32_t r){return gen(r);}
    // range(start, stop) の要素からランダムに選ばれた要素を返します
    inline uint32_t randrange(uint32_t l,uint32_t r){return gen(l,r);}
    // a <= N <= b であるようなランダムな整数 N を返します randrange(a, b + 1) のエイリアスです
    inline uint32_t randint(uint32_t l,uint32_t r){return gen(l,r+1);}
    // シーケンス x をインプレースにシャッフルします
    template<class T>void shuffle(vector<T>&x){for(int i=x.size(),j;i>1;){j=gen(i);swap(x[j],x[--i]);}}
    // 空でないシーケンス seq からランダムに要素を返します
    template<class T>T choice(const vector<T>&seq){assert(!seq.empty());return seq[gen(seq.size())];}
    // 相対的な重みに基づいて要素が選ばれます (※複数回呼ぶ場合は処理を変えた方が良い)
    template<class T,class U>T choice(const vector<T>&seq,const vector<U>&weights){assert(seq.size()==weights.size());vector<U>acc(weights.size());acc[0]=weights[0];for(int i=1;i<int(weights.size());i++)acc[i]=acc[i-1]+weights[i];return seq[lower_bound(acc.begin(),acc.end(),random()*acc.back())-acc.begin()];}
    // 母集団のシーケンスまたは集合から選ばれた長さ k の一意な要素からなるリストを返します 重複無しのランダムサンプリングに用いられます
    template<class T>vector<T>sample(const vector<T>&p,int k){int j,i=0,n=p.size();assert(0<=k&&k<=n);vector<T>ret(k);unordered_set<int>s;for(;i<k;i++){do{j=gen(n);}while(s.find(j)!=s.end());s.insert(j);ret[i]=p[j];}return ret;}
    // 正規分布です mu は平均で sigma は標準偏差です
    double normalvariate(double mu=0.0,double sigma=1.0){double u2,z,NV=4*exp(-0.5)/sqrt(2.0);while(true){u2=1.0-random();z=NV*(random()-0.5)/u2;if(z*z/4.0<=-log(u2))break;}return mu+z*sigma;}
    private: Xor128 gen;
}myrand;

namespace esc{const vector<int>colors{196,208,226,46,77,14,12,13,5,136,195,245};constexpr int RED=0,ORANGE=1,YELLOW=2,LIGHTGREEN=3,GREEN=4,AQUA=5,BLUE=6,PINK=7,PURPLE=8,BROWN=9,WHITE=10,GRAY=11;
void back(int n){cerr<<"\e["<<n<<"A";}void locate(int r,int c){cerr<<"\e["<<r+1<<+";"<<c+1<<"H";}void reset(){cerr<<"\e[0m";}
void color(int c){cerr<<"\e[38;5;"<<colors[c]<<"m";}void color(int c,string s){color(c);cerr<<s;reset();}void color(int c,int s){color(c,to_string(s));}
void bcolor(int c){cerr<<"\e[4;"<<colors[c]<<"m";}void bcolor(int c,string s){bcolor(c);cerr<<s;reset();}void bcolor(int c,int s){color(c,to_string(s));}
string with_sep(int n,char sep=','){string ret="",s=to_string(n);reverse(s.begin(),s.end());for(int i=0,len=s.length();i<=len;){ret+=s.substr(i,3);if((i+=3)>=len)break;ret+=sep;}reverse(ret.begin(),ret.end());return ret;}
string with_fill(int n,int num=3,char space=' '){string s=to_string(n);return string(max(0,num-int(s.size())),space)+s;}}  // namespace esc

template <int Z>
struct _YX {
    int y, x;
    _YX() : y(-1), x(-1) {}
    _YX(int y, int x) : y(y), x(x) {}
    inline int idx() const { return y * Z + x; };
    inline bool isInside() const { return 0 <= y && y < Z && 0 <= x && x < Z; }
    inline int abs() const { return std::abs(y) + std::abs(x); }
    inline double hypot() const { return std::hypot(y, x); }
    inline void flip() { swap(y, x); }
    bool operator==(_YX const& r) const { return y == r.y && x == r.x; }
    bool operator!=(_YX const& r) const { return !((*this) == r); }
    bool operator<(_YX const& r) const { return y == r.y ? x < r.x : y < r.y; }
    bool operator>(_YX const& r) const { return r < (*this); }
    _YX& operator+=(_YX const& r) { y += r.y, x += r.x; return *this; }
    _YX& operator-=(_YX const& r) { y -= r.y, x -= r.x; return *this; }
    _YX& operator*=(int const& v) { y *= v, x *= v; return *this; }
    _YX& operator/=(int const& v) { y /= v, x /= v; return *this; }
    _YX operator+(_YX const& r) const { return _YX{ y + r.y, x + r.x }; }
    _YX operator-(_YX const& r) const { return _YX{ y - r.y, x - r.x }; }
    _YX operator*(int const& v) const { return _YX{ y * v, x * v }; }
    _YX operator/(int const& v) const { return _YX{ y / v, x / v }; }
    _YX operator-() const { return _YX{-y, -x}; }
    friend istream& operator>>(istream& is, _YX<Z>& r) { return is >> r.y >> r.x; }
    friend ostream& operator<<(ostream& os, _YX<Z> const& r) { return os << r.y << " " << r.x; }
};

template <int sz>
struct IndexSet {
    vector<int> vec;
    IndexSet() {
        for (int i = 0; i < sz; i++) _pos[i] = -1;
    }
    void insert(int v) {
        assert(0 <= v && v < sz);
        if (contains(v)) return;
        _pos[v] = vec.size();
        vec.push_back(v);
    }
    void remove(int v) {
        assert(contains(v));
        int p = _pos[v], b = vec.back();
        vec[p] = b;
        vec.pop_back();
        _pos[b] = p;
        _pos[v] = -1;
    }
    int random_pop() {
        assert(!vec.empty());
        int v = myrand.choice(vec);
        remove(v);
        return v;
    }
    bool contains(int v) const { return _pos[v] != -1; }
    bool empty() const { return vec.empty(); }
    size_t size() const { return vec.size(); }
    friend ostream& operator<<(ostream& os, const IndexSet& is) {
        vector<int> v = is.vec;
        sort(v.begin(), v.end());
        for (auto& e : v) os << e << " ";
        return os << endl;
    }

   private:
    int _pos[sz];
};
using IdxSet = IndexSet<100>;

// clang-format on

#ifdef VIS
#include "matplotlibcpp.h"
namespace plt = matplotlibcpp;
#define vis(...) _vis(__LINE__, #__VA_ARGS__, __VA_ARGS__)
void _vis(int lineNum, string name, vector<int> As) {
    cerr << "\033[1;32m" << lineNum << "\033[0m: now plotting '" << name << "'..."
         << endl;
    plt::title(name);
    plt::plot(As);
    plt::show();
    // plt::save("img/imshow.png");
}
#else
#define vis(...)
#endif

// constexpr int N = 10;
// using YX = _YX<N>;
// const YX DYX[4] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
// inline YX toYX(int idx) { return {idx / N, idx % N}; };

void getInput() {}

void solve() {
    vi As(100);
    iota(ALL(As), 0);

    vis(As);
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    timer.start();

    getInput();

    solve();

    timer.stop();
    debug(timer.report());

    return 0;
}
