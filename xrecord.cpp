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
    std::string saveDir = FetchSaveDirectory();

    if (saveDir == "") {
        std::cout << "No set saveDirectory, using default.\nTo change this, edit 'preferences.json'\n\n";
        if (std::filesystem::is_directory("./output")) {}
        else {
            system("mkdir ./output/");
        }
        
        saveDir = "./output/";
    }   

    const char* command = "wf-recorder --audio --file GRAH.mp4";
    system("clear");

    return 0;
}