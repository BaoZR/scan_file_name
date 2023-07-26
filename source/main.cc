#include <Windows.h>
#include <filesystem>
#include "csvfile.h"
#include "iconv.h"



namespace fs = std::filesystem;

std::string excel_name = "MyTable.csv";

std::string UTF8_to_GBK(const std::string& in )
{
    const int endBlankLength = 1;
    size_t inputLength = std::strlen(in.c_str())+ endBlankLength;
    size_t outputLength = inputLength;    
    size_t inByteLeft = inputLength;
    size_t outByteLeft = outputLength;
    std::string msg;

    auto inBuff = std::unique_ptr<char, decltype(free)*>{ 
        static_cast<char*>(malloc(sizeof(char) * inputLength)),free
    };
    auto outBuff = std::unique_ptr<char, decltype(free)*>{
        static_cast<char*>(malloc(sizeof(char) * outputLength)),free
    };

    const char* pInBuff = inBuff.get();
    char* pOutBuff = outBuff.get();
   
   std::memset(inBuff.get(), 0, inputLength);
   std::memset(outBuff.get(), 0, outputLength);
   std::memcpy(inBuff.get(), in.c_str(), inputLength);
 
   iconv_t iconvHandle = iconv_open("GBK", "UTF-8");
   size_t ret = iconv(iconvHandle, &pInBuff, &inByteLeft, &pOutBuff, &outByteLeft);
   iconv_close(iconvHandle);
   
   return std::string(outBuff.get());
}

std::string GBK_to_UTF8(const std::string& in )
{
    const int endBlankLength = 1;
    size_t inputLength = std::strlen(in.c_str())+ endBlankLength;
    size_t outputLength = inputLength *2;    
    size_t inByteLeft = inputLength;
    size_t outByteLeft = outputLength;
    std::string msg;

    auto inBuff = std::unique_ptr<char, decltype(free)*>{ 
        static_cast<char*>(malloc(sizeof(char) * inputLength)),free
    };
    auto outBuff = std::unique_ptr<char, decltype(free)*>{
        static_cast<char*>(malloc(sizeof(char) * outputLength)),free
    };

    const char* pInBuff = inBuff.get();
    char* pOutBuff = outBuff.get();
   
   std::memset(inBuff.get(), 0, inputLength);
   std::memset(outBuff.get(), 0, outputLength);
   std::memcpy(inBuff.get(), in.c_str(), inputLength);
 
   iconv_t iconvHandle = iconv_open("UTF-8","GBK");
   size_t ret = iconv(iconvHandle, &pInBuff, &inByteLeft, &pOutBuff, &outByteLeft);
   iconv_close(iconvHandle);
   
   return std::string(outBuff.get());
}


void SetColor(unsigned short forecolor =4 ,unsigned short backgroudcolor =0)
{
	HANDLE hCon =GetStdHandle(STD_OUTPUT_HANDLE); //获取缓冲区句柄
	SetConsoleTextAttribute(hCon,forecolor|backgroudcolor); //设置文本及背景色
}

int main(int argc,char* argv[])
{
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    std::cout << "这个程序用来获取当前目录下的文件名" << std::endl;
    std::cout << "输出的EXCEL文件名为,回车确认(默认 " << excel_name << "):";

    std::string temp_str;
    std::getline(std::cin, temp_str);
    if (temp_str != "")
    {
        excel_name = temp_str + ".csv";
    }

    std::string this_excel_path = fs::current_path().string() + "\\" + excel_name;
    std::string this_exe_path = fs::current_path().string() + "\\" + fs::path(argv[0]).filename().string();
    
    std::cout << "============" << std::endl;
 
    
    try
    {
        csvfile csv(excel_name); // throws exceptions!

        for (auto const &dir_entry : fs::recursive_directory_iterator{ fs::current_path().string() })
        {
            if (!dir_entry.is_directory())
            {
                std::string GBK_path = dir_entry.path().string();
                std::string UTF8_path = GBK_to_UTF8(GBK_path);
                if(UTF8_path == this_excel_path)
                {

                    std::cout << this_excel_path.c_str();
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
                    std::cout << " skip" ;
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
                    std::cout<< std::endl;
                    continue;
                }
                if(UTF8_path == this_exe_path)
                {
                    std::cout << this_exe_path.c_str();
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
                    std::cout << " skip" ;
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
                    std::cout<< std::endl;
                    continue;
                }
                std::cout << UTF8_path.c_str() << std::endl;
                csv << (GBK_path.c_str()) <<endrow;
            }
        }
    }
    catch (const std::exception &ex)
    {
        std::cout << "Exception was thrown: " << ex.what() << std::endl;
    }
    std::cout << "============" << std::endl;

    system("pause");
    return 0;
}