#ifndef TINYSPELL_H
#define TINYSPELL_H

#include <Arduino.h>
#include <FS.h> // File system for handling files
#include <map>
#include <vector>

class TinySpell {
public:
    TinySpell();
    bool loadDictionary(File &file);
    bool checkWord(const String &word);
    std::vector<String> suggestCorrections(const String &word, size_t maxSuggestions);

private:
    std::map<String, String> specialTokens;
    std::map<String, String> contractions;
    std::vector<String> mainWords;

    void categorizeEntry(const String &line);
    String preprocess(const String &word);
    int levenshteinDistance(const String &a, const String &b);
};

#endif // TinySpell_H
