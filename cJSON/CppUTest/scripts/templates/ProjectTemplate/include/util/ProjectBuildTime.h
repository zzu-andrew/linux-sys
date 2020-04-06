/***
 * Excerpted from "Test-Driven Development for Embedded C",
 * published by The Pragmatic Bookshelf.
 * Copyrights apply to this code. It may not be used to create training material, 
 * courses, books, articles, and the like. Contact us if you are in doubt.
 * We make no guarantees that this code is fit for any purpose. 
 * Visit http://www.pragmaticprogrammer.com/titles/jgade for more book information.
***/
#ifndef D_ProjectBuildTime_H
#define D_ProjectBuildTime_H

///////////////////////////////////////////////////////////////////////////////
//
//  ProjectBuildTime is responsible for recording and reporting when
//  this project library was built
//
///////////////////////////////////////////////////////////////////////////////

class ProjectBuildTime
  {
  public:
    explicit ProjectBuildTime();
    virtual ~ProjectBuildTime();
    
    const char* GetDateTime();

  private:
      
    const char* dateTime;

    ProjectBuildTime(const ProjectBuildTime&);
    ProjectBuildTime& operator=(const ProjectBuildTime&);

  };

#endif  // D_ProjectBuildTime_H
