#if defined(_ANDROID_)
#define VK_USE_PLATFORM_ANDROID_KHR
#elif defined(_linux_)
#define VK_USE_PLATFORM_XLIB_KHR
#elif defined(_WIN32)
#define VK_USE_PLATFORM_WIN32_KHR
#endif

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_DERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

//Tell SDL not to mess with main()
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_syswm.h>
#include <SDL2/SDL_vulkan.h>

#include <vulkan/vulkan.hpp>

#include <iostream>
#include <vector>
#include <stdexcept>
#include <cstdlib>
#include <map>
#include <optional>
#include <cstring>




const int WIDTH = 800;
const int HEIGHT = 600;

const std::vector<const char*> validationLayers = {
    "VK_LAYER_KHRONOS_validation"
};

#ifdef NDEBUG
const bool enableValidationLayers = false;
#else
const bool enableValidationLayers = true;
#endif
VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger) {
    auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
    if (func != nullptr) {
        return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
    }
    else {
        return VK_ERROR_EXTENSION_NOT_PRESENT;
    }
}

void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator) {
    auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
    if (func != nullptr) {
        func(instance, debugMessenger, pAllocator);
    }
}

struct QueueFamilyIndices {
    std::optional<uint32_t> graphicsFamily;

    bool isComplete() {
        return graphicsFamily.has_value();
    }
};
class HelloTriangleApplication
{
public:
    void run()
    {
        initWindow();
        initVulkan();
        mainLoop();
        cleanup();
    }

private:
    GLFWwindow* window;

    VkInstance instance;
    //Create a Vulkan surface for rendering.
    VkSurfaceKHR surface;
    //扩展计数
    uint32_t glfwExtensionCount = 0;
    //保存扩展
    const char** glfwExtensions;
    
    //图层
    std::vector<const char*>layers;
#if defined(_DEBUG_)
    layers.push_back("VK_LAYERS_KHRONOS_validation");
#endif

    //物理设备，计数
    VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
    uint32_t deviceCount = 0;
    
    VkDebugUtilsMessengerEXT debugMessenger;
    glm::mat4 matrix;
    glm::vec4 vec;
    glm::vec4 text = matrix * vec;

    void initWindow()
    {
        glfwInit();

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);


    }

    void initVulkan()
    {
        createInstance();
        setupDebugMessenger();
        pickPhyicalDevice();
    } 
    
    void mainLoop()
    {
        while (!glfwWindowShouldClose(window)) {
            glfwPollEvents();
        }
    }

    void cleanup()
    {
        if (enableValidationLayers)
        {
            DestroyDebugUtilsMessengerEXT(instance, debugMessenger, nullptr);
        }
        vkDestroySurfaceKHR(instance, surface, nullptr);

        vkDestroyInstance(instance, nullptr);//必须首先释放vkDestorySurfaceKHR()，不然报错：访问冲突，即重复释放。

        glfwDestroyWindow(window);

        glfwTerminate();
    }

    void setupDebugMessenger() 
    {
        if (!enableValidationLayers) return;

        VkDebugUtilsMessengerCreateInfoEXT createInfo;
        populateDebugMessengerCreateInfo(createInfo);

        if (CreateDebugUtilsMessengerEXT(instance, &createInfo, nullptr, &debugMessenger) != VK_SUCCESS) {
            throw std::runtime_error("failed to set up debug messenger!");
        }
    }
    //加载检测图形卡
    void pickPhyicalDevice()
    {


        //获取图形卡列表
        deviceCount = 0;
        vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);
        std::cout << deviceCount << std::endl;

        if (deviceCount == 0)
        {
            throw std::runtime_error("Failde to find GPUs with Vulkan support.");
        }
        std::vector<VkPhysicalDevice>devices(deviceCount);
        vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());

        //检查所有物理设备是否符合功能需求
        for (const auto& device : devices)
        {
            if (isDeviceSuitable(device))
            {
                physicalDevice = device;
                break;
            }
        }
        if (physicalDevice == VK_NULL_HANDLE)
        {
            throw std::runtime_error("Failed to find a suitable GPU.");
        }
        // Use an ordered map to automatically sort candidates by increasing score
        std::multimap<int, VkPhysicalDevice> candidates;

        for (const auto& device : devices)
        {
            int score = rateDeviceSuitability(device);
            candidates.insert(std::make_pair(score, device));
        }

        // Check if the best candidate is suitable at all
        if (candidates.rbegin()->first > 0) {
            physicalDevice = candidates.rbegin()->second;
        }
        else
        {
            throw std::runtime_error("failed to find a suitable GPU!");
        }
    }
             
    
   //检查物理设备是否符合功能需求
    bool isDeviceSuitable(VkPhysicalDevice device)
    {
        //属性、名称等
        VkPhysicalDeviceProperties deviceProperties;
        //查询纹理压缩，64位浮点数和多视图渲染等功能
        VkPhysicalDeviceFeatures deviceFeatures;
        //遍历获取
        vkGetPhysicalDeviceProperties(device, &deviceProperties);
        vkGetPhysicalDeviceFeatures(device, &deviceFeatures);
        //仅做示例，还可得到更多属性。
        std::cout << deviceProperties.deviceName << std::endl;
        std::cout << deviceFeatures.alphaToOne << std::endl; 
        return deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU &&
            deviceFeatures.geometryShader;
    }

    int rateDeviceSuitability(VkPhysicalDevice device) 
    {
        //属性、名称等
        VkPhysicalDeviceProperties deviceProperties;
        //查询纹理压缩，64位浮点数和多视图渲染等功能
        VkPhysicalDeviceFeatures deviceFeatures;
        //遍历获取
        vkGetPhysicalDeviceProperties(device, &deviceProperties);
        vkGetPhysicalDeviceFeatures(device, &deviceFeatures);
            int score = 0;

        // Discrete GPUs have a significant performance advantage
        if (deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU) {
            score += 1000;
        }

        // Maximum possible size of textures affects graphics quality
        score += deviceProperties.limits.maxImageDimension2D;

        // Application can't function without geometry shaders
        if (!deviceFeatures.geometryShader) {
            return 0;
        }

        return score;
    }
   
    QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device)
    {
        QueueFamilyIndices indices;
        
        uint32_t queueFamilyCount = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount,nullptr);
        std::vector <VkQueueFamilyProperties>queueFamilies(queueFamilyCount);
        vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());
        int i = 0;
        for (const auto& queueFamily : queueFamilies) {
            if (queueFamily.queueCount > 0 && queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
                indices.graphicsFamily = i;
            }

            if (indices.isComplete()) {
                break;
            }

            i++;
        }

        return indices;
    }
  
    std::vector<const char*> getRequiredExtensions()
    {
        uint32_t glfwExtensionCount = 0;
        const char** glfwExtensions;
        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

        std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

        if (enableValidationLayers) {
            extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
        }

        return extensions;
    }
      
    void createInstance() 
    {
        if (enableValidationLayers && !checkValidationLayerSupport())
        {
            throw std::runtime_error("Validation Layers requested,but not validatable!");
        }
        //Vulkan加载的扩展信息输出
        //1.扩展数量
        vkEnumerateInstanceExtensionProperties(nullptr, &glfwExtensionCount, nullptr);
        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
        std::cout << glfwExtensionCount << " Extensions supported." << std::endl;
        //2.扩展具体信息
        //另一种方式，具体查看有哪些扩展
        //分配一个集合去持有扩展信息
        std::vector<VkExtensionProperties>extensions(glfwExtensionCount);
        //可遍历扩展信息
        vkEnumerateInstanceExtensionProperties(nullptr, &glfwExtensionCount, extensions.data());
        std::cout << "available extensions:" << std::endl;
        for (const auto& extension : extensions)
        {
            std::cout << "\t" << extension.extensionName << std::endl;
        }

               
        // vk::ApplicationInfo allows the programmer to specifiy some basic information about the
        // program, which can be useful for layers and tools to provide more debug information.
        vk::ApplicationInfo appInfo = vk::ApplicationInfo()
            .setPApplicationName("Vulkan C++ Windowed Program Template")
            .setApplicationVersion(1)
            .setPEngineName("No Engine")
            .setEngineVersion(1)
            .setApiVersion(VK_API_VERSION_1_0);
        //another type
        //  VkApplicationInfo appInfo = {};
        //  appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO; appInfo.pNext = nullptr;
        //  appInfo.pApplicationName = "Hello Triangle";
        //  appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        //  appInfo.pEngineName = "No Engine";
        //  appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        //  appInfo.apiVersion = VK_API_VERSION_1_0;
      
        // vk::InstanceCreateInfo is where the programmer specifies the layers and/or extensions that
        // are needed.
        if (enableValidationLayers)
        {

        }
        vk::InstanceCreateInfo instInfo = vk::InstanceCreateInfo()
            .setFlags(vk::InstanceCreateFlags())
            .setPApplicationInfo(&appInfo)
            .setEnabledExtensionCount(static_cast<uint32_t>(glfwExtensionCount))
            .setPpEnabledExtensionNames(glfwExtensions)
            .setEnabledLayerCount(static_cast<uint32_t>(layers.size()))
            .setPpEnabledLayerNames(layers.data());
         //instInfo.sType(VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO);
       
        VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo;
        //if (enableValidationLayers) {
        //   createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
        //   createInfo.ppEnabledLayerNames = validationLayers.data();

        //    populateDebugMessengerCreateInfo(debugCreateInfo);
        //    createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*)&debugCreateInfo;
       // }
        //else {
         //   createInfo.enabledLayerCount = 0;

          //  createInfo.pNext = nullptr;
        //}


        //Create the Vulkan instance.
        try {
            instance = vk::createInstance(instInfo);
            //VkResult result = vkCreateInstance(&instInfo, nullptr, &instance);
        }
        catch (const std::exception& e) {
            std::cout << "Could not create a Vulkan instance:" << e.what() << std::endl;
            //exit ;
        }


        VkWin32SurfaceCreateInfoKHR surfaceCreateInfo = {};
        surfaceCreateInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
        surfaceCreateInfo.hwnd = glfwGetWin32Window(window);//此函数声明在glfw3native.h里面
        surfaceCreateInfo.hinstance = GetModuleHandle(nullptr);

        if (vkCreateWin32SurfaceKHR(instance, &surfaceCreateInfo, nullptr, &surface) != VK_SUCCESS)
            std::runtime_error("Failed to create window surface!");

        // if (vkCreateInstance(&instInfo, nullptr, &instance) != VK_SUCCESS) {
        //     throw std::runtime_error("failed to create instance!");
        // }
    }
   
    void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo)
    {
        createInfo = {};
        createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
        createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
        createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
        createInfo.pfnUserCallback = debugCallback;
    }
   
    bool checkValidationLayerSupport() {
        uint32_t layerCount;
        vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

        std::vector<VkLayerProperties> availableLayers(layerCount);
        vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

        for (const char* layerName : validationLayers) {
            bool layerFound = false;

            for (const auto& layerProperties : availableLayers) {
                if (strcmp(layerName, layerProperties.layerName) == 0) {
                    layerFound = true;
                    break;
                }
            }

            if (!layerFound) {
                return false;
            }
        }

        return true;
    }
   
    static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData)
    {
        std::cerr << "validation layer: " << pCallbackData->pMessage << std::endl;

        return VK_FALSE;
    }
};

int main()
{
    HelloTriangleApplication app;

    try {
        app.run();
    }catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

