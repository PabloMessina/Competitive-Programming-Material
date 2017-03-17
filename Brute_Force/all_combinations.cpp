/* ========================= */
/*  Try all 2^n combinations */
/* ========================= */

void all_combs(vector<int> items) {
  int n = vals.size();
  int times = (1 << n);
  vector<int> comb(n, 0)

  while(times-- > 0) {

    do_something(comb)

    // generate next combination    
    int i = 0, carry = 1;
    while (i < n) {
      in[i] += carry;
      if (in[i] <= 1)
        carry = 0;
      else
        in[i] = 0;        
      // do something with i'th item
      i++;
    }
  }
}