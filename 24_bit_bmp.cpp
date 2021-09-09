
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>

#pragma pack(2)
#pragma(push)
struct BmpHeader {
  char bitmapSignatureBytes[2];
  uint32_t size_of_file = NULL;
  uint16_t reservedBytes;
  uint16_t reservedBytes2;
  uint32_t pixelDataOffset;
} bmpHeader;

struct BmpInfoHeader {
  uint32_t sizeOfThisHeader;
  int32_t width;
  int32_t height;
  uint16_t numberOfColorPlanes;
  uint16_t BitCount;
  uint32_t compressionMethod;
  uint32_t rawBitmapDataSize;    // generally ignored
  int32_t horizontalResolution;  // in pixel per meter
  int32_t verticalResolution;    // in pixel per meter
  uint32_t clr_used;
  uint32_t importantColors;

} bmpInfoHeader;

#pragma(pop)

constexpr uint16_t get16bit(char buffer[]) {
  return static_cast<uint16_t>(static_cast<uint8_t>(buffer[0])) |
         static_cast<uint16_t>(static_cast<uint8_t>(buffer[1]));
}

constexpr uint32_t get32bit(char buffer[]) {
  return static_cast<uint32_t>(static_cast<uint8_t>(buffer[0])) |
         static_cast<uint32_t>(static_cast<uint8_t>(buffer[1])) << 8 |
         static_cast<uint32_t>(static_cast<uint8_t>(buffer[2])) << 16 |
         static_cast<uint32_t>(static_cast<uint8_t>(buffer[3])) << 24;
}

int Pixel[3]{0, 0, 0};

int main(int argc, char **argv) {
  char buffer[4];

  std::ifstream file("", std::ios::binary);

  file.read(buffer, 2);
  bmpHeader.bitmapSignatureBytes[0] = buffer[0];
  bmpHeader.bitmapSignatureBytes[1] = buffer[1];
  std::cout << bmpHeader.bitmapSignatureBytes[0]
            << bmpHeader.bitmapSignatureBytes[1] << std::endl;

  file.read(buffer, 4);
  bmpHeader.size_of_file = get32bit(buffer);
  std::cout << "size of file: " << bmpHeader.size_of_file << std::endl;

  file.read(buffer, 2);  // ignored section
  bmpHeader.reservedBytes = get16bit(buffer);
  std::cout << "rezerved 1: " << bmpHeader.reservedBytes << std::endl;

  file.read(buffer, 2);  // ignored section
  bmpHeader.reservedBytes = get16bit(buffer);
  std::cout << "rezerved 2: " << bmpHeader.reservedBytes2 << std::endl;

  file.read(buffer, 4);
  bmpHeader.pixelDataOffset = get32bit(buffer);
  std::cout << "Pixel Offset data: " << bmpHeader.pixelDataOffset << std::endl;

  file.read(buffer, 4);  //--------------------------------------------INFO
  bmpInfoHeader.sizeOfThisHeader = get32bit(buffer);
  std::cout << "size of bmp_INFO_header: " << bmpInfoHeader.sizeOfThisHeader
            << std::endl;

  file.read(buffer, 4);
  bmpInfoHeader.width = get32bit(buffer);
  std::cout << "width: " << bmpInfoHeader.width << std::endl;

  file.read(buffer, 4);
  bmpInfoHeader.height = get32bit(buffer);
  std::cout << "height: " << bmpInfoHeader.height << std::endl;

  file.read(buffer, 2);
  bmpInfoHeader.numberOfColorPlanes = get16bit(buffer);
  std::cout << "colours planes: " << bmpInfoHeader.numberOfColorPlanes
            << std::endl;

  file.read(buffer, 2);
  bmpInfoHeader.BitCount = get16bit(buffer);
  std::cout << "bit count : " << bmpInfoHeader.compressionMethod << std::endl;

  file.read(buffer, 4);
  bmpInfoHeader.compressionMethod = get32bit(buffer);
  std::cout << "compression : " << bmpInfoHeader.compressionMethod << std::endl;

  file.read(buffer, 4);
  bmpInfoHeader.rawBitmapDataSize = get32bit(buffer);
  std::cout << "rawBitmapDataSize : " << bmpInfoHeader.rawBitmapDataSize
            << std::endl;

  file.read(buffer, 4);
  bmpInfoHeader.horizontalResolution = get32bit(buffer);
  std::cout << "horizontal res : " << bmpInfoHeader.horizontalResolution
            << std::endl;

  file.read(buffer, 4);
  bmpInfoHeader.verticalResolution = get32bit(buffer);
  std::cout << "vertical res : " << bmpInfoHeader.verticalResolution
            << std::endl;

  file.read(buffer, 4);
  bmpInfoHeader.clr_used = get32bit(buffer);
  std::cout << "clR_USED : " << bmpInfoHeader.clr_used << std::endl;

  file.read(buffer, 4);
  bmpInfoHeader.importantColors = get32bit(buffer);
  std::cout << "important colours : " << bmpInfoHeader.importantColors
            << std::endl;

  std::ofstream file_out("test.bmp");
  file_out.seekp(0);
  file_out.write((char *)&bmpHeader, 14);
  file_out.write((char *)&bmpInfoHeader, 40);

  for (int i = 54; i < bmpHeader.size_of_file; i += 3) {
    file.seekg(i);
    file.read(buffer, 3);
    Pixel[0] = static_cast<uint8_t>(static_cast<uint8_t>(buffer[0]));
    Pixel[1] = static_cast<uint8_t>(static_cast<uint8_t>(buffer[1]));
    Pixel[2] = static_cast<uint8_t>(static_cast<uint8_t>(buffer[2]));
    // std::cout <<Pixel[0]<<" "<<Pixel[1]<<" "<<Pixel[2]<<std::endl;
    unsigned int grey_scale = (Pixel[0] + Pixel[1] + Pixel[2]) / 3;
    Pixel[0] = grey_scale;
    Pixel[1] = grey_scale;
    Pixel[2] = grey_scale;
    // std::cout <<"new "<<Pixel[0]<<" "<<Pixel[1]<<" "<<Pixel[2]<<std::endl;
    file_out.seekp(i);
    file_out.write((char *)&grey_scale, 1);
    file_out.write((char *)&grey_scale, 1);
    file_out.write((char *)&grey_scale, 1);
  }
  std::cout << "Done!" << std::endl;
  return 0;
}
