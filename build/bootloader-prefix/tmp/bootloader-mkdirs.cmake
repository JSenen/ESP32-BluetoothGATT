# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/Users/JSenen/esp/v5.2/esp-idf/components/bootloader/subproject"
  "/Users/JSenen/Documents/VS_Code_Projects/ESP_IDF/throughput_server/build/bootloader"
  "/Users/JSenen/Documents/VS_Code_Projects/ESP_IDF/throughput_server/build/bootloader-prefix"
  "/Users/JSenen/Documents/VS_Code_Projects/ESP_IDF/throughput_server/build/bootloader-prefix/tmp"
  "/Users/JSenen/Documents/VS_Code_Projects/ESP_IDF/throughput_server/build/bootloader-prefix/src/bootloader-stamp"
  "/Users/JSenen/Documents/VS_Code_Projects/ESP_IDF/throughput_server/build/bootloader-prefix/src"
  "/Users/JSenen/Documents/VS_Code_Projects/ESP_IDF/throughput_server/build/bootloader-prefix/src/bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/Users/JSenen/Documents/VS_Code_Projects/ESP_IDF/throughput_server/build/bootloader-prefix/src/bootloader-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/Users/JSenen/Documents/VS_Code_Projects/ESP_IDF/throughput_server/build/bootloader-prefix/src/bootloader-stamp${cfgdir}") # cfgdir has leading slash
endif()
