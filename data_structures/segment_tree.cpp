#include <iostream>
#include <limits.h>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

const int MAX_N = 1 << 17;

//セグメント木を持つグローバル配列
int n, dat[2 * MAX_N - 1];

//初期化
void init(int n_)
{
	//簡単のため、要素数を2のべき乗に
	n = 1;
	while(n < n_)
	{
		n *= 2;
	}
	//全ての値をINT_MAXに
	for (int i = 0; i < 2 * n -1; i++)
	{
		dat[i] = INT_MAX;
	}
}

//k番目の値(0-indexed)をaに変更
void update(int k, int a)
{
	//葉の節点
	k += n - 1;
	dat[k] = a;
	//登りながら更新
	while(k > 0)
	{
		k = (k - 1) / 2;
		dat[k] = min(dat[k * 2 + 1], dat[k * 2 + 2]);
	}
}

//[a, b)の最小値を求める
//後ろの方の引数は、計算の簡単のための引数
//kは節点の番号,l,rはその節点が[l, r)に対応づいていることを表す
//したがって外からはquery(a, b, 0, 0, n)として呼ぶ
int query_(int a, int b, int k, int l, int r){
	//[a, b)と[l, r)が交差しなければ、INT_MAX
	if(r <= a || b <= l){ 
		return INT_MAX;
	}

	//[a, b)が[l, r)を完全に含んでいれば、この節点の値
	if(a <= l && r <= b)
	{
		return dat[k];
	}else{
		//そうでなければ,2つの子の最小値
		int vl = query_(a, b, k * 2 + 1, l, (l + r) / 2);
		int vr = query_(a, b, k * 2 + 2, (l + r) / 2, r);
		return min(vl, vr);
	}
}

int main()
{
	int m, q;
	cin >> m >> q;
	n = m;
	vector<int> a(n, 0);
	for(int i = 0; i < n; i++)
	{
		cin >> a[i];
	}
	struct query {
		int kind;
		int f;
		int s;
	};
	vector<query> queries(q);
	for(int i = 0; i < q; i++){
		int kind, f, s;
		cin >> kind >> f >> s;
		query q = {kind, f, s};
		queries[i] = q;
	}

	//セグメント木の構築
	init(m);	
	for(int i = 0; i < m; i++)
	{
		update(i, a[i]);
	}
	for(int i = 0; i < q; i++)
	{
		if(queries[i].kind == 1)
		{
			int result = query_(queries[i].f - 1, 
					queries[i].s, 0, 0, n);
			cout << result << endl;
		}else{
			update(queries[i].f - 1, queries[i].s);
		}
	}
	return 0;
}
