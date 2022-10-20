#include<bits/stdc++.h>
#include<chrono>
using namespace std;
using vec = vector<int>;

struct State{
  vector<int> cp,co,ep,eo;
  State(){
    cp={0, 1, 2, 3, 4, 5, 6, 7};
    co={0, 0, 0, 0, 0, 0, 0, 0};
    ep={0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    eo={0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  };
  State(vec _cp, vec _co, vec _ep, vec _eo):cp(_cp),co(_co),ep(_ep),eo(_eo){};
  
  bool operator==(const State &s2){
    if(cp!=s2.cp)return 0;
    if(co!=s2.co)return 0;
    if(ep!=s2.ep)return 0;
    if(eo!=s2.eo)return 0;
    return 1;
  }  
  
  void apply_move(const State &move){
    vec cp2(8),co2(8),ep2(12),eo2(12);
    for(int i=0; i<8; i++){
      cp2.at(i)=cp.at(move.cp.at(i));
    }
    for(int i=0; i<8; i++){
      co2.at(i)
      =(co.at(move.cp.at(i))+move.co.at(i))%3;
    }
    for(int i=0; i<12; i++){
      ep2.at(i)=ep.at(move.ep.at(i));
    }
    for(int i=0; i<12; i++){
      eo2.at(i)
      =(eo.at(move.ep.at(i))+move.eo.at(i))%2;
    }
    cp = cp2; co = co2;
    ep = ep2; eo = eo2;
  }
  
  bool is_solved(){
    for(int i=0; i<8; i++){
      if(cp.at(i)!=i) return 0;
      if(co.at(i)!=0) return 0;
    }
    for(int i=0; i<12; i++){
      if(ep.at(i)!=i) return 0;
      if(eo.at(i)!=0) return 0;
    }
    return 1;
  }
};

int count_solved_corners(const State &state){
  int sum{};
  for(int i=0; i<8; i++){
    sum += state.cp.at(i)==i;
  }
  return sum;
}
int count_solved_edges(const State &state){
  int sum{};
  for(int i=0; i<12; i++){
    sum += state.ep.at(i)==i;
  }
  return sum;
}
int count_eo_edges(const State &state){
  int sum{};
  for(int i=0; i<12; i++){
    sum += state.eo.at(i);
  }
  return sum;
}

bool prune(int depth, const State &state){
  if(depth==1 &&(count_solved_corners(state)<4||count_solved_edges(state)<8)) {
    return 1;
  }
  if(depth==2 && count_solved_edges(state)<4) {
    return 1;
  }
  if(depth==3 && count_solved_edges(state)<2) {
    return 1;
  }
  if(depth==2){
    int num = count_eo_edges(state);
    if(!(num==0||num==4||num==8)) {
      return 1;
    }
  }
  return 0;
}

void moves(State &sol,string s){
  State temp;
  if(s.at(0)=='U'){
     temp = {
      {3, 0, 1, 2, 4, 5, 6, 7},
      {0, 0, 0, 0, 0, 0, 0, 0},
      {0,1, 2, 3, 7, 4, 5, 6, 8, 9, 10, 11},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    };
  }
  if(s.at(0)=='D'){
     temp = {
      {0, 1, 2, 3, 5, 6, 7, 4},
      {0, 0, 0, 0, 0, 0, 0, 0},
      {0, 1, 2, 3, 4, 5, 6, 7, 9, 10, 11, 8},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    };
  }
  if(s.at(0)=='L'){
     temp = {
      {4, 1, 2, 0, 7, 5, 6, 3},
      {2, 0, 0, 1, 1, 0, 0, 2},
      {11, 1, 2, 7, 4, 5, 6, 0, 8, 9, 10, 3},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    };
  }
  if(s.at(0)=='R'){
     temp = {
      {0, 2, 6, 3, 4, 1, 5, 7},
      {0, 1, 2, 0, 0, 2, 1, 0},
      {0, 5, 9, 3, 4, 2, 6, 7, 8, 1, 10, 11},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    };
  }
  if(s.at(0)=='F'){
     temp = {
      {0, 1, 3, 7, 4, 5, 2, 6},
      {0, 0, 1, 2, 0, 0, 2, 1},
      {0, 1, 6, 10, 4, 5, 3, 7, 8, 9, 2, 11},
      {0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 1, 0}
    };
  }
  if(s.at(0)=='B'){
     temp = {
      {1, 5, 2, 3, 0, 4, 6, 7},
      {1, 2, 0, 0, 2, 1, 0, 0},
      {4, 8, 2, 3, 1, 5, 6, 7, 0, 9, 10, 11},
      {1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0}
    };
  }
  int num;
  if(s.size()==1)num=1;
  else if(s.at(1)=='2')num=2;
  else num=3;
  for(int i=0; i<num; i++){
    sol.apply_move(temp);
  }
  return; 
}

State scr(string s){
  auto sol = State();
  int n = s.size();
  string t;
  for(int i=0; i<n; i++){
    t+=s.at(i);
    if(i+1==n||s.at(i+1)==' '){
      moves(sol,t);
      t = string();
      i++;
    }
  }
  return sol;
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
  char prev_face = prev_move.at(0);
  if(prev_face == move.at(0)) return 0;
  if(inv_face(prev_face) == move.at(0)){
    return prev_face<move.at(0);
  }
  return 1;
}

int co_to_idx(vec &co){
  int index = 0;
  for(int i=0; i<7; i++){
    index *= 3;
    index += co.at(i);
  }
  return index;
}
vec idx_to_co(int index){
  vec co(8);
  int sum_co{};
  for(int i=6; i>=0; i--){
    co.at(i)=index%3;
    index/=3;
    sum_co+=co.at(i);
  }
  co.at(7)=(3-sum_co%3)%3;
  return co;
}
int eo_to_idx(vec &eo){
  int index = 0;
  for(int i=0; i<11; i++){
    index *= 2;
    index += eo.at(i);
  }
  return index;
}
vec idx_to_eo(int index){
  vec eo(12);
  int sum_eo{};
  for(int i=10; i>=0; i--){
    eo.at(i)=index%2;
    index/=2;
    sum_eo+=eo.at(i);
  }
  eo.at(11)=(2-sum_eo%2)%2;
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
    if(comb.at(i)){
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
      comb.at(i) = 1;
      index -= calc_comb(i,r);
      --r;
    }
  }
  return comb;
}
int perm_to_idx(vec &perm){
  int index = 0;
  int sz  =perm.size();
  for(int i=0; i<sz; i++){
    index *= sz-i;
    for(int j=i+1; j<sz; j++){
      if(perm.at(i)>perm.at(j)) index++;
    }
  }
  return index;
}
vec idx_to_perm(int index,int sz){
  vec perm(sz);
  for(int i=sz-2; i>=0; --i){
    perm.at(i) = index % (sz-i);
    index /= sz-i;
    for(int j=i+1; j<sz; j++){
      if(perm.at(j)>=perm.at(i)){
        perm.at(j)++;
      }
    }
  }
  return perm;
}



struct Search{
  
  State state;
  int max_sol_len = 9999;
  vector<string> current_sol_ph1,current_sol_ph2;
  vector<string> moves_names={
    "U","U2","U'","D","D2","D'","L","L2","L'","R","R2","R'","F","F2","F'","B","B2","B'"
  };
  vector<string> moves_names_ph2={
    "U","U2","U'","D","D2","D'","L2","R2","F2","B2"
  };
  const int num_co = 2187;
  const int num_eo = 2048;
  const int num_e_comb = 495;
  const int num_cp = 40320;
  const int num_udep = 40320;
  const int num_eep = 24;
  vector<vec> co_move_t, eo_move_t, e_comb_t, cp_move_t, udep_move_t, eep_move_t, co_eec_prune_t, eo_eec_prune_t, cp_eep_prune_t, udep_eep_prune_t;
  chrono::system_clock::time_point start_search_t = chrono::system_clock::now();

  
  
  Search(State _state):state(_state){
    
    auto start = chrono::system_clock::now();
    co_move_t = vector(num_co,vec(18));
    for(int i=0; i<num_co; i++){
      State state = {
        vec(8),idx_to_co(i),vec(12),vec(12)
      };
      for(int j=0; j<18; j++){
        auto s2 = state;
        moves(s2,moves_names.at(j));
        co_move_t.at(i).at(j)=co_to_idx(s2.co);
      }
    }
    eo_move_t = vector(num_eo,vec(18));
    for(int i=0; i<num_eo; i++){
      State state = {
        vec(8),vec(8),vec(12),idx_to_eo(i)
      };
      for(int j=0; j<18; j++){
        auto s2 = state;
        moves(s2,moves_names.at(j));
        eo_move_t.at(i).at(j)=eo_to_idx(s2.eo);
      }
    }
    e_comb_t = vector(num_e_comb,vec(18));
    for(int i=0; i<num_e_comb; i++){
      State state = {
        vec(8),vec(8),
        idx_to_e_comb(i),vec(12)
      };
      for(int j=0; j<18; j++){
        auto s2 = state;
        moves(s2,moves_names.at(j));
        e_comb_t.at(i).at(j)=e_comb_to_idx(s2.ep);
      }
    }
    cp_move_t = vector(num_cp,vec(10));
    for(int i=0; i<num_cp; i++){
      State state = {
        idx_to_perm(i,8),vec(8),
        vec(12),vec(12)
      };
      for(int j=0; j<10; j++){
        auto s2 = state;
        moves(s2,moves_names_ph2.at(j));
        cp_move_t.at(i).at(j)=perm_to_idx(s2.cp);
      }
    }
    udep_move_t = vector(num_udep,vec(10));
    for(int i=0; i<num_udep; i++){
      State state = {
        vec(8),vec(8),vec(12),vec(12)
      };
      auto v2 = idx_to_perm(i,8);
      for(int k=0; k<8; k++){
        state.ep.at(k+4) = v2.at(k);
      }
      for(int j=0; j<10; j++){
        auto s2 = state;
        moves(s2,moves_names_ph2.at(j));
        for(int k=0; k<8; k++){
          v2.at(k) = s2.ep.at(k+4);
        }
        udep_move_t.at(i).at(j)=perm_to_idx(v2);
      }
    }
    eep_move_t = vector(num_eep,vec(10));
    for(int i=0; i<num_eep; i++){
      State state = {
        vec(8),vec(8),vec(12),vec(12)
      };
      auto v2 = idx_to_perm(i,4);
      for(int k=0; k<4; k++){
        state.ep.at(k) = v2.at(k);
      }
      for(int j=0; j<10; j++){
        auto s2 = state;
        moves(s2,moves_names_ph2.at(j));
        for(int k=0; k<4; k++){
          v2.at(k) = s2.ep.at(k);
        }
        eep_move_t.at(i).at(j)=perm_to_idx(v2);
      }
    }
    auto end = chrono::system_clock::now();
    auto dur = end - start;
    auto msec = chrono::duration_cast<chrono::milliseconds>(dur).count();
    cout<<msec<<" msec.:move_t"<<endl;
    
    start = chrono::system_clock::now();
    co_eec_prune_t = vector(num_co,vec(num_e_comb,-1));
    co_eec_prune_t.at(0).at(0) = 0;
    int dist = 0, num_filled = 1;
    while(num_filled != num_co*num_e_comb){
      for(int i_co=0; i_co<num_co; i_co++){
        for(int i_eec=0; i_eec<num_e_comb; i_eec++){
          if(co_eec_prune_t.at(i_co).at(i_eec) == dist){
            for(int i_move=0; i_move<18; i_move++){
              int next_co = co_move_t.at(i_co).at(i_move);
              int next_eec = e_comb_t.at(i_eec).at(i_move);
              if(co_eec_prune_t.at(next_co).at(next_eec)==-1){
                co_eec_prune_t.at(next_co).at(next_eec) = dist + 1;
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
    eo_eec_prune_t.at(0).at(0) = 0;
    dist = 0; num_filled = 1;
    while(num_filled != num_eo*num_e_comb){
      for(int i_eo=0; i_eo<num_eo; i_eo++){
        for(int i_eec=0; i_eec<num_e_comb; i_eec++){
          if(eo_eec_prune_t.at(i_eo).at(i_eec) == dist){
            for(int i_move=0; i_move<18; i_move++){
              int next_eo = eo_move_t.at(i_eo).at(i_move);
              int next_eec = e_comb_t.at(i_eec).at(i_move);
              if(eo_eec_prune_t.at(next_eo).at(next_eec)==-1){
                eo_eec_prune_t.at(next_eo).at(next_eec) = dist + 1;
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
    cp_eep_prune_t.at(0).at(0) = 0;
    dist = 0; num_filled = 1;
    while(num_filled != num_cp*num_eep){
      for(int i_cp=0; i_cp<num_cp; i_cp++){
        for(int i_eep=0; i_eep<num_eep; i_eep++){
          if(cp_eep_prune_t.at(i_cp).at(i_eep) == dist){
            for(int i_move=0; i_move<10; i_move++){
              int next_cp = cp_move_t.at(i_cp).at(i_move);
              int next_eep = eep_move_t.at(i_eep).at(i_move);
              if(cp_eep_prune_t.at(next_cp).at(next_eep)==-1){
                cp_eep_prune_t.at(next_cp).at(next_eep) = dist + 1;
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
    udep_eep_prune_t.at(0).at(0) = 0;
    dist = 0; num_filled = 1;
    while(num_filled != num_udep*num_eep){
      for(int i_udep=0; i_udep<num_udep; i_udep++){
        for(int i_eep=0; i_eep<num_eep; i_eep++){
          if(udep_eep_prune_t.at(i_udep).at(i_eep) == dist){
            for(int i_move=0; i_move<10; i_move++){
              int next_udep = udep_move_t.at(i_udep).at(i_move);
              int next_eep = eep_move_t.at(i_eep).at(i_move);
              if(udep_eep_prune_t.at(next_udep).at(next_eep)==-1){
                udep_eep_prune_t.at(next_udep).at(next_eep) = dist + 1;
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
  
  /*bool depth_lim_search(State &state,int depth){
    if(depth==0&&state.is_solved()) return 1;
    if(depth==0) return 0;
    
    if(prune(depth,state)) return 0;
    string prev_move = "0";
    if(current_sol.size()) prev_move = current_sol.back();
    
    for(auto move_name:moves_names){
      if(!is_move_available(prev_move,move_name)) continue;
      current_sol.emplace_back(move_name);
      auto s2 = state;
      moves(s2,move_name);
      if(depth_lim_search(s2,depth-1)) return 1;
      current_sol.pop_back();
    }
    return 0;
  }*/
  
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
    
    if(max(cp_eep_prune_t.at(cp_idx).at(eep_idx),udep_eep_prune_t.at(udep_idx).at(eep_idx))>depth) return 0;
    
    string prev_move = "0";
    if(current_sol_ph2.size()) prev_move = current_sol_ph2.back();
    else if(current_sol_ph1.size()) prev_move = current_sol_ph1.back();
    
    for(int move_idx=0; move_idx<10; move_idx++){
      string move_name = moves_names_ph2.at(move_idx);
      if(!is_move_available(prev_move,move_name)) continue;
      current_sol_ph2.emplace_back(move_name);
      int next_cp_idx = cp_move_t.at(cp_idx).at(move_idx);
      int next_udep_idx = udep_move_t.at(udep_idx).at(move_idx);
      int next_eep_idx = eep_move_t.at(eep_idx).at(move_idx);
      bool found = depth_lim_search_ph2(next_cp_idx,next_udep_idx,next_eep_idx,depth-1);
      current_sol_ph2.pop_back();
      if(found) return 1;
    }
    return 0;
  }
  
  bool start_ph2(State state){
    
    int cp_idx = perm_to_idx(state.cp);
    vec v2(8),v3(4);
    for(int i=0; i<8; i++){
      v2.at(i)=state.ep.at(i+4);
    }
    for(int i=0; i<4; i++){
      v3.at(i)=state.ep.at(i);
    }
    int udep_idx = perm_to_idx(v2);
    int eep_idx = perm_to_idx(v3);
    int depth = 0;
    while(depth<=max_sol_len-(int)current_sol_ph1.size()){
      if(depth_lim_search_ph2(cp_idx,udep_idx,eep_idx,depth)) return 1;
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
    
    if(max(co_eec_prune_t.at(co_idx).at(e_comb_idx),eo_eec_prune_t.at(eo_idx).at(e_comb_idx))>depth) return 0;
    
    string prev_move = "0";
    if(current_sol_ph1.size()) prev_move = current_sol_ph1.back();
    
    for(int move_idx=0; move_idx<18; move_idx++){
      string move_name = moves_names.at(move_idx);
      if(!is_move_available(prev_move,move_name)) continue;
      current_sol_ph1.emplace_back(move_name);      
      int next_co_idx = co_move_t.at(co_idx).at(move_idx);
      int next_eo_idx = eo_move_t.at(eo_idx).at(move_idx);
      int next_e_comb_idx = e_comb_t.at(e_comb_idx).at(move_idx);
      depth_lim_search_ph1(next_co_idx,next_eo_idx,next_e_comb_idx,depth-1);
      current_sol_ph1.pop_back();
    }
    return 0;
  }
  
  void start_search(int max_len=23){
    
    start_search_t = chrono::system_clock::now();
    
    max_sol_len = max_len;
    int co_idx = co_to_idx(state.co);
    int eo_idx = eo_to_idx(state.eo);
    vec e_comb(12);
    for(int i=0; i<12; i++){
      if(state.ep.at(i)<4) e_comb.at(i)++;
    }
    int e_comb_idx = e_comb_to_idx(e_comb);
    for(int depth=0;depth<=max_sol_len;depth++){
      
      auto now_t = chrono::system_clock::now();
      auto dur = now_t - start_search_t;
      auto sec = chrono::duration_cast<chrono::seconds>(dur).count();
      if(sec)cout<<sec<<" sec."<<endl;
      if(sec>120)break;
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