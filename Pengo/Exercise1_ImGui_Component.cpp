#include "Exercise1_ImGui_Component.h"
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_sdl2.h"
#include <cstdint>
#include <iostream>
#include <imgui_plot.h>
#include <chrono>
#include <numeric>

void dae::Exercise1_ImGui_Component::CalculateYValues()
{
	const int bufferSize = 1 << 26;
	int* buffer = new int[bufferSize];

	m_yValues.clear();

	for (int i = 0; i < bufferSize; ++i)
	{
		buffer[i] = i;
	}

	for (int step = 1; step <= 1024; step *= 2)
	{
		std::vector<float> tempVec;

		for (size_t j = 0; j < static_cast<size_t>(m_Samples); j++)
		{
			const auto start = std::chrono::high_resolution_clock::now();
			for (int i = 0; i < bufferSize; i += step)
			{
				buffer[i] *= 2;
			}
			const auto end = std::chrono::high_resolution_clock::now();
			const auto total = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

			tempVec.emplace_back(static_cast<float>(total));
		}

		m_yValues.emplace_back(std::accumulate(tempVec.begin(), tempVec.end(), 0.0f) / tempVec.size());
	}

	delete[] buffer;
}


void dae::Exercise1_ImGui_Component::Render() const
{
	static ImU32 color = ImColor(255, 165, 0);
	static uint32_t selection_start = 0, selection_length = 0;

	ImGui::Begin("Exercise 1", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

	if (ImGui::InputInt("# sampler", &m_Samples))
	{

	}
	if (ImGui::Button("Trash the cache", ImVec2(150, 25)))
	{
		const_cast<Exercise1_ImGui_Component*>(this)->CalculateYValues();
	}

	// Draw first plot with multiple sources
	ImGui::PlotConfig conf;
	conf.values.xs = m_xValues.data();
	conf.values.count = 11;
	conf.values.ys = m_yValues.data();
	conf.values.ys_count = 3;
	conf.values.color = color;
	conf.scale.min = 0;
	conf.scale.max = m_yValues.at(0);
	conf.tooltip.show = true;
	conf.tooltip.format = "%g: %8.40g";
	conf.grid_x.show = true;
	conf.grid_x.size = 128;
	conf.grid_x.subticks = 4;
	conf.grid_y.show = true;
	conf.grid_y.size = m_yValues.at(0)/2;
	conf.grid_y.subticks = 5;
	conf.selection.show = true;
	conf.selection.start = &selection_start;
	conf.selection.length = &selection_length;
	conf.frame_size = ImVec2(512, 200);
	ImGui::Plot("plot1", conf);
	ImGui::End();
}