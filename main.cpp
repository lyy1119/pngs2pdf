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

std::vector<std::string> generate_image_file_vector(int pageNumbers)
{
    std::vector<std::string> imageFiles;
    for (int i = 1; i <= pageNumbers; i++)
    {
        imageFiles.push_back(std::to_string(i) + ".png");
    }
    return imageFiles;
}

int main()
{
    int pageNumber = get_page_numbers();
    std::cout << pageNumber << " pages found." << std::endl;
    std::vector<std::string> imageFiles;
    imageFiles = generate_image_file_vector(pageNumber);
    HPDF_Doc pdf = HPDF_New(error_handler, nullptr);
    if (!pdf) {
        std::cerr << "Failed to create PDF object" << std::endl;
        return 1;
    }
    try
    {
        for (const auto &imageFile : imageFiles)
        {
            std::cout << "process png file:" << imageFile << std::endl;
            HPDF_Page page = HPDF_AddPage(pdf);
            HPDF_Image image = HPDF_LoadPngImageFromFile(pdf, imageFile.c_str());
            std::cout << 1 << std::endl;
            if (!image) {
                HPDF_Free(pdf);
                throw std::runtime_error("Failed to load PNG image.");
            }
            std::cout << "load png file:" << imageFile << std::endl;
            HPDF_REAL imageWidth = HPDF_Image_GetWidth(image);
            HPDF_REAL imageHeight = HPDF_Image_GetHeight(image);
            HPDF_Page_SetWidth(page, imageWidth);
            HPDF_Page_SetHeight(page, imageHeight);
            HPDF_Page_DrawImage(page, image, 0, 0, imageWidth, imageHeight);
        }
        HPDF_SaveToFile(pdf, "output.pdf");
        HPDF_Free(pdf);
        std::cout << "PDF successfully created!" << std::endl;
    }
    catch(...)
    {
        HPDF_Free(pdf);
        std::cerr << "An error occurred while creating the PDF." << std::endl;
        return 1;
    }
    return 0;
}