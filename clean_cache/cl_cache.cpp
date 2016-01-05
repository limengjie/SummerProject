#include <iostream>
#include <vector>
#include <sys/time.h>
#include <time.h>

using namespace std;

class LongVec {
	private:
		vector<int> vec;
	public:
		LongVec(const int &);
		void increase();
		void increase(const int &);
		void show() const;

};

LongVec::LongVec(const int & size) {
	srand(time(NULL));
	for (int i = 0; i < size; ++i) {
		int elt = rand();
		vec.push_back(elt);
	}

}

void LongVec::increase() {
	for (size_t i = 0; i < vec.size(); ++i) 
		++vec.at(i);
}

void LongVec::increase(const int & n) {
	for (size_t i = 0; i < vec.size(); ++i) 
		vec.at(i) += n;
}



void LongVec::show() const {
	for (size_t i = 0; i < vec.size(); ++i) 
		cout << vec.at(i) << " ";
	cout << endl;
}



int main (int argc, char ** argv) {
	if (argc != 2) {
		cout << "Usage: cl_cache [number].\n";
		exit(1);
	}


	int num = atoi(argv[1]);
	
	LongVec V(num);
	
	//V.show();

	V.increase(5);

	//V.show();

	return 0;
}
