# SPDX-License-Identifier: Unlicense

target_sources( ${PROJECT_NAME}
    PRIVATE
        Dx11TextureView.h
        Dx11TextureView.cpp
        GDExtensionTemplate.h
        GDExtensionTemplate.cpp
        DX11App.h
        DX11App.cpp
        RegisterExtension.cpp
)

target_include_directories( ${PROJECT_NAME}
    PRIVATE
        "src"
)
