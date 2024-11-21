#include <SPI.h>
#include <SD.h>
#include "TinySpell.h"

#define SD_CS_PIN 5

TinySpell spellChecker;

void setup() {
    Serial.begin(115200);

    if (!SD.begin(SD_CS_PIN)) {
        Serial.println("SD card initialization failed!");
        return;
    }

    File wordlist = SD.open("/wordlist.txt");
    if (!wordlist) {
        Serial.println("Failed to open wordlist.txt!");
        return;
    }

    if (!spellChecker.loadDictionary(wordlist)) {
        Serial.println("Failed to load dictionary!");
        return;
    }

    String word = "helo";
    if (spellChecker.checkWord(word)) {
        Serial.println(word + " is a valid word.");
    } else {
        Serial.println(word + " is not a valid word. Suggestions:");
        auto suggestions = spellChecker.suggestCorrections(word, 5);
        for (const auto &suggestion : suggestions) {
            Serial.println("- " + suggestion);
        }
    }
}

void loop() {
    // Additional logic
}
