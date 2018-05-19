#include "stringSearch.h"
#include <vector>
#include <sstream>
#include <algorithm>
#include <cctype>

const static std::vector<std::string> myDictionary = {"a", "o", "as", "os", "de", "da", "do"};

void computerPrefixFunction(std::string toSearch, int pi[]) {
	int m = toSearch.length();
	pi[0] = 0;
	int k = 0;

	for (int q = 1; q < m; q++) {
		while (k > 0 && toSearch[k] != toSearch[q])
			k = pi[k - 1];
		if (tolower(toSearch[k]) == tolower(toSearch[q]))
			k++;
		pi[q] = k;
	}

	return;
}


int kmpMatcher(std::string text, std::string pattern) {
	int n = text.length();
	int m = pattern.length();

	int pi[m];
	computerPrefixFunction(pattern, pi);

	int i = 0, q = 0, result = 0;

	for (; i < n; i++) {

		while (q > 0 && pattern.at(q) != text.at(i))
			q = pi[q - 1];

		if (tolower(pattern.at(q)) == tolower(text.at(i)))
			q++;

		if (q == m) {
			result++;
			q = pi[q - 1];
		}

	}

	return result;
}

int editDistance(std::string text, std::string pattern) {

	int m = pattern.length();
	int n = text.length();

	std::vector<int> cur(m + 1, 0);

	for (int i = 1; i <= m; i++)
		cur[i] = i;
	for (int j = 1; j <= n; j++) {
		int pre = cur[0];
		cur[0] = j;
		for (int i = 1; i <= m; i++) {
			int temp = cur[i];
			if (tolower(pattern.at(i - 1)) == tolower(text.at(j - 1)))
				cur[i] = pre;
			else
				cur[i] = std::min(pre + 1,
						std::min(cur[i] + 1, cur[i - 1] + 1));
			pre = temp;
		}
	}
	return cur[m];

}

std::vector<std::string> tokenize(const std::string &s){
	std::vector<std::string> result;
	std::stringstream ss(s);
	std::string item;
	while(std::getline(ss, item, ' '))
		result.push_back(item);

	return result;
}

int tokenizeAndSearch(std::string stationName, std::string userStationInput)
{
	int maxEditDistance = userStationInput.length() * 0.70;

	// tokenize the station name
	std::vector<std::string> tokens = tokenize(stationName);

	// remove some definite articles, etc.
	removeWordsFromDictionary(tokens);

	// try to find at least one token from station name, where the user input is close enough
	for (std::string s : tokens){
		int sizeDiff = userStationInput.length() - s.length();
		if (editDistance(userStationInput, s) <= maxEditDistance && (abs(sizeDiff) <= 1))
			return 0;
	}

	return -1;
}

void removeWordsFromDictionary(std::vector<std::string> &tokens){

	for (std::string token : myDictionary)
	{
		auto it = std::find(tokens.begin(), tokens.end(), token);

		if (it != tokens.end())
			tokens.erase(it);
	}
}