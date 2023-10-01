// Time complexity : O(word.size())
// Space complexity : O(1)

class Solution {
public:
    long long
    countVowels(string word) {
        // Determining all the substrings and counting the number of vowels in each of
        // them involves a substantial perf hit due to the huge number of combinations
        
        // Instead, adopt the approach of determining the number of substrings each vowel
        // char in the string is a part up and add up the total count of such substrings
        auto wSz = word.size();
        // A char word[i] at index 'i' in the string (0-indexed) is a part of every substring
        // which start at any of the indices [0, i] (i.e a total of i - 0 + 1 start indices)
        // and which ends at any of the indices [i, wSz - 1] (i.e a total if wSz - i + 1
        // end indices)
        // => there are a total of (i + 1) * (wSz - i) substrings containing char word[i]

        long long nAllSubstringVowels = 0;
        // Iterate over every char in word sequentially
        for (auto i = 0; i != wSz; ++i) {
            if (isVowel(word[i])) {
                // Current char is a vowel. Compute the number of substrings it
                // is a part of and add up the total
                nAllSubstringVowels += ((long long)(i + 1)) * (wSz - i);
            }
        }
        
        return nAllSubstringVowels;
    }
    
private:
    
    inline bool
    isVowel(char c) {
        return ('a' == c) || ('e' == c) || ('i' == c) || ('o' == c) || ('u' == c);
    }
};
