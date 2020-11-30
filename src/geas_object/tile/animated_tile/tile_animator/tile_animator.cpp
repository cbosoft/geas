#include "tile_animator.hpp"
#include "../../../../resourcemanager/resourcemanager.hpp"

TileAnimator::TileAnimator(GeasObject &owner)
    :   Animator(owner)
{
    // do nothing
}

void TileAnimator::load_animations(const std::string &texture)
{
    json j = ResourceManager::singleton().get_metadata(texture);
    auto *anim = new Animation("all", 0, j["number_frames"]);
    this->add_animation(anim);
    this->set_current_anim("all");
}
