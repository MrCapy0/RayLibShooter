#include "IActor.h"

void G::IActor::SetTransform(const Transform transform)
{
    this->transform = transform;
}

G::Transform G::IActor::GetTransform() const
{
    return transform;
}