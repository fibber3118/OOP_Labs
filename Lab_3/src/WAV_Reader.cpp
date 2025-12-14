#include "WAV_Reader.h"
#include <cstring> // Для std::memcpy

WAV_Reader::WAV_Reader(const std::string file) {
    // Используйте std::ios::binary для корректной работы с бинарными файлами
    wav_file.open(file, std::ios::binary);
    if (!wav_file.is_open()) {
        throw std::invalid_argument("Не удалось открыть файл");
    }

    // 1. Считываем RIFF Header и 'fmt ' Header (вся header структура)
    wav_file.read(reinterpret_cast<char *>(&header), sizeof(header));

    // Проверка формата (оставлю ваши проверки)
    // Обратите внимание: header.bitsPerSample не проверяется, но для int16_t (sample)
    // она должна быть 16.
    if (header.audioFormat != 1 || header.numChannels != 1 || header.sampleRate != 44100) {
        throw std::invalid_argument("Формат файла не поддерживается");
    }

    // --- ИСПРАВЛЕНИЕ: Логика пропуска необязательных фрагментов ---

    char current_chunk_id[4];
    uint32_t current_chunk_size = 0;

    // Цикл поиска фрагмента 'data'
    while (true) {
        // 2. Считываем идентификатор следующего подфрагмента (4 байта)
        if (!wav_file.read(current_chunk_id, 4)) {
            throw std::invalid_argument("Файл WAV поврежден: фрагмент 'data' не найден или файл обрезан.");
        }

        // 3. Считываем размер этого подфрагмента (4 байта)
        if (!wav_file.read(reinterpret_cast<char *>(&current_chunk_size), 4)) {
            throw std::invalid_argument("Файл WAV поврежден: не удалось считать размер фрагмента.");
        }

        // 4. Проверяем, нашли ли мы 'data'
        if (std::memcmp(current_chunk_id, "data", 4) == 0) {
            // КОПИРУЕМ найденные данные в структуру data_chunk
            std::memcpy(data_chunk.data_id, current_chunk_id, 4);
            data_chunk.data_size = current_chunk_size;
            break; // Выходим из цикла, мы готовы читать аудиоданные
        }

        // 5. Если это не 'data' (например, "LIST"), то пропускаем его

        // Смещаем указатель чтения на размер считанного фрагмента.
        wav_file.seekg(current_chunk_size, std::ios_base::cur);

        // WAV-спецификация требует 1-байтового выравнивания для нечетных размеров фрагментов.
        if (current_chunk_size % 2 != 0) {
            wav_file.seekg(1, std::ios_base::cur);
        }
    }
}

bool WAV_Reader::get_sample() {
    // sample имеет тип int16_t, который занимает 2 байта
    if (wav_file.read(reinterpret_cast<char *>(&sample), sizeof(sample))) {
        samples_read++;
        return true;
    }
    return false;
}