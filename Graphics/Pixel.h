// Copyright © 2016 BugsEx. All rights reserved.
// Author: Dmitriy Lysenko
// License: http://opensource.org/licenses/MIT
// Site: http://lic-ui.bugsex.net

#pragma once

namespace licui
{
	namespace graphics
	{
		template<class Type, size_t Channels> struct PIXEL;

		template<class Type, size_t Channels> struct BASE_PIXEL
		{
		protected:
			Type m_aData[Channels];
		public:
			inline Type &operator[](const size_t channel);
			inline const Type &operator[](const size_t channel) const;
			inline bool operator==(const PIXEL<Type, Channels> &other) const;
			inline bool operator!=(const PIXEL<Type, Channels> &other) const;
		};

		template<class Type, size_t Channels> struct PIXEL :public BASE_PIXEL<Type, Channels>
		{

		};

		template<class Type> struct PIXEL<Type, 3> : public BASE_PIXEL<Type, 3>
		{
		public:
			inline Type getRed() const;
			inline Type getGreen() const;
			inline Type getBlue() const;

			inline void setRed(const Type value);
			inline void setGreen(const Type value);
			inline void setBlue(const Type value);

			inline PIXEL();
			inline PIXEL(const Type r, const Type g, const Type b);
		};

		template<class Type> struct PIXEL<Type, 4> : public BASE_PIXEL<Type, 4>
		{
		public:
			inline Type getRed() const;
			inline Type getGreen() const;
			inline Type getBlue() const;
			inline Type getAlpha() const;

			inline void setRed(const Type value);
			inline void setGreen(const Type value);
			inline void setBlue(const Type value);
			inline void setAlpha(const Type value);

			inline PIXEL();
			inline PIXEL(const Type r, const Type g, const Type b, const Type a);
		};

	#pragma region BASE_PIXEL
		template<class Type, size_t Channels> bool BASE_PIXEL<Type, Channels>::operator==(const PIXEL<Type, Channels> &other) const
		{
			for (size_t channel = 0; channel < Channels; channel++)
				if (other.m_aData[channel] != m_aData[channel])
					return false;
			return true;
		}

		template<class Type, size_t Channels> bool BASE_PIXEL<Type, Channels>::operator!=(const PIXEL<Type, Channels> &other) const
		{
			for (unsigned char channel = 0; channel < Channels; channel++)
				if (other.m_aData[channel] != m_aData[channel])
					return true;
			return false;
		}

		template<class Type, size_t Channels> Type &BASE_PIXEL<Type, Channels>::operator[](const size_t channel)
		{
	#ifdef _DEBUG
			if (channel >= Channels)
				throw "Channel is out of bounds";
	#endif
			return m_aData[channel];
		}

		template<class Type, size_t Channels> const Type &BASE_PIXEL<Type, Channels>::operator[](const size_t channel) const
		{
	#ifdef _DEBUG
			if (channel >= Channels)
				throw "Channel is out of bounds";
	#endif
			return m_aData[channel];
		}
	#pragma endregion

	#pragma region PIXEL<Type, 3>
		template<class Type> PIXEL<Type, 3>::PIXEL()
		{

		}

		template<class Type> PIXEL<Type, 3>::PIXEL(const Type r, const Type g, const Type b)
		{
			m_aData[0] = r;
			m_aData[1] = g;
			m_aData[2] = b;
		}

		template<class Type> Type PIXEL<Type, 3>::getRed() const
		{
			return m_aData[0];
		}

		template<class Type> void PIXEL<Type, 3>::setRed(const Type value)
		{
			m_aData[0] = value;
		}

		template<class Type> Type PIXEL<Type, 3>::getGreen() const
		{
			return m_aData[1];
		}

		template<class Type> void PIXEL<Type, 3>::setGreen(const Type value)
		{
			m_aData[1] = value;
		}

		template<class Type> Type PIXEL<Type, 3>::getBlue() const
		{
			return m_aData[2];
		}

		template<class Type> void PIXEL<Type, 3>::setBlue(const Type value)
		{
			m_aData[2] = value;
		}
	#pragma endregion

	#pragma region PIXEL<Type, 4>
		template<class Type> PIXEL<Type, 4>::PIXEL()
		{

		}

		template<class Type> PIXEL<Type, 4>::PIXEL(const Type r, const Type g, const Type b, const Type a)
		{
			m_aData[0] = r;
			m_aData[1] = g;
			m_aData[2] = b;
			m_aData[3] = a;
		}

		template<class Type> Type PIXEL<Type, 4>::getRed() const
		{
			return m_aData[0];
		}

		template<class Type> void PIXEL<Type, 4>::setRed(const Type value)
		{
			m_aData[0] = value;
		}

		template<class Type> Type PIXEL<Type, 4>::getGreen() const
		{
			return m_aData[1];
		}

		template<class Type> void PIXEL<Type, 4>::setGreen(const Type value)
		{
			m_aData[1] = value;
		}

		template<class Type> Type PIXEL<Type, 4>::getBlue() const
		{
			return m_aData[2];
		}

		template<class Type> void PIXEL<Type, 4>::setBlue(const Type value)
		{
			m_aData[2] = value;
		}

		template<class Type> Type PIXEL<Type, 4>::getAlpha() const
		{
			return m_aData[3];
		}

		template<class Type> void PIXEL<Type, 4>::setAlpha(const Type value)
		{
			m_aData[3] = value;
		}
	#pragma endregion
	}
}