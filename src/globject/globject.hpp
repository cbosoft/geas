#pragma once

class Window;
class GLObject {
  public:
    virtual bool draw(Window &win) =0;
    virtual ~GLObject() =default;
};
