#include <stdio.h>
#include <CscNetLib/netSrv.h>
#include <CscNetLib/std.h>
#include <CscNetLib/logger.h>

#define MaxLineLen 255

char *progName = NULL;

void usage()
{  
    fprintf(stderr, "Usage %s address port_number\n%s\n", progName,
    "This command takes three arguments from the command line. The first\n"
    "argument will be the address, and the second argument port number\n"
    );
//    exit 1;  // Non zero indicates success.
}

int main(int argc, char **argv)
{   
    netSrv_t *ntp = NULL;
    int fd = -1;
    FILE *fin = NULL;
    char line[MaxLineLen+1];

    logger_t *log;
    char *logPath;
    int logLevel;

    char msgPrint[80];	
	
// Initialise the logging.
    log = logger_new("log.txt", 1);
	
    if (log == NULL)
    {   
        fprintf(stderr, "Failed to initialise logging!");
        //exit(1);
    }
    else
    {
        logger_log(log, logger_logLevel_ERROR, "Initialise logging");
    }

	
// Get the name of the program invoked.
    progName = argv[0];	

// Check for correct number of arguments.
    if (argc != 3)
        usage();	

// Create netSrv object.
    ntp = netSrv_new();
    netSrv_setAddr(ntp, "TCP", argv[1], atoi(argv[2]), -1);

// For each successful connection.
    while ((fd = netSrv_accept(ntp)) >= 0)
    {   
        sprintf(msgPrint, "Connection from %s\n", netSrv_acceptAddr(ntp));
//        fprintf(stdout, "Connection from %s\n", netSrv_acceptAddr(ntp));
        logger_log(log, logger_logLevel_TRACE, msgPrint);
		
        fin = fdopen(fd, "r");
        if (fin == NULL)
        {
            //fprintf(stderr, "fdopen error");
            logger_log(log, logger_logLevel_ERROR, "fdopen error");
            return 1;
        }
        fgetline(fin,line,MaxLineLen);
        sprintf(msgPrint, "Got line: %s\n", line);
        logger_log(log, logger_logLevel_TRACE, msgPrint);
        //fprintf(stdout, "Got line: \"%s\"\n", line);
        fclose(fin);
    }
	
 
    netSrv_close(ntp);
	
// Release resources and quit.
    logger_close(log);

}

 

 
        


