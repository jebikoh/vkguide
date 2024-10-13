// vulkan_guide.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <vk_descriptors.h>
#include <vk_types.h>

struct DeletionQueue {
    std::deque<std::function<void()>> deletors;

    void push_function(std::function<void()> &&function) {
        deletors.push_back(function);
    }

    void flush() {
        for (auto it = deletors.rbegin(); it != deletors.rend(); it++) {
            (*it)();
        }

        deletors.clear();
    }
};

struct FrameData {
    VkCommandPool _commandPool;
    VkCommandBuffer _mainCommandBuffer;
    VkSemaphore _swapchainSemaphore, _renderSemaphore;// GPU - GPU Sync
    VkFence _renderFence;                             // CPU - GPU Sync
    DeletionQueue _delQueue;
};

constexpr unsigned int FRAME_OVERLAP = 2;// 2 -> Double Buffering

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

    void immediate_submit(std::function<void(VkCommandBuffer cmd)> &&function);

    FrameData &get_current_frame() { return _frames[_frameNumber % FRAME_OVERLAP]; };

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

    // Frames
    FrameData _frames[FRAME_OVERLAP];
    VkQueue _graphicsQueue;
    uint32_t _graphicsQueueFamily;
    DeletionQueue _mainDelQueue;

    AllocatedImage _drawImage;
    VkExtent2D _drawExtent;

    VmaAllocator _allocator;

    // Descriptors
    DescriptorAllocator globalDescriptorAllocator;
    VkDescriptorSet _drawImageDescriptors;
    VkDescriptorSetLayout _drawImageDescriptorLayout;

    // Pipelines
    VkPipeline _gradientPipeline;
    VkPipelineLayout _gradientPipelineLayout;

    // Immediate Submit
    VkFence _immFence;
    VkCommandBuffer _immCommandBuffer;
    VkCommandPool _immCommandPool;

private:
    void init_vulkan();
    void init_swapchain();
    void init_commands();
    void init_sync_structures();
    void init_descriptors();
    void init_pipelines();
    void init_background_pipelines();
    void init_imgui();

    void create_swapchain(uint32_t width, uint32_t height);
    void destroy_swapchain();
    void draw_background(VkCommandBuffer cmd);
};
