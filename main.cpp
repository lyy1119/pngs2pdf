#include <iostream>
#include <vector>
#include <filesystem>
#include <sstream>
#include <hpdf.h>

int get_page_numbers()
{
    int pageNumber = 0;
    std::filesystem::path fileName("0");
    do
    {
        pageNumber++;
        std::ostringstream oss;
        oss << pageNumber << ".png";
        std::string fileNameString = oss.str();
        fileName = fileNameString;
    } while (std::filesystem::exists(fileName));
    return pageNumber - 1;
}

void error_handler(HPDF_STATUS error_no, HPDF_STATUS detail_no, void *user_data) {
    std::cerr << "Error: " << error_no << ", detail: " << detail_no << std::endl;
    exit(1);
}

std::vector<std::string> generate_image_file_vector(int page_numbers)
{
    std::vector<std::string> image_files;
    for (int i = 1; i <= page_numbers; i++)
    {
        image_files.push_back(std::to_string(i) + ".png");
    }
    return image_files;
}

int main()
{
    int pageNumber = get_page_numbers();
    std::cout << pageNumber << " pages found." << std::endl;
    HPDF_Doc pdf = HPDF_New(error_handler, nullptr);

    if (!pdf) {
        std::cerr << "Failed to create PDF object" << std::endl;
        return 1;
    }

}