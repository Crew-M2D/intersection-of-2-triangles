#include <iostream>
#include <Application.hpp>
#include <GraphicsComponent.hpp>
#include <InputComponent.hpp>
#include <MathComponent.hpp>

int main() {
  std::cout << "Entrypoint run" << std::endl;
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
