#if !defined(__OPENGL3D_H__)
#define		 __OPENGL3D_H__

#include "OpenGL.h"

namespace OpenGLui
{
	struct C3DSet : public CDataSet
	{
		CXYZW	m_XYZ;
		// add more properties here for 3D mapping

		C3DSet()
		{
			m_XYZ.x = NULL;
			m_XYZ.y = NULL;
			m_XYZ.z = NULL;
			m_XYZ.w = NULL;
		};

		~C3DSet()
		{
			if (m_XYZ.x)	delete[]m_XYZ.x;
			if (m_XYZ.y)	delete[]m_XYZ.y;
			if (m_XYZ.z)	delete[]m_XYZ.z;
			if (m_XYZ.w)	delete[]m_XYZ.w;
		};
	};

	typedef CClassArray<C3DSet, C3DSet&> C3DSetArray;

	class COpenGL3D : public COpenGL
	{
	public:
		COpenGL3D();
		~COpenGL3D() { ; }

		virtual void OpenGLDrawMap();
		virtual void GDIDrawMap();
		virtual void DrawBox();
		virtual void Legend(RECT& rt);
		virtual void OpenMaps(unsigned int);
		virtual void SaveMaps(unsigned int);

		void DrawBase();
		void DrawSide();
		void DrawFlat();
		void DrawSurface();
		void DrawGrid();
		void DrawMarker();

		void Load3DData(FILE* fp, char type);
		void Load3dArray(float* pXgrid, float* pYgrid, float* pArray, int row, int col);

		C3DSetArray	m_DS;
		C3DSet*		m_p3D;

		void Set3Dpters();

	private:
		void LoadSurferBinaryData(FILE* fp);
		void LoadSurferTextData(FILE* fp);
		void LoadSurferData(FILE* fp, char type);
		void Load3DMultipleMapsData(FILE* fp, char type);
		void Init3DDataSet(int col, int row, int group, int n);
		void Normalisation(int type, int n);
	};
}
#endif
