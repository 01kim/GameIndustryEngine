#pragma once

#include <memory>
#include "Phoenix/Types.h"
#include "Phoenix/Graphics/GraphicsDevice.h"
#include "Phoenix/Graphics/Camera.h"
#include "Phoenix/FrameWork/Object/Object.h"
#include "Phoenix/FrameWork/Audio/Audio.h"
#include "Phoenix/FrameWork/Shader/Shader.h"
#include "Phoenix/FrameWork/Shader/BasicShader.h"
#include "Phoenix/FrameWork/Shader/BasicSkinShader.h"
#include "Phoenix/FrameWork/Shader/StandardShader.h"
#include "Phoenix/FrameWork/Shader/PBRShader.h"


class SceneCommonData
{
public:

public:
	SceneCommonData() {}
	~SceneCommonData() {}

public:
	// ê∂ê¨
	static std::shared_ptr<SceneCommonData> Create();

	// èâä˙âª
	void Initialize(Phoenix::Graphics::IGraphicsDevice* graphicsDevice);
};