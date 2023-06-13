#include "fraction.h"
fraction make_fraction(int F, int S)
{
	fraction t;
	t.Init(F, S);
	return t;
}

void main()
{
	setlocale(LC_ALL, "");
	fraction t;
	t.Read();
	if ((t.first > 0) && (t.second > 0))
	{
		cout << "integer part F/S " << t.ipart() << "\n";
	}
	else
	{
		cout << "Enter a positive integer!" << endl;
	}
	
	fraction A;
	fraction B;
	A.Init(12, 3);
	B.Read();

	A.Show();
	cout << "A.Power(" << A.first << "," << A.second << ")=" << A.Power() << endl;

	B.Show();
	cout << "B.Power(" << B.first << "," << B.second << ")=" << B.Power() << endl;

	cout << "\nPointer method\n";
	
	fraction* X = new fraction;
	X->Read();
	X->Show();
	cout << "X.Power(" << X->first << "," << X->second << ")=" << X->Power() << endl;

	cout << "\nThe method of arrays without pointers\n";
	fraction mas[3];
	for (int i = 0; i < 3; i++)
		mas[i].Read();

	for (int i = 0; i < 3; i++)
		mas[i].Show(); 

	for (int i = 0; i < 3; i++)
	{
		cout << "mas[" << i << "].Power(" << mas[i].first << "," << mas[i].second << ")=";
		cout << mas[i].Power() << endl;
	}


	cout << "\nMethod of arrays with pointers\n";
	fraction* p_mas = new fraction[3];
	for (int i = 0; i < 3; i++)
		p_mas[i].Read();
	for (int i = 0; i < 3; i++)
		p_mas[i].Show();

	for (int i = 0; i < 3; i++)
	{
		cout << "p_mas[" << i << "].Power(" << p_mas[i].first << "," << p_mas[i].second; cout << ")=" << p_mas[i].Power() << endl;
	}

	
	cout << "Method via function" << endl;
	int y; int z;
	cout << "first:"; cin >> y;
	cout << "second:"; cin >> z;
	
	fraction F = make_fraction(y, z);
	F.Show();
}