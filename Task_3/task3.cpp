#include <iostream>
#include <fstream>
#include <ctime>
#include <limits>
using namespace std;

struct UserLog {
    int userID;
    string actionString;
    string timestamp;
};

string encryptText(string text, int shift) {
    for (int i = 0; i < text.length(); i++) {
        text[i] = text[i] + shift;
    }
    return text;
}

string decryptText(string text, int shift) {
    for (int i = 0; i < text.length(); i++) {
        text[i] = text[i] - shift;
    }
    return text;
}

bool containsForbidden(string text) {
    for (int i = 0; i < text.length(); i++)
        text[i] = tolower(text[i]);

    return text.find("forbidden") != string::npos;
}


void showLogs(int shift) {
    ifstream file("logs.txt");
    if (!file) return;

    string stored[200];
    int total = 0, index = 0;

    while (getline(file, stored[index])) {
        index++;
        total++;
    }
    file.close();

    string recent[3] = {"", "", ""};
    int section = 0;

    for (int i = total - 1; i >= 0 && section < 3; i--) {
        if (stored[i] == "---") {
            section++;
        } else if (section > 0) {
            recent[section - 1] = stored[i] + "\n" + recent[section - 1];
        }
    }

    cout << "\n--- Last 3 Log Entries ---\n";
    for (int i = 0; i < section; i++) {
        cout << recent[i];

        size_t pos = recent[i].find("Action: ");
        if (pos != string::npos) {
            string encrypted = recent[i].substr(pos + 8);
            size_t end = encrypted.find('\n');
            if (end != string::npos)
                encrypted = encrypted.substr(0, end);

            cout << "Decrypted Action: " << decryptText(encrypted, shift) << "\n\n";
        }
    }
}
\
string getTime() {
    time_t t = time(nullptr);
    char buf[80];
    strftime(buf, 80, "%Y-%m-%d %H:%M:%S", localtime(&t));
    return string(buf);
}

void saveLog(const UserLog& log, int shift, const string& encryptedAction) {
    ofstream file("logs.txt", ios::app);
    if (!file) return;

    file << "UserID: " << log.userID << "\n";
    file << "Time: " << log.timestamp << "\n";
    file << "Action: " << encryptedAction << "\n";
    file << "---\n";

    file.close();
}

int main() {
    cout << "=== Secure Logger System ===\n";

    UserLog log;
    cout << "Action: ";
    getline(cin, log.actionString);

    cout << "User ID: ";
    cin >> log.userID;

    int lastDigit = log.userID % 10;
    int shift = lastDigit + 1;

    cout << "Computed Shift (lastDigit + 1): " << shift << "\n";

    if (containsForbidden(log.actionString)) {
        cout << "Error: Forbidden word detected.\n";
        return 1;
    }

    log.timestamp = getTime();
    string encrypted = encryptText(log.actionString, shift);

    saveLog(log, shift, encrypted);

    cout << "\nLog Saved!\n";
    cout << "Original Action:  " << log.actionString << "\n";
    cout << "Stored Encrypted: " << encrypted << "\n";
    cout << "Decrypted Check:  " << decryptText(encrypted, shift) << "\n";

    showLogs(shift);

    return 0;
}
