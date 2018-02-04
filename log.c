//
//  log.c
//  ThreadPool
//
//  Created by Gal Argov Sofer on 2/4/18.
//  Copyright © 2018 Gal Argov Sofer. All rights reserved.
//

#include <stdlib.h>
#include <stdio.h>
#include "log.h"

bool LogCreated = false;

void Log (char *message)
{
    FILE *file;
    
    if (!LogCreated) {
        file = fopen(LOGFILE, "w");
        LogCreated = true;
    }
    else
        file = fopen(LOGFILE, "a");
    
    if (file == NULL) {
        if (LogCreated)
            LogCreated = false;
        return;
    }
    else
    {
        fputs(message, file);
        fclose(file);
    }
    
    if (file)
        fclose(file);
}

void LogErr (char *message)
{
    Log(message);
    Log("\n");
}

