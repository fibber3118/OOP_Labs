#include "convert.h"

void print_help() {
    std::cout << "Usage: sound_processor [-h] [-c config.txt output.wav input1.wav [input2.wav ...]]" << std::endl;
    std::cout << "  -h                  Show this help message and exit." << std::endl;
    std::cout << "  -c                  Configuration mode." << std::endl;
    std::cout << "\nConfiguration Format:" << std::endl;
    std::cout << "  config.txt" << std::endl;
    std::cout << "  output.wav" << std::endl;
    std::cout << "  input1.wav" << std::endl;
}

void convert(
    const std::string &config_file,
    const std::string &output_file,
    const std::vector<std::string> &input_files) {
    if (input_files.empty()) {
        throw std::invalid_argument("Не задан входной WAV-файл.");
    }
    ConfigParser parser(config_file, input_files);
    std::string current_input_file = input_files[0];
    std::string temp_file = "";
    int command_index = 0;
    while (true) {
        std::vector<std::string> command = parser.get_command();
        if (command.empty()) {
            break;
        }
        std::string converter_name = command[0];
        std::string args_string;
        for (size_t i = 1; i < command.size(); ++i) {
            args_string += command[i];
            if (i < command.size() - 1) {
                args_string += " ";
            }
        }
        std::string current_output_file;
        if (parser.is_last_command()) {
            current_output_file = output_file;
        } else {
            command_index++;
            current_output_file = TEMP_FILE + std::to_string(command_index);
        }
        std::unique_ptr<Converter> converter = Factory_Converter::getInstance()->create_converter(converter_name);
        if (!converter) {
            throw std::runtime_error("Неизвестный конвертер: " + converter_name);
        }
        try {
            WAV_Reader in_stream(current_input_file);
            WAV_Writer out_stream(current_output_file);
            converter->convert(in_stream, out_stream, args_string);
            out_stream.close();
        } catch (const std::exception &e) {
            throw std::runtime_error("Ошибка при выполнении конвертера " + converter_name + ": " + e.what());
        }
        if (!temp_file.empty() && temp_file.rfind(TEMP_FILE, 0) == 0) {
            std::remove(temp_file.c_str());
        }
        temp_file = current_input_file;
        current_input_file = current_output_file;
    }
    if (current_input_file.rfind(TEMP_FILE, 0) == 0) {
        std::remove(current_input_file.c_str());
    }
    std::cout << "Конвертация успешно завершена. Результат сохранен в: " << output_file << std::endl;
}

int convert(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "Недостаточно аргументов" << std::endl;
        return 1;
    }
    if (std::string(argv[1]) == "-h") {
        print_help();
        return 0;
    }
    if (std::string(argv[1]) == "-c") {
        if (argc < 5) {
            std::cerr << "Для опции -c требуется: config.txt output.wav input1.wav [input2.wav ...]" <<
                    std::endl;
            return 1;
        }

        std::string config_file = argv[2];
        std::string output_file = argv[3];
        std::vector<std::string> input_files;
        for (int i = 4; i < argc; ++i) {
            input_files.push_back(argv[i]);
        }

        try {
            convert(config_file, output_file, input_files);
        } catch (const std::exception &e) {
            std::cerr << e.what() << std::endl;
            return 2;
        }
        return 0;
    }
    std::cerr << "Неизвестная опция '" << argv[1] << std::endl;
    return 1;
}
