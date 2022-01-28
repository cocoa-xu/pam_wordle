#include "pam_wordle.h"
#include <stdio.h>
#include <cstring>

PAM_EXTERN int pam_sm_authenticate(pam_handle_t *handle, int flags, int argc, const char **argv)
{
    int pam_code;
    const char *answer = "hello";
    const char *guess = nullptr;
    int num_guesses = 6;

    for (int i = 0; i < num_guesses; ++i) {
        /* Asking the user for a guess */
        pam_code = pam_get_user(handle, &guess, "guess: ");
        if (pam_code != PAM_SUCCESS) {
            fprintf(stderr, "Please make a guess.");
            return PAM_PERM_DENIED;
        }

        if (guess == nullptr || strlen(guess) != 5) {
            fprintf(stderr, "Please input a word with 5 letters.");
            return PAM_PERM_DENIED;
        }

        if (strcmp(guess, answer) == 0) {
            return PAM_SUCCESS;
        }
    }

    fprintf(stderr, "Maximum number of guess reached. It was %s\r\n", answer);
    return PAM_PERM_DENIED;
}

PAM_EXTERN int pam_sm_setcred(pam_handle_t *pamh, int flags, int argc, const char **argv) {
    return PAM_SUCCESS;
}

PAM_EXTERN int pam_sm_acct_mgmt(pam_handle_t *pamh, int flags, int argc, const char **argv)
{
    return PAM_SUCCESS;
}
