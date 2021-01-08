#include <iostream>
#include <vector>

#include "./_editdist.h"

// returns struct of 4 values [cost, inserts, deletes, subs]
void _editdist(const int64_t *a, const unsigned int alen, const int64_t *b, const unsigned int blen, int *res) {
  if(alen == 0){
    res[0] = blen;
    res[1] = blen;
    return;
  } 
  else if(blen == 0) {
    res[0] = alen;
    res[2] = alen;
    return;
  }

  std::vector< std::vector<uint32_t> > d(alen + 1, std::vector<uint32_t>(blen + 1));
  std::vector< std::vector< std::vector<uint32_t> > > stats(alen + 1, std::vector< std::vector<uint32_t> >(blen + 1, std::vector<uint32_t>(3)));
  
  for (int i = 0; i < alen + 1; ++i){
    d[i][0] = i;
    stats[i][0][1] = i;
  }
  for (int j = 0; j < blen + 1; ++j){
    d[0][j] = j;
    stats[0][j][0] = j;
  }
  
  int cost[3];
  int op_cost[3] = {1, 1, 1};
  int min_idx;
  
  for (int i = 1; i < alen + 1; ++i) {
    for (int j = 1; j < blen + 1; ++j) {
      op_cost[2] = (a[i - 1] != b[j - 1]) ? 1 : 0;

      cost[0] = d[i][j - 1] + op_cost[0];
      cost[1] = d[i - 1][j] + op_cost[1];
      cost[2] = d[i - 1][j - 1] + op_cost[2];

      min_idx = 0;
      if (cost[1] < cost[min_idx]) min_idx = 1;
      if (cost[2] < cost[min_idx]) min_idx = 2;
      d[i][j] = cost[min_idx];

      if (min_idx == 0) stats[i][j] = stats[i][j - 1];
      else if (min_idx == 1) stats[i][j] = stats[i -1][j];
      else stats[i][j] = stats[i - 1][j - 1];

      stats[i][j][min_idx] += op_cost[min_idx];
    }
  }

  res[0] = d[alen][blen];
  res[1] = stats[alen][blen][0];
  res[2] = stats[alen][blen][1];
  res[3] = stats[alen][blen][2];
  return;
}
