//
//  log.h
//  ThreadPool
//
//  Created by Gal Argov Sofer on 2/4/18.
//  Copyright © 2018 Gal Argov Sofer. All rights reserved.
//

#ifndef log_h
#define log_h

#include <stdio.h>
#include <stdbool.h>

#define LOGFILE    "gl.log"     // all Log(); messages will be appended to this file

extern bool LogCreated;      // keeps track whether the log file is created or not

void Log (char *message);    // logs a message to LOGFILE
void LogErr (char *message); // logs a message; execution is interrupted


#endif /* log_h */
