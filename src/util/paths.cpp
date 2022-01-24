#include <util/paths.h>

std::string paths::getProjectRootPath() {
  std::filesystem::path currentPath{"../../../chess"};
  return currentPath.make_preferred().generic_string();
}

std::string paths::getImagesPath() {
  std::filesystem::path imagesPath{
      paths::getProjectRootPath() + "/assets/images/"};
  return std::filesystem ::path(imagesPath.make_preferred(),
                                std::filesystem::path::native_format)
      .generic_string();
}

std::string paths::getSoundsPath() {
  std::filesystem::path soundsPath{
      paths::getProjectRootPath() + "/assets/sounds/"};
  return std::filesystem ::path(soundsPath.make_preferred(),
                                std::filesystem::path::native_format)
      .generic_string();
}

std::string paths::getFontsPath() {
  std::filesystem::path fontsPath{
      paths::getProjectRootPath() + "/assets/fonts/"};
  return std::filesystem ::path(fontsPath.make_preferred(),
                                std::filesystem::path::native_format)
      .generic_string();
}
