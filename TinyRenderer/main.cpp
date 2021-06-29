#include <iostream>
#include <thread>
#include "main.h"
#include "main_window.h"
#include "window_msg_processor.h"
#include "renderer.h"
#include "game_time.h"
#include "game_controller.h"
#include "graphic_math.h"
#include "cube.h"
#include "model.h"
#include "orthogonal_camera.h"
#include "perspective_camera.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

MainWindow *CreateMainWindow(bool &is_success)
{
    MainWindow *win = new MainWindow();

    if (!win->Create(L"TinyRenderer", WS_SYSMENU | WS_MINIMIZEBOX, 0, CW_USEDEFAULT, CW_USEDEFAULT, WINDOW_WIDTH, WINDOW_HEIGHT))
    {
        is_success = false;
        delete win;
        return nullptr;
    }
    is_success = true;
    ShowWindow(win->Window(), SW_SHOW);
    return win;
}


void InitModules(MainWindow *main_window)
{
    Singleton<GameTime>::GetInstance()->Init();
    Singleton<GameController>::GetInstance()->Init(main_window->Window(), 10);
    Singleton<Renderer>::GetInstance()->Init(main_window->Window(), WINDOW_WIDTH, WINDOW_HEIGHT);
}

void Test()
{
    /*
    Vector3 v{ 2.2, 3.3, 4.4 };
    v.Print();
    Matrix4x4 view_matrix = Matrix4x4::LookAt(Vector3(0, 0, -3), Vector3(0, 0, 1), Vector3(0, 1, 0));
    printf("view_matrix:\n");
    view_matrix.Print();

    Matrix4x4 perspective_matrix = Matrix4x4::Perspective(45, 4.f / 3.f, 1, 1000);
    printf("perspective_matrix:\n");
    perspective_matrix.Print();
    perspective_matrix.Inverse().Print();
    perspective_matrix.Transpose().Print();
    perspective_matrix.Inverse().Transpose().Print();

    Matrix4x4 orthogonal_matrix1 = Matrix4x4::Orthogonal(-1, 1, -1, 1, 1, 1000);
    Matrix4x4 orthogonal_matrix2 = Matrix4x4::Orthogonal(1, 1, 1, 1000);
    printf("orthogonal_matrix:\n");
    orthogonal_matrix1.Print();
    orthogonal_matrix2.Print();
    printf("translate_matrix:\n");
    Matrix4x4::Translate(Vector3(40, 10, 55)).Print();
    printf("scale_matrix:\n");
    Matrix4x4::Scale(Vector3(1, 3, 4)).Print();
    printf("rotate matrix:\n");
    Matrix4x4::Rotate(Vector3(90, 0, 0)).Print();
    (Matrix4x4::kIdentity * orthogonal_matrix1).Print();
    */
    //Cube cube;
    //std::vector<Vector3> *vs = cube.vertices();
    /*
    Matrix4x4 m1;
    m1.Print();
    m1 = Matrix4x4::kIdentity;
    m1.Print();
    Matrix4x4 m2(Matrix4x4::kIdentity);
    m2.Print();
    Matrix4x4::kIdentity.Print();
    */
}

OrthogonalCamera *GetOrthogonalCamera()
{
    OrthogonalCamera *camera = new OrthogonalCamera();
    camera->set_aspect(4.f / 3.f);
    camera->set_position({ 0, 0, -3 });
    camera->set_up({ 0, 1, 0 });
    camera->set_z_near(1);
    camera->set_z_far(1000);
    camera->set_size(3);
    return camera;
}

PerspectiveCamera *GetPerspectiveCamera()
{
    PerspectiveCamera *camera = new PerspectiveCamera();
    camera->set_aspect(4.f / 3.f);
    camera->set_position({ 0, 0, -3 });
    camera->set_up({ 0, 1, 0 });
    camera->set_z_near(1);
    camera->set_z_far(1000);
    camera->set_fov(45);
    return camera;
}


int main()
{
    Test();
    bool is_create_main_window_success;
    MainWindow *win = CreateMainWindow(is_create_main_window_success);
    if (!is_create_main_window_success)
    {
        std::cerr << "Create MainWindow Failed!" << std::endl;
        return 0;
    }
    InitModules(win);

    Cube cube;

    Camera *camera = GetPerspectiveCamera();

    Renderer *renderer = Singleton<Renderer>::GetInstance();
    renderer->set_fill_mode(FillMode::kFill);
    renderer->set_model_matrix(Matrix4x4::kIdentity);
    renderer->set_camera(camera);
    renderer->set_vertices(cube.vertices());
    renderer->set_triangles(cube.triangles());
    renderer->set_normals(cube.normals());
    renderer->set_cull_mode(FaceCullMode::kCullBack);

    bool is_moving = false;
    bool is_rotating = false;
    Vector2 last_move_pos;
    //test 
    win->temp_cb = [&camera, &is_moving, &last_move_pos, &renderer, &is_rotating, &cube](UINT uMsg, WPARAM w, LPARAM l) {
        Vector3 src_pos = camera->position();
        Vector3 target_pos = src_pos;
        const Vector3 camera_dir = camera->GetDirection();
        float move_speed = 0.01;
        switch (uMsg)
        {
        case WM_KEYDOWN:
            switch (w)
            {
            case 'S':
                target_pos = src_pos + -camera_dir * move_speed;
                break;
            case 'W':
                target_pos = src_pos + camera_dir * move_speed;
                break;
            case 'A':
                target_pos = src_pos + Vector3(-1, 0, 0) * move_speed;
                break;
            case 'D':
                target_pos = src_pos + Vector3(1, 0, 0) * move_speed;
                break;
            case 'Q':
                target_pos = src_pos + Vector3(0, 1, 0) * move_speed;
                break;
            case 'E':
                target_pos = src_pos + Vector3(0, -1, 0) * move_speed;
                break;
            case 'R':
                target_pos = Vector3(0, 0, -3);
                camera->set_rotation(Vector3(0, 0, 0));
                cube.set_rotation({ 0, 0, 0 });
                renderer->set_model_matrix(Matrix4x4::kIdentity);
                break;
            case VK_ESCAPE:
                PostQuitMessage(0);
                break;
            }
            camera->set_position(target_pos);
            return;
        case WM_KEYUP:
            break;
        case WM_LBUTTONDOWN:
            is_moving = true;
            last_move_pos = { (float)LOWORD(l), (float)HIWORD(l) };
            break;
        case WM_LBUTTONUP:
            is_moving = false;
            break;
        case WM_MOUSEMOVE:
        {
            int mouse_x = LOWORD(l);
            int mouse_y = HIWORD(l);
            Vector2 offset = { mouse_x - last_move_pos.x, mouse_y - last_move_pos.y };
            offset /= 5.f;
            last_move_pos = { (float)mouse_x, (float)mouse_y };
            if (is_moving)
            {
                Vector3 rotation = cube.rotation() + Vector3(offset.y, offset.x, 0);
                cube.set_rotation(rotation);
                renderer->set_model_matrix(Matrix4x4::Rotate(rotation));
            }
            if (is_rotating)
            {
                Vector3 cam_rot = camera->rotation();
                Vector3 rot = cam_rot + Vector3(-offset.y, offset.x, 0);
                camera->set_rotation(rot);
            }
            break;
        }
        case WM_RBUTTONDOWN:
            is_rotating = true;
            break;
        case WM_RBUTTONUP:
            is_rotating = false;
            break;
        case WM_PAINT:
            clock_t start = clock();
			renderer->Render();
            printf("elapse: %d\n", clock() - start);
            break;
        }
    };
    //test

    WindowMsgProcessor *window_msg_processor = Singleton<WindowMsgProcessor>::GetInstance();
    while (!window_msg_processor->ShouldQuit())
    {
        /*
        while (!Singleton<GameController>::GetInstance()->CanNextFrame());
        while(window_msg_processor->Update()) ;
        */
        window_msg_processor->Update();
        Singleton<GameController>::GetInstance()->Update();
    }
    renderer->Release();

    delete camera;
    return 0;
}
