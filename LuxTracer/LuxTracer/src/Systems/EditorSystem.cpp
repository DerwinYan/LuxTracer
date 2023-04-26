#include <Timer.h>
#include <Scenes/Scene1.h>
#include <Math/mathUtils.h>

namespace lux
{
	float maxFps{};
	float avgFps{};
	int frameCounter{1};

	template<typename BaseSystem>
	inline void EditorSystem<BaseSystem>::Init()
	{
		// Init IMGUI
		ImGui::CreateContext();
		ImGui::StyleColorsDark();
		ImGui_ImplGlfw_InitForOpenGL(Window::windowptr, true);
		ImGui_ImplOpenGL3_Init("#version 460 core");

		//Load scene
		scene::LoadScene1();
	}

	template<typename BaseSystem>
	void EditorSystem<BaseSystem>::Update()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		static bool alwaysOpen = true;
		ImGui::Begin("Inspector", &alwaysOpen);

		float fps = 1.0f / Timer::dt;
		if (fps > maxFps || maxFps == INFINITY)
			maxFps = fps;
		if (avgFps == INFINITY)
			avgFps = fps;
		avgFps += fps;
		ImGui::Text("Fps: %.2lf", fps);
		ImGui::Text("Max Fps: %.2lf", maxFps);
		ImGui::Text("Avg Fps: %.2lf", avgFps / (float)frameCounter);
		ImGui::Separator();

		float width = ImGui::GetWindowContentRegionMax().x - 10.0f;

		//Show properties
		for (size_t i{}; i < BaseSystem::scene.size(); ++i)
		{
			ImGui::PushID((int)i);
			GameObject& go = BaseSystem::scene[i];
			ImGui::Text("Gameobject %d", i);
			ImGui::DragFloat3("Position", go.position.data, 0.01f);
			ImGui::DragFloat("Radius", &go.radius, 0.1f, 0.0001f, math::inf);
			ImGui::ColorEdit3("Tint", go.mat.color.data);
			ImGui::ColorEdit3("Emission color", go.mat.emission.data);
			ImGui::SliderFloat("Emission strength", &go.mat.emissionStr, 0.0f, 5.0f);
			ImGui::Separator();
			ImGui::PopID();
		}

		ImGui::End();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		++frameCounter;
	}

	template<typename BaseSystem>
	void EditorSystem<BaseSystem>::UnInit()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}
}
