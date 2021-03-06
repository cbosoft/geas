#include "geas_object.hpp"

GeasObject::GeasObject()
  : Transform()
    , physics(nullptr)
    , _renderable(nullptr)
    , _animator(nullptr)
    , _marked_for_destruction(false)
{
    // do nothing
}

GeasObject::GeasObject(Transform *parent)
  : Transform(parent)
  , physics(nullptr)
  , _renderable(nullptr)
  , _animator(nullptr)
  , _marked_for_destruction(false)
  , contact_mask(0)
{
    // do nothing
}

GeasObject::~GeasObject()
{
  delete this->_renderable;
  delete this->physics;
}

bool GeasObject::is_marked_for_destruction() const
{
  return this->_marked_for_destruction;
}

void GeasObject::destroy()
{
  this->_marked_for_destruction = true;
}


Renderable *GeasObject::renderable() const
{
    return this->_renderable;
}

void GeasObject::renderable(Renderable *renderable)
{
    this->_renderable = renderable;
}

Animator *GeasObject::animator() const
{
    return this->_animator;
}

void GeasObject::animator(Animator *animator)
{
    delete this->_animator;
    this->_animator = animator;
}