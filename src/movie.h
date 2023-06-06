#include <string>
#include <fstream>
#include <optional>

struct MovieButtons {
    bool u=false,d=false,l=false,r=false,a=false,b=false,select=false,start=false;
};

class Movie {
    std::ifstream buttons_file;
    std::ifstream ramseq_file;
    std::string line;
    int delay_counter = 0;
    size_t counter = 0;
    MovieButtons last;
public:
    Movie(std::string buttons_filename)
        : buttons_file(buttons_filename)
    {
    }
    Movie(std::string buttons_filename, std::string ramseq_filename)
        : buttons_file(buttons_filename), ramseq_file(std::ifstream(ramseq_filename, std::ios::binary))
    {
    }

    // a crude "iterator" over the buttons
    std::optional<MovieButtons> next() {
        if (delay_counter > 0) {
            delay_counter -= 1;
            return last;
        }
        while (std::getline(buttons_file, line)) {
            if (line.length() < 8) {
                continue;
            }
            const std::string& s = line;
            last = MovieButtons{
                .u = s.find("U") != std::string::npos,
                .d = s.find("D") != std::string::npos,
                .l = s.find("L") != std::string::npos,
                .r = s.find("R") != std::string::npos,
                .a = s.find("A") != std::string::npos,
                .b = s.find("B") != std::string::npos,
                .select = s.find("S") != std::string::npos,
                .start = s.find("T") != std::string::npos,
            };
            counter += 1;
            return last;
        }
        return {};
    }

    bool get_ram(unsigned char *buf, size_t offset_frames) {
        if (ramseq_file.fail()) {
            return false;
        }
        ramseq_file.seekg((counter-1+offset_frames)* 0x800);
        ramseq_file.read((char*)buf, 0x800);
        return true;
    }

    void delay(int amount) {
        delay_counter += amount;
    }
};
