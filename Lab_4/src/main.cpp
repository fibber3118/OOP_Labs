#include "Tuple_print.h"
#include "CSVParser.h"
#include <fstream>

int main() {
    std::ifstream file("data.csv");
    CSVParser<int, std::string, double> parser(file, 0, ',', '"');
    for (auto row: parser) {
      std::cout<<row<<std::endl;
    }
    return 0;
}
