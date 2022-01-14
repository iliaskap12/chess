#include <util/paths.h>

std::string paths::getProjectRootPath() {
  return std::filesystem::current_path().make_preferred();
}

std::string paths::getImagesPath() {
  std::string root{paths::getProjectRootPath()};
  return std::filesystem::path(root + "/assets/images/", std::filesystem::path::native_format);
}

std::string paths::getSoundsPath() {
  std::string root{paths::getProjectRootPath()};
  return std::filesystem::path(root + "/assets/sounds/", std::filesystem::path::native_format);
}

std::string paths::getFontsPath() {
  std::string root{paths::getProjectRootPath()};
  return std::filesystem::path(root + "/assets/fonts/", std::filesystem::path::native_format);
}
