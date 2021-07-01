#pragma once

#include <memory>
#include <vector>
#include "Component.h"
#include "Phoenix/Graphics/Model.h"
#include "Phoenix/Graphics/Texture.h"
#include "Phoenix/Graphics/GraphicsDevice.h"
#include "Phoenix/Math/PhoenixMath.h"


namespace Phoenix
{
	namespace FrameWork
	{
		//class Animator;
		class Model : public Component
		{
		private:
			struct Node
			{
				const char* name;
				Node* parent;
				Math::Vector3 scale;
				Math::Quaternion rotate;
				Math::Vector3 translate;
				Math::Matrix localTransform;
				Math::Matrix worldTransform;
			};

			struct MeshNode
			{
				std::vector<Math::Matrix> boneTransform;
				u32 boneTransformCount = 0;

				MeshNode() {}
			};

			struct Material
			{
				std::string name;
				std::vector<std::unique_ptr<Graphics::ITexture>> textures;
				std::vector<Math::Color> colors;
			};

		private:
			std::shared_ptr<Graphics::IModelResource> modelResource;
			//std::unique_ptr<Animator> animator;
			std::vector<Node> nodes;
			std::vector<MeshNode> meshNodes;
			std::vector<Material> materials;
			std::unique_ptr<OS::IResourceManager> resourceManamger;
			std::unique_ptr<OS::IFileStream> file;

			// �{�[�����񋓗p
			std::vector<const char*> boneNames;

		public:
			Model() {}
			~Model() {}

		public:
			//// �R���X�g���N�^
			//void Construct() override;

			//// �f�X�g���N�^
			//void Destruct() override;

			//// ������
			//void Initialize() override;

			//// �I����
			//void Finalize() override;

			// �X�V
			void Update() override;

		public:
			// ���f���̓ǂݍ���
			void Load(Graphics::IGraphicsDevice* graphicsDevice, const char* filename);
		};
	}
}