import java.io.*;
import java.util.*;
import java.math.*;

public class FairWarning {

  static int MAXN = 1000;
  static BigInteger[] times = new BigInteger[MAXN];
  static BigInteger BIGZERO = BigInteger.valueOf(0);

  public static void main(String[] args) throws IOException {

    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    StringTokenizer st = new StringTokenizer(br.readLine());

    int C = Integer.parseInt(st.nextToken());

    for (int test = 1; test <= C; ++test) {

      // read N
      st = new StringTokenizer(br.readLine());
      int N = Integer.parseInt(st.nextToken());

      // read times
      for (int i = 0; i < N; ++i) {
        times[i] = new BigInteger(st.nextToken());
      }

      // find T
      BigInteger T = times[1].subtract(times[0]);
      for (int i = 0; i < N-1; ++i) {
        T = T.gcd(times[i].subtract(times[i+1]));
      }

      // find Y
      BigInteger mod = times[0].mod(T);      
      BigInteger Y = mod.compareTo(BIGZERO) == 0 ?  BIGZERO : T.subtract(mod);

      // print answer
      System.out.println(String.format("Case #%d: %s", test, Y));
    }
  }
}


