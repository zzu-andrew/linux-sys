/***
 * Excerpted from "Test-Driven Development for Embedded C",
 * published by The Pragmatic Bookshelf.
 * Copyrights apply to this code. It may not be used to create training material, 
 * courses, books, articles, and the like. Contact us if you are in doubt.
 * We make no guarantees that this code is fit for any purpose. 
 * Visit http://www.pragmaticprogrammer.com/titles/jgade for more book information.
***/
#ifndef D_VirtualCall_H
#define D_VirtualCall_H

#define send(obj,msg)\
              ((obj)->msg(obj))

#define send1(obj,msg,arg0)\
              ((obj)->msg((obj),(arg0)))

#define send2(obj,msg,arg0,arg1)\
              ((obj)->msg((obj),(arg0),(arg1)))

#define send3(obj,msg,arg0,arg1,arg2)\
              ((obj)->msg((obj),(arg0),(arg1),(arg2)))

#define send4(obj,msg,arg0,arg1,arg2,arg3)\
              ((obj)->msg((obj),(arg0),(arg1),(arg2),(arg3)))

#define vBind(obj,msg,newMethod)\
              (obj->msg=&newMethod)

#define castToDestroyer(Class) (Class* (*)(Class*))

#endif
