#pragma once
#include<iostream>
#include<string>
#include<vector>

using namespace std;

//字符串转换为整型的算法
size_t _BKDRHash(const char *str)
{
	register size_t hash = 0;
	while (size_t ch = (size_t)*str++)
	{
		hash = hash * 131 + ch;
	}
	return hash;
}
//仿函数
template<class K>
struct HashFun
{
	int operator()(const K& key)
	{
		return key;
	}
};
//特化
template<>
struct HashFun<string>
{
	size_t operator()(const string& key)
	{
		return _BKDRHash(key.c_str());
	}
};


//位图为直接地址映射法
template<class K>
class BitMap
{
public:
	BitMap(size_t n = 0)
		:_size(0)
	{
		_bm.resize((n >> 5) + 1);
	}
	//置1
	void Set(const K& key)
	{
		int index = _Hashfun(key);
		int num = index % 32;
		_bm[index >> 5] |= 1 << num;
	}
	//清零
	void ReSet(const K& key)
	{
		int index = _Hashfun(key);
		int num = index % 32;
		_bm[index >> 5] &= ~(1 << num);
	}
	//测试是否存在
	bool Test(const K& key)
	{
		int index = _Hashfun(key);
		int num = index % 32;
		int tmp = _bm[index >> 5];
		return tmp &= (1 << num);
	}
protected:
	//哈希函数
	int _Hashfun(const K& key)
	{
		HashFun<K> hf;
		return hf(key);
	}
protected:
	vector<int> _bm;
	size_t _size;
};

//测试函数
void TestBitMap()
{
	BitMap<int> bm(100);
	bm.Set(10);
	bm.Set(55);
	bm.Set(99);
	bm.Set(40);

	cout << "10 ?:" << bm.Test(10) << endl;
	cout << "55 ?:" << bm.Test(55) << endl;
	cout << "99 ?:" << bm.Test(99) << endl;
	cout << "40 ?:" << bm.Test(40) << endl;

	bm.ReSet(10);
	cout << "10 ?:" << bm.Test(10) << endl;

}
