#include "Game.hpp"

#include <cassert>
#include <iostream>

Game::Game::Game() : mIsRunning(false), mWindow(nullptr), mEGL(nullptr), m_Renderer(nullptr)
{
}

Game::Game::~Game()
{
}

void Game::Game::init()
{
  mWindow = std::make_unique<Engine::Win32Window>(1280, 720);
  assert(mWindow->tryCreate());
  mWindow->createObserver(this);

  mEGL = std::make_unique<Engine::EGLManager>(mWindow.get());
  assert(mEGL->tryCreate());

  m_Renderer = std::make_unique<Engine::Renderer>(mEGL.get());
  assert(m_Renderer->tryCreate());
  mWindow->createObserver(m_Renderer.get());

  mIsRunning = true;
}

void Game::Game::run()
{
  while (mIsRunning)
  {
    m_Renderer->draw();
    mWindow->update();
    m_Renderer->update();
  }
}

void Game::Game::onClose()
{
  mIsRunning = false;
}

void Game::Game::shutdown()
{
  m_Renderer->destroy();
  mEGL->destroy();
  mWindow->destroy();
}
