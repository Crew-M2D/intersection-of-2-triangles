#include <fmt/core.h>
#include <Application.hpp>
#include <GraphicsComponent.hpp>
#include <InputComponent.hpp>
#include <MathComponent.hpp>

int main() {
  fmt::print("The answer is: {}\n", 42);
  Application app;
  app.run();
  MathComponent m;
  m.run();
  GraphicsComponent g;
  g.run();
  InputComponent i;
  i.run();
  
  return 0;
}
