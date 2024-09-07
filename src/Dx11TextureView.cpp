// Copied from godot-cpp/test/src and modified.

#include "Dx11TextureView.h"
#include <chrono>



// Used to mark unused parameters to indicate intent and suppress warnings.
#define UNUSED( expr ) (void)( expr )


//// Dx11TextureView

Dx11TextureView::Dx11TextureView()
{
    godot::UtilityFunctions::print( "Constructor." );
}

Dx11TextureView::~Dx11TextureView()
{
    godot::UtilityFunctions::print( "Destructor." );
}

// Methods.

//

void Dx11TextureView::_bind_methods()
{
    // Methods.

    // Constants.
}

void Dx11TextureView::_notification( int inWhat )
{
    godot::UtilityFunctions::print( "Notification: ", godot::String::num( inWhat ) );
}

bool Dx11TextureView::_set( const godot::StringName &inName, const godot::Variant &inValue )
{
    godot::String name = inName;

    return false;
}

bool Dx11TextureView::_get( const godot::StringName &inName, godot::Variant &outReturn ) const
{
    return false;
}

void Dx11TextureView::_get_property_list( godot::List<godot::PropertyInfo> *outList ) const
{
}

bool Dx11TextureView::_property_can_revert( const godot::StringName &inName ) const
{
    return false;
};

bool Dx11TextureView::_property_get_revert( const godot::StringName &inName,
                                    godot::Variant &outProperty ) const
{
    return false;
};

void Dx11TextureView::_validate_property( godot::PropertyInfo &inProperty ) const
{
}



int ScaleformAppMain()
{
    printf( "main" );
    return 0;
}


BOOL Dx11TextureView::isSharedTextureSupported( VkPhysicalDevice physicalDevice, VkDevice device,
                               VkFormat imageFormat, VkImageUsageFlags imageUsage,
                               VkExternalMemoryPropertiesKHR *pExternalMemoryProperties,
                               VkExternalMemoryHandleTypeFlagBitsKHR *pHandleType )
{
    VkInstance vkInstance = (VkInstance)rd->get_driver_resource(
        godot::RenderingDevice::DRIVER_RESOURCE_VULKAN_INSTANCE, godot::RID(), 0 );

    auto __vkGetPhysicalDeviceImageFormatProperties2KHR =
        PFN_vkGetPhysicalDeviceImageFormatProperties2KHR(
            vkGetInstanceProcAddr( vkInstance, "vkGetPhysicalDeviceImageFormatProperties2KHR" ) );

    VkPhysicalDeviceImageFormatInfo2KHR imageFormatInfo;
    VkPhysicalDeviceExternalImageFormatInfoKHR externalImageFormat;

    externalImageFormat.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTERNAL_IMAGE_FORMAT_INFO_KHR;
    externalImageFormat.pNext = NULL;
    externalImageFormat.handleType = VK_EXTERNAL_MEMORY_HANDLE_TYPE_D3D11_TEXTURE_BIT_KHR;

    imageFormatInfo.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGE_FORMAT_INFO_2_KHR;
    imageFormatInfo.pNext = &externalImageFormat;
    imageFormatInfo.format = imageFormat;
    imageFormatInfo.type = VK_IMAGE_TYPE_2D;
    imageFormatInfo.tiling = VK_IMAGE_TILING_OPTIMAL;
    imageFormatInfo.flags = 0;
    imageFormatInfo.usage = imageUsage;

    VkExternalImageFormatPropertiesKHR externalImageFormatProperties;
    memset( &externalImageFormatProperties, 0, sizeof( VkExternalImageFormatPropertiesKHR ) );
    externalImageFormatProperties.sType = VK_STRUCTURE_TYPE_EXTERNAL_IMAGE_FORMAT_PROPERTIES_KHR;
    externalImageFormatProperties.pNext = NULL;

    VkImageFormatProperties2KHR imageFormatProperties;
    memset( &imageFormatProperties, 0, sizeof( VkImageFormatProperties2KHR ) );
    imageFormatProperties.sType = VK_STRUCTURE_TYPE_IMAGE_FORMAT_PROPERTIES_2_KHR;
    imageFormatProperties.pNext = &externalImageFormatProperties;

    VkResult result = __vkGetPhysicalDeviceImageFormatProperties2KHR(
        physicalDevice, &imageFormatInfo, &imageFormatProperties );

    if ( VK_SUCCESS != result )
    {
        externalImageFormat.handleType = VK_EXTERNAL_MEMORY_HANDLE_TYPE_D3D11_TEXTURE_KMT_BIT_KHR;
        *pHandleType = VK_EXTERNAL_MEMORY_HANDLE_TYPE_D3D11_TEXTURE_KMT_BIT_KHR;

        result = __vkGetPhysicalDeviceImageFormatProperties2KHR( physicalDevice, &imageFormatInfo,
                                                                   &imageFormatProperties );
    }
    else
    {
        *pHandleType = VK_EXTERNAL_MEMORY_HANDLE_TYPE_D3D11_TEXTURE_BIT_KHR;
    }

    *pExternalMemoryProperties = externalImageFormatProperties.externalMemoryProperties;

    return ( ( VK_SUCCESS == result ) && ( pExternalMemoryProperties->externalMemoryFeatures &
                                           VK_EXTERNAL_MEMORY_FEATURE_IMPORTABLE_BIT_KHR ) );
}





void Dx11TextureView::_process( double delta )
{
    this->queue_redraw();
}


void Dx11TextureView::_draw()
{
    godot::UtilityFunctions::print( "process call" );

    /* ask dx11 application to change textute */
    app.draw( godot::Engine::get_singleton()->get_frames_drawn() );
}





bool Dx11TextureView::createVulkanSharedTexture(VkPhysicalDevice physicalDevice, VkDevice vkDevice, uint32_t imageWidth, uint32_t imageHeight, VkFormat format, VkExternalMemoryHandleTypeFlagBitsKHR handleType, VkExternalMemoryPropertiesKHR externalMemoryProperties, HANDLE* pSharedHandle, VkImage* pImage, VkDeviceMemory* pDeviceMemory)
{
    VkInstance vkInstance = (VkInstance)rd->get_driver_resource(
        godot::RenderingDevice::DRIVER_RESOURCE_VULKAN_INSTANCE, godot::RID(), 0 );


    auto __vkGetImageMemoryRequirements2KHR = PFN_vkGetImageMemoryRequirements2KHR(
        vkGetInstanceProcAddr( vkInstance, "vkGetImageMemoryRequirements2KHR" ) );

    auto __vkBindImageMemory2KHR =
        PFN_vkBindImageMemory2KHR( vkGetInstanceProcAddr( vkInstance, "vkBindImageMemory2KHR" ) );


	VkExternalMemoryImageCreateInfoKHR externalMemoryImageInfo;
	externalMemoryImageInfo.sType       = VK_STRUCTURE_TYPE_EXTERNAL_MEMORY_IMAGE_CREATE_INFO_KHR;
	externalMemoryImageInfo.pNext       = nullptr; 
	externalMemoryImageInfo.handleTypes = handleType;

	VkImageCreateInfo imageCreateInfo;
	memset(&imageCreateInfo, 0, sizeof(VkImageCreateInfo));

	imageCreateInfo.sType         = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
	imageCreateInfo.pNext         = &externalMemoryImageInfo;
	imageCreateInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;

	VkFormat targetFormat = format;

	imageCreateInfo.imageType     = VK_IMAGE_TYPE_2D;
	imageCreateInfo.format        = targetFormat; //VK_FORMAT_R8G8B8A8_UNORM;
	imageCreateInfo.extent.width  = imageWidth;
	imageCreateInfo.extent.height = imageHeight;
	imageCreateInfo.extent.depth  = 1;
	imageCreateInfo.mipLevels     = 1;
	imageCreateInfo.arrayLayers   = 1;
	imageCreateInfo.samples       = VK_SAMPLE_COUNT_1_BIT;
	imageCreateInfo.tiling        = VK_IMAGE_TILING_OPTIMAL;
    imageCreateInfo.usage = 
        VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | 
        VK_IMAGE_USAGE_TRANSFER_DST_BIT |
        VK_IMAGE_USAGE_TRANSFER_SRC_BIT | 
        VK_IMAGE_USAGE_SAMPLED_BIT;
	imageCreateInfo.flags         = 0;
	imageCreateInfo.sharingMode   = VK_SHARING_MODE_EXCLUSIVE;

	VkResult result = vkCreateImage( vkDevice, &imageCreateInfo, nullptr, pImage );

	if (result != VK_SUCCESS)
	{
		return false;
	}

	VkMemoryRequirements memoryRequirements;

	if ( externalMemoryProperties.externalMemoryFeatures &
         VK_EXTERNAL_MEMORY_FEATURE_DEDICATED_ONLY_BIT_KHR )
	{
		VkMemoryDedicatedRequirementsKHR dedicatedRequirements;
		memset(&dedicatedRequirements, 0, sizeof(dedicatedRequirements));
		dedicatedRequirements.sType = VK_STRUCTURE_TYPE_MEMORY_DEDICATED_REQUIREMENTS_KHR;
		dedicatedRequirements.pNext = nullptr;

		VkMemoryRequirements2KHR memoryRequirements2;
		memset(&memoryRequirements2, 0, sizeof(VkMemoryRequirements2KHR));
		memoryRequirements2.sType = VK_STRUCTURE_TYPE_MEMORY_REQUIREMENTS_2_KHR;
		memoryRequirements2.pNext = &dedicatedRequirements;

		VkImageMemoryRequirementsInfo2KHR imageRequirementsInfo;
		memset(&imageRequirementsInfo, 0, sizeof(VkImageMemoryRequirementsInfo2KHR));
		imageRequirementsInfo.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_REQUIREMENTS_INFO_2_KHR;
		imageRequirementsInfo.pNext = nullptr;
		imageRequirementsInfo.image = *pImage;

		__vkGetImageMemoryRequirements2KHR( vkDevice, &imageRequirementsInfo, &memoryRequirements2 );
		memoryRequirements = memoryRequirements2.memoryRequirements;
	}
	else
	{
        vkGetImageMemoryRequirements( vkDevice, *pImage, &memoryRequirements );
	}

	uint32_t memoryTypeIndex = 0xdeadbeef;

	{
		//Get memory type index

		VkMemoryPropertyFlags properties     = VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;

		VkPhysicalDeviceMemoryProperties props;
		vkGetPhysicalDeviceMemoryProperties(physicalDevice, &props);

		for (auto i = 0u; i < props.memoryTypeCount; i++)
		{
			if ((1 << i) & memoryRequirements.memoryTypeBits)
			{
				if ((props.memoryTypes[i].propertyFlags & properties) == properties)
				{
					memoryTypeIndex = i;
				}
			}
		}
	}

    if ( memoryTypeIndex == -1 )
    {
        DEV_ASSERT( false );
        return false;
    }

	VkImportMemoryWin32HandleInfoKHR importMemoryInfo;
	importMemoryInfo.sType      = VK_STRUCTURE_TYPE_IMPORT_MEMORY_WIN32_HANDLE_INFO_KHR;
	importMemoryInfo.pNext      = nullptr;
	importMemoryInfo.name       = nullptr;
	importMemoryInfo.handleType = handleType;
	importMemoryInfo.handle     = *pSharedHandle;

	VkMemoryAllocateInfo memoryInfo;
	memoryInfo.sType           = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
	memoryInfo.pNext           = &importMemoryInfo;
	memoryInfo.memoryTypeIndex = memoryTypeIndex;
	memoryInfo.allocationSize  = memoryRequirements.size;

	VkMemoryDedicatedAllocateInfoKHR dedicatedAllocationInfo;
    dedicatedAllocationInfo.sType = VK_STRUCTURE_TYPE_MEMORY_DEDICATED_ALLOCATE_INFO_KHR;
	dedicatedAllocationInfo.pNext  = nullptr;
	dedicatedAllocationInfo.buffer = VK_NULL_HANDLE;

	if (externalMemoryProperties.externalMemoryFeatures & VK_EXTERNAL_MEMORY_FEATURE_DEDICATED_ONLY_BIT_KHR)
	{
		dedicatedAllocationInfo.image = *pImage;
		importMemoryInfo.pNext        = &dedicatedAllocationInfo;
	}

	result = vkAllocateMemory( vkDevice, &memoryInfo, 0, pDeviceMemory );

	if (VK_SUCCESS != result)
	{
        vkDestroyImage( vkDevice, *pImage, nullptr );

		return false;
	}

	if (!(externalMemoryProperties.externalMemoryFeatures & VK_EXTERNAL_MEMORY_FEATURE_DEDICATED_ONLY_BIT_KHR))
	{
        result = vkBindImageMemory( vkDevice, *pImage, *pDeviceMemory, 0 );

		if (VK_SUCCESS != result)
		{
            vkDestroyImage( vkDevice, *pImage, nullptr );
			return false;
		}
	}
	else
	{
		VkBindImageMemoryInfoKHR bindImageMemoryInfo;
		memset(&bindImageMemoryInfo, 0, sizeof(VkBindImageMemoryInfoKHR));
		bindImageMemoryInfo.sType        = VK_STRUCTURE_TYPE_BIND_IMAGE_MEMORY_INFO;
		bindImageMemoryInfo.image        = *pImage;
		bindImageMemoryInfo.memory       = *pDeviceMemory;
		bindImageMemoryInfo.memoryOffset = 0;

		result = __vkBindImageMemory2KHR( vkDevice, 1, &bindImageMemoryInfo );

		if (VK_SUCCESS != result)
		{
            vkDestroyImage( vkDevice, *pImage, nullptr );
			return false;
		}
	}

	return true;
}


void Dx11TextureView::_ready()
{
    godot::UtilityFunctions::print( "ready call" );

    /* prepare dx11 application to share texture */
    rd = godot::RenderingServer::get_singleton()->get_rendering_device();
    VkPhysicalDevice vkPhysicalDevice = (VkPhysicalDevice)rd->get_driver_resource(
        godot::RenderingDevice::DRIVER_RESOURCE_VULKAN_PHYSICAL_DEVICE, godot::RID(), 0 );
    app.init( vkPhysicalDevice );

    
    VkDevice vkDevice = (VkDevice)rd->get_driver_resource(
        godot::RenderingDevice::DRIVER_RESOURCE_VULKAN_DEVICE, godot::RID(), 0 );
    
    VkExternalMemoryPropertiesKHR externalMemoryProperties;
    VkExternalMemoryHandleTypeFlagBitsKHR externalMemoryHandleType;

    VkFormat imageFormat = VK_FORMAT_R8G8B8A8_UNORM;
    VkImageUsageFlags imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT |
                                   VK_IMAGE_USAGE_TRANSFER_SRC_BIT |
                                   VK_IMAGE_USAGE_TRANSFER_DST_BIT;

    BOOL sharingTexturesSupported =
        isSharedTextureSupported( vkPhysicalDevice, vkDevice, imageFormat, imageUsage,
                                  &externalMemoryProperties, &externalMemoryHandleType );
    DEV_ASSERT( sharingTexturesSupported );

    createVulkanSharedTexture(
        vkPhysicalDevice, vkDevice, app.textureWidth, app.textureHeight, VK_FORMAT_R8G8B8A8_UNORM,
        VK_EXTERNAL_MEMORY_HANDLE_TYPE_D3D11_TEXTURE_BIT_KHR, externalMemoryProperties,
        &app.renderTargetHandle, &sharedImage, &sharedMemory );

    uint64_t usage_flags = godot::RenderingDevice::TEXTURE_USAGE_COLOR_ATTACHMENT_BIT |
                           godot::RenderingDevice::TEXTURE_USAGE_CAN_COPY_FROM_BIT |
                           godot::RenderingDevice::TEXTURE_USAGE_SAMPLING_BIT;
    auto texCreateResult = rd->texture_create_from_extension(
        godot::RenderingDevice::TEXTURE_TYPE_2D, godot::RenderingDevice::DATA_FORMAT_R8G8B8A8_UNORM,
        godot::RenderingDevice::TEXTURE_SAMPLES_1, usage_flags, (uint64_t)sharedImage,
        app.textureWidth, app.textureHeight, 1, 1 );

    textureRd = (godot::Ref<godot::Texture2DRD>)memnew( godot::Texture2DRD );
    textureRd->set_texture_rd_rid( texCreateResult );

    auto size = textureRd->get_size();
    auto imageRd = textureRd->get_image();

    godot::UtilityFunctions::print( "First 16 bytes of set_texture_rd_rid texture" );
    godot::UtilityFunctions::print( imageRd->get_data().slice( 0, 16 ).hex_encode() );


    DEV_ASSERT( size.width > 0 );

    
    this->set_texture( textureRd );

    
    godot::RID canvasRID = godot::RenderingServer::get_singleton()->canvas_item_create();
    godot::RenderingServer::get_singleton()->canvas_item_set_parent( canvasRID,
                                                                     this->get_canvas_item() );

    godot::RenderingServer::get_singleton()->canvas_item_add_texture_rect(
        canvasRID, godot::Rect2( 0, 110, 100, 100 ), textureRd->get_rid() );
}

void Dx11TextureView::_exit_tree()
{
    app.fini();
}

godot::String Dx11TextureView::_to_string() const
{
    return "[ GDExtension::Dx11TextureView <--> Instance ID:" + godot::uitos( get_instance_id() ) + " ]";
}

