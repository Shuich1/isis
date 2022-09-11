#include <iostream>
#include <ctime>
#include <math.h>

using namespace std;

template<class T>
class din
{
private:
	int size;
	T* array;
public:
	din(int size) {
		this->size = size;
		array = new T[size];
		if (array == nullptr)
			throw bad_alloc();
		else {
			for (int i = 0; i < size; i++)
				array[i] = ((T)(rand() % 10000)) / (T)100;
		}
		
	}

	~din() {
		delete[]array;
	}

	din(din& copy) {
		array = new T[size];
		if (array == nullptr)
			throw bad_alloc();
		else {
			array = new T[copy.size];
			for (int i = 0; i < copy.size; i++)
				array[i] = copy.array[i];
			size = copy.size;
		}
	}
	T getarr(int i) {
		if (i > size || i < 0)
			throw out_of_range("Out of array length");
		else
		return array[i];
	}

	void setarr(int i, T value) {
		if (value < -100 || value > 100)
			throw invalid_argument("The number must be between -100 and 100");
		else if (i > size || i < 0)
			throw out_of_range("Out of array length");
		else
			array[i] = value;
	}

	void sum(din& stream) {
		int tempsize = (size > stream.size ? stream.size : size);
		for (int i = 0; i < tempsize; i++)
			array[i] += stream.array[i];
	}

	void sub(din& stream) {
		int tempsize = (size > stream.size ? stream.size : size);
		for (int i = 0; i < tempsize; i++)
			array[i] -= stream.array[i];
	}

	void show() {
		for (int i = 0; i < size; i++)
			cout << array[i] << " ";
		cout << endl;
	}
	void pushback(T value) {
		T* tmpArr = new T[size];
		if (tmpArr == nullptr)
			throw bad_alloc();

		for (int i = 0; i < size; i++)
			tmpArr[i] = array[i];

		size++;
		delete[]array;

		array = new T[size];
		if (array == nullptr)
			throw bad_alloc();

		for (int i = 0; i < size; i++)
			array[i] = tmpArr[i];

		array[size - 1] = value;
		delete[]tmpArr;
	}

	din& operator=(const din& copy) {
		try {
			array = new T[size];
		}
		catch (std::bad_alloc&) {
			cout << "Exception bad_alloc: ñannot allocate memory for data" << endl;
			delete[]array;
			exit(0);
		}
		array = new T[copy.size];
		for (int i = 0; i < copy.size; i++)
			array[i] = copy.array[i];
		size = copy.size;
		return *this;
	}

	template <typename T> friend  ostream& operator << (ostream& out, const din<T>& din);
	template <typename T> friend  T distance (din<T>& a, din<T>& b);
};

template<typename T>
ostream& operator<<(ostream& out, const din<T>& din)
{
	for (int i = 0; i < din.size; i++)
		out << din.array[i] << " ";
	out << endl;
	return out;
}

template<typename T>
T distance(din<T>& a, din<T>& b)
{	
	if (a.size != b.size)
		return -1;
	T result = 0;
	for (int i = 0; i < a.size; i++) {
		result += (a.array[i] - b.array[i]) * (a.array[i] - b.array[i]);
	}
	return sqrt(result);
}


int main() {
	srand(time(NULL));

	try {
		din <double> a(5);
		din <double> b(5);
		cout << "*Arrays allocated*" << endl << "********************" << endl;
		cout << a;
		cout << b;
		cout << "Euclidean distance = " << distance(a, b) << endl;
		cout << "********************" << endl;

		cout << "a[0] = " << a.getarr(0) << endl;
		a.setarr(0, 32);
		cout << "New array a: ";
		cout << a;
		cout << "********************" << endl;

		din <double> c = a;
		cout << "Array c, copied from a: ";
		cout << c;
		cout << "********************" << endl;
		cout << "a = a + b" << endl;
		a.sum(b);
		cout << a;
		cout << "********************" << endl;
		cout << "a = a - b" << endl;
		a.sub(b);
		cout << a;
		cout << "********************" << endl;
		cout << "Array a pushback: ";
		a.pushback(81);
		cout << a;
	}
	catch (bad_alloc&) {
		cout << "Bad allocation";
		exit(0);
	}
	catch (out_of_range&) {
		cout << "Out of range";
	}
	catch (invalid_argument&) {
		cout << "Invalid argument";

	}

}
