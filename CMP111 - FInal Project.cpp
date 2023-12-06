#include <iostream>
#include <sstream>
#include <unordered_set>
#include <algorithm>

bool isUppercase(char c) {
    return std::isupper(static_cast<unsigned char>(c)) != 0;
}
bool isSentenceStart(const std::string &sentence) {
    for (char c : sentence) {
        if (!std::isspace(c)) {
            return isUppercase(c);
        }
    }
    return false;
}

bool hasCorrectPunctuation(const std::string &sentence) {
    if (!sentence.empty()) {
        char lastChar = sentence.back();
        return lastChar == '.' || lastChar == '!' || lastChar == '?';
    }
    return false;
}

bool hasCorrectSpelling(const std::string &word, const std::unordered_set<std::string> &dictionary) {
    std::string cleanedWord = word;
    if (cleanedWord.size() > 1) {
        cleanedWord.erase(std::remove_if(cleanedWord.begin(), cleanedWord.end(), ::ispunct), cleanedWord.end());
    }

    std::transform(cleanedWord.begin(), cleanedWord.end(), cleanedWord.begin(), ::tolower);

    return dictionary.find(cleanedWord) != dictionary.end();
}

void checkGrammar(const std::string &sentence, const std::unordered_set<std::string> &dictionary) {
    
    if (!isSentenceStart(sentence)) {
        std::cout << "Error: Sentence does not start with an uppercase letter: '" << sentence << "'\n";
        return;
    }
  
    if (!hasCorrectPunctuation(sentence)) {
        std::cout << "Error: Sentence does not end with correct punctuation: '" << sentence << "'\n";
        return;
    }

    std::stringstream ss(sentence);
    std::string word;
    while (ss >> word) {
     
        if (!hasCorrectSpelling(word, dictionary)) {
            std::cout << "Error: Possible misspelled word in the sentence: '" << word << "'\n";
            return;
        }
    }

    std::cout << "No grammatical errors found in the sentence: '" << sentence << "'\n";
}

int main() {
    std::string text;
    std::cout << "Enter text for grammar check:\n";
    std::getline(std::cin, text);
    
    std::unordered_set<std::string> dictionary = {"hello", "world", "spell", "checker", "example", "apple", "banana", "orange", "computer", "programming", "hi", "hey", "there", "good", "morning", "afternoon", "evening", "how", "are", "your", "you're", "you", "what", "what's", "up", "how's", "it", "going", "please", "thank", "excuse", "me", "am", "i'm", "sorry", "pardon", "welcome", "yes", "absolutely", "definitely", "that's", "right", "i", "agree", "for", "sure", "no", "don't", "think", "so", "disagree", "maybe", "not", "about", "do", "feel", "believe", "opinion", "on", "could", "tell", "thoughts", "really", "interesting", "more", "i'm", "intrigued", "sounds", "exciting", "was", "day", "have", "been", "to", "lately", "any", "plans", "the", "weekend", "did", "watch", "read", "hear", "weather", "where", "it", "nice", "talking", "take", "care", "see", "later", "goodbye", "a", "great", "night", "somewhere", "mall", "school", "home", "yet", "why", "doing", "with", "that", "love", "miss", "is", "from"};
    
    std::stringstream sentenceStream(text);
    std::string sentence;
    
    while (std::getline(sentenceStream, sentence, '.')) {
        if (!sentence.empty() && sentence.back() != '.') {
            sentence += '.';
        }
        checkGrammar(sentence, dictionary);
    }
    
    std::cout << "Grammar check complete.\n";
    
    return 0;
}
