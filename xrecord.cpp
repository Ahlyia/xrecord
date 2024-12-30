#include <cstddef>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <filesystem>
#include <nlohhman//json.hpp>
#include <nlohmann/json_fwd.hpp>
#include <string>
namespace fs = std::filesystem;

using json = nlohmann::json;

std::string FetchSaveDirectory() {
    std::ifstream file("./preferences.json");

    json data;
    file >> data;

    file.close();

    return data["video-directory"];
}

int main() {
    system("clear");
    std::string saveDir = FetchSaveDirectory();

    if (saveDir == "") {
        std::cout << "No set saveDirectory, using default.\nTo change this, edit 'preferences.json'\n\n";
        if (fs::is_directory("./output")) {}
        else {
            system("mkdir ./output/");
        }
        
        saveDir = "./output/";
    }   

    int n_files = 1;

    for (const auto& entry : fs::directory_iterator(saveDir)) {
        if (fs::is_regular_file(entry)) {
            n_files += 1;
        }
    }

    std::string filename = std::to_string(n_files);
    while (filename.length() < 4) {
        filename = "0" + filename;
    }
    filename = filename + "-xrecord.mp4";
    filename = saveDir + filename;

    const std::string command = "wf-recorder --audio --file "+filename;

    std::cout << "wf-recorder --audio --file "+filename+"\n\n";

    FILE* pipe = popen(command.c_str(),"r");
    if (!pipe) {
        std::cerr << "pOpen failed..\n";
        return 1;
    } 

    std::string _;
    std::cin >> _;

    return 0;
}