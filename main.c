#include <windows.h>
#include <gl/gl.h>
float xAlfa = 20;
float zAlfa = 0;
LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);
void EnableOpenGL(HWND hwnd, HDC*, HGLRC*);
void DisableOpenGL(HWND, HDC, HGLRC);

void drawCube(float x, float y, float z, float a){
    float dx = a, dy = a, dz = a;
  glBegin(GL_POLYGON);
  glVertex3f(  x + dx, y, z );
  glVertex3f(  x + dx,  y + dy, z );
  glVertex3f( x,  y + dy, z);
  glVertex3f( x, y, z );
  glEnd();
  glBegin(GL_POLYGON);
  glVertex3f(x + dx, y, z + dz);
  glVertex3f(  x + dx,  y + dy, z + dz );
  glVertex3f( x,  y + dy, z + dz );
  glVertex3f( x, y, z + dz );
  glEnd();
  glBegin(GL_POLYGON);
  glVertex3f( x + dx, y, z );
  glVertex3f( x + dx,  y + dy, z );
  glVertex3f( x + dx,  y + dy,  z + dz );
  glVertex3f( x + dx, y,  z + dz );
  glEnd();
  glBegin(GL_POLYGON);
  glVertex3f( x,y,  z + dz );
  glVertex3f( x,  y + dy,  z + dz );
  glVertex3f( x,  y + dy, z );
  glVertex3f( x, y, z );
  glEnd();
  glBegin(GL_POLYGON);
  glVertex3f(  x + dx, y + dy,  z + dz );
  glVertex3f(  x + dx,  y + dy, z );
  glVertex3f( x,  y + dy, z );
  glVertex3f( x,  y + dy,  z + dz );
  glEnd();
  glBegin(GL_POLYGON);
  glVertex3f(  x + dx, y, z );
  glVertex3f(  x + dx, y,  z + dz );
  glVertex3f( x, y,  z + dz );
  glVertex3f( x, y, z );
  glEnd();
}
float vert[] = {1, 1 , 0, -1, 1, 0, -1, -1, 0, 1, -1, 0};
float py [] = {0,0,2,1,1,0,1,-1,0,-1,-1,0,-1,1,0,1,1,0};
float kube[] = {0,0,0,0,1,0,1,1,0,1,0,0,0,0,1,0,1,1,1,1,1,1,0,1};
GLuint kubeInd[] = {0,1,2,2,3,0,4,5,6,6,7,4,3,2,5,6,7,3,0,1,5,5,4,0,1,2,6,6,5,1,0,3,7,7,4,0};
int act[4] = {1};
void show(){
    int i, a;
    glColor3f(0.91f,0.75f,0.41f);
    glBegin( GL_TRIANGLE_FAN );
               glVertex3f( 0.0f, 0.0f, 0.0f );
               for( i = 0; i <= 10000; i++ ) {
                   a = (float)i / 50.0f * 3.1415f * 2.0f;
                   glVertex3f( cos( a ) * 1.0f, sin( a ) * 1.0f, 0.0f );
               }
    glEnd();
    glColor3f(0.85, 0.64, 0.12);
    drawCube(0.5,0.5,0.5,0.5);
}
void ShowWorld(){
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT,0, vert);
    int i, j;
    for (i = -12; i < 12; i++){
        for(j = -19; j < 19; j++){
            glPushMatrix();
            glColor3f(0.94, 0.9, 0.54);
            int x = abs(i * j) / 10;
            glTranslatef(i*2, j*2, 0);
            glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
            glPopMatrix();
        }
    }
    glVertexPointer(3, GL_FLOAT,0, kube);
    glColor3f(0.91,0.75,0.41);
    //glColor3f(0.85, 0.64, 0.12);
    if(act[0] == 1) glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, kubeInd);
    if(act[1] == 1){
        glPushMatrix();
        glTranslatef(-7, -5, 0);
        glScalef(4,4,4);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, kubeInd);
        glPopMatrix();
    }
    if(act[2] == 1){
        glPushMatrix();
        glTranslatef(-2, 4, 0);
        glScalef(8,5,5);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, kubeInd);
        glPopMatrix();
    }
    if(act[3] == 1){
        glPushMatrix();
        glTranslatef(-10, 2, 0);
        glScalef(2,9,5);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, kubeInd);
        glPopMatrix();
    }
    glVertexPointer(3, GL_FLOAT,0, py);
    glColor3f(0,1,0);
    glPushMatrix();
        glTranslatef(5, -2, 0);
        glScalef(0.5,0.5,1);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 6);
    glPopMatrix();

   glDisableClientState(GL_VERTEX_ARRAY);
}
POINTFLOAT pos = {0,0};
void active(){ // измняем параметр видимости
    if(GetKeyState('1') < 0){
        act[0] = (act[0] + 1) % 2;
    }
    if(GetKeyState('2') < 0){
        act[1] = (act[1] + 1) % 2;
    }
    if(GetKeyState('3') < 0){
        act[2] = (act[2] + 1) % 2;
    }
    if(GetKeyState('4') < 0){
        act[3] = (act[3] + 1) % 2;
    }
}
void MoveCamera(){
    if(GetKeyState(VK_UP) < 0) xAlfa = ++ xAlfa > 180 ? 180 : xAlfa;
    if(GetKeyState(VK_DOWN) < 0) xAlfa = -- xAlfa < 0 ? 0 : xAlfa;
    if(GetKeyState(VK_LEFT) < 0) zAlfa ++;
    if(GetKeyState(VK_RIGHT) < 0) zAlfa --;
    float u = -zAlfa / 180 * 3.14;
    float s = 0;
    if(GetKeyState('W') < 0) s = 0.1;
    if(GetKeyState('S') < 0) s = -0.1;
    if(GetKeyState('A') < 0) {s= 0.1; u -= 3.14*0.5;}
    if(GetKeyState('D') < 0) {s = 0.1; u += 3.14*0.5;}
    if(s != 0){
        pos.x += sin(u) * s;
        pos.y += cos(u) * s;
    }
    glRotatef(-xAlfa, 1, 0 ,0);
    glRotatef(-zAlfa, 0,0,1);
    glTranslatef(-pos.x,-pos.y,-3);
}

int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine,
                   int nCmdShow)
{
    WNDCLASSEX wcex;
    HWND hwnd;
    HDC hDC;
    HGLRC hRC;
    MSG msg;
    BOOL bQuit = FALSE;
    float theta = 0.0f;

    /* register window class */
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_OWNDC;
    wcex.lpfnWndProc = WindowProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = "GLSample";
    wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);;


    if (!RegisterClassEx(&wcex))
        return 0;

    /* create main window */
    hwnd = CreateWindowEx(0,
                          "GLSample",
                          "OpenGL Sample",
                          WS_OVERLAPPEDWINDOW,
                          CW_USEDEFAULT,
                          CW_USEDEFAULT,
                          1920,
                          1080,
                          NULL,
                          NULL,
                          hInstance,
                          NULL);

    ShowWindow(hwnd, nCmdShow);

    /* enable OpenGL for the window */
    EnableOpenGL(hwnd, &hDC, &hRC);
    glFrustum(-1,1,-1,1,2,80);
    /* program main loop */
    glEnable(GL_DEPTH_TEST);
    while (!bQuit)
    {
        /* check for messages */
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            /* handle or dispatch messages */
            if (msg.message == WM_QUIT)
            {
                bQuit = TRUE;
            }
            else
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        else
        {
            /* OpenGL animation code goes here */

            //glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
            glClearColor(0.0f, 0.75f, 1.0f, 0.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
           // show();
           glRotatef(0,0,0,1);
            glPushMatrix();
                active();
                MoveCamera();
                ShowWorld();

            glPopMatrix();

            //drawCube(0,0,0,0.5);
            //MoveCamera();


            SwapBuffers(hDC);

            Sleep (1);
        }
    }

    /* shutdown OpenGL */
    DisableOpenGL(hwnd, hDC, hRC);

    /* destroy the window explicitly */
    DestroyWindow(hwnd);

    return msg.wParam;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_CLOSE:
            PostQuitMessage(0);
        break;

        case WM_DESTROY:
            return 0;

        case WM_KEYDOWN:
        {
            switch (wParam)
            {
                case VK_ESCAPE:
                    PostQuitMessage(0);
                break;
            }
        }
        break;

        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    return 0;
}

void EnableOpenGL(HWND hwnd, HDC* hDC, HGLRC* hRC)
{
    PIXELFORMATDESCRIPTOR pfd;

    int iFormat;

    /* get the device context (DC) */
    *hDC = GetDC(hwnd);

    /* set the pixel format for the DC */
    ZeroMemory(&pfd, sizeof(pfd));

    pfd.nSize = sizeof(pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW |
                  PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 24;
    pfd.cDepthBits = 16;
    pfd.iLayerType = PFD_MAIN_PLANE;

    iFormat = ChoosePixelFormat(*hDC, &pfd);

    SetPixelFormat(*hDC, iFormat, &pfd);

    /* create and enable the render context (RC) */
    *hRC = wglCreateContext(*hDC);

    wglMakeCurrent(*hDC, *hRC);
}

void DisableOpenGL (HWND hwnd, HDC hDC, HGLRC hRC)
{
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(hRC);
    ReleaseDC(hwnd, hDC);
}
