#ifndef PAM_WORDLE_H
#define PAM_WORDLE_H

#define PAM_SM_ACCOUNT
#define PAM_SM_AUTH
#define PAM_SM_PASSWORD

#include <security/pam_appl.h>
#include <security/pam_modules.h>
#ifdef   OPENPAM
#include <security/openpam.h>
#else
#include <security/pam_misc.h>
#endif

PAM_EXTERN int pam_sm_authenticate(pam_handle_t *handle, int flags, int argc, const char **argv);
PAM_EXTERN int pam_sm_setcred(pam_handle_t *pamh, int flags, int argc, const char **argv);
PAM_EXTERN int pam_sm_acct_mgmt(pam_handle_t *pamh, int flags, int argc, const char **argv);

#endif // PAM_WORDLE_H
