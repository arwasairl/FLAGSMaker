#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>
#include <stdlib.h>
#include <Windows.h>

using namespace std;
namespace fs = std::filesystem;

std::string ReplaceAll(std::string str, const std::string& from, const std::string& to) {
    size_t start_pos = 0;
    while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length();
    }
    return str;
}

int main()
{
    string path;
    cout << "\033[94mFLAGSmaker [Version 1.1]\n";
    cout << "\033[94m(c) Microcuck and Adobo Corporation. 2024 No rights reserved.\n\n";
    cout << "\033[97mEnter texture directory: \n";
    getline(cin, path);
    std::filesystem::path filepath = path;
    bool filepathExists = std::filesystem::exists(filepath);

    if (filepathExists == false) {
        cout << "\033[91mInvalid directory!\n\n";
        cout << "\033[97mPress any key to quit...";
        getchar();
        return 1;
    }
    else {
        int count = 0;
        int count2 = 0;
        for (const auto& entry : fs::directory_iterator(path)) {
            string temp = (entry.path()).generic_string();
            string temp3 = ReplaceAll(temp, std::string(".png"), std::string(".png.FLAGS"));
            bool fileExists = std::filesystem::exists(temp3);
            if (temp.find(".FLAGS") != std::string::npos) {
                count2++;
                string temp2 = ReplaceAll(temp, std::string(".png.FLAGS"), std::string(".png"));
                cout << "\033[33mThe texture: " << temp2 << " already has a FLAG file!" << "\n";
            }
            else if (temp.find("COMP") != std::string::npos && temp.find(".FLAGS") == std::string::npos && fileExists == false) {
                string temp2 = ReplaceAll(temp, std::string(".png"), std::string(".png.FLAGS"));
                ofstream outfile(temp2);
                outfile << "_DEFAULT=QUALITYHIGH" << endl;
                outfile.close();
                cout << "\033[32mFLAG file for texture: " << temp2 << " has been created!" << "\n";
                count++;
            }
        }
        if (count == 0 && count2 == 0) {
            cout << "\033[91mNo valid COMP textures were found.\n\n";
        }
        if (count > 1) {
            cout << "\033[92mSuccesfully made " << count << " FLAG file(s)!\n";
        }
        if (count2 > 1) {
            cout << "\033[93mSkipped " << count2 << " files.\n\n";
        }
        cout << "\033[97mPress any key to quit...";
        getchar();
        return 0;
    }
}
