/***************************************************
Copyright (c) 2021 Luis Llamas
(www.luisllamas.es)

This program is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by
the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Affero General Public License for more details.

You should have received a copy of the GNU Affero General Public License along with this program.  If not, see <http://www.gnu.org/licenses
****************************************************/

#pragma once

#include "Palettes64/Palette_accent_64.h"
#include "Palettes64/Palette_afmhot_64.h"
#include "Palettes64/Palette_autum_64.h"
#include "Palettes64/Palette_black_white_64.h"
#include "Palettes64/Palette_blues_64.h"
#include "Palettes64/Palette_bone_64.h"
#include "Palettes64/Palette_brewer_64.h"
#include "Palettes64/Palette_brg_64.h"
#include "Palettes64/Palette_bwr_64.h"
#include "Palettes64/Palette_cmrmap_64.h"
#include "Palettes64/Palette_cold_64.h"
#include "Palettes64/Palette_cool_64.h"
#include "Palettes64/Palette_cool_warm_64.h"
#include "Palettes64/Palette_cooper_64.h"
#include "Palettes64/Palette_dark_64.h"
#include "Palettes64/Palette_earth_64.h"
#include "Palettes64/Palette_fire_64.h"
#include "Palettes64/Palette_gnuplot2_64.h"
#include "Palettes64/Palette_gnuplot_64.h"
#include "Palettes64/Palette_helix_64.h"
#include "Palettes64/Palette_hot_64.h"
#include "Palettes64/Palette_hsv_64.h"
#include "Palettes64/Palette_jet_64.h"
#include "Palettes64/Palette_magma_64.h"
#include "Palettes64/Palette_ocean_64.h"
#include "Palettes64/Palette_oranges_64.h"
#include "Palettes64/Palette_orange_purple_64.h"
#include "Palettes64/Palette_paired_64.h"
#include "Palettes64/Palette_pastel1_64.h"
#include "Palettes64/Palette_pastel2_64.h"
#include "Palettes64/Palette_pink_64.h"
#include "Palettes64/Palette_pink_green_64.h"
#include "Palettes64/Palette_plasma_64.h"
#include "Palettes64/Palette_rainbow_64.h"
#include "Palettes64/Palette_rainbow2_64.h"
#include "Palettes64/Palette_redBlue_64.h"
#include "Palettes64/Palette_reds_64.h"
#include "Palettes64/Palette_red_blue_64.h"
#include "Palettes64/Palette_set1_64.h"
#include "Palettes64/Palette_set2_64.h"
#include "Palettes64/Palette_set3_64.h"
#include "Palettes64/Palette_soft_rainbow_64.h"
#include "Palettes64/Palette_spectral_64.h"
#include "Palettes64/Palette_spring_64.h"
#include "Palettes64/Palette_spring2_64.h"
#include "Palettes64/Palette_stern_64.h"
#include "Palettes64/Palette_summer_64.h"
#include "Palettes64/Palette_terrain_64.h"
#include "Palettes64/Palette_tropical_64.h"
#include "Palettes64/Palette_vivid_64.h"
#include "Palettes64/Palette_winter_64.h"
#include "Palettes64/Palette_yellow_blue_green_64.h"
#include "Palettes64/Palette_yellow_green_64.h"


namespace ESP_Color
{
	template <class T>
	class Palette
	{
	public:
		Palette(T* palette, T paletteSize)
		{
			data = palette;
			dataSize = paletteSize;
		}

		Palette(T paletteSize)
		{
			data = new T[paletteSize];
			dataSize = paletteSize;
		}

		T operator[](std::size_t index) { return GetData(index); }

		T GetData(std::size_t index)
		{
			auto i = index;

			if (Reversed) i = dataSize - 1 - index;

			if (index < OffsetStart) index = OffsetStart;
			if (index > dataSize - 1 - OffsetEnd) index = OffsetEnd;

			return data[index];
		}

		T GetData(std::size_t index, int min, int max)
		{
			auto i = linear_interpolate(index, min, max, 0, dataSize);

			if (Reversed) i = dataSize - 1 - index;

			if (index < OffsetStart) index = OffsetStart;
			if (index > dataSize - 1 - OffsetEnd) index = OffsetEnd;

			return data[index];
		}

		void Generate(const std::function<T(float)>& generator)
		{
			for (size_t index = 0; index < dataSize; index++)
			{
				data[index] = generator((float)index / dataSize);
			}
		}

		std::size_t GetSize()
		{
			return dataSize;
		}

		std::size_t OffsetStart = 0;
		std::size_t OffsetEnd = 0;
		bool Reversed = false;

	private:
		T* data;
		std::size_t  dataSize;

		T linear_interpolate(T x, T in_min, T in_max, T out_min, T out_max)
		{
			return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
		}
	};
}