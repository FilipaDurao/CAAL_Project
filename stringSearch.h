#include <string>
#include <vector>

/** 
* Struct containing the essential info for the string searching algorithmns 
*/ 
typedef struct{
  std::string stationName; ///< the stop name 
  int index;         ///< the stop index in the Graph's vector 
  int editDistance;  ///< it's current editDistance 
}Guess;

/**
 * < operator for Guess 
 */
struct cmpGuess{ 
   bool operator()(Guess * a,  Guess * b) const { 
        return a->editDistance < b->editDistance; 
    } 
}; 

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
 * @retval The number of pattern ocurrences in text
 */
int kmpMatcher(std::string text, std::string pattern);

/**
 * @see kmpMatcher
 * This is the kmpMatcher algorithm, but the prefix table is passed by reference. This is useful when the algorithm is applied on different texts, but the pattern is constant
 * @param text The text to be processed
 * @param pattern The pattern to be found in text
 * @param pi The prefix table computed by computerPrefixFunction()
 * @return int The number of pattern ocurrences in text
 */
int kmpMatcher(std::string text, std::string pattern, int pi[]);

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