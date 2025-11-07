#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>
#include <stdlib.h>
#include <Windows.h>
#include <vector>

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

bool contains_case_insensitive(const std::string& haystack, const std::string& needle) {
    auto it = std::search(
        haystack.begin(), haystack.end(),
        needle.begin(), needle.end(),
        [](char ch1, char ch2) {
            auto to_upper_ascii = [](char c) {
                return (c >= 'a' && c <= 'z') ? c - 32 : c;
                };
            return to_upper_ascii(ch1) == to_upper_ascii(ch2);
        }
    );
    return it != haystack.end();
}

int main()
{
    string path;
    string simVer;
    vector<string> skippedFilesDirectory = {};
    cout << "\033[94mFLAGSmaker//XMLmaker [Version 1.3]\n";
    cout << "\033[94mProvided under MIT License.\n\n";
    cout << "\033[97mIs this a MSFS2020 or MSFS2024 project? \n";
    cout << "\033[97m(1) - MSFS2020 \n";
    cout << "\033[97m(2) - MSFS2024 \n";
    getline(cin, simVer);
    if (simVer == "1")
    {
        cout << "\033[32mSelected MSFS2020... \n";
    }
    else if (simVer == "2")
    {
        cout << "\033[32mSelected MSFS2024... \n";
    }
    else
    {
        cout << "\033[91mInvalid sim selection!\n\n";
        system("pause");
        return 1;
    }
    cout << "\033[97mEnter texture directory: \n";
    getline(cin, path);
    std::filesystem::path filepath = path;
    bool filepathExists = std::filesystem::exists(filepath);

    if (filepathExists == false) {
        cout << "\033[91mInvalid directory!\n\n";
        system("pause");
        return 1;
    }
    else {
        if (simVer == "1")
        {
            int count = 0;
            int count2 = 0;
            for (const auto& entry : fs::directory_iterator(path)) {
                string temp = (entry.path()).generic_string();
                string temp3 = ReplaceAll(temp, std::string(".png"), std::string(".png.FLAGS"));
                bool fileExists = std::filesystem::exists(temp3);
                if (temp.find(".FLAGS") != std::string::npos) {
                    count2++;
                    string temp2 = ReplaceAll(temp, std::string(".png.FLAGS"), std::string(".png"));
                    skippedFilesDirectory.push_back(temp2);
                    //cout << "\033[33mThe texture: " << temp2 << " already has a FLAG file!" << "\n";
                }
                else if (contains_case_insensitive(temp, "COMP") && temp.find(".FLAGS") == std::string::npos && fileExists == false) {
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
                string answer;
                cout << "\033[93mSkipped " << count2 << " files. Would you like to display the directories of the skipped files?\nY/N.\n";
                cin >> answer;
                if (answer == "Y")
                {
                    for (int i = 0; i < skippedFilesDirectory.size(); i++)
                    {
                        cout << skippedFilesDirectory[i] << "\n";
                    }
                }
            }
            system("pause");
            return 0;
        }

        if (simVer == "2")
        {
            int count = 0;
            int count2 = 0;
            for (const auto& entry : fs::directory_iterator(path)) {
                string temp = (entry.path()).generic_string();
                string temp3 = ReplaceAll(temp, std::string(".png"), std::string(".png.xml"));
                bool fileExists = std::filesystem::exists(temp3);
                if (temp.find(".xml") != std::string::npos) {
                    count2++;
                    string temp2 = ReplaceAll(temp, std::string(".png.xml"), std::string(".png"));
                    skippedFilesDirectory.push_back(temp2);
                    //cout << "\033[33mThe texture: " << temp2 << " already has a FLAG file!" << "\n";
                }
                else if (contains_case_insensitive(temp, "COMP") == false && temp.find(".FLAGS") == std::string::npos && fileExists == false)
                {
                    string temp2 = ReplaceAll(temp, std::string(".png"), std::string(".png.xml"));
                    ofstream outfile(temp2);
                    outfile << "<BitmapConfiguration><BitmapSlot>MTL_BITMAP_DECAL0</BitmapSlot></BitmapConfiguration>" << endl;
                    outfile.close();
                    cout << "\033[32mXML file for COMP texture: " << temp2 << " has been created!" << "\n";
                    count++;
                }
                else if (contains_case_insensitive(temp, "COMP") && temp.find(".xml") == std::string::npos && fileExists == false) {
                    string temp2 = ReplaceAll(temp, std::string(".png"), std::string(".png.xml"));
                    ofstream outfile(temp2);
                    outfile << "<BitmapConfiguration><BitmapSlot>MTL_BITMAP_DECAL0</BitmapSlot><UserFlags Type=\"_DEFAULT\">QUALITYHIGH</UserFlags><ForceNoAlpha>true</ForceNoAlpha></BitmapConfiguration>" << endl;
                    outfile.close();
                    cout << "\033[32mXML file for COMP texture: " << temp2 << " has been created!" << "\n";
                    count++;
                }
            }
            if (count == 0 && count2 == 0) {
                cout << "\033[91mNo valid textures were found.\n\n";
            }
            if (count > 1) {
                cout << "\033[92mSuccesfully made " << count << " XML file(s)!\n";
            }
            if (count2 > 1) {
                string answer;
                cout << "\033[93mSkipped " << count2 << " files. Would you like to display the directories of the skipped files?\nY/N.\n";
                cin >> answer;
                if (answer == "Y")
                {
                    for (int i = 0; i < skippedFilesDirectory.size(); i++)
                    {
                        cout << skippedFilesDirectory[i] << "\n";
                    }
                }
            }
            system("pause");
            return 0;
        }
    }
}
