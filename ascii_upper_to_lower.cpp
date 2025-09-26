#include <iostream>

int main() 
{
    char input = 'H '; // Example uppercase letter
    int ascii_value = static_cast<int>(input);
    int lower_ascii = ascii_value + 32;
    char lower_char = static_cast<char>(lower_ascii);
    std::cout << "Original: " << input << std::endl;
    std::cout << "Converted: " << lower_char << std::endl;
    return 0;
}
