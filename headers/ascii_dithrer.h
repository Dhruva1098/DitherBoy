#ifndef ASCII_DITHRER_H
#define ASCII_DITHRER_H

#include "dithrer.h"
#include <string>
#include <vector>
#include <fstream>

enum class AsciiCharSet {
    BASIC,      // .:-=+*#%@
    EXTENDED,   // .'`^",:;Il!i><~+_-?][}{1)(|\/tfjrxnuvczXYUJCLQ0OZmwqpdbkhao*#MW&8%B@$
    ARTISTIC,   // ░▒▓█ (block characters)
    SIMPLE,     // .# (simple binary)
    SHADER,     // Optimized for shader-like output
    RETRO,      // Retro terminal style
    ADVANCED,   // Advanced with edge-aware characters
    FONT8X8     // Use actual 8x8 font tiles
};

enum class EdgeDirection {
    NONE = -1,
    VERTICAL = 0,    // |
    HORIZONTAL = 1,  // -
    DIAGONAL_1 = 2,  // /
    DIAGONAL_2 = 3   // backslash
};

enum class ColorTheme {
    MONOCHROME,      // Black and white
    CYBERPUNK,       // Neon colors
    CRT,            // Green terminal
    COMMAND_PROMPT,  // White on black
    RETRO_GAME,     // 8-bit style colors
    CUSTOM          // User-defined colors
};

enum class DepthMode {
    NONE,           // No depth effects
    LINEAR,         // Linear depth fade
    EXPONENTIAL,    // Exponential depth fade
    GAUSSIAN        // Gaussian depth fade
};

struct TileInfo {
    float averageLuminance;
    EdgeDirection dominantEdge;
    float edgeStrength;
    int edgePixelCount;
    float depth;
    bool hasSignificantEdges;
};

class AsciiDithrer : public Dither {
public:
    AsciiDithrer(AsciiCharSet charSet = AsciiCharSet::FONT8X8, bool detectEdges = true);
    ~AsciiDithrer() override = default;
    
    void applyDither(const Image& inputImage, Image& outputImage, const Pallete& pallete) override;
    
    // Save as text file
    bool saveAsText(const Image& inputImage, const std::string& filename);
    
    // Save as advanced text file (uses advanced tile/edge/character logic)
    bool saveAsTextAdvanced(const Image& inputImage, const std::string& filename);
    
    // Save as simplified text file (specific characters + Gaussian blur)
    bool saveAsTextSimplified(const Image& inputImage, const std::string& filename);
    
    // Save as image (true tile-based ASCII art)
    bool saveAsAsciiImage(const Image& inputImage, const std::string& filename, const Color& fg, const Color& bg, int scale = 1);
    
    // Enhanced settings
    void setEdgeThreshold(float threshold) { edgeThreshold_ = threshold; }
    void setContrast(float contrast) { contrast_ = contrast; }
    void setBrightness(float brightness) { brightness_ = brightness; }
    void setGamma(float gamma) { gamma_ = gamma; }
    void setDogSigma(float sigma) { dogSigma_ = sigma; }
    void setDogSigmaScale(float scale) { dogSigmaScale_ = scale; }
    void setDogTau(float tau) { dogTau_ = tau; }
    void setDogThreshold(float threshold) { dogThreshold_ = threshold; }
    void setEdgePixelThreshold(int threshold) { edgePixelThreshold_ = threshold; }
    
    // New advanced settings
    void setColorTheme(ColorTheme theme) { colorTheme_ = theme; }
    void setDepthMode(DepthMode mode) { depthMode_ = mode; }
    void setDepthThreshold(float threshold) { depthThreshold_ = threshold; }
    void setDepthFade(float fade) { depthFade_ = fade; }
    void setBloomIntensity(float intensity) { bloomIntensity_ = intensity; }
    void setColorBurn(float burn) { colorBurn_ = burn; }
    void setToneMapping(float mapping) { toneMapping_ = mapping; }
    void setLowContrast(bool lowContrast) { lowContrast_ = lowContrast; }
    void setTileSize(int size) { tileSize_ = size; }
    void setComputeShaderMode(bool enabled) { computeShaderMode_ = enabled; }
    
private:
    AsciiCharSet charSet_;
    bool detectEdges_;
    std::string charMap_;
    float edgeThreshold_;
    float contrast_;
    float brightness_;
    float gamma_;
    float dogSigma_;
    float dogSigmaScale_;
    float dogTau_;
    float dogThreshold_;
    int edgePixelThreshold_;
    
    // New advanced parameters
    ColorTheme colorTheme_;
    DepthMode depthMode_;
    float depthThreshold_;
    float depthFade_;
    float bloomIntensity_;
    float colorBurn_;
    float toneMapping_;
    bool lowContrast_;
    int tileSize_;
    bool computeShaderMode_;
    
    // Advanced edge detection
    std::vector<float> luminanceBuffer_;
    std::vector<float> dogBuffer_;
    std::vector<float> edgeBuffer_;
    std::vector<EdgeDirection> edgeDirectionBuffer_;
    std::vector<TileInfo> tileBuffer_;
    
    // Font8x8 data
    static const unsigned char font8x8_basic[128][8];
    static const unsigned char font8x8_block[32][8];
    
    void initializeCharMap();
    float getBrightness(const Color& color);
    char brightnessToChar(float brightness, bool isEdge = false);
    char getDirectionalChar(float brightness, EdgeDirection direction);
    bool isEdgePixel(const Image& image, int x, int y);
    float calculateEdgeStrength(const Image& image, int x, int y);
    float applyImageProcessing(float value);
    char getShaderOptimizedChar(float brightness, float edgeStrength);
    
    // Advanced edge detection methods
    void calculateLuminanceBuffer(const Image& image);
    void applyDifferenceOfGaussians();
    void applySobelFilter();
    void detectEdgeDirections();
    EdgeDirection getEdgeDirection(float theta);
    float gaussian(float sigma, float pos);
    void horizontalBlur(std::vector<float>& input, std::vector<float>& output, int width, int height);
    void verticalBlur(std::vector<float>& input, std::vector<float>& output, int width, int height);
    char getAdvancedChar(int x, int y, float brightness, EdgeDirection direction);
    
    // Font8x8 methods
    char getFont8x8Char(float brightness, EdgeDirection direction);
    void renderFont8x8Tile(std::ofstream& file, char asciiChar);
    float getFont8x8Density(const char* fontData);
    char selectFont8x8Char(float brightness);
    
    // New advanced methods
    void processTiles(const Image& image);
    TileInfo analyzeTile(const Image& image, int tileX, int tileY);
    EdgeDirection getDominantEdgeDirection(const std::vector<EdgeDirection>& directions);
    char selectTileCharacter(const TileInfo& tile);
    Color applyColorTheme(const Color& original, float luminance, float depth);
    float calculateDepthEffect(float depth);
    void applyBloomEffect(std::vector<Color>& colors, int width, int height);
    void applyColorBurnEffect(std::vector<Color>& colors);
    void applyToneMapping(std::vector<Color>& colors);
    void applyLowContrastEffect(std::vector<Color>& colors);
    Color getThemeColor(float luminance, float depth);
};

#endif // ASCII_DITHRER_H 