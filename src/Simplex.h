#pragma once

#include <list>           // std::list
#include <memory>         // std::shared_ptr

#include "raylib_wrapper.h"
#include "app_util.h"

//class SimplexContainer; 

/***********************************************************
* This class is the base for any two-dimensional object
***********************************************************/
class Simplex
{
public:
  friend SimplexContainer;

  using SimplexListIterator 
    = std::list< std::unique_ptr<Simplex> >::iterator;

  Simplex() = default;

  /*--------------------------------------------------------
  | Ostream of simplex
  --------------------------------------------------------*/
  virtual std::ostream& print(std::ostream& os) const = 0;

  /*--------------------------------------------------------
  | Setters
  --------------------------------------------------------*/
  virtual void active(bool a){ active_ = a; }
  virtual void updating(bool u) { updating_ = u; }

  /*--------------------------------------------------------
  | Getters
  --------------------------------------------------------*/
  virtual bool active() const { return active_; }
  virtual bool updating() const { return updating_; }
  virtual const Vec2& xy() const = 0;

  /*--------------------------------------------------------
  | Reset routine
  --------------------------------------------------------*/
  virtual void reset() 
  {
    active_   = false;
    updating_ = false;
  }

  /*--------------------------------------------------------
  | Update routine
  --------------------------------------------------------*/
  virtual void update() { if ( updating_ == false ) return; }

  /*--------------------------------------------------------
  | Draw routine
  --------------------------------------------------------*/
  virtual void draw(const WorldSpace& ws) const = 0;

protected:
  SimplexListIterator list_pos_ { nullptr };

  bool active_   { false };
  bool updating_ { false };

}; // Simplex

/***********************************************************
* Simplex ostream operator overload
***********************************************************/
static std::ostream& operator<<(std::ostream& os, const Simplex& s)
{
  return s.print(os);
}

