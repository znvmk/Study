
class OpenGL  
{	public:	OpenGL();
	virtual ~OpenGL();
	public:

	HDC		hDC;		// GDI设备描述表
	HGLRC	hRC;		// 永久着色描述表
	BOOL	SetupPixelFormat(HDC hDC);
	void	init(int Width, int Height);
	void	Render();
	void	CleanUp();

};


