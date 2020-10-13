#pragma once

class Window;
class GLObject {
  public:
    virtual bool draw() =0;
    virtual ~GLObject() =default;
};
