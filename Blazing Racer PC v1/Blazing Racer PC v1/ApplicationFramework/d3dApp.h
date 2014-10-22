
#ifndef _D3DAPP
#define _D3DAPP

#include<string>

class D3DApp
{
public:
		D3DApp(HINSTANCE hInstance, std::string winCaption, bool enable4xMsaa);
		virtual ~D3DApp();

		HINSTANCE				getAppInst();
		HWND					getMainWnd();
		int						run();

		//Framework Methods
		virtual void			init();
		virtual void			onResize();
		virtual void			updateScene(float dt);
		virtual void			drawScene();
		virtual LRESULT			msgProc(HWND hwnd, UINT msg,WPARAM wParam,LPARAM lParam);

		void					enableFullScreenMode(bool enable);
		bool					isDeviceLost();

		int						m_clientWidth;
		int						m_clientHeight;

protected:
	//Override these methods please if you need to change working

		virtual void			initMainWindow();
		virtual void			initDirect3D();
		virtual void			calculateFramesPerSecond(float dt){}	//Call from update method

	//Customized data members
		std::string				mMainWndCaption;
		bool					m_Enable4xMsaa;

	//Application,Windows and DIrec3D data members
		HINSTANCE				mhAppInst;
		HWND					mhMainWnd;
		bool					mAppPaused; 
};

#endif