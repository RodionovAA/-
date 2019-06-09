
#include "stdafx.h"
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <list>

using namespace std;

const int Maxlen = 100000;

typedef int TELEM;



class TBitField
	{
	
	private:
	TELEM *pMem;
	int Bitlen;
	int Memlen;

	public:
		TBitField (){};

		TBitField (int len)
		{ 
			if (len < 0 || len > Maxlen)
			throw "incorrect size";
			Bitlen = len;
			Memlen = len/(sizeof(TELEM)*8)+1;
			pMem = new TELEM[Memlen];
			for (int i = 0; i < Memlen; i++)
			{
				pMem[i]=0;
			};
		}



		TBitField (const TBitField &bf)
		{	
			Bitlen = bf.Bitlen;
			Memlen = bf.Memlen;
			pMem = new TELEM[Memlen];
			//copy(bf.pMem,bf.pMem+Memlen,pMem);
		}

		~TBitField()
		{
			delete [] pMem;
		}

	private:
		
		int GetMemIndex (int n)
		{
			return n/(sizeof(TELEM)*8);
		}

		TELEM GetMemMask (int n)
		{
			return (TELEM)(1<<(n%(sizeof(TELEM)*8)));
		}

		public:
			void SetBit (int n)
			{
				if(n<0 || n > Bitlen)
					throw "incorrect index";
				GetMemMask(n);
				pMem[GetMemIndex(n)]|=GetMemMask(n);
			}

			int non_zero_count()
				{
					
					int counter=0;
					for (int i=2; i <= Size(); i++)
					{
						if (GetBit(i) == 1) counter ++;
					}

					return counter;
				}



			int GetBit (int n)
			{
				if(n<0 || n > Bitlen)
					throw "incorrect index";
				if (pMem[GetMemIndex(n)]&GetMemMask(n)) return 1;
				return 0;
			}

			int Size() const
			{
				return Bitlen;
			}
			
			void Clearbit(int n)
			{
				pMem[GetMemIndex(n)]&=~GetMemMask(n);
			}


			bool& TBitField:: operator[](TELEM idx)
			{
				bool val = GetBit(idx) == 1 ? true : false;
				return val;
			}
};



		

int _tmain(int argc, _TCHAR* argv[])
{
	int n; //число на входе оно же длина битового поля
	int p=2;//для вычеркивая непрострых чисел

	std::cin>>n;//прочитать чило n

	TBitField Bit(n);

	for (int i = 0; i < n; ++i)
	{
		Bit.SetBit(i);
	};


	unsigned int startBit = 2;
	while (startBit < (Bit.Size() / 2 + 1))
	{
		if (Bit.GetBit(startBit))
		{
			int pos = startBit;
			while (pos < Bit.Size())
			{
				pos += startBit;
				if (pos < Bit.Size())
				{
					Bit.Clearbit(pos);
				}
			}
		}
		++startBit;
	};
	ofstream outfile ("output.txt");
	setlocale(0,"");
	for (int i = 2; i <= n; ++i)
	{
		if (Bit[i] == 1)
		outfile << i << " ";
	};


	system("pause");
	return 0;
}