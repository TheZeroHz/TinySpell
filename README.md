
---

# **TinySpell**

**TinySpell** is a lightweight and efficient spell checker library designed for resource-constrained environments like the **ESP32**. It provides dynamic dictionary loading, spell checking, and intelligent suggestions, making it ideal for microcontroller-based projects and embedded systems.

## **Features**
- 📚 **Dynamic Dictionary Loading**: Load large dictionaries directly from an SD card, supporting extensive word lists without exhausting memory.
- ✍️ **Spell Checking**: Validate words against a dictionary to check spelling accuracy.
- 🤖 **Intelligent Suggestions**: Suggest corrections for misspelled words using fuzzy matching (Levenshtein Distance).
- 🔤 **Supports Special Tokens**: Handle special tokens (e.g., `#`, `!`, `.`), contractions (e.g., `'ll`, `'cause`), and regular words.
- 💾 **Memory Efficient**: Optimized for low-memory devices, making it perfect for IoT and embedded systems.
- 🛠 **Easy Integration**: Designed to work seamlessly with Arduino and ESP32 projects.

---

## **Applications**
- **IoT and Embedded Systems**: Enable text-based spell checking on devices with limited memory.
- **Educational Tools**: Build language learning applications with real-time spelling feedback.
- **Text Correction**: Use in microcontroller-based text processing applications.

---

## **How It Works**
1. **Dictionary Management**: The library supports dictionaries stored as plain text files on an SD card. Each file can include:
   - **Main Words**: Standard English words.
   - **Contractions**: Common contractions like `'ll`, `'s`, etc.
   - **Special Tokens**: Symbols and their descriptions (e.g., `!exclamation-point`).
2. **Dynamic Loading**: Loads only the required dictionary files to minimize memory usage.
3. **Spell Checking**: Verifies if a word exists in the loaded dictionaries.
4. **Suggestions**: Provides corrections for misspelled words using a fuzzy matching algorithm.

---

## **Installation**
1. Clone or download this repository.
2. Place the library folder in your Arduino `libraries` directory.
3. Add dictionary files (e.g., `wordlist.txt`) to an SD card for use with the library.

---

## **Usage**

### **Setup**
1. Ensure the SD card is connected to your ESP32 device.
2. Include the TinySpell library in your sketch.

### **Example Code**
```cpp
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
```

---

## **File Structure**
### **SD Card Dictionary Format**
- **`wordlist.txt`**: A plain text file with one word, token, or contraction per line.
  Example:
  ```
  hello
  world
  !exclamation-point
  #sharp-sign
  'cause
  'll
  ```

### **Library Directory**
- `/TinySpell`:
  - `TinySpell.h`
  - `TinySpell.cpp`
  - `examples/` (Example sketches)

---

## **API Reference**

### **Methods**
1. **`bool loadDictionary(File &file)`**
   - Loads a dictionary file from the SD card.
   - **Parameters**: `File &file` – The dictionary file.
   - **Returns**: `true` if successful, `false` otherwise.

2. **`bool checkWord(const String &word)`**
   - Checks if the word exists in the dictionary.
   - **Parameters**: `const String &word` – The word to check.
   - **Returns**: `true` if the word is valid, `false` otherwise.

3. **`std::vector<String> suggestCorrections(const String &word, size_t maxSuggestions)`**
   - Provides suggestions for misspelled words.
   - **Parameters**:
     - `const String &word` – The misspelled word.
     - `size_t maxSuggestions` – Maximum number of suggestions.
   - **Returns**: A vector of suggested words.

---

## **Contributing**
Contributions are welcome! Feel free to submit pull requests for improvements, bug fixes, or new features.

---

## **Credits**
Created by Rakib Hasan for lightweight and efficient spell checking on embedded devices.
