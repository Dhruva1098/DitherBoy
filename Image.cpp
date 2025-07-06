//
// Created by Dhruva Sharma on 18/2/25.
//
#include "headers/Image.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include <iostream>

Image::Image(int width, int height) : width_(width), height_(height), pixels_(width * height) {}
Image::~Image() {}

bool Image::load(const std::string& filename) {
  int channels;
  unsigned char* data = stbi_load(filename.c_str(), &width_, &height_, &channels, 4);  // 4 = RGBA
  if(!data) {
    std::cerr << "Failed to load image: " << filename << "-" << stbi_failure_reason() << std::endl;
    return false;
  }

  pixels_.resize(width_ * height_);
  for(int i = 0; i < height_; i++) {
    for(int j = 0; j < width_; j++) {
      int index = (i * width_ + j)*4;
      pixels_[i * width_ + j] = Color(
            static_cast<float>(data[index + 0]) / 255.0f,  // R
            static_cast<float>(data[index + 1]) / 255.0f,  // G
            static_cast<float>(data[index + 2]) / 255.0f,  // B
            static_cast<float>(data[index + 3]) / 255.0f);  // A
    }
  }
  stbi_image_free(data);
  return true;
}

bool Image::save(const std::string& filename, const std::string& format){
  unsigned char* data = new unsigned char[width_ * height_ * 4];
  for(int i = 0; i < height_; i++) {
    for(int j = 0; j < width_; j++) {
      Color color = getPixel(j,i).Clamped();
      int index = (i * width_ + j) * 4;
      data[index + 0] = static_cast<float>(color.r * 255.0f);
      data[index + 1] = static_cast<float>(color.g * 255.0f);
      data[index + 2] = static_cast<float>(color.b * 255.0f);
      data[index + 3] = static_cast<float>(color.a * 255.0f);
    }
  }
  bool success = false;
  if (format == "png" || format == "PNG") {
    success = stbi_write_png(filename.c_str(), width_, height_, 4, data, width_ * 4);
  } else if (format == "bmp" || format == "BMP") {
    success = stbi_write_bmp(filename.c_str(), width_, height_, 4, data);
  } else if (format == "jpg" || format == "JPG" || format == "jpeg" || format == "JPEG") {
    success = stbi_write_jpg(filename.c_str(), width_, height_, 4, data, 95);
  } else {
    std::cerr << "Unsupported image format: " << format << std::endl;
  }
  delete[] data;
  if (!success) {
    std::cerr << "Failed to save image: " << filename << std::endl;
  } return success;
}

Color Image::getPixel(int x, int y) const {
  if (x >= 0 && x < width_ && y >= 0 && y < height_) {
    return pixels_[y * width_ + x];
  } else {
    return Color(0, 0, 0);
  }
}

void Image::setPixel(int x, int y, const Color& color){
  if (x >= 0 && x < width_ && y >= 0 && y < height_) {
    pixels_[y * width_ + x] = color;
  }
}

int Image::getWidth() const { return width_; }
int Image::getHeight() const { return height_; }
