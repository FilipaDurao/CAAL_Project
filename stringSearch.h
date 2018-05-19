#include <string>
#include <vector>

/**
 * @brief The KMP prefix pre-processing algorithm
 * 
 * @param toSearch The pattern to be searched
 * @param pi A reference for the prefix-table to be filled
 */
void computerPrefixFunction(std::string toSearch, int pi[]);

/**
 * @brief KMP Matching algorithm
 * 
 * @param text The text to be processed
 * @param pattern The pattern to be found in text
 * @retval 0 If pattern not found
 */
int kmpMatcher(std::string text, std::string pattern);

/**
 * @brief The Levenshtein Distance algorithm
 * 
 * @param text The text to be processed
 * @param pattern The pattern to be found in text
 * @return int The number of changes in pattern for matching text
 */
int editDistance(std::string text, std::string pattern);


std::vector<std::string> tokenize(const std::string &s);


/**
 * @brief A more heavy string matching approaching, where the the text string, stationName, is splitted in tokens, and for each token tries to approximate to the userStationInput
 * Moreover, some unwanted tokens are removed, such determiners. 
 * @see removeWordsFromDictionary
 * 
 * @param stationName
 * @param userStationInput 
 * @return 0 if at least one stationName's token is close enough to userStationInput, -1 otherwise
 */
int tokenizeAndSearch(std::string stationName, std::string userStationInput);

/**
 * @brief An utility function to remove tokens from a give container of strings
 * The tokens to be removed are specified in stringSearch.cpp#myDictionary
 * 
 * @param tokens The container of tokens to be processed
 */
void removeWordsFromDictionary(std::vector<std::string> &tokens);