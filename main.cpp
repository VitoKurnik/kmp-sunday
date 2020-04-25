#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
using namespace std;

int *preKmp(string pattern) {
    int size = pattern.size();
    int k = 0;
    int *kmpNext = new int [size];
    kmpNext[0] = 0;
    for (int i = 1; i < size; i++) {
        while (k > 0 && pattern[k] != pattern[i]) {
            k = kmpNext[k-1];
        }

        if (pattern[k] == pattern[i]) {
            k = k + 1;
        }
        kmpNext[i] = k;
    }

    return kmpNext;
}

void kmp(string pattern, string text) {
    int* kmpNext = preKmp(pattern);
    int matchedPos = 0;
    ofstream output("out.txt");
    for (int i = 0; i < text.length(); i++) {
        while (matchedPos > 0 && pattern[matchedPos] != text[i]) {
            matchedPos = kmpNext[matchedPos-1];
        }

        if (pattern[matchedPos] == text[i]) {
            matchedPos = matchedPos + 1;
        }

        if (matchedPos == (pattern.length())) {
            output << i - (pattern.length()-1) << ' ';
        }
    }

    output.close();
}

void bch(string str, int size, int badChar[256]) {
    for (int i = 0; i < 256; i++) {
        badChar[i] = -1;
    }

    for (int i = 0; i < size; i++) {
        badChar[(int) str[i]] = i;
    }
}

void sunday(string pattern, string text) {
    int m = pattern.size();
    int n = text.size();
    int badChar[256];
    int s = 0;
    ofstream output("out.txt");

    bch(pattern, m, badChar);
    while (s <= (n-m)) {
        int j = m - 1;

        while (j >= 0 && pattern[j] == text[s+j]) {
            j--;
        }

        if (j < 0) {
            output << s << ' ';
            s += (s + m < n)? m-badChar[text[s+m]] : 1;
        } else {
            s += max(1, j - badChar[text[s+j]]);
        }
    }

    output.close();
}

int main(int argc, const char* argv[]) {
    string pattern;

    if (argc < 3) return 0;
    int option = atoi(argv[1]);
    pattern = argv[2];

    ifstream input(argv[3]);
    string text( (istreambuf_iterator<char>(input) ),
                 (istreambuf_iterator<char>()    ) );

    if (option == 0) {
        kmp(pattern, text);
    }

    else if (option == 1) {
        sunday(pattern, text);
    }

    else {
        return 0;
    }

    input.close();

    return 0;
}
