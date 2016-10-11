#include <bits/stdc++.h>
#include <cstdlib>
using namespace std;

const int N = 1e5 + 5;
int n , a[N] ,  nx;

struct trie {
    int data;
    struct trie * left , * right;
    trie() : data(0) , left(NULL) , right(NULL) {}
    trie(int _data , struct trie * _left , struct trie * _right) {
        this -> data = _data;
        this -> left = _left;
        this -> right = _right;
    }
};
int getBit(int x) {
    int cnt = 0;
    do{
        cnt++;
        x >>= 1;
    }while(x > 0);

    return cnt;
}
string getBitsDir(int x) {
    int xx = x;
    string cur = "";
    do {
        cur += (char) ((x % 2) + '0');
        x >>= 1;
    }while(x > 0);

    while(cur.size() < nx) cur += '0';
    reverse(cur.begin() , cur.end());

    return cur;
}
struct trie * getnewnode() {
    return new trie();
}
struct trie * root = getnewnode() , *curptr;
void Insert(int x) {
    string res = getBitsDir(x);
    curptr = root;
    for(int i = 0; i < res.size(); ++i) {
      if(res[i] == '0') {
        if(curptr -> left == NULL)
           curptr -> left = getnewnode();
           curptr = curptr -> left;
      } else {
          if(curptr -> right == NULL)
            curptr -> right = getnewnode();
            curptr = curptr -> right;
          }
      }
    //printf("Inserted xor value %d\n" , x);
}
int Query(int x) {
    string res = getBitsDir(x);
    curptr = root;
    string ans = "";
    for(int i = 0; i < res.size(); ++i) {
        if(res[i] == '0') {
           if(curptr -> right != NULL) {
             curptr = curptr -> right;
             ans += '1';
           } else {
               curptr = curptr -> left;
               ans += '0';
           }
        } else {
            if(curptr -> left != NULL) {
                curptr = curptr -> left;
                ans += '1';
            } else {
                curptr = curptr -> right;
                ans += '0';
            }
        }
    }
    int ret = 0;
    for(int i = 0; i < ans.size(); ++i) {
      ret <<= 1;
      ret += int(ans[i] - '0');
    }
    return ret;
}
void initroot()
{
    root = NULL;
    root = getnewnode();
}
int main() {
    int tt;
    scanf("%d" , &tt);
    while(tt--){
    scanf("%d" , &n);
    for(int i = 0; i < n; ++i) {
        scanf("%d" , a + i);
    }
    int mx = *max_element(a , a + n);
    int boos = 0;
    for(int i = 0; i < n; ++i) {
       boos ^= a[i];
       mx = max(mx , boos);
    }
    nx = getBit(mx);
    int ans = 0;
    int xors = 0;
    initroot();
    Insert(xors);
    for(int i = 0; i < n; ++i) {
        xors ^= a[i];
        int value = Query(xors);
        ans = max(ans , value);
        Insert(xors);
    }
    printf("%d\n" , ans);
    }
    return 0;
}
