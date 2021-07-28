#include<bits/stdc++.h>
#define ri register int
#define chuPai pigs[p].card.erase(pigs[p].card.begin()+i), i = -1
using namespace std;
namespace debug{
    int round = 0;
}
int n, m, p, FPcnt, tmp;
char tcard;
vector<char> cards;
/*
    (bool)leiFanZhu �Ƿ�Ϊ�෴��
    false �����෴��
    true  δ��������Ҷ���������˺� ��Ϊ�෴��
*/
bool leiFanZhu[15];
struct pig{
    /*
        (string)shenFen ���
        MP ����
        ZP ����
        FP ����
    */
    string shenFen;
    /*
        (bool)liangShenFen ���Լ������
        false δ�����
        true  �����Լ������ ���Ϊ��������� -> ���� ���Ϊ���� -> ����
    */
    bool liangShenFen;
    /*
        (bool)alive ���
        false ����
        true  ���
    */
    bool alive;
    /*
        (bool)zhuGeLianNu �������
        false δװ���������
        true  װ��������� ���ƽ׶ο���ʹ��������ɱ
    */
    bool zhuGeLianNu;
    /*
        (int)hp ����ֵ
    */
    int hp;
    /*
        (vector<char>)card ����
        P ��
        K ɱ
        D ��
        F ����
        N ��������
        W ����뷢
        J ��и�ɻ�
        Z �������
    */
    vector<char> card;
    /*
        INIT
    */
    pig(){
        liangShenFen = false;
        alive = true;
        zhuGeLianNu = false;
        hp = 4;
    }
}pigs[15];
/*
    (void)gameOver ��Ϸ��������
*/
void gameOver(){
    if(!pigs[0].alive) puts("FP");
    else puts("MP");
    for(ri i = 0; i < n; i++){
        if(!pigs[i].alive){
            puts("DEAD");
            continue;
        }
        for(ri j = 0; j < pigs[i].card.size(); j++) cout << pigs[i].card[j] << ' ';
        cout << endl;
    }
    exit(0);
}
/*
    (char)moPai ����
    �����ƶѶ����� �����������Ƴ��ƶ�
*/
char moPai(){
    char tmp = cards.front();
    if(cards.size() > 1) cards.erase(cards.begin());
    return tmp;
}
/*
    (bool)xunWen �����ѯ���Ƿ�ӵ��ָ������
    false û��ָ������
    true  ӵ��ָ�����Ʋ�����ָ������
*/
bool xunWen(int p, char target){
    for(ri i = 0; i < pigs[p].card.size(); i++){
        char card = pigs[p].card[i];
        if(card == target){
            chuPai;
            return true;
        }
    }
    return false;
}
/*
    (bool)diaoTiLiZhi ��ָ��������ָ���˺�
    false ָ��������ܵ��˺�������
    true  ָ������ܹ������˺� ����ʹ���Һ�û������
*/
bool diaoTiLiZhi(int p, int v){
    pigs[p].hp -= v;
    while(pigs[p].hp <= 0){
        if(xunWen(p, 'P')) pigs[p].hp++;
        else{
            pigs[p].alive = false;
            if(p == 0){ // ��Ϸ��������������
                gameOver();
            }
            else if(pigs[p].shenFen == "FP"){
                FPcnt--;
                if(FPcnt == 0){ // ��Ϸ��������������
                    gameOver();
                }
            }
            return false;
        }
    }
    return true;
}
#define isMPZP(thePig) (thePig.shenFen == "MP" || (thePig.liangShenFen && thePig.shenFen == "ZP"))
/*
    (bool)biaoDiYi �����
    false ������ָ����ұ����
    true  �ܹ����ƶ���ұ����
*/
bool biaoDiYi(int from, int to){
    if(pigs[from].shenFen == "MP"){
        if(pigs[to].liangShenFen && pigs[to].shenFen == "FP") return true;
        if(!pigs[to].liangShenFen && leiFanZhu[to]) return true;
    }
    if(pigs[from].shenFen == "ZP" && pigs[to].liangShenFen && pigs[to].shenFen == "FP") return true;
    if(pigs[from].shenFen == "FP" && isMPZP(pigs[to])) return true;
    return false;
}
/*
    (bool)xianYinQin ������
    false ������ָ�����������
    true  �ܹ����ƶ����������
*/
bool xianYinQing(int from, int to){
    if((pigs[from].shenFen == "MP" || pigs[from].shenFen == "ZP") && isMPZP(pigs[to])) return true;
    if(pigs[from].shenFen == "FP" && pigs[to].liangShenFen && pigs[to].shenFen == "FP") return true;
    return false;
}
#undef isMPZP
/*
    (void)jiangCheng ������ͷ�
    ����ɱ������ -> ����ʧȥ�������ƺ�װ����
    �κ���ɱ������ -> �˺���Դ��3����
*/
void jiangCheng(int from, int to){
    if(pigs[from].shenFen == "MP" && pigs[to].shenFen == "ZP"){
        pigs[from].zhuGeLianNu = false;
        pigs[from].card.clear();
        return;
    }
    if(pigs[to].shenFen == "FP"){
        pigs[from].card.push_back(moPai());
        pigs[from].card.push_back(moPai());
        pigs[from].card.push_back(moPai());
        return;
    }
}
/*
    (bool)xunWenWuXieKeJi ѯ����и�ɻ�
    flag:
        true  �� to ������
        false �� to �����
*/
bool xunWenWuXieKeJi(int from, int to, bool flag){
    if(!pigs[to].liangShenFen) return false;
    bool fl = true;
    for(ri i = from; i != from || fl; i = (i + 1) % n){
        fl = false;
        if(!pigs[i].alive) continue;
        if(flag){
            if(xianYinQing(i, to)){
                if(xunWen(i, 'J')){
                    pigs[i].liangShenFen = true;
                    return !xunWenWuXieKeJi(i, to, false);
                }
            }
        }
        else{
            if(biaoDiYi(i, to)){
                if(xunWen(i, 'J')){
                    pigs[i].liangShenFen = true;
                    return !xunWenWuXieKeJi(i, to, true);
                }
            }
        }
    }
    return false;
}
int main(){
    cin >> n >> m;
    for(ri i = 0; i < n; i++){
        cin >> pigs[i].shenFen;
        if(pigs[i].shenFen == "FP") FPcnt++;
        for(ri j = 0; j < 4; j++){
            cin >> tcard;
            pigs[i].card.push_back(tcard);
        }
    }
    pigs[0].liangShenFen = true;
    for(ri i = 0; i < m; i++){
        cin >> tcard;
        cards.push_back(tcard);
    }
    p = -1;
    while(true){ // main loop
        p = (p + 1) % n;
        if(!pigs[p].alive) continue;
        debug::round++;
        // ����
        pigs[p].card.push_back(moPai());
        pigs[p].card.push_back(moPai());
        // ����
        bool chuSha = false; // ���û��װ������� ֻ�ܳ�һ��ɱ
        int xiaJia = (p + 1) % n; // ��һ�����
        while(!pigs[xiaJia].alive) xiaJia = (xiaJia + 1) % n;
        for(ri i = 0; i < pigs[p].card.size(); i++){
            char card = pigs[p].card[i];
            switch(card){
                case 'P':
                    // ��
                    if(pigs[p].hp < 4){
                        pigs[p].hp++;
                        chuPai;
                    }
                    break;
                case 'K':
                    // ɱ
                    if((pigs[p].zhuGeLianNu || !chuSha) && biaoDiYi(p, xiaJia)){
                        pigs[p].liangShenFen = true;
                        chuSha = true;
                        chuPai;
                        if(!xunWen(xiaJia, 'D')){
                            if(!diaoTiLiZhi(xiaJia, 1)){
                                jiangCheng(p, xiaJia);
                            }
                        }
                    }
                    break;
                case 'F':
                    // ����
                    tmp = xiaJia;
                    if(pigs[p].shenFen == "FP") tmp = 0;
                    else{
                        while(tmp != p && (!pigs[tmp].alive || !biaoDiYi(p, tmp))){
                            tmp = (tmp + 1) % n;
                        }
                        if(tmp == p) break;
                    }
                    if(biaoDiYi(p, tmp)){
                        chuPai;
                        if(p == 0 && pigs[tmp].shenFen == "ZP"){
                            if(!diaoTiLiZhi(tmp, 1)){
                                jiangCheng(p, tmp);
                            }
                            break;
                        }
                        pigs[p].liangShenFen = true;
                        if(xunWenWuXieKeJi(p, tmp, true)) continue;
                        int now = 0;
                        while(true){
                            now ^= 1;
                            if(now == 0){ // �Լ���ɱ
                                if(!xunWen(p, 'K')){
                                    if(!diaoTiLiZhi(p, 1)){
                                        jiangCheng(tmp, p);
                                    }
                                    break;
                                }
                            }
                            else{ // �Է���ɱ
                                if(!xunWen(tmp, 'K')){
                                    if(!diaoTiLiZhi(tmp, 1)){
                                        jiangCheng(p, tmp);
                                    }
                                    break;
                                }
                            }
                        }
                    }
                    break;
                case 'N':
                    // ��������
                    chuPai;
                    for(ri j = (p + 1) % n; j != p; j = (j + 1) % n){
                        if(!pigs[j].alive) continue;
                        if(xunWenWuXieKeJi(p, j, true)) continue;
                        if(xunWen(j, 'K')) continue;
                        if(!diaoTiLiZhi(j, 1)) jiangCheng(p, j);
                        if(j == 0) leiFanZhu[p] = true;
                    }
                    break;
                case 'W':
                    // ����뷢
                    chuPai;
                    for(ri j = (p + 1) % n; j != p; j = (j + 1) % n){
                        if(!pigs[j].alive) continue;
                        if(xunWenWuXieKeJi(p, j, true)) continue;
                        if(xunWen(j, 'D')) continue;
                        if(!diaoTiLiZhi(j, 1)) jiangCheng(p, j);
                        if(j == 0) leiFanZhu[p] = true;
                    }
                    break;
                case 'Z':
                    // �������
                    pigs[p].zhuGeLianNu = true;
                    chuPai;
                    break;
            }
            if(!pigs[p].alive) break;
        }
        // cout << "Round " << debug::round << endl;
        // for(ri j = 0; j < n; j++){
        //     if(!pigs[j].alive) cout << "DEAD" << endl;
        //     for(ri k = 0; k < pigs[j].card.size(); k++) cout << pigs[j].card[k] << ' ';
        //     cout << endl;
        // }
        // cout << endl;
    }
    return 0;
}
/*
Data - 1
5 6
MP P P P Z
ZP K P Z P
FP K W W K
ZP J F N K
FP W W D P
J W J N J W 

Data - 2
4 10
MP W W J J
FP J J J J
ZP J J J J
FP J J J J
J J F F J F F F K K

Data - 3
3 8
MP W W J J
FP D J J J
ZP J D J J
J K F F J F K F

Data - 4
5 12
MP F F K K
ZP P F W D
FP F D K W
FP K P F N
ZP Z F N K
F W W W F F W N N W D W
*/
