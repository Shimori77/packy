#pragma once

namespace shimori::packy {
    /**
     * File types for the entries.
     */
    enum EntryType {
        TEXT_PLAIN,
        TEXT_XML,
        TEXT_JSON,
        TEXT_YAML,
        SHADER_GLSL,
        SHADER_HLSL,
        SHADER_SPIRV,
        SHADER_BIN,
        IMAGE_PNG,
        IMAGE_EXR,
        SOUND_OGG,
        SOUND_OPUS,
        MODEL_WOBJ,
        MODEL_FBX,
        MATERIAL_WMTL,
        MATERIAL_SMTL,
    };
}