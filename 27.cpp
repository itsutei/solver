#include<vector>
#include<chrono>
#include<string>
#include<iostream>
using namespace std;
using vec = vector<int>;

struct Corner{
  vec cp,co;
  Corner(){
    cp = {0, 1, 2, 3, 4, 5, 6, 7};
    co = {0, 0, 0, 0, 0, 0, 0, 0};
  };
  Corner(vec _cp, vec _co) : cp(_cp), co(_co){};
  void apply_move(const Corner &move){
    vec cp2(8), co2(8);
    for(int i=0; i<8; i++){
      cp2[i] = cp[move.cp[i]];
    }
    for(int i=0; i<8; i++){
      co2[i] = (co[move.cp[i]]+move.co[i])%3;
    }
    cp = cp2; co = co2;;
  }
};

struct Edge{
  vector<int> ep, eo;
  Edge(){
    ep = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    eo = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  };
  Edge(vec _ep, vec _eo) : ep(_ep), eo(_eo){};
   
  void apply_move(const Edge &move) {
    vec ep2(12), eo2(12);
    for(int i=0; i<12; i++) {
      ep2[i] = ep[move.ep[i]];
    }
    for(int i=0; i<12; i++) {
      eo2[i] = (eo[move.ep[i]] + move.eo[i]) % 2;
    }
    ep = ep2;
    eo = eo2;
  }
};

struct State {
  Corner c; Edge e;
  State() : c(), e() {};
  State(Corner _c, Edge _e) : c(_c), e(_e) {};
};

void moves(Corner &c, string s) {
  Corner temp;
  if(s[0]=='U') {
     temp = {
      {3, 0, 1, 2, 4, 5, 6, 7},
      {0, 0, 0, 0, 0, 0, 0, 0},
    };
  }
  if(s[0]=='D') {
     temp = {
      {0, 1, 2, 3, 5, 6, 7, 4},
      {0, 0, 0, 0, 0, 0, 0, 0},
    };
  }
  if(s[0]=='L') {
     temp = {
      {4, 1, 2, 0, 7, 5, 6, 3},
      {2, 0, 0, 1, 1, 0, 0, 2},
    };
  }
  if(s[0]=='R') {
     temp = {
      {0, 2, 6, 3, 4, 1, 5, 7},
      {0, 1, 2, 0, 0, 2, 1, 0},
    };
  }
  if(s[0]=='F') {
     temp = {
      {0, 1, 3, 7, 4, 5, 2, 6},
      {0, 0, 1, 2, 0, 0, 2, 1},
    };
  }
  if(s[0]=='B') {
     temp = {
      {1, 5, 2, 3, 0, 4, 6, 7},
      {1, 2, 0, 0, 2, 1, 0, 0},
    };
  }

  int num;
  if(s.size()==1) {
    num = 1;
  } else if(s[1]=='2') {
    num = 2;
  } else {
    num = 3;
  }
  for(int i=0; i<num; i++) {
    c.apply_move(temp);
  }
  return; 
}

void moves(Edge &e, string s) {
  Edge temp;
  if(s[0]=='U') {
     temp = {
      {0, 1, 2, 3, 7, 4, 5, 6, 8, 9, 10, 11},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    };
  }
  if(s[0]=='D') {
     temp = {
      {0, 1, 2, 3, 4, 5, 6, 7, 9, 10, 11, 8},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    };
  }
  if(s[0]=='L') {
     temp = {
      {11, 1, 2, 7, 4, 5, 6, 0, 8, 9, 10, 3},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    };
  }
  if(s[0]=='R') {
     temp = {
      {0, 5, 9, 3, 4, 2, 6, 7, 8, 1, 10, 11},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    };
  }
  if(s[0]=='F') {
     temp = {
      {0, 1, 6, 10, 4, 5, 3, 7, 8, 9, 2, 11},
      {0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 1, 0}
    };
  }
  if(s[0]=='B') {
     temp = {
      {4, 8, 2, 3, 1, 5, 6, 7, 0, 9, 10, 11},
      {1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0}
    };
  }
  int num;
  if(s.size()==1) {
    num = 1;
  } else if(s[1]=='2') {
    num = 2;
  } else {
    num = 3;
  }
  for(int i=0; i<num; i++) {
    e.apply_move(temp);
  }
  return; 
}

void moves(State &state, string s) {
  moves(state.c,s);
  moves(state.e,s);
}

State scr(string s){
  auto state = State();
  int n = s.size();
  string t;
  for(int i=0; i<n; i++){
    t+=s[i];
    if(i+1==n||s[i+1]==' '){
      moves(state,t);
      t = string();
      i++;
    }
  }
  return state;
}

char inv_face(char s){
  if(s=='U')return 'D';
  if(s=='D')return 'U';
  if(s=='R')return 'L';
  if(s=='L')return 'R';
  if(s=='F')return 'B';
  if(s=='B')return 'F';
  return '1';
}

bool is_move_available(string prev_move, string move){
  char prev_face = prev_move[0];
  if(prev_face == move[0]) return 0;
  if(inv_face(prev_face) == move[0]){
    return prev_face<move[0];
  }
  return 1;
}

int co_to_idx(vec &co){
  int index = 0;
  for(int i=0; i<7; i++){
    index *= 3;
    index += co[i];
  }
  return index;
}
vec idx_to_co(int index){
  vec co(8);
  int sum_co{};
  for(int i=6; i>=0; i--){
    co[i]=index%3;
    index/=3;
    sum_co+=co[i];
  }
  co[7]=(3-sum_co%3)%3;
  return co;
}
int eo_to_idx(vec &eo){
  int index = 0;
  for(int i=0; i<11; i++){
    index *= 2;
    index += eo[i];
  }
  return index;
}
vec idx_to_eo(int index){
  vec eo(12);
  int sum_eo{};
  for(int i=10; i>=0; i--){
    eo[i]=index%2;
    index/=2;
    sum_eo+=eo[i];
  }
  eo[11]=(2-sum_eo%2)%2;
  return eo;
}
int calc_comb(int n, int r){
  long long ret = 1;
  for(int i=0; i<r; i++) ret *= n-i;
  for(int i=0; i<r; i++) ret /= r-i;
  return (int)ret;
}
int e_comb_to_idx(vec &comb){
  int index = 0;
  int r = 4;
  for(int i=11; i>=0; --i){
    if(comb[i]){
      index += calc_comb(i,r);
      --r;
    }
  }
  return index;
}
vec idx_to_e_comb(int index){
  vec comb(12);
  int r = 4;
  for(int i=12; i>=0; --i){
    if(index>=calc_comb(i,r)){
      comb[i] = 1;
      index -= calc_comb(i,r);
      --r;
    }
  }
  return comb;
}
int perm_to_idx(const vec &perm){
  int index = 0;
  int sz  =perm.size();
  for(int i=0; i<sz; i++){
    index *= sz-i;
    for(int j=i+1; j<sz; j++){
      if(perm[i]>perm[j]) index++;
    }
  }
  return index;
}
vec idx_to_perm(int index,int sz){
  vec perm(sz);
  for(int i=sz-2; i>=0; --i){
    perm[i] = index % (sz-i);
    index /= sz-i;
    for(int j=i+1; j<sz; j++){
      if(perm[j]>=perm[i]){
        perm[j]++;
      }
    }
  }
  return perm;
}

struct Search{
  
  State state;
  int max_sol_len = 9999;
  vector<string> current_sol_ph1,current_sol_ph2;
  vector<string> moves_names = {
    "U","U2","U'","D","D2","D'","L","L2","L'","R","R2","R'","F","F2","F'","B","B2","B'"
  };
  vector<string> moves_names_ph2 = {
    "U","U2","U'","D","D2","D'","L2","R2","F2","B2"
  };
  const int num_co = 2187;
  const int num_eo = 2048;
  const int num_e_comb = 495;
  const int num_cp = 40320;
  const int num_udep = 40320;
  const int num_eep = 24;
  vector<vec> co_move_t, eo_move_t, e_comb_t, cp_move_t, udep_move_t, eep_move_t,
    co_eec_prune_t, eo_eec_prune_t, cp_eep_prune_t, udep_eep_prune_t;
  
  chrono::system_clock::time_point start_search_t = chrono::system_clock::now();
  
  Search(State _state):state(_state){
    
    auto start = chrono::system_clock::now();

    co_move_t = vector(num_co, vec(18));
    for(int i=0; i<num_co; i++){
      Corner corner_state = {
        vec(8), idx_to_co(i)
      };
      for(int j=0; j<18; j++){
        auto s2 = corner_state;
        moves(s2, moves_names[j]);
        co_move_t[i][j]=co_to_idx(s2.co);
      }
    }
    eo_move_t = vector(num_eo,vec(18));
    for(int i=0; i<num_eo; i++){
      Edge edge_state = {
        vec(12),idx_to_eo(i)
      };
      for(int j=0; j<18; j++){
        auto s2 = edge_state;
        moves(s2,moves_names[j]);
        eo_move_t[i][j]=eo_to_idx(s2.eo);
      }
    }
    e_comb_t = vector(num_e_comb,vec(18));
    for(int i=0; i<num_e_comb; i++){
      Edge edge_state = {
        idx_to_e_comb(i),vec(12)
      };
      for(int j=0; j<18; j++){
        auto s2 = edge_state;
        moves(s2,moves_names[j]);
        e_comb_t[i][j]=e_comb_to_idx(s2.ep);
      }
    }
    cp_move_t = vector(num_cp,vec(10));
    for(int i=0; i<num_cp; i++){
      Corner corner_state = {
        idx_to_perm(i,8),vec(8),
      };
      for(int j=0; j<10; j++){
        auto s2 = corner_state;
        moves(s2,moves_names_ph2[j]);
        cp_move_t[i][j]=perm_to_idx(s2.cp);
      }
    }
    udep_move_t = vector(num_udep,vec(10));
    for(int i=0; i<num_udep; i++){
      Edge edge_state = {
        vec(12),vec(12)
      };
      auto v2 = idx_to_perm(i,8);
      for(int k=0; k<8; k++){
        edge_state.ep[k+4] = v2[k];
      }
      for(int j=0; j<10; j++){
        auto s2 = edge_state;
        moves(s2,moves_names_ph2[j]);
        for(int k=0; k<8; k++){
          v2[k] = s2.ep[k+4];
        }
        udep_move_t[i][j]=perm_to_idx(v2);
      }
    }
    eep_move_t = vector(num_eep,vec(10));
    for(int i=0; i<num_eep; i++){
      Edge edge_state = {
        vec(12),vec(12)
      };
      auto v2 = idx_to_perm(i,4);
      for(int k=0; k<4; k++){
        edge_state.ep[k] = v2[k];
      }
      for(int j=0; j<10; j++){
        auto s2 = edge_state;
        moves(s2,moves_names_ph2[j]);
        for(int k=0; k<4; k++){
          v2[k] = s2.ep[k];
        }
        eep_move_t[i][j]=perm_to_idx(v2);
      }
    }
    auto end = chrono::system_clock::now();
    auto dur = end - start;
    auto msec = chrono::duration_cast<chrono::milliseconds>(dur).count();
    cout<<msec<<" msec.:move_t"<<endl;
    
    start = chrono::system_clock::now();
    co_eec_prune_t = vector(num_co,vec(num_e_comb,-1));
    co_eec_prune_t[0][0] = 0;
    int dist = 0, num_filled = 1;
    while(num_filled != num_co*num_e_comb){
      for(int i_co=0; i_co<num_co; i_co++){
        for(int i_eec=0; i_eec<num_e_comb; i_eec++){
          if(co_eec_prune_t[i_co][i_eec] == dist){
            for(int i_move=0; i_move<18; i_move++){
              int next_co = co_move_t[i_co][i_move];
              int next_eec = e_comb_t[i_eec][i_move];
              if(co_eec_prune_t[next_co][next_eec]==-1){
                co_eec_prune_t[next_co][next_eec] = dist + 1;
                num_filled++;
              }
            }
          }
        }
      }
      dist++;
    }
    end = chrono::system_clock::now();
    dur = end - start;
    msec = chrono::duration_cast<chrono::milliseconds>(dur).count();
    cout<<msec<<" msec.:co_eec_prune_t"<<endl;
    
    start = chrono::system_clock::now();
    eo_eec_prune_t = vector(num_eo,vec(num_e_comb,-1));
    eo_eec_prune_t[0][0] = 0;
    dist = 0; num_filled = 1;
    while(num_filled != num_eo*num_e_comb){
      for(int i_eo=0; i_eo<num_eo; i_eo++){
        for(int i_eec=0; i_eec<num_e_comb; i_eec++){
          if(eo_eec_prune_t[i_eo][i_eec] == dist){
            for(int i_move=0; i_move<18; i_move++){
              int next_eo = eo_move_t[i_eo][i_move];
              int next_eec = e_comb_t[i_eec][i_move];
              if(eo_eec_prune_t[next_eo][next_eec]==-1){
                eo_eec_prune_t[next_eo][next_eec] = dist + 1;
                num_filled++;
              }
            }
          }
        }
      }
      dist++;
    }
    end = chrono::system_clock::now();
    dur = end - start;
    msec = chrono::duration_cast<chrono::milliseconds>(dur).count();
    cout<<msec<<" msec.:eo_eec_prune_t"<<endl;
    
    start = chrono::system_clock::now();
    cp_eep_prune_t = vector(num_cp,vec(num_eep,-1));
    cp_eep_prune_t[0][0] = 0;
    dist = 0; num_filled = 1;
    while(num_filled != num_cp*num_eep){
      for(int i_cp=0; i_cp<num_cp; i_cp++){
        for(int i_eep=0; i_eep<num_eep; i_eep++){
          if(cp_eep_prune_t[i_cp][i_eep] == dist){
            for(int i_move=0; i_move<10; i_move++){
              int next_cp = cp_move_t[i_cp][i_move];
              int next_eep = eep_move_t[i_eep][i_move];
              if(cp_eep_prune_t[next_cp][next_eep]==-1){
                cp_eep_prune_t[next_cp][next_eep] = dist + 1;
                num_filled++;
              }
            }
          }
        }
      }
      dist++;
    }
    end = chrono::system_clock::now();
    dur = end - start;
    msec = chrono::duration_cast<chrono::milliseconds>(dur).count();
    cout<<msec<<" msec.:cp_eep_prune_t"<<endl;
    
    start = chrono::system_clock::now();
    udep_eep_prune_t = vector(num_udep,vec(num_eep,-1));
    udep_eep_prune_t[0][0] = 0;
    dist = 0; num_filled = 1;
    while(num_filled != num_udep*num_eep){
      for(int i_udep=0; i_udep<num_udep; i_udep++){
        for(int i_eep=0; i_eep<num_eep; i_eep++){
          if(udep_eep_prune_t[i_udep][i_eep] == dist){
            for(int i_move=0; i_move<10; i_move++){
              int next_udep = udep_move_t[i_udep][i_move];
              int next_eep = eep_move_t[i_eep][i_move];
              if(udep_eep_prune_t[next_udep][next_eep]==-1){
                udep_eep_prune_t[next_udep][next_eep] = dist + 1;
                num_filled++;
              }
            }
          }
        }
      }
      dist++;
    }
    end = chrono::system_clock::now();
    dur = end - start;
    msec = chrono::duration_cast<chrono::milliseconds>(dur).count();
    cout<<msec<<" msec.:udep_eep_prune_t"<<endl;

  };
  
  bool depth_lim_search_ph2(int cp_idx,int udep_idx,int eep_idx,int depth){
    if(depth==0){
      if(cp_idx==0&&udep_idx==0&&eep_idx==0){
        for(auto i:current_sol_ph1){
          cout<<i<<' ';
          if(i.size()==1)cout<<' ';
        }
        cout<<".  ";
        for(auto i:current_sol_ph2){
          cout<<i<<' ';
          if(i.size()==1)cout<<' ';
        }
        max_sol_len = current_sol_ph1.size()+current_sol_ph2.size()-1;
        
        cout<<"("<<max_sol_len+1<<" moves,";
        auto now_t = chrono::system_clock::now();
        auto dur = now_t - start_search_t;
        auto msec = chrono::duration_cast<chrono::milliseconds>(dur).count();
        cout<<" "<<msec<<" msec.)"<<endl;
        return 1;
      }
      return 0;
    }
    
    if(max(cp_eep_prune_t[cp_idx][eep_idx],udep_eep_prune_t[udep_idx][eep_idx])>depth) return 0;
    
    string prev_move = "0";
    if(current_sol_ph2.size()) prev_move = current_sol_ph2.back();
    else if(current_sol_ph1.size()) prev_move = current_sol_ph1.back();
    
    for(int move_idx=0; move_idx<10; move_idx++){
      string move_name = moves_names_ph2[move_idx];
      if(!is_move_available(prev_move,move_name)) continue;
      current_sol_ph2.emplace_back(move_name);
      int next_cp_idx = cp_move_t[cp_idx][move_idx];
      int next_udep_idx = udep_move_t[udep_idx][move_idx];
      int next_eep_idx = eep_move_t[eep_idx][move_idx];
      bool found = depth_lim_search_ph2(next_cp_idx,next_udep_idx,next_eep_idx,depth-1);
      current_sol_ph2.pop_back();
      if(found) return 1;
    }
    return 0;
  }
  
  bool start_ph2(const State &_state){
    int cp_idx = perm_to_idx(_state.c.cp);
    vec v2(8),v3(4);
    for(int i=0; i<8; i++){
      v2[i]=_state.e.ep[i+4];
    }
    for(int i=0; i<4; i++){
      v3[i]=_state.e.ep[i];
    }
    int udep_idx = perm_to_idx(v2);
    int eep_idx = perm_to_idx(v3);
    int depth = 0;
    while(depth<=max_sol_len-(int)current_sol_ph1.size()) {
      if(depth_lim_search_ph2(cp_idx, udep_idx, eep_idx, depth)) {
        return 1;
      }
      depth++;
    }
    return 0;
  }
  
  bool depth_lim_search_ph1(int co_idx,int eo_idx,int e_comb_idx,int depth){
    if(depth==0){
      if(co_idx==0&&eo_idx==0&&e_comb_idx==0){
        string last_move = "0";
        if(current_sol_ph1.size()) last_move = current_sol_ph1.back();
        if(last_move.back()=='2')return 0;
        
        auto s2 = state;
        for(auto i:current_sol_ph1){
          moves(s2,i);
        }
        return start_ph2(s2);        
      }
      return 0;
    }
    
    if(max(co_eec_prune_t[co_idx][e_comb_idx],eo_eec_prune_t[eo_idx][e_comb_idx])>depth) return 0;
    
    string prev_move = "0";
    if(current_sol_ph1.size()) prev_move = current_sol_ph1.back();
    
    for(int move_idx=0; move_idx<18; move_idx++){
      string move_name = moves_names[move_idx];
      if(!is_move_available(prev_move,move_name)) continue;
      current_sol_ph1.emplace_back(move_name);      
      int next_co_idx = co_move_t[co_idx][move_idx];
      int next_eo_idx = eo_move_t[eo_idx][move_idx];
      int next_e_comb_idx = e_comb_t[e_comb_idx][move_idx];
      depth_lim_search_ph1(next_co_idx,next_eo_idx,next_e_comb_idx,depth-1);
      current_sol_ph1.pop_back();
    }
    return 0;
  }
  
  void start_search(int max_len=23){
    
    start_search_t = chrono::system_clock::now();
    
    max_sol_len = max_len;
    int co_idx = co_to_idx(state.c.co);
    int eo_idx = eo_to_idx(state.e.eo);
    vec e_comb(12);
    for(int i=0; i<12; i++){
      if(state.e.ep[i]<4) e_comb[i]++;
    }
    int e_comb_idx = e_comb_to_idx(e_comb);
    for(int depth=0;depth<=max_sol_len;depth++){
      
      auto now_t = chrono::system_clock::now();
      auto dur = now_t - start_search_t;
      auto sec = chrono::duration_cast<chrono::seconds>(dur).count();
      if(sec)cout<<sec<<" sec."<<endl;
      if(sec>60)break;
      if(depth_lim_search_ph1(co_idx,eo_idx,e_comb_idx,depth)){
      }
    }
    return;
  }
};


int main(){
  
  string sc;  
  getline(cin,sc);
  auto cube = scr(sc);
  auto search = Search(cube);
  search.start_search();
  
}