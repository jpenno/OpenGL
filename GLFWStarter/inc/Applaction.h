#pragma once
struct  GLFWwindow;

class Applaction {
protected:
	GLFWwindow *m_window;
	int m_windowWidth;
	int m_windowHeight;

public:
	Applaction();
	virtual ~Applaction();

	bool SetUp(int windowWidh, int windowHeight);
	void shutDown();

	void Run();

	virtual void Load();
	virtual void UnLoad();

	virtual void UpDate();
	virtual void Draw();


	int GetWindowWidth() const;
	int GetWindowHeight() const;

	GLFWwindow *GetWindow;

};