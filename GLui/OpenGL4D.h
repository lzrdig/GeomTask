#if !defined(__OPENGL4D_H__)
#define		 __OPENGL4D_H__

#include "OpenGL.h"

namespace OpenGLui
{
	enum C4DCut
	{
		NoCutting,
		TopFrontRightCorner,
		TopBackRightCorner,
		TopFrontLeftCorner,
		TopBackLeftCorner,
		BottomFrontRightCorner,
		BottomBackRightCorner,
		BottomFrontLeftCorner,
		BottomBackLeftCorner,
		RightCutFromTopToBottom,
		LeftCutFromTopToBottom,
		FrontCutFromTopToBottom,
		BackCutFromTopToBottom,
		CutFromMiddleToTop,
		CutFromMiddleToBottom,
		CutFromOutsideToInside,
		CutFromInsideToOutSide,
		xTopFrontRightCorner,
		xTopBackRightCorner,
		xTopFrontLeftCorner,
		xTopBackLeftCorner,
		xBottomFrontRightCorner,
		xBottomBackRightCorner,
		xBottomFrontLeftCorner,
		xBottomBackLeftCorner
	};

	struct C4DSet : public CDataSet
	{
		CXYZW		m_XYZW;
		CLinkType	m_CutingLink;

		// 4D cutting special
		int   m_xBackForward;
		int   m_yBackForward;
		int   m_zBackForward;
		int   m_CutCorner;
		int   m_KeepCorner;
		int   m_Parallel;

		float m_xCutting;
		float m_yCutting;
		float m_zCutting;

		int   xSE;
		int   ySE;
		int   zSE;

		int   Cut4DType;
		int   OldCutting;

		C4DSet()
		{
			m_XYZW.x = NULL;
			m_XYZW.y = NULL;
			m_XYZW.z = NULL;
			m_XYZW.w = NULL;
		};

		~C4DSet()
		{
			if (m_XYZW.x)	delete[]m_XYZW.x;
			if (m_XYZW.y)	delete[]m_XYZW.y;
			if (m_XYZW.z)	delete[]m_XYZW.z;
			if (m_XYZW.w)	delete[]m_XYZW.w;
		}
	};

	typedef CClassArray<C4DSet, C4DSet&> C4DSetArray;

	class COpenGL4D : public COpenGL
	{
	public:
		COpenGL4D();
		~COpenGL4D() {}

		virtual void OpenGLDrawMap();
		virtual void GDIDrawMap();
		virtual void DrawBox();
		virtual void Legend(RECT& rt);
		//void DrawMarker();
		void DrawBlock();
		void DrawNoProperty4D() {}
		void DrawProperty4D() {}
		virtual void OpenMaps(unsigned int);
		virtual void SaveMaps(unsigned int);

		void Load4DData(FILE* fp, char type);

		void Init4DDataSet(int col, int row, int high, int group, int n);
		void Normalisation(int type, int n);


		C4DSetArray m_DS;
		C4DSet*		m_p4D;

	protected:
		void BlockNoCutting(int, int, int);
		void BlockTopFrontRightCorner(int, int, int);
		void BlockTopBackRightCorner(int, int, int);
		void BlockTopFrontLeftCorner(int, int, int);
		void BlockTopBackLeftCorner(int, int, int);
		void BlockBottomFrontRightCorner(int, int, int);
		void BlockBottomBackRightCorner(int, int, int);
		void BlockBottomFrontLeftCorner(int, int, int);
		void BlockBottomBackLeftCorner(int, int, int);
		void BlockRightCutFromTopToBottom(int, int, int);
		void BlockLeftCutFromTopToBottom(int, int, int);
		void BlockFrontCutFromTopToBottom(int, int, int);
		void BlockBackCutFromTopToBottom(int, int, int);
		void BlockCutFromMiddleToTop(int, int, int);
		void BlockCutFromMiddleToBottom(int, int, int);
		void BlockCutFromOutsideToInside(int, int, int);
		void BlockCutFromInsideToOutSide(int, int, int);
		void BlockxTopFrontRightCorner(int, int, int);
		void BlockxTopBackRightCorner(int, int, int);
		void BlockxTopFrontLeftCorner(int, int, int);
		void BlockxTopBackLeftCorner(int, int, int);
		void BlockxBottomFrontRightCorner(int, int, int);
		void BlockxBottomBackRightCorner(int, int, int);
		void BlockxBottomFrontLeftCorner(int, int, int);
		void BlockxBottomBackLeftCorner(int, int, int);
	};
}
#endif
