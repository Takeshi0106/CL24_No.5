//�}���`�o�C�g����
#undef UNICODE

#include <Windows.h>
#include "Game.h"

#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>


//�}�N����` ============================
// �E�B���h�E�N���X�̖��O
#define CLASS_NAME "CL24_NO.5"
// �E�B���h�E�ɕ\�����閼�O
#define WINDOW_NAME "CL24�ۑ�NO.5"

// �֐��̃v���g�^�C�v�錾
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

//--------------------------------------------------------------------------------------
// �G���g���|�C���g����ԍŏ��Ɏ��s�����֐�
//--------------------------------------------------------------------------------------
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	// ���������[�N���o��L����
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// �E�B���h�E�N���X�����܂Ƃ߂�
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_CLASSDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = CLASS_NAME;
	wc.hIconSm = NULL;

	RegisterClassEx(&wc);

	// �E�B���h�E�̏����܂Ƃ߂�
	HWND hWnd;
	hWnd = CreateWindowEx(0,	// �g���E�B���h�E�X�^�C��
		CLASS_NAME,				// �E�B���h�E�N���X�̖��O
		WINDOW_NAME,			// �E�B���h�E�̖��O
		WS_OVERLAPPEDWINDOW,	// �E�B���h�E�X�^�C��
		CW_USEDEFAULT,			// �E�B���h�E�̍���w���W
		CW_USEDEFAULT,			// �E�B���h�E�̍���x���W 
		SCREEN_WIDTH,			// �E�B���h�E�̕�
		SCREEN_HEIGHT,			// �E�B���h�E�̍���
		NULL,					// �e�E�B���h�E�̃n���h��
		NULL,					// ���j���[�n���h���܂��͎q�E�B���h�EID
		hInstance,				// �C���X�^���X�n���h��
		NULL);					// �E�B���h�E�쐬�f�[�^


	//�E�B���h�E�̃T�C�Y���C��
	RECT rc1, rc2;
	GetWindowRect(hWnd, &rc1);  //�E�B���h�E�̗̈���擾
	GetClientRect(hWnd, &rc2);
	int sx = SCREEN_WIDTH;
	int sy = SCREEN_HEIGHT;
	sx += ((rc1.right - rc1.left) - (rc2.right - rc2.left));
	sy += ((rc1.bottom - rc1.top) - (rc2.bottom - rc2.top));
	SetWindowPos(hWnd, NULL, 0, 0, sx, sy, (SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOMOVE));

	//�E�B���h�E�T�C�Y�̕ύX


	// �w�肳�ꂽ�E�B���h�E�̕\����Ԃ�ݒ�(�E�B���h�E��\��)
	ShowWindow(hWnd, nCmdShow);
	// �E�B���h�E�̏�Ԃ𒼂��ɔ��f(�E�B���h�E�̃N���C�A���g�̈���X�V)
	UpdateWindow(hWnd);

	//-------------------------------------------------------------
	// �Q�[�����[�v�ɓ���O��DirectX�̏�����������

	Game::GetInstance()->Init(hWnd);

	MSG msg;

	int cnt = 0;

	//FPS�v�Z�p�ϐ�
	int fpsCounter = 0;
	long long oldTick = GetTickCount64();  //�O��̌v�����̎���
	long long nowTick = oldTick;           //����̌v�����̎���

	//FPS�Œ�p�ϐ�
	LARGE_INTEGER liWork;  //work�����ϐ��͍�Ɨp�ϐ�
	long long frequency;   //�ǂꂭ�炢�ׂ������Ԃ�ݒ�ł��邩
	QueryPerformanceFrequency(&liWork);
	frequency = liWork.QuadPart;

	//���ԁi�P�ʁF�J�E���g�j�擾
	QueryPerformanceCounter(&liWork);
	long long oldCount = liWork.QuadPart;  //�O��̌v�����̎���
	long long nowCount = oldCount;         //����̌v�����̎���

	bool loop = true;

	// �Q�[�����[�v
	while (Game::GetInstance()->GameLoop())
	{
		cnt++;
		// �V���Ƀ��b�Z�[�W�������
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			// �E�B���h�E�v���V�[�W���Ƀ��b�Z�[�W�𑗂�
			DispatchMessage(&msg);

			// �uWM_QUIT�v���b�Z�[�W���󂯎�����烋�[�v�𔲂���
			if (msg.message == WM_QUIT) {
				break;
			}
		}
		else
		{
			QueryPerformanceCounter(&liWork);//���ݎ��Ԃ��擾
			nowCount = liWork.QuadPart;
			//1/60�b�Ԃ��o�߂������H
			if (nowCount >= oldCount + frequency / 60)
			{
				//---------------------------------------------------
				// �Q�[���������s
				Game::GetInstance()->Update();
				Game::GetInstance()->Draw();

				fpsCounter++;  //�Q�[�����������s������{�P����
				oldCount = nowCount;
			}

			nowTick = GetTickCount64();  //���ݎ��Ԃ��擾
			//�O��v�Z����1000�~���b���o�߂�����
			if (nowTick >= oldTick + 1000)
			{

				//FPS�\��
				char str[32];
				wsprintfA(str, "FPS=%d", fpsCounter);
				SetWindowTextA(hWnd, str);
				//�J�E���^�[���Z�b�g
				fpsCounter = 0;
				oldTick = nowTick;
				
			}
		}
	}
	Game::GetInstance()->Uninit();
	delete Game::GetInstance();

	// ���������[�N��\��
	_CrtDumpMemoryLeaks();

	//-----------------------------------------------------------
	// DirectX�̉������
	D3D_Release();

	UnregisterClass(CLASS_NAME, hInstance);

	return 0;
}

//--------------------------------------------------------------------------------------
//�E�B���h�E�v���V�[�W��
//--------------------------------------------------------------------------------------
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:// �E�B���h�E�j���̃��b�Z�[�W
		PostQuitMessage(0);// �uWM_QUIT�v���b�Z�[�W�𑗂�@���@�A�v���I��
		break;

	case WM_CLOSE:  // �ux�v�{�^���������ꂽ��
	{
		int res = MessageBoxA(NULL, "�I�����܂����H", "�m�F", MB_OKCANCEL);
		if (res == IDOK) {
			DestroyWindow(hWnd);  // �uWM_DESTROY�v���b�Z�[�W�𑗂�
		}
	}
	break;

	case WM_KEYDOWN: //�L�[���͂����������b�Z�[�W
		if (LOWORD(wParam) == VK_ESCAPE) { //���͂��ꂽ�L�[��ESCAPE�Ȃ�
			PostMessage(hWnd, WM_CLOSE, wParam, lParam);//�uWM_CLOSE�v�𑗂�
		}

	default:
		// �󂯎�������b�Z�[�W�ɑ΂��ăf�t�H���g�̏��������s
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
		break;
	}

	return 0;
}
