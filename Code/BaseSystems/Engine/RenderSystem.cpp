#include "RenderSystem.hpp"
#include "MeshGen.hpp"

#include "../EaseFunctions/AEVEC2OVERLOAD.hpp"


void RenderSystem::init()
{
	meshSystem = &MeshGen::getInstance();
}
void RenderSystem::Draw(const Mesh &mesh)
{
	switch (mesh.type)
	{
	case BOX_B:
	{
		meshSystem->DrawBox(mesh.entity->transform->getPosition(), mesh.entity->transform->getScale(), mesh.color, mesh.entity->transform->getRotation());
		break;
	}
	case BOX_BL:
	{
		meshSystem->DrawBoxLeft(mesh.entity->transform->getPosition(), mesh.entity->transform->getScale(), mesh.color, mesh.entity->transform->getRotation());
		break;
	}
	case BOX_T:
	{
		meshSystem->DrawBoxTexture(mesh.entity->transform->getPosition(), mesh.entity->transform->getScale(), mesh.color, mesh.entity->transform->getRotation(), mesh.pTex);
		break;
	}
	case CIRCLE_B:
	{
		meshSystem->DrawCircle(mesh.entity->transform->getPosition(), mesh.entity->transform->getScale(), mesh.color);
		break;
	}
	case SPRITE_T:
	{
		//meshSystem->DrawBox(entity->transform->position, entity->transform->scale, color, entity->transform->Deg);
		break;
	}

	}

}

void RenderSystem::Draw(Text* text) const
{
	meshSystem->RenderFont(text);
}

void RenderSystem::RenderObjects(const std::vector<std::unique_ptr<Entity>>& entities)
{

    std::vector<IRenderable*> queue;
	for (int i = 0; i < entities.size(); i++)
	{
        if (auto mesh = entities[i]->getComponent<Mesh>()) {
            if (entities[i]->isActive == true && mesh->isActive == true)
            {
                queue.push_back(mesh);
            }
        }
    }
	for (int j = 0; j < meshSystem->tempTexts.size(); j++)
	{
		queue.push_back(meshSystem->tempTexts[j].get());
	}

    std::stable_sort(queue.begin(), queue.end(), [](const IRenderable* a, const IRenderable* b) {
        return a->drawOrder < b->drawOrder;
        });


    for (auto& cmd : queue) {
		if (cmd != nullptr)
		{
			Mesh* mesh = dynamic_cast<Mesh*>(cmd);
			if (mesh != nullptr)
			{
				Draw(*mesh);
			}
			Text* txt = dynamic_cast<Text*>(cmd);
			if (txt != nullptr)
			{
				Draw(txt);
			}
			
		}
       
    }

	meshSystem->tempTexts.clear();
}