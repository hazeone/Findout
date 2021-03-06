//图形学大作业
//by hazeone

#include "stdafx.h"
#include <gl/glut.h>
#include <math.h>


static float angle = 0.0, ratio;//angle绕y轴的旋转角，ratio窗口高宽比
static float x = 0.0f, y = 1.75f, z = 5.0f;//相机位置
static float lx = 0.0f, ly = 0.0f, lz = -1.0f;//视线方向，初始设为沿着Z轴负方向
static GLint object_display_list;//物体显示列表索引

								 //定义观察方式
void changeSize(int w, int h)
{
	//除以0的情况
	if (h == 0)
		h = 1;
	ratio = 1.0f*w / h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//设置视口为整个窗口大小
	glViewport(0, 0, w, h);
	//设置可视空间
	gluPerspective(45, ratio, 1, 1000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(x, y, z, x + lx, y + ly, z + lz, 0.0f, 1.0f, 0.0f);
}

//绘制物体（墙面）
void drawObject()
{
	glColor3f(1.0f, 1.0f, 1.0f);

	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.5f, 0.5f);
	glVertex3f(6.0f, -3.0f, 0.0f);
	glVertex3f(6.0f, 9.0f, 0.0f);
	glVertex3f(6.0f, 9.0f, 5.0f);
	glVertex3f(6.0f, -3.0f, 5.0f);
	glEnd();

}

//定义显示列表
GLuint createDL()
{
	GLuint objectDL;
	//生成一个显示列表号
	objectDL = glGenLists(1);
	//开始显示列表
	glNewList(objectDL, GL_COMPILE);
	drawObject();
	glEndList();
	return (objectDL);
}

//初始化场景
void initScenne()
{
	glEnable(GL_DEPTH_TEST);
	object_display_list = createDL();
}

//渲染场景
void renderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//画地面
	glBegin(GL_QUADS);
	glColor3f(0.4f, 0.5f, 0.4f);
	glVertex3f(-100.0f, 0.0f, -100.0f);
	glVertex3f(-100.0f, 0.0f, 100.0f);
	glVertex3f(100.0f, 0.0f, 100.0f);
	glVertex3f(100.0f, 0.0f, -100.0f);
	glEnd();
	//画36个物体
	for (int i = -3; i< 3; i++)
		for (int j = -3; j< 3; j++) {
			glPushMatrix();
			glTranslatef(i*10.0, 0, j*10.0);
			glCallList(object_display_list);
			glPopMatrix();
		}
	glutSwapBuffers();
}

//旋转相机
void orientMe(float ang)
{
	lx = sin(ang);
	lz = -cos(ang);
	glLoadIdentity();
	gluLookAt(x, y, z, x + lx, y + ly, z + lz, 0.0f, 1.0f, 0.0f);
}

//移动相机
void moveMeFlat(int direction)
{
	x = x + direction * (lx)*0.1;
	z = z + direction * (lz)*0.1;
	glLoadIdentity();
	gluLookAt(x, y, z, x + lx, y + ly, z + lz, 0.0f, 1.0f, 0.0f);
}

//键盘响应
//左右键旋转相机，上下键移动相机
void inputKey(int key, int x, int y) {
	switch (key)
	{
	case GLUT_KEY_LEFT:
		angle -= 0.01f;
		orientMe(angle);
		break;
	case GLUT_KEY_RIGHT:
		angle += 0.01f;
		orientMe(angle);
		break;
	case GLUT_KEY_UP:
		moveMeFlat(1);
		break;
	case GLUT_KEY_DOWN:
		moveMeFlat(-1);
		break;
	default:
		break;
	}
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(640, 360);
	glutCreateWindow("Maze test");

	initScenne();
	glutSpecialFunc(inputKey);
	glutDisplayFunc(renderScene);
	glutIdleFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutMainLoop();

	return 0;
}
