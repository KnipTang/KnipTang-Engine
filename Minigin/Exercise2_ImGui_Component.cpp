#include "Exercise2_ImGui_Component.h"
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_sdl2.h"
#include <cstdint>
#include <iostream>
#include <imgui_plot.h>
#include <chrono>
#include <numeric>

void dae::Exercise2_ImGui_Component::CalculateYValuesNormal()
{
	m_yValuesNormal.clear();

	struct Transform
	{
		float matrix[16] = {
			1,0,0,0,
			0,1,0,0,
			0,0,1,0,
			0,0,0,1 };
	};

	class GameObject3D
	{
	public:
		Transform transform;
		int ID;
	};

	const int bufferSize = 1 << 24;
	GameObject3D* buffer = new GameObject3D[bufferSize];

	for (int i = 0; i < bufferSize; ++i)
	{
		buffer[i].ID = i;
	}

	for (int step = 1; step <= 1024; step *= 2)
	{
		std::vector<float> tempVec;

		for (size_t j = 0; j < static_cast<size_t>(m_Samples); j++)
		{
			const auto start = std::chrono::high_resolution_clock::now();
			for (int i = 0; i < bufferSize; i += step)
			{
				buffer[i].ID *= 2;
			}
			const auto end = std::chrono::high_resolution_clock::now();
			const auto total = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

			tempVec.emplace_back(static_cast<float>(total));
		}

		m_yValuesNormal.emplace_back(std::accumulate(tempVec.begin(), tempVec.end(), 0.0f) / tempVec.size());
	}

	delete[] buffer;
}

void dae::Exercise2_ImGui_Component::CalculateYValuesAlt()
{
	m_yValuesAlt.clear();

	struct Transform
	{
		float matrix[16] = {
			1,0,0,0,
			0,1,0,0,
			0,0,1,0,
			0,0,0,1 };
	};

	class GameObject3DAlt
	{
	public:
		Transform* transform;
		int ID;
	};

	const int bufferSize = 1 << 25;
	GameObject3DAlt* buffer = new GameObject3DAlt[bufferSize];

	for (int i = 0; i < bufferSize; ++i)
	{
		buffer[i].ID = i;
	}

	for (int step = 1; step <= 1024; step *= 2)
	{
		std::vector<float> tempVec;

		for (size_t j = 0; j < static_cast<size_t>(m_Samples); j++)
		{
			const auto start = std::chrono::high_resolution_clock::now();
			for (int i = 0; i < bufferSize; i += step)
			{
				buffer[i].ID *= 2;
			}
			const auto end = std::chrono::high_resolution_clock::now();
			const auto total = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

			tempVec.emplace_back(static_cast<float>(total));
		}

		m_yValuesAlt.emplace_back(std::accumulate(tempVec.begin(), tempVec.end(), 0.0f) / tempVec.size());
	}

	delete[] buffer;
}

void dae::Exercise2_ImGui_Component::Render() const
{
	static ImU32 colorNormal = ImColor(0, 255, 0);
	static ImU32 colorAlt= ImColor(0, 0, 255);
	static uint32_t selection_start = 0, selection_length = 0;

	ImGui::Begin("Exercise 2", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

	if (ImGui::InputInt("# sampler", &m_Samples))
	{
	}
	if (ImGui::Button("Trash the cache with GameObject3D", ImVec2(250, 25)))
	{
		const_cast<Exercise2_ImGui_Component*>(this)->CalculateYValuesNormal();
	}

	// Draw first plot with multiple sources
	ImGui::PlotConfig conf;
	conf.values.xs = m_xValues.data();
	conf.values.count = 11;
	conf.values.ys = m_yValuesNormal.data();
	conf.values.ys_count = 3;
	conf.values.color = colorNormal;
	conf.scale.min = 0;
	conf.scale.max = m_yValuesNormal.at(0);
	conf.tooltip.show = true;
	conf.tooltip.format = "%g: %8.40g";
	conf.grid_x.show = true;
	conf.grid_x.size = 128;
	conf.grid_x.subticks = 4;
	conf.grid_y.show = true;
	conf.grid_y.size = m_yValuesNormal.at(0) / 2;
	conf.grid_y.subticks = 5;
	conf.selection.show = true;
	conf.selection.start = &selection_start;
	conf.selection.length = &selection_length;
	conf.frame_size = ImVec2(512, 200);
	ImGui::Plot("plot1", conf);

	if (ImGui::Button("Trash the cache with GameObject3DAlt", ImVec2(300, 25)))
	{
		const_cast<Exercise2_ImGui_Component*>(this)->CalculateYValuesAlt();
	}
	// Draw second plot with multiple sources
	conf.values.ys = m_yValuesAlt.data();
	conf.values.color = colorAlt;
	conf.scale.max = m_yValuesAlt.at(0);
	ImGui::Plot("plot2", conf);

	static const float* y_data[] = { m_yValuesNormal.data(), m_yValuesAlt.data() };
	static ImU32 colors[2] = { colorNormal, colorAlt };

	ImGui::Text("Combination:");

	// Draw 3 plot with multiple sources
	conf.values.xs = m_xValues.data();
	conf.values.ys = nullptr;
	conf.values.ys_list = y_data;
	conf.values.ys_count = 2;
	conf.values.colors = colors;
	conf.scale.max = m_yValuesNormal.at(0);
	conf.grid_y.size = m_yValuesNormal.at(0) / 2;
	ImGui::Plot("plot3", conf);

	ImGui::End();
}