import java.io.*;
import java.math.*;
import java.util.*;

public class Main
{
    public static final int maxn = 2000;
    public static BigInteger[][] f = new BigInteger[maxn*2+5][2];
    //public static BigInteger[] sz = new BigInteger[maxn*2+5];
    public static int[][] son = new int[maxn*2+5][2];
    public static String[] s = new String[maxn+5]; 
    public static int n;
    public static BigInteger MM = BigInteger.ONE.shiftLeft(maxn+3);
    
    public static BigInteger dfs(int now)
    {
        if(now >= n) 
        {
            f[now][0] = BigInteger.ONE;
            f[now][1] = BigInteger.ONE;
            return BigInteger.valueOf(2);
        }
        f[now][0] = MM;
        f[now][1] = BigInteger.ZERO;
        int ls = son[now][0];
        int rs = son[now][1];
        BigInteger lsz = dfs(ls);
        BigInteger rsz = dfs(rs);
        for(int i = 0; i < 16; i++)
        {
            if(s[now].charAt(i) == '0') continue;
            for(int j = 0; j < 2; j++) for(int k = 0; k < 2; k++)
            {
                BigInteger t1 = f[ls][j];
                BigInteger t2 = f[rs][k];
                BigInteger ans = BigInteger.ZERO;
                if((i&8)>0) ans=ans.add(t1.multiply(t2));
                if((i&4)>0) ans=ans.add(t1.multiply(rsz.subtract(t2)));
                if((i&2)>0) ans=ans.add(t2.multiply(lsz.subtract(t1)));
                if((i&1)>0) ans=ans.add((lsz.subtract(t1)).multiply(rsz.subtract(t2)));
                f[now][0]=f[now][0].min(ans);
                f[now][1]=f[now][1].max(ans);
            }
        }
        return lsz.multiply(rsz);
    }
    
    public static void main(String args[])
    {
        Scanner cin = new Scanner(System.in);
        int T = cin.nextInt();
        for(int t = 1; t <= T; t++)
        {
            n = cin.nextInt();
            for(int i = 1; i < n; i++) s[i] = cin.next();
            for(int i = 1; i < n; i++) son[i][0] = son[i][1] = 0;
            for(int i = 2; i < 2*n; i++)
            {
                int u = cin.nextInt();
                if(son[u][0] == 0) son[u][0] = i;
                else son[u][1] = i;
            }
            dfs(1);
            System.out.format("Case #%d: ", t);
            System.out.println(f[1][1]);
        }
    }
}

//定义最大值、定义数组
public static final int maxn = 2000;
public static int[] a = new int[maxn*2+5];
public static BigInteger[] b = new BigInteger[maxn*2+5];

//读入、输出
Scanner cin = new Scanner(System.in);
while(cin.hasNext());
int x = cin.nextInt();
BigInteger y = cin.nextBigInteger();
String s = "-123459999999999999999999";
BigInteger c = new BigInteger(s,10);//把字符串转换成10进制的大数

System.out.format("%d\n", x);
System.out.println(y);

//排序
Arrays.Sort(a,1,n+1);

//大数
BigInteger x = BigInteger.valueOf(3);
BigInteger y = BigInteger.valueOf(4);
BigInteger z;
z = x.add(y);
z = x.subtract(y);
z = x.multiply(y);
z = x.divide(y);
z = x.remainder(y);
z = x.mod(y);//返回永远非负
z = x.max(y);
z = x.min(y);
z = x.shiftLeft(1);
z = x.shiftRight(1);
z = x.pow(2);
z = x.gcd(y);
z = x.abs();
z = x.negate();
