#include "test_str.h"


int main() {
	//compareAlgorithmsIncrementPattern();
	compareAlgorithmsIncrementText();
}

std::string random_string( size_t length )
{
    auto randchar = []() -> char
    {
        const char charset[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
        const size_t max_index = (sizeof(charset) - 1);
        return charset[ rand() % max_index ];
    };
    std::string str(length,0);
    std::generate_n( str.begin(), length, randchar );
    return str;
}

void compareAlgorithmsIncrementPattern(){

	string text = random_string(1000);
	string pattern;

	vector<double> kmpTimes;
	vector<double> edTimes;

	cout << "*** Testing Kmp and Edit Distance with incrementing pattern size *** \n\n";

	for(unsigned int i = 1000; i <= 10000; i+= 1000){

		pattern = random_string(i);

		auto start = std::chrono::high_resolution_clock::now();

		kmpMatcher(text, pattern);

		auto finish = std::chrono::high_resolution_clock::now();
		auto elapsed = chrono::duration_cast<chrono::microseconds>(finish - start).count();

		kmpTimes.push_back(elapsed);

		start = std::chrono::high_resolution_clock::now();

		editDistance(pattern, text);

		finish = std::chrono::high_resolution_clock::now();
		elapsed = chrono::duration_cast<chrono::microseconds>(finish - start).count();

		edTimes.push_back(elapsed);

	}

	for(unsigned int i = 0; i < kmpTimes.size(); i++){
		cout << "KMP time: " << kmpTimes.at(i) << "  ED time: " << edTimes.at(i) << endl;
	}

	cout << endl;

}

void compareAlgorithmsIncrementText(){

	string text;
	string pattern = random_string(1000);
	
	// compute prefix function
	int *pi = (int *)malloc(sizeof(int)*10000);
	computerPrefixFunction(pattern, pi);

	vector<double> kmpTimes;
	vector<double> edTimes;

	cout << "\n*** Testing Kmp and Edit Distance with incrementing text size *** \n\n";

	for(unsigned int i = 100; i <= 1000; i+= 100){

		text = random_string(i);

		auto start = std::chrono::high_resolution_clock::now();

		kmpMatcher(text, pattern, pi);
		//kmpMatcher(text, pattern);

		auto finish = std::chrono::high_resolution_clock::now();
		auto elapsed = chrono::duration_cast<chrono::microseconds>(finish - start).count();

		kmpTimes.push_back(elapsed);

		start = std::chrono::high_resolution_clock::now();

		editDistance(pattern, text);

		finish = std::chrono::high_resolution_clock::now();
		elapsed = chrono::duration_cast<chrono::microseconds>(finish - start).count();

		edTimes.push_back(elapsed);

	}

	for(unsigned int i = 0; i < kmpTimes.size(); i++){
		cout << "KMP time: " << kmpTimes.at(i) << "  ED time: " << edTimes.at(i) << endl;
	}

	free(pi);
}

















