#include <windows.h>
#include <string>

using namespace std;

class Impersonation {
private:
    HANDLE userToken;

public:
    Impersonation() : userToken(NULL) {
    }

    ~Impersonation();

    string Logon(string userName, string password, string domain);

    string Logoff();
};
