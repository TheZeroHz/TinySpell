#include "TinySpell.h"

TinySpell::TinySpell() {}

bool TinySpell::loadDictionary(File &file) {
    if (!file) {
        Serial.println("Invalid file passed!");
        return false;
    }

    specialTokens.clear();
    contractions.clear();
    mainWords.clear();

    while (file.available()) {
        String line = file.readStringUntil('\n');
        line.trim();
        if (!line.isEmpty()) {
            categorizeEntry(line);
        }
    }
    file.close();
    return true;
}

void TinySpell::categorizeEntry(const String &line) {
    if (line.startsWith("'") || line.indexOf("'") != -1) {
        // Contractions or informal terms
        contractions[line] = line; // Map to itself for now
    } else if (line.startsWith(".") || line.startsWith("!") || line.startsWith("?") || line.startsWith("#")) {
        // Special tokens
        int splitIndex = line.indexOf(' ');
        if (splitIndex != -1) {
            // Capture key and value correctly
            String key = line.substring(0, splitIndex); // Get the key part
            key.trim();  // Trim it separately

            String value = line.substring(splitIndex + 1); // Get the value part
            value.trim(); // Trim it separately

            specialTokens[key] = value;  // Add to specialTokens map
        }
    } else {
        // Regular words
        mainWords.push_back(line); // Add to mainWords
    }
}


String TinySpell::preprocess(const String &word) {
    String cleanWord = word;
    cleanWord.toLowerCase();
    cleanWord.trim();
    return cleanWord;
}

bool TinySpell::checkWord(const String &word) {
    String cleanWord = preprocess(word);

    for (const String &w : mainWords) {
        if (w.equalsIgnoreCase(cleanWord)) {
            return true;
        }
    }

    if (contractions.find(cleanWord) != contractions.end()) {
        return true;
    }

    if (specialTokens.find(cleanWord) != specialTokens.end()) {
        return true;
    }

    return false;
}

std::vector<String> TinySpell::suggestCorrections(const String &word, size_t maxSuggestions) {
    std::vector<std::pair<int, String>> candidates;

    for (const String &dictWord : mainWords) {
        int dist = levenshteinDistance(preprocess(word), dictWord);
        candidates.push_back({dist, dictWord});
    }

    std::sort(candidates.begin(), candidates.end(),
              [](const std::pair<int, String> &a, const std::pair<int, String> &b) {
                  return a.first < b.first;
              });

    std::vector<String> suggestions;
    for (size_t i = 0; i < maxSuggestions && i < candidates.size(); ++i) {
        suggestions.push_back(candidates[i].second);
    }

    return suggestions;
}

int TinySpell::levenshteinDistance(const String &a, const String &b) {
    size_t lenA = a.length(), lenB = b.length();
    std::vector<std::vector<int>> dp(lenA + 1, std::vector<int>(lenB + 1));

    for (size_t i = 0; i <= lenA; ++i) dp[i][0] = i;
    for (size_t j = 0; j <= lenB; ++j) dp[0][j] = j;

    for (size_t i = 1; i <= lenA; ++i) {
        for (size_t j = 1; j <= lenB; ++j) {
            int cost = (a[i - 1] == b[j - 1]) ? 0 : 1;
            dp[i][j] = std::min({dp[i - 1][j] + 1, dp[i][j - 1] + 1, dp[i - 1][j - 1] + cost});
        }
    }
    return dp[lenA][lenB];
}
