#include "Impersonation.h"

Impersonation::~Impersonation() {
    Logoff();
}

string Impersonation::Logon(string userName, string password, string domain) {
    if (userToken != NULL) {
        string error = Logoff();
        if (!error.empty()) {
            return error;
        }
    }

    if (userName.empty()) {
        return "Username cannot be empty";
    }

    if (password.empty()) {
        return "Password cannot be empty";
    }

    BOOL loginSuccess = LogonUser(const_cast<char *>(userName.c_str()),
            const_cast<char *>(domain.c_str()),
            const_cast<char *>(password.c_str()),
            LOGON32_LOGON_INTERACTIVE,
            LOGON32_PROVIDER_DEFAULT,
            &userToken);

    if (!loginSuccess) {
        return "Login failed with error code: " + GetLastError();
    }

    if (!ImpersonateLoggedOnUser(userToken)) {
        return "Impersonation failed with error code: " + GetLastError();
    }

    return "";
}

string Impersonation::Logoff() {
    if (userToken == NULL) {
        return "";
    }

    RevertToSelf();

    if (!CloseHandle(userToken)) {
        return "Logoff failed: CloseHandle Failed";
    }

    userToken = NULL;

    return "";
}