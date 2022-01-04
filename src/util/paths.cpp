#include <util/paths.h>

std::string getProjectRootPath() {
  return std::filesystem::current_path().make_preferred().parent_path().parent_path();
}

std::string getImagesPath() {
  std::string root = getProjectRootPath();
  return std::filesystem::path(root + "/assets/images/", std::filesystem::path::native_format);
}

std::string getSoundsPath() {
  std::string root = getProjectRootPath();
  return std::filesystem::path(root + "/assets/sounds/", std::filesystem::path::native_format);
}

std::string getFontsPath() {
  std::string root = getProjectRootPath();
  return std::filesystem::path(root + "/assets/fonts/", std::filesystem::path::native_format);
}
