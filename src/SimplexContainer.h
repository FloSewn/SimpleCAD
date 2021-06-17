#pragma once

#include <list>           // std::list
#include <memory>         // std::shared_ptr
#include <utility>        // std::move

#include "Simplex.h"
#include "Vertex.h"

/***********************************************************
* This class is a container for two-dimensional objects 
***********************************************************/
class SimplexContainer
{
public:
  using List           = std::list<std::unique_ptr<Simplex>>;
  using size_type      = typename List::size_type;
  using value_type     = Simplex;
  using iterator       = typename List::iterator;
  using const_iterator = typename List::const_iterator;

  iterator begin() { return items_.begin(); }
  iterator end() { return items_.end(); }

  const_iterator begin() const { return items_.begin(); }
  const_iterator end() const { return items_.end(); }

  /*--------------------------------------------------------
  | Get the current size of the list
  --------------------------------------------------------*/
  size_type size() const { return items_.size(); }

  /*--------------------------------------------------------
  | Function to remove an object from this list
  --------------------------------------------------------*/
  template <class T>
  void remove(T*& item) 
  { 
    items_.erase( item->list_pos_ ); 
    item = nullptr;
  }

  /*--------------------------------------------------------
  | Add new vertex to the list
  --------------------------------------------------------*/
  template <typename T=Vertex, typename... Args>
  T* add_vertex( Args&&... args )
  {
    std::unique_ptr<T> u_ptr = std::make_unique<T>(args...);

    T* v_ptr = u_ptr.get();

    items_.push_back( std::move(u_ptr) );
    
    v_ptr->list_pos_ = --items_.end();

    return v_ptr;
  }

  /*--------------------------------------------------------
  | Add any simplex through unique_ptr
  --------------------------------------------------------*/
  template <typename T>
  T* add( std::unique_ptr<T>&& u_ptr )
  {
    T* ptr = u_ptr.get();

    items_.push_back( std::move(u_ptr) );

    ptr->list_pos_ = --items_.end();

    return ptr;

  }


private:
  List items_;

}; // SimplexContainer
