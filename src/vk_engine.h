// vulkan_guide.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <vk_types.h>

class VulkanEngine {
public:
    bool _isInitialized{false};
    int _frameNumber{0};
    bool stop_rendering{false};
    VkExtent2D _windowExtent{1700, 900};

    struct SDL_Window *_window{nullptr};

    static VulkanEngine &Get();

    //initializes everything in the engine
    void init();

    //shuts down the engine
    void cleanup();

    //draw loop
    void draw();

    //run main loop
    void run();

    VkInstance _instance;                     // Vulkan API instance
    VkDebugUtilsMessengerEXT _debug_messenger;// Debug messenger
    VkPhysicalDevice _chosenGPU;              // GPU
    VkDevice _device;                         // Logical device
    VkSurfaceKHR _surface;                    // Window

    // Swapchain
    VkSwapchainKHR _swapchain;
    VkFormat _swapchainImageFormat;

    std::vector<VkImage> _swapchainImages;        // Handle to actual image object
    std::vector<VkImageView> _swapchainImageViews;// Wrapper to perform actions on the image
    VkExtent2D _swapchainExtent;

private:
    void init_vulkan();
    void init_swapchain();
    void init_commands();
    void init_sync_structures();

    void create_swapchain(uint32_t width, uint32_t height);
    void destroy_swapchain();
};
