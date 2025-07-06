#include "headers/ascii_dithrer.h"
#include "headers/Image.h"
#include <iostream>

int main() {
    // Load test image
    Image inputImage(1, 1);
    if (!inputImage.load("/Users/dhruvasharma/downloads/test.jpeg")) {
        std::cerr << "Failed to load test.jpeg\n";
        return 1;
    }
    
    std::cout << "Loaded image: " << inputImage.getWidth() << "x" << inputImage.getHeight() << "\n";
    
    // Test 1: Basic monochrome with advanced features
    {
        AsciiDithrer ditherer(AsciiCharSet::FONT8X8, true);
        ditherer.setComputeShaderMode(true);
        ditherer.setColorTheme(ColorTheme::MONOCHROME);
        ditherer.setDepthMode(DepthMode::NONE);
        
        Color black(0, 0, 0);
        Color white(255, 255, 255);
        
        if (ditherer.saveAsAsciiImage(inputImage, "advanced_monochrome.png", black, white, 2)) {
            std::cout << "Generated advanced_monochrome.png\n";
        }
    }
    
    // Test 2: Cyberpunk theme with depth effects
    {
        AsciiDithrer ditherer(AsciiCharSet::FONT8X8, true);
        ditherer.setComputeShaderMode(true);
        ditherer.setColorTheme(ColorTheme::CYBERPUNK);
        ditherer.setDepthMode(DepthMode::EXPONENTIAL);
        ditherer.setDepthThreshold(0.7f);
        ditherer.setDepthFade(0.5f);
        ditherer.setBloomIntensity(0.2f);
        ditherer.setColorBurn(0.1f);
        
        Color neonBlue(0, 150, 255);
        Color darkBg(10, 10, 20);
        
        if (ditherer.saveAsAsciiImage(inputImage, "advanced_cyberpunk.png", neonBlue, darkBg, 2)) {
            std::cout << "Generated advanced_cyberpunk.png\n";
        }
    }
    
    // Test 3: CRT terminal theme
    {
        AsciiDithrer ditherer(AsciiCharSet::FONT8X8, true);
        ditherer.setComputeShaderMode(true);
        ditherer.setColorTheme(ColorTheme::CRT);
        ditherer.setDepthMode(DepthMode::LINEAR);
        ditherer.setDepthFade(0.3f);
        ditherer.setLowContrast(true);
        
        Color green(0, 255, 0);
        Color black(0, 0, 0);
        
        if (ditherer.saveAsAsciiImage(inputImage, "advanced_crt.png", green, black, 2)) {
            std::cout << "Generated advanced_crt.png\n";
        }
    }
    
    // Test 4: Command prompt theme with tone mapping
    {
        AsciiDithrer ditherer(AsciiCharSet::FONT8X8, true);
        ditherer.setComputeShaderMode(true);
        ditherer.setColorTheme(ColorTheme::COMMAND_PROMPT);
        ditherer.setDepthMode(DepthMode::GAUSSIAN);
        ditherer.setDepthFade(0.4f);
        ditherer.setToneMapping(0.8f);
        
        Color white(255, 255, 255);
        Color black(0, 0, 0);
        
        if (ditherer.saveAsAsciiImage(inputImage, "advanced_cmd.png", white, black, 2)) {
            std::cout << "Generated advanced_cmd.png\n";
        }
    }
    
    // Test 5: Retro game theme with bloom
    {
        AsciiDithrer ditherer(AsciiCharSet::FONT8X8, true);
        ditherer.setComputeShaderMode(true);
        ditherer.setColorTheme(ColorTheme::RETRO_GAME);
        ditherer.setDepthMode(DepthMode::NONE);
        ditherer.setBloomIntensity(0.3f);
        ditherer.setColorBurn(0.2f);
        
        Color warm(255, 200, 100);
        Color dark(20, 10, 5);
        
        if (ditherer.saveAsAsciiImage(inputImage, "advanced_retro.png", warm, dark, 2)) {
            std::cout << "Generated advanced_retro.png\n";
        }
    }
    
    // Test 6: High contrast edge detection
    {
        AsciiDithrer ditherer(AsciiCharSet::FONT8X8, true);
        ditherer.setComputeShaderMode(true);
        ditherer.setColorTheme(ColorTheme::MONOCHROME);
        ditherer.setEdgeThreshold(0.2f);
        ditherer.setContrast(1.5f);
        ditherer.setBrightness(0.1f);
        ditherer.setDogSigma(1.2f);
        ditherer.setDogThreshold(0.01f);
        
        Color black(0, 0, 0);
        Color white(255, 255, 255);
        
        if (ditherer.saveAsAsciiImage(inputImage, "advanced_edges.png", black, white, 2)) {
            std::cout << "Generated advanced_edges.png\n";
        }
    }
    
    // Test 7: Low contrast eye-friendly version
    {
        AsciiDithrer ditherer(AsciiCharSet::FONT8X8, true);
        ditherer.setComputeShaderMode(true);
        ditherer.setColorTheme(ColorTheme::MONOCHROME);
        ditherer.setLowContrast(true);
        ditherer.setContrast(0.8f);
        ditherer.setBrightness(0.2f);
        
        Color gray(128, 128, 128);
        Color lightGray(200, 200, 200);
        
        if (ditherer.saveAsAsciiImage(inputImage, "advanced_eyefriendly.png", gray, lightGray, 2)) {
            std::cout << "Generated advanced_eyefriendly.png\n";
        }
    }
    
    // Test 8: Small tile size for higher resolution
    {
        AsciiDithrer ditherer(AsciiCharSet::FONT8X8, true);
        ditherer.setComputeShaderMode(true);
        ditherer.setColorTheme(ColorTheme::CYBERPUNK);
        ditherer.setTileSize(4); // Smaller tiles for more detail
        ditherer.setDepthMode(DepthMode::EXPONENTIAL);
        ditherer.setBloomIntensity(0.15f);
        
        Color cyan(0, 255, 255);
        Color darkBlue(5, 5, 15);
        
        if (ditherer.saveAsAsciiImage(inputImage, "advanced_highres.png", cyan, darkBlue, 1)) {
            std::cout << "Generated advanced_highres.png\n";
        }
    }
    
    // Test 9: Advanced ASCII text output
    {
        AsciiDithrer ditherer(AsciiCharSet::FONT8X8, true);
        ditherer.setComputeShaderMode(true);
        ditherer.setColorTheme(ColorTheme::MONOCHROME);
        ditherer.setTileSize(8);
        if (ditherer.saveAsTextAdvanced(inputImage, "advanced_ascii.txt")) {
            std::cout << "Generated advanced_ascii.txt\n";
        }
    }
    
    // Test 10: Simplified ASCII text output (specific characters + Gaussian blur)
    {
        AsciiDithrer ditherer(AsciiCharSet::FONT8X8, true);
        if (ditherer.saveAsTextSimplified(inputImage, "simplified_ascii.txt")) {
            std::cout << "Generated simplified_ascii.txt\n";
        }
    }
    
    std::cout << "All advanced ASCII shader tests completed!\n";
    std::cout << "\nGenerated files:\n";
    std::cout << "- advanced_monochrome.png (Basic with compute shader)\n";
    std::cout << "- advanced_cyberpunk.png (Cyberpunk theme with depth and bloom)\n";
    std::cout << "- advanced_crt.png (CRT terminal with low contrast)\n";
    std::cout << "- advanced_cmd.png (Command prompt with tone mapping)\n";
    std::cout << "- advanced_retro.png (Retro game with bloom and color burn)\n";
    std::cout << "- advanced_edges.png (High contrast edge detection)\n";
    std::cout << "- advanced_eyefriendly.png (Low contrast eye-friendly)\n";
    std::cout << "- advanced_highres.png (High resolution with small tiles)\n";
    
    return 0;
} 