#include "pam_wordle.h"
#include <stdio.h>
#include <cstring>
#include <string>
#include <iostream>

PAM_EXTERN int pam_sm_authenticate(pam_handle_t *handle, int flags, int argc, const char **argv)
{
    int pam_code;
    std::string answer = "hello";
    std::string guess;
    int num_guesses = 6;

    for (int i = 0; i < num_guesses; ++i) {
        /* Asking the user for a guess */
        fprintf(stdout, "Your guess[%d/%d]: ", i + 1, num_guesses);
        std::cin >> guess;

        if (guess.length() != 5) {
            fprintf(stderr, "Please input a word with 5 letters.\r\n");
            return PAM_PERM_DENIED;
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
