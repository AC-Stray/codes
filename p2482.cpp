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
    (bool)leiFanZhu 是否为类反猪
    false 不是类反猪
    true  未亮明身份且对主猪造成伤害 成为类反猪
*/
bool leiFanZhu[15];
struct pig{
    /*
        (string)shenFen 身份
        MP 主猪
        ZP 忠猪
        FP 反诸
    */
    string shenFen;
    /*
        (bool)liangShenFen 亮自己的身份
        false 未亮身份
        true  亮明自己的身份 身份为主猪和忠猪 -> 跳忠 身份为反猪 -> 跳反
    */
    bool liangShenFen;
    /*
        (bool)alive 存活
        false 死亡
        true  存活
    */
    bool alive;
    /*
        (bool)zhuGeLianNu 猪哥连弩
        false 未装备猪哥连弩
        true  装备猪哥连弩 出牌阶段可以使用任意张杀
    */
    bool zhuGeLianNu;
    /*
        (int)hp 体力值
    */
    int hp;
    /*
        (vector<char>)card 手牌
        P 桃
        K 杀
        D 闪
        F 决斗
        N 南猪入侵
        W 万箭齐发
        J 无懈可击
        Z 猪哥连弩
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
    (void)gameOver 游戏结束操作
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
    (char)moPai 摸牌
    返回牌堆顶的牌 并将这张牌移出牌堆
*/
char moPai(){
    char tmp = cards.front();
    if(cards.size() > 1) cards.erase(cards.begin());
    return tmp;
}
/*
    (bool)xunWen 向玩家询问是否拥有指定手牌
    false 没有指定手牌
    true  拥有指定手牌并弃掉指定手牌
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
    (bool)diaoTiLiZhi 对指定玩家造成指定伤害
    false 指定玩家在受到伤害后死亡
    true  指定玩家能够承受伤害 或在使用桃后没有死亡
*/
bool diaoTiLiZhi(int p, int v){
    pigs[p].hp -= v;
    while(pigs[p].hp <= 0){
        if(xunWen(p, 'P')) pigs[p].hp++;
        else{
            pigs[p].alive = false;
            if(p == 0){ // 游戏结束：主猪死亡
                gameOver();
            }
            else if(pigs[p].shenFen == "FP"){
                FPcnt--;
                if(FPcnt == 0){ // 游戏结束：反猪死光
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
    (bool)biaoDiYi 表敌意
    false 不能向指定玩家表敌意
    true  能够向制定玩家表敌意
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
    (bool)xianYinQin 献殷勤
    false 不能向指定玩家献殷勤
    true  能够向制定玩家献殷勤
*/
bool xianYinQing(int from, int to){
    if((pigs[from].shenFen == "MP" || pigs[from].shenFen == "ZP") && isMPZP(pigs[to])) return true;
    if(pigs[from].shenFen == "FP" && pigs[to].liangShenFen && pigs[to].shenFen == "FP") return true;
    return false;
}
#undef isMPZP
/*
    (void)jiangCheng 奖励与惩罚
    主猪杀死忠猪 -> 主猪失去所有手牌和装备牌
    任何猪杀死反猪 -> 伤害来源摸3张牌
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
    (bool)xunWenWuXieKeJi 询问无懈可击
    flag:
        true  向 to 献殷勤
        false 向 to 表敌意
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
        // 摸牌
        pigs[p].card.push_back(moPai());
        pigs[p].card.push_back(moPai());
        // 出牌
        bool chuSha = false; // 如果没有装猪哥连弩 只能出一张杀
        int xiaJia = (p + 1) % n; // 下一个玩家
        while(!pigs[xiaJia].alive) xiaJia = (xiaJia + 1) % n;
        for(ri i = 0; i < pigs[p].card.size(); i++){
            char card = pigs[p].card[i];
            switch(card){
                case 'P':
                    // 桃
                    if(pigs[p].hp < 4){
                        pigs[p].hp++;
                        chuPai;
                    }
                    break;
                case 'K':
                    // 杀
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
                    // 决斗
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
                            if(now == 0){ // 自己出杀
                                if(!xunWen(p, 'K')){
                                    if(!diaoTiLiZhi(p, 1)){
                                        jiangCheng(tmp, p);
                                    }
                                    break;
                                }
                            }
                            else{ // 对方出杀
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
                    // 南猪入侵
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
                    // 万箭齐发
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
                    // 猪哥连弩
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
