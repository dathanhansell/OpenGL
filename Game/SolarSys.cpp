#include "stdafx.h"
#include <MGLE.h>
#include "SolarSys.h"
using namespace MGLE;
	Sys::Sys(Game* g) {
		m_g = g;
	}
	
	void Sys::Planet(float rad, float radfromsun, float speed, Vector3 color) {
		Vector3 pos;
		pos = { (float)sin(c*(speed * M_PI)) , 0,(float)cos(c*(speed * M_PI)) };
		pos *= radfromsun;
		Debug::DrawWireCircle(Vector3::zero, radfromsun, color, 128);
		Debug::DrawWireSphere(pos, rad, color);
		Debug::DrawWireBox(pos, { rad,rad,rad }, color);
	}

	void Sys::Run() {
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		w = m_g->graphics->window->GetWidth();
		h = m_g->graphics->window->GetHeight();
		c += .0016;
		glPushMatrix();
		pos = { (float)sin(c*(2 * M_PI)) , (float)sin(c*.5f *M_PI) ,(float)cos(c*(2 * M_PI))*(float)sin(c*(2 * M_PI)) };
		pos *= 30000;
		pos.y += 400;
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glViewport(0, 0, w,h );
		//glOrtho(-pos.y, pos.y, -pos.y, pos.y, .1, 200000);
		gluPerspective(90, (GLfloat) w/ h, 0.1, 200000);
		glMatrixMode(GL_MODELVIEW);

		gluLookAt(pos.x, pos.y, pos.z, 0, 0, 0, 0, 1, 0);
		//gluLookAt(0, pos.y, 0, 0, 0, 0, 0, 0, 1);
		Debug::DrawWireSphere(Vector3::zero, 40);
		Planet(50, 360, 8, { .4f,.4f,.4f });
		Planet(100, 672, 7, { .7f,.7f,.2f });
		Planet(100, 930, 6, { .2f,.2f,.8f });
		Planet(80, 1496, 5, { .8f,.2f,.1f });
		Planet(500, 4836, 4, { 1,.5f,.2f });
		Planet(470, 8867, 3, { .6f,.5f,.2f });
		Planet(400, 17840, 2, { .2f,.2f,.6f });
		Planet(410, 27944, 1, { .3f,.4f,.8f });

		glPopMatrix();
	}
