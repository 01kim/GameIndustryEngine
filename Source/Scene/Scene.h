#pragma once

#include <memory>
#include "Phoenix/Types.h"
#include "Phoenix/OS/Display.h"
#include "Phoenix/Graphics/GraphicsDevice.h"
#include "Phoenix/Graphics/Camera.h"
#include "Phoenix/Graphics/Texture.h"
#include "Phoenix/FrameWork/Object/Object.h"
#include "Phoenix/FrameWork/Shader/Shader.h"
#include "Phoenix/FrameWork/Shader/BasicShader.h"
#include "Phoenix/FrameWork/Shader/BasicSkinShader.h"
#include "Phoenix/FrameWork/Shader/StandardShader.h"
#include "Phoenix/FrameWork/Shader/PBRShader.h"
#include "../Source/Graphics/Device/Win/DirectX11/DeviceDX11.h"
#include "Phoenix/FrameWork/FrameBuffer/FrameBuffer.h"
#include "Phoenix/FrameWork/Quad/Quad.h"
#include "Phoenix/FrameWork/IBL/IBL.h"
#include "Phoenix/FrameWork/ComputeShader/TestComputeShader.h"
#include "Phoenix/FrameWork/ComputeShader/BitonicSort.h"
#include "Phoenix/FrameWork/ComputeShader/GPUParticle.h"


class SceneSystem;
class SceneCommonData;
class Scene
{
protected:
	SceneSystem* sceneSystem = nullptr;
	Phoenix::OS::IDisplay* display = nullptr;
	Phoenix::Graphics::IGraphicsDevice* graphicsDevice = nullptr;
	SceneCommonData* commonData = nullptr;

public:
	Scene() {}
	virtual ~Scene() {}

public:
	virtual void Construct(SceneSystem* sceneSystem) = 0;
	virtual void Initialize() = 0;
	virtual void Update(Phoenix::f32 elapsedTime) = 0;
	virtual void Draw(Phoenix::f32 elapsedTime) = 0;
	virtual void GUI() = 0;
};

class SceneTitle : public Scene
{
private:
	// �t���[���o�b�t�@
	std::unique_ptr<Phoenix::FrameWork::FrameBuffer> frameBuffer[3];

	// �|�X�g�v���Z�X
	std::unique_ptr<Phoenix::FrameWork::PostProcessingEffects> postProcessingEffects;

	// �u���[��
	std::unique_ptr<Phoenix::FrameWork::Quad> quad;
	std::unique_ptr<Phoenix::FrameWork::MSAAResolve> msaaResolve;
	std::unique_ptr<Phoenix::FrameWork::Bloom> bloom;

	// �X�J�C�}�b�v
	std::unique_ptr<Phoenix::FrameWork::SkyMap> skyMap;

	// �^�C�g��
	std::unique_ptr<Phoenix::Graphics::ITexture> logo;
	std::unique_ptr<Phoenix::Graphics::ITexture> icon;
	std::unique_ptr<Phoenix::Graphics::ITexture> button;
	Phoenix::f32 dissolveThreshold = 0.0f;        //����臒l
	Phoenix::f32 dissolveEmissiveWidth = 0.0f;    //����臒l(�f�B�]���u�E�G�~�b�V�u)

	// �t���O
	bool isChangeScene = false;

public:
	SceneTitle() {}
	~SceneTitle() {}

public:
	void Construct(SceneSystem* sceneSystem) override;
	void Initialize() override;
	void Update(Phoenix::f32 elapsedTime) override;
	void Draw(Phoenix::f32 elapsedTime) override;
	void GUI() override;
};

class SceneGame : public Scene
{
private:
	// �v���C���[�J����
	std::shared_ptr<Phoenix::Graphics::Camera> camera;

	// �t���[���o�b�t�@
	std::unique_ptr<Phoenix::FrameWork::FrameBuffer> frameBuffer[6];

	// �|�X�g�v���Z�X
	std::unique_ptr<Phoenix::FrameWork::PostProcessingEffects> postProcessingEffects;

	// �V���h�E�}�b�v
	std::unique_ptr<Phoenix::FrameWork::FrameBuffer> shadowMap;
	std::unique_ptr<Phoenix::Graphics::IShader> voidPS;
	std::unique_ptr<Phoenix::Graphics::Camera> lightSpaceCamera;
	std::unique_ptr<Phoenix::Graphics::IBuffer> shaderConstantsBuffer;
	std::unique_ptr<Phoenix::Graphics::ISampler> comparisonSamplerState;
	ShaderConstants shaderContexts;

	// ���[�V�����u���[
	bool isMotionBlur = false;
	std::unique_ptr<Phoenix::FrameWork::MotionBlur> motionBlur;
	Phoenix::s32 targetEnemyIndex = -1;

	// �u���[��
	std::unique_ptr<Phoenix::FrameWork::Quad> quad;
	std::unique_ptr<Phoenix::FrameWork::MSAAResolve> msaaResolve;
	std::unique_ptr<Phoenix::FrameWork::Bloom> bloom;

	// �X�J�C�}�b�v
	std::unique_ptr<Phoenix::FrameWork::SkyMap> skyMap;

	// �g�[���}�b�v
	std::unique_ptr<Phoenix::FrameWork::ToneMap> toneMap;

	// �X�N���[���t�B���^�[
	Phoenix::f32 bright = 0.1f; //���x
	Phoenix::f32 contrast = 0.9f; //�Z�W
	Phoenix::f32 saturate = 1.1f; //�ʓx
	Phoenix::Math::Color screenColor = Phoenix::Math::Color::White; //�F��

public:
	SceneGame() {}
	~SceneGame() {}

public:
	void Construct(SceneSystem* sceneSystem) override;
	void Initialize() override;
	void Update(Phoenix::f32 elapsedTime) override;
	void Draw(Phoenix::f32 elapsedTime) override;
	void GUI() override;
};