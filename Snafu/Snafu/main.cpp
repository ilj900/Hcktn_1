#include <fstream>
constexpr const char* svg = 
    "<svg width=\"3840\" height=\"2160\" viewBox=\"0 0 3840 2160\" fill=\"none\" xmlns=\"http://www.w3.org/2000/svg\">\n"
    "<rect x=\"200\" y=\"200\" width=\"600\" height=\"600\" stroke=\"black\"/>\n"
    "<circle cx=\"500\" cy=\"500\" r=\"200\" stroke=\"green\"/>\n"
    "</svg>";

int main()
{
    std::ofstream out( "pic.svg" );
    out << svg;
    return 0;
}