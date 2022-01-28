#include "pam_wordle.h"
#include <stdio.h>
#include <cstring>
#include <string>
#include <iostream>
#include <map>
#include <vector>

PAM_EXTERN int pam_sm_authenticate(pam_handle_t *handle, int flags, int argc, const char **argv)
{
    int pam_code;
    std::string answer = "hello";
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

        if (guess.length() != 5) {
            fprintf(stderr, "Please input a word with 5 letters.\r\n");
            return PAM_PERM_DENIED;
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
        guesses.push_back(result);

        for (auto & guessed : guesses) {
            fprintf(stdout, "%s\r\n", guessed.c_str());
        }

        if (guess == answer) {
            return PAM_SUCCESS;
        }
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
