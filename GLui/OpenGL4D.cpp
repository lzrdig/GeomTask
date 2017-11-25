#include "stdafx.h"
#include "OpenGL4D.h"

#define delta 0.002f*m_fC
#define pD m_p4D->m_XYZW

namespace OpenGLui
{
	COpenGL4D::COpenGL4D()
	{
		m_p4D		= NULL;
		m_DataGroup	= G4D;
	}

	void COpenGL4D::OpenGLDrawMap()
	{
		glTranslated(m_p4D->m_xTrans, m_p4D->m_yTrans, m_p4D->m_zTrans);
		glRotatef(m_p4D->m_xRotat, 1.0, 0.0, 0.0);
		glRotatef(m_p4D->m_yRotat, 0.0, 1.0, 0.0);
		glRotatef(m_p4D->m_zRotat, 0.0, 0.0, 1.0);
		if(m_p4D->m_xRotat > 360)	m_p4D->m_xRotat -= 360;
		if(m_p4D->m_xRotat < -360)	m_p4D->m_xRotat += 360;
		if(m_p4D->m_yRotat > 360)	m_p4D->m_yRotat -= 360;
		if(m_p4D->m_yRotat < -360)	m_p4D->m_yRotat += 360;
		if(m_p4D->m_zRotat > 360)	m_p4D->m_zRotat -= 360;
		if(m_p4D->m_zRotat < -360)	m_p4D->m_zRotat += 360;
		glScalef(m_p4D->m_xScale, m_p4D->m_yScale, m_p4D->m_zScale);

		switch(m_p4D->m_Move)
		{
			case MOVE:
			case RANDROTAT:
				glOrtho(-m_fC + m_p4D->m_fDx, m_fC + m_p4D->m_fDx, 
						-m_fC + m_p4D->m_fDy, m_fC + m_p4D->m_fDy, 1., -1.);
				break;
			case CENTERROTAT:
				break;	//Centre rotation: do not call glOrtho
		}

		if(m_p4D->m_bAxes)		DrawAxis();
		if(m_p4D->m_bBorder)	DrawBorder();
		//if(m_p4D->m_bMark)		DrawMarker();
		switch(m_p4D->m_MapType)
		{
			case BLOCK:
				DrawBlock();
				break;
			case NOPROPERTY4D:
				DrawNoProperty4D();
				break;
			case PROPERTY4D:
				DrawProperty4D();
				break;
		}
		if(m_p4D->m_bLegend)	DrawLegend();  // Must keep to draw legend the last
	}

	void COpenGL4D::GDIDrawMap()
	{

	}

	void COpenGL4D::DrawBox()
	{
		Draw3DLine(-m_fC, -m_fC, -m_fC, -m_fC, -m_fC, m_fC);
		Draw3DLine(-m_fC, m_fC, -m_fC, -m_fC, m_fC,   m_fC);
		Draw3DLine(m_fC, m_fC, -m_fC, m_fC, m_fC,     m_fC);
		Draw3DLine(m_fC, -m_fC, -m_fC, m_fC, -m_fC,   m_fC);

		glBegin(GL_LINE_STRIP);
			glVertex3f(-m_fC, -m_fC, m_fC);
			glVertex3f(-m_fC, m_fC,  m_fC);
			glVertex3f(m_fC, m_fC,   m_fC);
			glVertex3f(m_fC, -m_fC,  m_fC);
			glVertex3f(-m_fC, -m_fC, m_fC);
		glEnd();
	}

	void COpenGL4D::Legend(RECT& rt)
	{
		char Tstr[12];
		float oldMin = m_p4D->m_fWmin;
		int i =0;

		m_p4D->m_fWmin = m_p4D->m_fWmin + (m_p4D->m_fCrThreshold + 0.5f) *
								(m_p4D->m_fWmax - m_p4D->m_fWmin);
		if (m_p4D->m_fWmin < 0.000001 && m_p4D->m_fWmin > -0.000001) m_p4D->m_fWmin = 0;
		if(m_p4D->m_bAutoCr)
		{
			for(i=0; i<m_p4D->m_nCrLevel; i++)
			{
				glColor3f(m_p4D->m_MinCr.r + i * (m_p4D->m_MaxCr.r - 
						  m_p4D->m_MinCr.r) / (m_p4D->m_nCrLevel - 1),
						  m_p4D->m_MinCr.g + i * (m_p4D->m_MaxCr.g - 
						  m_p4D->m_MinCr.g) / (m_p4D->m_nCrLevel - 1),
						  m_p4D->m_MinCr.b + i * (m_p4D->m_MaxCr.b - 
						  m_p4D->m_MinCr.b) / (m_p4D->m_nCrLevel - 1));

				glBegin(GL_QUADS);
					glVertex3i(rt.right-rt.left + m_p4D->m_xLgdOs, 
							  (rt.bottom - rt.top - m_nD * m_p4D->m_nCrLevel) / 2 + 
							  i * m_nD + m_p4D->m_yLgdOs, 0);
					glVertex3i(rt.right-rt.left + m_p4D->m_xLgdOs, 
							  (rt.bottom - rt.top - m_nD * m_p4D->m_nCrLevel) / 2 + 
							  (i + 1) * m_nD + m_p4D->m_yLgdOs, 0);
					glVertex3i(rt.right-rt.left + m_p4D->m_xLgdOs + 2 * m_nD, 
							  (rt.bottom - rt.top - m_nD * m_p4D->m_nCrLevel) / 2 + 
							  (i + 1) * m_nD + m_p4D->m_yLgdOs, 0);
					glVertex3i(rt.right-rt.left + m_p4D->m_xLgdOs + 2 * m_nD, 
							  (rt.bottom - rt.top - m_nD * m_p4D->m_nCrLevel) / 2 + 
							  i * m_nD + m_p4D->m_yLgdOs, 0);
				glEnd();
			}
			glColor3f(m_p4D->m_BorderCr.r, m_p4D->m_BorderCr.g, m_p4D->m_BorderCr.b);
			glBegin(GL_LINE_LOOP);
				glVertex3i(rt.right-rt.left + m_p4D->m_xLgdOs - 1, 
						  (rt.bottom - rt.top - m_nD * m_p4D->m_nCrLevel) / 2 - 
						  1 + m_p4D->m_yLgdOs, 0);
				glVertex3i(rt.right-rt.left + m_p4D->m_xLgdOs - 1, 
						  (rt.bottom - rt.top - m_nD * m_p4D->m_nCrLevel) / 2 + 
						  i * m_nD + 1 + m_p4D->m_yLgdOs, 0);
				glVertex3i(rt.right-rt.left + m_p4D->m_xLgdOs + 2 * m_nD + 1, 
						  (rt.bottom - rt.top - m_nD * m_p4D->m_nCrLevel) / 2 + 
						  i * m_nD + 1 + m_p4D->m_yLgdOs, 0);
				glVertex3i(rt.right-rt.left + m_p4D->m_xLgdOs + 2 * m_nD + 1, 
						  (rt.bottom - rt.top - m_nD * m_p4D->m_nCrLevel) / 2 - 
						  1 + m_p4D->m_yLgdOs, 0);
			glEnd();
			for(i=0; i<=m_p4D->m_nCrLevel; i++)
			{
				glRasterPos2i(rt.right-rt.left + m_p4D->m_xLgdOs + 5 * m_nD / 2,
							 (rt.bottom-rt.top - m_nD * m_p4D->m_nCrLevel) / 2 +
							 i * m_nD - m_nD / 4 + m_p4D->m_yLgdOs);
				sprintf(Tstr, "%-10.2f", m_p4D->m_fWmin + 
						i * (m_p4D->m_fWmax - m_p4D->m_fWmin) / m_p4D->m_nCrLevel);
				PrintString(Tstr);
			}
		}
		else
		{
			for(i=0; i<m_p4D->m_nUserCrNum; i++)
			{
				glColor3f(GetRValue(m_p4D->m_UserCr.GetAt(i)) / 255.f, 
						  GetGValue(m_p4D->m_UserCr.GetAt(i)) / 255.f,
						  GetBValue(m_p4D->m_UserCr.GetAt(i)) / 255.f);

				glBegin(GL_QUADS);
					glVertex3i(rt.right-rt.left + m_p4D->m_xLgdOs, 
							  (rt.bottom - rt.top - m_nD * m_p4D->m_nUserCrNum) / 2 + 
							  i * m_nD + m_p4D->m_yLgdOs, 0);
					glVertex3i(rt.right-rt.left + m_p4D->m_xLgdOs, 
							  (rt.bottom - rt.top - m_nD * m_p4D->m_nUserCrNum) / 2 + 
							  (i + 1) * m_nD + m_p4D->m_yLgdOs, 0);
					glVertex3i(rt.right-rt.left + m_p4D->m_xLgdOs + 2 * m_nD, 
							  (rt.bottom - rt.top - m_nD * m_p4D->m_nUserCrNum) / 2 + 
							  (i + 1) * m_nD + m_p4D->m_yLgdOs, 0);
					glVertex3i(rt.right-rt.left + m_p4D->m_xLgdOs + 2 * m_nD, 
							  (rt.bottom - rt.top - m_nD * m_p4D->m_nUserCrNum) / 2 + 
							  i * m_nD + m_p4D->m_yLgdOs, 0);
				glEnd();
			}
			glColor3f(m_p4D->m_BorderCr.r, m_p4D->m_BorderCr.g, m_p4D->m_BorderCr.b);
			glBegin(GL_LINE_LOOP);
				glVertex3i(rt.right-rt.left + m_p4D->m_xLgdOs - 1, 
						  (rt.bottom - rt.top - m_nD * m_p4D->m_nUserCrNum) / 2 + 
						  m_p4D->m_yLgdOs, 0);
				glVertex3i(rt.right-rt.left + m_p4D->m_xLgdOs - 1, 
						  (rt.bottom - rt.top - m_nD * m_p4D->m_nUserCrNum) / 2 + 
						  i * m_nD + m_p4D->m_yLgdOs, 0);
				glVertex3i(rt.right-rt.left + m_p4D->m_xLgdOs + 2 * m_nD + 1, 
						  (rt.bottom - rt.top - m_nD * m_p4D->m_nUserCrNum) / 2 + 
						  i * m_nD + m_p4D->m_yLgdOs, 0);
				glVertex3i(rt.right-rt.left + m_p4D->m_xLgdOs + 2 * m_nD + 1, 
						  (rt.bottom - rt.top - m_nD * m_p4D->m_nUserCrNum) / 2 + 
						  m_p4D->m_yLgdOs, 0);
			glEnd();
			for(i=0; i<=m_p4D->m_nUserCrNum; i++)
			{
				glRasterPos2i(rt.right-rt.left + m_p4D->m_xLgdOs + 5 * m_nD / 2,
							 (rt.bottom-rt.top - m_nD * m_p4D->m_nUserCrNum) / 2 +
							 i * m_nD - m_nD / 4 + m_p4D->m_yLgdOs);
				sprintf(Tstr, "%-10.2f", m_p4D->m_fWmin + 
						i * (m_p4D->m_fWmax - m_p4D->m_fWmin) / m_p4D->m_nUserCrNum);
				PrintString(Tstr);
			}
		}
		m_p4D->m_fWmin = oldMin;
	}

	void COpenGL4D::Init4DDataSet(int col, int row, int high, int group, int n)
	{
		int k = 0;

		for(k=0; k<n; k++)
		{
			m_DS[k].nDataGroup = group;

			m_DS[k].nX		= col;
			m_DS[k].nY		= row;
			m_DS[k].nZ		= high;

			m_DS[k].m_XYZW.x = new float[col];
			m_DS[k].m_XYZW.y = new float[row];
			if (group == G4D)
			{
				m_DS[k].m_XYZW.z  = new float[high];
				m_DS[k].m_MapType = BLOCK;
			}
			else if (group == G4DNOPROP)
			{
				m_DS[k].m_XYZW.z  = new float[col*row*high];
				m_DS[k].m_MapType = NOPROPERTY4D;
			}
			else //if (group == G4DHASPROP)
			{
				m_DS[k].m_XYZW.z  = new float[col*row*high];
				m_DS[k].m_MapType = PROPERTY4D;
			}
			m_DS[k].m_XYZW.w  = new float[col*row*high];

			m_DS[k].m_fXmin = 1.e+30f;
			m_DS[k].m_fXmax = -1.e+30f;
			m_DS[k].m_fYmin = 1.e+30f;
			m_DS[k].m_fYmax = -1.e+30f;
			m_DS[k].m_fZmin = 1.e+30f;
			m_DS[k].m_fZmax = -1.e+30f;
			m_DS[k].m_fWmin = 1.e+30f;
			m_DS[k].m_fWmax = -1.e+30f;

			m_DS[k].m_nCrLevel   = 10;
			m_DS[k].m_nUserCrNum = 10;
			m_DS[k].m_bAutoCr    = 1;

			m_DS[k].m_bAxes      = 1;
			m_DS[k].m_bLegend	 = 0;
			m_DS[k].m_bBorder    = 1;

			m_DS[k].m_Rotate	 = RZ;
			m_DS[k].m_Move		 = MOVE;
			m_DS[k].m_fDx		 = 0.0f;
			m_DS[k].m_fDy		 = 0.0f;
			m_DS[k].m_xLgdOs	 = 50;
			m_DS[k].m_yLgdOs	 = 0;

			m_DS[k].m_xRotat	 = -70;
			m_DS[k].m_yRotat	 = 0;
			m_DS[k].m_zRotat	 = 0;

			m_DS[k].m_xTrans	 = 0;
			m_DS[k].m_yTrans	 = 0;
			m_DS[k].m_zTrans	 = -4;

			m_DS[k].m_xScale	 = 1;
			m_DS[k].m_yScale	 = 1;
			m_DS[k].m_zScale	 = 1;

			m_DS[k].m_Link		 = NoLink;
			m_DS[k].m_CutingLink = NoLink;

			m_DS[k].m_xBackForward = 0;
			m_DS[k].m_yBackForward = 0;
			m_DS[k].m_zBackForward = 0;
			m_DS[k].m_CutCorner	   = 1;
			m_DS[k].m_KeepCorner   = 0;
			m_DS[k].m_Parallel	   = 0;

			m_DS[k].m_xCutting   = 0;
			m_DS[k].m_yCutting	 = 0;
			m_DS[k].m_zCutting   = 0;

			m_DS[k].xSE			 = 1;
			m_DS[k].ySE			 = 1;
			m_DS[k].zSE			 = 1;

			m_DS[k].Cut4DType	 = NoCutting;
			m_DS[k].OldCutting	 = NoCutting;

			m_DS[k].m_UserCr.SetSize(20);
			m_DS[k].m_UserCr[0]  = RGB(0, 0, 0);
			m_DS[k].m_UserCr[1]  = RGB(255, 255, 0);
			m_DS[k].m_UserCr[2]  = RGB(128, 128, 0);
			m_DS[k].m_UserCr[3]  = RGB(255, 0, 0);
			m_DS[k].m_UserCr[4]  = RGB(128, 0, 0);
			m_DS[k].m_UserCr[5]  = RGB(255, 0, 255);
			m_DS[k].m_UserCr[6]  = RGB(128, 0, 128);
			m_DS[k].m_UserCr[7]  = RGB(0, 0, 255);
			m_DS[k].m_UserCr[8]  = RGB(0, 0, 128);
			m_DS[k].m_UserCr[9]  = RGB(0, 255, 255);
			m_DS[k].m_UserCr[10] = RGB(0, 128, 128);
			m_DS[k].m_UserCr[11] = RGB(0, 255, 0);
			m_DS[k].m_UserCr[12] = RGB(0, 128, 0);
			m_DS[k].m_UserCr[13] = RGB(192, 192, 192);
			m_DS[k].m_UserCr[14] = RGB(128, 128, 128);
			m_DS[k].m_UserCr[15] = RGB(255, 255, 255);
			m_DS[k].m_UserCr[16] = RGB(255, 251, 240);
			m_DS[k].m_UserCr[17] = RGB(192, 220, 192);
			m_DS[k].m_UserCr[18] = RGB(166, 202, 240);
			m_DS[k].m_UserCr[19] = RGB(160, 160, 164);
	
			m_DS[k].m_BackCr.r   = 0;
			m_DS[k].m_BackCr.g   = 0;
			m_DS[k].m_BackCr.b   = 128 / 255.f;

			m_DS[k].m_MinCr.r    = 0;
			m_DS[k].m_MinCr.g    = 0;
			m_DS[k].m_MinCr.b    = 1;

			m_DS[k].m_MaxCr.r    = 1;
			m_DS[k].m_MaxCr.g    = 0;
			m_DS[k].m_MaxCr.b	 = 0;

			m_DS[k].m_BorderCr.r = 1;
			m_DS[k].m_BorderCr.g = 1;
			m_DS[k].m_BorderCr.b = 1.0f - 128 / 255.f;

			m_DS[k].m_MarkerCr.r = 1;
			m_DS[k].m_MarkerCr.g = 1;
			m_DS[k].m_MarkerCr.b = 1.0f - 128 / 255.f;

			m_DS[k].m_fCrThreshold = -m_fC;
		}
	}

	void COpenGL4D::Normalisation(int group, int n)
	{
		int  m = 0, k = 0, j = 0;

		for(m=0; m<n; m++)
		{
			for(k=0; k<m_DS[m].nX; k++)
			{
				if(m_DS[m].m_XYZW.x[k] < m_DS[m].m_fXmin)
					m_DS[m].m_fXmin = m_DS[m].m_XYZW.x[k];
				if(m_DS[m].m_XYZW.x[k] > m_DS[m].m_fXmax)
					m_DS[m].m_fXmax = m_DS[m].m_XYZW.x[k];
			}
			for(k=0; k<m_DS[m].nY; k++)
			{
				if(m_DS[m].m_XYZW.y[k] < m_DS[m].m_fYmin)
					m_DS[m].m_fYmin = m_DS[m].m_XYZW.y[k];
				if(m_DS[m].m_XYZW.y[k] > m_DS[m].m_fYmax)
					m_DS[m].m_fYmax = m_DS[m].m_XYZW.y[k];
			}
			if (group == G4D)
			{
				for(k=0; k<m_DS[m].nZ; k++)
				{
					if(m_DS[m].m_XYZW.z[k] < m_DS[m].m_fZmin)
						m_DS[m].m_fZmin = m_DS[m].m_XYZW.z[k];
					if(m_DS[m].m_XYZW.z[k] > m_DS[m].m_fZmax)
						m_DS[m].m_fZmax = m_DS[m].m_XYZW.z[k];
				}
				j = m_DS[m].nX*m_DS[m].nY*m_DS[m].nZ;
				for(k=0; k<j; k++)
				{
					if(m_DS[m].m_XYZW.w[k] < m_DS[m].m_fWmin)
						m_DS[m].m_fWmin = m_DS[m].m_XYZW.w[k];
					if(m_DS[m].m_XYZW.w[k] > m_DS[m].m_fWmax)
						m_DS[m].m_fWmax = m_DS[m].m_XYZW.w[k];
				}
			}
			else
			{
				j = m_DS[m].nX*m_DS[m].nY*m_DS[m].nZ;
				for(k=0; k<j; k++)
				{
					if(m_DS[m].m_XYZW.z[k] < m_DS[m].m_fZmin)
						m_DS[m].m_fZmin = m_DS[m].m_XYZW.z[k];
					if(m_DS[m].m_XYZW.z[k] > m_DS[m].m_fZmax)
						m_DS[m].m_fZmax = m_DS[m].m_XYZW.z[k];
					if(m_DS[m].m_XYZW.w[k] < m_DS[m].m_fWmin)
						m_DS[m].m_fWmin = m_DS[m].m_XYZW.w[k];
					if(m_DS[m].m_XYZW.w[k] > m_DS[m].m_fWmax)
						m_DS[m].m_fWmax = m_DS[m].m_XYZW.w[k];
				}
			}
		}

		for(m=0; m<n; m++)
		{
			for(k=0; k<m_DS[m].nX; k++)
				m_DS[m].m_XYZW.x[k] = (m_DS[m].m_XYZW.x[k] - m_DS[m].m_fXmin) / 
									  (m_DS[m].m_fXmax - m_DS[m].m_fXmin) - m_fC;
			for(k=0; k<m_DS[m].nY; k++)
				m_DS[m].m_XYZW.y[k] = (m_DS[m].m_XYZW.y[k] - m_DS[m].m_fYmin) / 
									  (m_DS[m].m_fYmax - m_DS[m].m_fYmin) - m_fC;
			if (group == G4D)
			{
				for(k=0; k<m_DS[m].nZ; k++)
					m_DS[m].m_XYZW.z[k] = (m_DS[m].m_XYZW.z[k] - m_DS[m].m_fZmin) / 
										  (m_DS[m].m_fZmax - m_DS[m].m_fZmin) - m_fC;
				j = m_DS[m].nX * m_DS[m].nY*m_DS[m].nZ;
				for(k=0; k<j; k++)
					m_DS[m].m_XYZW.w[k] = (m_DS[m].m_XYZW.w[k] - m_DS[m].m_fWmin) / 
										  (m_DS[m].m_fWmax - m_DS[m].m_fWmin) - m_fC;
			}
			else
			{
				j = m_DS[m].nX * m_DS[m].nY*m_DS[m].nZ;
				for(k=0; k<j; k++)
				{
					m_DS[m].m_XYZW.z[k] = (m_DS[m].m_XYZW.z[k] - m_DS[m].m_fZmin) / 
										  (m_DS[m].m_fZmax - m_DS[m].m_fZmin) - m_fC;
					m_DS[m].m_XYZW.w[k] = (m_DS[m].m_XYZW.w[k] - m_DS[m].m_fWmin) / 
										  (m_DS[m].m_fWmax - m_DS[m].m_fWmin) - m_fC;
				}
			}
		}
	}

	void COpenGL4D::Load4DData(FILE* fp, char type)
	{
		char ch[32];
		int m, n, col, row, high;
		fread(&n, sizeof(int), 1, fp); // Number of maps
		int  g = 0, k = 0, j = 0, i = 0;


		m_DS.RemoveAll(); 
		m_p4D = NULL;
		m_pDS = NULL;
		m_DS.SetSize(n);

		for(k=0; k<n; k++)
		{
			fread(ch, sizeof(char), 32, fp);
			j = strlen(ch);
			for(i = 0; i < j; i++)
			{
				if (ch[i] == '\r' || ch[i] == '\n')
				{
					ch[i] = '\0';
					break;
				}
			}
			m_DS[k].m_MapName = ch;
		}

		fread(&col, sizeof(int), 1, fp);
		fread(&row, sizeof(int), 1, fp);
		fread(&high, sizeof(int), 1, fp);

		if (type =='E')
			m_DataGroup = G4D;
		else if (type == 'F')
			m_DataGroup = G4DNOPROP;
		else // type == 'G'
			m_DataGroup = G4DHASPROP;

		Init4DDataSet(col, row, high, m_DataGroup, n);

		if (type == 'F')
			m = n + 2;
		else
			m = n + 3;
		float* tValue = new float[m];
		for(g=0; g<high; g++)
		{
			for(k=0; k<row; k++)
			{
				for(j=0; j<col; j++)
				{
					i = (g * row + k )* col + j;
					fread(tValue, sizeof(float), m, fp);
					for(int h=0; h<n; h++)
					{
						if(k == 0 && g == 0)
							m_DS[h].m_XYZW.x[j] = tValue[0];
						if(j == 0 && g == 0)
							m_DS[h].m_XYZW.y[k] = tValue[1];
						if (type =='E')
						{
							if(j == 0 && k == 0)
								m_DS[h].m_XYZW.z[g] = tValue[2];
							m_DS[h].m_XYZW.w[i] = tValue[3+h];
						}
						else if(type =='F')
						{
							m_DS[h].m_XYZW.z[i] = tValue[2];
							m_DS[h].m_XYZW.w[i] = g + 1.0f;
						}
						else //if(type =='G')
						{
							m_DS[h].m_XYZW.z[i] = tValue[2];
							m_DS[h].m_XYZW.w[i] = tValue[3+h];
						}
					}
				}
			}
		}
		delete []tValue;
		Normalisation(m_DataGroup, n);
		m_p4D = &m_DS[0];
		m_pDS = m_p4D;
	}

	void COpenGL4D::OpenMaps(unsigned int hHandle)
	{
		DWORD  len;
		int	   m, n;
		int i = 0;

		HANDLE handle = (HANDLE)hHandle;
		::ReadFile(handle, &m, sizeof(int), &len, NULL);
		m_DS.SetSize(m);
		for(int k=0; k<m; k++)
		{
			char str[32];
			::ReadFile(handle, str, 32, &len, NULL);
			m_DS[k].m_MapName = str;
			::ReadFile(handle, &m_DS[k].nDataGroup, sizeof(int), &len, NULL);
			::ReadFile(handle, &m_DS[k].nX, sizeof(int), &len, NULL);
			::ReadFile(handle, &m_DS[k].nY, sizeof(int), &len, NULL);
			::ReadFile(handle, &m_DS[k].nZ, sizeof(int), &len, NULL);
			m_DS[k].m_XYZW.x = new float[m_DS[k].nX];
			m_DS[k].m_XYZW.y = new float[m_DS[k].nY];
			::ReadFile(handle, m_DS[k].m_XYZW.x, sizeof(float) * m_DS[k].nX, &len, NULL);
			::ReadFile(handle, m_DS[k].m_XYZW.y, sizeof(float) * m_DS[k].nY, &len, NULL);
			if (m_DS[k].nDataGroup == G4D)
			{
				m_DS[k].m_XYZW.z = new float[m_DS[k].nZ];
				::ReadFile(handle, m_DS[k].m_XYZW.z, sizeof(float) * m_DS[k].nZ, &len, NULL);
			}
			else
			{
				m_DS[k].m_XYZW.z = new float[m_DS[k].nX  * m_DS[k].nY * m_DS[k].nZ];
				::ReadFile(handle, m_DS[k].m_XYZW.z, sizeof(float) * m_DS[k].nX  * m_DS[k].nY * m_DS[k].nZ, &len, NULL);
			}
			m_DS[k].m_XYZW.w = new float[m_DS[k].nX  * m_DS[k].nY * m_DS[k].nZ];
			::ReadFile(handle, m_DS[k].m_XYZW.w, sizeof(float) * m_DS[k].nX  * m_DS[k].nY * m_DS[k].nZ, &len, NULL);

			::ReadFile(handle, &m_DS[k].m_fXmin, sizeof(float), &len, NULL);
			::ReadFile(handle, &m_DS[k].m_fXmax, sizeof(float), &len, NULL);
			::ReadFile(handle, &m_DS[k].m_fYmin, sizeof(float), &len, NULL);
			::ReadFile(handle, &m_DS[k].m_fYmax, sizeof(float), &len, NULL);
			::ReadFile(handle, &m_DS[k].m_fZmin, sizeof(float), &len, NULL);
			::ReadFile(handle, &m_DS[k].m_fZmax, sizeof(float), &len, NULL);
			::ReadFile(handle, &m_DS[k].m_fWmin, sizeof(float), &len, NULL);
			::ReadFile(handle, &m_DS[k].m_fWmax, sizeof(float), &len, NULL);

			::ReadFile(handle, &m_DS[k].m_nCrLevel, sizeof(int), &len, NULL);
			::ReadFile(handle, &m_DS[k].m_nUserCrNum, sizeof(int), &len, NULL);
			::ReadFile(handle, &m_DS[k].m_bAutoCr, sizeof(bool), &len, NULL);
			::ReadFile(handle, &m_DS[k].m_MapType, sizeof(CMapType), &len, NULL);

			::ReadFile(handle, &m_DS[k].m_bAxes, sizeof(int), &len, NULL);
			::ReadFile(handle, &m_DS[k].m_bLegend, sizeof(int), &len, NULL);
			::ReadFile(handle, &m_DS[k].m_bBorder, sizeof(int), &len, NULL);
			//::ReadFile(handle, &m_DS[k].m_bMark, sizeof(int), &len, NULL);

			//::ReadFile(handle, &m_DS[k].m_bLable, sizeof(int), &len, NULL);
			//::ReadFile(handle, &m_DS[k].m_nMarkIndex, sizeof(int), &len, NULL);
			//::ReadFile(handle, &m_DS[k].m_bMarkLine, sizeof(int), &len, NULL);

			::ReadFile(handle, &m_DS[k].m_Rotate, sizeof(CRotateType), &len, NULL);
			::ReadFile(handle, &m_DS[k].m_Move, sizeof(CMoveType), &len, NULL);
			::ReadFile(handle, &m_DS[k].m_fDx, sizeof(float), &len, NULL);
			::ReadFile(handle, &m_DS[k].m_fDy, sizeof(float), &len, NULL);
			::ReadFile(handle, &m_DS[k].m_xLgdOs, sizeof(int), &len, NULL);
			::ReadFile(handle, &m_DS[k].m_yLgdOs, sizeof(int), &len, NULL);

			::ReadFile(handle, &m_DS[k].m_xRotat, sizeof(float), &len, NULL);
			::ReadFile(handle, &m_DS[k].m_yRotat, sizeof(float), &len, NULL);
			::ReadFile(handle, &m_DS[k].m_zRotat, sizeof(float), &len, NULL);

			::ReadFile(handle, &m_DS[k].m_xTrans, sizeof(float), &len, NULL);
			::ReadFile(handle, &m_DS[k].m_yTrans, sizeof(float), &len, NULL);
			::ReadFile(handle, &m_DS[k].m_zTrans, sizeof(float), &len, NULL);

			::ReadFile(handle, &m_DS[k].m_xScale, sizeof(float), &len, NULL);
			::ReadFile(handle, &m_DS[k].m_yScale, sizeof(float), &len, NULL);
			::ReadFile(handle, &m_DS[k].m_zScale, sizeof(float), &len, NULL);

			::ReadFile(handle, &m_DS[k].m_Link, sizeof(CLinkType), &len, NULL);
			::ReadFile(handle, &m_DS[k].m_CutingLink, sizeof(CLinkType), &len, NULL);

			::ReadFile(handle, &m_DS[k].m_xBackForward, sizeof(int), &len, NULL);
			::ReadFile(handle, &m_DS[k].m_yBackForward, sizeof(int), &len, NULL);
			::ReadFile(handle, &m_DS[k].m_zBackForward, sizeof(int), &len, NULL);
			::ReadFile(handle, &m_DS[k].m_CutCorner, sizeof(int), &len, NULL);
			::ReadFile(handle, &m_DS[k].m_KeepCorner, sizeof(int), &len, NULL);
			::ReadFile(handle, &m_DS[k].m_Parallel, sizeof(int), &len, NULL);

			::ReadFile(handle, &m_DS[k].m_xCutting, sizeof(float), &len, NULL);
			::ReadFile(handle, &m_DS[k].m_yCutting, sizeof(float), &len, NULL);
			::ReadFile(handle, &m_DS[k].m_zCutting, sizeof(float), &len, NULL);

			::ReadFile(handle, &m_DS[k].xSE, sizeof(int), &len, NULL);
			::ReadFile(handle, &m_DS[k].ySE, sizeof(int), &len, NULL);
			::ReadFile(handle, &m_DS[k].zSE, sizeof(int), &len, NULL);

			::ReadFile(handle, &m_DS[k].Cut4DType, sizeof(int), &len, NULL);
			::ReadFile(handle, &m_DS[k].OldCutting, sizeof(int), &len, NULL);

			::ReadFile(handle, &n, sizeof(int), &len, NULL);
			m_DS[k].m_UserCr.SetSize(n);
			for(i = 0; i < n; i++)
				::ReadFile(handle, &m_DS[k].m_UserCr[i], sizeof(DWORD), &len, NULL);
	
			::ReadFile(handle, &m_DS[k].m_BackCr, sizeof(CFRGB), &len, NULL);
			::ReadFile(handle, &m_DS[k].m_MinCr, sizeof(CFRGB), &len, NULL);
			::ReadFile(handle, &m_DS[k].m_MaxCr, sizeof(CFRGB), &len, NULL);
			::ReadFile(handle, &m_DS[k].m_BorderCr, sizeof(CFRGB), &len, NULL);
			::ReadFile(handle, &m_DS[k].m_MarkerCr, sizeof(CFRGB), &len, NULL);

			::ReadFile(handle, &m_DS[k].m_fCrThreshold, sizeof(float), &len, NULL);

			/////////Marker structure
			//n = m_DS[k].m_Marker.GetSize();
			//::ReadFile(handle, &n, sizeof(int), &len, NULL);
			//for(i=0; i<n; i++)
			//{
			//	::ReadFile(handle, &m_DS[k].m_Marker[i].x, sizeof(float), &len, NULL);
			//	::ReadFile(handle, &m_DS[k].m_Marker[i].y, sizeof(float), &len, NULL);
			//	::ReadFile(handle, &m_DS[k].m_Marker[i].Hight, sizeof(float), &len, NULL);
			//	::ReadFile(handle, &m_DS[k].m_Marker[i].Flag, sizeof(int), &len, NULL);
			//	::ReadFile(handle, (char*)m_DS[k].m_Marker[i].Name, 12, &len, NULL);
			//}
		}
		m_p4D = &m_DS[0];
		m_pDS = m_p4D;
	}

	void COpenGL4D::SaveMaps(unsigned int hHandle)
	{
		int i = 0;

		int m = m_DS.GetSize();
		if(m < 1)   return;

		HANDLE handle = (HANDLE)hHandle;
		DWORD  len;
		::WriteFile(handle, m_Version, 12, &len, NULL);
		::WriteFile(handle, &m_DataGroup, sizeof(CDataGroup), &len, NULL);
		::WriteFile(handle, &m, sizeof(int), &len, NULL);
		for(int k=0; k<m; k++)
		{
			::WriteFile(handle, (char*)m_DS[k].m_MapName, 32, &len, NULL);
			::WriteFile(handle, &m_DS[k].nDataGroup, sizeof(int), &len, NULL);
			::WriteFile(handle, &m_DS[k].nX, sizeof(int), &len, NULL);
			::WriteFile(handle, &m_DS[k].nY, sizeof(int), &len, NULL);
			::WriteFile(handle, &m_DS[k].nZ, sizeof(int), &len, NULL);
			::WriteFile(handle, m_DS[k].m_XYZW.x, sizeof(float) * m_DS[k].nX, &len, NULL);
			::WriteFile(handle, m_DS[k].m_XYZW.y, sizeof(float) * m_DS[k].nY, &len, NULL);
			if (m_DS[k].nDataGroup == G4D)
				::WriteFile(handle, m_DS[k].m_XYZW.z, sizeof(float) * m_DS[k].nZ, &len, NULL);
			else
				::WriteFile(handle, m_DS[k].m_XYZW.z, sizeof(float) * m_DS[k].nX  * m_DS[k].nY * m_DS[k].nZ, &len, NULL);
			::WriteFile(handle, m_DS[k].m_XYZW.w, sizeof(float) * m_DS[k].nX  * m_DS[k].nY * m_DS[k].nZ, &len, NULL);

			::WriteFile(handle, &m_DS[k].m_fXmin, sizeof(float), &len, NULL);
			::WriteFile(handle, &m_DS[k].m_fXmax, sizeof(float), &len, NULL);
			::WriteFile(handle, &m_DS[k].m_fYmin, sizeof(float), &len, NULL);
			::WriteFile(handle, &m_DS[k].m_fYmax, sizeof(float), &len, NULL);
			::WriteFile(handle, &m_DS[k].m_fZmin, sizeof(float), &len, NULL);
			::WriteFile(handle, &m_DS[k].m_fZmax, sizeof(float), &len, NULL);
			::WriteFile(handle, &m_DS[k].m_fWmin, sizeof(float), &len, NULL);
			::WriteFile(handle, &m_DS[k].m_fWmax, sizeof(float), &len, NULL);

			::WriteFile(handle, &m_DS[k].m_nCrLevel, sizeof(int), &len, NULL);
			::WriteFile(handle, &m_DS[k].m_nUserCrNum, sizeof(int), &len, NULL);
			::WriteFile(handle, &m_DS[k].m_bAutoCr, sizeof(bool), &len, NULL);
			::WriteFile(handle, &m_DS[k].m_MapType, sizeof(CMapType), &len, NULL);

			::WriteFile(handle, &m_DS[k].m_bAxes, sizeof(int), &len, NULL);
			::WriteFile(handle, &m_DS[k].m_bLegend, sizeof(int), &len, NULL);
			::WriteFile(handle, &m_DS[k].m_bBorder, sizeof(int), &len, NULL);
			//::WriteFile(handle, &m_DS[k].m_bMark, sizeof(int), &len, NULL);

			//::WriteFile(handle, &m_DS[k].m_bLable, sizeof(int), &len, NULL);
			//::WriteFile(handle, &m_DS[k].m_nMarkIndex, sizeof(int), &len, NULL);
			//::WriteFile(handle, &m_DS[k].m_bMarkLine, sizeof(int), &len, NULL);

			::WriteFile(handle, &m_DS[k].m_Rotate, sizeof(CRotateType), &len, NULL);
			::WriteFile(handle, &m_DS[k].m_Move, sizeof(CMoveType), &len, NULL);
			::WriteFile(handle, &m_DS[k].m_fDx, sizeof(float), &len, NULL);
			::WriteFile(handle, &m_DS[k].m_fDy, sizeof(float), &len, NULL);
			::WriteFile(handle, &m_DS[k].m_xLgdOs, sizeof(int), &len, NULL);
			::WriteFile(handle, &m_DS[k].m_yLgdOs, sizeof(int), &len, NULL);

			::WriteFile(handle, &m_DS[k].m_xRotat, sizeof(float), &len, NULL);
			::WriteFile(handle, &m_DS[k].m_yRotat, sizeof(float), &len, NULL);
			::WriteFile(handle, &m_DS[k].m_zRotat, sizeof(float), &len, NULL);

			::WriteFile(handle, &m_DS[k].m_xTrans, sizeof(float), &len, NULL);
			::WriteFile(handle, &m_DS[k].m_yTrans, sizeof(float), &len, NULL);
			::WriteFile(handle, &m_DS[k].m_zTrans, sizeof(float), &len, NULL);

			::WriteFile(handle, &m_DS[k].m_xScale, sizeof(float), &len, NULL);
			::WriteFile(handle, &m_DS[k].m_yScale, sizeof(float), &len, NULL);
			::WriteFile(handle, &m_DS[k].m_zScale, sizeof(float), &len, NULL);

			::WriteFile(handle, &m_DS[k].m_Link, sizeof(CLinkType), &len, NULL);
			::WriteFile(handle, &m_DS[k].m_CutingLink, sizeof(CLinkType), &len, NULL);

			::WriteFile(handle, &m_DS[k].m_xBackForward, sizeof(int), &len, NULL);
			::WriteFile(handle, &m_DS[k].m_yBackForward, sizeof(int), &len, NULL);
			::WriteFile(handle, &m_DS[k].m_zBackForward, sizeof(int), &len, NULL);
			::WriteFile(handle, &m_DS[k].m_CutCorner, sizeof(int), &len, NULL);
			::WriteFile(handle, &m_DS[k].m_KeepCorner, sizeof(int), &len, NULL);
			::WriteFile(handle, &m_DS[k].m_Parallel, sizeof(int), &len, NULL);

			::WriteFile(handle, &m_DS[k].m_xCutting, sizeof(float), &len, NULL);
			::WriteFile(handle, &m_DS[k].m_yCutting, sizeof(float), &len, NULL);
			::WriteFile(handle, &m_DS[k].m_zCutting, sizeof(float), &len, NULL);

			::WriteFile(handle, &m_DS[k].xSE, sizeof(int), &len, NULL);
			::WriteFile(handle, &m_DS[k].ySE, sizeof(int), &len, NULL);
			::WriteFile(handle, &m_DS[k].zSE, sizeof(int), &len, NULL);

			::WriteFile(handle, &m_DS[k].Cut4DType, sizeof(int), &len, NULL);
			::WriteFile(handle, &m_DS[k].OldCutting, sizeof(int), &len, NULL);

			int n = m_DS[k].m_UserCr.GetSize();
			::WriteFile(handle, &n, sizeof(int), &len, NULL);
			for(i = 0; i < n; i++)
				::WriteFile(handle, &m_DS[k].m_UserCr[i], sizeof(DWORD), &len, NULL);
	
			::WriteFile(handle, &m_DS[k].m_BackCr, sizeof(CFRGB), &len, NULL);
			::WriteFile(handle, &m_DS[k].m_MinCr, sizeof(CFRGB), &len, NULL);
			::WriteFile(handle, &m_DS[k].m_MaxCr, sizeof(CFRGB), &len, NULL);
			::WriteFile(handle, &m_DS[k].m_BorderCr, sizeof(CFRGB), &len, NULL);
			::WriteFile(handle, &m_DS[k].m_MarkerCr, sizeof(CFRGB), &len, NULL);

			::WriteFile(handle, &m_DS[k].m_fCrThreshold, sizeof(float), &len, NULL);

			/////////Marker structure
			//n = m_DS[k].m_Marker.GetSize();
			//::WriteFile(handle, &n, sizeof(int), &len, NULL);
			//for(i=0; i<n; i++)
			//{
			//	::WriteFile(handle, &m_DS[k].m_Marker[i].x, sizeof(float), &len, NULL);
			//	::WriteFile(handle, &m_DS[k].m_Marker[i].y, sizeof(float), &len, NULL);
			//	::WriteFile(handle, &m_DS[k].m_Marker[i].Hight, sizeof(float), &len, NULL);
			//	::WriteFile(handle, &m_DS[k].m_Marker[i].Flag, sizeof(int), &len, NULL);
			//	::WriteFile(handle, (char*)m_DS[k].m_Marker[i].Name, 12, &len, NULL);
			//}
		}
	}

	void COpenGL4D::DrawBlock()
	{
		int ix = m_p4D->nX;
		int iy = m_p4D->nY;
		int iz = m_p4D->nZ;

		switch(m_p4D->Cut4DType)
		{
			case NoCutting:
				BlockNoCutting(ix, iy, iz);
				break;
			case TopFrontRightCorner:
				BlockTopFrontRightCorner(ix, iy, iz);
				break;
			case TopBackRightCorner:
				BlockTopBackRightCorner(ix, iy, iz);
				break;
			case TopFrontLeftCorner:
				BlockTopFrontLeftCorner(ix, iy, iz);
				break;
			case TopBackLeftCorner:
				BlockTopBackLeftCorner(ix, iy, iz);
				break;
			case BottomFrontRightCorner:
				BlockBottomFrontRightCorner(ix, iy, iz);
				break;
			case BottomBackRightCorner:
				BlockBottomBackRightCorner(ix, iy, iz);
				break;
			case BottomFrontLeftCorner:
				BlockBottomFrontLeftCorner(ix, iy, iz);
				break;
			case BottomBackLeftCorner:
				BlockBottomBackLeftCorner(ix, iy, iz);
				break;
			case RightCutFromTopToBottom:
				BlockRightCutFromTopToBottom(ix, iy, iz);
				break;
			case LeftCutFromTopToBottom:
				BlockLeftCutFromTopToBottom(ix, iy, iz);
				break;
			case FrontCutFromTopToBottom:
				BlockFrontCutFromTopToBottom(ix, iy, iz);
				break;
			case BackCutFromTopToBottom:
				BlockBackCutFromTopToBottom(ix, iy, iz);
				break;
			case CutFromMiddleToTop:
				BlockCutFromMiddleToTop(ix, iy, iz);
				break;
			case CutFromMiddleToBottom:
				BlockCutFromMiddleToBottom(ix, iy, iz);
				break;
			case CutFromOutsideToInside:
				BlockCutFromOutsideToInside(ix, iy, iz);
				break;
			case CutFromInsideToOutSide:
				BlockCutFromInsideToOutSide(ix, iy, iz);
				break;
			case xTopFrontRightCorner:
				BlockxTopFrontRightCorner(ix, iy, iz);
				break;
			case xTopBackRightCorner:
				BlockxTopBackRightCorner(ix, iy, iz);
				break;
			case xTopFrontLeftCorner:
				BlockxTopFrontLeftCorner(ix, iy, iz);
				break;
			case xTopBackLeftCorner:
				BlockxTopBackLeftCorner(ix, iy, iz);
				break;
			case xBottomFrontRightCorner:
				BlockxBottomFrontRightCorner(ix, iy, iz);
				break;
			case xBottomBackRightCorner:
				BlockxBottomBackRightCorner(ix, iy, iz);
				break;
			case xBottomFrontLeftCorner:
				BlockxBottomFrontLeftCorner(ix, iy, iz);
				break;
			case xBottomBackLeftCorner:
				BlockxBottomBackLeftCorner(ix, iy, iz);
				break;
		}
	}

	void COpenGL4D::BlockNoCutting(int ix, int iy, int iz)
	{
		int j = 0, i = 0;

		//     w    z   Y     y     X    x
		// int g = (k * row + j)* col + i; 
		// Bottom: z = 0;
		for(j=0; j<iy-1; j++)
			for(i=0; i<ix-1; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[j*ix+i]);
			glVertex3f(pD.x[i], pD.y[j], pD.z[0]);
			ColorLevel(pD.w[j*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[j], pD.z[0]);
			ColorLevel(pD.w[(j+1)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[j+1], pD.z[0]);
			ColorLevel(pD.w[(j+1)*ix+i]);
			glVertex3f(pD.x[i], pD.y[j+1], pD.z[0]);
			glEnd();
		}

		// Top: z=max
		int m = (iz - 1) * iy;
		for(j=0; j<iy-1; j++)
			for(i=0; i<ix-1; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[(m+j)*ix+i]);
			glVertex3f(pD.x[i], pD.y[j], pD.z[iz-1]);
			ColorLevel(pD.w[(m+j)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[j], pD.z[iz-1]);
			ColorLevel(pD.w[(m+j+1)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[j+1], pD.z[iz-1]);
			ColorLevel(pD.w[(m+j+1)*ix+i]);
			glVertex3f(pD.x[i], pD.y[j+1], pD.z[iz-1]);
			glEnd();
		}

		// Left: y=0
		m = iy*ix;
		for(j=0; j<iz-1; j++)
			for(i=0; i<ix-1; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[j*m+i]);
			glVertex3f(pD.x[i], pD.y[0], pD.z[j]);
			ColorLevel(pD.w[j*m+i+1]);
			glVertex3f(pD.x[i+1], pD.y[0], pD.z[j]);
			ColorLevel(pD.w[(j+1)*m+i+1]);
			glVertex3f(pD.x[i+1], pD.y[0], pD.z[j+1]);
			ColorLevel(pD.w[(j+1)*m+i]);
			glVertex3f(pD.x[i], pD.y[0], pD.z[j+1]);
			glEnd();
		}

		// Right: y=max
		for(j=0; j<iz-1; j++)
			for(i=0; i<ix-1; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[((j+1)*iy-1)*ix+i]);
			glVertex3f(pD.x[i], pD.y[iy-1], pD.z[j]);
			ColorLevel(pD.w[((j+1)*iy-1)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[iy-1], pD.z[j]);
			ColorLevel(pD.w[((j+2)*iy-1)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[iy-1], pD.z[j+1]);
			ColorLevel(pD.w[((j+2)*iy-1)*ix+i]);
			glVertex3f(pD.x[i], pD.y[iy-1], pD.z[j+1]);
			glEnd();
		}

		// front: x=max
		for(j=0; j<iz-1; j++)
			for(i=0; i<iy-1; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[(j*iy+i+1)*ix-1]);
			glVertex3f(pD.x[ix-1], pD.y[i], pD.z[j]);
			ColorLevel(pD.w[(j*iy+i+2)*ix-1]);
			glVertex3f(pD.x[ix-1], pD.y[i+1], pD.z[j]);
			ColorLevel(pD.w[((j+1)*iy+i+2)*ix-1]);
			glVertex3f(pD.x[ix-1], pD.y[i+1], pD.z[j+1]);
			ColorLevel(pD.w[((j+1)*iy+i+1)*ix-1]);
			glVertex3f(pD.x[ix-1], pD.y[i], pD.z[j+1]);
			glEnd();
		}

		// back: x=0
		for(j=0; j<iz-1; j++)
			for(i=0; i<iy-1; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[(j*iy+i)*ix]);
			glVertex3f(pD.x[0], pD.y[i], pD.z[j]);
			ColorLevel(pD.w[(j*iy+i+1)*ix]);
			glVertex3f(pD.x[0], pD.y[i+1], pD.z[j]);
			ColorLevel(pD.w[((j+1)*iy+i+1)*ix]);
			glVertex3f(pD.x[0], pD.y[i+1], pD.z[j+1]);
			ColorLevel(pD.w[((j+1)*iy+i)*ix]);
			glVertex3f(pD.x[0], pD.y[i], pD.z[j+1]);
			glEnd();
		}
	}

	void COpenGL4D::BlockTopFrontRightCorner(int ix, int iy, int iz)
	{
		int x = m_p4D->xSE;
		int y = m_p4D->ySE;
		int z = m_p4D->zSE;
		int j = 0, i = 0;

		// back: x==0
		for(j=0; j<iz-1; j++)
			for(i=0; i<iy-1; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[(j*iy+i)*ix]);
			glVertex3f(pD.x[0], pD.y[i], pD.z[j]);
			ColorLevel(pD.w[(j*iy+i+1)*ix]);
			glVertex3f(pD.x[0], pD.y[i+1], pD.z[j]);
			ColorLevel(pD.w[((j+1)*iy+i+1)*ix]);
			glVertex3f(pD.x[0], pD.y[i+1], pD.z[j+1]);
			ColorLevel(pD.w[((j+1)*iy+i)*ix]);
			glVertex3f(pD.x[0], pD.y[i], pD.z[j+1]);
			glEnd();
		}

		// left: y==0
		int m = iy*ix; 
		for(j=0; j<iz-1; j++)
			for(i=0; i<ix-1; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[j*m+i]);
			glVertex3f(pD.x[i], pD.y[0], pD.z[j]);
			ColorLevel(pD.w[j*m+i+1]);
			glVertex3f(pD.x[i+1], pD.y[0], pD.z[j]);
			ColorLevel(pD.w[(j+1)*m+i+1]);
			glVertex3f(pD.x[i+1], pD.y[0], pD.z[j+1]);
			ColorLevel(pD.w[(j+1)*m+i]);
			glVertex3f(pD.x[i], pD.y[0], pD.z[j+1]);
			glEnd();
		}

		// bottom: z = 0;
		for(j=0; j<iy-1; j++)
			for(i=0; i<ix-1; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[j*ix+i]);
			glVertex3f(pD.x[i], pD.y[j], pD.z[0]);
			ColorLevel(pD.w[j*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[j], pD.z[0]);
			ColorLevel(pD.w[(j+1)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[j+1], pD.z[0]);
			ColorLevel(pD.w[(j+1)*ix+i]);
			glVertex3f(pD.x[i], pD.y[j+1], pD.z[0]);
			glEnd();
		}

		// front left cutting: x==max
		for(j=0; j<iz-1; j++)
			for(i=0; i<y; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[(j*iy+i+1)*ix-1]);
			glVertex3f(pD.x[ix-1], pD.y[i], pD.z[j]);
			ColorLevel(pD.w[(j*iy+i+2)*ix-1]);
			glVertex3f(pD.x[ix-1], pD.y[i+1], pD.z[j]);
			ColorLevel(pD.w[((j+1)*iy+i+2)*ix-1]);
			glVertex3f(pD.x[ix-1], pD.y[i+1], pD.z[j+1]);
			ColorLevel(pD.w[((j+1)*iy+i+1)*ix-1]);
			glVertex3f(pD.x[ix-1], pD.y[i], pD.z[j+1]);
			glEnd();
		}

		// front right bottom cutting: x==max
		for(j=0; j<z; j++)
			for(i=y; i<iy-1; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[(j*iy+i+1)*ix-1]);
			glVertex3f(pD.x[ix-1], pD.y[i], pD.z[j]);
			ColorLevel(pD.w[(j*iy+i+2)*ix-1]);
			glVertex3f(pD.x[ix-1], pD.y[i+1], pD.z[j]);
			ColorLevel(pD.w[((j+1)*iy+i+2)*ix-1]);
			glVertex3f(pD.x[ix-1], pD.y[i+1], pD.z[j+1]);
			ColorLevel(pD.w[((j+1)*iy+i+1)*ix-1]);
			glVertex3f(pD.x[ix-1], pD.y[i], pD.z[j+1]);
			glEnd();
		}

		// right back cutting: y=max
		for(j=0; j<iz-1; j++)
			for(i=0; i<x; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[((j+1)*iy-1)*ix+i]);
			glVertex3f(pD.x[i], pD.y[iy-1], pD.z[j]);
			ColorLevel(pD.w[((j+1)*iy-1)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[iy-1], pD.z[j]);
			ColorLevel(pD.w[((j+2)*iy-1)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[iy-1], pD.z[j+1]);
			ColorLevel(pD.w[((j+2)*iy-1)*ix+i]);
			glVertex3f(pD.x[i], pD.y[iy-1], pD.z[j+1]);
			glEnd();
		}

		// right front bottom cutting: y=max
		for(j=0; j<z; j++)
			for(i=x; i<ix-1; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[((j+1)*iy-1)*ix+i]);
			glVertex3f(pD.x[i], pD.y[iy-1], pD.z[j]);
			ColorLevel(pD.w[((j+1)*iy-1)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[iy-1], pD.z[j]);
			ColorLevel(pD.w[((j+2)*iy-1)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[iy-1], pD.z[j+1]);
			ColorLevel(pD.w[((j+2)*iy-1)*ix+i]);
			glVertex3f(pD.x[i], pD.y[iy-1], pD.z[j+1]);
			glEnd();
		}

		// top back cutting: z=max
		m = (iz - 1) * iy;
		for(j=0; j<iy-1; j++)
			for(i=0; i<x; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[(m+j)*ix+i]);
			glVertex3f(pD.x[i], pD.y[j], pD.z[iz-1]);
			ColorLevel(pD.w[(m+j)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[j], pD.z[iz-1]);
			ColorLevel(pD.w[(m+j+1)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[j+1], pD.z[iz-1]);
			ColorLevel(pD.w[(m+j+1)*ix+i]);
			glVertex3f(pD.x[i], pD.y[j+1], pD.z[iz-1]);
			glEnd();
		}

		for(j=0; j<y; j++)
			for(i=x; i<ix-1; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[(m+j)*ix+i]);
			glVertex3f(pD.x[i], pD.y[j], pD.z[iz-1]);
			ColorLevel(pD.w[(m+j)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[j], pD.z[iz-1]);
			ColorLevel(pD.w[(m+j+1)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[j+1], pD.z[iz-1]);
			ColorLevel(pD.w[(m+j+1)*ix+i]);
			glVertex3f(pD.x[i], pD.y[j+1], pD.z[iz-1]);
			glEnd();
		}

		// cut yz face x = m_p4D->xSE
		for(j=z; j<iz-1; j++)
			for(i=y; i<iy-1; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[(j*iy+i)*ix+x]);
			glVertex3f(pD.x[x], pD.y[i], pD.z[j]);
			ColorLevel(pD.w[(j*iy+i+1)*ix+x]);
			glVertex3f(pD.x[x], pD.y[i+1], pD.z[j]);
			ColorLevel(pD.w[((j+1)*iy+i+1)*ix+x]);
			glVertex3f(pD.x[x], pD.y[i+1], pD.z[j+1]);
			ColorLevel(pD.w[((j+1)*iy+i)*ix+x]);
			glVertex3f(pD.x[x], pD.y[i], pD.z[j+1]);
			glEnd();
		}

		// cut xz face: y=m_p4D->ySE
		for(j=z; j<iz-1; j++)
			for(i=x; i<ix-1; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[(j*iy+y)*ix+i]);
			glVertex3f(pD.x[i], pD.y[y], pD.z[j]);
			ColorLevel(pD.w[(j*iy+y)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[y], pD.z[j]);
			ColorLevel(pD.w[((j+1)*iy+y)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[y], pD.z[j+1]);
			ColorLevel(pD.w[((j+1)*iy+y)*ix+i]);
			glVertex3f(pD.x[i], pD.y[y], pD.z[j+1]);
			glEnd();
		}
	
		// cut xy face z = m_p4D->zSE
		m = z * iy; 
		for(j=y; j<iy-1; j++)
			for(i=x; i<ix-1; i++)
		{
			glBegin(GL_QUADS);
			// int g = (k * row + j)* col + i; 
			ColorLevel(pD.w[(m+j)*ix+i]);
			glVertex3f(pD.x[i], pD.y[j], pD.z[z]);
			ColorLevel(pD.w[(m+j)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[j], pD.z[z]);
			ColorLevel(pD.w[(m+j+1)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[j+1], pD.z[z]);
			ColorLevel(pD.w[(m+j+1)*ix+i]);
			glVertex3f(pD.x[i], pD.y[j+1], pD.z[z]);
			glEnd();
		}

		// draw cut lines
		float xp = pD.x[x] + delta;
		float yp = pD.y[y] + delta;
		float zp = pD.z[z] + delta;

		glColor3f(1.0f - m_p4D->m_BackCr.r, 1.0f - m_p4D->m_BackCr.g, 1.0f - m_p4D->m_BackCr.b);
		//glLineWidth(2);
		Draw3DLine(xp, yp, zp, xp, yp, pD.z[iz-1]);
		Draw3DLine(pD.x[ix-1], yp, zp, pD.x[ix-1], yp, pD.z[iz-1]);
		Draw3DLine(xp, pD.y[iy-1], pD.z[iz-1], xp, pD.y[iy-1], zp);

		//glLineWidth(2);
		glBegin(GL_LINE_LOOP);
		glVertex3f(xp, yp, zp);
		glVertex3f(pD.x[ix-1], yp, zp);
		glVertex3f(pD.x[ix-1], pD.y[iy-1], zp);
		glVertex3f(xp, pD.y[iy-1], zp);
		glEnd();

		//glLineWidth(1);

		Draw3DLine(xp, yp, pD.z[iz-1], pD.x[ix-1], yp, pD.z[iz-1]);
		Draw3DLine(xp, yp, pD.z[iz-1], xp, pD.y[iy-1], pD.z[iz-1]);
	}

	void COpenGL4D::BlockTopBackRightCorner(int ix, int iy, int iz)
	{
		m_p4D->xSE = ix - m_p4D->xSE;
		int x = m_p4D->xSE-1;
		int y = m_p4D->ySE;
		int z = m_p4D->zSE;
		int j = 0, i = 0;

		// front: x==max
		for(j=0; j<iz-1; j++)
			for(i=0; i<iy-1; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[(j*iy+i+1)*ix-1]);
			glVertex3f(pD.x[ix-1], pD.y[i], pD.z[j]);
			ColorLevel(pD.w[(j*iy+i+2)*ix-1]);
			glVertex3f(pD.x[ix-1], pD.y[i+1], pD.z[j]);
			ColorLevel(pD.w[((j+1)*iy+i+2)*ix-1]);
			glVertex3f(pD.x[ix-1], pD.y[i+1], pD.z[j+1]);
			ColorLevel(pD.w[((j+1)*iy+i+1)*ix-1]);
			glVertex3f(pD.x[ix-1], pD.y[i], pD.z[j+1]);
			glEnd();
		}

		// left: y==0
		int m = iy*ix; 
		for(j=0; j<iz-1; j++)
			for(i=0; i<ix-1; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[j*m+i]);
			glVertex3f(pD.x[i], pD.y[0], pD.z[j]);
			ColorLevel(pD.w[j*m+i+1]);
			glVertex3f(pD.x[i+1], pD.y[0], pD.z[j]);
			ColorLevel(pD.w[(j+1)*m+i+1]);
			glVertex3f(pD.x[i+1], pD.y[0], pD.z[j+1]);
			ColorLevel(pD.w[(j+1)*m+i]);
			glVertex3f(pD.x[i], pD.y[0], pD.z[j+1]);
			glEnd();
		}

		// bottom: z = 0;
		for(j=0; j<iy-1; j++)
			for(i=0; i<ix-1; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[j*ix+i]);
			glVertex3f(pD.x[i], pD.y[j], pD.z[0]);
			ColorLevel(pD.w[j*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[j], pD.z[0]);
			ColorLevel(pD.w[(j+1)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[j+1], pD.z[0]);
			ColorLevel(pD.w[(j+1)*ix+i]);
			glVertex3f(pD.x[i], pD.y[j+1], pD.z[0]);
			glEnd();
		}

		// back left cutting: x==0
		for(j=0; j<iz-1; j++)
			for(i=0; i<y; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[(j*iy+i)*ix]);
			glVertex3f(pD.x[0], pD.y[i], pD.z[j]);
			ColorLevel(pD.w[(j*iy+i+1)*ix]);
			glVertex3f(pD.x[0], pD.y[i+1], pD.z[j]);
			ColorLevel(pD.w[((j+1)*iy+i+1)*ix]);
			glVertex3f(pD.x[0], pD.y[i+1], pD.z[j+1]);
			ColorLevel(pD.w[((j+1)*iy+i)*ix]);
			glVertex3f(pD.x[0], pD.y[i], pD.z[j+1]);
			glEnd();
		}

		// back right bottom cutting: x==0
		for(j=0; j<z; j++)
			for(i=y; i<iy-1; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[(j*iy+i)*ix]);
			glVertex3f(pD.x[0], pD.y[i], pD.z[j]);
			ColorLevel(pD.w[(j*iy+i+1)*ix]);
			glVertex3f(pD.x[0], pD.y[i+1], pD.z[j]);
			ColorLevel(pD.w[((j+1)*iy+i+1)*ix]);
			glVertex3f(pD.x[0], pD.y[i+1], pD.z[j+1]);
			ColorLevel(pD.w[((j+1)*iy+i)*ix]);
			glVertex3f(pD.x[0], pD.y[i], pD.z[j+1]);
			glEnd();
		}

		// right back cutting: y=max
		for(j=0; j<iz-1; j++)
			for(i=x; i<ix-1; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[((j+1)*iy-1)*ix+i]);
			glVertex3f(pD.x[i], pD.y[iy-1], pD.z[j]);
			ColorLevel(pD.w[((j+1)*iy-1)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[iy-1], pD.z[j]);
			ColorLevel(pD.w[((j+2)*iy-1)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[iy-1], pD.z[j+1]);
			ColorLevel(pD.w[((j+2)*iy-1)*ix+i]);
			glVertex3f(pD.x[i], pD.y[iy-1], pD.z[j+1]);
			glEnd();
		}

		// right front bottom cutting: y=max
		for(j=0; j<z; j++)
			for(i=0; i<x; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[((j+1)*iy-1)*ix+i]);
			glVertex3f(pD.x[i], pD.y[iy-1], pD.z[j]);
			ColorLevel(pD.w[((j+1)*iy-1)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[iy-1], pD.z[j]);
			ColorLevel(pD.w[((j+2)*iy-1)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[iy-1], pD.z[j+1]);
			ColorLevel(pD.w[((j+2)*iy-1)*ix+i]);
			glVertex3f(pD.x[i], pD.y[iy-1], pD.z[j+1]);
			glEnd();
		}

		// top back cutting: z=max
		m = (iz - 1) * iy;
		for(j=0; j<iy-1; j++)
			for(i=x; i<ix-1; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[(m+j)*ix+i]);
			glVertex3f(pD.x[i], pD.y[j], pD.z[iz-1]);
			ColorLevel(pD.w[(m+j)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[j], pD.z[iz-1]);
			ColorLevel(pD.w[(m+j+1)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[j+1], pD.z[iz-1]);
			ColorLevel(pD.w[(m+j+1)*ix+i]);
			glVertex3f(pD.x[i], pD.y[j+1], pD.z[iz-1]);
			glEnd();
		}

		for(j=0; j<y; j++)
			for(i=0; i<x; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[(m+j)*ix+i]);
			glVertex3f(pD.x[i], pD.y[j], pD.z[iz-1]);
			ColorLevel(pD.w[(m+j)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[j], pD.z[iz-1]);
			ColorLevel(pD.w[(m+j+1)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[j+1], pD.z[iz-1]);
			ColorLevel(pD.w[(m+j+1)*ix+i]);
			glVertex3f(pD.x[i], pD.y[j+1], pD.z[iz-1]);
			glEnd();
		}

		// cut yz face x = m_p4D->xSE
		for(j=z; j<iz-1; j++)
			for(i=y; i<iy-1; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[(j*iy+i)*ix+x]);
			glVertex3f(pD.x[x], pD.y[i], pD.z[j]);
			ColorLevel(pD.w[(j*iy+i+1)*ix+x]);
			glVertex3f(pD.x[x], pD.y[i+1], pD.z[j]);
			ColorLevel(pD.w[((j+1)*iy+i+1)*ix+x]);
			glVertex3f(pD.x[x], pD.y[i+1], pD.z[j+1]);
			ColorLevel(pD.w[((j+1)*iy+i)*ix+x]);
			glVertex3f(pD.x[x], pD.y[i], pD.z[j+1]);
			glEnd();
		}

		// cut xz face: y=m_p4D->ySE
		for(j=z; j<iz-1; j++)
			for(i=0; i<x; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[(j*iy+y)*ix+i]);
			glVertex3f(pD.x[i], pD.y[y], pD.z[j]);
			ColorLevel(pD.w[(j*iy+y)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[y], pD.z[j]);
			ColorLevel(pD.w[((j+1)*iy+y)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[y], pD.z[j+1]);
			ColorLevel(pD.w[((j+1)*iy+y)*ix+i]);
			glVertex3f(pD.x[i], pD.y[y], pD.z[j+1]);
			glEnd();
		}
	
		// cut xy face z = m_p4D->zSE
		m = z * iy; 
		for(j=y; j<iy-1; j++)
			for(i=0; i<x; i++)
		{
			glBegin(GL_QUADS);
			// int g = (k * row + j)* col + i; 
			ColorLevel(pD.w[(m+j)*ix+i]);
			glVertex3f(pD.x[i], pD.y[j], pD.z[z]);
			ColorLevel(pD.w[(m+j)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[j], pD.z[z]);
			ColorLevel(pD.w[(m+j+1)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[j+1], pD.z[z]);
			ColorLevel(pD.w[(m+j+1)*ix+i]);
			glVertex3f(pD.x[i], pD.y[j+1], pD.z[z]);
			glEnd();
		}

		// draw cut lines
		float xp = pD.x[x] - delta;
		float yp = pD.y[y] + delta;
		float zp = pD.z[z] + delta;

		glColor3f(1.0f - m_p4D->m_BackCr.r, 1.0f - m_p4D->m_BackCr.g, 1.0f - m_p4D->m_BackCr.b);
		Draw3DLine(xp, yp, zp, xp, yp, pD.z[iz-1]);
		Draw3DLine(pD.x[0], yp, zp, pD.x[0], yp, pD.z[iz-1]);
		Draw3DLine(xp, pD.y[iy-1], pD.z[iz-1], xp, pD.y[iy-1], zp);

		glBegin(GL_LINE_LOOP);
		glVertex3f(xp, yp, zp);
		glVertex3f(pD.x[0], yp, zp);
		glVertex3f(pD.x[0], pD.y[iy-1], zp);
		glVertex3f(xp, pD.y[iy-1], zp);
		glEnd();

		Draw3DLine(xp, yp, pD.z[iz-1], pD.x[0], yp, pD.z[iz-1]);
		Draw3DLine(xp, yp, pD.z[iz-1], xp, pD.y[iy-1], pD.z[iz-1]);
		m_p4D->xSE = ix - m_p4D->xSE;
	}

	void COpenGL4D::BlockTopFrontLeftCorner(int ix, int iy, int iz)
	{
		m_p4D->ySE = iy - m_p4D->ySE;
		int x = m_p4D->xSE;
		int y = m_p4D->ySE-1;
		int z = m_p4D->zSE;
		int j = 0, i = 0;
	
		// front: x==0
		for(j=0; j<iz-1; j++)
			for(i=0; i<iy-1; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[(j*iy+i)*ix]);
			glVertex3f(pD.x[0], pD.y[i], pD.z[j]);
			ColorLevel(pD.w[(j*iy+i+1)*ix]);
			glVertex3f(pD.x[0], pD.y[i+1], pD.z[j]);
			ColorLevel(pD.w[((j+1)*iy+i+1)*ix]);
			glVertex3f(pD.x[0], pD.y[i+1], pD.z[j+1]);
			ColorLevel(pD.w[((j+1)*iy+i)*ix]);
			glVertex3f(pD.x[0], pD.y[i], pD.z[j+1]);
			glEnd();
		}

		// left: y==max
		for(j=0; j<iz-1; j++)
			for(i=0; i<ix-1; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[((j+1)*iy-1)*ix+i]);
			glVertex3f(pD.x[i], pD.y[iy-1], pD.z[j]);
			ColorLevel(pD.w[((j+1)*iy-1)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[iy-1], pD.z[j]);
			ColorLevel(pD.w[((j+2)*iy-1)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[iy-1], pD.z[j+1]);
			ColorLevel(pD.w[((j+2)*iy-1)*ix+i]);
			glVertex3f(pD.x[i], pD.y[iy-1], pD.z[j+1]);
			glEnd();
		}

		// bottom: z = 0;
		for(j=0; j<iy-1; j++)
			for(i=0; i<ix-1; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[j*ix+i]);
			glVertex3f(pD.x[i], pD.y[j], pD.z[0]);
			ColorLevel(pD.w[j*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[j], pD.z[0]);
			ColorLevel(pD.w[(j+1)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[j+1], pD.z[0]);
			ColorLevel(pD.w[(j+1)*ix+i]);
			glVertex3f(pD.x[i], pD.y[j+1], pD.z[0]);
			glEnd();
		}

		// front left cutting: x==max
		for(j=0; j<iz-1; j++)
			for(i=y; i<iy-1; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[(j*iy+i+1)*ix-1]);
			glVertex3f(pD.x[ix-1], pD.y[i], pD.z[j]);
			ColorLevel(pD.w[(j*iy+i+2)*ix-1]);
			glVertex3f(pD.x[ix-1], pD.y[i+1], pD.z[j]);
			ColorLevel(pD.w[((j+1)*iy+i+2)*ix-1]);
			glVertex3f(pD.x[ix-1], pD.y[i+1], pD.z[j+1]);
			ColorLevel(pD.w[((j+1)*iy+i+1)*ix-1]);
			glVertex3f(pD.x[ix-1], pD.y[i], pD.z[j+1]);
			glEnd();
		}

		// back right bottom cutting: x==max
		for(j=0; j<z; j++)
			for(i=0; i<y; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[(j*iy+i+1)*ix-1]);
			glVertex3f(pD.x[ix-1], pD.y[i], pD.z[j]);
			ColorLevel(pD.w[(j*iy+i+2)*ix-1]);
			glVertex3f(pD.x[ix-1], pD.y[i+1], pD.z[j]);
			ColorLevel(pD.w[((j+1)*iy+i+2)*ix-1]);
			glVertex3f(pD.x[ix-1], pD.y[i+1], pD.z[j+1]);
			ColorLevel(pD.w[((j+1)*iy+i+1)*ix-1]);
			glVertex3f(pD.x[ix-1], pD.y[i], pD.z[j+1]);
			glEnd();
		}

		// right back cutting: y==0
		int m = iy * ix;
		for(j=0; j<iz-1; j++)
			for(i=0; i<x; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[j*m+i]);
			glVertex3f(pD.x[i], pD.y[0], pD.z[j]);
			ColorLevel(pD.w[j*m+i+1]);
			glVertex3f(pD.x[i+1], pD.y[0], pD.z[j]);
			ColorLevel(pD.w[(j+1)*m+i+1]);
			glVertex3f(pD.x[i+1], pD.y[0], pD.z[j+1]);
			ColorLevel(pD.w[(j+1)*m+i]);
			glVertex3f(pD.x[i], pD.y[0], pD.z[j+1]);
			glEnd();
		}

		// right front bottom cutting: y==0
		for(j=0; j<z; j++)
			for(i=x; i<ix-1; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[j*m+i]);
			glVertex3f(pD.x[i], pD.y[0], pD.z[j]);
			ColorLevel(pD.w[j*m+i+1]);
			glVertex3f(pD.x[i+1], pD.y[0], pD.z[j]);
			ColorLevel(pD.w[(j+1)*m+i+1]);
			glVertex3f(pD.x[i+1], pD.y[0], pD.z[j+1]);
			ColorLevel(pD.w[(j+1)*m+i]);
			glVertex3f(pD.x[i], pD.y[0], pD.z[j+1]);
			glEnd();
		}

		// top front left  cutting: z==max
		m = (iz - 1) * iy;
		for(j=0; j<iy-1; j++)
			for(i=0; i<x; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[(m+j)*ix+i]);
			glVertex3f(pD.x[i], pD.y[j], pD.z[iz-1]);
			ColorLevel(pD.w[(m+j)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[j], pD.z[iz-1]);
			ColorLevel(pD.w[(m+j+1)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[j+1], pD.z[iz-1]);
			ColorLevel(pD.w[(m+j+1)*ix+i]);
			glVertex3f(pD.x[i], pD.y[j+1], pD.z[iz-1]);
			glEnd();
		}

		for(j=y; j<iy-1; j++) // z==max
			for(i=x; i<ix-1; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[(m+j)*ix+i]);
			glVertex3f(pD.x[i], pD.y[j], pD.z[iz-1]);
			ColorLevel(pD.w[(m+j)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[j], pD.z[iz-1]);
			ColorLevel(pD.w[(m+j+1)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[j+1], pD.z[iz-1]);
			ColorLevel(pD.w[(m+j+1)*ix+i]);
			glVertex3f(pD.x[i], pD.y[j+1], pD.z[iz-1]);
			glEnd();
		}

		// cut yz face x = m_p4D->xSE
		for(j=z; j<iz-1; j++)
			for(i=0; i<y; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[(j*iy+i)*ix+x]);
			glVertex3f(pD.x[x], pD.y[i], pD.z[j]);
			ColorLevel(pD.w[(j*iy+i+1)*ix+x]);
			glVertex3f(pD.x[x], pD.y[i+1], pD.z[j]);
			ColorLevel(pD.w[((j+1)*iy+i+1)*ix+x]);
			glVertex3f(pD.x[x], pD.y[i+1], pD.z[j+1]);
			ColorLevel(pD.w[((j+1)*iy+i)*ix+x]);
			glVertex3f(pD.x[x], pD.y[i], pD.z[j+1]);
			glEnd();
		}

		// cut xz face: y=m_p4D->ySE
		for(j=z; j<iz-1; j++)
			for(i=x; i<ix-1; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[(j*iy+y)*ix+i]);
			glVertex3f(pD.x[i], pD.y[y], pD.z[j]);
			ColorLevel(pD.w[(j*iy+y)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[y], pD.z[j]);
			ColorLevel(pD.w[((j+1)*iy+y)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[y], pD.z[j+1]);
			ColorLevel(pD.w[((j+1)*iy+y)*ix+i]);
			glVertex3f(pD.x[i], pD.y[y], pD.z[j+1]);
			glEnd();
		}
	
		// cut xy face z = m_p4D->zSE
		m = z * iy; 
		for(j=0; j<y; j++)
			for(i=x; i<ix-1; i++)
		{
			glBegin(GL_QUADS);
			// int g = (k * row + j)* col + i; 
			ColorLevel(pD.w[(m+j)*ix+i]);
			glVertex3f(pD.x[i], pD.y[j], pD.z[z]);
			ColorLevel(pD.w[(m+j)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[j], pD.z[z]);
			ColorLevel(pD.w[(m+j+1)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[j+1], pD.z[z]);
			ColorLevel(pD.w[(m+j+1)*ix+i]);
			glVertex3f(pD.x[i], pD.y[j+1], pD.z[z]);
			glEnd();
		}

		// draw cut lines
		float xp = pD.x[x] + delta;
		float yp = pD.y[y] - delta;
		float zp = pD.z[z] + delta;

		glColor3f(1.0f - m_p4D->m_BackCr.r, 1.0f - m_p4D->m_BackCr.g, 1.0f - m_p4D->m_BackCr.b);
		Draw3DLine(xp, yp, zp, xp, yp, pD.z[iz-1]);
		Draw3DLine(pD.x[ix-1], yp, zp, pD.x[ix-1], yp, pD.z[iz-1]);
		Draw3DLine(xp, pD.y[0], pD.z[iz-1], xp, pD.y[0], zp);

		glBegin(GL_LINE_LOOP);
		glVertex3f(xp, yp, zp);
		glVertex3f(pD.x[x], pD.y[0], zp);
		glVertex3f(pD.x[ix-1], pD.y[0], zp);
		glVertex3f(pD.x[ix-1], pD.y[y], zp);
		glEnd();

		Draw3DLine(xp, yp, pD.z[iz-1], pD.x[x], pD.y[0], pD.z[iz-1]);
		Draw3DLine(xp, yp, pD.z[iz-1], pD.x[ix-1], pD.y[y], pD.z[iz-1]);
		m_p4D->ySE = iy - m_p4D->ySE;
	}

	void COpenGL4D::BlockTopBackLeftCorner(int ix, int iy, int iz)
	{
		m_p4D->xSE = ix - m_p4D->xSE;
		m_p4D->ySE = iy - m_p4D->ySE;
		int x = m_p4D->xSE-1;
		int y = m_p4D->ySE-1;
		int z = m_p4D->zSE;
		int j = 0, i = 0;
	
		// front: x==max
		for(j=0; j<iz-1; j++)
			for(i=0; i<iy-1; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[(j*iy+i+1)*ix-1]);
			glVertex3f(pD.x[ix-1], pD.y[i], pD.z[j]);
			ColorLevel(pD.w[(j*iy+i+2)*ix-1]);
			glVertex3f(pD.x[ix-1], pD.y[i+1], pD.z[j]);
			ColorLevel(pD.w[((j+1)*iy+i+2)*ix-1]);
			glVertex3f(pD.x[ix-1], pD.y[i+1], pD.z[j+1]);
			ColorLevel(pD.w[((j+1)*iy+i+1)*ix-1]);
			glVertex3f(pD.x[ix-1], pD.y[i], pD.z[j+1]);
			glEnd();
		}

		// right: y==max
		for(j=0; j<iz-1; j++)
			for(i=0; i<ix-1; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[((j+1)*iy-1)*ix+i]);
			glVertex3f(pD.x[i], pD.y[iy-1], pD.z[j]);
			ColorLevel(pD.w[((j+1)*iy-1)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[iy-1], pD.z[j]);
			ColorLevel(pD.w[((j+2)*iy-1)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[iy-1], pD.z[j+1]);
			ColorLevel(pD.w[((j+2)*iy-1)*ix+i]);
			glVertex3f(pD.x[i], pD.y[iy-1], pD.z[j+1]);
			glEnd();
		}

		// bottom: z = 0;
		for(j=0; j<iy-1; j++)
			for(i=0; i<ix-1; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[j*ix+i]);
			glVertex3f(pD.x[i], pD.y[j], pD.z[0]);
			ColorLevel(pD.w[j*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[j], pD.z[0]);
			ColorLevel(pD.w[(j+1)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[j+1], pD.z[0]);
			ColorLevel(pD.w[(j+1)*ix+i]);
			glVertex3f(pD.x[i], pD.y[j+1], pD.z[0]);
			glEnd();
		}

		// back left cutting: x==0
		for(j=0; j<z; j++)
			for(i=0; i<iy-1; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[(j*iy+i)*ix]);
			glVertex3f(pD.x[0], pD.y[i], pD.z[j]);
			ColorLevel(pD.w[(j*iy+i+1)*ix]);
			glVertex3f(pD.x[0], pD.y[i+1], pD.z[j]);
			ColorLevel(pD.w[((j+1)*iy+i+1)*ix]);
			glVertex3f(pD.x[0], pD.y[i+1], pD.z[j+1]);
			ColorLevel(pD.w[((j+1)*iy+i)*ix]);
			glVertex3f(pD.x[0], pD.y[i], pD.z[j+1]);
			glEnd();
		}

		// back left cutting: x==0
		for(j=z; j<iz-1; j++)
			for(i=y; i<iy-1; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[(j*iy+i)*ix]);
			glVertex3f(pD.x[0], pD.y[i], pD.z[j]);
			ColorLevel(pD.w[(j*iy+i+1)*ix]);
			glVertex3f(pD.x[0], pD.y[i+1], pD.z[j]);
			ColorLevel(pD.w[((j+1)*iy+i+1)*ix]);
			glVertex3f(pD.x[0], pD.y[i+1], pD.z[j+1]);
			ColorLevel(pD.w[((j+1)*iy+i)*ix]);
			glVertex3f(pD.x[0], pD.y[i], pD.z[j+1]);
			glEnd();
		}

		// left back cutting: y==0
		int m = iy * ix;
		for(j=0; j<z; j++)
			for(i=0; i<ix-1; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[j*m+i]);
			glVertex3f(pD.x[i], pD.y[0], pD.z[j]);
			ColorLevel(pD.w[j*m+i+1]);
			glVertex3f(pD.x[i+1], pD.y[0], pD.z[j]);
			ColorLevel(pD.w[(j+1)*m+i+1]);
			glVertex3f(pD.x[i+1], pD.y[0], pD.z[j+1]);
			ColorLevel(pD.w[(j+1)*m+i]);
			glVertex3f(pD.x[i], pD.y[0], pD.z[j+1]);
			glEnd();
		}

		// right front  cutting: y==0
		for(j=z; j<iz-1; j++)
			for(i=x; i<ix-1; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[j*m+i]);
			glVertex3f(pD.x[i], pD.y[0], pD.z[j]);
			ColorLevel(pD.w[j*m+i+1]);
			glVertex3f(pD.x[i+1], pD.y[0], pD.z[j]);
			ColorLevel(pD.w[(j+1)*m+i+1]);
			glVertex3f(pD.x[i+1], pD.y[0], pD.z[j+1]);
			ColorLevel(pD.w[(j+1)*m+i]);
			glVertex3f(pD.x[i], pD.y[0], pD.z[j+1]);
			glEnd();
		}

		// top back left  cutting: z==max
		m = (iz - 1) * iy;
		for(j=0; j<iy-1; j++)
			for(i=x; i<ix-1; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[(m+j)*ix+i]);
			glVertex3f(pD.x[i], pD.y[j], pD.z[iz-1]);
			ColorLevel(pD.w[(m+j)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[j], pD.z[iz-1]);
			ColorLevel(pD.w[(m+j+1)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[j+1], pD.z[iz-1]);
			ColorLevel(pD.w[(m+j+1)*ix+i]);
			glVertex3f(pD.x[i], pD.y[j+1], pD.z[iz-1]);
			glEnd();
		}

		for(j=y; j<iy-1; j++) // z==max
			for(i=0; i<x; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[(m+j)*ix+i]);
			glVertex3f(pD.x[i], pD.y[j], pD.z[iz-1]);
			ColorLevel(pD.w[(m+j)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[j], pD.z[iz-1]);
			ColorLevel(pD.w[(m+j+1)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[j+1], pD.z[iz-1]);
			ColorLevel(pD.w[(m+j+1)*ix+i]);
			glVertex3f(pD.x[i], pD.y[j+1], pD.z[iz-1]);
			glEnd();
		}

		// cut yz face x = m_p4D->xSE
		for(j=z; j<iz-1; j++)
			for(i=0; i<y; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[(j*iy+i)*ix+x]);
			glVertex3f(pD.x[x], pD.y[i], pD.z[j]);
			ColorLevel(pD.w[(j*iy+i+1)*ix+x]);
			glVertex3f(pD.x[x], pD.y[i+1], pD.z[j]);
			ColorLevel(pD.w[((j+1)*iy+i+1)*ix+x]);
			glVertex3f(pD.x[x], pD.y[i+1], pD.z[j+1]);
			ColorLevel(pD.w[((j+1)*iy+i)*ix+x]);
			glVertex3f(pD.x[x], pD.y[i], pD.z[j+1]);
			glEnd();
		}

		// cut xz face: y=m_p4D->ySE
		for(j=z; j<iz-1; j++)
			for(i=0; i<x; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[(j*iy+y)*ix+i]);
			glVertex3f(pD.x[i], pD.y[y], pD.z[j]);
			ColorLevel(pD.w[(j*iy+y)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[y], pD.z[j]);
			ColorLevel(pD.w[((j+1)*iy+y)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[y], pD.z[j+1]);
			ColorLevel(pD.w[((j+1)*iy+y)*ix+i]);
			glVertex3f(pD.x[i], pD.y[y], pD.z[j+1]);
			glEnd();
		}
	
		// cut xy face z = m_p4D->zSE
		m = z * iy; 
		for(j=0; j<y; j++)
			for(i=0; i<x; i++)
		{
			glBegin(GL_QUADS);
			// int g = (k * row + j)* col + i; 
			ColorLevel(pD.w[(m+j)*ix+i]);
			glVertex3f(pD.x[i], pD.y[j], pD.z[z]);
			ColorLevel(pD.w[(m+j)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[j], pD.z[z]);
			ColorLevel(pD.w[(m+j+1)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[j+1], pD.z[z]);
			ColorLevel(pD.w[(m+j+1)*ix+i]);
			glVertex3f(pD.x[i], pD.y[j+1], pD.z[z]);
			glEnd();
		}

		// draw cut lines
		float xp = pD.x[x] - delta;
		float yp = pD.y[y] - delta;
		float zp = pD.z[z] + delta;

		glColor3f(1.0f - m_p4D->m_BackCr.r, 1.0f - m_p4D->m_BackCr.g, 1.0f - m_p4D->m_BackCr.b);
		Draw3DLine(xp, yp, zp, xp, yp, pD.z[iz-1]);
		Draw3DLine(pD.x[x], pD.y[0], zp, pD.x[x], pD.y[0], pD.z[iz-1]);
		Draw3DLine(pD.x[0], pD.y[y], pD.z[iz-1], pD.x[0], pD.y[y], zp);

		glBegin(GL_LINE_LOOP);
		glVertex3f(xp, yp, zp);
		glVertex3f(pD.x[0], pD.y[y], zp);
		glVertex3f(pD.x[0], pD.y[0], zp);
		glVertex3f(pD.x[x], pD.y[0], zp);
		glEnd();

		Draw3DLine(xp, yp, pD.z[iz-1], pD.x[0], pD.y[y], pD.z[iz-1]);
		Draw3DLine(xp, yp, pD.z[iz-1], pD.x[x], pD.y[0], pD.z[iz-1]);
		m_p4D->xSE = ix - m_p4D->xSE;
		m_p4D->ySE = iy - m_p4D->ySE;
	}

	void COpenGL4D::BlockBottomFrontRightCorner(int ix, int iy, int iz)
	{
		m_p4D->zSE = iz - m_p4D->zSE;
		int x = m_p4D->xSE;
		int y = m_p4D->ySE;
		int z = m_p4D->zSE-1;
		int j = 0, i = 0;

		// back: x==0
		for(j=0; j<iz-1; j++)
			for(i=0; i<iy-1; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[(j*iy+i)*ix]);
			glVertex3f(pD.x[0], pD.y[i], pD.z[j]);
			ColorLevel(pD.w[(j*iy+i+1)*ix]);
			glVertex3f(pD.x[0], pD.y[i+1], pD.z[j]);
			ColorLevel(pD.w[((j+1)*iy+i+1)*ix]);
			glVertex3f(pD.x[0], pD.y[i+1], pD.z[j+1]);
			ColorLevel(pD.w[((j+1)*iy+i)*ix]);
			glVertex3f(pD.x[0], pD.y[i], pD.z[j+1]);
			glEnd();
		}

		// left: y==0
		int m = iy*ix; 
		for(j=0; j<iz-1; j++)
			for(i=0; i<ix-1; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[j*m+i]);
			glVertex3f(pD.x[i], pD.y[0], pD.z[j]);
			ColorLevel(pD.w[j*m+i+1]);
			glVertex3f(pD.x[i+1], pD.y[0], pD.z[j]);
			ColorLevel(pD.w[(j+1)*m+i+1]);
			glVertex3f(pD.x[i+1], pD.y[0], pD.z[j+1]);
			ColorLevel(pD.w[(j+1)*m+i]);
			glVertex3f(pD.x[i], pD.y[0], pD.z[j+1]);
			glEnd();
		}

		// top: z = max;
		m = (iz-1) * iy;
		for(j=0; j<iy-1; j++)
			for(i=0; i<ix-1; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[(m+j)*ix+i]);
			glVertex3f(pD.x[i], pD.y[j], pD.z[iz-1]);
			ColorLevel(pD.w[(m+j)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[j], pD.z[iz-1]);
			ColorLevel(pD.w[(m+j+1)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[j+1], pD.z[iz-1]);
			ColorLevel(pD.w[(m+j+1)*ix+i]);
			glVertex3f(pD.x[i], pD.y[j+1], pD.z[iz-1]);
			glEnd();
		}

		// front left cutting: x==max
		for(j=0; j<iz-1; j++)
			for(i=0; i<y; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[(j*iy+i+1)*ix-1]);
			glVertex3f(pD.x[ix-1], pD.y[i], pD.z[j]);
			ColorLevel(pD.w[(j*iy+i+2)*ix-1]);
			glVertex3f(pD.x[ix-1], pD.y[i+1], pD.z[j]);
			ColorLevel(pD.w[((j+1)*iy+i+2)*ix-1]);
			glVertex3f(pD.x[ix-1], pD.y[i+1], pD.z[j+1]);
			ColorLevel(pD.w[((j+1)*iy+i+1)*ix-1]);
			glVertex3f(pD.x[ix-1], pD.y[i], pD.z[j+1]);
			glEnd();
		}

		// front right bottom cutting: x==max
		for(j=z; j<iz-1; j++)
			for(i=y; i<iy-1; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[(j*iy+i+1)*ix-1]);
			glVertex3f(pD.x[ix-1], pD.y[i], pD.z[j]);
			ColorLevel(pD.w[(j*iy+i+2)*ix-1]);
			glVertex3f(pD.x[ix-1], pD.y[i+1], pD.z[j]);
			ColorLevel(pD.w[((j+1)*iy+i+2)*ix-1]);
			glVertex3f(pD.x[ix-1], pD.y[i+1], pD.z[j+1]);
			ColorLevel(pD.w[((j+1)*iy+i+1)*ix-1]);
			glVertex3f(pD.x[ix-1], pD.y[i], pD.z[j+1]);
			glEnd();
		}

		// right back cutting: y=max
		for(j=0; j<iz-1; j++)
			for(i=0; i<x; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[((j+1)*iy-1)*ix+i]);
			glVertex3f(pD.x[i], pD.y[iy-1], pD.z[j]);
			ColorLevel(pD.w[((j+1)*iy-1)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[iy-1], pD.z[j]);
			ColorLevel(pD.w[((j+2)*iy-1)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[iy-1], pD.z[j+1]);
			ColorLevel(pD.w[((j+2)*iy-1)*ix+i]);
			glVertex3f(pD.x[i], pD.y[iy-1], pD.z[j+1]);
			glEnd();
		}

		// right front bottom cutting: y=max
		for(j=z; j<iz-1; j++)
			for(i=x; i<ix-1; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[((j+1)*iy-1)*ix+i]);
			glVertex3f(pD.x[i], pD.y[iy-1], pD.z[j]);
			ColorLevel(pD.w[((j+1)*iy-1)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[iy-1], pD.z[j]);
			ColorLevel(pD.w[((j+2)*iy-1)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[iy-1], pD.z[j+1]);
			ColorLevel(pD.w[((j+2)*iy-1)*ix+i]);
			glVertex3f(pD.x[i], pD.y[iy-1], pD.z[j+1]);
			glEnd();
		}

		// top back cutting: z==0
		for(j=0; j<iy-1; j++)
			for(i=0; i<x; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[j*ix+i]);
			glVertex3f(pD.x[i], pD.y[j], pD.z[0]);
			ColorLevel(pD.w[j*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[j], pD.z[0]);
			ColorLevel(pD.w[(j+1)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[j+1], pD.z[0]);
			ColorLevel(pD.w[(j+1)*ix+i]);
			glVertex3f(pD.x[i], pD.y[j+1], pD.z[0]);
			glEnd();
		}

		for(j=0; j<y; j++)
			for(i=x; i<ix-1; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[j*ix+i]);
			glVertex3f(pD.x[i], pD.y[j], pD.z[0]);
			ColorLevel(pD.w[j*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[j], pD.z[0]);
			ColorLevel(pD.w[(j+1)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[j+1], pD.z[0]);
			ColorLevel(pD.w[(j+1)*ix+i]);
			glVertex3f(pD.x[i], pD.y[j+1], pD.z[0]);
			glEnd();
		}

		// cut yz face x = m_p4D->xSE
		for(j=0; j<z; j++)
			for(i=y; i<iy-1; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[(j*iy+i)*ix+x]);
			glVertex3f(pD.x[x], pD.y[i], pD.z[j]);
			ColorLevel(pD.w[(j*iy+i+1)*ix+x]);
			glVertex3f(pD.x[x], pD.y[i+1], pD.z[j]);
			ColorLevel(pD.w[((j+1)*iy+i+1)*ix+x]);
			glVertex3f(pD.x[x], pD.y[i+1], pD.z[j+1]);
			ColorLevel(pD.w[((j+1)*iy+i)*ix+x]);
			glVertex3f(pD.x[x], pD.y[i], pD.z[j+1]);
			glEnd();
		}

		// cut xz face: y=m_p4D->ySE
		for(j=0; j<z; j++)
			for(i=x; i<ix-1; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[(j*iy+y)*ix+i]);
			glVertex3f(pD.x[i], pD.y[y], pD.z[j]);
			ColorLevel(pD.w[(j*iy+y)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[y], pD.z[j]);
			ColorLevel(pD.w[((j+1)*iy+y)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[y], pD.z[j+1]);
			ColorLevel(pD.w[((j+1)*iy+y)*ix+i]);
			glVertex3f(pD.x[i], pD.y[y], pD.z[j+1]);
			glEnd();
		}
	
		// cut xy face z = m_p4D->zSE
		m = z * iy; 
		for(j=y; j<iy-1; j++)
			for(i=x; i<ix-1; i++)
		{
			glBegin(GL_QUADS);
			// int g = (k * row + j)* col + i; 
			ColorLevel(pD.w[(m+j)*ix+i]);
			glVertex3f(pD.x[i], pD.y[j], pD.z[z]);
			ColorLevel(pD.w[(m+j)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[j], pD.z[z]);
			ColorLevel(pD.w[(m+j+1)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[j+1], pD.z[z]);
			ColorLevel(pD.w[(m+j+1)*ix+i]);
			glVertex3f(pD.x[i], pD.y[j+1], pD.z[z]);
			glEnd();
		}

		// draw cut lines
		float xp = pD.x[x] + delta;
		float yp = pD.y[y] + delta;
		float zp = pD.z[z] - delta;

		glColor3f(1.0f - m_p4D->m_BackCr.r, 1.0f - m_p4D->m_BackCr.g, 1.0f - m_p4D->m_BackCr.b);
		//glLineWidth(2);
		Draw3DLine(xp, yp, zp, xp, yp, pD.z[0]);
		Draw3DLine(pD.x[ix-1], yp, zp, pD.x[ix-1], yp, pD.z[0]);
		Draw3DLine(xp, pD.y[iy-1], zp, xp, pD.y[iy-1], pD.z[0]);

		//glLineWidth(2);
		glBegin(GL_LINE_LOOP);
		glVertex3f(xp, yp, zp);
		glVertex3f(pD.x[ix-1], yp, zp);
		glVertex3f(pD.x[ix-1], pD.y[iy-1], zp);
		glVertex3f(xp, pD.y[iy-1], zp);
		glEnd();

		//glLineWidth(1);

		Draw3DLine(xp, yp, pD.z[0], pD.x[ix-1], yp, pD.z[0]);
		Draw3DLine(xp, yp, pD.z[0], xp, pD.y[iy-1], pD.z[0]);

		m_p4D->zSE = iz - m_p4D->zSE;
	}

	void COpenGL4D::BlockBottomBackRightCorner(int ix, int iy, int iz)
	{
		m_p4D->xSE = ix - m_p4D->xSE;
		m_p4D->zSE = iz - m_p4D->zSE;
		int x = m_p4D->xSE-1;
		int y = m_p4D->ySE;
		int z = m_p4D->zSE-1;
		int j = 0, i = 0;

		// front: x==max
		for(j=0; j<iz-1; j++)
			for(i=0; i<iy-1; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[(j*iy+i+1)*ix-1]);
			glVertex3f(pD.x[ix-1], pD.y[i], pD.z[j]);
			ColorLevel(pD.w[(j*iy+i+2)*ix-1]);
			glVertex3f(pD.x[ix-1], pD.y[i+1], pD.z[j]);
			ColorLevel(pD.w[((j+1)*iy+i+2)*ix-1]);
			glVertex3f(pD.x[ix-1], pD.y[i+1], pD.z[j+1]);
			ColorLevel(pD.w[((j+1)*iy+i+1)*ix-1]);
			glVertex3f(pD.x[ix-1], pD.y[i], pD.z[j+1]);
			glEnd();
		}

		// left: y==0
		int m = iy*ix; 
		for(j=0; j<iz-1; j++)
			for(i=0; i<ix-1; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[j*m+i]);
			glVertex3f(pD.x[i], pD.y[0], pD.z[j]);
			ColorLevel(pD.w[j*m+i+1]);
			glVertex3f(pD.x[i+1], pD.y[0], pD.z[j]);
			ColorLevel(pD.w[(j+1)*m+i+1]);
			glVertex3f(pD.x[i+1], pD.y[0], pD.z[j+1]);
			ColorLevel(pD.w[(j+1)*m+i]);
			glVertex3f(pD.x[i], pD.y[0], pD.z[j+1]);
			glEnd();
		}

		// bottom: z = max;
		m = (iz-1) * iy;
		for(j=0; j<iy-1; j++)
			for(i=0; i<ix-1; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[(m+j)*ix+i]);
			glVertex3f(pD.x[i], pD.y[j], pD.z[iz-1]);
			ColorLevel(pD.w[(m+j)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[j], pD.z[iz-1]);
			ColorLevel(pD.w[(m+j+1)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[j+1], pD.z[iz-1]);
			ColorLevel(pD.w[(m+j+1)*ix+i]);
			glVertex3f(pD.x[i], pD.y[j+1], pD.z[iz-1]);
			glEnd();
		}

		// back left cutting: x==0
		for(j=0; j<iz-1; j++)
			for(i=0; i<y; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[(j*iy+i)*ix]);
			glVertex3f(pD.x[0], pD.y[i], pD.z[j]);
			ColorLevel(pD.w[(j*iy+i+1)*ix]);
			glVertex3f(pD.x[0], pD.y[i+1], pD.z[j]);
			ColorLevel(pD.w[((j+1)*iy+i+1)*ix]);
			glVertex3f(pD.x[0], pD.y[i+1], pD.z[j+1]);
			ColorLevel(pD.w[((j+1)*iy+i)*ix]);
			glVertex3f(pD.x[0], pD.y[i], pD.z[j+1]);
			glEnd();
		}

		// back right bottom cutting: x==0
		for(j=z; j<iz-1; j++)
			for(i=y; i<iy-1; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[(j*iy+i)*ix]);
			glVertex3f(pD.x[0], pD.y[i], pD.z[j]);
			ColorLevel(pD.w[(j*iy+i+1)*ix]);
			glVertex3f(pD.x[0], pD.y[i+1], pD.z[j]);
			ColorLevel(pD.w[((j+1)*iy+i+1)*ix]);
			glVertex3f(pD.x[0], pD.y[i+1], pD.z[j+1]);
			ColorLevel(pD.w[((j+1)*iy+i)*ix]);
			glVertex3f(pD.x[0], pD.y[i], pD.z[j+1]);
			glEnd();
		}

		// right back cutting: y=max
		for(j=0; j<iz-1; j++)
			for(i=x; i<ix-1; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[((j+1)*iy-1)*ix+i]);
			glVertex3f(pD.x[i], pD.y[iy-1], pD.z[j]);
			ColorLevel(pD.w[((j+1)*iy-1)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[iy-1], pD.z[j]);
			ColorLevel(pD.w[((j+2)*iy-1)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[iy-1], pD.z[j+1]);
			ColorLevel(pD.w[((j+2)*iy-1)*ix+i]);
			glVertex3f(pD.x[i], pD.y[iy-1], pD.z[j+1]);
			glEnd();
		}

		// right front bottom cutting: y=max
		for(j=z; j<iz-1; j++)
			for(i=0; i<x; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[((j+1)*iy-1)*ix+i]);
			glVertex3f(pD.x[i], pD.y[iy-1], pD.z[j]);
			ColorLevel(pD.w[((j+1)*iy-1)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[iy-1], pD.z[j]);
			ColorLevel(pD.w[((j+2)*iy-1)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[iy-1], pD.z[j+1]);
			ColorLevel(pD.w[((j+2)*iy-1)*ix+i]);
			glVertex3f(pD.x[i], pD.y[iy-1], pD.z[j+1]);
			glEnd();
		}

		// bottom back cutting: z=0
		for(j=0; j<iy-1; j++)
			for(i=x; i<ix-1; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[j*ix+i]);
			glVertex3f(pD.x[i], pD.y[j], pD.z[0]);
			ColorLevel(pD.w[j*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[j], pD.z[0]);
			ColorLevel(pD.w[(j+1)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[j+1], pD.z[0]);
			ColorLevel(pD.w[(j+1)*ix+i]);
			glVertex3f(pD.x[i], pD.y[j+1], pD.z[0]);
			glEnd();
		}

		for(j=0; j<y; j++) // z==0
			for(i=0; i<x; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[j*ix+i]);
			glVertex3f(pD.x[i], pD.y[j], pD.z[0]);
			ColorLevel(pD.w[j*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[j], pD.z[0]);
			ColorLevel(pD.w[(j+1)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[j+1], pD.z[0]);
			ColorLevel(pD.w[(j+1)*ix+i]);
			glVertex3f(pD.x[i], pD.y[j+1], pD.z[0]);
			glEnd();
		}

		// cut yz face x = m_p4D->xSE
		for(j=0; j<z; j++)
			for(i=y; i<iy-1; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[(j*iy+i)*ix+x]);
			glVertex3f(pD.x[x], pD.y[i], pD.z[j]);
			ColorLevel(pD.w[(j*iy+i+1)*ix+x]);
			glVertex3f(pD.x[x], pD.y[i+1], pD.z[j]);
			ColorLevel(pD.w[((j+1)*iy+i+1)*ix+x]);
			glVertex3f(pD.x[x], pD.y[i+1], pD.z[j+1]);
			ColorLevel(pD.w[((j+1)*iy+i)*ix+x]);
			glVertex3f(pD.x[x], pD.y[i], pD.z[j+1]);
			glEnd();
		}

		// cut xz face: y=m_p4D->ySE
		for(j=0; j<z; j++)
			for(i=0; i<x; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[(j*iy+y)*ix+i]);
			glVertex3f(pD.x[i], pD.y[y], pD.z[j]);
			ColorLevel(pD.w[(j*iy+y)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[y], pD.z[j]);
			ColorLevel(pD.w[((j+1)*iy+y)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[y], pD.z[j+1]);
			ColorLevel(pD.w[((j+1)*iy+y)*ix+i]);
			glVertex3f(pD.x[i], pD.y[y], pD.z[j+1]);
			glEnd();
		}
	
		// cut xy face z = m_p4D->zSE
		m = z * iy; 
		for(j=y; j<iy-1; j++)
			for(i=0; i<x; i++)
		{
			glBegin(GL_QUADS);
			// int g = (k * row + j)* col + i; 
			ColorLevel(pD.w[(m+j)*ix+i]);
			glVertex3f(pD.x[i], pD.y[j], pD.z[z]);
			ColorLevel(pD.w[(m+j)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[j], pD.z[z]);
			ColorLevel(pD.w[(m+j+1)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[j+1], pD.z[z]);
			ColorLevel(pD.w[(m+j+1)*ix+i]);
			glVertex3f(pD.x[i], pD.y[j+1], pD.z[z]);
			glEnd();
		}

		// draw cut lines
		float xp = pD.x[x] - delta;
		float yp = pD.y[y] + delta;
		float zp = pD.z[z] - delta;

		glColor3f(1.0f - m_p4D->m_BackCr.r, 1.0f - m_p4D->m_BackCr.g, 1.0f - m_p4D->m_BackCr.b);
		Draw3DLine(xp, yp, zp, xp, yp, pD.z[0]);
		Draw3DLine(pD.x[0], yp, zp, pD.x[0], yp, pD.z[0]);
		Draw3DLine(xp, pD.y[iy-1], pD.z[0], xp, pD.y[iy-1], zp);

		glBegin(GL_LINE_LOOP);
		glVertex3f(xp, yp, zp);
		glVertex3f(pD.x[0], yp, zp);
		glVertex3f(pD.x[0], pD.y[iy-1], zp);
		glVertex3f(xp, pD.y[iy-1], zp);
		glEnd();

		Draw3DLine(xp, yp, pD.z[0], pD.x[0], yp, pD.z[0]);
		Draw3DLine(xp, yp, pD.z[0], xp, pD.y[iy-1], pD.z[0]);
		m_p4D->xSE = ix - m_p4D->xSE;
		m_p4D->zSE = iz - m_p4D->zSE;
	}

	void COpenGL4D::BlockBottomFrontLeftCorner(int ix, int iy, int iz)
	{
		m_p4D->ySE = iy - m_p4D->ySE;
		m_p4D->zSE = iz - m_p4D->zSE;
		int x = m_p4D->xSE;
		int y = m_p4D->ySE-1;
		int z = m_p4D->zSE-1;
		int j = 0, i = 0;

	
		// front: x==0
		for(j=0; j<iz-1; j++)
			for(i=0; i<iy-1; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[(j*iy+i)*ix]);
			glVertex3f(pD.x[0], pD.y[i], pD.z[j]);
			ColorLevel(pD.w[(j*iy+i+1)*ix]);
			glVertex3f(pD.x[0], pD.y[i+1], pD.z[j]);
			ColorLevel(pD.w[((j+1)*iy+i+1)*ix]);
			glVertex3f(pD.x[0], pD.y[i+1], pD.z[j+1]);
			ColorLevel(pD.w[((j+1)*iy+i)*ix]);
			glVertex3f(pD.x[0], pD.y[i], pD.z[j+1]);
			glEnd();
		}

		// left: y==max
		for(j=0; j<iz-1; j++)
			for(i=0; i<ix-1; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[((j+1)*iy-1)*ix+i]);
			glVertex3f(pD.x[i], pD.y[iy-1], pD.z[j]);
			ColorLevel(pD.w[((j+1)*iy-1)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[iy-1], pD.z[j]);
			ColorLevel(pD.w[((j+2)*iy-1)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[iy-1], pD.z[j+1]);
			ColorLevel(pD.w[((j+2)*iy-1)*ix+i]);
			glVertex3f(pD.x[i], pD.y[iy-1], pD.z[j+1]);
			glEnd();
		}

		// bottom: z = max;
		int m = (iz-1) * iy;
		for(j=0; j<iy-1; j++)
			for(i=0; i<ix-1; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[(m+j)*ix+i]);
			glVertex3f(pD.x[i], pD.y[j], pD.z[iz-1]);
			ColorLevel(pD.w[(m+j)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[j], pD.z[iz-1]);
			ColorLevel(pD.w[(m+j+1)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[j+1], pD.z[iz-1]);
			ColorLevel(pD.w[(m+j+1)*ix+i]);
			glVertex3f(pD.x[i], pD.y[j+1], pD.z[iz-1]);
			glEnd();
		}

		// front left cutting: x==max
		for(j=0; j<iz-1; j++)
			for(i=y; i<iy-1; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[(j*iy+i+1)*ix-1]);
			glVertex3f(pD.x[ix-1], pD.y[i], pD.z[j]);
			ColorLevel(pD.w[(j*iy+i+2)*ix-1]);
			glVertex3f(pD.x[ix-1], pD.y[i+1], pD.z[j]);
			ColorLevel(pD.w[((j+1)*iy+i+2)*ix-1]);
			glVertex3f(pD.x[ix-1], pD.y[i+1], pD.z[j+1]);
			ColorLevel(pD.w[((j+1)*iy+i+1)*ix-1]);
			glVertex3f(pD.x[ix-1], pD.y[i], pD.z[j+1]);
			glEnd();
		}

		// back right bottom cutting: x==max
		for(j=z; j<iz-1; j++)
			for(i=0; i<y; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[(j*iy+i+1)*ix-1]);
			glVertex3f(pD.x[ix-1], pD.y[i], pD.z[j]);
			ColorLevel(pD.w[(j*iy+i+2)*ix-1]);
			glVertex3f(pD.x[ix-1], pD.y[i+1], pD.z[j]);
			ColorLevel(pD.w[((j+1)*iy+i+2)*ix-1]);
			glVertex3f(pD.x[ix-1], pD.y[i+1], pD.z[j+1]);
			ColorLevel(pD.w[((j+1)*iy+i+1)*ix-1]);
			glVertex3f(pD.x[ix-1], pD.y[i], pD.z[j+1]);
			glEnd();
		}

		// left front cutting: y==0
		m = iy * ix;
		for(j=0; j<iz-1; j++)
			for(i=0; i<x; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[j*m+i]);
			glVertex3f(pD.x[i], pD.y[0], pD.z[j]);
			ColorLevel(pD.w[j*m+i+1]);
			glVertex3f(pD.x[i+1], pD.y[0], pD.z[j]);
			ColorLevel(pD.w[(j+1)*m+i+1]);
			glVertex3f(pD.x[i+1], pD.y[0], pD.z[j+1]);
			ColorLevel(pD.w[(j+1)*m+i]);
			glVertex3f(pD.x[i], pD.y[0], pD.z[j+1]);
			glEnd();
		}

		// right front bottom cutting: y==0
		for(j=z; j<iz-1; j++)
			for(i=x; i<ix-1; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[j*m+i]);
			glVertex3f(pD.x[i], pD.y[0], pD.z[j]);
			ColorLevel(pD.w[j*m+i+1]);
			glVertex3f(pD.x[i+1], pD.y[0], pD.z[j]);
			ColorLevel(pD.w[(j+1)*m+i+1]);
			glVertex3f(pD.x[i+1], pD.y[0], pD.z[j+1]);
			ColorLevel(pD.w[(j+1)*m+i]);
			glVertex3f(pD.x[i], pD.y[0], pD.z[j+1]);
			glEnd();
		}

		// top front left  cutting: z==0
		// top back cutting: z==0
		for(j=0; j<iy-1; j++)
			for(i=0; i<x; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[j*ix+i]);
			glVertex3f(pD.x[i], pD.y[j], pD.z[0]);
			ColorLevel(pD.w[j*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[j], pD.z[0]);
			ColorLevel(pD.w[(j+1)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[j+1], pD.z[0]);
			ColorLevel(pD.w[(j+1)*ix+i]);
			glVertex3f(pD.x[i], pD.y[j+1], pD.z[0]);
			glEnd();
		}

		for(j=y; j<iy-1; j++)
			for(i=x; i<ix-1; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[j*ix+i]);
			glVertex3f(pD.x[i], pD.y[j], pD.z[0]);
			ColorLevel(pD.w[j*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[j], pD.z[0]);
			ColorLevel(pD.w[(j+1)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[j+1], pD.z[0]);
			ColorLevel(pD.w[(j+1)*ix+i]);
			glVertex3f(pD.x[i], pD.y[j+1], pD.z[0]);
			glEnd();
		}

		// cut yz face x = m_p4D->xSE
		for(j=0; j<z; j++)
			for(i=0; i<y; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[(j*iy+i)*ix+x]);
			glVertex3f(pD.x[x], pD.y[i], pD.z[j]);
			ColorLevel(pD.w[(j*iy+i+1)*ix+x]);
			glVertex3f(pD.x[x], pD.y[i+1], pD.z[j]);
			ColorLevel(pD.w[((j+1)*iy+i+1)*ix+x]);
			glVertex3f(pD.x[x], pD.y[i+1], pD.z[j+1]);
			ColorLevel(pD.w[((j+1)*iy+i)*ix+x]);
			glVertex3f(pD.x[x], pD.y[i], pD.z[j+1]);
			glEnd();
		}

		// cut xz face: y=m_p4D->ySE
		for(j=0; j<z; j++)
			for(i=x; i<ix-1; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[(j*iy+y)*ix+i]);
			glVertex3f(pD.x[i], pD.y[y], pD.z[j]);
			ColorLevel(pD.w[(j*iy+y)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[y], pD.z[j]);
			ColorLevel(pD.w[((j+1)*iy+y)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[y], pD.z[j+1]);
			ColorLevel(pD.w[((j+1)*iy+y)*ix+i]);
			glVertex3f(pD.x[i], pD.y[y], pD.z[j+1]);
			glEnd();
		}
	
		// cut xy face z = m_p4D->zSE
		m = z * iy; 
		for(j=0; j<y; j++)
			for(i=x; i<ix-1; i++)
		{
			glBegin(GL_QUADS);
			// int g = (k * row + j)* col + i; 
			ColorLevel(pD.w[(m+j)*ix+i]);
			glVertex3f(pD.x[i], pD.y[j], pD.z[z]);
			ColorLevel(pD.w[(m+j)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[j], pD.z[z]);
			ColorLevel(pD.w[(m+j+1)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[j+1], pD.z[z]);
			ColorLevel(pD.w[(m+j+1)*ix+i]);
			glVertex3f(pD.x[i], pD.y[j+1], pD.z[z]);
			glEnd();
		}

		// draw cut lines
		float xp = pD.x[x] + delta;
		float yp = pD.y[y] - delta;
		float zp = pD.z[z] - delta;

		glColor3f(1.0f - m_p4D->m_BackCr.r, 1.0f - m_p4D->m_BackCr.g, 1.0f - m_p4D->m_BackCr.b);
		Draw3DLine(xp, yp, zp, xp, yp, pD.z[0]);
		Draw3DLine(pD.x[ix-1], yp, zp, pD.x[ix-1], yp, pD.z[0]);
		Draw3DLine(xp, pD.y[0], pD.z[0], xp, pD.y[0], zp);

		glBegin(GL_LINE_LOOP);
		glVertex3f(xp, yp, zp);
		glVertex3f(pD.x[x], pD.y[0], zp);
		glVertex3f(pD.x[ix-1], pD.y[0], zp);
		glVertex3f(pD.x[ix-1], pD.y[y], zp);
		glEnd();

		Draw3DLine(xp, yp, pD.z[0], pD.x[x], pD.y[0], pD.z[0]);
		Draw3DLine(xp, yp, pD.z[0], pD.x[ix-1], pD.y[y], pD.z[0]);
		m_p4D->ySE = iy - m_p4D->ySE;
		m_p4D->zSE = iz - m_p4D->zSE;
	}

	void COpenGL4D::BlockBottomBackLeftCorner(int ix, int iy, int iz)
	{
		m_p4D->xSE = ix - m_p4D->xSE;
		m_p4D->ySE = iy - m_p4D->ySE;
		m_p4D->zSE = iz - m_p4D->zSE;
		int x = m_p4D->xSE-1;
		int y = m_p4D->ySE-1;
		int z = m_p4D->zSE-1;
		int j = 0, i = 0;

	
		// front: x==max
		for(j=0; j<iz-1; j++)
			for(i=0; i<iy-1; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[(j*iy+i+1)*ix-1]);
			glVertex3f(pD.x[ix-1], pD.y[i], pD.z[j]);
			ColorLevel(pD.w[(j*iy+i+2)*ix-1]);
			glVertex3f(pD.x[ix-1], pD.y[i+1], pD.z[j]);
			ColorLevel(pD.w[((j+1)*iy+i+2)*ix-1]);
			glVertex3f(pD.x[ix-1], pD.y[i+1], pD.z[j+1]);
			ColorLevel(pD.w[((j+1)*iy+i+1)*ix-1]);
			glVertex3f(pD.x[ix-1], pD.y[i], pD.z[j+1]);
			glEnd();
		}

		// right: y==max
		for(j=0; j<iz-1; j++)
			for(i=0; i<ix-1; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[((j+1)*iy-1)*ix+i]);
			glVertex3f(pD.x[i], pD.y[iy-1], pD.z[j]);
			ColorLevel(pD.w[((j+1)*iy-1)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[iy-1], pD.z[j]);
			ColorLevel(pD.w[((j+2)*iy-1)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[iy-1], pD.z[j+1]);
			ColorLevel(pD.w[((j+2)*iy-1)*ix+i]);
			glVertex3f(pD.x[i], pD.y[iy-1], pD.z[j+1]);
			glEnd();
		}

		// bottom: z = 0;
		int m = (iz-1) * iy;
		for(j=0; j<iy-1; j++)
			for(i=0; i<ix-1; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[(m+j)*ix+i]);
			glVertex3f(pD.x[i], pD.y[j], pD.z[iz-1]);
			ColorLevel(pD.w[(m+j)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[j], pD.z[iz-1]);
			ColorLevel(pD.w[(m+j+1)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[j+1], pD.z[iz-1]);
			ColorLevel(pD.w[(m+j+1)*ix+i]);
			glVertex3f(pD.x[i], pD.y[j+1], pD.z[iz-1]);
			glEnd();
		}

		// back left cutting: x==0
		for(j=z; j<iz-1; j++)
			for(i=0; i<iy-1; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[(j*iy+i)*ix]);
			glVertex3f(pD.x[0], pD.y[i], pD.z[j]);
			ColorLevel(pD.w[(j*iy+i+1)*ix]);
			glVertex3f(pD.x[0], pD.y[i+1], pD.z[j]);
			ColorLevel(pD.w[((j+1)*iy+i+1)*ix]);
			glVertex3f(pD.x[0], pD.y[i+1], pD.z[j+1]);
			ColorLevel(pD.w[((j+1)*iy+i)*ix]);
			glVertex3f(pD.x[0], pD.y[i], pD.z[j+1]);
			glEnd();
		}

		// back left cutting: x==0
		for(j=z; j<iz-1; j++)
			for(i=0; i<y; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[(j*iy+i)*ix]);
			glVertex3f(pD.x[0], pD.y[i], pD.z[j]);
			ColorLevel(pD.w[(j*iy+i+1)*ix]);
			glVertex3f(pD.x[0], pD.y[i+1], pD.z[j]);
			ColorLevel(pD.w[((j+1)*iy+i+1)*ix]);
			glVertex3f(pD.x[0], pD.y[i+1], pD.z[j+1]);
			ColorLevel(pD.w[((j+1)*iy+i)*ix]);
			glVertex3f(pD.x[0], pD.y[i], pD.z[j+1]);
			glEnd();
		}

		// left back cutting: y==0
		m = iy * ix;
		for(j=z; j<iz-1; j++)
			for(i=0; i<ix-1; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[j*m+i]);
			glVertex3f(pD.x[i], pD.y[0], pD.z[j]);
			ColorLevel(pD.w[j*m+i+1]);
			glVertex3f(pD.x[i+1], pD.y[0], pD.z[j]);
			ColorLevel(pD.w[(j+1)*m+i+1]);
			glVertex3f(pD.x[i+1], pD.y[0], pD.z[j+1]);
			ColorLevel(pD.w[(j+1)*m+i]);
			glVertex3f(pD.x[i], pD.y[0], pD.z[j+1]);
			glEnd();
		}

		// right front  cutting: y==0
		for(j=0; j<z; j++)
			for(i=x; i<ix-1; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[j*m+i]);
			glVertex3f(pD.x[i], pD.y[0], pD.z[j]);
			ColorLevel(pD.w[j*m+i+1]);
			glVertex3f(pD.x[i+1], pD.y[0], pD.z[j]);
			ColorLevel(pD.w[(j+1)*m+i+1]);
			glVertex3f(pD.x[i+1], pD.y[0], pD.z[j+1]);
			ColorLevel(pD.w[(j+1)*m+i]);
			glVertex3f(pD.x[i], pD.y[0], pD.z[j+1]);
			glEnd();
		}

		// back left bottom corner
		for(j=0; j<iy-1; j++)
			for(i=x; i<ix-1; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[j*ix+i]);
			glVertex3f(pD.x[i], pD.y[j], pD.z[0]);
			ColorLevel(pD.w[j*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[j], pD.z[0]);
			ColorLevel(pD.w[(j+1)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[j+1], pD.z[0]);
			ColorLevel(pD.w[(j+1)*ix+i]);
			glVertex3f(pD.x[i], pD.y[j+1], pD.z[0]);
			glEnd();
		}

		for(j=y; j<iy-1; j++)
			for(i=0; i<x; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[j*ix+i]);
			glVertex3f(pD.x[i], pD.y[j], pD.z[0]);
			ColorLevel(pD.w[j*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[j], pD.z[0]);
			ColorLevel(pD.w[(j+1)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[j+1], pD.z[0]);
			ColorLevel(pD.w[(j+1)*ix+i]);
			glVertex3f(pD.x[i], pD.y[j+1], pD.z[0]);
			glEnd();
		}

		// cut yz face x = m_p4D->xSE
		for(j=0; j<z; j++)
			for(i=0; i<y; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[(j*iy+i)*ix+x]);
			glVertex3f(pD.x[x], pD.y[i], pD.z[j]);
			ColorLevel(pD.w[(j*iy+i+1)*ix+x]);
			glVertex3f(pD.x[x], pD.y[i+1], pD.z[j]);
			ColorLevel(pD.w[((j+1)*iy+i+1)*ix+x]);
			glVertex3f(pD.x[x], pD.y[i+1], pD.z[j+1]);
			ColorLevel(pD.w[((j+1)*iy+i)*ix+x]);
			glVertex3f(pD.x[x], pD.y[i], pD.z[j+1]);
			glEnd();
		}

		// cut xz face: y=m_p4D->ySE
		for(j=0; j<z; j++)
			for(i=0; i<x; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[(j*iy+y)*ix+i]);
			glVertex3f(pD.x[i], pD.y[y], pD.z[j]);
			ColorLevel(pD.w[(j*iy+y)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[y], pD.z[j]);
			ColorLevel(pD.w[((j+1)*iy+y)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[y], pD.z[j+1]);
			ColorLevel(pD.w[((j+1)*iy+y)*ix+i]);
			glVertex3f(pD.x[i], pD.y[y], pD.z[j+1]);
			glEnd();
		}
	
		// cut xy face z = m_p4D->zSE
		m = z * iy; 
		for(j=0; j<y; j++)
			for(i=0; i<x; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[(m+j)*ix+i]);
			glVertex3f(pD.x[i], pD.y[j], pD.z[z]);
			ColorLevel(pD.w[(m+j)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[j], pD.z[z]);
			ColorLevel(pD.w[(m+j+1)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[j+1], pD.z[z]);
			ColorLevel(pD.w[(m+j+1)*ix+i]);
			glVertex3f(pD.x[i], pD.y[j+1], pD.z[z]);
			glEnd();
		}

		// draw cut lines
		float xp = pD.x[x] - delta;
		float yp = pD.y[y] - delta;
		float zp = pD.z[z] - delta;

		glColor3f(1.0f - m_p4D->m_BackCr.r, 1.0f - m_p4D->m_BackCr.g, 1.0f - m_p4D->m_BackCr.b);
		Draw3DLine(xp, yp, zp, xp, yp, pD.z[0]);
		Draw3DLine(pD.x[x], pD.y[0], zp, pD.x[x], pD.y[0], pD.z[0]);
		Draw3DLine(pD.x[0], pD.y[y], pD.z[0], pD.x[0], pD.y[y], zp);

		glBegin(GL_LINE_LOOP);
		glVertex3f(xp, yp, zp);
		glVertex3f(pD.x[0], pD.y[y], zp);
		glVertex3f(pD.x[0], pD.y[0], zp);
		glVertex3f(pD.x[x], pD.y[0], zp);
		glEnd();

		Draw3DLine(xp, yp, pD.z[0], pD.x[0], pD.y[y], pD.z[0]);
		Draw3DLine(xp, yp, pD.z[0], pD.x[x], pD.y[0], pD.z[0]);
		m_p4D->xSE = ix - m_p4D->xSE;
		m_p4D->ySE = iy - m_p4D->ySE;
		m_p4D->zSE = iz - m_p4D->zSE;
	}

	void COpenGL4D::BlockRightCutFromTopToBottom(int ix, int iy, int iz)
	{
		int y = m_p4D->ySE;
		int j = 0, i = 0;

		// z == 0
		for(j=0; j<y; j++)
			for(i=0; i<ix-1; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[j*ix+i]);
			glVertex3f(pD.x[i], pD.y[j], pD.z[0]);
			ColorLevel(pD.w[j*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[j], pD.z[0]);
			ColorLevel(pD.w[(j+1)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[j+1], pD.z[0]);
			ColorLevel(pD.w[(j+1)*ix+i]);
			glVertex3f(pD.x[i], pD.y[j+1], pD.z[0]);
			glEnd();
		}

		// Top: z=max
		int m = (iz - 1) * iy;
		for(j=0; j<y; j++)
			for(i=0; i<ix-1; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[(m+j)*ix+i]);
			glVertex3f(pD.x[i], pD.y[j], pD.z[iz-1]);
			ColorLevel(pD.w[(m+j)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[j], pD.z[iz-1]);
			ColorLevel(pD.w[(m+j+1)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[j+1], pD.z[iz-1]);
			ColorLevel(pD.w[(m+j+1)*ix+i]);
			glVertex3f(pD.x[i], pD.y[j+1], pD.z[iz-1]);
			glEnd();
		}

		// Left: y=0
		m = iy*ix;
		for(j=0; j<iz-1; j++)
			for(i=0; i<ix-1; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[j*m+i]);
			glVertex3f(pD.x[i], pD.y[0], pD.z[j]);
			ColorLevel(pD.w[j*m+i+1]);
			glVertex3f(pD.x[i+1], pD.y[0], pD.z[j]);
			ColorLevel(pD.w[(j+1)*m+i+1]);
			glVertex3f(pD.x[i+1], pD.y[0], pD.z[j+1]);
			ColorLevel(pD.w[(j+1)*m+i]);
			glVertex3f(pD.x[i], pD.y[0], pD.z[j+1]);
			glEnd();
		}

		// Right: y=m_p4D->ySE
		for(j=0; j<iz-1; j++)
			for(i=0; i<ix-1; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[(j*iy+y)*ix+i]);
			glVertex3f(pD.x[i], pD.y[y], pD.z[j]);
			ColorLevel(pD.w[(j*iy+y)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[y], pD.z[j]);
			ColorLevel(pD.w[((j+1)*iy+y)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[y], pD.z[j+1]);
			ColorLevel(pD.w[((j+1)*iy+y)*ix+i]);
			glVertex3f(pD.x[i], pD.y[y], pD.z[j+1]);
			glEnd();
		}

		// front: x=max
		for(j=0; j<iz-1; j++)
			for(i=0; i<y; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[(j*iy+i+1)*ix-1]);
			glVertex3f(pD.x[ix-1], pD.y[i], pD.z[j]);
			ColorLevel(pD.w[(j*iy+i+2)*ix-1]);
			glVertex3f(pD.x[ix-1], pD.y[i+1], pD.z[j]);
			ColorLevel(pD.w[((j+1)*iy+i+2)*ix-1]);
			glVertex3f(pD.x[ix-1], pD.y[i+1], pD.z[j+1]);
			ColorLevel(pD.w[((j+1)*iy+i+1)*ix-1]);
			glVertex3f(pD.x[ix-1], pD.y[i], pD.z[j+1]);
			glEnd();
		}

		// back: x=0
		for(j=0; j<iz-1; j++)
			for(i=0; i<y; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[(j*iy+i)*ix]);
			glVertex3f(pD.x[0], pD.y[i], pD.z[j]);
			ColorLevel(pD.w[(j*iy+i+1)*ix]);
			glVertex3f(pD.x[0], pD.y[i+1], pD.z[j]);
			ColorLevel(pD.w[((j+1)*iy+i+1)*ix]);
			glVertex3f(pD.x[0], pD.y[i+1], pD.z[j+1]);
			ColorLevel(pD.w[((j+1)*iy+i)*ix]);
			glVertex3f(pD.x[0], pD.y[i], pD.z[j+1]);
			glEnd();
		}

		glColor3f(1.0f - m_p4D->m_BackCr.r, 1.0f - m_p4D->m_BackCr.g, 1.0f - m_p4D->m_BackCr.b);
		glBegin(GL_LINE_LOOP);
		glVertex3f(pD.x[ix-1], pD.y[y], pD.z[iz-1]);
		glVertex3f(pD.x[ix-1], pD.y[y], pD.z[0]);
		glVertex3f(pD.x[0], pD.y[y], pD.z[0]);
		glVertex3f(pD.x[0], pD.y[y], pD.z[iz-1]);
		glEnd();
	}

	void COpenGL4D::BlockLeftCutFromTopToBottom(int ix, int iy, int iz) 
	{
		m_p4D->ySE = iy - m_p4D->ySE;
		int y = m_p4D->ySE - 1;
		int j = 0, i = 0;

		// z == 0
		for(j=y; j<iy-1; j++)
			for(i=0; i<ix-1; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[j*ix+i]);
			glVertex3f(pD.x[i], pD.y[j], pD.z[0]);
			ColorLevel(pD.w[j*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[j], pD.z[0]);
			ColorLevel(pD.w[(j+1)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[j+1], pD.z[0]);
			ColorLevel(pD.w[(j+1)*ix+i]);
			glVertex3f(pD.x[i], pD.y[j+1], pD.z[0]);
			glEnd();
		}

		// Top: z=max
		int m = (iz - 1) * iy;
		for(j=y; j<iy-1; j++)
			for(i=0; i<ix-1; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[(m+j)*ix+i]);
			glVertex3f(pD.x[i], pD.y[j], pD.z[iz-1]);
			ColorLevel(pD.w[(m+j)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[j], pD.z[iz-1]);
			ColorLevel(pD.w[(m+j+1)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[j+1], pD.z[iz-1]);
			ColorLevel(pD.w[(m+j+1)*ix+i]);
			glVertex3f(pD.x[i], pD.y[j+1], pD.z[iz-1]);
			glEnd();
		}

		// y=max
		for(j=0; j<iz-1; j++)
			for(i=0; i<ix-1; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[((j+1)*iy-1)*ix+i]);
			glVertex3f(pD.x[i], pD.y[iy-1], pD.z[j]);
			ColorLevel(pD.w[((j+1)*iy-1)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[iy-1], pD.z[j]);
			ColorLevel(pD.w[((j+2)*iy-1)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[iy-1], pD.z[j+1]);
			ColorLevel(pD.w[((j+2)*iy-1)*ix+i]);
			glVertex3f(pD.x[i], pD.y[iy-1], pD.z[j+1]);
			glEnd();
		}

		// Right: y=m_p4D->ySE
		for(j=0; j<iz-1; j++)
			for(i=0; i<ix-1; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[(j*iy+y)*ix+i]);
			glVertex3f(pD.x[i], pD.y[y], pD.z[j]);
			ColorLevel(pD.w[(j*iy+y)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[y], pD.z[j]);
			ColorLevel(pD.w[((j+1)*iy+y)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[y], pD.z[j+1]);
			ColorLevel(pD.w[((j+1)*iy+y)*ix+i]);
			glVertex3f(pD.x[i], pD.y[y], pD.z[j+1]);
			glEnd();
		}

		// front: x=max
		for(j=0; j<iz-1; j++)
			for(i=y; i<iy-1; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[(j*iy+i+1)*ix-1]);
			glVertex3f(pD.x[ix-1], pD.y[i], pD.z[j]);
			ColorLevel(pD.w[(j*iy+i+2)*ix-1]);
			glVertex3f(pD.x[ix-1], pD.y[i+1], pD.z[j]);
			ColorLevel(pD.w[((j+1)*iy+i+2)*ix-1]);
			glVertex3f(pD.x[ix-1], pD.y[i+1], pD.z[j+1]);
			ColorLevel(pD.w[((j+1)*iy+i+1)*ix-1]);
			glVertex3f(pD.x[ix-1], pD.y[i], pD.z[j+1]);
			glEnd();
		}

		// back: x=0
		for(j=0; j<iz-1; j++)
			for(i=y; i<iy-1; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[(j*iy+i)*ix]);
			glVertex3f(pD.x[0], pD.y[i], pD.z[j]);
			ColorLevel(pD.w[(j*iy+i+1)*ix]);
			glVertex3f(pD.x[0], pD.y[i+1], pD.z[j]);
			ColorLevel(pD.w[((j+1)*iy+i+1)*ix]);
			glVertex3f(pD.x[0], pD.y[i+1], pD.z[j+1]);
			ColorLevel(pD.w[((j+1)*iy+i)*ix]);
			glVertex3f(pD.x[0], pD.y[i], pD.z[j+1]);
			glEnd();
		}

		glColor3f(1.0f - m_p4D->m_BackCr.r, 1.0f - m_p4D->m_BackCr.g, 1.0f - m_p4D->m_BackCr.b);
		glBegin(GL_LINE_LOOP);
		glVertex3f(pD.x[ix-1], pD.y[y], pD.z[iz-1]);
		glVertex3f(pD.x[ix-1], pD.y[y], pD.z[0]);
		glVertex3f(pD.x[0], pD.y[y], pD.z[0]);
		glVertex3f(pD.x[0], pD.y[y], pD.z[iz-1]);
		glEnd();

		m_p4D->ySE = iy - m_p4D->ySE;
	}

	void COpenGL4D::BlockFrontCutFromTopToBottom(int ix, int iy, int iz)
	{
		int x = m_p4D->xSE;
		int j = 0, i = 0;

		// z == 0
		for(j=0; j<iy-1; j++)
			for(i=0; i<x; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[j*ix+i]);
			glVertex3f(pD.x[i], pD.y[j], pD.z[0]);
			ColorLevel(pD.w[j*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[j], pD.z[0]);
			ColorLevel(pD.w[(j+1)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[j+1], pD.z[0]);
			ColorLevel(pD.w[(j+1)*ix+i]);
			glVertex3f(pD.x[i], pD.y[j+1], pD.z[0]);
			glEnd();
		}

		// Top: z=max
		int m = (iz - 1) * iy;
		for(j=0; j<iy-1; j++)
			for(i=0; i<x; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[(m+j)*ix+i]);
			glVertex3f(pD.x[i], pD.y[j], pD.z[iz-1]);
			ColorLevel(pD.w[(m+j)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[j], pD.z[iz-1]);
			ColorLevel(pD.w[(m+j+1)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[j+1], pD.z[iz-1]);
			ColorLevel(pD.w[(m+j+1)*ix+i]);
			glVertex3f(pD.x[i], pD.y[j+1], pD.z[iz-1]);
			glEnd();
		}

		// Left: y=0
		m = iy*ix;
		for(j=0; j<iz-1; j++)
			for(i=0; i<x; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[j*m+i]);
			glVertex3f(pD.x[i], pD.y[0], pD.z[j]);
			ColorLevel(pD.w[j*m+i+1]);
			glVertex3f(pD.x[i+1], pD.y[0], pD.z[j]);
			ColorLevel(pD.w[(j+1)*m+i+1]);
			glVertex3f(pD.x[i+1], pD.y[0], pD.z[j+1]);
			ColorLevel(pD.w[(j+1)*m+i]);
			glVertex3f(pD.x[i], pD.y[0], pD.z[j+1]);
			glEnd();
		}

		// Right: y=max
		for(j=0; j<iz-1; j++)
			for(i=0; i<x; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[((j+1)*iy-1)*ix+i]);
			glVertex3f(pD.x[i], pD.y[iy-1], pD.z[j]);
			ColorLevel(pD.w[((j+1)*iy-1)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[iy-1], pD.z[j]);
			ColorLevel(pD.w[((j+2)*iy-1)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[iy-1], pD.z[j+1]);
			ColorLevel(pD.w[((j+2)*iy-1)*ix+i]);
			glVertex3f(pD.x[i], pD.y[iy-1], pD.z[j+1]);
			glEnd();
		}

		// front: x=m_p4D->xSE;
		for(j=0; j<iz-1; j++)
			for(i=0; i<iy-1; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[(j*iy+i)*ix+x]);
			glVertex3f(pD.x[x], pD.y[i], pD.z[j]);
			ColorLevel(pD.w[(j*iy+i+1)*ix+x]);
			glVertex3f(pD.x[x], pD.y[i+1], pD.z[j]);
			ColorLevel(pD.w[((j+1)*iy+i+1)*ix+x]);
			glVertex3f(pD.x[x], pD.y[i+1], pD.z[j+1]);
			ColorLevel(pD.w[((j+1)*iy+i)*ix+x]);
			glVertex3f(pD.x[x], pD.y[i], pD.z[j+1]);
			glEnd();
		}

		// back: x=0
		for(j=0; j<iz-1; j++)
			for(i=0; i<iy-1; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[(j*iy+i)*ix]);
			glVertex3f(pD.x[0], pD.y[i], pD.z[j]);
			ColorLevel(pD.w[(j*iy+i+1)*ix]);
			glVertex3f(pD.x[0], pD.y[i+1], pD.z[j]);
			ColorLevel(pD.w[((j+1)*iy+i+1)*ix]);
			glVertex3f(pD.x[0], pD.y[i+1], pD.z[j+1]);
			ColorLevel(pD.w[((j+1)*iy+i)*ix]);
			glVertex3f(pD.x[0], pD.y[i], pD.z[j+1]);
			glEnd();
		}
		
		glColor3f(1.0f - m_p4D->m_BackCr.r, 1.0f - m_p4D->m_BackCr.g, 1.0f - m_p4D->m_BackCr.b);
		glBegin(GL_LINE_LOOP);
		glVertex3f(pD.x[x], pD.y[0], pD.z[0]);
		glVertex3f(pD.x[x], pD.y[iy-1], pD.z[0]);
		glVertex3f(pD.x[x], pD.y[iy-1], pD.z[iz-1]);
		glVertex3f(pD.x[x], pD.y[0], pD.z[iz-1]);
		glEnd();
	}

	void COpenGL4D::BlockBackCutFromTopToBottom(int ix, int iy, int iz)
	{
		m_p4D->xSE = ix - m_p4D->xSE;
		int x = m_p4D->xSE - 1;
		int j = 0, i = 0;

		// z == 0
		for(j=0; j<iy-1; j++)
			for(i=x; i<ix-1; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[j*ix+i]);
			glVertex3f(pD.x[i], pD.y[j], pD.z[0]);
			ColorLevel(pD.w[j*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[j], pD.z[0]);
			ColorLevel(pD.w[(j+1)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[j+1], pD.z[0]);
			ColorLevel(pD.w[(j+1)*ix+i]);
			glVertex3f(pD.x[i], pD.y[j+1], pD.z[0]);
			glEnd();
		}

		// Top: z=max
		int m = (iz - 1) * iy;
		for(j=0; j<iy-1; j++)
			for(i=x; i<ix-1; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[(m+j)*ix+i]);
			glVertex3f(pD.x[i], pD.y[j], pD.z[iz-1]);
			ColorLevel(pD.w[(m+j)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[j], pD.z[iz-1]);
			ColorLevel(pD.w[(m+j+1)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[j+1], pD.z[iz-1]);
			ColorLevel(pD.w[(m+j+1)*ix+i]);
			glVertex3f(pD.x[i], pD.y[j+1], pD.z[iz-1]);
			glEnd();
		}

		// Left: y=0
		m = iy*ix;
		for(j=0; j<iz-1; j++)
			for(i=x; i<ix-1; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[j*m+i]);
			glVertex3f(pD.x[i], pD.y[0], pD.z[j]);
			ColorLevel(pD.w[j*m+i+1]);
			glVertex3f(pD.x[i+1], pD.y[0], pD.z[j]);
			ColorLevel(pD.w[(j+1)*m+i+1]);
			glVertex3f(pD.x[i+1], pD.y[0], pD.z[j+1]);
			ColorLevel(pD.w[(j+1)*m+i]);
			glVertex3f(pD.x[i], pD.y[0], pD.z[j+1]);
			glEnd();
		}

		// Right: y=max
		for(j=0; j<iz-1; j++)
			for(i=x; i<ix-1; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[((j+1)*iy-1)*ix+i]);
			glVertex3f(pD.x[i], pD.y[iy-1], pD.z[j]);
			ColorLevel(pD.w[((j+1)*iy-1)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[iy-1], pD.z[j]);
			ColorLevel(pD.w[((j+2)*iy-1)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[iy-1], pD.z[j+1]);
			ColorLevel(pD.w[((j+2)*iy-1)*ix+i]);
			glVertex3f(pD.x[i], pD.y[iy-1], pD.z[j+1]);
			glEnd();
		}

		// front: x=m_p4D->xSE;
		for(j=0; j<iz-1; j++)
			for(i=0; i<iy-1; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[(j*iy+i)*ix+x]);
			glVertex3f(pD.x[x], pD.y[i], pD.z[j]);
			ColorLevel(pD.w[(j*iy+i+1)*ix+x]);
			glVertex3f(pD.x[x], pD.y[i+1], pD.z[j]);
			ColorLevel(pD.w[((j+1)*iy+i+1)*ix+x]);
			glVertex3f(pD.x[x], pD.y[i+1], pD.z[j+1]);
			ColorLevel(pD.w[((j+1)*iy+i)*ix+x]);
			glVertex3f(pD.x[x], pD.y[i], pD.z[j+1]);
			glEnd();
		}

		// back: x=max
		for(j=0; j<iz-1; j++)
			for(i=0; i<iy-1; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[(j*iy+i+1)*ix-1]);
			glVertex3f(pD.x[ix-1], pD.y[i], pD.z[j]);
			ColorLevel(pD.w[(j*iy+i+2)*ix-1]);
			glVertex3f(pD.x[ix-1], pD.y[i+1], pD.z[j]);
			ColorLevel(pD.w[((j+1)*iy+i+2)*ix-1]);
			glVertex3f(pD.x[ix-1], pD.y[i+1], pD.z[j+1]);
			ColorLevel(pD.w[((j+1)*iy+i+1)*ix-1]);
			glVertex3f(pD.x[ix-1], pD.y[i], pD.z[j+1]);
			glEnd();
		}
		
		glColor3f(1.0f - m_p4D->m_BackCr.r, 1.0f - m_p4D->m_BackCr.g, 1.0f - m_p4D->m_BackCr.b);
		glBegin(GL_LINE_LOOP);
		glVertex3f(pD.x[x], pD.y[0], pD.z[0]);
		glVertex3f(pD.x[x], pD.y[iy-1], pD.z[0]);
		glVertex3f(pD.x[x], pD.y[iy-1], pD.z[iz-1]);
		glVertex3f(pD.x[x], pD.y[0], pD.z[iz-1]);
		glEnd();

		m_p4D->xSE = ix - m_p4D->xSE;
	}

	void COpenGL4D::BlockCutFromMiddleToTop(int ix, int iy, int iz)
	{
		int z = m_p4D->zSE;
		int j = 0, i = 0;

		// z == 0
		for(j=0; j<iy-1; j++)
			for(i=0; i<ix-1; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[j*ix+i]);
			glVertex3f(pD.x[i], pD.y[j], pD.z[0]);
			ColorLevel(pD.w[j*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[j], pD.z[0]);
			ColorLevel(pD.w[(j+1)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[j+1], pD.z[0]);
			ColorLevel(pD.w[(j+1)*ix+i]);
			glVertex3f(pD.x[i], pD.y[j+1], pD.z[0]);
			glEnd();
		}

		// Top: z=m_p4D->zSE
		int m = z * iy; 
		for(j=0; j<iy-1; j++)
			for(i=0; i<ix-1; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[(m+j)*ix+i]);
			glVertex3f(pD.x[i], pD.y[j], pD.z[z]);
			ColorLevel(pD.w[(m+j)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[j], pD.z[z]);
			ColorLevel(pD.w[(m+j+1)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[j+1], pD.z[z]);
			ColorLevel(pD.w[(m+j+1)*ix+i]);
			glVertex3f(pD.x[i], pD.y[j+1], pD.z[z]);
			glEnd();
		}

		// Left: y=0
		m = iy*ix;
		for(j=0; j<z; j++)
			for(i=0; i<ix-1; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[j*m+i]);
			glVertex3f(pD.x[i], pD.y[0], pD.z[j]);
			ColorLevel(pD.w[j*m+i+1]);
			glVertex3f(pD.x[i+1], pD.y[0], pD.z[j]);
			ColorLevel(pD.w[(j+1)*m+i+1]);
			glVertex3f(pD.x[i+1], pD.y[0], pD.z[j+1]);
			ColorLevel(pD.w[(j+1)*m+i]);
			glVertex3f(pD.x[i], pD.y[0], pD.z[j+1]);
			glEnd();
		}

		// Right: y=max
		for(j=0; j<z; j++)
			for(i=0; i<ix-1; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[((j+1)*iy-1)*ix+i]);
			glVertex3f(pD.x[i], pD.y[iy-1], pD.z[j]);
			ColorLevel(pD.w[((j+1)*iy-1)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[iy-1], pD.z[j]);
			ColorLevel(pD.w[((j+2)*iy-1)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[iy-1], pD.z[j+1]);
			ColorLevel(pD.w[((j+2)*iy-1)*ix+i]);
			glVertex3f(pD.x[i], pD.y[iy-1], pD.z[j+1]);
			glEnd();
		}

		// front: x=max
		for(j=0; j<z; j++)
			for(i=0; i<iy-1; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[(j*iy+i+1)*ix-1]);
			glVertex3f(pD.x[ix-1], pD.y[i], pD.z[j]);
			ColorLevel(pD.w[(j*iy+i+2)*ix-1]);
			glVertex3f(pD.x[ix-1], pD.y[i+1], pD.z[j]);
			ColorLevel(pD.w[((j+1)*iy+i+2)*ix-1]);
			glVertex3f(pD.x[ix-1], pD.y[i+1], pD.z[j+1]);
			ColorLevel(pD.w[((j+1)*iy+i+1)*ix-1]);
			glVertex3f(pD.x[ix-1], pD.y[i], pD.z[j+1]);
			glEnd();
		}

		// back: x=0
		for(j=0; j<z; j++)
			for(i=0; i<iy-1; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[(j*iy+i)*ix]);
			glVertex3f(pD.x[0], pD.y[i], pD.z[j]);
			ColorLevel(pD.w[(j*iy+i+1)*ix]);
			glVertex3f(pD.x[0], pD.y[i+1], pD.z[j]);
			ColorLevel(pD.w[((j+1)*iy+i+1)*ix]);
			glVertex3f(pD.x[0], pD.y[i+1], pD.z[j+1]);
			ColorLevel(pD.w[((j+1)*iy+i)*ix]);
			glVertex3f(pD.x[0], pD.y[i], pD.z[j+1]);
			glEnd();
		}

		glColor3f(1.0f - m_p4D->m_BackCr.r, 1.0f - m_p4D->m_BackCr.g, 1.0f - m_p4D->m_BackCr.b);
		glBegin(GL_LINE_LOOP);
		glVertex3f(pD.x[0], pD.y[0], pD.z[z]);
		glVertex3f(pD.x[ix-1], pD.y[0], pD.z[z]);
		glVertex3f(pD.x[ix-1], pD.y[iy-1], pD.z[z]);
		glVertex3f(pD.x[0], pD.y[iy-1], pD.z[z]);
		glEnd();

		iz = 0;
	}

	void COpenGL4D::BlockCutFromMiddleToBottom(int ix, int iy, int iz)
	{
		m_p4D->zSE = iz - m_p4D->zSE;
		int z = m_p4D->zSE - 1;
		int j = 0, i = 0;

		//z == max
		int m = (iz - 1) * iy;
		for(j=0; j<iy-1; j++)
			for(i=0; i<ix-1; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[(m+j)*ix+i]);
			glVertex3f(pD.x[i], pD.y[j], pD.z[iz-1]);
			ColorLevel(pD.w[(m+j)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[j], pD.z[iz-1]);
			ColorLevel(pD.w[(m+j+1)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[j+1], pD.z[iz-1]);
			ColorLevel(pD.w[(m+j+1)*ix+i]);
			glVertex3f(pD.x[i], pD.y[j+1], pD.z[iz-1]);
			glEnd();
		}

		// Top: z=m_p4D->zSE
		m = z * iy; 
		for(j=0; j<iy-1; j++)
			for(i=0; i<ix-1; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[(m+j)*ix+i]);
			glVertex3f(pD.x[i], pD.y[j], pD.z[z]);
			ColorLevel(pD.w[(m+j)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[j], pD.z[z]);
			ColorLevel(pD.w[(m+j+1)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[j+1], pD.z[z]);
			ColorLevel(pD.w[(m+j+1)*ix+i]);
			glVertex3f(pD.x[i], pD.y[j+1], pD.z[z]);
			glEnd();
		}

		// Left: y=0
		m = iy*ix;
		for(j=z; j<iz-1; j++)
			for(i=0; i<ix-1; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[j*m+i]);
			glVertex3f(pD.x[i], pD.y[0], pD.z[j]);
			ColorLevel(pD.w[j*m+i+1]);
			glVertex3f(pD.x[i+1], pD.y[0], pD.z[j]);
			ColorLevel(pD.w[(j+1)*m+i+1]);
			glVertex3f(pD.x[i+1], pD.y[0], pD.z[j+1]);
			ColorLevel(pD.w[(j+1)*m+i]);
			glVertex3f(pD.x[i], pD.y[0], pD.z[j+1]);
			glEnd();
		}

		// Right: y=max
		for(j=z; j<iz-1; j++)
			for(i=0; i<ix-1; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[((j+1)*iy-1)*ix+i]);
			glVertex3f(pD.x[i], pD.y[iy-1], pD.z[j]);
			ColorLevel(pD.w[((j+1)*iy-1)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[iy-1], pD.z[j]);
			ColorLevel(pD.w[((j+2)*iy-1)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[iy-1], pD.z[j+1]);
			ColorLevel(pD.w[((j+2)*iy-1)*ix+i]);
			glVertex3f(pD.x[i], pD.y[iy-1], pD.z[j+1]);
			glEnd();
		}

		// front: x=max
		for(j=z; j<iz-1; j++)
			for(i=0; i<iy-1; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[(j*iy+i+1)*ix-1]);
			glVertex3f(pD.x[ix-1], pD.y[i], pD.z[j]);
			ColorLevel(pD.w[(j*iy+i+2)*ix-1]);
			glVertex3f(pD.x[ix-1], pD.y[i+1], pD.z[j]);
			ColorLevel(pD.w[((j+1)*iy+i+2)*ix-1]);
			glVertex3f(pD.x[ix-1], pD.y[i+1], pD.z[j+1]);
			ColorLevel(pD.w[((j+1)*iy+i+1)*ix-1]);
			glVertex3f(pD.x[ix-1], pD.y[i], pD.z[j+1]);
			glEnd();
		}

		// back: x=0
		for(j=z; j<iz-1; j++)
			for(i=0; i<iy-1; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[(j*iy+i)*ix]);
			glVertex3f(pD.x[0], pD.y[i], pD.z[j]);
			ColorLevel(pD.w[(j*iy+i+1)*ix]);
			glVertex3f(pD.x[0], pD.y[i+1], pD.z[j]);
			ColorLevel(pD.w[((j+1)*iy+i+1)*ix]);
			glVertex3f(pD.x[0], pD.y[i+1], pD.z[j+1]);
			ColorLevel(pD.w[((j+1)*iy+i)*ix]);
			glVertex3f(pD.x[0], pD.y[i], pD.z[j+1]);
			glEnd();
		}

		glColor3f(1.0f - m_p4D->m_BackCr.r, 1.0f - m_p4D->m_BackCr.g, 1.0f - m_p4D->m_BackCr.b);
		glBegin(GL_LINE_LOOP);
		glVertex3f(pD.x[0], pD.y[0], pD.z[z]);
		glVertex3f(pD.x[ix-1], pD.y[0], pD.z[z]);
		glVertex3f(pD.x[ix-1], pD.y[iy-1], pD.z[z]);
		glVertex3f(pD.x[0], pD.y[iy-1], pD.z[z]);
		glEnd();

		m_p4D->zSE = iz - m_p4D->zSE;
	}

	void COpenGL4D::BlockCutFromOutsideToInside(int ix, int iy, int iz)
	{
		int x = m_p4D->xSE;
		int y = m_p4D->ySE;
		int z = m_p4D->zSE;
		//z == z1
		int x1 = ix - m_p4D->xSE - 1;
		int y1 = iy - m_p4D->ySE - 1;
		int z1 = iz - m_p4D->zSE - 1;
		int j = 0, i = 0;

		int m = z1 * iy;
		for(j=y; j<y1; j++)
			for(i=x; i<x1; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[(m+j)*ix+i]);
			glVertex3f(pD.x[i], pD.y[j], pD.z[z1]);
			ColorLevel(pD.w[(m+j)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[j], pD.z[z1]);
			ColorLevel(pD.w[(m+j+1)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[j+1], pD.z[z1]);
			ColorLevel(pD.w[(m+j+1)*ix+i]);
			glVertex3f(pD.x[i], pD.y[j+1], pD.z[z1]);
			glEnd();
		}

		// Top: z=z
		m = z * iy; 
		for(j=y; j<y1; j++)
			for(i=x; i<x1; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[(m+j)*ix+i]);
			glVertex3f(pD.x[i], pD.y[j], pD.z[z]);
			ColorLevel(pD.w[(m+j)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[j], pD.z[z]);
			ColorLevel(pD.w[(m+j+1)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[j+1], pD.z[z]);
			ColorLevel(pD.w[(m+j+1)*ix+i]);
			glVertex3f(pD.x[i], pD.y[j+1], pD.z[z]);
			glEnd();
		}

		// Left: y=y
		for(j=z; j<z1; j++)
			for(i=x; i<x1; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[(j*iy+y)*ix+i]);
			glVertex3f(pD.x[i], pD.y[y], pD.z[j]);
			ColorLevel(pD.w[(j*iy+y)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[y], pD.z[j]);
			ColorLevel(pD.w[((j+1)*iy+y)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[y], pD.z[j+1]);
			ColorLevel(pD.w[((j+1)*iy+y)*ix+i]);
			glVertex3f(pD.x[i], pD.y[y], pD.z[j+1]);
			glEnd();
		}

		// Right: y=y1
		for(j=z; j<z1; j++)
			for(i=x; i<x1; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[(j*iy+y1)*ix+i]);
			glVertex3f(pD.x[i], pD.y[y1], pD.z[j]);
			ColorLevel(pD.w[(j*iy+y1)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[y1], pD.z[j]);
			ColorLevel(pD.w[((j+1)*iy+y1)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[y1], pD.z[j+1]);
			ColorLevel(pD.w[((j+1)*iy+y1)*ix+i]);
			glVertex3f(pD.x[i], pD.y[y1], pD.z[j+1]);
			glEnd();
		}

		// front: x=x1
		for(j=z; j<z1; j++)
			for(i=y; i<y1; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[(j*iy+i)*ix+x1]);
			glVertex3f(pD.x[x1], pD.y[i], pD.z[j]);
			ColorLevel(pD.w[(j*iy+i+1)*ix+x1]);
			glVertex3f(pD.x[x1], pD.y[i+1], pD.z[j]);
			ColorLevel(pD.w[((j+1)*iy+i+1)*ix+x1]);
			glVertex3f(pD.x[x1], pD.y[i+1], pD.z[j+1]);
			ColorLevel(pD.w[((j+1)*iy+i)*ix+x1]);
			glVertex3f(pD.x[x1], pD.y[i], pD.z[j+1]);
			glEnd();
		}

		// back: x=x
		for(j=z; j<z1; j++)
			for(i=y; i<y1; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[(j*iy+i)*ix+x]);
			glVertex3f(pD.x[x], pD.y[i], pD.z[j]);
			ColorLevel(pD.w[(j*iy+i+1)*ix+x]);
			glVertex3f(pD.x[x], pD.y[i+1], pD.z[j]);
			ColorLevel(pD.w[((j+1)*iy+i+1)*ix+x]);
			glVertex3f(pD.x[x], pD.y[i+1], pD.z[j+1]);
			ColorLevel(pD.w[((j+1)*iy+i)*ix+x]);
			glVertex3f(pD.x[x], pD.y[i], pD.z[j+1]);
			glEnd();
		}

		glColor3f(1.0f - m_p4D->m_BackCr.r, 1.0f - m_p4D->m_BackCr.g, 1.0f - m_p4D->m_BackCr.b);
		glBegin(GL_LINE_LOOP);
		glVertex3f(pD.x[x], pD.y[y], pD.z[z]);
		glVertex3f(pD.x[x], pD.y[y1], pD.z[z]);
		glVertex3f(pD.x[x], pD.y[y1], pD.z[z1]);
		glVertex3f(pD.x[x], pD.y[y], pD.z[z1]);
		glEnd();

		glBegin(GL_LINE_LOOP);
		glVertex3f(pD.x[x1], pD.y[y], pD.z[z]);
		glVertex3f(pD.x[x1], pD.y[y1], pD.z[z]);
		glVertex3f(pD.x[x1], pD.y[y1], pD.z[z1]);
		glVertex3f(pD.x[x1], pD.y[y], pD.z[z1]);
		glEnd();

		Draw3DLine(pD.x[x], pD.y[y], pD.z[z], pD.x[x1], pD.y[y], pD.z[z]);
		Draw3DLine(pD.x[x], pD.y[y], pD.z[z1], pD.x[x1], pD.y[y], pD.z[z1]);
		Draw3DLine(pD.x[x], pD.y[y1], pD.z[z], pD.x[x1], pD.y[y1], pD.z[z]);
		Draw3DLine(pD.x[x], pD.y[y1], pD.z[z1], pD.x[x1], pD.y[y1], pD.z[z1]);
	}

	void COpenGL4D::BlockCutFromInsideToOutSide(int ix, int iy, int iz)
	{
		int x = m_p4D->xSE;
		int y = m_p4D->ySE;
		int z = m_p4D->zSE;
		int j = 0, i = 0;

	
		//z=z
		int m = z * iy;
		for(j=0; j<iy-1; j++)
			for(i=0; i<ix-1; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[(m+j)*ix+i]);
			glVertex3f(pD.x[i], pD.y[j], pD.z[z]);
			ColorLevel(pD.w[(m+j)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[j], pD.z[z]);
			ColorLevel(pD.w[(m+j+1)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[j+1], pD.z[z]);
			ColorLevel(pD.w[(m+j+1)*ix+i]);
			glVertex3f(pD.x[i], pD.y[j+1], pD.z[z]);
			glEnd();
		}


		// y=y
		for(j=0; j<iz-1; j++)
			for(i=0; i<ix-1; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[(j*iy+y)*ix+i]);
			glVertex3f(pD.x[i], pD.y[y], pD.z[j]);
			ColorLevel(pD.w[(j*iy+y)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[y], pD.z[j]);
			ColorLevel(pD.w[((j+1)*iy+y)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[y], pD.z[j+1]);
			ColorLevel(pD.w[((j+1)*iy+y)*ix+i]);
			glVertex3f(pD.x[i], pD.y[y], pD.z[j+1]);
			glEnd();
		}

		// back: x=x
		for(j=0; j<iz-1; j++)
			for(i=0; i<iy-1; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[(j*iy+i)*ix+x]);
			glVertex3f(pD.x[x], pD.y[i], pD.z[j]);
			ColorLevel(pD.w[(j*iy+i+1)*ix+x]);
			glVertex3f(pD.x[x], pD.y[i+1], pD.z[j]);
			ColorLevel(pD.w[((j+1)*iy+i+1)*ix+x]);
			glVertex3f(pD.x[x], pD.y[i+1], pD.z[j+1]);
			ColorLevel(pD.w[((j+1)*iy+i)*ix+x]);
			glVertex3f(pD.x[x], pD.y[i], pD.z[j+1]);
			glEnd();
		}

		glColor3f(1.0f - m_p4D->m_BackCr.r, 1.0f - m_p4D->m_BackCr.g, 1.0f - m_p4D->m_BackCr.b);
		glBegin(GL_LINE_LOOP);
		glVertex3f(pD.x[x], pD.y[0], pD.z[0]);
		glVertex3f(pD.x[x], pD.y[iy-1], pD.z[0]);
		glVertex3f(pD.x[x], pD.y[iy-1], pD.z[iz-1]);
		glVertex3f(pD.x[x], pD.y[0], pD.z[iz-1]);
		glEnd();

		glBegin(GL_LINE_LOOP);
		glVertex3f(pD.x[0], pD.y[y], pD.z[0]);
		glVertex3f(pD.x[ix-1], pD.y[y], pD.z[0]);
		glVertex3f(pD.x[ix-1], pD.y[y], pD.z[iz-1]);
		glVertex3f(pD.x[0], pD.y[y], pD.z[iz-1]);
		glEnd();

		glBegin(GL_LINE_LOOP);
		glVertex3f(pD.x[0], pD.y[0], pD.z[z]);
		glVertex3f(pD.x[ix-1], pD.y[0], pD.z[z]);
		glVertex3f(pD.x[ix-1], pD.y[iy-1], pD.z[z]);
		glVertex3f(pD.x[0], pD.y[iy-1], pD.z[z]);
		glEnd();
	}

	void COpenGL4D::BlockxTopFrontRightCorner(int ix, int iy, int iz)
	{
		m_p4D->xSE = ix - m_p4D->xSE;
		m_p4D->ySE = iy - m_p4D->ySE;
		m_p4D->zSE = iz - m_p4D->zSE;
		int x = m_p4D->xSE-1;
		int y = m_p4D->ySE-1;
		int z = m_p4D->zSE-1;
		int j = 0, i = 0;


		// back: x==x
		for(j=z; j<iz-1; j++)
			for(i=y; i<iy-1; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[(j*iy+i)*ix+x]);
			glVertex3f(pD.x[x], pD.y[i], pD.z[j]);
			ColorLevel(pD.w[(j*iy+i+1)*ix+x]);
			glVertex3f(pD.x[x], pD.y[i+1], pD.z[j]);
			ColorLevel(pD.w[((j+1)*iy+i+1)*ix+x]);
			glVertex3f(pD.x[x], pD.y[i+1], pD.z[j+1]);
			ColorLevel(pD.w[((j+1)*iy+i)*ix+x]);
			glVertex3f(pD.x[x], pD.y[i], pD.z[j+1]);
			glEnd();
		}

		//x = max
		for(j=z; j<iz-1; j++)
			for(i=y; i<iy-1; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[(j*iy+i+1)*ix-1]);
			glVertex3f(pD.x[ix-1], pD.y[i], pD.z[j]);
			ColorLevel(pD.w[(j*iy+i+2)*ix-1]);
			glVertex3f(pD.x[ix-1], pD.y[i+1], pD.z[j]);
			ColorLevel(pD.w[((j+1)*iy+i+2)*ix-1]);
			glVertex3f(pD.x[ix-1], pD.y[i+1], pD.z[j+1]);
			ColorLevel(pD.w[((j+1)*iy+i+1)*ix-1]);
			glVertex3f(pD.x[ix-1], pD.y[i], pD.z[j+1]);
			glEnd();
		}

		// left: y==y
		for(j=z; j<iz-1; j++)
			for(i=x; i<ix-1; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[(j*iy+y)*ix+i]);
			glVertex3f(pD.x[i], pD.y[y], pD.z[j]);
			ColorLevel(pD.w[(j*iy+y)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[y], pD.z[j]);
			ColorLevel(pD.w[((j+1)*iy+y)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[y], pD.z[j+1]);
			ColorLevel(pD.w[((j+1)*iy+y)*ix+i]);
			glVertex3f(pD.x[i], pD.y[y], pD.z[j+1]);
			glEnd();
		}

		// y = max
		for(j=z; j<iz-1; j++)
			for(i=x; i<ix-1; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[(j*iy+iy-1)*ix+i]);
			glVertex3f(pD.x[i], pD.y[iy-1], pD.z[j]);
			ColorLevel(pD.w[(j*iy+iy-1)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[iy-1], pD.z[j]);
			ColorLevel(pD.w[((j+1)*iy+iy-1)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[iy-1], pD.z[j+1]);
			ColorLevel(pD.w[((j+1)*iy+iy-1)*ix+i]);
			glVertex3f(pD.x[i], pD.y[iy-1], pD.z[j+1]);
			glEnd();
		}

		// z = z;
		int m = z * iy;
		for(j=y; j<iy-1; j++)
			for(i=x; i<ix-1; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[(m+j)*ix+i]);
			glVertex3f(pD.x[i], pD.y[j], pD.z[z]);
			ColorLevel(pD.w[(m+j)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[j], pD.z[z]);
			ColorLevel(pD.w[(m+j+1)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[j+1], pD.z[z]);
			ColorLevel(pD.w[(m+j+1)*ix+i]);
			glVertex3f(pD.x[i], pD.y[j+1], pD.z[z]);
			glEnd();
		}

		// z = z;
		m = (iz - 1) * iy;
		for(j=y; j<iy-1; j++)
			for(i=x; i<ix-1; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[(m+j)*ix+i]);
			glVertex3f(pD.x[i], pD.y[j], pD.z[iz-1]);
			ColorLevel(pD.w[(m+j)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[j], pD.z[iz-1]);
			ColorLevel(pD.w[(m+j+1)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[j+1], pD.z[iz-1]);
			ColorLevel(pD.w[(m+j+1)*ix+i]);
			glVertex3f(pD.x[i], pD.y[j+1], pD.z[iz-1]);
			glEnd();
		}

		// draw cut lines
		float xp = pD.x[x];// + delta;
		float yp = pD.y[y];// + delta;
		float zp = pD.z[z];// + delta;

		glColor3f(1.0f - m_p4D->m_BackCr.r, 1.0f - m_p4D->m_BackCr.g, 1.0f - m_p4D->m_BackCr.b);
		Draw3DLine(xp, yp, zp, xp, yp, pD.z[iz-1]);
		Draw3DLine(pD.x[ix-1], yp, zp, pD.x[ix-1], yp, pD.z[iz-1]);
		Draw3DLine(xp, pD.y[iy-1], pD.z[iz-1], xp, pD.y[iy-1], zp);

		glBegin(GL_LINE_LOOP);
		glVertex3f(xp, yp, zp);
		glVertex3f(pD.x[ix-1], yp, zp);
		glVertex3f(pD.x[ix-1], pD.y[iy-1], zp);
		glVertex3f(xp, pD.y[iy-1], zp);
		glEnd();


		Draw3DLine(xp, yp, pD.z[iz-1], pD.x[ix-1], yp, pD.z[iz-1]);
		Draw3DLine(xp, yp, pD.z[iz-1], xp, pD.y[iy-1], pD.z[iz-1]);

		m_p4D->xSE = ix - m_p4D->xSE;
		m_p4D->ySE = iy - m_p4D->ySE;
		m_p4D->zSE = iz - m_p4D->zSE;
	}

	void COpenGL4D::BlockxTopBackRightCorner(int ix, int iy, int iz)
	{
		m_p4D->ySE = iy - m_p4D->ySE;
		m_p4D->zSE = iz - m_p4D->zSE;
		int x = m_p4D->xSE;
		int y = m_p4D->ySE-1;
		int z = m_p4D->zSE-1;
		int j = 0, i = 0;

		// back: x==x
		for(j=z; j<iz-1; j++)
			for(i=y; i<iy-1; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[(j*iy+i)*ix+x]);
			glVertex3f(pD.x[x], pD.y[i], pD.z[j]);
			ColorLevel(pD.w[(j*iy+i+1)*ix+x]);
			glVertex3f(pD.x[x], pD.y[i+1], pD.z[j]);
			ColorLevel(pD.w[((j+1)*iy+i+1)*ix+x]);
			glVertex3f(pD.x[x], pD.y[i+1], pD.z[j+1]);
			ColorLevel(pD.w[((j+1)*iy+i)*ix+x]);
			glVertex3f(pD.x[x], pD.y[i], pD.z[j+1]);
			glEnd();
		}

		//x = 0
		for(j=z; j<iz-1; j++)
			for(i=y; i<iy-1; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[(j*iy+i)*ix]);
			glVertex3f(pD.x[0], pD.y[i], pD.z[j]);
			ColorLevel(pD.w[(j*iy+i+1)*ix]);
			glVertex3f(pD.x[0], pD.y[i+1], pD.z[j]);
			ColorLevel(pD.w[((j+1)*iy+i+1)*ix]);
			glVertex3f(pD.x[0], pD.y[i+1], pD.z[j+1]);
			ColorLevel(pD.w[((j+1)*iy+i)*ix]);
			glVertex3f(pD.x[0], pD.y[i], pD.z[j+1]);
			glEnd();
		}

		// left: y==y
		for(j=z; j<iz-1; j++)
			for(i=0; i<x; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[(j*iy+y)*ix+i]);
			glVertex3f(pD.x[i], pD.y[y], pD.z[j]);
			ColorLevel(pD.w[(j*iy+y)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[y], pD.z[j]);
			ColorLevel(pD.w[((j+1)*iy+y)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[y], pD.z[j+1]);
			ColorLevel(pD.w[((j+1)*iy+y)*ix+i]);
			glVertex3f(pD.x[i], pD.y[y], pD.z[j+1]);
			glEnd();
		}

		// y = max
		for(j=z; j<iz-1; j++)
			for(i=0; i<x; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[(j*iy+iy-1)*ix+i]);
			glVertex3f(pD.x[i], pD.y[iy-1], pD.z[j]);
			ColorLevel(pD.w[(j*iy+iy-1)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[iy-1], pD.z[j]);
			ColorLevel(pD.w[((j+1)*iy+iy-1)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[iy-1], pD.z[j+1]);
			ColorLevel(pD.w[((j+1)*iy+iy-1)*ix+i]);
			glVertex3f(pD.x[i], pD.y[iy-1], pD.z[j+1]);
			glEnd();
		}

		// z = z;
		int m = z * iy;
		for(j=y; j<iy-1; j++)
			for(i=0; i<x; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[(m+j)*ix+i]);
			glVertex3f(pD.x[i], pD.y[j], pD.z[z]);
			ColorLevel(pD.w[(m+j)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[j], pD.z[z]);
			ColorLevel(pD.w[(m+j+1)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[j+1], pD.z[z]);
			ColorLevel(pD.w[(m+j+1)*ix+i]);
			glVertex3f(pD.x[i], pD.y[j+1], pD.z[z]);
			glEnd();
		}

		// z = z;
		m = (iz - 1) * iy;
		for(j=y; j<iy-1; j++)
			for(i=0; i<x; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[(m+j)*ix+i]);
			glVertex3f(pD.x[i], pD.y[j], pD.z[iz-1]);
			ColorLevel(pD.w[(m+j)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[j], pD.z[iz-1]);
			ColorLevel(pD.w[(m+j+1)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[j+1], pD.z[iz-1]);
			ColorLevel(pD.w[(m+j+1)*ix+i]);
			glVertex3f(pD.x[i], pD.y[j+1], pD.z[iz-1]);
			glEnd();
		}

		// draw cut lines
		float xp = pD.x[x];// + delta;
		float yp = pD.y[y];// + delta;
		float zp = pD.z[z];// + delta;

		glColor3f(1.0f - m_p4D->m_BackCr.r, 1.0f - m_p4D->m_BackCr.g, 1.0f - m_p4D->m_BackCr.b);
		Draw3DLine(xp, yp, zp, xp, yp, pD.z[iz-1]);
		Draw3DLine(pD.x[0], yp, zp, pD.x[0], yp, pD.z[iz-1]);
		Draw3DLine(xp, pD.y[iy-1], pD.z[iz-1], xp, pD.y[iy-1], zp);

		glBegin(GL_LINE_LOOP);
		glVertex3f(xp, yp, zp);
		glVertex3f(pD.x[0], yp, zp);
		glVertex3f(pD.x[0], pD.y[iy-1], zp);
		glVertex3f(xp, pD.y[iy-1], zp);
		glEnd();


		Draw3DLine(xp, yp, pD.z[iz-1], pD.x[0], yp, pD.z[iz-1]);
		Draw3DLine(xp, yp, pD.z[iz-1], xp, pD.y[iy-1], pD.z[iz-1]);

		m_p4D->ySE = iy - m_p4D->ySE;
		m_p4D->zSE = iz - m_p4D->zSE;
	}

	void COpenGL4D::BlockxTopFrontLeftCorner(int ix, int iy, int iz)
	{
		m_p4D->xSE = ix - m_p4D->xSE;
		m_p4D->zSE = iz - m_p4D->zSE;
		int x = m_p4D->xSE - 1;
		int y = m_p4D->ySE;
		int z = m_p4D->zSE - 1;
		int j = 0, i = 0;


		// back: x==x
		for(j=z; j<iz-1; j++)
			for(i=0; i<y; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[(j*iy+i)*ix+x]);
			glVertex3f(pD.x[x], pD.y[i], pD.z[j]);
			ColorLevel(pD.w[(j*iy+i+1)*ix+x]);
			glVertex3f(pD.x[x], pD.y[i+1], pD.z[j]);
			ColorLevel(pD.w[((j+1)*iy+i+1)*ix+x]);
			glVertex3f(pD.x[x], pD.y[i+1], pD.z[j+1]);
			ColorLevel(pD.w[((j+1)*iy+i)*ix+x]);
			glVertex3f(pD.x[x], pD.y[i], pD.z[j+1]);
			glEnd();
		}

		//x = max
		for(j=z; j<iz-1; j++)
			for(i=0; i<y; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[(j*iy+i+1)*ix-1]);
			glVertex3f(pD.x[ix-1], pD.y[i], pD.z[j]);
			ColorLevel(pD.w[(j*iy+i+2)*ix-1]);
			glVertex3f(pD.x[ix-1], pD.y[i+1], pD.z[j]);
			ColorLevel(pD.w[((j+1)*iy+i+2)*ix-1]);
			glVertex3f(pD.x[ix-1], pD.y[i+1], pD.z[j+1]);
			ColorLevel(pD.w[((j+1)*iy+i+1)*ix-1]);
			glVertex3f(pD.x[ix-1], pD.y[i], pD.z[j+1]);
			glEnd();
		}

		// left: y==y
		for(j=z; j<iz-1; j++)
			for(i=x; i<ix-1; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[(j*iy+y)*ix+i]);
			glVertex3f(pD.x[i], pD.y[y], pD.z[j]);
			ColorLevel(pD.w[(j*iy+y)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[y], pD.z[j]);
			ColorLevel(pD.w[((j+1)*iy+y)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[y], pD.z[j+1]);
			ColorLevel(pD.w[((j+1)*iy+y)*ix+i]);
			glVertex3f(pD.x[i], pD.y[y], pD.z[j+1]);
			glEnd();
		}

		// y = 0
		for(j=z; j<iz-1; j++)
			for(i=x; i<ix-1; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[(j*iy)*ix+i]);
			glVertex3f(pD.x[i], pD.y[0], pD.z[j]);
			ColorLevel(pD.w[(j*iy)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[0], pD.z[j]);
			ColorLevel(pD.w[((j+1)*iy)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[0], pD.z[j+1]);
			ColorLevel(pD.w[((j+1)*iy)*ix+i]);
			glVertex3f(pD.x[i], pD.y[0], pD.z[j+1]);
			glEnd();
		}

		// z = z;
		int m = z * iy;
		for(j=0; j<y; j++)
			for(i=x; i<ix-1; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[(m+j)*ix+i]);
			glVertex3f(pD.x[i], pD.y[j], pD.z[z]);
			ColorLevel(pD.w[(m+j)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[j], pD.z[z]);
			ColorLevel(pD.w[(m+j+1)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[j+1], pD.z[z]);
			ColorLevel(pD.w[(m+j+1)*ix+i]);
			glVertex3f(pD.x[i], pD.y[j+1], pD.z[z]);
			glEnd();
		}

		// z = max;
		m = (iz - 1) * iy;
		for(j=0; j<y; j++)
			for(i=x; i<ix-1; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[(m+j)*ix+i]);
			glVertex3f(pD.x[i], pD.y[j], pD.z[iz-1]);
			ColorLevel(pD.w[(m+j)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[j], pD.z[iz-1]);
			ColorLevel(pD.w[(m+j+1)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[j+1], pD.z[iz-1]);
			ColorLevel(pD.w[(m+j+1)*ix+i]);
			glVertex3f(pD.x[i], pD.y[j+1], pD.z[iz-1]);
			glEnd();
		}

		// draw cut lines
		float xp = pD.x[x];// + delta;
		float yp = pD.y[y];// + delta;
		float zp = pD.z[z];// + delta;

		glColor3f(1.0f - m_p4D->m_BackCr.r, 1.0f - m_p4D->m_BackCr.g, 1.0f - m_p4D->m_BackCr.b);
		Draw3DLine(xp, yp, zp, xp, yp, pD.z[iz-1]);
		Draw3DLine(pD.x[ix-1], yp, zp, pD.x[ix-1], yp, pD.z[iz-1]);
		Draw3DLine(xp, pD.y[0], pD.z[iz-1], xp, pD.y[0], zp);

		glBegin(GL_LINE_LOOP);
		glVertex3f(xp, yp, zp);
		glVertex3f(pD.x[ix-1], yp, zp);
		glVertex3f(pD.x[ix-1], pD.y[0], zp);
		glVertex3f(xp, pD.y[0], zp);
		glEnd();


		Draw3DLine(xp, yp, pD.z[iz-1], pD.x[ix-1], yp, pD.z[iz-1]);
		Draw3DLine(xp, yp, pD.z[iz-1], xp, pD.y[0], pD.z[iz-1]);

		m_p4D->xSE = ix - m_p4D->xSE;
		m_p4D->zSE = iz - m_p4D->zSE;
	}

	void COpenGL4D::BlockxTopBackLeftCorner(int ix, int iy, int iz)
	{
		m_p4D->zSE = iz - m_p4D->zSE;
		int x = m_p4D->xSE;
		int y = m_p4D->ySE;
		int z = m_p4D->zSE - 1;
		int j = 0, i = 0;


		// back: x==x
		for(j=z; j<iz-1; j++)
			for(i=0; i<y; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[(j*iy+i)*ix+x]);
			glVertex3f(pD.x[x], pD.y[i], pD.z[j]);
			ColorLevel(pD.w[(j*iy+i+1)*ix+x]);
			glVertex3f(pD.x[x], pD.y[i+1], pD.z[j]);
			ColorLevel(pD.w[((j+1)*iy+i+1)*ix+x]);
			glVertex3f(pD.x[x], pD.y[i+1], pD.z[j+1]);
			ColorLevel(pD.w[((j+1)*iy+i)*ix+x]);
			glVertex3f(pD.x[x], pD.y[i], pD.z[j+1]);
			glEnd();
		}

		//x = 0
		for(j=z; j<iz-1; j++)
			for(i=0; i<y; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[(j*iy+i)*ix]);
			glVertex3f(pD.x[0], pD.y[i], pD.z[j]);
			ColorLevel(pD.w[(j*iy+i+1)*ix]);
			glVertex3f(pD.x[0], pD.y[i+1], pD.z[j]);
			ColorLevel(pD.w[((j+1)*iy+i+1)*ix]);
			glVertex3f(pD.x[0], pD.y[i+1], pD.z[j+1]);
			ColorLevel(pD.w[((j+1)*iy+i)*ix]);
			glVertex3f(pD.x[0], pD.y[i], pD.z[j+1]);
			glEnd();
		}

		// left: y==y
		for(j=z; j<iz-1; j++)
			for(i=0; i<x; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[(j*iy+y)*ix+i]);
			glVertex3f(pD.x[i], pD.y[y], pD.z[j]);
			ColorLevel(pD.w[(j*iy+y)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[y], pD.z[j]);
			ColorLevel(pD.w[((j+1)*iy+y)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[y], pD.z[j+1]);
			ColorLevel(pD.w[((j+1)*iy+y)*ix+i]);
			glVertex3f(pD.x[i], pD.y[y], pD.z[j+1]);
			glEnd();
		}

		// y = 0
		for(j=z; j<iz-1; j++)
			for(i=0; i<x; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[j*iy*ix+i]);
			glVertex3f(pD.x[i], pD.y[0], pD.z[j]);
			ColorLevel(pD.w[j*iy*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[0], pD.z[j]);
			ColorLevel(pD.w[(j+1)*iy*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[0], pD.z[j+1]);
			ColorLevel(pD.w[(j+1)*iy*ix+i]);
			glVertex3f(pD.x[i], pD.y[0], pD.z[j+1]);
			glEnd();
		}

		// z = z;
		int m = z * iy;
		for(j=0; j<y; j++)
			for(i=0; i<x; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[(m+j)*ix+i]);
			glVertex3f(pD.x[i], pD.y[j], pD.z[z]);
			ColorLevel(pD.w[(m+j)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[j], pD.z[z]);
			ColorLevel(pD.w[(m+j+1)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[j+1], pD.z[z]);
			ColorLevel(pD.w[(m+j+1)*ix+i]);
			glVertex3f(pD.x[i], pD.y[j+1], pD.z[z]);
			glEnd();
		}

		// z = max;
		m = (iz - 1) * iy;
		for(j=0; j<y; j++)
			for(i=0; i<x; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[(m+j)*ix+i]);
			glVertex3f(pD.x[i], pD.y[j], pD.z[iz-1]);
			ColorLevel(pD.w[(m+j)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[j], pD.z[iz-1]);
			ColorLevel(pD.w[(m+j+1)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[j+1], pD.z[iz-1]);
			ColorLevel(pD.w[(m+j+1)*ix+i]);
			glVertex3f(pD.x[i], pD.y[j+1], pD.z[iz-1]);
			glEnd();
		}

		// draw cut lines
		float xp = pD.x[x];// + delta;
		float yp = pD.y[y];// + delta;
		float zp = pD.z[z];// + delta;

		glColor3f(1.0f - m_p4D->m_BackCr.r, 1.0f - m_p4D->m_BackCr.g, 1.0f - m_p4D->m_BackCr.b);
		Draw3DLine(xp, yp, zp, xp, yp, pD.z[iz-1]);
		Draw3DLine(pD.x[0], yp, zp, pD.x[0], yp, pD.z[iz-1]);
		Draw3DLine(xp, pD.y[0], pD.z[iz-1], xp, pD.y[0], zp);

		glBegin(GL_LINE_LOOP);
		glVertex3f(xp, yp, zp);
		glVertex3f(pD.x[0], yp, zp);
		glVertex3f(pD.x[0], pD.y[0], zp);
		glVertex3f(xp, pD.y[0], zp);
		glEnd();


		Draw3DLine(xp, yp, pD.z[iz-1], pD.x[0], yp, pD.z[iz-1]);
		Draw3DLine(xp, yp, pD.z[iz-1], xp, pD.y[0], pD.z[iz-1]);

		m_p4D->zSE = iz - m_p4D->zSE;
	}

	void COpenGL4D::BlockxBottomFrontRightCorner(int ix, int iy, int iz)
	{
		m_p4D->xSE = ix - m_p4D->xSE;
		m_p4D->ySE = iy - m_p4D->ySE;
		int x = m_p4D->xSE-1;
		int y = m_p4D->ySE-1;
		int z = m_p4D->zSE;
		int j = 0, i = 0;


		// back: x==x
		for(j=0; j<z; j++)
			for(i=y; i<iy-1; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[(j*iy+i)*ix+x]);
			glVertex3f(pD.x[x], pD.y[i], pD.z[j]);
			ColorLevel(pD.w[(j*iy+i+1)*ix+x]);
			glVertex3f(pD.x[x], pD.y[i+1], pD.z[j]);
			ColorLevel(pD.w[((j+1)*iy+i+1)*ix+x]);
			glVertex3f(pD.x[x], pD.y[i+1], pD.z[j+1]);
			ColorLevel(pD.w[((j+1)*iy+i)*ix+x]);
			glVertex3f(pD.x[x], pD.y[i], pD.z[j+1]);
			glEnd();
		}

		//x = max
		for(j=0; j<z; j++)
			for(i=y; i<iy-1; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[(j*iy+i+1)*ix-1]);
			glVertex3f(pD.x[ix-1], pD.y[i], pD.z[j]);
			ColorLevel(pD.w[(j*iy+i+2)*ix-1]);
			glVertex3f(pD.x[ix-1], pD.y[i+1], pD.z[j]);
			ColorLevel(pD.w[((j+1)*iy+i+2)*ix-1]);
			glVertex3f(pD.x[ix-1], pD.y[i+1], pD.z[j+1]);
			ColorLevel(pD.w[((j+1)*iy+i+1)*ix-1]);
			glVertex3f(pD.x[ix-1], pD.y[i], pD.z[j+1]);
			glEnd();
		}

		// left: y==y
		for(j=0; j<z; j++)
			for(i=x; i<ix-1; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[(j*iy+y)*ix+i]);
			glVertex3f(pD.x[i], pD.y[y], pD.z[j]);
			ColorLevel(pD.w[(j*iy+y)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[y], pD.z[j]);
			ColorLevel(pD.w[((j+1)*iy+y)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[y], pD.z[j+1]);
			ColorLevel(pD.w[((j+1)*iy+y)*ix+i]);
			glVertex3f(pD.x[i], pD.y[y], pD.z[j+1]);
			glEnd();
		}

		// y = max
		for(j=0; j<z; j++)
			for(i=x; i<ix-1; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[(j*iy+iy-1)*ix+i]);
			glVertex3f(pD.x[i], pD.y[iy-1], pD.z[j]);
			ColorLevel(pD.w[(j*iy+iy-1)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[iy-1], pD.z[j]);
			ColorLevel(pD.w[((j+1)*iy+iy-1)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[iy-1], pD.z[j+1]);
			ColorLevel(pD.w[((j+1)*iy+iy-1)*ix+i]);
			glVertex3f(pD.x[i], pD.y[iy-1], pD.z[j+1]);
			glEnd();
		}

		// z = z;
		int m = z * iy;
		for(j=y; j<iy-1; j++)
			for(i=x; i<ix-1; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[(m+j)*ix+i]);
			glVertex3f(pD.x[i], pD.y[j], pD.z[z]);
			ColorLevel(pD.w[(m+j)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[j], pD.z[z]);
			ColorLevel(pD.w[(m+j+1)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[j+1], pD.z[z]);
			ColorLevel(pD.w[(m+j+1)*ix+i]);
			glVertex3f(pD.x[i], pD.y[j+1], pD.z[z]);
			glEnd();
		}

		// z = 0;
		for(j=y; j<iy-1; j++)
			for(i=x; i<ix-1; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[j*ix+i]);
			glVertex3f(pD.x[i], pD.y[j], pD.z[0]);
			ColorLevel(pD.w[j*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[j], pD.z[0]);
			ColorLevel(pD.w[(j+1)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[j+1], pD.z[0]);
			ColorLevel(pD.w[(j+1)*ix+i]);
			glVertex3f(pD.x[i], pD.y[j+1], pD.z[0]);
			glEnd();
		}

		// draw cut lines
		float xp = pD.x[x];// + delta;
		float yp = pD.y[y];// + delta;
		float zp = pD.z[z];// + delta;

		glColor3f(1.0f - m_p4D->m_BackCr.r, 1.0f - m_p4D->m_BackCr.g, 1.0f - m_p4D->m_BackCr.b);
		Draw3DLine(xp, yp, zp, xp, yp, pD.z[0]);
		Draw3DLine(pD.x[ix-1], yp, zp, pD.x[ix-1], yp, pD.z[0]);
		Draw3DLine(xp, pD.y[iy-1], pD.z[0], xp, pD.y[iy-1], zp);

		glBegin(GL_LINE_LOOP);
		glVertex3f(xp, yp, zp);
		glVertex3f(pD.x[ix-1], yp, zp);
		glVertex3f(pD.x[ix-1], pD.y[iy-1], zp);
		glVertex3f(xp, pD.y[iy-1], zp);
		glEnd();


		Draw3DLine(xp, yp, pD.z[0], pD.x[ix-1], yp, pD.z[0]);
		Draw3DLine(xp, yp, pD.z[0], xp, pD.y[iy-1], pD.z[0]);

		m_p4D->xSE = ix - m_p4D->xSE;
		m_p4D->ySE = iy - m_p4D->ySE;

		iz = 0;
	}

	void COpenGL4D::BlockxBottomBackRightCorner(int ix, int iy, int iz)
	{
		m_p4D->ySE = iy - m_p4D->ySE;
		int x = m_p4D->xSE;
		int y = m_p4D->ySE-1;
		int z = m_p4D->zSE;
		int j = 0, i = 0;


		// back: x==x
		for(j=0; j<z; j++)
			for(i=y; i<iy-1; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[(j*iy+i)*ix+x]);
			glVertex3f(pD.x[x], pD.y[i], pD.z[j]);
			ColorLevel(pD.w[(j*iy+i+1)*ix+x]);
			glVertex3f(pD.x[x], pD.y[i+1], pD.z[j]);
			ColorLevel(pD.w[((j+1)*iy+i+1)*ix+x]);
			glVertex3f(pD.x[x], pD.y[i+1], pD.z[j+1]);
			ColorLevel(pD.w[((j+1)*iy+i)*ix+x]);
			glVertex3f(pD.x[x], pD.y[i], pD.z[j+1]);
			glEnd();
		}

		//x = 0
		for(j=0; j<z; j++)
			for(i=y; i<iy-1; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[(j*iy+i)*ix]);
			glVertex3f(pD.x[0], pD.y[i], pD.z[j]);
			ColorLevel(pD.w[(j*iy+i+1)*ix]);
			glVertex3f(pD.x[0], pD.y[i+1], pD.z[j]);
			ColorLevel(pD.w[((j+1)*iy+i+1)*ix]);
			glVertex3f(pD.x[0], pD.y[i+1], pD.z[j+1]);
			ColorLevel(pD.w[((j+1)*iy+i)*ix]);
			glVertex3f(pD.x[0], pD.y[i], pD.z[j+1]);
			glEnd();
		}

		// left: y==y
		for(j=0; j<z; j++)
			for(i=0; i<x; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[(j*iy+y)*ix+i]);
			glVertex3f(pD.x[i], pD.y[y], pD.z[j]);
			ColorLevel(pD.w[(j*iy+y)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[y], pD.z[j]);
			ColorLevel(pD.w[((j+1)*iy+y)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[y], pD.z[j+1]);
			ColorLevel(pD.w[((j+1)*iy+y)*ix+i]);
			glVertex3f(pD.x[i], pD.y[y], pD.z[j+1]);
			glEnd();
		}

		// y = max
		for(j=0; j<z; j++)
			for(i=0; i<x; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[(j*iy+iy-1)*ix+i]);
			glVertex3f(pD.x[i], pD.y[iy-1], pD.z[j]);
			ColorLevel(pD.w[(j*iy+iy-1)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[iy-1], pD.z[j]);
			ColorLevel(pD.w[((j+1)*iy+iy-1)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[iy-1], pD.z[j+1]);
			ColorLevel(pD.w[((j+1)*iy+iy-1)*ix+i]);
			glVertex3f(pD.x[i], pD.y[iy-1], pD.z[j+1]);
			glEnd();
		}

		// z = z;
		int m = z * iy;
		for(j=y; j<iy-1; j++)
			for(i=0; i<x; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[(m+j)*ix+i]);
			glVertex3f(pD.x[i], pD.y[j], pD.z[z]);
			ColorLevel(pD.w[(m+j)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[j], pD.z[z]);
			ColorLevel(pD.w[(m+j+1)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[j+1], pD.z[z]);
			ColorLevel(pD.w[(m+j+1)*ix+i]);
			glVertex3f(pD.x[i], pD.y[j+1], pD.z[z]);
			glEnd();
		}

		// z = 0;
		for(j=y; j<iy-1; j++)
			for(i=0; i<x; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[j*ix+i]);
			glVertex3f(pD.x[i], pD.y[j], pD.z[0]);
			ColorLevel(pD.w[j*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[j], pD.z[0]);
			ColorLevel(pD.w[(j+1)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[j+1], pD.z[0]);
			ColorLevel(pD.w[(j+1)*ix+i]);
			glVertex3f(pD.x[i], pD.y[j+1], pD.z[0]);
			glEnd();
		}

		// draw cut lines
		float xp = pD.x[x];// + delta;
		float yp = pD.y[y];// + delta;
		float zp = pD.z[z];// + delta;

		glColor3f(1.0f - m_p4D->m_BackCr.r, 1.0f - m_p4D->m_BackCr.g, 1.0f - m_p4D->m_BackCr.b);
		Draw3DLine(xp, yp, zp, xp, yp, pD.z[0]);
		Draw3DLine(pD.x[0], yp, zp, pD.x[0], yp, pD.z[0]);
		Draw3DLine(xp, pD.y[iy-1], pD.z[0], xp, pD.y[iy-1], zp);

		glBegin(GL_LINE_LOOP);
		glVertex3f(xp, yp, zp);
		glVertex3f(pD.x[0], yp, zp);
		glVertex3f(pD.x[0], pD.y[iy-1], zp);
		glVertex3f(xp, pD.y[iy-1], zp);
		glEnd();


		Draw3DLine(xp, yp, pD.z[0], pD.x[0], yp, pD.z[0]);
		Draw3DLine(xp, yp, pD.z[0], xp, pD.y[iy-1], pD.z[0]);

		m_p4D->ySE = iy - m_p4D->ySE;

		iz = 0;
	}

	void COpenGL4D::BlockxBottomFrontLeftCorner(int ix, int iy, int iz)
	{
		m_p4D->xSE = ix - m_p4D->xSE;
		int x = m_p4D->xSE - 1;
		int y = m_p4D->ySE;
		int z = m_p4D->zSE;
		int j = 0, i = 0;


		// back: x==x
		for(j=0; j<z; j++)
			for(i=0; i<y; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[(j*iy+i)*ix+x]);
			glVertex3f(pD.x[x], pD.y[i], pD.z[j]);
			ColorLevel(pD.w[(j*iy+i+1)*ix+x]);
			glVertex3f(pD.x[x], pD.y[i+1], pD.z[j]);
			ColorLevel(pD.w[((j+1)*iy+i+1)*ix+x]);
			glVertex3f(pD.x[x], pD.y[i+1], pD.z[j+1]);
			ColorLevel(pD.w[((j+1)*iy+i)*ix+x]);
			glVertex3f(pD.x[x], pD.y[i], pD.z[j+1]);
			glEnd();
		}

		//x = max
		for(j=0; j<z; j++)
			for(i=0; i<y; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[(j*iy+i+1)*ix-1]);
			glVertex3f(pD.x[ix-1], pD.y[i], pD.z[j]);
			ColorLevel(pD.w[(j*iy+i+2)*ix-1]);
			glVertex3f(pD.x[ix-1], pD.y[i+1], pD.z[j]);
			ColorLevel(pD.w[((j+1)*iy+i+2)*ix-1]);
			glVertex3f(pD.x[ix-1], pD.y[i+1], pD.z[j+1]);
			ColorLevel(pD.w[((j+1)*iy+i+1)*ix-1]);
			glVertex3f(pD.x[ix-1], pD.y[i], pD.z[j+1]);
			glEnd();
		}

		// left: y==y
		for(j=0; j<z; j++)
			for(i=x; i<ix-1; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[(j*iy+y)*ix+i]);
			glVertex3f(pD.x[i], pD.y[y], pD.z[j]);
			ColorLevel(pD.w[(j*iy+y)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[y], pD.z[j]);
			ColorLevel(pD.w[((j+1)*iy+y)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[y], pD.z[j+1]);
			ColorLevel(pD.w[((j+1)*iy+y)*ix+i]);
			glVertex3f(pD.x[i], pD.y[y], pD.z[j+1]);
			glEnd();
		}

		// y = 0
		for(j=0; j<z; j++)
			for(i=x; i<ix-1; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[(j*iy)*ix+i]);
			glVertex3f(pD.x[i], pD.y[0], pD.z[j]);
			ColorLevel(pD.w[(j*iy)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[0], pD.z[j]);
			ColorLevel(pD.w[((j+1)*iy)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[0], pD.z[j+1]);
			ColorLevel(pD.w[((j+1)*iy)*ix+i]);
			glVertex3f(pD.x[i], pD.y[0], pD.z[j+1]);
			glEnd();
		}

		// z = z;
		int m = z * iy;
		for(j=0; j<y; j++)
			for(i=x; i<ix-1; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[(m+j)*ix+i]);
			glVertex3f(pD.x[i], pD.y[j], pD.z[z]);
			ColorLevel(pD.w[(m+j)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[j], pD.z[z]);
			ColorLevel(pD.w[(m+j+1)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[j+1], pD.z[z]);
			ColorLevel(pD.w[(m+j+1)*ix+i]);
			glVertex3f(pD.x[i], pD.y[j+1], pD.z[z]);
			glEnd();
		}

		// z = 0;
		for(j=0; j<y; j++)
			for(i=x; i<ix-1; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[j*ix+i]);
			glVertex3f(pD.x[i], pD.y[j], pD.z[0]);
			ColorLevel(pD.w[j*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[j], pD.z[0]);
			ColorLevel(pD.w[(j+1)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[j+1], pD.z[0]);
			ColorLevel(pD.w[(j+1)*ix+i]);
			glVertex3f(pD.x[i], pD.y[j+1], pD.z[0]);
			glEnd();
		}

		// draw cut lines
		float xp = pD.x[x];// + delta;
		float yp = pD.y[y];// + delta;
		float zp = pD.z[z];// + delta;

		glColor3f(1.0f - m_p4D->m_BackCr.r, 1.0f - m_p4D->m_BackCr.g, 1.0f - m_p4D->m_BackCr.b);
		Draw3DLine(xp, yp, zp, xp, yp, pD.z[0]);
		Draw3DLine(pD.x[ix-1], yp, zp, pD.x[ix-1], yp, pD.z[0]);
		Draw3DLine(xp, pD.y[0], pD.z[0], xp, pD.y[0], zp);

		glBegin(GL_LINE_LOOP);
		glVertex3f(xp, yp, zp);
		glVertex3f(pD.x[ix-1], yp, zp);
		glVertex3f(pD.x[ix-1], pD.y[0], zp);
		glVertex3f(xp, pD.y[0], zp);
		glEnd();


		Draw3DLine(xp, yp, pD.z[0], pD.x[ix-1], yp, pD.z[0]);
		Draw3DLine(xp, yp, pD.z[0], xp, pD.y[0], pD.z[0]);

		m_p4D->xSE = ix - m_p4D->xSE;

		iz = 0;
	}

	void COpenGL4D::BlockxBottomBackLeftCorner(int ix, int iy, int iz)
	{
		int x = m_p4D->xSE;
		int y = m_p4D->ySE;
		int z = m_p4D->zSE;
		int j = 0, i = 0;


		// back: x==x
		for(j=0; j<z; j++)
			for(i=0; i<y; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[(j*iy+i)*ix+x]);
			glVertex3f(pD.x[x], pD.y[i], pD.z[j]);
			ColorLevel(pD.w[(j*iy+i+1)*ix+x]);
			glVertex3f(pD.x[x], pD.y[i+1], pD.z[j]);
			ColorLevel(pD.w[((j+1)*iy+i+1)*ix+x]);
			glVertex3f(pD.x[x], pD.y[i+1], pD.z[j+1]);
			ColorLevel(pD.w[((j+1)*iy+i)*ix+x]);
			glVertex3f(pD.x[x], pD.y[i], pD.z[j+1]);
			glEnd();
		}

		//x = 0
		for(j=0; j<z; j++)
			for(i=0; i<y; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[(j*iy+i)*ix]);
			glVertex3f(pD.x[0], pD.y[i], pD.z[j]);
			ColorLevel(pD.w[(j*iy+i+1)*ix]);
			glVertex3f(pD.x[0], pD.y[i+1], pD.z[j]);
			ColorLevel(pD.w[((j+1)*iy+i+1)*ix]);
			glVertex3f(pD.x[0], pD.y[i+1], pD.z[j+1]);
			ColorLevel(pD.w[((j+1)*iy+i)*ix]);
			glVertex3f(pD.x[0], pD.y[i], pD.z[j+1]);
			glEnd();
		}

		// left: y==y
		for(j=0; j<z; j++)
			for(i=0; i<x; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[(j*iy+y)*ix+i]);
			glVertex3f(pD.x[i], pD.y[y], pD.z[j]);
			ColorLevel(pD.w[(j*iy+y)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[y], pD.z[j]);
			ColorLevel(pD.w[((j+1)*iy+y)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[y], pD.z[j+1]);
			ColorLevel(pD.w[((j+1)*iy+y)*ix+i]);
			glVertex3f(pD.x[i], pD.y[y], pD.z[j+1]);
			glEnd();
		}

		// y = 0
		for(j=0; j<z; j++)
			for(i=0; i<x; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[j*iy*ix+i]);
			glVertex3f(pD.x[i], pD.y[0], pD.z[j]);
			ColorLevel(pD.w[j*iy*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[0], pD.z[j]);
			ColorLevel(pD.w[(j+1)*iy*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[0], pD.z[j+1]);
			ColorLevel(pD.w[(j+1)*iy*ix+i]);
			glVertex3f(pD.x[i], pD.y[0], pD.z[j+1]);
			glEnd();
		}

		// z = z;
		int m = z * iy;
		for(j=0; j<y; j++)
			for(i=0; i<x; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[(m+j)*ix+i]);
			glVertex3f(pD.x[i], pD.y[j], pD.z[z]);
			ColorLevel(pD.w[(m+j)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[j], pD.z[z]);
			ColorLevel(pD.w[(m+j+1)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[j+1], pD.z[z]);
			ColorLevel(pD.w[(m+j+1)*ix+i]);
			glVertex3f(pD.x[i], pD.y[j+1], pD.z[z]);
			glEnd();
		}

		// z = max;
		for(j=0; j<y; j++)
			for(i=0; i<x; i++)
		{
			glBegin(GL_QUADS);
			ColorLevel(pD.w[j*ix+i]);
			glVertex3f(pD.x[i], pD.y[j], pD.z[0]);
			ColorLevel(pD.w[j*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[j], pD.z[0]);
			ColorLevel(pD.w[(j+1)*ix+i+1]);
			glVertex3f(pD.x[i+1], pD.y[j+1], pD.z[0]);
			ColorLevel(pD.w[(j+1)*ix+i]);
			glVertex3f(pD.x[i], pD.y[j+1], pD.z[0]);
			glEnd();
		}

		// draw cut lines
		float xp = pD.x[x];// + delta;
		float yp = pD.y[y];// + delta;
		float zp = pD.z[z];// + delta;

		glColor3f(1.0f - m_p4D->m_BackCr.r, 1.0f - m_p4D->m_BackCr.g, 1.0f - m_p4D->m_BackCr.b);
		Draw3DLine(xp, yp, zp, xp, yp, pD.z[0]);
		Draw3DLine(pD.x[0], yp, zp, pD.x[0], yp, pD.z[0]);
		Draw3DLine(xp, pD.y[0], pD.z[0], xp, pD.y[0], zp);

		glBegin(GL_LINE_LOOP);
		glVertex3f(xp, yp, zp);
		glVertex3f(pD.x[0], yp, zp);
		glVertex3f(pD.x[0], pD.y[0], zp);
		glVertex3f(xp, pD.y[0], zp);
		glEnd();

		Draw3DLine(xp, yp, pD.z[0], pD.x[0], yp, pD.z[0]);
		Draw3DLine(xp, yp, pD.z[0], xp, pD.y[0], pD.z[0]);

		iz = 0;
	}
}