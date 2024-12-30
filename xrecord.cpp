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

std::string FetchSaveDirectory() { // Command to fetch the users save directory. (whether its specified or not.)
    std::ifstream file("./preferences.json");

    json data;
    file >> data;

    file.close();

    return data["video-directory"];
}

int main() {
    system("clear");
    std::string saveDir = FetchSaveDirectory();

    if (saveDir == "") { // If they're using default, and it's not found then create it.
        std::cout << "No set saveDirectory, using default.\nTo change this, edit 'preferences.json'\n\n";
        if (fs::is_directory("./output")) {}
        else {
            system("mkdir ./output/");
        }
        
        saveDir = "./output/";
    }   

    int n_files = 1; // Start counting files in save folder for automatic naming

    for (const auto& entry : fs::directory_iterator(saveDir)) {
        if (fs::is_regular_file(entry)) {
            n_files += 1;
        }
    }

    std::string filename = std::to_string(n_files); // Make automatic name
    while (filename.length() < 4) {
        filename = "0" + filename;
    }
    filename = filename + "-xrecord.mp4";
    filename = saveDir + filename;

    const std::string command = "wf-recorder --audio --file "+filename; // Establish the command used to rec.

    std::cout << "wf-recorder --audio --file "+filename+"\n\n"; // Print the output location

    FILE* pipe = popen(command.c_str(),"r"); // Run the command and do some freaky fukshit
    if (!pipe) {
        std::cerr << "pOpen failed..\n";
        return 1;
    } 

    std::string _;
    std::cin >> _; // Wait for the users input so it doesnt instantly stop recording...

    return 0;
}