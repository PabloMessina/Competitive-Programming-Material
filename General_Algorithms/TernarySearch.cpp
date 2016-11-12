int times = 100;
double left = 0.0;
double right = 1000.0;
double ans, m1, m2, v1, v2, third;

while (times--) {
  third = (right - left) / 3.0;
  m1 = left + third;
  m2 = right - third;
  v1 = eval(m1);
  v2 = eval(m2);
  if (v1 < v2)
    left = m1;
  else if(v2  < v1)
    right = m2;
  else
    left = m1, right = m2;
}

ans = (v1 + v2) * 0.5;