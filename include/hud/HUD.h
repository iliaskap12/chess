
#ifndef HUD_H
#define HUD_H

#include <string>
#include <sgg/graphics.h>
#include "graphics/Drawable.h"

class HUD : public Drawable {
  std::string message;
  std::pair<float, float> coordinates;
  std::size_t size;
  graphics::Brush textBrush { graphics::Brush() };

public:
  explicit HUD(std::string message, std::pair<float, float> coordinates, size_t size);
  void draw() override;
  [[nodiscard]] const std::pair<float, float> &getCoordinates() const;
  [[nodiscard]] size_t getSize() const;
  [[nodiscard]] float getLength() const;
  void setTextBrush(float red, float green, float blue);
};

#endif // HUD_H
