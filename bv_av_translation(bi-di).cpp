/*
本程序仅用于学术交流和实际应用
算法来自知乎用户 mcfx 转载请注明
以下是写程序者（不是破解算法人）的联系方式
Github : Reiame
Bilibili : 67547621
*/
#define Length 10
#define capicity 58
#include<iostream>
#include<map>
#include<math.h>
using namespace std;

map<char,int> trans_table;
map<int, char> trans_table_Reversed;
pair<char, int> Group[capicity];
pair<int, char> Group_Reversed[capicity];
char hash_char[capicity] = { '1','2','3','4' ,'5','6','7','8','9','A','B','C','D','E','F','G','H','J','K','L','M','N','P','Q','R','S','T','U','V','W','X','Y','Z','a','b','c','d','e','f','g','h','i','j','k','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
int hash_int[capicity] = { 13,12,46,31,43,18,40,28,5,54,20,15,8,39,57,45,36,38,51,42,49,52,53,7,4,9,50,10,44,34,6,25,1,26,29,56,3,24,0,47,27,22,41,16,11,37,2,35,21,17,33,30,48,23,55,32,14,19 };

map<int, int> power_table;
map<int, int> power_table_reverse;
pair<int, int> Power_Group[Length];
pair<int, int> Power_Group_Reverse[Length];
int digit[Length] = { 0,1,2,3,4,5,6,7,8,9 };
int power_distributed[Length] = { 6,2,4,8,5,9,3,7,1,0 };

void initial_hash()
{
	for (int i = 0; i < Length; i++)
	{
		Power_Group[i] = pair<int, int>(digit[i], power_distributed[i]);
		power_table.insert(Power_Group[i]);
		Power_Group_Reverse[i] = pair<int, int>(power_distributed[i], digit[i]);
		power_table_reverse.insert(Power_Group_Reverse[i]);
	}
	for (int i = 0; i < capicity; i++)
	{
		Group[i] = pair<char, int>(hash_char[i], hash_int[i]);
		trans_table.insert(Group[i]);
		Group_Reversed[i] = pair<int, char>(hash_int[i], hash_char[i]);
		trans_table_Reversed.insert(Group_Reversed[i]);
	}
}

int* Dec2Binary(unsigned long long para)
{		
	int upper_limit = 30;
	int* binary_output = new int[upper_limit] {0};
	for (int i = 0; i < upper_limit; i++)
	{
		binary_output[upper_limit -1- i] = para % 2;
		para /= 2;
	}
	return binary_output;
}

int* exclusiveor(int* B_O)
{
	int original[30] = { 0,0,1,0,1,0,1,0,0,1,0,0,1,1,1,0,1,1,0,0,1,1,0,0,1,0,0,1,0,0 };
	int* output = new int[30]{ 0 };
	for (int i = 0; i < 30; i++)
		output[i] = original[i] == B_O[i] ? 0 : 1;
	return output;
}

unsigned long long Binary2Dec(int* table)
{
	unsigned long long av_number = 0;
	for (int i = 0; i < 30; i++)
		av_number += table[i]*(unsigned long long)pow(2, 29 - i);
	return av_number;
}

class BV
{
private:
	char bv_string[Length] = {'0' };
public:
	BV() { }
	BV(const char* string_test)
	{
		for (int i = 0; i < Length; i++)
			bv_string[i] = string_test[i];
	}
	char* Getbv_string()
	{
		return bv_string;
	}
	void bv_string_update(int pointer, char replacement)
	{
		bv_string[pointer] = replacement;
	}
	void show()
	{
		for (int i = 0; i < Length; i++)
		{
			cout << bv_string[i];
		}
	}
};
class AV
{
private:
	int av_num[Length] = { 0 };
public:
	AV(){ }
	AV(unsigned long long a)
	{
		av_string_update(a);
	}
	int* Getav_num()
	{
		return av_num;
	}
	unsigned long long Getav_num_ull()
	{
		unsigned long long a = 0;
		for (int i = 0; i < Length; i++)
			a += av_num[i] * pow(10, 9 - i);
		return a;
	}
	void av_string_update(int pointer, int replacement)
	{
		av_num[pointer] = replacement;
	}
	void av_string_update(unsigned long long av)
	{
		for (int i = 0; i < 10; i++)
		{
			av_num[i] = av / (int)pow(10, 9 - i);
			av = av % (int)pow(10, 9 - i);
		}
	}
	void show()
	{
		int flag = 1;
		cout << "av";
		for (int i = 0; i < Length; i++)
		{
			if (av_num[i]) flag = 0;
			if(!flag)	cout << av_num[i];
		}
	}
};

AV BV2AV(BV& bv_test)
{
	AV av_output;
	unsigned long long temp = 0;
	int* binary_temp;

	for (int i = 0; i < Length; i++)
		temp += trans_table[bv_test.Getbv_string()[i]] * (unsigned long long)pow(capicity, power_table[i]);
	temp -= 100618342136696320;
	binary_temp = Dec2Binary(temp);
	binary_temp = exclusiveor(binary_temp);
	temp = Binary2Dec(binary_temp);
	av_output.av_string_update(temp);
	return av_output;
}

BV AV2BV(AV& av_test)
{
	BV bv_output;
	int* binary_temp = new int[58]{ 0 };
	int* av_hash = new int[10]{ 0 };
	unsigned long long temp;
	binary_temp = exclusiveor(Dec2Binary(av_test.Getav_num_ull()));
	temp = Binary2Dec(binary_temp)+ 100618342136696320;
	for (int i = 0; i < 10; i++)
	{
		av_hash[power_table_reverse[i]] = temp % capicity;
		temp = temp / capicity;
	}
	for (int i = 0; i < 10; i++)
		bv_output.bv_string_update(i, trans_table_Reversed[av_hash[i]]);
	return bv_output;
}

int main()
{
	initial_hash();
	char input[10];
	unsigned long long input_int;
	while (true)
	{
		while (true)
		{
			cout << "请输入需要转化的AV号，不需要带AV两个字母(转化BV号请输入0后按回车)：";
			cin >> input_int;
			if (!input_int) break;
			AV av_new(input_int);
			cout << "av" << input_int << " 对应 BV"; AV2BV(av_new).show();
			cout << endl;
		}
		while (true)
		{
			cout << "请输入需要转化的BV号，不需要带BV两个字母(转化AV号请输入0后按回车)：";
			cin >> input;
			if (input[0] == '0') break;
			BV bv_new(input);
			BV2AV(bv_new).show();
			cout << endl;
		}
	}
}