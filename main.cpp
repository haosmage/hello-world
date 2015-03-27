#include "VectorConstructorDestructorOperatorEqual.h"
#include <ostream>
#include "VectorCopyDestructor.h"


int main()
{
	{
		Vector2<int> a;
		//int a1 = 0;
		//a.push_back(a1);
		//MyObject1 dd(1);
		//dd.str = 3;
		for (int i = 0; i<100; ++i)
			a.push_back(i);
		a.push_back(4);
		a.push_back(5);
		//a.printData();
		//cout << a[1];
		// bug maina
		Vector2<int> c(a);
		Vector2<int> d;
		d = c;// ako komentiram tozi red raboti .....
		//d.printData();
		for (int i = 0; i<100; ++i)
			a.pop_back();
		a.pop_back();
		a.pop_back();
		a.pop_back();

		/*for (unsigned int i = 0; i < a.size(); ++i)
		{
		a1 = a[i];

		cout << a1 << endl;
		}*/


	}

	return 0;
}




//class proba
//{
//public:
//	proba()
//	{
//		cout << "proba simple constr" << endl;
//	}
//	proba(const proba & a)
//	{
//		cout << "proba "<<endl;
//	}
//	proba& operator = (const proba &a){
//		cout << "operator =" << endl;
//		return *this;
//	}
//};
//int main()
//{
//	{
//		proba a;
//		proba * b = new proba[5];
//		for (int i = 0; i < 5; ++i)
//			b[i] = a;
//	}
//	return 0;
//}