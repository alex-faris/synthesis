#include "Game.hpp"

#include <cassert>
#include <iostream>

Game::Game::Game() : m_IsRunning(false), m_Window(nullptr), m_EGL(nullptr), m_Renderer(nullptr)
{
}

Game::Game::~Game()
{
}

void Game::Game::Init()
{
  m_Window = std::make_unique<Engine::Win32Window>(1280, 720);
  assert(m_Window->TryCreate());
  m_Window->CreateObserver(this);

  m_EGL = std::make_unique<Engine::EGLManager>(m_Window.get());
  assert(m_EGL->TryCreate());

  m_Renderer = std::make_unique<Engine::Renderer>(m_EGL.get());
  assert(m_Renderer->TryCreate());
  m_Window->CreateObserver(m_Renderer.get());

  m_IsRunning = true;
}

void Game::Game::Run()
{
  while (m_IsRunning)
  {
    m_Renderer->Draw();
    m_Window->Update();
    m_Renderer->Update();
  }
}

void Game::Game::OnClose()
{
  m_IsRunning = false;
}

void Game::Game::Shutdown()
{
  m_Renderer->Destroy();
  m_EGL->Destroy();
  m_Window->Destroy();
}
