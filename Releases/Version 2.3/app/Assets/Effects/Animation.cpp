#include <iostream>
#include <thread>
#include <chrono>

// Progress Bar Animation
int main() {
    int totalProgress = 30;
    for (int progress = 0; progress <= totalProgress; progress++) {
        float percentage = static_cast<float>(progress) / totalProgress * 100;
        std::cout << "[";

        for (int i = 0; i < progress; i++) {
            std::cout << "=";
        }
        std::cout << ">" << std::string(totalProgress - progress, ' ') << "]";
        std::cout << " " << static_cast<int>(percentage) << "%\r";
        std::cout.flush();

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    std::cout << std::endl << "Progress complete!" << std::endl;
    return 0;
}