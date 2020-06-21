#include "pch.h"
#include "Renderer2D.h"
#include <SK-Game-Engine\Renderer\VertexArray.h>
#include <SK-Game-Engine\Renderer\Shader.h>
#include <SK-Game-Engine\Renderer\RenderCommand.h>
#include <glm\ext\matrix_transform.hpp>

namespace SK_Game_Engine
{
	struct Renderer2DStorage
	{
		Ref<VertexArray> VertexArray;
		Ref<ShaderLibrary> ShaderLibrary;
		Ref<Texture2D> WhiteTexture;
	};

	static Scope<Renderer2DStorage> storage;

	void Renderer2D::Init()
	{
		SKGE_PROFILING_FUNCTION();

		storage = std::make_unique<Renderer2DStorage>();
		storage->VertexArray = VertexArray::Create();
		storage->ShaderLibrary = std::make_unique<ShaderLibrary>();

		float squareVertices[] =
		{
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
		};

		Ref<VertexBuffer> squareVertexBuffer = VertexBuffer::Create(squareVertices, sizeof(squareVertices));


		squareVertexBuffer->SetLayout(BufferLayout
			{
				{ ShaderDataType::Float3, "v_Position"},
				{ ShaderDataType::Float2, "v_TexCoord"}
			});
		storage->VertexArray->AddVertexBuffer(squareVertexBuffer);
		uint32_t squareIndices[] = { 0,1,2, 2,3,0 };
		Ref<IndexBuffer> squareIndexBuffer = IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
		storage->VertexArray->AddIndexBuffer(squareIndexBuffer);
		storage->WhiteTexture = Texture2D::Create(1, 1);
		uint32_t whiteTextureData = 0xffffffff;
		storage->WhiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));
		storage->ShaderLibrary->Add(Shader::Create("Shader", "assets/shaders/Shader.glsl"));
		// Ref<Shader> textureShader = storage->ShaderLibrary->Get("TextureShader");
		// textureShader->Bind();
		Ref<Shader> shader = storage->ShaderLibrary->Get("Shader");
		shader->SetInt("u_Texture", 0);
	}

	void Renderer2D::Shutdown()
	{
		SKGE_PROFILING_FUNCTION();

		storage.release();
	}

	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{
		SKGE_PROFILING_FUNCTION();

		Ref<Shader> shader = storage->ShaderLibrary->Get("Shader");
		shader->Bind();
		shader->SetMat4("u_ViewProjectionMatrix", camera.GetViewProjectionMatrix());
	}

	void Renderer2D::EndScene()
	{
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{
		DrawQuad({ position.x, position.y, 0 }, size, color);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{
		SKGE_PROFILING_FUNCTION();

		Ref<Shader> shader = storage->ShaderLibrary->Get("Shader");
		shader->SetFloat4("u_Color", color);
		shader->SetFloat("u_TilingFactor", 1.0f);
		storage->WhiteTexture->Bind();
		glm::mat4 scale = glm::scale(glm::mat4(1), glm::vec3(size.x, size.y, 1.0f));
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * scale;
		shader->SetMat4("u_TransformationMatrix", transform);
		storage->VertexArray->Bind();
		RenderCommand::DrawIndexed(storage->VertexArray);
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor)
	{
		DrawQuad({ position.x, position.y, 0 }, size, texture, tilingFactor, tintColor);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor)
	{
		SKGE_PROFILING_FUNCTION();

		Ref<Shader> shader = storage->ShaderLibrary->Get("Shader");
		shader->SetFloat4("u_Color", tintColor);
		shader->SetFloat("u_TilingFactor", tilingFactor);
		texture->Bind();
		glm::mat4 translation = glm::translate(glm::mat4(1.0f), position);
		glm::mat4 scale = glm::scale(glm::mat4(1), glm::vec3(size.x, size.y, 1.0f));
		glm::mat4 transform = translation * scale;
		texture->Bind();
		shader->SetMat4("u_TransformationMatrix", transform);
		storage->VertexArray->Bind();
		RenderCommand::DrawIndexed(storage->VertexArray);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotationAngle, const glm::vec4& color)
	{
		DrawRotatedQuad({ position.x, position.y, 0.0f }, size, rotationAngle, color);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotationAngle, const glm::vec4& color)
	{
		SKGE_PROFILING_FUNCTION();

		Ref<Shader> shader = storage->ShaderLibrary->Get("Shader");
		shader->SetFloat4("u_Color", color);
		shader->SetFloat("u_TilingFactor", 1.0f);
		storage->WhiteTexture->Bind();
		glm::mat4 translation = glm::translate(glm::mat4(1.0f), position);
		glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), rotationAngle, { 0.0f, 0.0f, 1.0f });
		glm::mat4 scale = glm::scale(glm::mat4(1), glm::vec3(size.x, size.y, 1.0f));
		glm::mat4 transform = translation * rotation * scale;
		shader->SetMat4("u_TransformationMatrix", transform);
		storage->VertexArray->Bind();
		RenderCommand::DrawIndexed(storage->VertexArray);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotationAngle, const Ref<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor)
	{
		DrawRotatedQuad({position.x, position.y, 0.0f}, size, rotationAngle, texture, tilingFactor, tintColor);
	}
	void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotationAngle, const Ref<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor)
	{
		SKGE_PROFILING_FUNCTION();

		Ref<Shader> shader = storage->ShaderLibrary->Get("Shader");
		shader->SetFloat4("u_Color", tintColor);
		shader->SetFloat("u_TilingFactor", tilingFactor);
		texture->Bind();
		glm::mat4 translation = glm::translate(glm::mat4(1.0f), position);
		glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), rotationAngle, { 0.0f, 0.0f, 1.0f });
		glm::mat4 scale = glm::scale(glm::mat4(1), glm::vec3(size.x, size.y, 1.0f));
		glm::mat4 transform = translation * rotation * scale;
		texture->Bind();
		shader->SetMat4("u_TransformationMatrix", transform);
		storage->VertexArray->Bind();
		RenderCommand::DrawIndexed(storage->VertexArray);
	}
}