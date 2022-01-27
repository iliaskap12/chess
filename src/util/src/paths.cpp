#include <util/paths.h>

std::string paths::getProjectRootPath() {
  const std::filesystem::path currentDirectory{std::filesystem::current_path().make_preferred()};
  const std::filesystem::path projectRoot{currentDirectory.parent_path().parent_path().make_preferred()};
  return std::filesystem::absolute(projectRoot).generic_string();
}

std::string paths::getImagesPath() {
  std::filesystem::path imagesPath{paths::getProjectRootPath() + "/assets/images/"};
  return std::filesystem::path(imagesPath.make_preferred()).generic_string();
}

std::string paths::getSoundsPath() {
  std::filesystem::path soundsPath{paths::getProjectRootPath() + "/assets/sounds/"};
  return std::filesystem::path(soundsPath.make_preferred()).generic_string();
}

std::string paths::getFontsPath() {
  std::filesystem::path fontsPath{paths::getProjectRootPath() + "/assets/fonts/"};
  return std::filesystem::path(fontsPath.make_preferred()).generic_string();
}
