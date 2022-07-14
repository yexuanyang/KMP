//KMP字符串匹配
//最主要的一点就是主串的比较位置不能后退，比较失败了移动模式串，主串位置不动。这样可以让匹配算法复杂度接近线性

//而传统的暴力匹配算法BF主串会回溯，模式串位置重置


#include <iostream>
#include <cstring>
#define MAXLEN 1000001

using namespace std;

//通常的暴力匹配算法
//成功则返回第一次匹配的子串在主串中的索引
//失败则返回主串的字符串长度
//m是主串，p是模式串
size_t BadMatch(char *m, char* p){
    size_t mlen = strlen(m);//主串的长度mlen
    size_t plen = strlen(p);//模式串的长度plen

    size_t i = 0;//主串的字符位置
    size_t j = 0;//模式串的字符位置

    //模式串和主串一一对比
    while(j < plen && i < mlen){
        if(m[i] == p[j]){
            i++;
            j++;
        }
        else{
            i = i - (j - 1);//i变成未匹配字符的下一个字符
            j = 0;//j变成模式串的开头
        }
    }

    //匹配成功
    if(i < mlen){
        return i - j;
    }
    else{
        return i;
    }
}


//KMP匹配算法
//m是主串，p是模式串,next是next数组,返回匹配的子串下标数组
int* KMP(char* m, char* p, const int* next){
    int* index;
    int mlen = (int)strlen(m);
    int plen = (int)strlen(p);
    index = (int*)malloc(sizeof(int) * mlen);
    for(int i = 0; i < mlen; i++)   index[i] = -1;
    int i = 0;//主串的位置
    int j = 0;//模式串的位置
    int iLoc = 0;//匹配的位置的下标
    while( i < mlen){
        if(m[i] == p[j]){//匹配，同时右移
            i++;
            j++;
            if(j == plen){//如果匹配完成
                index[iLoc] = i - j;//记录下标
                iLoc++;
                //把主串的位置变成匹配到的位置的之后一位
                j = next[j-1];//调整模式串的位置，继续匹配
            }
        }
        else{//不匹配，i不动，模式串右移共同前后缀长度，开始匹配
            if( j == 0 ){//第一个字符都不匹配
                i++;//主串向右移动
            }
            else{
                j = next[j - 1];
            }
        }
    }
    return index;
}

//打印next数组
//len是模式串的长度
void show(int* next, int len){
    for(int i = 0; i < len; i++){
        cout << next[i] << " ";
    }
    cout << endl;
}

//运算next数组
//p是模式串
void getNext(char* p, int* next){
    next[0] = 0;
    int i = 1;//主串中比较的位置的索引
    int preFix = 0;//记录当前的共同前后缀的长度

    while(i < strlen(p)){

        if(p[i] == p[preFix]){
            next[i] = ++preFix;
            i++;

        }
        else {
            if(preFix == 0){//找不到共同的前后缀了
                next[i] = 0;//这个子串没有共同前后缀
                i++;//主串比较位置向前移动一位
            }
            else{
                preFix = next[preFix - 1];//还能找到部分匹配的子串,则从部分匹配的子串后面开始比较，主串的位置不动
            }
        }
    }
    //show(next, (int)strlen(p));

}


int main() {
    char m[MAXLEN],p[MAXLEN];
    cin >> m >> p;
    int plen = (int)strlen(p);
    int mlen = (int)strlen(m);
    //size_t index = BadMatch(m,p);
    //cout << index << endl;
    int next[plen];
    getNext(p,next);
    int* ans = KMP(m,p,next);
    for(int i = 0; i < mlen; i ++){
        if(ans[i] == -1)    break;
        cout << ans[i] + 1 << endl;
    }
    show(next, plen);
    return 0;
}
