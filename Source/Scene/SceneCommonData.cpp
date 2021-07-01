#include "SceneCommonData.h"
#include "../Source/Graphics/Device/Win/DirectX11/DeviceDX11.h"


std::shared_ptr<SceneCommonData> SceneCommonData::Create()
{
	return std::make_shared<SceneCommonData>();
}

void SceneCommonData::Initialize(Phoenix::Graphics::IGraphicsDevice* graphicsDevice)
{
	;
}