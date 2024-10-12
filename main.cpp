#include <iostream>
// #include <fstream>
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

int main()
{
    int pageNumber = get_page_numbers();
    std::cout << pageNumber << " pages found." << std::endl;

}