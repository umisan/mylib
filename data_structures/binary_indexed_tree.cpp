#include <iostream>
#include <vector>

using namespace std;

class BinaryIndexedTree{
	public:
		BinaryIndexedTree(int n);
		void add(int i, int x);
		int sum(int i);
	private:
		vector<int> nodes;	//1-indexed
		void init(int n);
};

BinaryIndexedTree::BinaryIndexedTree(int n)
{
	init(n);
}

void BinaryIndexedTree::init(int n)
{
	//ノードの値を0に初期化
	for(int i = 0; i < n + 1; i++)
	{
		nodes.push_back(0);
	}
}

void BinaryIndexedTree::add(int i, int x)
{
	//iの最後の1が立っているビットを足していく
	while(i <= nodes.size())
	{
		nodes[i] += x;
		i += i & -i;
	}
}

int BinaryIndexedTree::sum(int i)
{
	int result = 0;
	while(i > 0)
	{
		result += nodes[i];
		i -= i & -i;
	}
	return result;
}

int main()
{
	//使用例
	BinaryIndexedTree bit(10);
	vector<int> test = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	//1-indexedに注意
	for(int i = 1; i <= 10; i++)
	{
		bit.add(i, test[i - 1]);
	}
	//10までの累積和
	cout << bit.sum(10) << endl;
	//5までの累積和
	cout << bit.sum(5) << endl;
}
