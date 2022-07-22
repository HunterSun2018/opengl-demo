#pragma execution_character_set("utf-8")
#define GLUT_DISABLE_ATEXIT_HACK
#include <GL/glut.h>
#include <glm/glm.hpp>

#define RADIUS 50.0f
#define SIZE 100.0f

#define CONE 1
#define TETRAHEDRON 2
#define CUBE 3
#define DODECAHEDRON 4
#define ICONSAHEDRON 5
#define OCTAHEDRON 6
#define SPHERE 7
#define TOURUS 8
#define TEAPOT 9
#define WIRED 10

GLboolean bWire = false;
GLint nSelected = CONE;

void OnDisplay(void);
void OnReshape(int, int);
void OnMenu(int value);
void CreateMenu();
void SetupLights();

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);                                    //初始化OpenGL
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); //设置显示模式
    glutInitWindowSize(1280*2, 768*2);
    glutCreateWindow("GLUT提供的9种实体对象");

    glutCreateMenu(OnMenu);
    glutReshapeFunc(OnReshape);
    glutDisplayFunc(OnDisplay);
    glutIdleFunc(OnDisplay);

    CreateMenu();  //实际生成菜单
    SetupLights(); //设置光照

    glutMainLoop(); //进入OpenGL主循环
}

void OnDisplay(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_DEPTH_TEST); //使能深度检测

    glPushMatrix();
    glMatrixMode(GL_MODELVIEW);

    static GLfloat angle = 1;
    glRotatef(angle++, 0, 1, 0);

    glColor3f(1.0f, 0.0f, 0.0f);

    glEnable(GL_NORMALIZE); //归一化法向量
    switch (nSelected)
    {
    case (CONE): //圆锥体
        if (bWire)
            glutWireCone(RADIUS, 2 * RADIUS, 30, 30);
        else
            glutSolidCone(RADIUS, 2 * RADIUS, 30, 30);
        break;

    case (TETRAHEDRON): //四面体
        glPushMatrix();
        glScalef(RADIUS, RADIUS, RADIUS);
        if (bWire)
            glutWireTetrahedron();
        else
            glutSolidTetrahedron();
        glPopMatrix();
        break;

    case (CUBE): //正方体
        if (bWire)
            glutWireCube(1.5 * RADIUS);
        else
            glutSolidCube(1.5 * RADIUS);
        break;

    case (DODECAHEDRON): //正十二面体
        glPushMatrix();
        glScalef(RADIUS / 2, RADIUS / 2, RADIUS / 2);
        if (bWire)
            glutWireDodecahedron();
        else
            glutSolidDodecahedron();
        glPopMatrix();
        break;

    case (ICONSAHEDRON): //正八面体
        glPushMatrix();
        glScalef(RADIUS, RADIUS, RADIUS);
        if (bWire)
            glutWireIcosahedron();
        else
            glutSolidIcosahedron();
        glPopMatrix();
        break;

    case (OCTAHEDRON): 
        glPushMatrix();
        glScalef(RADIUS, RADIUS, RADIUS);
        if (bWire)
            glutWireOctahedron();
        else
            glutSolidOctahedron();
        glPopMatrix();
        break;

    case (SPHERE):  //球体
        if (bWire)
            glutWireSphere(RADIUS, 30, 30);
        else
            glutSolidSphere(RADIUS, 30, 30);
        break;

    case (TOURUS): //圆环体
        if (bWire)
            glutWireTorus(RADIUS / 2, RADIUS, 30, 30);
        else
            glutSolidTorus(RADIUS / 2, RADIUS, 30, 30);
        break;

    case (TEAPOT): // 茶壶
        if (bWire)
            glutWireTeapot(RADIUS);
        else
            glutSolidTeapot(RADIUS);
    }

    glPopMatrix();
    glutSwapBuffers();
}

void OnReshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);

    float aspect = (float)h / (float)w;

    // if (w <= h)
    //     glOrtho(-SIZE, SIZE, -SIZE * aspect, SIZE * aspect, -SIZE, SIZE);
    // else
    //     glOrtho(-SIZE / aspect, SIZE / aspect, -SIZE, SIZE, -SIZE, SIZE);

    // gluLookAt(10.0f, 20.0f, 25.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

    gluPerspective(90, (GLfloat)w / h, 0.1f, 1000.0f);

    gluLookAt(0.0f, 50.0f, 200.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
}

void OnMenu(int value)
{
    if (value == WIRED)
        bWire = !bWire;
    else
        nSelected = value;

    glutPostRedisplay();
}

void CreateMenu()
{
    glutAddMenuEntry("圆锥体", CONE);
    glutAddMenuEntry("四面体", TETRAHEDRON);
    glutAddMenuEntry("正方体", CUBE);
    glutAddMenuEntry("正十二面体", DODECAHEDRON);
    glutAddMenuEntry("正二十面体", ICONSAHEDRON);
    glutAddMenuEntry("正八面体", OCTAHEDRON);
    glutAddMenuEntry("球体", SPHERE);
    glutAddMenuEntry("圆环体", TOURUS);
    glutAddMenuEntry("茶壶", TEAPOT);
    glutAddMenuEntry("线框或实体", WIRED);

    glutAttachMenu(GLUT_RIGHT_BUTTON); //指定菜单事件由鼠标右键单击产生
}

void SetupLights()
{
    GLfloat ambientLight[] = {0.2f, 0.2f, 0.2f, 1.0f};  //环境光
    GLfloat diffuseLight[] = {0.9f, 0.9f, 0.9f, 1.0f};  //漫反射
    GLfloat specularLight[] = {1.0f, 1.0f, 1.0f, 1.0f}; //镜面光
    GLfloat lightPos[] = {50.0f, 80.0f, 60.0f, 1.0f};   //光源位置

    glEnable(GL_LIGHTING);                            //启用光照
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);   //设置环境光源
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);   //设置漫反射光源
    glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight); //设置镜面光源
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);      //设置灯光位置
    glEnable(GL_LIGHT0);                              //打开第一个灯光

    glEnable(GL_COLOR_MATERIAL);                        //启用材质的颜色跟踪
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);  //指定材料着色的面
    glMaterialfv(GL_FRONT, GL_SPECULAR, specularLight); //指定材料对镜面光的反应
    glMateriali(GL_FRONT, GL_SHININESS, 100);           //指定反射系数
}