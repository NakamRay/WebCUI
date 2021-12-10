#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define INF 100000
#define TRUE 1
#define FALSE 0

#include "station.h"
#include "time_table.h"

int COST[N];     //コスト
int VIA[N];      //経路全て
int SCHEDULE[H]; //電車の時刻と乗り換えの場合にFALSEを入れる
int TMP[H];      //経由した駅番号を入れる
char USED[N];    //探索済みかの判定
int CHANGE[H];   //乗り換えをした時の路線番号と再出発時刻
int COUNT;       //
int TOTAL;       //SCHEDULEに記録する場合のカウント数
int END;         //1つの路線の最終終点駅番号
int BRANCH;      //重なっていた路線が分岐する時の駅番号
int STOP;        //電車の方面を変える時の駅番号

int change_station(int i, int j, int c, int absent, int d); //乗り換えをする時の路線の設定
int terminus();                                             //最終終点駅と分岐駅の記録
void arrange_time(int i, int hour, int minute, int* h, int* m, int c);

int dijkstra(int start, int goal, int DIST[][N], int distline) {
  int min;
  int u, v;

  COST[start] = 0;
  while(1){
    min = INF;
    for(int i = 0; i < distline; i++){
      if(!USED[i] && min > COST[i]) { //探索元の設定
        u = i;
        min = COST[i];
      }
    }
    if(u == goal){
      return COST[goal];
    }
    for(v = 0; v < distline; v++){ //最短コストと最短経路の更新
      if(COST[v] > DIST[u][v] + COST[u]) {
        COST[v] = DIST[u][v] + COST[u];
        VIA[v] = u;
      }
    }
    USED[u] = TRUE;
  }
}

int terminus() {
  int count = 0;

  for(int i = 0; i <= N; i++) {
    for(int j = 0; j <= N; j++) {
      if(DIST[i][j] == INF && DIST[i][j-1] == 0) {
        END = j-1;
      }
    }
  }
  for(int i = 0; i <= N; i++) {
    for(int j = 0; j <= N; j++) {
      if(DIST[i][j] == 1) {
        count++;
        if(count > 2) {
          BRANCH = i;
        }
      }
    }
    count = 0;
  }
}

void get_time(int s, int d, int hour, int o_ryomoline[][O], int t_ryomoline[][T], int k, int c, int s2, int d2) {
  int i;
  int j = s;
  int save = s;
  int m1 = 0;
  int m2 = 0;
  int absent = 0; //乗り換えの有無の判定と有りの場合は路線の判定
  int station[N];
  int n = 0;

  if(n == 1) {
    return;
  }
  terminus();
  if(s < d) { //大前方面や小山方面の場合
    for(; k >= 0; k--) { //station[]に経由した駅を前から入れていく
      station[m1] = TMP[k];
      if(END < station[m1] && !SCHEDULE[0]) { //1つの路線の最終駅を過ぎていてまだ時刻が未探索な場合
        STOP = m1;
        if(station[m1-2] > station[m1-1] && station[m1] > station[m1-1]) { //探索途中で方面が変わる場合
          return get_time(s, station[m1-1], hour, o_ryomoline, t_ryomoline, k, c, station[m1], d);
        }
      }
      m1++;
    }
    station[m1] = d;
    for(i = 0; i < O; i++) {
      j = save;
      if(hour <= o_ryomoline[j][i] && o_ryomoline[j][i] < INF) {
        if(CHANGE[c-1] == 4 && !m2) { //前の駅で探索途中で方面が変化(m2の再設定)
          m2 = STOP;
          SCHEDULE[TOTAL] = o_ryomoline[BRANCH][i];
          TOTAL++;
        }
        for(; j <= d; j++) {
          if(o_ryomoline[j][i] < INF) {
            if(absent == 2) { //前の駅が終点だった場合
              SCHEDULE[TOTAL] = FALSE;
              c = change_station(i, j, c, absent, d);
              CHANGE[c] = o_ryomoline[j-1][i];
              c++;
              absent = 0;
              TOTAL++;
            }
            if(j != station[m2]) { 
              SCHEDULE[TOTAL] = FALSE;
              if(o_ryomoline[j][i] < SCHEDULE[TOTAL]) { 
                break;
              }
              save = station[m2];
              i--;
              TOTAL++;
              c = change_station(i, j, c, absent, d);
              break;
            }
            if(o_ryomoline[j+1][i] == INF && o_ryomoline[j][i+1] < INF) { //終点駅かつ次の発車時刻が同じ路線の場合
              break;
            }
            SCHEDULE[TOTAL] = o_ryomoline[j][i];
            save++;
            absent = 0;
            m2++;
            if(TOTAL == 0) { //最初の発車で路線の設定
              c = change_station(i, j, c, absent, d);
            }
            TOTAL++;
          }
          else if(j != station[m2]) { 
            save = station[m2];
            absent = 1;
            i = i-2;
            break;
          }
          else if(absent != 1){ //今までの路線ではその先へ行けない場合
            absent = 2;
            i++;
            j--;
          }
        }
      }
    }
  }
  else {
    station[COUNT] = d;
    for(int k = COUNT-1; 0 <= k; k--) {
      station[m1] = TMP[k];
      m1++;
    }
    for(i = 0; i < T; i++) {
      j = save;
      if(hour <= t_ryomoline[j][i] && t_ryomoline[j][i] < INF) {
        if(absent == 1 && station[m2] < station[m2+1]) { //方面を変更する場合
          SCHEDULE[TOTAL] = t_ryomoline[j][i];
          SCHEDULE[TOTAL+1] = FALSE;
          TOTAL = TOTAL + 2;
          absent = 3;
          c = change_station(i, j, c, absent, d);
          hour = t_ryomoline[j][i]; //発車希望時刻の再設定
          return get_time(save, d, hour, o_ryomoline, t_ryomoline, COUNT-2, c, s2, d2);
        }
        for(; d <= j; j--) {
          if(t_ryomoline[j][i] < INF) {
            if(absent == 2) {
              SCHEDULE[TOTAL] = FALSE;
              c = change_station(i, j, c, absent, d);
              CHANGE[c] = t_ryomoline[j+1][i];
              c++;
              absent = 0;
              TOTAL++;
            }
            if(t_ryomoline[j][i] < SCHEDULE[TOTAL-1]) { 
              break;
            }
            SCHEDULE[TOTAL] = t_ryomoline[j][i];
            absent = 0;
            save--;
            m2++;
            if(TOTAL == 0) {
              c = change_station(i, j, c, absent, d);
            }
            TOTAL++;
          }
          else if(j != station[m2]) { 
            save = station[m2];
            absent = 1;
            i = i-2;
            break;
          }
          else if(absent != 1){
            absent = 2;
            i++;
            j++;
          }
        }
      }
    }
  }
  if(s2 > 0) {
    if(s2 < d2) { //方面変更する場合の再出発駅と到着駅の設定
      SCHEDULE[TOTAL] = FALSE;
      TOTAL++;
      absent = 4;
      c = change_station(i, j, c, absent, d);
      hour = SCHEDULE[TOTAL-2];
    }
    return get_time(s2, d2, hour, o_ryomoline, t_ryomoline, COUNT-1, c, 0, 0);
  }
  return ;
}

int change_station(int i, int j, int c, int absent, int d) {
  int judge = 0;

  terminus();
  if(END < d) { //最初の発車駅の路線の判定
    if(o_ryomoline[BRANCH+1][i] == INF) { //両毛線
      judge = 1;
    }
    else {
      judge = 0;
    }
  }
  else {
    if(t_ryomoline[BRANCH+2][i] == INF && t_ryomoline[END+1][i] < INF) { //両毛線以外
      judge = 1;
    }
    else {
      judge = 0;
    }
  }
  if(c == 0) { //最初の発車駅の路線の記録
    if(judge == 0) {
      CHANGE[c] = 1;
      c++;
    }
    else {
      CHANGE[c] = 2;
      c++;
    }
  }
  else { 
    CHANGE[c] = 1; //路線
    if(absent == 0 || absent == 1) { //路線
      CHANGE[c] = 2; 
    }
    if(absent == 2) { //路線
      CHANGE[c] = 2;
      if(j >= d) {
        CHANGE[c] = 1;
      }
    }
    if(absent == 3) { //方面
      CHANGE[c] = 3;
    }
    if(absent == 4) { //方面
      CHANGE[c] = 4;
    }
    c++;
  }

  return c;
}

int print_time(int s, int d, int k) {
  int i;
  int c = 0;
  int absent = 0;
  int result = 0;
  int hour, minute;
  int h, m;

  switch (CHANGE[c]) {
      case 1:
        printf(" %s ", ROUTE1);
        c++;
        break;
      case 2:
        printf(" %s ", ROUTE2);
        c++;
        break;
      case 3:
        printf(" %s ", COURSE1);
        c++;
        break;
      case 4:
        printf(" %s ", COURSE2);
        c++;
        break;
      default:
        break;
      }
  for(i = 0; i < TOTAL-1; i++) {
    if(!SCHEDULE[i] && !absent) {
      switch (CHANGE[c]) {
        case 1:
          printf(" %s に", ROUTE1);
          c++;
          break;
        case 2:
          printf(" %s に", ROUTE2);
          c++;
          break;
        case 3:
          printf(" %s に", COURSE1);
          c = c+1;
          break;
        case 4:
          printf(" %s に", COURSE2);
          c++;
          break;
        default:
          break;
      }
      printf(" 乗り換え -> ");
      absent++;
      if(SCHEDULE[i-1] < CHANGE[c] && CHANGE[c] < SCHEDULE[i+1]) {
        printf("%s (再出発_", name[TMP[k]]);
        arrange_time(-1, hour, minute, &h, &m, c);
        printf("%2d:%2d) -> ", h, m);
        c++;
      }
    }
    if(SCHEDULE[i]) { 
      if(!SCHEDULE[i+1]) {
        printf("%s [到着_", name[TMP[k]]);
        k--;
        arrange_time(i, hour, minute, &h, &m, c);
        printf("%2d:%2d] -> ", h, m);
      }
      else {
        printf("%s (", name[TMP[k]]);
        k--;
        arrange_time(i, hour, minute, &h, &m, c);
        printf("%2d:%2d) -> ", h, m);
      }
      absent = 0;
    }
  }
  printf("%s [到着_", name[TMP[d]]);
  arrange_time(TOTAL-1, hour, minute, &h, &m, c);
  printf("%2d:%2d]\n", h, m);

  return 0;
}

void arrange_time(int i, int hour, int minute, int* h, int* m, int c) {
  int result = 0;

  if(i > -1) {
    result = SCHEDULE[i];
    *h = result / 100;
    *m = result % 100;
  }
  else {
    result = CHANGE[c];
    *h = result / 100;
    *m = result % 100;
  }
}

int arrange_station(int s, int d) {
  int node;
  int l = 0;
  int k;

  COUNT = 0;
  printf("最短経路(時刻) : \n");
  node = d;
  while(1){
    node = VIA[node];
    TMP[l] = node;
    l++;
    COUNT++;
    if (node == s) break;
  }
}

int main(int argc, char *argv[]) {
  int i, j;
  int k; 
  int e = N - 1;
  int s, d;
  int s2 = 0;
  int d2 = 0;
  int hour = 0;
  int c = 0;

  for(i = 0; i < N; i++) { //初期設定
    COST[i] = INF;
    USED[i] = FALSE;
    VIA[i] = -1;
  }
  printf("%s -> %s %s \n", argv[1], argv[2], argv[3]);  
  printf("---------------\n");
  for(i = 0; i < N; i++) { 
    if(strcmp(argv[1], name[i]) == 0) {
      s = i;
    }
    if(strcmp(argv[2], name[i]) == 0) {
      d = i;
    }
  }
  hour = atoi(argv[3]);
  printf("最短距離 : %d 駅経由します\n", dijkstra(s, d, DIST, N));
  arrange_station(s, d);
  k = COUNT-1; //経由した駅の総数を設定しておく
  get_time(s, d, hour, o_ryomoline, t_ryomoline, k, c, s2, d2);
  print_time(s, d, k);
  
  return 0;
}
