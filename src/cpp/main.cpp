#ifndef LOCAL
#pragma GCC target("avx2")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#define NDEBUG
#define dbg(...)
#endif

#ifdef DBG
#define DBG_MACRO_NO_WARNING
#include "dbg.h"
#endif

#include <bits/stdc++.h>
// clang-format off
using namespace std;
template <typename T> using vec = vector<T>;
template <typename T> using vvec = vector<vec<T>>;
template <typename T> using vvvec = vector<vvec<T>>;
using ll = long long; using ld = long double;
using pii = pair<int, int>; using pll = pair<ll, ll>;
using tiii = tuple<int, int, int>; using tlll = tuple<ll, ll, ll>;
using vi = vec<int>; using vvi = vvec<int>; using vvvi = vvvec<int>;
using vll = vec<ll>; using vvll = vvec<ll>; using vvvll = vvvec<ll>;
#define ALL(x) begin(x), end(x)
#define RALL(x) (x).rbegin(), (x).rend()
constexpr int INF = 1001001001; constexpr long long INFll = 1001001001001001001;
template <class T> bool chmax(T& a, const T& b) { return a < b ? a = b, 1 : 0; }
template <class T> bool chmaxEq(T& a, const T &b) { return a <= b ? a = b, 1 : 0; }
template <class T> bool chmin(T& a, const T& b) { return a > b ? a = b, 1 : 0; }
template <class T> bool chminEq(T& a, const T &b) { return a >= b ? a = b, 1 : 0; }

struct Timer{
  using C=std::chrono::system_clock;
  Timer(){}
  void start(){s=C::now();assert(!b);b=1;}
  void stop(){sum+=duration();assert(b);b=0;}
  void reset(){sum=0;}
  double sec(){return sum+(b?duration():0);}
  private:C::time_point s;bool b=0;double sum=0;
  double duration(){return std::chrono::duration<double>(C::now()-s).count();}
}timer,timer1,timer2,timer3;

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
  Rand():gen(0),mt(0){}
  void set_seed(int seed){Xor128 _gen(seed);gen=_gen;}
  /* prob%  */ bool randBool(double prob){return gen()<prob*gen.max();}
  /* [0, 1) */ double random(){return(double)gen()/gen.max();}
  /* [a, b] */ double uniform(double a,double b){if(b<a)swap(a,b);return a+(b-a)*double(gen())/gen.max();}
  /* [0, r) */ uint32_t randRange(uint32_t r){return gen(r);}
  /* [l, r) */ uint32_t randRange(uint32_t l,uint32_t r){return gen(l,r);}
  /* [l, r] */ uint32_t randInt(uint32_t l,uint32_t r){return gen(l,r+1);}
  /* Fisher */ template<class T>void shuffle(vector<T>&x){for(int i=x.size(),j;i>1;){j=gen(i);swap(x[j],x[--i]);}}
  /* Normal */ double normalvariate(double mu=0.0,double sigma=1.0){return std::normal_distribution(mu,sigma)(mt);}
  private: Xor128 gen; std::mt19937 mt;
}myrand;

namespace esc {
const vi colors{196,208,226,46,77,14,12,13,5,136,195,245};
template <class T>void color(int c,T s,bool doEndl=true){cerr<<"\e[38;5;"<<colors[c]<<"m"<<s<<"\e[0m";if(doEndl)cerr<<endl;}
template <class T>void RED       (T s,bool doEndl=true){color( 0,s,doEndl);}
template <class T>void ORANGE    (T s,bool doEndl=true){color( 1,s,doEndl);}
template <class T>void YELLOW    (T s,bool doEndl=true){color( 2,s,doEndl);}
template <class T>void LIGHTGREEN(T s,bool doEndl=true){color( 3,s,doEndl);}
template <class T>void GREEN     (T s,bool doEndl=true){color( 4,s,doEndl);}
template <class T>void AQUA      (T s,bool doEndl=true){color( 5,s,doEndl);}
template <class T>void BLUE      (T s,bool doEndl=true){color( 6,s,doEndl);}
template <class T>void PINK      (T s,bool doEndl=true){color( 7,s,doEndl);}
template <class T>void PURPLE    (T s,bool doEndl=true){color( 8,s,doEndl);}
template <class T>void BROWN     (T s,bool doEndl=true){color( 9,s,doEndl);}
template <class T>void WHITE     (T s,bool doEndl=true){color(10,s,doEndl);}
template <class T>void GRAY      (T s,bool doEndl=true){color(11,s,doEndl);}
string withSep(int n,char sep=','){string ret="",s=to_string(n);reverse(ALL(s));for(int i=0,len=s.length();i<=len;)
{ret+=s.substr(i,3);if((i+=3)>=len)break;ret+=sep;}reverse(ALL(ret));return ret;}
string withFill(int n,int num=3,char space=' '){string s=to_string(n);return string(max(0,num-int(s.size())),space)+s;}}

template<int sz>
struct IndexSet{
  vector<int>vec;
  IndexSet(){for(int i=0;i<sz;i++)_pos[i]=-1;}
  void insert(int v){assert(0<=v&&v<sz);if(contains(v))return;_pos[v]=vec.size();vec.push_back(v);}
  void remove(int v){assert(contains(v));int p=_pos[v],b=vec.back();vec[p]=b;vec.pop_back();_pos[b]=p;_pos[v]=-1;}
  int random_pop(){assert(!vec.empty());int v=myrand.choice(vec);remove(v);return v;}
  bool contains(int v)const{return _pos[v]!=-1;}
  bool empty()const{return vec.empty();}
  size_t size()const{return vec.size();}
  friend ostream&operator<<(ostream&os,const IndexSet&is){vi v=is.vec;sort(ALL(v));for(auto&e:v)os<<e<<" ";return os<<endl;}
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

  return 0;
}
