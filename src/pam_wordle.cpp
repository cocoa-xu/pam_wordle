#include "pam_wordle.h"
#include <stdio.h>
#include <cstring>
#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include <random>

PAM_EXTERN int pam_sm_authenticate(pam_handle_t *handle, int flags, int argc, const char **argv)
{
    std::ifstream ifs;
    ifs.open("/usr/share/dict/words");
    std::vector<std::string> available_words;
    std::map<std::string, bool> dict;
    if (ifs.is_open()) {
        std::string word;
        while(std::getline(ifs, word)) {
            if (word.length() == 5) {
                available_words.push_back(word);
                dict[word] = true;
            }
        }
    } else {
        return PAM_PERM_DENIED;
    }

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<size_t> dist(0, dict.size() - 1);
    size_t random_index = dist(mt);

    std::string answer = available_words[random_index];
    std::map<char, bool> exists;
    for (auto &c : answer) {
        exists[c] = true;
    }

    std::string guess;
    std::vector<std::string> guesses;
    int num_guesses = 6;

    for (int i = 0; i < num_guesses; ++i) {
        /* Asking the user for a guess */
        fprintf(stdout, "Your guess[%d/%d]: ", i + 1, num_guesses);
        std::cin >> guess;

        if (std::cin.eof()) {
            return PAM_PERM_DENIED;
        }

        if (guess.length() != 5) {
            fprintf(stderr, "Please input a word with 5 letters.\r\n");
            return PAM_PERM_DENIED;
        }

        if (dict.find(guess) == dict.end()) {
            fprintf(stdout, "%s is not in word list\r\n", guess.c_str());
            i -= 1;
            continue;
        }

        std::string result;
        for (int j = 0; j < 5; ++j) {
            if (answer[j] == guess[j]) {
                result += "\033[92;102m██\033[m ";
            } else if (exists[guess[j]]) {
                result += "\033[93;103m██\033[m ";
            } else {
                result += "\033[90;100m██\033[m ";
            }
        }
        result += "\t";
        for (int j = 0; j < 5; ++j) {
            if (answer[j] == guess[j]) {
                result += "\033[92m";
            } else if (exists[guess[j]]) {
                result += "\033[93m";
            } else {
                result += "\033[90m";
            }
            result += guess[j];
            result += "\033[m";
        }
        guesses.push_back(result);

        for (auto & guessed : guesses) {
            fprintf(stdout, "%s\r\n", guessed.c_str());
        }

        if (guess == answer) {
            return PAM_SUCCESS;
        }
        guess = "";
    }

    fprintf(stderr, "Maximum number of guess reached. It was %s\r\n", answer.c_str());
    return PAM_PERM_DENIED;
}

PAM_EXTERN int pam_sm_setcred(pam_handle_t *pamh, int flags, int argc, const char **argv) {
    return PAM_SUCCESS;
}

PAM_EXTERN int pam_sm_acct_mgmt(pam_handle_t *pamh, int flags, int argc, const char **argv)
{
    return PAM_SUCCESS;
}
