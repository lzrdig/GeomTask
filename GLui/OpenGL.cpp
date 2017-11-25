#include "stdafx.h"
#include "OpenGL.h"

namespace OpenGLui
{
	GLubyte m_RasterFont[][13] =
	{
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
		{0x00, 0x00, 0x18, 0x18, 0x00, 0x00, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18},
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x36, 0x36, 0x36, 0x36},
		{0x00, 0x00, 0x00, 0x66, 0x66, 0xff, 0x66, 0x66, 0xff, 0x66, 0x66, 0x00, 0x00},
		{0x00, 0x00, 0x18, 0x7e, 0xff, 0x1b, 0x1f, 0x7e, 0xf8, 0xd8, 0xff, 0x7e, 0x18},
		{0x00, 0x00, 0x0e, 0x1b, 0xdb, 0x6e, 0x30, 0x18, 0x0c, 0x76, 0xdb, 0xd8, 0x70},
		{0x00, 0x00, 0x7f, 0xc6, 0xcf, 0xd8, 0x70, 0x70, 0xd8, 0xcc, 0xcc, 0x6c, 0x38},
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x1c, 0x0c, 0x0e},
		{0x00, 0x00, 0x0c, 0x18, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x18, 0x0c},
		{0x00, 0x00, 0x30, 0x18, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x18, 0x30},
		{0x00, 0x00, 0x00, 0x00, 0x99, 0x5a, 0x3c, 0xff, 0x3c, 0x5a, 0x99, 0x00, 0x00},
		{0x00, 0x00, 0x00, 0x18, 0x18, 0x18, 0xff, 0xff, 0x18, 0x18, 0x18, 0x00, 0x00},
		{0x00, 0x00, 0x30, 0x18, 0x1c, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00},
		{0x00, 0x00, 0x00, 0x38, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
		{0x00, 0x60, 0x60, 0x30, 0x30, 0x18, 0x18, 0x0c, 0x0c, 0x06, 0x06, 0x03, 0x03},
		{0x00, 0x00, 0x3c, 0x66, 0xc3, 0xe3, 0xf3, 0xdb, 0xcf, 0xc7, 0xc3, 0x66, 0x3c},
		{0x00, 0x00, 0x7e, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x78, 0x38, 0x18},
		{0x00, 0x00, 0xff, 0xc0, 0xc0, 0x60, 0x30, 0x18, 0x0c, 0x06, 0x03, 0xe7, 0x7e},
		{0x00, 0x00, 0x7e, 0xe7, 0x03, 0x03, 0x07, 0x7e, 0x07, 0x03, 0x03, 0xe7, 0x7e},
		{0x00, 0x00, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0xff, 0xcc, 0x6c, 0x3c, 0x1c, 0x0c},
		{0x00, 0x00, 0x7e, 0xe7, 0x03, 0x03, 0x07, 0xfe, 0xc0, 0xc0, 0xc0, 0xc0, 0xff},
		{0x00, 0x00, 0x7e, 0xe7, 0xc3, 0xc3, 0xc7, 0xfe, 0xc0, 0xc0, 0xc0, 0xe7, 0x7e},
		{0x00, 0x00, 0x30, 0x30, 0x30, 0x30, 0x18, 0x0c, 0x06, 0x03, 0x03, 0x03, 0xff},
		{0x00, 0x00, 0x7e, 0xe7, 0xc3, 0xc3, 0xe7, 0x7e, 0xe7, 0xc3, 0xc3, 0xe7, 0x7e},
		{0x00, 0x00, 0x7e, 0xe7, 0x03, 0x03, 0x03, 0x7f, 0xe7, 0xc3, 0xc3, 0xe7, 0x7e},
		{0x00, 0x00, 0x00, 0x38, 0x38, 0x00, 0x00, 0x38, 0x38, 0x00, 0x00, 0x00, 0x00},
		{0x00, 0x00, 0x30, 0x18, 0x1c, 0x1c, 0x00, 0x00, 0x1c, 0x1c, 0x00, 0x00, 0x00},
		{0x00, 0x00, 0x06, 0x0c, 0x18, 0x30, 0x60, 0xc0, 0x60, 0x30, 0x18, 0x0c, 0x06},
		{0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00},
		{0x00, 0x00, 0x60, 0x30, 0x18, 0x0c, 0x06, 0x03, 0x06, 0x0c, 0x18, 0x30, 0x60},
		{0x00, 0x00, 0x18, 0x00, 0x00, 0x18, 0x18, 0x0c, 0x06, 0x03, 0xc3, 0xc3, 0x7e},
		{0x00, 0x00, 0x3f, 0x60, 0xcf, 0xdb, 0xd3, 0xdd, 0xc3, 0x7e, 0x00, 0x00, 0x00},
		{0x00, 0x00, 0xc3, 0xc3, 0xc3, 0xc3, 0xff, 0xc3, 0xc3, 0xc3, 0x66, 0x3c, 0x18},
		{0x00, 0x00, 0xfe, 0xc7, 0xc3, 0xc3, 0xc7, 0xfe, 0xc7, 0xc3, 0xc3, 0xc7, 0xfe},
		{0x00, 0x00, 0x7e, 0xe7, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xe7, 0x7e},
		{0x00, 0x00, 0xfc, 0xce, 0xc7, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc7, 0xce, 0xfc},
		{0x00, 0x00, 0xff, 0xc0, 0xc0, 0xc0, 0xc0, 0xfc, 0xc0, 0xc0, 0xc0, 0xc0, 0xff},
		{0x00, 0x00, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xfc, 0xc0, 0xc0, 0xc0, 0xff},
		{0x00, 0x00, 0x7e, 0xe7, 0xc3, 0xc3, 0xcf, 0xc0, 0xc0, 0xc0, 0xc0, 0xe7, 0x7e},
		{0x00, 0x00, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xff, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3},
		{0x00, 0x00, 0x7e, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x7e},
		{0x00, 0x00, 0x7c, 0xee, 0xc6, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06},
		{0x00, 0x00, 0xc3, 0xc6, 0xcc, 0xd8, 0xf0, 0xe0, 0xf0, 0xd8, 0xcc, 0xc6, 0xc3},
		{0x00, 0x00, 0xff, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0},
		{0x00, 0x00, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xdb, 0xff, 0xff, 0xe7, 0xc3},
		{0x00, 0x00, 0xc7, 0xc7, 0xcf, 0xcf, 0xdf, 0xdb, 0xfb, 0xf3, 0xf3, 0xe3, 0xe3},
		{0x00, 0x00, 0x7e, 0xe7, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xe7, 0x7e},
		{0x00, 0x00, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xfe, 0xc7, 0xc3, 0xc3, 0xc7, 0xfe},
		{0x00, 0x00, 0x3f, 0x6e, 0xdf, 0xdb, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0x66, 0x3c},
		{0x00, 0x00, 0xc3, 0xc6, 0xcc, 0xd8, 0xf0, 0xfe, 0xc7, 0xc3, 0xc3, 0xc7, 0xfe},
		{0x00, 0x00, 0x7e, 0xe7, 0x03, 0x03, 0x07, 0x7e, 0xe0, 0xc0, 0xc0, 0xe7, 0x7e},
		{0x00, 0x00, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0xff},
		{0x00, 0x00, 0x7e, 0xe7, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3},
		{0x00, 0x00, 0x18, 0x3c, 0x3c, 0x66, 0x66, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3},
		{0x00, 0x00, 0xc3, 0xe7, 0xff, 0xff, 0xdb, 0xdb, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3},
		{0x00, 0x00, 0xc3, 0x66, 0x66, 0x3c, 0x3c, 0x18, 0x3c, 0x3c, 0x66, 0x66, 0xc3},
		{0x00, 0x00, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x3c, 0x3c, 0x66, 0x66, 0xc3},
		{0x00, 0x00, 0xff, 0xc0, 0xc0, 0x60, 0x30, 0x7e, 0x0c, 0x06, 0x03, 0x03, 0xff},
		{0x00, 0x00, 0x3c, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x3c},
		{0x00, 0x03, 0x03, 0x06, 0x06, 0x0c, 0x0c, 0x18, 0x18, 0x30, 0x30, 0x60, 0x60},
		{0x00, 0x00, 0x3c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x3c},
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc3, 0x66, 0x3c, 0x18},
		{0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x38, 0x30, 0x70},
		{0x00, 0x00, 0x7f, 0xc3, 0xc3, 0x7f, 0x03, 0xc3, 0x7e, 0x00, 0x00, 0x00, 0x00},
		{0x00, 0x00, 0xfe, 0xc3, 0xc3, 0xc3, 0xc3, 0xfe, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0},
		{0x00, 0x00, 0x7e, 0xc3, 0xc0, 0xc0, 0xc0, 0xc3, 0x7e, 0x00, 0x00, 0x00, 0x00},
		{0x00, 0x00, 0x7f, 0xc3, 0xc3, 0xc3, 0xc3, 0x7f, 0x03, 0x03, 0x03, 0x03, 0x03},
		{0x00, 0x00, 0x7f, 0xc0, 0xc0, 0xfe, 0xc3, 0xc3, 0x7e, 0x00, 0x00, 0x00, 0x00},
		{0x00, 0x00, 0x30, 0x30, 0x30, 0x30, 0x30, 0xfc, 0x30, 0x30, 0x30, 0x33, 0x1e},
		{0x7e, 0xc3, 0x03, 0x03, 0x7f, 0xc3, 0xc3, 0xc3, 0x7e, 0x00, 0x00, 0x00, 0x00},
		{0x00, 0x00, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xfe, 0xc0, 0xc0, 0xc0, 0xc0},
		{0x00, 0x00, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x00, 0x00, 0x18, 0x00},
		{0x38, 0x6c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x00, 0x00, 0x0c, 0x00},
		{0x00, 0x00, 0xc6, 0xcc, 0xf8, 0xf0, 0xd8, 0xcc, 0xc6, 0xc0, 0xc0, 0xc0, 0xc0},
		{0x00, 0x00, 0x7e, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x78},
		{0x00, 0x00, 0xdb, 0xdb, 0xdb, 0xdb, 0xdb, 0xdb, 0xfe, 0x00, 0x00, 0x00, 0x00},
		{0x00, 0x00, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0xfc, 0x00, 0x00, 0x00, 0x00},
		{0x00, 0x00, 0x7c, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0x7c, 0x00, 0x00, 0x00, 0x00},
		{0xc0, 0xc0, 0xc0, 0xfe, 0xc3, 0xc3, 0xc3, 0xc3, 0xfe, 0x00, 0x00, 0x00, 0x00},
		{0x03, 0x03, 0x03, 0x7f, 0xc3, 0xc3, 0xc3, 0xc3, 0x7f, 0x00, 0x00, 0x00, 0x00},
		{0x00, 0x00, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xe0, 0xfe, 0x00, 0x00, 0x00, 0x00},
		{0x00, 0x00, 0xfe, 0x03, 0x03, 0x7e, 0xc0, 0xc0, 0x7f, 0x00, 0x00, 0x00, 0x00},
		{0x00, 0x00, 0x1c, 0x36, 0x30, 0x30, 0x30, 0x30, 0xfc, 0x30, 0x30, 0x30, 0x00},
		{0x00, 0x00, 0x7e, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0x00, 0x00, 0x00, 0x00},
		{0x00, 0x00, 0x18, 0x3c, 0x3c, 0x66, 0x66, 0xc3, 0xc3, 0x00, 0x00, 0x00, 0x00},
		{0x00, 0x00, 0xc3, 0xe7, 0xff, 0xdb, 0xc3, 0xc3, 0xc3, 0x00, 0x00, 0x00, 0x00},
		{0x00, 0x00, 0xc3, 0x66, 0x3c, 0x18, 0x3c, 0x66, 0xc3, 0x00, 0x00, 0x00, 0x00},
		{0xc0, 0x60, 0x60, 0x30, 0x18, 0x3c, 0x66, 0x66, 0xc3, 0x00, 0x00, 0x00, 0x00},
		{0x00, 0x00, 0xff, 0x60, 0x30, 0x18, 0x0c, 0x06, 0xff, 0x00, 0x00, 0x00, 0x00},
		{0x00, 0x00, 0x0f, 0x18, 0x18, 0x18, 0x38, 0xf0, 0x38, 0x18, 0x18, 0x18, 0x0f},
		{0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18},
		{0x00, 0x00, 0xf0, 0x18, 0x18, 0x18, 0x1c, 0x0f, 0x1c, 0x18, 0x18, 0x18, 0xf0},
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x8f, 0xf1, 0x60, 0x00, 0x00, 0x00}
	};

	COpenGL::COpenGL()
	{
		m_Version = "GLDemo1.0";
		m_fC = 0.5f; // do not change this value !!!
		m_fDelta = 0.002f * m_fC;
		m_bDrawNothing = TRUE;
		m_hGLContext = NULL;

		m_bLButtonDown = FALSE;
		m_bRButtonDown = FALSE;

		m_nFontOffset = 0;
		m_nTimerSpeed = 200;
		m_fDY = -3;
		m_fAngleX = 0;
		m_fAngleY = 45;
		m_fAngleZ = 10;

		m_pDS = NULL;
		m_fDV = 3;
		m_nD = 30; // for legend
		m_bDraw = true;
	}

	bool COpenGL::InitOpenGL(HWND hWnd)
	{
		if (!::IsWindow(hWnd))
			return false;

		m_hWnd = hWnd;
		m_hDC = ::GetDC(m_hWnd);

		if (!SetWindowPixelFormat())
			return false;
		if (!CreateViewGLContext())
			return false;

		glClearDepth(1.0);
		glEnable(GL_DEPTH_TEST);
		RasterFont();

		return true;
	}

	bool COpenGL::SetWindowPixelFormat()
	{
		PIXELFORMATDESCRIPTOR pfd;

		pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);	// Size of this pfd
		pfd.nVersion = 1;							// Version number : must be 1
		pfd.dwFlags = PFD_DRAW_TO_WINDOW |			// Support window
			PFD_SUPPORT_OPENGL |			// Support OpenGL
			PFD_DOUBLEBUFFER |			// Double buffered
			PFD_STEREO_DONTCARE;			// Support either monoscopic or stereoscopic
		pfd.iPixelType = PFD_TYPE_RGBA;				// RGBA type
		pfd.cColorBits = 32;						// Specifies the number of color bitplanes in each color buffer
		pfd.cRedBits = 8;							// Specifies the number of red bitplanes in each RGBA color buffer
		pfd.cRedShift = 16;							// Specifies the shift count for red bitplanes in each RGBA color buffer
		pfd.cGreenBits = 8;							// Specifies the number of green bitplanes in each RGBA color buffer
		pfd.cGreenShift = 8;						// Specifies the shift count for green bitplanes in each RGBA color buffer
		pfd.cBlueBits = 8;							// Specifies the number of blue bitplanes in each RGBA color buffer
		pfd.cBlueShift = 0;							// Specifies the shift count for blue bitplanes in each RGBA color buffer
		pfd.cAlphaBits = 0;							// Specifies the number of alpha bitplanes in each RGBA color buffer. Alpha bitplanes are not supported
		pfd.cAlphaShift = 0;						// Specifies the shift count for alpha bitplanes in each RGBA color buffer. Alpha bitplanes are not supported
		pfd.cAccumBits = 64;						// Specifies the total number of bitplanes in the accumulation buffer
		pfd.cAccumRedBits = 16;						// Specifies the number of red bitplanes in the accumulation buffer
		pfd.cAccumGreenBits = 16;					// Specifies the number of green bitplanes in the accumulation buffer
		pfd.cAccumBlueBits = 16;					// Specifies the number of blue bitplanes in the accumulation buffer
		pfd.cAccumAlphaBits = 0;					// Specifies the number of alpha bitplanes in the accumulation buffer
		pfd.cDepthBits = 32;						// Specifies the depth of the depth (z-axis) buffer
		pfd.cStencilBits = 8;						// Specifies the depth of the stencil buffer
		pfd.cAuxBuffers = 0;						// Specifies the number of auxiliary buffers. Auxiliary buffers are not supported
		pfd.iLayerType = PFD_MAIN_PLANE;			// Ignored. Earlier implementations of OpenGL used this member, but it is no longer used
		pfd.bReserved = 0;							// Specifies the number of overlay and underlay planes
		pfd.dwLayerMask = 0;						// Ignored. Earlier implementations of OpenGL used this member, but it is no longer used
		pfd.dwVisibleMask = 0;						// Specifies the transparent color or index of an underlay plane
		pfd.dwDamageMask = 0;						// Ignored. Earlier implementations of OpenGL used this member, but it is no longer used

		int m_GLPixelIndex = ChoosePixelFormat(m_hDC, &pfd);// Attempts to match an appropriate pixel format supported by a device context to a given pixel format specification
		if (m_GLPixelIndex == 0)								// Choose default
		{
			m_GLPixelIndex = 1;
			if (DescribePixelFormat(m_hDC, m_GLPixelIndex,	// Obtains information about the pixel format identified by iPixelFormat of the device associated with hdc
				sizeof(PIXELFORMATDESCRIPTOR), &pfd) == 0)
				return FALSE;
		}
		if (!SetPixelFormat(m_hDC, m_GLPixelIndex, &pfd))	//Sets the pixel format of the specified device context to the format specified by the iPixelFormat index
			return false;

		return true;
	}

	bool COpenGL::CreateViewGLContext()
	{
		m_hGLContext = wglCreateContext(m_hDC); // Create an OpenGL rendering context
		if (!m_hGLContext)
			return false;
		if (!wglMakeCurrent(m_hDC, m_hGLContext)) // Set the current rendering context
			return false;

		return true;
	}

	void COpenGL::DestroyOpenGL()
	{
		if (wglGetCurrentContext())
			wglMakeCurrent(NULL, NULL);

		if (m_hGLContext)
		{
			wglDeleteContext(m_hGLContext);
			m_hGLContext = NULL;
		}

		::ReleaseDC(m_hWnd, m_hDC);
	}

	void COpenGL::OpenGLSize(int cx, int cy)
	{
		// Set OpenGL perspective, viewport and mode
		glViewport(0, 0, cx, cy);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(45, (cy == 0) ? 1.0 : cx / (double)cy, 1, 15.0);
		glMatrixMode(GL_MODELVIEW);
	}

	void COpenGL::RasterFont()
	{
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		m_nFontOffset = glGenLists(128);
		for (GLuint i = 32; i < 127; i++)
		{
			glNewList(i + m_nFontOffset, GL_COMPILE);
			glBitmap(8, 13, 0.0f, 2.0f, 10.0f, 0.0f, m_RasterFont[i - 32]);
			glEndList();
		}
	}

	void COpenGL::PrintString(const char* str)
	{
		glPushAttrib(GL_LIST_BIT);
		glListBase(m_nFontOffset);
		glCallLists(strlen(str), GL_UNSIGNED_BYTE, (GLubyte*)str);
		glPopAttrib();
	}

	void COpenGL::SetOpenGLTimer(int n)
	{
		if (n >= RX && n <= RXYZ)
		{
			if (!::SetTimer(m_hWnd, n, m_nTimerSpeed, NULL))
			{
				::MessageBox(m_hWnd, "Not enough timers available for this window.",
					"OpenGL ...", MB_ICONEXCLAMATION | MB_OK);
				return;
			}
		}
	}

	void COpenGL::KillOpenGLTimer(int n)
	{
		if (n >= RX && n <= RXYZ)
			::KillTimer(m_hWnd, n);
	}

	void COpenGL::OpenGLDrawBanner()
	{
		m_fAngleX += 10.2f;
		m_fAngleY += 10.2f;
		m_fAngleZ += 10.2f;
		if (m_fAngleX > 360)	m_fAngleX = 0;
		if (m_fAngleY > 360)	m_fAngleY = 0;
		if (m_fAngleZ > 360)	m_fAngleZ = 0;

		glTranslated(0, 0, -3.0);
		glRotatef(m_fAngleX, 1.0, 0.0, 0.0);
		glRotatef(m_fAngleY, 0.0, 1.0, 0.0);
		glRotatef(m_fAngleZ, 0.0, 0.0, 1.0);
		glScalef(1, 1, 1);

		glBegin(GL_QUAD_STRIP);
		glColor3f(1.0f, 0.0f, 1.0f);
		glVertex3f(-0.5f, 0.5f, 0.5f);

		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(-0.5f, -0.5f, 0.5f);

		glColor3f(1.0f, 1.0f, 1.0f);
		glVertex3f(0.5f, 0.5f, 0.5f);

		glColor3f(1.0f, 1.0f, 0.0f);
		glVertex3f(0.5f, -0.5f, 0.5f);

		glColor3f(0.0f, 1.0f, 1.0f);
		glVertex3f(0.5f, 0.5f, -0.5f);

		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(0.5f, -0.5f, -0.5f);

		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(-0.5f, 0.5f, -0.5f);

		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(-0.5f, -0.5f, -0.5f);

		glColor3f(1.0f, 0.0f, 1.0f);
		glVertex3f(-0.5f, 0.5f, 0.5f);

		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(-0.5f, -0.5f, 0.5f);

		glEnd();

		glBegin(GL_QUADS);
		glColor3f(1.0f, 0.0f, 1.0f);
		glVertex3f(-0.5f, 0.5f, 0.5f);

		glColor3f(1.0f, 1.0f, 1.0f);
		glVertex3f(0.5f, 0.5f, 0.5f);

		glColor3f(0.0f, 1.0f, 1.0f);
		glVertex3f(0.5f, 0.5f, -0.5f);

		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(-0.5f, 0.5f, -0.5f);
		glEnd();

		glBegin(GL_QUADS);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(-0.5f, -0.5f, 0.5f);

		glColor3f(1.0f, 1.0f, 0.0f);
		glVertex3f(0.5f, -0.5f, 0.5f);

		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(0.5f, -0.5f, -0.5f);

		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(-0.5f, -0.5f, -0.5f);
		glEnd();

		glRotatef(-2, 1.0, 0.0, 0.0);
		glRotatef(-2, 0.0, 1.0, 0.0);
		glRotatef(-2, 0.0, 0.0, 1.0);
		glColor3ub(128, 128, 0);

		GLUquadricObj* q = gluNewQuadric();
		gluQuadricDrawStyle(q, GLU_LINE);
		gluSphere(q, 1.0, 16, 16);
		gluDeleteQuadric(q);
	}

	void COpenGL::GDIDrawBanner()
	{
		SetTextColor(m_hDC, RGB(0, 0, 0));
		SetBkMode(m_hDC, TRANSPARENT);
		RECT rc;
		::GetClientRect(m_hWnd, &rc);
		DrawText(m_hDC, "Hello world !", -1, &rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}

	void COpenGL::OpenGLRendering()
	{
		if (!m_bDraw)
			return;

		m_bDraw = false;
		// begin OpenGL call
		wglMakeCurrent(m_hDC, m_hGLContext);

		if (m_pDS == NULL)
			glClearColor(140.0f / 255, 195.0f / 255, 245.0f / 155, 1.0f);
		else
			glClearColor(m_pDS->m_BackCr.r, m_pDS->m_BackCr.g, m_pDS->m_BackCr.b, 1.0f);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glPushMatrix();

		if (m_pDS == NULL)
			OpenGLDrawBanner();
		else
		{
			OpenGLDrawMap();
		}

		glPopMatrix();
		glFinish();
		SwapBuffers(wglGetCurrentDC());

		// begin GDI call
		if (m_pDS == NULL)
			GDIDrawBanner();
		else
			GDIDrawMap();

		m_bDraw = true;
	}

	void COpenGL::OpenGLTimer(CRotateType type)
	{
		if (!m_bDraw)
			return;

		switch (type)
		{
		case RX:
			m_pDS->m_xRotat += m_fDV;
			break;
		case RY:
			m_pDS->m_yRotat += m_fDV;
			break;
		case RZ:
			m_pDS->m_zRotat += m_fDV;
			break;
		case RXY:
			m_pDS->m_yRotat += m_fDV;
			m_pDS->m_xRotat += (m_fDV - 1);
			break;
		case RXZ:
			m_pDS->m_zRotat += m_fDV;
			m_pDS->m_xRotat += (m_fDV - 1);
			break;
		case RYZ:
			m_pDS->m_zRotat += m_fDV;
			m_pDS->m_yRotat += (m_fDV - 1);
			break;
		case RXYZ:
			m_pDS->m_zRotat += m_fDV;
			m_pDS->m_yRotat += (m_fDV - 1);
			m_pDS->m_xRotat += (m_fDV - 2);
			break;
		}
		::InvalidateRect(m_hWnd, NULL, FALSE);
	}

	void COpenGL::LButtonDown(POINT point)
	{
		m_bLButtonDown = TRUE;
		m_LDownPos = point;
	}

	void COpenGL::MouseMove(UINT nFlags, POINT point)
	{
		if (m_pDS)
		{
			if (m_bLButtonDown)
			{
				RECT rect;
				::GetClientRect(m_hWnd, &rect);
				if (nFlags & MK_SHIFT)
				{
					if (!m_pDS->m_bLegend) return;
					m_pDS->m_xLgdOs += point.x - m_LDownPos.x;
					m_pDS->m_yLgdOs -= point.y - m_LDownPos.y;
				}
				else if (m_pDS)
				{
					m_nWidth = rect.right - rect.left;
					m_nHeight = rect.bottom - rect.top;
					switch (m_pDS->m_Move)
					{
					case MOVE:
						m_pDS->m_fDx -= 1.0f * (point.x - m_LDownPos.x) / m_nWidth;
						m_pDS->m_fDy += 1.0f * (point.y - m_LDownPos.y) / m_nHeight;

						break;

					case RANDROTAT:
						if (m_bLButtonDown)
						{
							m_pDS->m_xRotat -= (float)(m_LDownPos.y - point.y) / m_fDV;
							m_pDS->m_zRotat -= (float)(m_LDownPos.x - point.x) / m_fDV;
						}

						break;

					case CENTERROTAT:
						m_pDS->m_xRotat -= (float)(m_LDownPos.y - point.y) / m_fDV;
						m_pDS->m_yRotat += (float)(m_LDownPos.x - point.x) / m_fDV;

						break;
					}
				}
				m_LDownPos = point;
				::InvalidateRect(m_hWnd, NULL, FALSE);
			}
		}
	}

	void COpenGL::ColorLevel(float level)
	{
		if (m_pDS->m_fCrThreshold > level)
			glColor3f(m_pDS->m_BackCr.r, m_pDS->m_BackCr.g, m_pDS->m_BackCr.b);
		else if (m_pDS->m_bAutoCr)
		{
			for (int i = 0; i < m_pDS->m_nCrLevel; i++)
			{
				if (level >= (-m_fC + i * 2 * m_fC / m_pDS->m_nCrLevel) &&
					level <= (-m_fC + (i + 1) * 2 * m_fC / m_pDS->m_nCrLevel))
				{
					glColor3f(m_pDS->m_MinCr.r + i*(m_pDS->m_MaxCr.r - m_pDS->m_MinCr.r) / (m_pDS->m_nCrLevel - 1),
						m_pDS->m_MinCr.g + i*(m_pDS->m_MaxCr.g - m_pDS->m_MinCr.g) / (m_pDS->m_nCrLevel - 1),
						m_pDS->m_MinCr.b + i*(m_pDS->m_MaxCr.b - m_pDS->m_MinCr.b) / (m_pDS->m_nCrLevel - 1));
					return;
				}
			}
		}
		else
		{
			for (int i = 0; i < m_pDS->m_nUserCrNum; i++)
			{
				if (level >= (-m_fC + i * 2 * m_fC / m_pDS->m_nUserCrNum) &&
					level <= (-m_fC + (i + 1) * 2 * m_fC / m_pDS->m_nUserCrNum))
				{
					glColor3f(GetRValue(m_pDS->m_UserCr.GetAt(i)) / 255.f,
						GetGValue(m_pDS->m_UserCr.GetAt(i)) / 255.f,
						GetBValue(m_pDS->m_UserCr.GetAt(i)) / 255.f);
					return;
				}
			}
		}
	}

	void COpenGL::DrawBorder()
	{
		glPushMatrix();

		//glTranslatef(m_dBottomCenter.x + m_fC, m_dBottomCenter.y + m_fC, m_dBottomCenter.z + m_fC);
		glTranslatef(m_fC, m_fC, m_fC);

		glColor3f(m_pDS->m_BorderCr.r, m_pDS->m_BorderCr.g, m_pDS->m_BorderCr.b);
		DrawBox();
		glBegin(GL_LINE_STRIP);
		glVertex3f(-m_fC, -m_fC, -m_fC);
		glVertex3f(-m_fC, m_fC, -m_fC);
		glVertex3f(m_fC, m_fC, -m_fC);
		glVertex3f(m_fC, -m_fC, -m_fC);
		glVertex3f(-m_fC, -m_fC, -m_fC);
		glEnd();

		glPopMatrix();
	}

	void COpenGL::DrawAxis()
	{
		glPushMatrix();

		//glTranslatef(m_dBottomCenter.x + m_fC, m_dBottomCenter.y + m_fC, m_dBottomCenter.z + m_fC);
		glTranslatef(m_fC, m_fC, m_fC);

		glColor3f(m_pDS->m_BorderCr.r, m_pDS->m_BorderCr.g, m_pDS->m_BorderCr.b);
		if (m_pDS->m_MapType != FLAT)
			Draw3DLine(-m_fC, -m_fC, m_fC, -m_fC, -m_fC, 6.8f * m_fC / 5);		// Z axis
		Draw3DLine(-m_fC, m_fC, -m_fC, -m_fC, 6.5f * m_fC / 5, -m_fC);			// Y axis 
		Draw3DLine(m_fC, -m_fC, -m_fC, 6.2f * m_fC / 5, -m_fC, -m_fC);			// X axis

		if (m_pDS->m_MapType != FLAT)
		{
			glRasterPos3f(-m_fC, -m_fC, 7 * m_fC / 5);
			PrintString("Z");
		}
		glRasterPos3f(-m_fC, 6.6f * m_fC / 5, -m_fC);
		PrintString("Y");
		glRasterPos3f(6.3f * m_fC / 5, -m_fC, -m_fC);
		PrintString("X");

		glPopMatrix();
	}

	void COpenGL::DrawLegend()
	{
		glPopMatrix();
		glPushMatrix();
		glTranslated(0.0, 0.0, m_pDS->m_zTrans);

		RECT rt;
		::GetClientRect(m_hWnd, &rt);
		gluOrtho2D((float)(rt.left + (rt.right - rt.left) / 20.),
			(float)(rt.right + (rt.right - rt.left) / 20.),
			(float)rt.top, (float)rt.bottom);

		Legend(rt);
	}

	void COpenGL::DrawCylinder()
	{
		float vx = m_dTopCenter.x - m_dBottomCenter.x;
		float vy = m_dTopCenter.y - m_dBottomCenter.y;
		float vz = m_dTopCenter.z - m_dBottomCenter.z;


		//handle the degenerate case of z1 == z2 with an approximation
		if (vz == 0)			vz = .00000001;

		float v = sqrt(vx*vx + vy*vy + vz*vz);
		float ax = 57.2957795*acos(vz / v);
		if (vz < 0.0)
			ax = -ax;
		float rx = -vy*vz;
		float ry = vx*vz;

		double cylHeight = sqrt(
			(m_dTopCenter.x - m_dBottomCenter.x)*(m_dTopCenter.x - m_dBottomCenter.x) +
			(m_dTopCenter.y - m_dBottomCenter.y)*(m_dTopCenter.y - m_dBottomCenter.y) +
			(m_dTopCenter.z - m_dBottomCenter.z)*(m_dTopCenter.z - m_dBottomCenter.z)
		);


		// *******************
		// start object setup

		GLUquadricObj* q = gluNewQuadric();

		if (m_pDS->m_MapType == GRID)
		{
			gluQuadricDrawStyle(q, GL_LINE);
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		else if (m_pDS->m_MapType == SURFACE)
		{
			gluQuadricDrawStyle(q, GL_QUADS);
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
		else
			gluQuadricDrawStyle(q, GL_LINE);


		// body
		glPushMatrix();
		glColor3f(200, 0, 0);
		glTranslatef(m_dBottomCenter.x, m_dBottomCenter.y, m_dBottomCenter.z);
		glRotatef(ax, rx, ry, 0.0);
		gluCylinder(q, m_dBottomRadius, m_dBottomRadius, cylHeight, m_nSlices, m_nStacks);
		glPopMatrix();

		// bottom cap
		glPushMatrix();
		glTranslatef(m_dBottomCenter.x, m_dBottomCenter.y, m_dBottomCenter.z);
		glRotatef(ax, rx, ry, 0.0);
		gluDisk(q, 0.0, m_dBottomRadius, m_nSlices, m_nStacks);
		glPopMatrix();

		//top cap
		glPushMatrix();
		glTranslatef(m_dTopCenter.x, m_dTopCenter.y, m_dTopCenter.z);
		glRotatef(ax, rx, ry, 0.0);
		gluDisk(q, 0.0, m_dBottomRadius, m_nSlices, m_nStacks);
		glPopMatrix();

		gluDeleteQuadric(q);
	}

	void COpenGL::DrawGeomLine()
	{
		glPushMatrix();
		Draw3DLine(	m_ptTestPtCtr.x, m_ptTestPtCtr.y, m_ptTestPtCtr.z, 
			m_ptFoundPtCtr.x, m_ptFoundPtCtr.y, m_ptFoundPtCtr.z
		);
		glPopMatrix();
	}

	void COpenGL::DrawSphere()
	{
		GLUquadricObj* q = gluNewQuadric();

		gluQuadricDrawStyle(q, GL_QUADS);

		glPushMatrix();
		glColor3f(0, 255, 255);
		//glTranslatef(m_ptTestPtCtr.x- m_dBottomCenter.x, m_ptTestPtCtr.y- m_dBottomCenter.y, m_ptTestPtCtr.z- m_dBottomCenter.z);
		glTranslatef(m_ptTestPtCtr.x, m_ptTestPtCtr.y, m_ptTestPtCtr.z);
		gluSphere(q, m_dSphRadius, 32, 32);
		glPopMatrix();

		gluDeleteQuadric(q);
	}

	void COpenGL::SetCylinderParams(Point3D dBottomCenter, Point3D dTopCenter, double dBottomRadius, int nSlices, int nStacks)
	{
		m_dBottomCenter = dBottomCenter;
		m_dTopCenter = dTopCenter;
		m_dBottomRadius = dBottomRadius;
		m_nSlices = nSlices;
		m_nStacks = nStacks;
	}

	void COpenGL::SetTestPointParams(Point3D dSphereCenter, double dSphereRadius)
	{
		m_ptTestPtCtr = dSphereCenter;
		m_dSphRadius = dSphereRadius;
	}

	void COpenGL::SetEndPointParams(Point3D dSphereCenter, double dSphereRadius)
	{
		m_ptFoundPtCtr = dSphereCenter;
		m_dSphRadius = dSphereRadius;
	}

	bool COpenGL::LoadMarkerData(const char* FileName)
	{
		FILE* fp;
		if ((fp = fopen(FileName, "r")) == NULL)
			return	 false;

		char ch[100];
		int i = 0, j = 0;
		int n;
		int flag;
		float x;
		float y;

		fgets(ch, 100, fp);
		for (; ;)
		{
			n = fscanf(fp, "%f%f%d%s\n", &x, &y, &flag, ch);
			if (x < m_pDS->m_fXmin || x > m_pDS->m_fXmax ||
				y < m_pDS->m_fYmin || y > m_pDS->m_fYmax)
			{
				MessageBox(NULL, "The values of markers are out of ranges", "Warning ...", MB_OK);
				fclose(fp);
				return false;
			}
			if (n != 4) break;
			i++;
		}

		if (i > 0) m_pDS->m_Marker.SetSize(0);
		else
		{
			fclose(fp);
			return false;
		}

		m_pDS->m_Marker.SetSize(i);
		fseek(fp, 0L, SEEK_SET);
		fgets(ch, 100, fp);
		for (j = 0; j < i; j++)
		{
			fscanf(fp, "%f%f%d%s\n", &x, &y, &flag, ch);
			CMarker marker;
			m_pDS->m_Marker[j].x = x;
			m_pDS->m_Marker[j].y = y;
			m_pDS->m_Marker[j].Hight = 2 * m_fC;
			m_pDS->m_Marker[j].Flag = flag;
			m_pDS->m_Marker[j].Name = ch;
		}
		fclose(fp);

		for (j = 0; j < i; j++)
		{
			m_pDS->m_Marker[j].x = (m_pDS->m_Marker[j].x - m_pDS->m_fXmin) /
				(m_pDS->m_fXmax - m_pDS->m_fXmin) - m_fC;
			m_pDS->m_Marker[j].y = (m_pDS->m_Marker[j].y - m_pDS->m_fYmin) /
				(m_pDS->m_fYmax - m_pDS->m_fYmin) - m_fC;
		}

		m_pDS->m_bMark = 1;

		return true;
	}
}