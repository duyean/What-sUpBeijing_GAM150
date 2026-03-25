#include "Bounce.hpp"
#include "Mesh.hpp"
#include "../EaseFunctions/AEVEC2OVERLOAD.hpp"


void Bounce::awake()
{

}
void Bounce::init()
{
	targetMesh = GetComponent<Mesh>()->targetMesh;
}
void Bounce::update()
{
	// 1. Lock/Map the buffer to get a pointer to the CPU-side data
	AEGfxVertexBuffer* pVertices = nullptr;


	// 2. Iterate through all vertices
	for (int i = 0; i < numVertices; ++i) {
		// 3. Identify top vertices based on their y-coordinate
		// Replace 1.0f with the Y-height of the top of your object
		if (pVertices[i].position.y >= 1.0f - 0.01f) {
			// 4. Modify the position for the bounce (e.g., using sin wave)
			pVertices[i].position.y = originalY + sin(time) * bounceAmplitude;
		}
	}

	// 5. Unlock/Unmap the buffer to update GPU memory
	mpVtBuffer->Unlock()
}
void Bounce::fixedUpdate()
{

}
void Bounce::destroy()
{

}
