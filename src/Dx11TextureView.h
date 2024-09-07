#pragma once
// Copied from godot-cpp/test/src and modified.
#include "godot_cpp/classes/global_constants.hpp"
#include "godot_cpp/templates/vector.hpp"
#include "godot_cpp/variant/array.hpp"
#include "godot_cpp/variant/variant.hpp"
#include "godot_cpp/variant/vector3.hpp"
#include <godot_cpp/classes/image.hpp>
#include <godot_cpp/classes/image_texture.hpp>
#include <godot_cpp/classes/rd_texture_format.hpp>
#include <godot_cpp/classes/rendering_device.hpp>
#include <godot_cpp/classes/rendering_server.hpp>
#include <godot_cpp/classes/sprite2d.hpp>
#include <godot_cpp/classes/sub_viewport.hpp>
#include <godot_cpp/classes/texture_rect.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/memory.hpp>
#include <godot_cpp/classes/texture2drd.hpp>
#include "godot_cpp/classes/global_constants.hpp"
#include "godot_cpp/classes/label.hpp"
#include "godot_cpp/core/class_db.hpp"
#include "godot_cpp/variant/utility_functions.hpp"

#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/engine.hpp>

#include "d3d11_1.h"
#include "thread"

#define VK_USE_PLATFORM_WIN32_KHR
#include "vulkan/vulkan.h"
#include <DX11App.h>


class Dx11TextureView : public godot::Sprite2D
{
    GDCLASS( Dx11TextureView, godot::Sprite2D )

public:
    // Constants.
    // 
    //

    Dx11TextureView();
    ~Dx11TextureView() override;

    void _draw() override;
    void _process(double delta) override;
    void _ready() override;
    void _exit_tree() override;

    BOOL Dx11TextureView::isSharedTextureSupported(
        VkPhysicalDevice physicalDevice, VkDevice device, VkFormat imageFormat,
        VkImageUsageFlags imageUsage, VkExternalMemoryPropertiesKHR *pExternalMemoryProperties,
        VkExternalMemoryHandleTypeFlagBitsKHR *pHandleType );

    bool Dx11TextureView::createVulkanSharedTexture( VkPhysicalDevice physicalDevice, VkDevice device,
                                             uint32_t imageWidth, uint32_t imageHeight,
                                             VkFormat format,
                                             VkExternalMemoryHandleTypeFlagBitsKHR handleType,
                                             VkExternalMemoryPropertiesKHR externalMemoryProperties,
                                             HANDLE *pSharedHandle, VkImage *pImage,
                                             VkDeviceMemory *pDeviceMemory );

protected:
    static void _bind_methods();

    void _notification( int inWhat );
    bool _set( const godot::StringName &inName, const godot::Variant &inValue );
    bool _get( const godot::StringName &inName, godot::Variant &outReturn ) const;
    void _get_property_list( godot::List<godot::PropertyInfo> *outList ) const;
    bool _property_can_revert( const godot::StringName &inName ) const;
    bool _property_get_revert( const godot::StringName &inName, godot::Variant &outProperty ) const;
    void _validate_property( godot::PropertyInfo &inProperty ) const;

    godot::String _to_string() const;

private:
    godot::Ref< godot::Texture2DRD > textureRd;

    godot::RenderingDevice *rd;

    VkImage sharedImage = NULL;
    VkDeviceMemory sharedMemory = NULL;

    DX11App app;

    int mLastRPCArg = 0;
};
