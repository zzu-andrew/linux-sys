/***
 * Excerpted from "Test-Driven Development for Embedded C",
 * published by The Pragmatic Bookshelf.
 * Copyrights apply to this code. It may not be used to create training material, 
 * courses, books, articles, and the like. Contact us if you are in doubt.
 * We make no guarantees that this code is fit for any purpose. 
 * Visit http://www.pragmaticprogrammer.com/titles/jgade for more book information.
***/
#ifndef D_MockClassName_H
#define D_MockClassName_H

///////////////////////////////////////////////////////////////////////////////
//
//  MockClassName.h
//
//  MockClassName is responsible for providing a test stub for ClassName
//
///////////////////////////////////////////////////////////////////////////////
#include "ClassName.h"


class MockClassName : public ClassName
  {
  public:
    explicit MockClassName()
    {}
    virtual ~MockClassName()
    {}

  private:

    MockClassName(const MockClassName&);
    MockClassName& operator=(const MockClassName&);

  };

#endif  // D_MockClassName_H
