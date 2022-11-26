#include "BigInteger.h"

using namespace bigNumber;

void main()
{
	BigInt x("10000","X"), y("","Y") , b;
	int64_t xSize, ySize;
	clock_t start, end;

	cout << "Enter X's Size : " << endl;
	cin >> xSize;

	cout << "Enter Y's Size : " << endl;
	cin >> ySize;

	x.beRandom(xSize);
	y.beRandom(ySize);

	start = clock();
	cout << x << endl << y << endl << endl;

	cout << "X * Y : " << endl << x * y << endl << endl;
	
	cout << "X / Y : " << endl << x / y << endl << endl;

	cout << "X mod Y : " << endl << x % y << endl << endl;

	cout << "X + Y : " << endl << x + y << endl << endl;

	cout << "X - Y : " << endl << x - y << endl << endl;

	bool status = false;

//	b = x.toBinary();

//	cout << "Binary X : " << endl << b << endl << endl;

//	cout << "Decimal X : " << endl << b.toDecimal() << endl << endl;

	cout << "X ++ : " << endl << x++ << endl << endl;

	cout << "++ Y : " << endl << ++y << endl << endl;

	cout << "X -- : " << endl << x-- << endl << endl;

	cout << "-- Y : " << endl << --y << endl << endl;

	cout << "X * 10 ^ 1000" << endl << x.multiply10(1000) << endl;

	cout << "X * 3 : " << endl << digitMult(x,3) << endl << endl;

//	cout << "Sqrt(X) : " << endl << sqrt(x) << endl << endl;
/*
	try
	{
		b = powMod(x, y, 100);
		cout << "Pow Mod (x,y,100) : " << endl << b << endl << endl;
	}
	catch (exception& e)
	{
		cout << e.what();
	}
	*/
//	cout << "x pow y" << endl << pow(x, y) << endl << endl;

	end = clock();

	cout << "Time " << (end - start)/CLOCKS_PER_SEC << endl << endl;
}