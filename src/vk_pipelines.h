#pragma once
#include <vk_types.h>

namespace vkutil {
    bool load_shader_module(const char *filePath, VkDevice device, VkShaderModule *outShaderModule);

    class PipelineBuilder {
    public:
        std::vector<VkPipelineShaderStageCreateInfo> _shaderStages;

        VkPipelineInputAssemblyStateCreateInfo _inputAssembly;
        VkPipelineRasterizationStateCreateInfo _rasterizer;
        VkPipelineColorBlendAttachmentState _colorBlendAttachment;
        VkPipelineMultisampleStateCreateInfo _multisampling;
        VkPipelineLayout _pipelineLayout;
        VkPipelineDepthStencilStateCreateInfo _depthStencil;
        VkPipelineRenderingCreateInfo _renderInfo;
        VkFormat _colorAttachmentformat;

        PipelineBuilder() { clear(); }

        void clear();

        VkPipeline build_pipeline(VkDevice device);

        void set_shaders(VkShaderModule vertexShader, VkShaderModule fragmentShader);

        void set_input_topology(VkPrimitiveTopology topology) {
            _inputAssembly.topology               = topology;
            _inputAssembly.primitiveRestartEnable = VK_FALSE;
        }

        void set_polygon_mode(VkPolygonMode mode) {
            _rasterizer.polygonMode = mode;
            _rasterizer.lineWidth   = 1.0f;
        }

        void set_cull_mode(VkCullModeFlagBits cullMode, VkFrontFace frontFace) {
            _rasterizer.cullMode  = cullMode;
            _rasterizer.frontFace = frontFace;
        }

        void set_multisampling_none();

        void disable_blending() {
            _colorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT |
                                                   VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
            _colorBlendAttachment.blendEnable = VK_FALSE;
        }

        void set_color_attachment_format(VkFormat format) {
            _colorAttachmentformat              = format;
            _renderInfo.colorAttachmentCount    = 1;
            _renderInfo.pColorAttachmentFormats = &_colorAttachmentformat;
        }

        void set_depth_format(VkFormat format) { _renderInfo.depthAttachmentFormat = format; }

        void disable_depthtest();
    };
};// namespace vkutil