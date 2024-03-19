#ifndef hari64
#pragma GCC target("avx2")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#define NDEBUG
#include <bits/stdc++.h>
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
using vd = vc<double>; using vvd = vvc<double>; using vvvd = vvvc<double>;
using vpii = vc<pii>; using vvpii = vvc<pii>; using vpll = vc<pll>; using vvpll = vvc<pll>;
using vtiii = vc<tiii>; using vvtiii = vvc<tiii>; using vtlll = vc<tlll>; using vvtlll = vvc<tlll>;
#define ALL(x) begin(x), end(x)
#define RALL(x) (x).rbegin(), (x).rend()
constexpr int INF = 1001001001; constexpr long long INFll = 1001001001001001001;
template <class T> bool chmax(T& a, const T& b) { return a < b ? a = b, 1 : 0; }
template <class T> bool chmaxEq(T& a, const T &b) { return a <= b ? a = b, 1 : 0; }
template <class T> bool chmin(T& a, const T& b) { return a > b ? a = b, 1 : 0; }
template <class T> bool chminEq(T& a, const T &b) { return a >= b ? a = b, 1 : 0; }

struct Timer{
  void start(){_start=chrono::system_clock::now();}
  void stop(){_end=chrono::system_clock::now();sum+=chrono::duration_cast<chrono::nanoseconds>(_end-_start).count();}
  inline int ms()const{const chrono::system_clock::time_point now=chrono::system_clock::now();return static_cast<int>(chrono::duration_cast<chrono::microseconds>(now-_start).count()/1000);}
  inline int ns()const{const chrono::system_clock::time_point now=chrono::system_clock::now();return static_cast<int>(chrono::duration_cast<chrono::microseconds>(now-_start).count());}
  string report(){return to_string(sum/1000000)+"[ms]";}
  void reset(){_start=chrono::system_clock::now();sum=0;}
  private: chrono::system_clock::time_point _start,_end;long long sum=0;
}timer, timer1, timer2, timer3;

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
  Rand(int seed):gen(seed),mt(seed){}
  // シードを変更します
  inline void set_seed(int seed){Xor128 _gen(seed);gen=_gen;}
  // ランダムな浮動小数点数（範囲は[0.0, 1.0)) を返します
  inline double random(){return(double)gen()/(double)gen.max();}
  // 確率 prob で True を返します
  inline bool randBool(double prob){return gen()<prob*gen.max();}
  // a <= b であれば a <= N <= b 、b < a であれば b <= N <= a であるようなランダムな浮動小数点数 N を返します
  inline double uniform(double a,double b){if(b<a)swap(a,b);return a+(b-a)*double(gen())/double(gen.max());}
  // range(0, stop) の要素からランダムに選ばれた要素を返します
  inline uint32_t randRange(uint32_t r){return gen(r);}
  // range(start, stop) の要素からランダムに選ばれた要素を返します
  inline uint32_t randRange(uint32_t l,uint32_t r){return gen(l,r);}
  // a <= N <= b であるようなランダムな整数 N を返します randRange(a, b + 1) のエイリアスです
  inline uint32_t randInt(uint32_t l,uint32_t r){return gen(l,r+1);}
  // シーケンス x をインプレースにシャッフルします
  template<class T>void shuffle(vector<T>&x){for(int i=x.size(),j;i>1;){j=gen(i);swap(x[j],x[--i]);}}
  // 空でないシーケンス seq からランダムに要素を返します
  template<class T>T choice(const vector<T>&seq){assert(!seq.empty());return seq[gen(seq.size())];}
  // 相対的な重みに基づいて要素が選ばれます (※複数回呼ぶ場合は処理を変えた方が良い)
  template<class T,class U>T choice(const vector<T>&seq,const vector<U>&weights){assert(seq.size()==weights.size());vector<U>acc(weights.size());acc[0]=weights[0];for(int i=1;i<int(weights.size());i++)acc[i]=acc[i-1]+weights[i];return seq[lower_bound(acc.begin(),acc.end(),random()*acc.back())-acc.begin()];}
  // 母集団のシーケンスまたは集合から選ばれた長さ k の一意な要素からなるリストを返します 重複無しのランダムサンプリングに用いられます
  template<class T>vector<T>sample(const vector<T>&p,int k){int j,i=0,n=p.size();assert(0<=k&&k<=n);vector<T>ret(k);unordered_set<int>s;for(;i<k;i++){do{j=gen(n);}while(s.find(j)!=s.end());s.insert(j);ret[i]=p[j];}return ret;}
  // 正規分布です mu は平均で sigma は標準偏差です
  double normalvariate(double mu=0.0,double sigma=1.0){return std::normal_distribution(mu,sigma)(mt);}
  private: Xor128 gen;std::mt19937 mt;
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
  debug(timer.report());

  return 0;
}
