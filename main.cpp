#include <iostream>
#include <fstream>
#include <experimental/filesystem>
#include <vector>
#include <set>
#include <string>
#include "AVL.h"


using namespace std;

const set<string> STOP_WORDS = {"i", "me", "my", "myself", "we", "our", "ours", "ourselves", "you", "your", "yours", "yourself", "yourselves", "he", "him", "his", "himself", "she", "her", "hers", "herself", "it", "its", "itself", "they", "them", "their", "theirs", "themselves", "what", "which", "who", "whom", "this", "that", "these", "those", "am", "is", "are", "was", "were", "be", "been", "being", "have", "has", "had", "having", "do", "does", "did", "doing", "a", "an", "the", "and", "but", "if", "or", "becuase", "as", "until", "while", "of", "at", "by", "for", "with", "about", "against", "between", "into", "through", "during", "before", "after", "above", "below", "to", "from", "up", "down", "in", "out", "on", "off", "over", "under", "again", "further", "then", "once", "here", "there", "when", "where", "why", "how", "all", "any", "both", "each", "few", "more", "most", "other", "some", "such", "no", "nor", "not", "only", "own", "same", "so", "than", "too", "very", "s", "t", "can", "will", "just", "don", "should", "now"};
namespace fs = experimental::filesystem;

vector<fs::path> getPathNames(fs::path path) {
  vector<fs::path> pathNames;
  
  for(auto& p: fs::recursive_directory_iterator(path))
    if (is_regular_file(status(p)))
      pathNames.push_back(p.path());
  
  return pathNames;
}

int main() {

	vector<string> wordList;
	ifstream file;
	AVL *avl = new AVL;
	string word;
	AvlNode* root = NULL;


	for(const auto& pathName : getPathNames("hotels")) {
		file.open(pathName);
		if (!file.is_open()){

		}

	    while (file >> word) {
	        for(unsigned int i = 0; i < word.size(); i++) {
	        	word[i] = tolower(word[i]);
	        	if(!isalpha(word[i])) {
	        		word.erase(i, 1);
	        		i--;
	        	}
	        }
	        if(STOP_WORDS.count(word)==0 && word.size() > 0) {
	        	wordList.push_back(word);
	        }
	    }
	    file.close();
	}

	for(string word: wordList) {
		avl->insert(word, root);
	}
	avl->printInorder();

}
