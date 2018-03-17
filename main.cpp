#include <iostream>
#include <fstream>
#include <experimental/filesystem>
#include <vector>
#include <set>
#include <string>
#include <boost/timer.hpp>
#include "avl.h"


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
	string word;
	int command;

	AVL *avl = new AVL;
	//Tree25 *tree25 = new Tree25;
	struct AVLNode *root = NULL;
	boost::timer t;
 	double elapsedTimeAVL;


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
		root = avl->insert(root, word);
	}
	cout << "Done with inserting to AVL" << endl << endl;
	
	// for(string word: wordList) {
	// 	tree25->insert(word);
	// }
	// tree25->traverse();

	while (true) {
    	cin >> command;

    	switch(command) {
    	case 1:
      	{
			string wordToSearch;
			bool wordExistsAVL;
			cin >> wordToSearch;
			t.restart();
			wordExistsAVL = avl->search(root, wordToSearch);
			elapsedTimeAVL = t.elapsed();
			// t.restart();
			// wordExistsHT = hashTable->search(wordToSearch);
			// elapsedTimeHT = t.elapsed();
			if (wordExistsAVL)
				cout << "True" << endl;
			else
				cout << "False" << endl;
			cout << fixed << "AVL: " << elapsedTimeAVL << endl;
			//cout << fixed << "Hash: " << elapsedTimeHT << endl;
		    }
     		break;
    	case 2:
      	{
			string wordToInsert;
			cin >> wordToInsert;
			t.restart();
			avl->insert(root, wordToInsert);
			elapsedTimeAVL = t.elapsed();
			// t.restart();
			// hashTable->insert(wordToInsert);
			// elapsedTimeHT = t.elapsed();
			cout << fixed << "AVL: " << elapsedTimeAVL << endl;
			//cout << fixed << "Hash: " << elapsedTimeHT << endl;
			avl->inOrder(root);
		}
		break;
    	case 3:
      	{
			string wordToDelete;
			cin >> wordToDelete;
			t.restart();
			root = avl->deleteNode(root, wordToDelete);
			elapsedTimeAVL = t.elapsed();
			// t.restart();
			// hashTable->deleteWord(wordToDelete);
			// elapsedTimeHT = t.elapsed();
			cout << fixed << "AVL: " << elapsedTimeAVL << endl;
			//cout << fixed << "Hash: " << elapsedTimeHT << endl;
			avl->inOrder(root);
    	}
    	break;
    	case 4:
     	{
			t.restart();
			avl->sort(root);
			elapsedTimeAVL = t.elapsed();
			// t.restart();
			// hashTable->sort();
			// elapsedTimeHT = t.elapsed();
			cout << "/output.txt" << endl;
			cout << fixed << "AVL: " << elapsedTimeAVL << endl;
			//cout << fixed << "Hash: " << elapsedTimeHT << endl;
		}
		break;
    	case 5:
      	{
			string startWord, endWord;
			cin >> startWord >> endWord;
			t.restart();
			avl->rangeSearch(root, startWord, endWord);
			elapsedTimeAVL = t.elapsed();
			cout << endl;
			// t.restart();
			// hashTable->rangeSearch(startWord, endWord);
			// elapsedTimeHT = t.elapsed();
			cout << fixed << "AVL: " << elapsedTimeAVL << endl;
			//cout << fixed << "Hash: " << elapsedTimeHT << endl;
      	}
   		}
	}
	return 0;

}
