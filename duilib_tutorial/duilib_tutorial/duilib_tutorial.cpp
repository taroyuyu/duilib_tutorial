//duilib_tutorial.cpp: 定义应用程序的入口点。
//

#include "stdafx.h"
#include "duilib_tutorial.h"

class MainWndFrame : public WindowImplBase
{
protected:
	virtual CDuiString GetSkinFolder() override;				// 获取皮肤文件的目录，如果有多层目录这里可以设置
	virtual CDuiString GetSkinFile() override;					// 设置皮肤文件名字
	virtual LPCTSTR GetWindowClassName(void) const override;	// 设置当前窗口的 class name

	virtual UILIB_RESOURCETYPE GetResourceType() const override;// 返回资源类型
	virtual LPCTSTR GetResourceID() const override;				// 如果是ZIP资源，返回资源ID

public:
	static const LPCTSTR kClassName;
	static const LPCTSTR kMainWndFrame;
};

DuiLib::CDuiString MainWndFrame::GetSkinFolder()
{
	// GetInstancePath 接口返回默认的皮肤文件位置
	// 在 main 函数中我们可以通过 SetResourcePath 来设置路径
	return m_PaintManager.GetInstancePath();
}

DuiLib::CDuiString MainWndFrame::GetSkinFile()
{
	// 成员变量定义的皮肤文件名
	return kMainWndFrame;
}

LPCTSTR MainWndFrame::GetWindowClassName(void) const
{
	// 成员变量定义的窗口 class name
	return kClassName;
}

DuiLib::UILIB_RESOURCETYPE MainWndFrame::GetResourceType() const
{
	return UILIB_ZIPRESOURCE;
}

LPCTSTR MainWndFrame::GetResourceID() const
{
	return MAKEINTRESOURCE(IDR_ZIPRES1);
}

const LPCTSTR MainWndFrame::kClassName = _T("main_wnd_frame");
const LPCTSTR MainWndFrame::kMainWndFrame = _T("main_wnd_frame.xml");

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// 设置窗口关联的实例
	CPaintManagerUI::SetInstance(hInstance);

	// 设置皮肤的默认路径
	CPaintManagerUI::SetCurrentPath(CPaintManagerUI::GetInstancePath());

	// 创建窗口
	MainWndFrame* pMainWndFrame = new MainWndFrame;
	pMainWndFrame->Create(nullptr, MainWndFrame::kClassName, UI_WNDSTYLE_DIALOG, 0);
	pMainWndFrame->CenterWindow();
	pMainWndFrame->ShowWindow();

	CPaintManagerUI::MessageLoop();

	if (nullptr != pMainWndFrame)
	{
		delete pMainWndFrame;
	}

	return 0;
}
