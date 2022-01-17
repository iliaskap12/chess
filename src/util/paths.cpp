#include <util/paths.h>

std::string paths::getProjectRootPath() {
  return std::filesystem::current_path().make_preferred().parent_path().parent_path().parent_path().generic_string();
}

std::string paths::getImagesPath() {
  std::string root{paths::getProjectRootPath()};
  return std::filesystem::path(root + "/assets/images/", std::filesystem::path::native_format).generic_string();
}

std::string paths::getSoundsPath() {
  std::string root{paths::getProjectRootPath()};
  return std::filesystem::path(root + "/assets/sounds/", std::filesystem::path::native_format).generic_string();
}

std::string paths::getFontsPath() {
  std::string root{paths::getProjectRootPath()};
  return std::filesystem::path(root + "/assets/fonts/", std::filesystem::path::native_format).generic_string();
}
