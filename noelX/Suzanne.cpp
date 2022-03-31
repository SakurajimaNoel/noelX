#include "Suzanne.h"

Suzanne::Suzanne(Graphics& gfx)
{
	
	Assimp::Importer importer;
	const auto pModel = importer.ReadFile("suzanne.obj",
		aiProcess_Triangulate | aiProcess_JoinIdenticalVertices);
	const auto pMesh = pModel->mMeshes[0];
	
	vertices.reserve(pMesh->mNumVertices);
	for (unsigned int i = 0; i < pMesh->mNumVertices; i++)
	{
		vertices.emplace_back(
			DirectX::XMFLOAT3{
					pMesh->mVertices[i].x *scale,
					pMesh->mVertices[i].y *scale,
					pMesh->mVertices[i].z *scale
			}, *reinterpret_cast<DirectX::XMFLOAT3*>(&pMesh->mNormals[i])
		);
	}

	indices.reserve(pMesh->mNumFaces * 3);
	for (unsigned int i = 0; i < pMesh->mNumFaces; i++)
	{
		const auto& face = pMesh->mFaces[i];
		indices.push_back(face.mIndices[0]);
		indices.push_back(face.mIndices[1]);
		indices.push_back(face.mIndices[2]);
	}

	initVSConstantBuffer(gfx, vertexCBuff, 0u);
	colorCBuff.color = material;
	initPSConstantBuffer(gfx, colorCBuff, 1);
	initIndexBuffer(gfx, indices);
	initPixelShader(gfx, pixelShader);
	initRasterizer(gfx, D3D11_CULL_FRONT);
	//initSampler(gfx);
	//initTexture(gfx, texture);
	setTopology(gfx, topology);
	initVertexBuffer(gfx, vertices);
	initVertexShaderAndIA(gfx, vertexShader, idesc);
	initViewport(gfx);
	
}
void Suzanne::updateTransform(Graphics& gfx)
{

	vertexCBuff.modelView = DirectX::XMMatrixIdentity() * gfx.getCamera();
	vertexCBuff.modelViewProjection = DirectX::XMMatrixTranspose
	(
		vertexCBuff.modelView * //model
		//gfx.getCamera() * //view
		DirectX::XMMatrixPerspectiveLH(1.0f, 0.75f, 0.4f, 100.0f) //projection matrix
	);



	/*cbvs =
	{
		{
			DirectX::XMMatrixTranspose
			(
				gfx.getCamera() *
				DirectX::XMMatrixPerspectiveLH(1.0f, 0.75f, 0.4f, 100.0f) //projection matrix

			)
		}
	};*/

	initVSConstantBuffer(gfx, vertexCBuff, 0u);
}

void Suzanne::bindAndDraw(Graphics& gfx)
{
	bindResources(gfx);
	gfx.drawIndexed(indices.size());
}
