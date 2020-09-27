#include <vector>
#include <iostream>
#include <string>
#include <map>
#include <ctime>


using namespace std;

struct TWords {
    long long wrd;
    long long str;
    long long value;
};

TWords MakeTWords (long long wrd, long long str, long long value){
    TWords tmp;
    tmp.wrd = wrd;
    tmp.str = str;
    tmp.value = value;
    return tmp;
}

void ZFunction(vector <long long> &patt, vector <long long> &z){
    long long r = 0,l = 0;
    long long size = patt.size();
    for (long long j = 1; j < size; ++j) {
        if (j <= r) 
            z[j] = min(r - j + 1, z[j - l]);
        while (j + z[j] < size && patt[size - 1 - z[j]] == patt[size - 1 - (j + z[j])]) 
            z[j]++;
        if (j + z[j] - 1 > r) {
            l = j;
            r = j + z[j] - 1;
        }
    }
}

void Suff (vector <long long> &patt, vector<long long> &suff){
    vector <long long> z(patt.size(), 0);
    ZFunction(patt, z);
    for (long long j = patt.size() - 1; j > 0; j--){
        suff[patt.size() - z[j]] = j;
    }
    for (long long j = 1, r = 0; j < patt.size(); j++){
        if (j + z[j] == patt.size()){
            for (; r <= j; r++){
                if (suff[r] == patt.size())
                    suff[r] = j;
            }
        }
    }
}

void ParseText(vector <TWords> &text){
    string s;
    long long str_num = 1,wrd = 1;
    long long symbol;
    bool num_read = false;
    int temp = 0;
    symbol = getchar();
    while(true) {
        if(symbol == ' ' || symbol == '\n') {
            if(num_read) {
                text.push_back(MakeTWords(wrd, str_num, temp));
                num_read = false;
                temp = 0;
                wrd++;
            }
            if(symbol == '\n') {
                    str_num++;
                    wrd = 1;
                }
        } else {
            if(!num_read) {
                num_read = true;
            }
            temp = temp * 10 + (symbol - '0');
        }
        symbol = getchar();
        if(symbol == EOF) {
            break;
        }
    }
    if(num_read) {
        text.push_back(MakeTWords(wrd, str_num, temp));
    }
}

void ParsePattern(vector <long long> &v){
    long long symbol;
    long long temp = 0;
    bool num_read = false;
    symbol = getchar();
    while(true) {
        if(symbol == ' ') {
            if(num_read) {
                v.push_back(temp);
                num_read = false;
                temp = 0;
            }
        } else {
            if(!num_read) {
                num_read = true;
            }
            temp = temp * 10 + (symbol - '0');
        }
        symbol = getchar();
        if(symbol == '\n') {
            break;
        }
    }
    if(num_read) {
        v.push_back(temp);
    }
}

void BadChar(vector <long long> &v, map<long long,long long> &m){
    for (long long i = v.size() - 2; i >= 0; i--){
        if (m.count(v[i]) == 0){
            m.insert(make_pair(v[i],i));
        }
    }
}

void BM (vector <long long> &patt, vector <TWords> &text){
    map<long long, long long> m;
    BadChar(patt, m);
    vector <long long> suff(patt.size() + 1, patt.size());
    Suff(patt, suff);
    vector <pair<long long, long>> ans;
    long long bound = 0, j;
    for (long long i = 0; i <= (long long)(text.size() - patt.size());){
        for (j = patt.size() - 1;j >= bound && patt[j] == text[i + j].value;j--){}
        if (j < bound){
            ans.push_back(make_pair(text[i].str, text[i].wrd));
            bound = patt.size() - suff[0];
            j = -1;
            i += suff[j + 1];
        } else {
            long long bad_s;
            if (m.count(text[i + j].value) != 0)
                bad_s = m[text[i + j].value];
            else 
                bad_s = -1;
            i += max(suff[j + 1], j - bad_s);
            bound = 0;
        }
    }
    for (long long i = 0; i < ans.size(); i++){
        cout << ans[i].first << ", " << ans[i].second << '\n';
    }
}


int main(){
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    vector <long long> pattern;
    vector <TWords> text;
    ParsePattern(pattern);
    ParseText(text);
    BM(pattern, text);
    return 0;
} 