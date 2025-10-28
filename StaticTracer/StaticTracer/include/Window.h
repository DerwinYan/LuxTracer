
#ifndef WINDOW
#define WINDOW

namespace pt
{
  class Window
  {
  public:
    Window(int width, int height);
    inline int getWidth() const noexcept { return width; }
    inline int getHeight() const noexcept { return height; }

  private:
    int width;
    int height;
  };
}

#endif // !WINDOW
