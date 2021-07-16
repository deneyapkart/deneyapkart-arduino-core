/***************************************************
Copyright (c) 2021 Luis Llamas
(www.luisllamas.es)

This program is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by
the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Affero General Public License for more details.

You should have received a copy of the GNU Affero General Public License along with this program.  If not, see <http://www.gnu.org/licenses
****************************************************/

#ifndef _ESP_COLOR_H_
#define _ESP_COLOR_H_

#define _ESP_COLOR_VERSION_ "1.0.0"

#include <cstddef>
#include <cstdint>
#include <type_traits>

#include "Colors.hpp"
#include "Palette.hpp"


class String;

namespace ESP_Color
{
	template <typename T>
	struct RGB
	{
		T R = T(0);
		T G = T(0);
		T B = T(0);
		T A = T(0);
	};
	using RGBf = RGB<float>;
	using RGBi = RGB<uint8_t>;

	template <typename T>
	struct HSV
	{
		T H = T(0);
		T S = T(0);
		T V = T(0);
		T A = T(0);
	};
	using HSVf = HSV<float>;
	using HSVi = HSV<uint8_t>;

	template <typename T>
	struct HSL
	{
		T H = T(0);
		T S = T(0);
		T L = T(0);
		T A = T(0);
	};
	using HSLf = HSL<float>;
	using HSLi = HSL<uint8_t>;

	enum GRAY_ALGORITHM
	{
		LIGHTNESS,
		AVERAGE,
		LUMINOSITY
	};

	class Color final
	{
	public:
		float R = 0.0f;
		float G = 0.0f;
		float B = 0.0f;
		float A = 0.0f;

		constexpr Color()
		{
		}

		explicit constexpr Color(const std::uint16_t color_rgb565, const float alpha = 1.0) :
			R(static_cast<std::uint8_t>((((((color_rgb565 >> 11) & 0x1F) * 527) + 23) >> 6)) / 255.0F),
			G(static_cast<std::uint8_t>(((((color_rgb565 >> 5) & 0x3F) * 259) + 33) >> 6) / 255.0F),
			B(static_cast<std::uint8_t>((((color_rgb565 & 0x1F) * 527) + 23) >> 6) / 255.0F),
			A(alpha)
		{
		}

		explicit constexpr Color(const std::uint32_t color) :
			R(static_cast<std::uint8_t>((color & 0xFF000000U) >> 24) / 255.0F),
			G(static_cast<std::uint8_t>((color & 0x00FF0000U) >> 16) / 255.0F),
			B(static_cast<std::uint8_t>((color & 0x0000FF00U) >> 8) / 255.0F),
			A(static_cast<std::uint8_t>(color & 0x000000FFU) / 255.0F)
		{
		}

		Color& operator=(const std::uint32_t color)
		{
			R = static_cast<std::uint8_t>((color & 0xFF000000U) >> 24) / 255.0F;
			G = static_cast<std::uint8_t>((color & 0x00FF0000U) >> 16) / 255.0F;
			B = static_cast<std::uint8_t>((color & 0x0000FF00U) >> 8) / 255.0F;
			A = static_cast<std::uint8_t>(color & 0x000000FFU) / 255.0F;

			return *this;
		}

		Color(const std::uint8_t red, const std::uint8_t green, const std::uint8_t blue, const std::uint8_t alpha = 0xFFU) :
			R(red / 255.0F),
			G(green / 255.0F),
			B(blue / 255.0F),
			A(alpha / 255.0F)
		{
		}

		Color(const float red, const float green, const float blue, const float alpha = 1.0f) :
			R(constrainf(red)),
			G(constrainf(green)),
			B(constrainf(blue)),
			A(constrainf(alpha))
		{ }

		Color(const float color[4]) : R(color[0]),
			G(color[1]),
			B(color[2]),
			A(color[3])
		{
		}

		Color operator+(const Color& color) const
		{
			return Color(R + color.R,
				G + color.G,
				B + color.B,
				A + color.A);
		}

		Color& operator+=(const float value)
		{
			R = constrainf(R + value);
			G = constrainf(G + value);
			B = constrainf(B + value);
			A = constrainf(A + value);
			return *this;
		}

		Color operator-(const Color& color) const
		{
			return Color(R - color.R,
				G - color.G,
				B - color.B,
				A - color.A);
		}

		Color& operator-=(const float value)
		{
			R = constrainf(R - value);
			G = constrainf(G - value);
			B = constrainf(B - value);
			A = constrainf(A - value);
			return *this;
		}

		Color operator*(const float value) const
		{
			return Color(R * value,
				G * value,
				B * value,
				A * value);
		}

		Color& operator*=(const float value)
		{
			R = constrainf(R * value);
			G = constrainf(G * value);
			B = constrainf(B * value);
			A = constrainf(A * value);
			return *this;
		}

		Color operator/(const float value) const
		{
			return Color(R / value,
				G / value,
				B / value,
				A / value);
		}

		Color& operator/=(const float value)
		{
			R = constrainf(R / value);
			G = constrainf(G / value);
			B = constrainf(B / value);
			A = constrainf(A / value);
			return *this;
		}

		std::uint8_t R_Byte()
		{
			return static_cast<std::uint8_t>(R * 255.0F);
		}

		std::uint8_t G_Byte()
		{
			return static_cast<std::uint8_t>(G * 255.0F);
		}

		std::uint8_t B_Byte()
		{
			return static_cast<std::uint8_t>(B * 255.0F);
		}

		std::uint8_t A_Byte()
		{
			return static_cast<std::uint8_t>(A * 255.0F);
		}

		Color LinearTo(const Color& target, float t) const
		{
			float r = (target.R - R) * t + R;
			float g = (target.G - G) * t + G;
			float b = (target.B - B) * t + B;
			float a = (target.A - A) * t + A;

			return Color(r, g, b, a);
		}

		static Color FromHsv(const HSVf hsv, const float alpha = 1.0f)
		{
			return FromHsv(hsv.V, hsv.S, hsv.V, alpha);
		}

		static Color FromHsv(const float hue, const float saturation, const float value, const float alpha = 1.0)
		{
			float r, g, b;

			const auto i = static_cast<int>(hue * 6);
			const auto f = hue * 6 - i;
			const auto p = value * (1 - saturation);
			const auto q = value * (1 - f * saturation);
			const auto t = value * (1 - (1 - f) * saturation);

			switch (i % 6)
			{
			case 0:
				r = value, g = t, b = p;
				break;
			case 1:
				r = q, g = value, b = p;
				break;
			case 2:
				r = p, g = value, b = t;
				break;
			case 3:
				r = p, g = q, b = value;
				break;
			case 4:
				r = t, g = p, b = value;
				break;
			case 5:
				r = value, g = p, b = q;
				break;
			}

			return Color(r, g, b, alpha);
		}

		static Color FromHsl(const HSLf hsv, const float alpha = 1.0f)
		{
			return FromHsl(hsv.H, hsv.S, hsv.L, alpha);
		}

		static Color FromHsl(const float hue, const float saturation, const float lightness, const float alpha = 1.0)
		{
			float r, g, b;

			if (saturation == 0)
			{
				r = g = b = lightness;
			}
			else
			{
				const auto q = lightness < 0.5 ? lightness * (1 + saturation) : lightness + saturation - lightness * saturation;
				const auto p = 2 * lightness - q;
				r = hue2rgb(p, q, hue + 1 / 3.0);
				g = hue2rgb(p, q, hue);
				b = hue2rgb(p, q, hue - 1 / 3.0);
			}

			return Color(r, g, b, alpha);
		}

		static Color FromTemperature(const int kelvin, const float alpha = 1.0)
		{
			float r, g, b;

			const auto temp = kelvin * 100;

			if (temp <= 66)
			{
				r = 1.0f;
				g = (99.4708025861 * log(temp) - 161.1195681661) / 255.0;

				if (temp <= 19)
				{
					b = 0.0f;
				}
				else
				{
					b = (138.5177312231 * log(temp - 10) - 305.0447927307) / 255.0;
				}
			}
			else
			{
				r = (329.698727446 * pow(temp - 60, -0.1332047592)) / 255.0;
				g = (288.1221695283 * pow(temp - 60, -0.0755148492)) / 255.0;
				b = 1.0f;
			}
			return Color(r, g, b, alpha);
		}

		static Color FromHex(String hex)
		{
			long number;

			if (hex[0] == '#') number = strtol(&hex[1], nullptr, 16);
			else number = strtol(&hex[0], nullptr, 16);

			uint8_t r = number >> 16;
			uint8_t g = number >> 8 & 0xFF;
			uint8_t b = number & 0xFF;

			return Color(r, g, b);
		}

		static Color FromGradient(const Color& color1, const Color& color2, const float t)
		{
			return color1.LinearTo(color2, t);
		}

		static Color FromGradient(const Color& color1, const Color& color2, const Color& color3, const float t)
		{
			if (t <= 0.5f) return color1.LinearTo(color2, t * 2);
			else return color2.LinearTo(color3, (t - 0.5f) * 2);
		}

		static Color FromGradient(const Color& color1, const Color& color2, const Color& color3, const Color& color4, const float t)
		{
			if (t <= 0.333333333f) return color1.LinearTo(color2, t * 3);
			else if (t <= 0.666666666f) return color2.LinearTo(color3, (t - 0.333333333f) * 3);
			else return color3.LinearTo(color4, (t - 0.666666666f) * 3);
		}

		static Color FromGradient(const Color& color1, const Color& color2, const Color& color3, const Color& color4, const Color& color5, const float t)
		{
			if (t <= 0.25f) return color1.LinearTo(color2, t * 4);
			else if (t <= 0.5f) return color2.LinearTo(color3, (t - 0.25f) * 4);
			else if (t <= 0.75f) return color3.LinearTo(color4, (t - 0.5f) * 4);
			else return color4.LinearTo(color5, (t - 0.75f) * 4);
		}

		RGBi ToRgbi()
		{
			RGBi rgbi;
			rgbi.R = R_Byte();
			rgbi.G = G_Byte();
			rgbi.B = B_Byte();
			rgbi.A = A_Byte();
			return rgbi;
		}

		std::uint32_t ToRgba8888()
		{
			return (static_cast<std::uint32_t>(R * 255.0F) << 24) |
				(static_cast<std::uint32_t>(G * 255.0F) << 16) |
				(static_cast<std::uint32_t>(B * 255.0F) << 8) |
				static_cast<std::uint32_t>(A * 255.0F);
		}

		std::uint32_t ToRgb888()
		{
			return RGB_TO_RGB888(R_Byte(), G_Byte(), B_Byte());
		}

		std::uint32_t ToRgb666()
		{
			return RGB_TO_RGB565(R_Byte(), G_Byte(), B_Byte());
		}

		std::uint16_t ToRgb565()
		{
			return RGB_TO_RGB565(R_Byte(), G_Byte(), B_Byte());
		}

		std::uint8_t ToRgb332()
		{
			return RGB_TO_RGB332(R_Byte(), G_Byte(), B_Byte());
		}

		HSVf ToHsv()
		{
			const auto max = threeway_max(R, G, B);
			const auto min = threeway_min(R, G, B);
			float h = 0, s, v = max;

			const auto d = max - min;
			s = max == 0 ? 0 : d / max;

			if (max == min)
			{
				h = 0;
			}
			else
			{
				if (max == R)
				{
					h = (G - B) / d + (G < B ? 6 : 0);
				}
				else if (max == G)
				{
					h = (B - R) / d + 2;
				}
				else if (max == B)
				{
					h = (R - G) / d + 4;
				}
				h /= 6;
			}

			HSVf hsv;
			hsv.H = h;
			hsv.S = s;
			hsv.V = v;
			hsv.A = A;
			return hsv;
		}

		HSLf ToHsl()
		{
			const auto max = threeway_max(R, G, B);
			const auto min = threeway_min(R, G, B);
			float h = 0, s;
			const float l = (max + min) / 2;

			if (max == min)
			{
				h = s = 0;
			}
			else
			{
				const auto d = max - min;
				s = l > 0.5 ? d / (2 - max - min) : d / (max + min);
				if (max == R)
				{
					h = (G - B) / d + (G < B ? 6 : 0);
				}
				else if (max == G)
				{
					h = (B - R) / d + 2;
				}
				else if (max == B)
				{
					h = (R - G) / d + 4;
				}
				h /= 6;
			}

			HSLf hsl;
			hsl.H = h;
			hsl.S = s;
			hsl.L = l;
			hsl.A = A;
			return hsl;
		}

		String& ToHex(std::uint8_t r, std::uint8_t g, std::uint8_t b)
		{
			char hexArray[6] = { 0 };
			sprintf(hexArray, "%02X%02X%02X", R_Byte(), G_Byte(), B_Byte());
			String hex = hexArray;
			return hex;
		}

		Color ToGray(GRAY_ALGORITHM mode = LUMINOSITY)
		{
			float g = ToGray(R, G, B, mode);
			return Color(g, g, g, A);
		}

		std::uint8_t ToGray256(GRAY_ALGORITHM mode = LUMINOSITY)
		{
			return static_cast<std::uint8_t>(ToGray(R, G, B, mode) * 255.0F);
		}

		std::uint8_t ToGray16(GRAY_ALGORITHM mode = LUMINOSITY) { return ToGray256(mode) >> 4; }

		std::uint8_t ToGray4(GRAY_ALGORITHM mode = LUMINOSITY) { return ToGray256(mode) >> 6; }

		bool ToBW(float threshold = 0)
		{
			return R > threshold || G > threshold || B > threshold;
		}

		template<class T>
		typename std::enable_if<std::is_same<T, Color>::value, uint32_t>::type
			To() { this; }

		template<class T>
		typename std::enable_if<std::is_same<T, uint32_t>::value, uint32_t>::type
			To() { return ToRgb888(); }

		template<class T>
		typename std::enable_if<std::is_same<T, uint16_t>::value, uint16_t>::type
			To() { return ToRgb565(); }

		template<class T>
		typename std::enable_if<std::is_same<T, uint8_t>::value, uint8_t>::type
			To() { return ToRgb332(); }

		template<class T>
		typename std::enable_if<std::is_same<T, RGBi>::value, RGBi>::type
			To() { return ToRgbi(); }


		template<class T>
		typename std::enable_if<std::is_same<T, HSVf>::value, HSVf>::type
			To() { return ToHsv(); }

		template<class T>
		typename std::enable_if<std::is_same<T, HSLf>::value, HSLf>::type
			To() { return ToHsl(); }

		//	template<class T>
		//typename std::enable_if<std::is_same<T, HSLi>::value, uint8_t>::type
		//	To() { return ToRgb332(); }

		//template<class T>
		//typename std::enable_if<std::is_same<T, HSLf>::value, uint8_t>::type
		//	To() { return ToRgb332(); }


		static constexpr std::uint8_t RGB_TO_RGB332(std::uint8_t r, std::uint8_t g, std::uint8_t b) { return (r >> 5) << 5 | (g >> 5) << 2 | b >> 6; }
		static constexpr std::uint16_t RGB_TO_RGB565(std::uint8_t r, std::uint8_t g, std::uint8_t b) { return (r >> 3) << 11 | (g >> 2) << 5 | b >> 3; }
		static constexpr std::uint32_t RGB_TO_RGB888(std::uint8_t r, std::uint8_t g, std::uint8_t b) { return r << 16 | g << 8 | b; }
		static constexpr std::uint16_t RGB_TO_SWAP565(std::uint8_t r, std::uint8_t g, std::uint8_t b) { return (((r >> 3) << 3) + (g >> 5)) | (((g >> 2) << 5) | (b >> 3)) << 8; }
		static constexpr std::uint32_t RGB_TO_SWAP888(std::uint8_t r, std::uint8_t g, std::uint8_t b) { return b << 16 | g << 8 | r; }

		static constexpr std::uint32_t swap_24bits(std::uint32_t c) { return ((std::uint8_t)c) << 16 | ((std::uint8_t)(c >> 8)) << 8 | (std::uint8_t)(c >> 16); }

		static constexpr std::uint32_t BGR888_TO_RGB332(std::uint32_t c) { return ((std::uint8_t)c >> 5) << 5 | (((std::uint16_t)c) >> 13) << 2 | c >> 22; }
		static constexpr std::uint32_t BGR888_TO_RGB565(std::uint32_t c) { return (((std::uint8_t)c) >> 3) << 11 | (((std::uint16_t)c) >> 10) << 5 | c >> 19; }
		static constexpr std::uint32_t BGR888_TO_RGB888(std::uint32_t c) { return swap_24bits(c); }
		static constexpr std::uint32_t BGR888_TO_SWAP565(std::uint32_t c) { return (((std::uint8_t)c) >> 3) << 3 | ((std::uint16_t)c) >> 13 | (c & 0x1C00) << 3 | (c >> 19) << 8; }
		static constexpr std::uint32_t BGR888_TO_BGR666(std::uint32_t c) { return (c >> 2) & 0x3F3F3F; }

		static constexpr std::uint32_t RGB888_TO_RGB332(std::uint32_t c) { return ((c >> 21) << 5) | ((((std::uint16_t)c) >> 13) << 2) | ((c >> 6) & 3); }
		static constexpr std::uint32_t RGB888_TO_RGB565(std::uint32_t c) { return (c >> 19) << 11 | (((std::uint16_t)c) >> 10) << 5 | ((std::uint8_t)c) >> 3; }
		static constexpr std::uint32_t RGB888_TO_BGR888(std::uint32_t c) { return swap_24bits(c); }
		static constexpr std::uint32_t RGB888_TO_SWAP565(std::uint32_t c) { return (c >> 19) << 3 | ((std::uint16_t)c) >> 13 | (c & 0x1C00) << 3 | (((std::uint8_t)c) >> 3) << 8; }
		static constexpr std::uint32_t RGB888_TO_BGR666(std::uint32_t c) { return ((c >> 2) & 0x3F) << 16 | ((c >> 10) & 0x3F) << 8 | ((c >> 18) & 0x3F); }

		static constexpr std::uint32_t RGB565_TO_RGB332(std::uint32_t c) { return ((c >> 13) << 5) | ((c >> 6) & 0x1C) | ((c >> 3) & 3); }
		static constexpr std::uint32_t RGB565_TO_RGB888(std::uint32_t c) { return ((((c >> 11) * 0x21) >> 2) << 8 | ((((c >> 5) & 0x3F) * 0x41) >> 4)) << 8 | (((c & 0x1F) * 0x21) >> 2); }
		static constexpr std::uint32_t RGB565_TO_SWAP565(std::uint32_t c) { return (0xFF & c) << 8 | c >> 8; }
		static constexpr std::uint32_t RGB565_TO_BGR666(std::uint32_t c) { return ((c & 0x1F) << 17) | ((c & 0x10) << 12) | ((c & 0x7E0) << 3) | ((c >> 10) & 0xF8) | (c >> 15); }
		static constexpr std::uint32_t RGB565_TO_BGR888(std::uint32_t c) { return ((((c & 0x1F) * 0x21) >> 2) << 8 | ((((c >> 5) & 0x3F) * 0x41) >> 4)) << 8 | (((c >> 11) * 0x21) >> 2); }

		static constexpr std::uint32_t RGB332_TO_RGB888(std::uint32_t c) { return ((((c >> 5) * 0x49) >> 1) << 8 | ((c & 0x1C) * 0x49) >> 3) << 8 | ((c & 3) * 0x55); }
		static constexpr std::uint32_t RGB332_TO_BGR888(std::uint32_t c) { return (((c & 3) * 0x55) << 8 | ((c & 0x1C) * 0x49) >> 3) << 8 | (((c >> 5) * 0x49) >> 1); }
		static constexpr std::uint32_t RGB332_TO_BGR666(std::uint32_t c) { return (((c & 0xE0) * 9) >> 5) | ((c & 0x1C) * 0x240) | ((c & 3) * 0x15) << 16; }
		static constexpr std::uint32_t RGB332_TO_SWAP565(std::uint32_t c) { return (((c & 3) * 0x15) >> 1) << 8 | ((c & 0x1C) << 11) | ((c & 0x1C) >> 2) | (((c >> 5) * 0x24) & 0xF8); }

		static std::uint8_t GammaCorrection(std::uint8_t value)
		{
			return (((45 * (static_cast<unsigned long>(value) + 1) + 3488) * (static_cast<unsigned long>(value) + 1) - 136379) * (static_cast<unsigned long>(value) + 1) + 1305350) / 3722130;
		}

	private:
		static float ToGray(const float r, const float g, const float b, const GRAY_ALGORITHM mode = LUMINOSITY)
		{
			float grey = 0;
			if (mode == GRAY_ALGORITHM::LUMINOSITY) { grey = (0.21f * r + 0.72f * g + 0.07f * b); }
			else if (mode == GRAY_ALGORITHM::LIGHTNESS) { grey = (threeway_max(r, g, b) + threeway_min(r, g, b)) / 2; }
			else { grey = ((r + g + b) / 3); }

			return grey;
		}

		static float threeway_max(float a, float b, float c)
		{
			return max(a, max(b, c));
		}

		static float threeway_min(float a, float b, float c)
		{
			return min(a, min(b, c));
		}

		static float constrainf(float f, float minf = 0.0f, float maxf = 1.0f)
		{
			if (f > maxf) f = maxf;
			if (f < minf) f = minf;
			return f;
		}

		static float hue2rgb(float p, float q, float t)
		{
			if (t < 0)
				t += 1;
			if (t > 1)
				t -= 1;
			if (t < 1 / 6.0)
				return p + (q - p) * 6 * t;
			if (t < 1 / 2.0)
				return q;
			if (t < 2 / 3.0)
				return p + (q - p) * (2 / 3.0 - t) * 6;
			return p;
		}
	};
}

#endif
