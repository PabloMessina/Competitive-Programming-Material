import java.io.*;
import java.util.*;
import java.math.*;

public class G {

  static class Node {
    Node[] children;
    public Node() {
      children = new Node[]{null, null};
    }
  }

  static class Pair {
    int v; int cost; 
    public Pair(int v, int cost) {
      this.v = v;
      this.cost = cost;
    }
  }

  static int N;
  static int D[];
  static ArrayList<Pair>[] g;
  static Node root = new Node();

  static void dfs(int u, int p, int d) {
    D[u] = d;
    for (Pair i : g[u])
      if (i.v !=  p)
        dfs(i.v, u, d^i.cost);
  }

  static void expand_trie(int bits) {
    Node curr = root;
    for (int i = 30; i >= 0; --i) {
      int b = (bits >> i) & 1;
      if (curr.children[b] == null)
        curr.children[b] = new Node();
      curr = curr.children[b];
    }
  }

  static int find_max(int target) {
    int ans = 0;
    Node curr = root;
    for (int i = 30; i>=0; --i) {
      int b = (target >> i) & 1;
      if (curr.children[b] != null) {
        ans |= (1 << i);
        curr = curr.children[b];
      } else if (curr.children[1-b] != null) {
        curr = curr.children[1-b];
      } else {
        break;
      }
    }
    return ans;
  }

  public static void main(String[] args) throws IOException {

    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    StringTokenizer st = new StringTokenizer(br.readLine());

    N = Integer.parseInt(st.nextToken());
    g = new ArrayList[N];
    for (int i = 0; i < N; ++i)
      g[i] = new ArrayList<Pair>();

    D = new int[N];
    for (int i = 1; i < N; ++i) {
      st = new StringTokenizer(br.readLine());
      int a = Integer.parseInt(st.nextToken());
      int b = Integer.parseInt(st.nextToken());
      int c = Integer.parseInt(st.nextToken());
      --a; --b;
      g[a].add(new Pair(b, c));
      g[b].add(new Pair(a, c));
    }

    dfs(0, -1, 0);

    for (int i = 0; i < N; ++i)
      expand_trie(D[i]);

    for (int i = 0; i < N; ++i)
      System.out.printf("%d\n", find_max(D[i] ^ Integer.MAX_VALUE));
  }
}


