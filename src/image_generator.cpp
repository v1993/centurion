#ifndef CENTURION_IMAGE_GENERATOR_SOURCE
#define CENTURION_IMAGE_GENERATOR_SOURCE

#include "image_generator.h"

#include "centurion_exception.h"
#include "image.h"
#include "renderer.h"

namespace centurion {
namespace video {

CENTURION_DEF ImageGenerator::ImageGenerator(
    const std::shared_ptr<Renderer>& renderer) {
  if (renderer) {
    this->renderer = renderer;
  } else {
    throw CenturionException{"Null renderer argument!"};
  }
}

CENTURION_DEF ImageGenerator::~ImageGenerator() noexcept = default;

CENTURION_DEF std::unique_ptr<Image> ImageGenerator::unique_img(
    const std::string& file) const {
  return Image::unique(renderer->get_internal(), file);
}

CENTURION_DEF std::unique_ptr<Image> ImageGenerator::unique_img(
    uint32_t format, TextureAccess access, int width, int height) const {
#ifdef CENTURION_HAS_MAKE_UNIQUE
  return std::make_unique<Image>(renderer->get_internal(), format, access,
                                 width, height);
#else
  return make_unique<Image>(renderer->get_internal(), format, access, width,
                            height);
#endif
}

CENTURION_DEF std::unique_ptr<Image> ImageGenerator::unique_img(
    PixelFormat format, TextureAccess access, int width, int height) const {
#ifdef CENTURION_HAS_MAKE_UNIQUE
  return std::make_unique<Image>(renderer->get_internal(), format, access,
                                 width, height);
#else
  return make_unique<Image>(renderer->get_internal(), format, access, width,
                            height);
#endif
}

CENTURION_DEF std::shared_ptr<Image> ImageGenerator::shared_img(
    const std::string& file) const {
  return Image::shared(renderer->get_internal(), file);
}

CENTURION_DEF std::shared_ptr<Image> ImageGenerator::shared_img(
    uint32_t format, TextureAccess access, int width, int height) const {
  return std::make_shared<Image>(renderer->get_internal(), format, access,
                                 width, height);
}

CENTURION_DEF std::shared_ptr<Image> ImageGenerator::shared_img(
    PixelFormat format, TextureAccess access, int width, int height) const {
  return std::make_shared<Image>(renderer->get_internal(), format, access,
                                 width, height);
}

}  // namespace video
}  // namespace centurion

#endif  // CENTURION_IMAGE_GENERATOR_SOURCE
